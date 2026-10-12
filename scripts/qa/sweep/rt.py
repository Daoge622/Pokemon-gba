#!/usr/bin/env python3
"""Headless mGBA runtime harness that also works on LTO release builds.
Setup is done by a tiny event script written into RAM (gStringVar4) and run by the game's own script engine.
User authorized silent mGBA runs on 2026-10-08. ROM and save inputs are never modified."""
import subprocess, re, os, shutil, struct
from pathlib import Path

R = Path.home() / 'projects/emerald-story'
OP = {'end': 0x02, 'waitstate': 0x27, 'setvar': 0x16, 'setflag': 0x29, 'clearflag': 0x2a, 'warpsilent': 0x3a, 'additem': 0x44, 'setmonmove': 0x7b}


class Harness:
    def __init__(self, rom, save, out):
        self.rom, self.elf, self.out = Path(rom), Path(rom).with_suffix('.elf'), Path(out)
        self.out.mkdir(parents=True, exist_ok=True)
        nm = subprocess.check_output(['arm-none-eabi-nm', str(self.elf)], text=True)
        (self.out / 'symbols.txt').write_text(nm)
        self.sym = {}
        for line in nm.splitlines():
            m = re.fullmatch(r'([0-9a-f]+) ([A-Za-z]) (\S+)', line)
            if m:
                name = m[3].split('.lto_priv')[0]
                self.sym.setdefault(name, int(m[1], 16))
        if not (self.out / 'probe').exists():
            subprocess.run(['cc', str(R / 'scripts/qa/gameplay-probe.c'), '-o', str(self.out / 'probe'), '-lmgba'], check=True)
        shutil.copyfile(save, self.out / 'input.sav')
        self.main = self.sym['gMain']
        self.buf = self.sym['gStringVar4']

    def a(self, name):
        return hex(self.sym[name])

    def script(self, cmds):
        """cmds: list of (op, args...) -> probe commands writing bytecode to gStringVar4 and running it."""
        b = b''
        for c in cmds:
            op, args = c[0], c[1:]
            if op in ('setflag', 'clearflag'):
                b += struct.pack('<BH', OP[op], args[0])
            elif op == 'setvar':
                b += struct.pack('<BHH', OP[op], args[0], args[1])
            elif op == 'additem':
                b += struct.pack('<BHH', OP[op], args[0], args[1])
            elif op == 'setmonmove':
                b += struct.pack('<BBBH', OP[op], args[0], args[1], args[2])
            elif op == 'warpsilent':
                mp, x, y = args
                b += struct.pack('<BBBBhh', OP[op], mp >> 8, mp & 0xFF, 0xFF, x, y) + bytes([OP['waitstate']])
            elif op == 'setwildbattle':
                sp, lv = args
                b += struct.pack('<BHBHHBH', 0xb6, sp, lv, 0, 0, 0, 0)
            elif op == 'dowildbattle':
                b += bytes([0xb7])
            elif op == 'end':
                b += bytes([OP['end']])
        s = ''.join(f'write {hex(self.buf + i)} {v} 1\n' for i, v in enumerate(b))
        return s + f'call ScriptContext_SetupScript {hex(self.buf)}\n'

    LOAD = 'frames 4000\nframes 4 8\nframes 500\nframes 4 1\nframes 700\n'

    def run_script(self, label, last_talked=0, facing=1):
        return (f'write gSpecialVar_LastTalked {last_talked} 2\nwrite gSpecialVar_Facing {facing} 2\n'
                f'call ScriptContext_SetupScript {self.a(label) if label in self.sym else label}\n')

    @staticmethod
    def taps(n, key=1, gap=60, shot_every=0):
        s = ''
        for i in range(n):
            s += f'frames 4 {key}\nframes {gap}\n'
            if shot_every and i % shot_every == 0:
                s += f'screen t{i:03d}.png\n'
        return s

    def tail(self):
        return f'status\nread {hex(self.main + 4)}\nread {hex(self.main)}\nscreen end.png\n'

    def run(self, name, commands, timeout=600):
        d = self.out / name
        d.mkdir(exist_ok=True)
        (d / 'commands.txt').write_text(commands)
        p = subprocess.run([str(self.out / 'probe'), '--allow-rom-execution', str(self.rom), str(self.out / 'symbols.txt'),
                            str(d / 'commands.txt'), str(self.out / 'input.sav')], cwd=d, capture_output=True, text=True, timeout=timeout)
        log = p.stdout + p.stderr
        (d / 'result.log').write_text(log)
        cb2 = re.findall(r'read 0x[0-9a-f]+=0x([0-9a-f]{8})', log)
        return p.returncode, log, cb2

    def cb2_name(self, value):
        v = int(value, 16) & ~1
        best = None
        for n, a in self.sym.items():
            if (a & ~1) == v:
                return n
        return hex(v)
