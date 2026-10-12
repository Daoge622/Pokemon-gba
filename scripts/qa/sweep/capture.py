#!/usr/bin/env python3
"""Capture a new species from the user's own save with real menu inputs (release/normal ROM)."""
import sys, os, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from rt import Harness
from pathlib import Path

rom = sys.argv[1]
h = Harness(rom, Path.home() / 'user-bug.sav', Path.home() / ('qa-capture-' + Path(rom).stem))
subprocess.run(['cp', str(Path.home() / 'qa-sweep/probe2'), str(h.out / 'probe')])
LOAD = 'frames 4000\nframes 4 8\nframes 500\nframes 4 1\nframes 900\n'


def tap(k, n=100):
    return f'frames 4 {k}\nframes {n}\n'


def case(species, level, dex_first=False):
    c = LOAD + h.script([('additem', 1, 10), ('setwildbattle', species, level), ('dowildbattle',), ('end',)])
    c += 'frames 1500\nscreen b0.png\n' + tap(1, 400) + 'screen b0b.png\n'
    # FIGHT/BAG menu: Right -> BAG, A, Right to Poke Ball pocket, A select, A use
    c += tap(16, 10) + tap(1, 140) + 'screen b1.png\n' + tap(16, 100) + 'screen b2.png\n' + tap(1, 30) + 'screen b3.png\n' + tap(1, 700)
    c += 'screen b4.png\n'
    for i in range(40):
        c += tap(2, 80)
        if i % 8 == 0:
            c += f'screen c{i:02d}.png\nread gBattleOutcome 1\nread {hex(h.main + 4)}\nstatus\n'
    c += f'frames 300\nscreen end.png\nread gBattleOutcome 1\nread {hex(h.main + 4)}\nstatus\n'
    return c


for name, (sp, lv) in {'caterpie-new': (10, 2), 'caterpie-again': (10, 2)}.items():
    rc, log, cb2 = h.run(name, case(sp, lv))
    print('=====', name, 'rc', rc)
    for line in log.splitlines():
        if line.startswith(('read gBattleOutcome', 'LOG', 'frame=')) or 'Jumped' in line:
            print(' ', line)
    print('  cb2:', [h.cb2_name(x) for x in cb2[-2:]])
