#!/usr/bin/env python3
"""Source-only late-game terrain audit; never loads or executes a ROM.

Crosses real matching map connections, static warps and Dive/Emerge links.
Current tiles permit only forced movement until blocked. All field moves are
assumed available. Dynamic script warps, moving NPCs, puzzles, bikes and story
visibility still require manual review; a finding is not automatically a bug.
"""
import argparse
from collections import defaultdict, deque
import json
import re
from pathlib import Path
import maptool as t

ROOT = Path(t.ROOT)
DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))
CURRENT = {t.MBI["MB_" + name + "_CURRENT"]: d for name, d in
           zip(("EASTWARD", "WESTWARD", "SOUTHWARD", "NORTHWARD"), DIRS)}
SIDE = dict(zip(DIRS, ("EAST", "WEST", "SOUTH", "NORTH")))


class World:
    def __init__(self):
        self.maps = {}
        self.ids = {}
        self.raw = {}
        for p in (ROOT / "data/maps").glob("*/map.json"):
            j = json.loads(p.read_text(encoding="utf-8"))
            if j.get("region") != "REGION_HOENN":
                continue
            self.raw[p.parent.name] = j
            self.ids[j["id"]] = p.parent.name
        self.warps = {}
        self.bad_landings = set()
        self.fixed_dive = {}
        for name in self.raw:
            p = ROOT / 'data/maps' / name / 'scripts.inc'
            if p.exists():
                rows = re.findall(r'^\s*setdivewarp\s+(MAP_\w+),\s*(\d+),\s*(\d+)', p.read_text(encoding='utf-8'), re.M)
                # Multiple destinations depend on script conditions; report
                # those separately instead of inventing a universally open link.
                if len(rows) == 1:
                    self.fixed_dive[name] = rows[0]

    def m(self, name):
        if name not in self.maps:
            # This map unconditionally selects this layout in OnTransition.
            # The default JSON layout alone misses the Sky Pillar shore.
            layout = "LAYOUT_ROUTE131_SKY_PILLAR" if name == "Route131" else None
            self.maps[name] = t.Map(name, layout=layout)
            self.warps[name] = {(w["x"], w["y"]): w for w in
                                self.maps[name].j.get("warp_events", [])}
        return self.maps[name]

    def underwater(self, name):
        return self.raw[name]["map_type"] == "MAP_TYPE_UNDERWATER"

    def locate(self, name, x, y):
        m = self.m(name)
        if m.inb(x, y):
            return name, x, y
        for c in m.j.get("connections") or []:
            n = self.ids.get(c["map"])
            if not n:
                continue
            dest = self.m(n)
            d, o = c["direction"], c["offset"]
            if d == "right" and x == m.w: nx, ny = 0, y - o
            elif d == "left" and x == -1: nx, ny = dest.w - 1, y - o
            elif d == "down" and y == m.h: nx, ny = x - o, 0
            elif d == "up" and y == -1: nx, ny = x - o, dest.h - 1
            else: continue
            if dest.inb(nx, ny):
                return n, nx, ny
        return None

    @staticmethod
    def blocked(behavior, side):
        return side in t.DIRBLOCK.get(behavior, "")

    def step(self, state, d):
        name, x, y, elev, surf = state
        m = self.m(name)
        dest = self.locate(name, x + d[0], y + d[1])
        if not dest:
            return None
        n, nx, ny = dest
        nm = self.m(n)
        b, ne = nm.beh(nx, ny), nm.elev(nx, ny)
        if self.blocked(m.beh(x, y), SIDE[d]) or self.blocked(b, SIDE[(-d[0], -d[1])]):
            return None
        if b in t.JUMP and not surf:
            if t.JUMP[b] != d:
                return None
            land = self.locate(n, nx + d[0], ny + d[1])
            if not land or self.m(land[0]).coll(*land[1:]):
                return None
            lm = self.m(land[0])
            return (*land, lm.elev(*land[1:]), False)
        if nm.coll(nx, ny):
            return None
        if self.underwater(n):
            return (n, nx, ny, ne, False) if t.compatible(elev, ne) else None
        if surf:
            if b == t.WATERFALL:
                return (n, nx, ny, ne, True) if d[0] == 0 else None
            if t.compatible(elev, ne):
                return n, nx, ny, elev if ne == 15 else ne, True
            if ne == 3:
                return n, nx, ny, ne, False
            return None
        if t.compatible(elev, ne):
            return n, nx, ny, elev if ne == 15 else ne, False
        if elev == 3 and b in t.SURF and b != t.WATERFALL:
            return n, nx, ny, ne, True
        return None

    def links(self, state):
        name, x, y, elev, surf = state
        m = self.m(name)
        underwater = self.underwater(name)
        behavior = m.beh(x, y)
        if name in self.fixed_dive and ((underwater and behavior not in (t.NO_EMERGE | {t.MBI['MB_WATER_DOOR']})) or (surf and behavior in t.DIVEABLE)):
            const, wx, wy = self.fixed_dive[name]
            n = self.ids.get(const)
            wx, wy = int(wx), int(wy)
            if n:
                nm = self.m(n)
                if nm.inb(wx, wy) and not nm.coll(wx, wy):
                    yield n, wx, wy, nm.elev(wx, wy), not self.underwater(n)
        for c in m.j.get("connections") or []:
            dive = c["direction"] == "dive" and surf and behavior in t.DIVEABLE
            emerge = c["direction"] == "emerge" and underwater and behavior not in (t.NO_EMERGE | {t.MBI['MB_WATER_DOOR']})
            if not (dive or emerge):
                continue
            n = self.ids.get(c["map"])
            if not n:
                continue
            nm = self.m(n)
            # SetDiveWarp keeps x/y; connection offsets are NOT used here.
            if not nm.inb(x, y) or nm.coll(x, y):
                self.bad_landings.add((name, x, y, n, "dive" if dive else "emerge"))
                continue
            yield n, x, y, nm.elev(x, y), emerge
        w = self.warps[name].get((x, y))
        if w:
            n = self.ids.get(w["dest_map"])
            try: idx = int(w["dest_warp_id"])
            except (ValueError, TypeError): return
            if n:
                nm = self.m(n)
                ww = nm.j.get("warp_events", [])
                if 0 <= idx < len(ww):
                    wx, wy = ww[idx]["x"], ww[idx]["y"]
                    if nm.inb(wx, wy):
                        yield n, wx, wy, nm.elev(wx, wy), nm.surfable(wx, wy) and not self.underwater(n)

    def flood(self):
        # Actual engine Fly/heal positions, assuming destinations unlocked.
        # Never seed arbitrary map edges or sealed pockets of water.
        starts = []
        heal = json.loads((ROOT / "src/data/heal_locations.json").read_text(encoding="utf-8"))
        for h in heal["heal_locations"]:
            name = self.ids.get(h["map"])
            if name and self.raw[name]["map_type"] in ("MAP_TYPE_CITY", "MAP_TYPE_TOWN", "MAP_TYPE_ROUTE"):
                m = self.m(name)
                x, y = h["x"], h["y"]
                if m.inb(x, y) and not m.coll(x, y):
                    starts.append((name, x, y, m.elev(x, y), False))
        seen, q = set(starts), deque(starts)
        while q:
            st = q.popleft()
            m = self.m(st[0])
            forced = CURRENT.get(m.beh(st[1], st[2])) if st[4] else None
            forward = self.step(st, forced) if forced else None
            if forward:
                nxt = [forward]
            else:
                nxt = [self.step(st, d) for d in DIRS]
                nxt.extend(self.links(st))
            for ns in nxt:
                if ns is not None and ns not in seen:
                    seen.add(ns); q.append(ns)
        return seen

    def audit(self, seen):
        cells = defaultdict(set)
        stable = defaultdict(set)
        for n, x, y, e, surf in seen:
            cells[(n, x, y)].add(e)
            d = CURRENT.get(self.m(n).beh(x, y)) if surf else None
            if not d or not self.step((n, x, y, e, surf), d):
                stable[(n, x, y)].add(e)
        findings = []
        checked = 0
        for name in sorted({s[0] for s in seen}):
            m = self.m(name)
            for kind in ("object_events", "bg_events", "warp_events"):
                for i, obj in enumerate(m.j.get(kind, []), 1):
                    if obj.get("type") == "clone": continue
                    x, y = obj.get("x"), obj.get("y")
                    if not isinstance(x, int) or not isinstance(y, int) or not m.inb(x, y):
                        continue
                    if kind == "object_events" and obj.get("script") in ("0x0", "0", None, ""):
                        continue
                    if kind == "bg_events" and obj.get("type") == "secret_base":
                        continue
                    checked += 1
                    oe = obj.get("elevation", 0)
                    candidates = [(x + dx, y + dy) for dx, dy in DIRS]
                    if kind != "object_events": candidates.append((x, y))
                    for dx, dy in DIRS:
                        if m.inb(x+dx, y+dy) and m.beh(x+dx, y+dy) == t.COUNTER:
                            candidates.append((x+dx*2, y+dy*2))
                    # Object lookup compares elevation; zero matches any elevation.
                    ok = any(e == oe or not e or not oe
                             for px, py in candidates for e in stable[(name, px, py)])
                    if not ok:
                        findings.append(dict(map=name, kind=kind, index=i, x=x, y=y,
                                             local_id=obj.get("local_id", ""),
                                             script=obj.get("script", obj.get("item", "")),
                                             elevation=oe))
        reached = {s[0] for s in seen}
        outside = {'MAP_TYPE_ROUTE', 'MAP_TYPE_TOWN', 'MAP_TYPE_CITY', 'MAP_TYPE_OCEAN_ROUTE', 'MAP_TYPE_UNDERWATER'}
        return dict(states=len(seen), maps=len(reached), checked=checked,
                    unvisited_outdoor=sorted(n for n,j in self.raw.items() if n not in reached and j['map_type'] in outside),
                    findings=findings, unsafe_dive_landings=sorted(self.bad_landings))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--output", type=Path)
    args = ap.parse_args()
    world = World()
    report = world.audit(world.flood())
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, ensure_ascii=False, indent=2)+"\n", encoding="utf-8")
    print(f'{report["maps"]} maps, {report["states"]} reachable states, {report["checked"]} events checked')
    for f in report["findings"]:
        if "PART" in f["local_id"] or "Part" in f["script"] or f["map"].startswith(("Route12", "Route13", "Underwater")):
            print(f)
    print(f'{len(report["findings"])} candidates; {len(report["unsafe_dive_landings"])} unsafe Dive/Emerge landings')


if __name__ == "__main__":
    main()
