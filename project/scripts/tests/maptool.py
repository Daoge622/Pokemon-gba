#!/usr/bin/env python3
"""Map inspection / reachability helper (CLI only, never runs the ROM).

Usage:
  maptool.py show MAP [x0 y0 x1 y1]     ASCII view: elevation digit, '#'=collision, '~'=water
  maptool.py reach MAP                  list objects / bg events the player cannot reach
  maptool.py reach-all [MAP...]         run reach on every outdoor map (or the given ones)

Movement model follows src/event_object_movement.c / field_player_avatar.c:
- a tile blocks if collision bits != 0 or it is directionally impassable;
- elevation mismatch unless either side is 0 (transition) or the tile is 15 (multi);
- surfing starts from elevation 3 into surfable water, and stops only on an
  elevation-3 tile with collision 0;
- ledges jump two tiles in their direction;
- entry points: every warp tile and every map edge that has a connection.
"""
import json, os, re, sys
from collections import deque

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))

def _behavior_names():
    txt = open(os.path.join(ROOT, 'include/constants/metatile_behaviors.h')).read()
    body = txt[txt.index('enum {') + 6: txt.index('};')]
    names = []
    for line in body.split('\n'):
        line = line.split('//')[0].strip().rstrip(',')
        if line.startswith('MB_'):
            names.append(line)
    return names

MB = _behavior_names()
MBI = {n: i for i, n in enumerate(MB)}

def _surfable():
    txt = open(os.path.join(ROOT, 'src/metatile_behavior.c')).read()
    return {MBI[m] for m in re.findall(r'\[(MB_\w+)\]\s*=[^\n]*TILE_FLAG_SURFABLE', txt) if m in MBI}

SURF = _surfable()
WATERFALL = MBI['MB_WATERFALL']
COUNTER = MBI.get('MB_COUNTER')
JUMP = {MBI['MB_JUMP_EAST']: (1, 0), MBI['MB_JUMP_WEST']: (-1, 0),
        MBI['MB_JUMP_NORTH']: (0, -1), MBI['MB_JUMP_SOUTH']: (0, 1)}
DIRBLOCK = {}
for n, i in MBI.items():
    if n.startswith('MB_IMPASSABLE_'):
        DIRBLOCK[i] = n[len('MB_IMPASSABLE_'):]

def _tileset_dirs():
    hdr = open(os.path.join(ROOT, 'src/data/tilesets/headers.h')).read()
    mt = open(os.path.join(ROOT, 'src/data/tilesets/metatiles.h')).read()
    attr = dict(re.findall(r'(gMetatileAttributes_\w+)\[\] = INCBIN_U16\("([^"]+)"\)', mt))
    res = {}
    for name, body in re.findall(r'const struct Tileset (gTileset_\w+) =\s*\{(.*?)\};', hdr, re.S):
        m = re.search(r'\.metatileAttributes = (\w+)', body)
        if m and m.group(1) in attr:
            res[name] = os.path.join(ROOT, attr[m.group(1)])
    return res

TS = _tileset_dirs()
_LAYOUTS = None

def layouts():
    global _LAYOUTS
    if _LAYOUTS is None:
        j = json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))
        _LAYOUTS = {l['id']: l for l in j['layouts'] if 'id' in l}
    return _LAYOUTS

def u16s(path):
    b = open(path, 'rb').read()
    return [b[i] | (b[i + 1] << 8) for i in range(0, len(b) - 1, 2)]

class Map:
    def __init__(self, name, layout=None):
        self.name = name
        self.dir = os.path.join(ROOT, 'data/maps', name)
        self.j = json.load(open(os.path.join(self.dir, 'map.json')))
        self.lay = layouts()[layout or self.j['layout']]
        self.w, self.h = self.lay['width'], self.lay['height']
        self.binpath = os.path.join(ROOT, self.lay['blockdata_filepath'])
        self.grid = u16s(self.binpath)
        pa = u16s(TS[self.lay['primary_tileset']])
        sa = u16s(TS[self.lay['secondary_tileset']])
        self.attrs = pa + [0] * (512 - len(pa)) + sa

    def save(self):
        with open(self.binpath, 'wb') as f:
            for v in self.grid:
                f.write(bytes([v & 0xFF, v >> 8]))

    def inb(self, x, y):
        return 0 <= x < self.w and 0 <= y < self.h

    def raw(self, x, y):
        return self.grid[y * self.w + x]

    def set(self, x, y, metatile=None, coll=None, elev=None):
        v = self.raw(x, y)
        mt, c, e = v & 0x3FF, (v >> 10) & 3, v >> 12
        if metatile is not None: mt = metatile
        if coll is not None: c = coll
        if elev is not None: e = elev
        self.grid[y * self.w + x] = mt | (c << 10) | (e << 12)

    def mt(self, x, y): return self.raw(x, y) & 0x3FF
    def coll(self, x, y): return (self.raw(x, y) >> 10) & 3
    def elev(self, x, y): return self.raw(x, y) >> 12

    def beh(self, x, y):
        m = self.mt(x, y)
        return self.attrs[m] & 0xFF if m < len(self.attrs) else 0

    def surfable(self, x, y): return self.beh(x, y) in SURF

    def show(self, x0=0, y0=0, x1=None, y1=None, marks=None):
        x1 = self.w - 1 if x1 is None else x1
        y1 = self.h - 1 if y1 is None else y1
        marks = marks or {}
        out = ['    ' + ''.join(str(x % 10) for x in range(x0, x1 + 1))]
        for y in range(y0, y1 + 1):
            row = ''
            for x in range(x0, x1 + 1):
                if (x, y) in marks: row += marks[(x, y)]; continue
                b = self.beh(x, y)
                if self.coll(x, y): ch = '#'
                elif b in SURF: ch = '~' if b != WATERFALL else 'W'
                elif b in JUMP: ch = {(1,0):'>',(-1,0):'<',(0,-1):'^',(0,1):'v'}[JUMP[b]]
                else:
                    e = self.elev(x, y); ch = 'abcdefghijklmnopqrstuvwxyz'[e] if e > 9 else str(e)
                row += ch
            out.append('%3d ' % y + row)
        return '\n'.join(out)

def _blocked_dir(b, dx, dy, entering=True):
    n = DIRBLOCK.get(b)
    if not n: return False
    d = {(1,0):'WEST',(-1,0):'EAST',(0,1):'NORTH',(0,-1):'SOUTH'}[(dx,dy)]  # side we enter from
    return d in n.split('_AND_') or any(d in part for part in n.split('_'))

def compatible(pe, te):
    return pe == 0 or te in (0, 15) or pe == te

def reach(m, starts, objects_block=None):
    """BFS over (x, y, elev, surfing). Returns set of reachable (x, y, elev)."""
    objects_block = objects_block or set()
    seen = set()
    q = deque()
    for s in starts:
        if s not in seen: seen.add(s); q.append(s)
    while q:
        x, y, e, surf = q.popleft()
        for dx, dy in ((1,0),(-1,0),(0,1),(0,-1)):
            nx, ny = x + dx, y + dy
            if not m.inb(nx, ny): continue
            b = m.beh(nx, ny); te = m.elev(nx, ny)
            nxt = None
            if b in JUMP and not surf:
                if JUMP[b] == (dx, dy):
                    lx, ly = nx + dx, ny + dy
                    if m.inb(lx, ly) and not m.coll(lx, ly):
                        nxt = (lx, ly, m.elev(lx, ly), False)
            elif m.coll(nx, ny) or (nx, ny) in objects_block or _blocked_dir(b, dx, dy):
                pass
            elif surf:
                if b in SURF and b != WATERFALL and compatible(e, te):
                    nxt = (nx, ny, te, True)
                elif b == WATERFALL and dy == -1:
                    nxt = (nx, ny, e, True)
                elif te == 3 and b not in SURF:
                    nxt = (nx, ny, 3, False)
            else:
                if compatible(e, te) and not (b in SURF and te not in (0, 15) and e != te):
                    if b in SURF and e == te:
                        nxt = (nx, ny, te, True)
                    else:
                        nxt = (nx, ny, te, False)
                elif e == 3 and b in SURF:
                    nxt = (nx, ny, te, True)
            if nxt and nxt not in seen:
                seen.add(nxt); q.append(nxt)
    return {(x, y, e) for x, y, e, s in seen} | {(x, y, -1 if s else -2) for x, y, e, s in seen}

def entry_points(m):
    starts = []
    for w in m.j.get('warp_events', []):
        x, y = w['x'], w['y']
        starts.append((x, y, m.elev(x, y) or 3, m.surfable(x, y)))
    conns = m.j.get('connections') or []
    for c in conns:
        d = c['direction']
        if d in ('dive', 'emerge'): continue
        if d == 'up': cells = [(x, 0) for x in range(m.w)]
        elif d == 'down': cells = [(x, m.h - 1) for x in range(m.w)]
        elif d == 'left': cells = [(0, y) for y in range(m.h)]
        else: cells = [(m.w - 1, y) for y in range(m.h)]
        for x, y in cells:
            if m.coll(x, y): continue
            starts.append((x, y, m.elev(x, y), m.surfable(x, y)))
    return starts

def coord(v):
    try: return int(v)
    except (TypeError, ValueError): return None

DIVEABLE = {MBI['MB_INTERIOR_DEEP_WATER'], MBI['MB_DEEP_WATER'], MBI['MB_SOOTOPOLIS_DEEP_WATER']}
NO_EMERGE = {MBI['MB_NO_SURFACING'], MBI['MB_SEAWEED_NO_SURFACING']}

def map_dir_name(const):
    # MAP_UNDERWATER_ROUTE124 -> Underwater_Route124 via map_groups lookup
    global _MAPCONST
    try: _MAPCONST
    except NameError:
        _MAPCONST = {}
        for d in os.listdir(os.path.join(ROOT, 'data/maps')):
            p = os.path.join(ROOT, 'data/maps', d, 'map.json')
            if os.path.exists(p):
                _MAPCONST[json.load(open(p))['id']] = d
    return _MAPCONST.get(const)

def underwater_reach(u, starts):
    seen = set(starts); q = deque(starts)
    while q:
        x, y = q.popleft()
        for dx, dy in ((1,0),(-1,0),(0,1),(0,-1)):
            nx, ny = x + dx, y + dy
            if u.inb(nx, ny) and not u.coll(nx, ny) and (nx, ny) not in seen:
                seen.add((nx, ny)); q.append((nx, ny))
    return seen

def surface_with_dive(m, starts):
    dive = [c for c in (m.j.get('connections') or []) if c['direction'] == 'dive']
    r = reach(m, starts)
    if not dive: return r, None, set()
    u = Map(map_dir_name(dive[0]['map']))
    uw = set()
    while True:
        dives = [(x, y) for x, y, e in r if e == -1 and m.beh(x, y) in DIVEABLE and u.inb(x, y) and not u.coll(x, y)]
        nuw = underwater_reach(u, [d for d in dives if d not in uw]) | uw
        emerge = [(x, y, m.elev(x, y), True) for x, y in nuw - uw
                  if u.beh(x, y) not in NO_EMERGE and m.beh(x, y) in DIVEABLE]
        if nuw == uw: break
        uw = nuw
        r = reach(m, list(starts) + emerge)
    return r, u, uw

def unreachable(m, extra_starts=()):
    starts = entry_points(m) + list(extra_starts)
    r, u, uw = surface_with_dive(m, starts)
    m.underwater = (u, uw)
    cells = {(x, y) for x, y, e in r}
    elev_at = {}
    for x, y, e in r: elev_at.setdefault((x, y), set()).add(e)
    bad = []
    def talkable(x, y, oe):
        for dx, dy in ((1,0),(-1,0),(0,1),(0,-1)):
            for k in (1, 2):
                px, py = x + dx * k, y + dy * k
                if k == 2:
                    mid = (x + dx, y + dy)
                    if not m.inb(*mid) or m.beh(*mid) != COUNTER: continue
                if (px, py) in cells:
                    return True
        return False
    for i, o in enumerate(m.j.get('object_events', [])):
        if o.get('type') == 'clone': continue
        x, y = coord(o.get('x')), coord(o.get('y'))
        if x is None or not m.inb(x, y): continue
        if o.get('graphics_id', '').endswith('ITEM_BALL') or o.get('script') not in ('0x0', '0', None, ''):
            if not talkable(x, y, o.get('elevation')):
                bad.append(('object', i + 1, o.get('local_id', ''), o.get('graphics_id'), x, y, o.get('script')))
    for b in m.j.get('bg_events', []):
        x, y = coord(b.get('x')), coord(b.get('y'))
        if x is None or not m.inb(x, y): continue
        if b.get('type') == 'hidden_item':
            if (x, y) not in cells and not talkable(x, y, 0):
                bad.append(('hidden', b.get('item'), b.get('flag'), x, y))
        elif not talkable(x, y, 0) and (x, y) not in cells:
            bad.append(('bg', b.get('script'), x, y))
    return bad, r

def outdoor_maps():
    res = []
    for d in sorted(os.listdir(os.path.join(ROOT, 'data/maps'))):
        p = os.path.join(ROOT, 'data/maps', d, 'map.json')
        if not os.path.exists(p): continue
        j = json.load(open(p))
        if j.get('map_type') in ('MAP_TYPE_ROUTE', 'MAP_TYPE_TOWN', 'MAP_TYPE_CITY', 'MAP_TYPE_OCEAN_ROUTE'):
            res.append(d)
    return res

if __name__ == '__main__':
    cmd = sys.argv[1]
    if cmd == 'show':
        m = Map(sys.argv[2])
        a = [int(v) for v in sys.argv[3:7]] or [0, 0, m.w - 1, m.h - 1]
        marks = {}
        for o in m.j.get('object_events', []):
            x, y = coord(o.get('x')), coord(o.get('y'))
            if x is not None: marks[(x, y)] = 'O'
        for w in m.j.get('warp_events', []): marks[(w['x'], w['y'])] = 'D'
        print(m.show(*a, marks=marks))
    elif cmd in ('reach', 'reach-all'):
        names = sys.argv[2:] if (cmd == 'reach' or len(sys.argv) > 2) else outdoor_maps()
        total = 0
        for n in names:
            m = Map(n)
            bad, _ = unreachable(m)
            for b in bad:
                print(n, *b); total += 1
        print('unreachable:', total)

def show_reach(name, x0=0, y0=0, x1=None, y1=None):
    m = Map(name)
    bad, r = unreachable(m)
    cells = {(x, y) for x, y, e in r}
    x1 = m.w - 1 if x1 is None else x1; y1 = m.h - 1 if y1 is None else y1
    marks = {}
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            if (x, y) in cells and not m.coll(x, y):
                marks[(x, y)] = '.' if not m.surfable(x, y) else ','
    for o in m.j.get('object_events', []):
        x, y = coord(o.get('x')), coord(o.get('y'))
        if x is not None: marks[(x, y)] = 'O'
    for w in m.j.get('warp_events', []): marks[(w['x'], w['y'])] = 'D'
    print(m.show(x0, y0, x1, y1, marks))

if __name__ == '__main__' and sys.argv[1] == 'showreach':
    show_reach(sys.argv[2], *[int(v) for v in sys.argv[3:7]])

def save_json(m):
    with open(os.path.join(m.dir, 'map.json'), 'w') as f:
        f.write(json.dumps(m.j, indent=2, ensure_ascii=False) + '\n')

def obj(m, local_id=None, script=None):
    for o in m.j['object_events']:
        if (local_id and o.get('local_id') == local_id) or (script and o.get('script') == script):
            return o
    raise KeyError(local_id or script)
