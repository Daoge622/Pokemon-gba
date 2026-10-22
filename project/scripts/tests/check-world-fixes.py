#!/usr/bin/env python3
"""Current-source map, save-compatibility and diagnostic gates. No ROM."""
import importlib.util
import json
from pathlib import Path
import re
import subprocess
import maptool as t

R = Path(t.ROOT)
spec = importlib.util.spec_from_file_location('world_audit', Path(__file__).with_name('audit-world-reachability.py'))
a = importlib.util.module_from_spec(spec)
spec.loader.exec_module(a)
w = a.World()
seen = w.flood()
report = w.audit(seen)
sea = {f'Route{i}' for i in range(124,135)} | {f'Underwater_Route{i}' for i in range(124,130)}
bad = [f for f in report['findings'] if f['map'] in sea and
       ('Part' in f['script'] or 'PART' in f['local_id'])]
assert not bad, bad
assert not report['unsafe_dive_landings'], report['unsafe_dive_landings']
for name in ('Underwater_Route124','Underwater_Route126','Underwater_Route127','Underwater_Route128','Underwater_Route129','Underwater_Route134'):
    assert any(s[0] == name for s in seen), ('underwater route not covered', name)
default = t.Map('Route131')
active = w.m('Route131')
for y in range(25,28):
    for x in range(45,50):
        assert active.raw(x,y) == default.raw(x,y), ('platform lost after layout switch',x,y)
assert active.elev(47,26)==3 and not active.coll(47,26)
assert any(s[:3] == ('Route131',46,26) and not s[4] for s in seen)
drifter = t.obj(w.m('Route132'),local_id='LOCALID_PART7_DRIFTER')
assert (drifter['x'],drifter['y'],drifter['elevation']) == (32,23,3)
assert any(s[:3] == ('Route132',31,23) and not s[4] for s in seen)
print('World PASS: actual Route131 layout/platform, ship viewpoint, current-safe trainer, underwater routes and sea quest interactions')

# Validate every JSON/layout structurally, including maps outside graph coverage.
maps = 0
for p in (R/'data/maps').glob('*/map.json'):
    j = json.loads(p.read_text(encoding='utf-8'))
    m = t.Map(p.parent.name)
    assert len(m.grid) == m.w*m.h, p
    local = [o['local_id'] for o in j.get('object_events',[]) if o.get('local_id')]
    assert len(local)==len(set(local)), ('duplicate local ID',p)
    for c in j.get('coord_events',[]):
        assert m.inb(c['x'],c['y']), ('coordinate trigger outside map',p,c)
    maps += 1
print(f'All {maps} map JSONs: layout sizes, local IDs, trigger bounds PASS')

trace = (R/'src/crash_trace.c').read_text(encoding='utf-8')
assert not re.search(r'\b(?:ReadFlash|ProgramFlashByte|ProgramFlashSector|EraseFlashSector|StartFlashTimer)\s*\(',trace)
assert 'gCrashTraceSnapshot = e;' in trace
assert re.search(r'^CRASH_TRACE\s*\?=\s*0$',(R/'Makefile').read_text(),re.M)
assert re.search(r'#define OW_UNION_DISABLE_CHECK\s+TRUE\b',(R/'include/config/overworld.h').read_text())
base = '4e15154194480966babb593cf5de2cc8fca7ce8e'
for f in ['include/global.h','include/pokemon.h','include/constants/flags.h','include/constants/vars.h','include/constants/species.h','include/constants/items.h','data/maps/map_groups.json','src/save.c','src/load_save.c','src/overworld.c']:
    old = subprocess.check_output(['git','show',base+':project/'+f],cwd=R)
    assert old == (R/f).read_bytes(), ('save ABI/IDs or ambient cry changed',f)
print('Save ABI/IDs/flags/vars/ambient cries unchanged; trace cannot access flash; wireless check remains disabled PASS')

out = R/'artifacts/audit/world-current.json'
out.parent.mkdir(parents=True,exist_ok=True)
out.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
