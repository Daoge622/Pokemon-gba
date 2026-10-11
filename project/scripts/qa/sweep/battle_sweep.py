#!/usr/bin/env python3
"""Battle every trainer and roster opponent once from the user's save (headless mGBA, authorized 2026-10-08).
A trainerbattle_no_intro bytecode is written to RAM and run; A is mashed for a few turns.
Checks: CPU jumps / undefined-instruction mode, crash screen, reset to title, debug-log asserts.
usage: battle_sweep.py ROM SAVE OUTDIR"""
import re, sys, struct, subprocess, json, concurrent.futures as cf
from pathlib import Path

R = Path.home() / 'projects/emerald-story'
ROM, SAVE, OUT = Path(sys.argv[1]), Path(sys.argv[2]), Path(sys.argv[3])
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
TEXT = sym['gText_WeHopeToSeeYouAgain']

opp = (R / 'include/constants/opponents.h').read_text()
ids = {m[1]: int(m[2]) for m in re.finditer(r'^#define (TRAINER_\w+)\s+(\d+)\s*$', opp, re.M)}
pids = {m[1]: int(m[2]) for m in re.finditer(r'^#define (PARTNER_\w+) (\d+)$', (R / 'include/constants/battle_partner.h').read_text(), re.M)}
trainers = []
for name in re.findall(r'^=== (TRAINER_\w+) ===', (R / 'src/data/trainers.party').read_text(), re.M):
    if name in ids and ids[name] != 0:
        trainers.append((name, ids[name]))
for name in re.findall(r'^=== (PARTNER_\w+) ===', (R / 'src/data/battle_partners.party').read_text(), re.M):
    if name in pids and pids[name] != 0:
        trainers.append((name, 864 + pids[name]))
used = set(re.findall(r'\b(TRAINER_\w+)\b', subprocess.run(['grep', '-rhow', r'TRAINER_[A-Z0-9_]*', 'data/maps', 'data/scripts', 'src'], cwd=R, capture_output=True, text=True).stdout))

LOAD = 'frames 4000\nframes 4 8\nframes 500\nframes 4 1\nframes 900\n'


def bytecode(tid):
    b = struct.pack('<BBBHIIIBHIIIIIB', 0x5c, 0x94, 0, tid, 0, TEXT, 0, 0, 0, 0, 0, 0, 0, 0, 0) + b'\x02'
    return ''.join(f'write {hex(BUF + i)} {v} 1\n' for i, v in enumerate(b)) + f'call ScriptContext_SetupScript {hex(BUF)}\n'


def case(k, tid):
    s = f'load boot.ss\nmark {k}\n' + bytecode(tid) + 'frames 600\n'
    for i in range(70):
        s += 'frames 4 1\nframes 50\n'
        if i in (10, 69):
            s += f'status\nread {hex(MAIN + 4)}\nread gBattleOutcome 1\n'
    return s


def run_chunk(ci, chunk):
    d = OUT / f'chunk{ci:02d}'
    d.mkdir(exist_ok=True)
    (d / 'commands.txt').write_text(LOAD + 'state boot.ss\n' + ''.join(case(k, t[1]) for k, t in chunk))
    p = subprocess.run([str(PROBE), '--allow-rom-execution', str(ROM), str(OUT / 'symbols.txt'), str(d / 'commands.txt'), str(SAVE)],
                       cwd=d, capture_output=True, text=True, timeout=10800)
    (d / 'result.log').write_text(p.stdout + p.stderr)
    res, cur = {}, None
    for line in (p.stdout + p.stderr).splitlines():
        if line.startswith('MARK '):
            cur = int(line.split()[1])
            res[cur] = {'logs': [], 'status': [], 'reads': []}
        elif cur is None:
            continue
        elif line.startswith('LOG['):
            res[cur]['logs'].append(line[:200])
        elif line.startswith('frame='):
            res[cur]['status'].append(line)
        elif line.startswith('read '):
            res[cur]['reads'].append(line.split('=')[1])
    return res, p.returncode


idx = list(enumerate(trainers))
chunks = [idx[i::8] for i in range(8)]
results = {}
with cf.ThreadPoolExecutor(8) as ex:
    for res, rc in ex.map(lambda a: run_chunk(*a), enumerate(chunks)):
        results.update(res)
BAD = ('CB2_InitCopyrightScreen', 'CB2_InitTitleScreen', 'MainCB2_Intro', 'CB2_InitMainMenu', 'Crash')
rep, summary = [], {}
for k, (name, tid) in idx:
    r = results.get(k)
    v = 'NO_RESULT'
    e = {'trainer': name, 'id': tid, 'referenced': name in used or name.startswith('PARTNER_')}
    if r:
        pcs = [re.search(r'pc=([0-9a-f]+)', s)[1] for s in r['status']]
        cpsr = [re.search(r'cpsr=([0-9a-f]+)', s)[1] for s in r['status']]
        cb2 = [addr2name.get(int(x, 16) & ~1, x) for x in r['reads'][0::2]]
        bad_pc = any(not (p.startswith('08') or p.startswith('09') or p.startswith('000001') or p.startswith('03') or p.startswith('02')) for p in pcs)
        und = any(c[-2:] in ('1b', '9b', '17', '97') for c in cpsr)
        crash = any(any(b in c for b in BAD) for c in cb2)
        jumped = any('Jumped' in l or 'invalid' in l.lower() for l in r['logs'])
        v = 'CRASH' if (bad_pc or und or crash or jumped) else ('LOG' if r['logs'] else 'OK')
        e.update({'cb2': cb2, 'status': r['status'], 'logs': r['logs'][:4], 'outcome': r['reads'][1::2]})
    e['verdict'] = v
    summary[v] = summary.get(v, 0) + 1
    rep.append(e)
(OUT / 'report.json').write_text(json.dumps({'summary': summary, 'cases': rep}, ensure_ascii=False, indent=1))
print('trainers', len(trainers), summary)
for e in rep:
    if e['verdict'] != 'OK':
        print(e['verdict'], e['trainer'], e['id'], 'referenced' if e['referenced'] else 'unused', e.get('cb2'), (e.get('logs') or [''])[0][:120], e.get('status', [''])[-1:])
