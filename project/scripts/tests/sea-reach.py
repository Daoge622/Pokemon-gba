#!/usr/bin/env python3
"""Cross-map surf/walk reachability for the Hoenn sea, starting on land in Mossdeep.

maptool.unreachable() checks one map at a time and treats every map edge as an
entry point, so a pocket of water fenced off by reefs still looks reachable.
This walks across map connections instead (no Dive, no Waterfall) and lists
every object on a sea map that no surface path can reach.
Vanilla dive-only spots (e.g. some Route 124 shards, Sootopolis, Ever Grande)
are expected in the output; anything new from story work is a bug.
"""
import json, os, sys
from collections import deque
sys.path.insert(0, os.path.dirname(__file__))
import maptool as t

ROOT = os.path.join(os.path.dirname(__file__), '..', '..', 'data', 'maps')
SEA = ['Route124', 'Route125', 'Route126', 'Route127', 'Route128', 'Route129', 'Route130',
       'Route131', 'Route132', 'Route133', 'Route134', 'MossdeepCity', 'EverGrandeCity',
       'SootopolisCity', 'PacifidlogTown', 'LilycoveCity', 'SlateportCity']
D = {'R': (1, 0), 'L': (-1, 0), 'D': (0, 1), 'U': (0, -1)}
_maps, _const = {}, {}

def M(name):
    if name not in _maps:
        _maps[name] = (t.Map(name), json.load(open(os.path.join(ROOT, name, 'map.json'))).get('connections') or [])
    return _maps[name]

def const_to_name(c):
    if not _const:
        grp = json.load(open(os.path.join(ROOT, 'map_groups.json')))
        for g in grp['group_order']:
            for n in grp[g]:
                _const[json.load(open(os.path.join(ROOT, n, 'map.json')))['id']] = n
    return _const.get(c)

def cross(name, x, y):
    m, conns = M(name)
    for c in conns:
        d, o = c['direction'], c['offset']
        tn = const_to_name(c['map'])
        if tn not in SEA: continue
        tm, _ = M(tn)
        if d == 'down' and y >= m.h: nx, ny = x - o, 0
        elif d == 'up' and y < 0: nx, ny = x - o, tm.h - 1
        elif d == 'right' and x >= m.w: nx, ny = 0, y - o
        elif d == 'left' and x < 0: nx, ny = tm.w - 1, y - o
        else: continue
        if tm.inb(nx, ny): return tn, nx, ny
    return None

def step(m, x, y, e, surf, dx, dy):
    nx, ny = x + dx, y + dy
    b = m.beh(nx, ny); te = m.elev(nx, ny)
    if b in t.JUMP and not surf:
        if t.JUMP[b] == (dx, dy):
            lx, ly = nx + dx, ny + dy
            if m.inb(lx, ly) and not m.coll(lx, ly): return (lx, ly, m.elev(lx, ly), False)
        return None
    if m.coll(nx, ny) or t._blocked_dir(b, dx, dy): return None
    if surf:
        if b in t.SURF and b != t.WATERFALL and t.compatible(e, te): return (nx, ny, te, True)
        if te == 3 and b not in t.SURF: return (nx, ny, 3, False)
        return None
    if t.compatible(e, te) and not (b in t.SURF and te not in (0, 15) and e != te):
        return (nx, ny, te, b in t.SURF and e == te)
    if e == 3 and b in t.SURF: return (nx, ny, te, True)
    return None

def flood(start):
    seen = {start}; q = deque([start])
    while q:
        n, x, y, e, s = q.popleft(); m, _ = M(n)
        for dx, dy in D.values():
            if m.inb(x + dx, y + dy):
                r = step(m, x, y, e, s, dx, dy)
                if not r: continue
                st = (n,) + r
            else:
                c = cross(n, x + dx, y + dy)
                if not c: continue
                tm, _ = M(c[0])
                if tm.coll(c[1], c[2]): continue
                st = (c[0], c[1], c[2], e if s else tm.elev(c[1], c[2]), s)
            if st not in seen: seen.add(st); q.append(st)
    return {(a[0], a[1], a[2]) for a in seen}

def main():
    cells = flood(('MossdeepCity', 32, 30, 3, False))
    bad = 0
    for n in SEA:
        for o in json.load(open(os.path.join(ROOT, n, 'map.json')))['object_events']:
            if 'BERRY_TREE' in o['graphics_id']: continue
            x, y = o['x'], o['y']
            if not any((n, x + dx, y + dy) in cells for dx, dy in D.values()):
                bad += 1
                print('unreachable by surface:', n, o.get('local_id') or o['graphics_id'], x, y, o['script'])
    print('objects unreachable by surface: %d' % bad)

if __name__ == '__main__':
    main()
