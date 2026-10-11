#!/usr/bin/env python3
"""Natural-input replay from the user's own save (release ROM). Keys: A1 B2 R16 L32 U64 D128."""
import sys, os, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from rt import Harness
from pathlib import Path

rom = sys.argv[1]
h = Harness(rom, Path.home() / 'user-bug.sav', Path.home() / ('qa-user2-' + Path(rom).stem))
subprocess.run(['cp', str(Path.home() / 'qa-sweep/probe2'), str(h.out / 'probe')])
LOAD = 'frames 4000\nframes 4 8\nframes 500\nframes 4 1\nframes 900\n' + h.script([('setvar', 0x4021, 250), ('end',)]) + 'frames 30\n'
POS = 'ptrread gSaveBlock1Ptr 0 2\nptrread gSaveBlock1Ptr 2 2\nptrread gSaveBlock1Ptr 5 1\n'
K = {'A': 1, 'B': 2, 'R': 16, 'L': 32, 'U': 64, 'D': 128}


def walk(d, tiles):
    return f'frames {tiles * 16 + 2} {K[d]}\nframes 10\n'


def press(k, n=1, gap=50):
    return ''.join(f'frames 4 {K[k]}\nframes {gap}\n' for _ in range(n))


def shot(name):
    return f'screen {name}.png\n{POS}status\nread {hex(h.main + 4)}\n'


cases = {k: v for k, v in {
    'stardust': LOAD + shot('s0') + walk('R', 5) + shot('s1') + press('A', 1) + shot('s2') + press('A', 12) + shot('s3'),
    'to-steven': LOAD + shot('s0') + walk('D', 5) + shot('s1') + walk('L', 3) + shot('s2') + walk('D', 1) + 'frames 150\n' + shot('s3')
    + 'frames 200\nframes 200 128\nframes 30\nscreen r1.png\n'
    + ''.join(f'frames 4 1\nframes 60\nscreen a{i:02d}.png\nstatus\nread {hex(h.main + 4)}\n' for i in range(40))
    + 'frames 400\n' + shot('s9'),
}.items() if k == 'to-steven'}
for name, c in cases.items():
    rc, log, cb2 = h.run(name, c)
    print('=====', name, rc)
    for line in log.splitlines():
        if line.startswith(('ptrread', 'frame=', 'LOG')) or 'read 0x3002414' in line:
            print(' ', line)
