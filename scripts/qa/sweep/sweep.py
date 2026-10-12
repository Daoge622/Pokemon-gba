#!/usr/bin/env python3
"""Whole-game event sweep (headless mGBA, user authorized 2026-10-08).
For every Emerald map: warp next to each object / sign / trigger, run its script, press A then B, and record
the final main callback, crash screens, resets and debug-log asserts. RAM-only; ROM/save never modified.
usage: sweep.py ROM SAVE OUTDIR [map-filter]"""
import json, re, sys, os, struct, subprocess, concurrent.futures as cf
from pathlib import Path

R = Path.home() / 'projects/emerald-story'
ROM, SAVE, OUT = Path(sys.argv[1]), Path(sys.argv[2]), Path(sys.argv[3])
FILTER = sys.argv[4] if len(sys.argv) > 4 else None
ELF = ROM.with_suffix('.elf')
PROBE = Path.home() / 'qa-sweep/probe2'
OUT.mkdir(parents=True, exist_ok=True)

nm = subprocess.check_output(['arm-none-eabi-nm', str(ELF)], text=True)
(OUT / 'symbols.txt').write_text(nm)
sym = {}
for line in nm.splitlines():
    m = re.fullmatch(r'([0-9a-f]+) ([A-Za-z]) (\S+)', line)
    if m:
        sym.setdefault(m[3].split('.lto_priv')[0], int(m[1], 16))
addr2name = {}
for n, a in sym.items():
    addr2name.setdefault(a & ~1, n)
MAIN, BUF = sym['gMain'], sym['gStringVar4']

consts = {}
for m in re.finditer(r'(MAP_\w+)\s*=\s*\((\d+) \| \((\d+) << 8\)\)', (R / 'include/constants/map_groups.h').read_text()):
    consts[m[1]] = int(m[2]) | (int(m[3]) << 8)
groups = json.loads((R / 'data/maps/map_groups.json').read_text())
maps = [n for g in groups['group_order'] for n in groups[g]]


def wscript(mapc, x, y):
    b = struct.pack('<BBBBhh', 0x3a, mapc >> 8, mapc & 0xFF, 0xFF, x, y) + b'\x27\x02'   # warpsilent, waitstate, end
    return ''.join(f'write {hex(BUF + i)} {v} 1\n' for i, v in enumerate(b)) + f'call ScriptContext_SetupScript {hex(BUF)}\n'


cases = []   # (map, kind, idx, label, x, y, localid)
skipped = []
for name in maps:
    if FILTER and not re.search(FILTER, name):
        continue
    p = R / f'data/maps/{name}/map.json'
    if not p.exists():
        continue
    v = json.loads(p.read_text())
    mc = consts.get(v['id'])
    if mc is None:
        continue
    for i, o in enumerate(v.get('object_events') or []):
        s = o.get('script', '0x0')
        if s in ('0x0', '0', ''):
            continue
        cases.append((name, 'obj', i, s, o['x'], o['y'] + 1, i + 1, mc))
    for i, b in enumerate(v.get('bg_events') or []):
        if b.get('type') == 'sign' and b.get('script') not in (None, '0x0'):
            cases.append((name, 'sign', i, b['script'], b['x'], b['y'] + 1, 0, mc))
    for i, c in enumerate(v.get('coord_events') or []):
        if c.get('script') not in (None, '0x0'):
            cases.append((name, 'coord', i, c['script'], c['x'], c['y'], 0, mc))
runnable = []
for c in cases:
    if c[3] in sym:
        runnable.append(c)
    else:
        skipped.append(c)

LOAD = 'frames 4000\nframes 4 8\nframes 500\nframes 4 1\nframes 700\n'


def case_cmds(c, k):
    name, kind, idx, label, x, y, lid, mc = c
    s = f'load boot.ss\nmark {k}\n' + wscript(mc, x, y) + 'frames 500\n'
    s += f'write gSpecialVar_LastTalked {lid} 2\nwrite gSpecialVar_Facing 2 2\ncall ScriptContext_SetupScript {hex(sym[label])}\n'
    for _ in range(22):
        s += 'frames 4 1\nframes 40\n'
    for _ in range(6):
        s += 'frames 4 2\nframes 30\n'
    s += f'status\nread {hex(MAIN + 4)}\nread {hex(MAIN)}\n'
    return s


def chunk_run(ci, chunk):
    d = OUT / f'chunk{ci:03d}'
    d.mkdir(exist_ok=True)
    cmds = LOAD + 'state boot.ss\n' + ''.join(case_cmds(c, k) for k, c in chunk)
    (d / 'commands.txt').write_text(cmds)
    p = subprocess.run([str(PROBE), '--allow-rom-execution', str(ROM), str(OUT / 'symbols.txt'), str(d / 'commands.txt'), str(SAVE)],
                       cwd=d, capture_output=True, text=True, timeout=7200)
    out = p.stdout + p.stderr
    (d / 'result.log').write_text(out)
    res = {}
    cur = None
    for line in out.splitlines():
        if line.startswith('MARK '):
            cur = int(line.split()[1])
            res[cur] = {'logs': [], 'reads': [], 'status': ''}
        elif cur is None:
            continue
        elif line.startswith('LOG['):
            res[cur]['logs'].append(line[:300])
        elif line.startswith('read '):
            res[cur]['reads'].append(line.split('=')[1])
        elif line.startswith('frame='):
            res[cur]['status'] = line
    return res, p.returncode, out[-400:]


idx = list(enumerate(runnable))
chunks = [idx[i::8] for i in range(8)]
results = {}
with cf.ThreadPoolExecutor(8) as ex:
    futs = [ex.submit(chunk_run, i, ch) for i, ch in enumerate(chunks)]
    for f in futs:
        res, rc, tail = f.result()
        results.update(res)
        if rc:
            print('probe rc', rc, tail)

BAD = ('CB2_InitCopyrightScreen', 'CB2_InitTitleScreen', 'MainCB2_Intro', 'CB2_InitMainMenu', 'Crash', 'crash')
report = []
for k, c in idx:
    r = results.get(k)
    entry = {'map': c[0], 'kind': c[1], 'index': c[2], 'script': c[3]}
    if r is None:
        entry['verdict'] = 'NO_RESULT'
    else:
        cb2 = addr2name.get(int(r['reads'][0], 16) & ~1, r['reads'][0]) if r['reads'] else '?'
        entry['cb2'] = cb2
        entry['logs'] = r['logs'][:5]
        pc = r['status']
        bad = any(b in cb2 for b in BAD)
        entry['verdict'] = 'RESET_OR_CRASH' if bad else ('ASSERT_LOG' if r['logs'] else 'OK')
        entry['status'] = pc
    report.append(entry)
summary = {}
for e in report:
    summary[e['verdict']] = summary.get(e['verdict'], 0) + 1
(OUT / 'report.json').write_text(json.dumps({'rom': str(ROM), 'summary': summary, 'skipped_no_symbol': len(skipped),
                                             'cases': report, 'skipped': [s[:4] for s in skipped]}, ensure_ascii=False, indent=1))
print('cases', len(runnable), 'skipped(no symbol)', len(skipped), summary)
for e in report:
    if e['verdict'] != 'OK':
        print(e['verdict'], e['map'], e['kind'], e['index'], e['script'], e.get('cb2'), (e.get('logs') or [''])[0][:160])
