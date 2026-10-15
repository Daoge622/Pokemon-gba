#!/usr/bin/env python3
"""Render a map layout to PNG (CLI only, no emulator).

  maprender.py MAP out.png [x0 y0 x1 y1] [--scale N]

Objects are drawn as red boxes, warps as blue boxes, bg events as yellow boxes.
"""
import os, re, sys
from PIL import Image, ImageDraw
sys.path.insert(0, os.path.dirname(__file__))
import maptool as t

ROOT = t.ROOT

def _tileset_paths():
    hdr = open(os.path.join(ROOT, 'src/data/tilesets/headers.h')).read()
    gfx = open(os.path.join(ROOT, 'src/data/tilesets/graphics.h')).read() + open(os.path.join(ROOT, 'src/graphics.c')).read()
    mt = open(os.path.join(ROOT, 'src/data/tilesets/metatiles.h')).read()
    tiles = dict(re.findall(r'const u32 (gTilesetTiles_\w+)\[\] = INC\w+\("([^"]+?)\.(?:png|4bpp)[^"]*"', gfx))
    metas = dict(re.findall(r'const u16 (gMetatiles_\w+)\[\] = INCBIN_U16\("([^"]+)"\)', mt))
    pals = {}
    for name, body in re.findall(r'const u16 (?:ALIGNED\(4\) )?(gTilesetPalettes_\w+)\[\]\[16\] =\s*\{(.*?)\};', gfx, re.S):
        pals[name] = re.findall(r'INC\w+\("([^"]+?)\.(?:pal|gbapal)"()', body)
    res = {}
    for name, body in re.findall(r'const struct Tileset (gTileset_\w+) =\s*\{(.*?)\};', hdr, re.S):
        g = lambda k: (re.search(r'\.%s = (\w+)' % k, body) or [None, None])[1]
        res[name] = dict(tiles=tiles.get(g('tiles')), metas=metas.get(g('metatiles')),
                         pals=[a or b for a, b in pals.get(g('palettes'), [])])
    return res

TSP = _tileset_paths()
_cache = {}

def load_pal(path):
    p = os.path.join(ROOT, path + '.pal')
    if not os.path.exists(p): return [(255, 0, 255)] * 16
    lines = open(p).read().split('\n')[3:19]
    return [tuple(int(v) for v in l.split()[:3]) for l in lines if l.strip()]

def load_ts(name):
    if name in _cache: return _cache[name]
    info = TSP[name]
    img = Image.open(os.path.join(ROOT, info['tiles'] + '.png'))
    w, h = img.size
    px = img.load()
    tiles = []
    for ty in range(h // 8):
        for tx in range(w // 8):
            tiles.append([[px[tx * 8 + x, ty * 8 + y] & 15 for x in range(8)] for y in range(8)])
    metas = t.u16s(os.path.join(ROOT, info['metas']))
    pals = [load_pal(p) for p in info['pals']]
    _cache[name] = (tiles, metas, pals)
    return _cache[name]

def render(m, x0=0, y0=0, x1=None, y1=None, scale=1, marks=True):
    x1 = m.w - 1 if x1 is None else x1; y1 = m.h - 1 if y1 is None else y1
    pt, pm, pp = load_ts(m.lay['primary_tileset'])
    st, sm, sp = load_ts(m.lay['secondary_tileset'])
    tiles = pt[:512] + [[[0] * 8 for _ in range(8)]] * (512 - len(pt[:512])) + st
    pals = pp[:6] + sp[6:13] + pp[13:]
    while len(pals) < 16: pals.append([(255, 0, 255)] * 16)
    W, H = (x1 - x0 + 1) * 16, (y1 - y0 + 1) * 16
    im = Image.new('RGB', (W, H), (0, 0, 0))
    px = im.load()
    for my in range(y0, y1 + 1):
        for mx in range(x0, x1 + 1):
            mid = m.mt(mx, my)
            meta = pm if mid < 512 else sm
            base = (mid if mid < 512 else mid - 512) * 8
            if base + 8 > len(meta): continue
            for layer in range(2):
                for i in range(4):
                    e = meta[base + layer * 4 + i]
                    ti, hf, vf, pal = e & 0x3FF, (e >> 10) & 1, (e >> 11) & 1, e >> 12
                    if ti >= len(tiles): continue
                    tl = tiles[ti]; cols = pals[pal]
                    ox = (mx - x0) * 16 + (i & 1) * 8; oy = (my - y0) * 16 + (i >> 1) * 8
                    for yy in range(8):
                        row = tl[7 - yy if vf else yy]
                        for xx in range(8):
                            c = row[7 - xx if hf else xx]
                            if c == 0 and layer == 1: continue
                            px[ox + xx, oy + yy] = cols[c] if c < len(cols) else (255, 0, 255)
    d = ImageDraw.Draw(im)
    if marks:
        def box(x, y, col):
            if x0 <= x <= x1 and y0 <= y <= y1:
                d.rectangle([(x - x0) * 16 + 1, (y - y0) * 16 + 1, (x - x0) * 16 + 14, (y - y0) * 16 + 14], outline=col, width=2)
        for o in m.j.get('object_events', []):
            x, y = t.coord(o.get('x')), t.coord(o.get('y'))
            if x is not None: box(x, y, (255, 0, 0))
        for w in m.j.get('warp_events', []): box(w['x'], w['y'], (0, 80, 255))
        for b in m.j.get('bg_events', []):
            x, y = t.coord(b.get('x')), t.coord(b.get('y'))
            if x is not None: box(x, y, (255, 220, 0))
    if scale != 1:
        im = im.resize((W * scale, H * scale), Image.NEAREST)
    return im

if __name__ == '__main__':
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    scale = 1
    if '--scale' in sys.argv: scale = int(sys.argv[sys.argv.index('--scale') + 1]); args.remove(str(scale))
    nomarks = '--nomarks' in sys.argv
    m = t.Map(args[0])
    box = [int(v) for v in args[2:6]] if len(args) >= 6 else []
    render(m, *box, scale=scale, marks=not nomarks).save(args[1])

def render_grid(m, x0, y0, x1, y1, scale=2):
    """Render with coordinate grid labels (for picking metatiles)."""
    im = render(m, x0, y0, x1, y1, scale=scale, marks=False)
    d = ImageDraw.Draw(im)
    s = 16 * scale
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            d.rectangle([(x - x0) * s, (y - y0) * s, (x - x0 + 1) * s - 1, (y - y0 + 1) * s - 1], outline=(0, 0, 0))
            if (x % 2 == 0 and y % 2 == 0):
                d.text(((x - x0) * s + 1, (y - y0) * s + 1), '%d,%d' % (x, y), fill=(255, 0, 0))
    return im
