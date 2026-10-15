#!/usr/bin/env python3
"""Print the crash breadcrumbs a CRASH_TRACE=1 build left in a .sav.

usage: read-crash-trace.py SAVE.sav [pokeemerald-release.map] [count]
Shows the last entries (newest last) with function addresses resolved
against the linker map of the same debug build.
"""
import bisect, json, os, re, struct, sys

def load_syms(path):
    syms = []
    for line in open(path):
        m = re.match(r'\s+0x([0-9a-f]{8,16})\s+(\S+)\s*$', line)
        if m:
            syms.append((int(m.group(1), 16), m.group(2)))
    syms.sort()
    return syms

def name(syms, addr):
    if not addr or not syms:
        return '%08x' % addr
    a = addr & ~1
    i = bisect.bisect_right([s[0] for s in syms], a) - 1
    if i < 0:
        return '%08x' % addr
    base, n = syms[i]
    return n if a == base else '%s+%x' % (n, a - base)

def map_names():
    root = os.path.join(os.path.dirname(__file__), '..', '..', 'data', 'maps')
    grp = json.load(open(os.path.join(root, 'map_groups.json')))
    return [grp[g] for g in grp['group_order']]

def main():
    sav = open(sys.argv[1], 'rb').read()
    syms = load_syms(sys.argv[2]) if len(sys.argv) > 2 else []
    count = int(sys.argv[3]) if len(sys.argv) > 3 else 12
    groups = map_names()
    entries = []
    for sector in (30, 31):
        for slot in range(64):
            off = sector * 0x1000 + slot * 64
            e = sav[off:off + 64]
            if len(e) < 64 or struct.unpack_from('<H', e)[0] != 0xC7A5:
                break
            entries.append(struct.unpack('<HHIBBhhBBIIII4IIIII', e))
    if not entries:
        print('no crash-trace entries found'); return
    # sequence numbers are u16 and may wrap: order by distance from the first
    base = entries[0][1]
    entries.sort(key=lambda e: (e[1] - base) & 0xFFFF)
    for e in entries[-count:]:
        (_, seq, frame, g, n, x, y, av, ntasks, cb1, cb2, vb, hb,
         t0, t1, t2, t3, bgm, se1, se2, bgmst) = e
        try: mapn = groups[g][n]
        except IndexError: mapn = '%d.%d' % (g, n)
        print('#%d frame %d  %s (%d,%d) avatar=%#x' % (seq, frame, mapn, x, y, av))
        print('   cb1=%s cb2=%s vblank=%s hblank=%s' % tuple(name(syms, v) for v in (cb1, cb2, vb, hb)))
        print('   tasks(%d): %s' % (ntasks, ', '.join(name(syms, t) for t in (t0, t1, t2, t3) if t)))
        print('   bgm=%s status=%#x se1=%s se2=%s' % (name(syms, bgm), bgmst, name(syms, se1), name(syms, se2)))

if __name__ == '__main__':
    main()
