#!/usr/bin/env python3
"""Stack high-water mark for several scenarios from the user's save."""
import sys, os, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from rt import Harness
from pathlib import Path

rom = sys.argv[1]
h = Harness(rom, Path.home() / 'user-bug.sav', Path.home() / ('qa-stack-' + Path(rom).stem))
subprocess.run(['cp', str(Path.home() / 'qa-sweep/probe2'), str(h.out / 'probe')])
LO, HI = '0x03006e98', '0x03007e00'
LOAD = 'frames 4000\nframes 4 8\nframes 500\nframes 4 1\nframes 900\n'
FILL, SCAN = f'stackfill {LO}\n', f'stackscan {LO} {HI}\n'   # fill only below the live SP
REPEL = h.script([('setvar', 0x4021, 250), ('end',)]) + 'frames 30\n'


def walk(k, t):
    return f'frames {t * 16 + 2} {k}\nframes 10\n'


def tap(k, n=60):
    return f'frames 4 {k}\nframes {n}\n'


steven = REPEL + walk(128, 5) + walk(32, 3) + walk(128, 1) + 'frames 350\nframes 200 128\nframes 30\n' + ''.join(tap(1) for _ in range(40)) + 'frames 400\n'
battle = h.script([('additem', 1, 10), ('setwildbattle', 10, 2), ('dowildbattle',), ('end',)]) + 'frames 1500\n' + tap(1, 400) \
    + tap(16, 10) + tap(1, 140) + tap(16, 100) + tap(1, 30) + tap(1, 700) + ''.join(tap(2, 80) for _ in range(40)) + 'frames 300\n'
fight = h.script([('setwildbattle', 41, 5), ('dowildbattle',), ('end',)]) + 'frames 1500\n' + ''.join(tap(1, 60) for _ in range(60)) + 'frames 300\n'
menu = tap(8, 60) + tap(1, 200) + tap(2, 100) + tap(2, 100) + tap(8, 60) + tap(128, 20) + tap(1, 300) + tap(2, 100) + tap(2, 100)
cases = {'idle': 'frames 600\n', 'steven': steven, 'capture': battle, 'wild-fight': fight, 'start-menu': menu}
for name, body in cases.items():
    rc, log, cb2 = h.run(name, LOAD + FILL + body + SCAN + f'status\nread {hex(h.main + 4)}\n')
    out = [l for l in log.splitlines() if l.startswith(('stackfill', 'stackscan', 'frame=')) or 'Jumped' in l]
    print(f'{name:12s}', ' | '.join(out[:1] + out[-2:]))
