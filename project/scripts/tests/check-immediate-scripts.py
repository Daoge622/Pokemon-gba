#!/usr/bin/env python3
"""Immediate map-script audit. Source only; never executes a ROM.
Follow calls, conditional/unconditional branches and label fallthroughs.
Special/native implementations require source review in addition to this check.
"""
from pathlib import Path
import json, re, sys, subprocess
from collections import Counter
from urllib.request import urlopen
R = Path(__file__).resolve().parents[2]
WAIT = set("lock lockall msgbox message waitstate waitmovement delay applymovement waitmessage waitbuttonpress waitfanfare waitmoncry waitcry waitse fadescreen fadescreenspeed yesnobox multichoice multichoicedefault multichoicegrid trainerbattle trainerbattle_single trainerbattle_double trainerbattle_no_intro wildbattle dowildbattle waitfieldse waitdooranim waitcryend showmonpic braillemessage drawboxtext bufferboxname givemon giveegg givepokemon giveitem".split())
HOOKS = {"MAP_SCRIPT_ON_TRANSITION", "MAP_SCRIPT_ON_LOAD", "MAP_SCRIPT_ON_RESUME", "MAP_SCRIPT_ON_RETURN_TO_FIELD", "MAP_SCRIPT_ON_DIVE_WARP", "MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE"}

def parse(files):
    nodes, labels = {}, {}
    for name, text in files:
        pending, previous = [], None
        for line_no, raw in enumerate(text.splitlines(), 1):
            line = raw.split('@', 1)[0].strip()
            match = re.match(r'^([A-Za-z_][\w]*):{1,2}(.*)$', line)
            if match:
                pending.append(match[1]); line = match[2].strip()
            if not line:
                continue
            node = (name, line_no)
            for label in pending:
                labels.setdefault(label, []).append(node)
            pending = []
            op, _, args = line.partition(' ')
            nodes[node] = [op, args.strip(), None]
            if previous is not None:
                nodes[previous][2] = node
            previous = node
    return nodes, labels

def walk(nodes, labels, root):
    if root not in labels:
        raise AssertionError(f'unresolved script {root}')
    seen, todo, waits = set(), [(n, [root]) for n in labels[root]], []
    while todo:
        node, trail = todo.pop()
        if node in seen: continue
        seen.add(node)
        op, args, following = nodes[node]
        if op in WAIT or op.startswith('wait') or op.startswith('trainerbattle'):
            waits.append((node, op, ' -> '.join(trail))); continue
        if op in {'end', 'return', 'returnram', 'endram', 'step_end'} or op.startswith(('.string', '.byte', '.2byte', '.4byte', '.incbin')):
            # ON_WARP table entries are handled below, before the terminator.
            continue
        branch = op in {'goto', 'call', 'case', 'map_script_2', 'map_script_3'} or op.startswith(('goto_if_', 'call_if_'))
        if branch:
            target = re.findall(r'[A-Za-z_]\w*', args)[-1]
            if target not in labels:
                raise AssertionError(f'{node}: unresolved branch {target}')
            todo.extend((n, trail + [target]) for n in labels[target])
        if op != 'goto' and following is not None:
            todo.append((following, trail))
    return waits, seen

def self_test():
    n,l = parse([('fixture', 'Root::\n call Safe\n end\nSafe::\n goto_if_set FLAG_X, Bad\n return\nBad::\n lockall\n end\n')])
    bad,_ = walk(n,l,'Root'); assert bad and bad[0][1] == 'lockall'
    n,l = parse([('fixture','Root::\n goto End\nIgnored::\n msgbox Text, 0\nEnd::\n setflag FLAG_X\n end\n')])
    assert not walk(n,l,'Root')[0]
    n,l = parse([('fixture','Root::\n setvar VAR_X, 0\nNext::\n delay 1\n end\n')])
    assert walk(n,l,'Root')[0][0][1] == 'delay'
    print('Immediate checker fixtures: nested call/branch, dead branch, fallthrough PASS')

# Upstream facility hooks intentionally schedule asynchronous work. Never extend
# this list casually: every reachable wait must still match official 1.17.1.
LEGACY_HOOK_ROOTS = {
    'TrainerHill_Entrance_OnResume', 'TrainerTower_Lobby_OnResume',
    'BattleFrontier_BattleArenaBattleRoom_OnWarp',
    'BattleFrontier_BattlePyramidFloor_OnResume',
    'BattleFrontier_BattlePyramidTop_OnResume',
    'BattleFrontier_BattleTowerBattleRoom_OnWarp',
    'BattleFrontier_BattlePalaceBattleRoom_OnWarp',
    'BattleFrontier_BattleDomeBattleRoom_OnWarp',
    'VerdanturfTown_BattleTentBattleRoom_OnWarp',
}
UPSTREAM = 'bb1093a7c72d3961d9a37d8e02ad2abc2c866682'

def legacy_matches(nodes, labels, root, waits, seen):
    source_files = sorted({n[0] for n in seen})
    def original(f):
        p = subprocess.run(['git','show',UPSTREAM+':'+f],cwd=R,capture_output=True)
        if p.returncode == 0:
            return p.stdout.decode('utf-8')
        # Cloud import has no upstream Git history. Compare against the same
        # pinned official source, never accept a changed baseline silently.
        url = 'https://raw.githubusercontent.com/rh-hideout/pokeemerald-expansion/' + UPSTREAM + '/' + f
        return urlopen(url, timeout=30).read().decode('utf-8')
    originals = [(f, original(f)) for f in source_files]
    old_nodes,old_labels = parse(originals)
    old_waits,_ = walk(old_nodes,old_labels,root)
    def signature(graph, issues):
        return Counter((n[0],op,graph[n][1],trail) for n,op,trail in issues)
    return signature(nodes,waits) == signature(old_nodes,old_waits)

def main():
    self_test()
    files = [(p.relative_to(R).as_posix(),p.read_text(encoding='utf-8')) for ext in ('*.inc','*.s') for p in (R/'data').rglob(ext)]
    nodes, labels = parse(files)
    roots, zero = [], 0
    for p in (R/'data/maps').glob('*/map.json'):
        data = json.loads(p.read_text())
        for c in data.get('coord_events',[]):
            if c.get('type')=='trigger' and str(c.get('var','')).lower() in {'0','0x0','0x0000','trigger_run_immediately'}:
                zero += 1
                if str(c.get('script','0')).lower() not in {'0','0x0','null'}:
                    roots.append((p.parent.name+' coord',c['script']))
    for name,text in files:
        if not name.startswith('data/maps/'): continue
        for hook, root in re.findall(r'^\s*map_script\s+(\w+),\s*(\w+)', text, re.M):
            if hook in HOOKS: roots.append((name+' '+hook,root))
    failures, touched, legacy_count = [], set(), 0
    for origin,root in roots:
        waits,seen = walk(nodes,labels,root); touched.update(seen)
        if waits and ' coord' not in origin and root in LEGACY_HOOK_ROOTS:
            assert legacy_matches(nodes,labels,root,waits,seen), ('upstream hook waits changed',root)
            legacy_count += len(waits)
        else:
            failures.extend((origin,root,x) for x in waits)
    for origin,root,(node,op,trail) in failures:
        print(f'UNSAFE {origin}: {node[0]}:{node[1]} {op}; {trail}')
    assert not failures, f'{len(failures)} waits reachable from immediate entrypoints'
    print(f'Immediate scripts PASS: {zero} zero-trigger coords, {len(roots)} roots, {len(touched)} reachable instructions; all map hooks audited; {legacy_count} unchanged upstream facility wait sites verified against official 1.17.1')

if __name__ == '__main__': main()
