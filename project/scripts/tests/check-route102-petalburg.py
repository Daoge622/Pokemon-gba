from part4_compat import source as part4_source
#!/usr/bin/env python3
"""Static inspection only: no game, simulator, native test or GUI is executed."""
import json,re,struct,subprocess
from collections import deque
from pathlib import Path
r=Path(__file__).resolve().parents[2]
base='bb1093a7c72d3961d9a37d8e02ad2abc2c866682'
files=['data/maps/Route102/map.json','data/maps/Route102/scripts.inc','data/maps/PetalburgCity/map.json','data/maps/PetalburgCity/scripts.inc','include/constants/opponents.h','src/data/trainers.party']
before={f:subprocess.check_output(['git','show',base+':'+f],cwd=r,text=True) for f in files}
flags=(r/'include/constants/flags.h').read_text()
defs=re.findall(r'^#define\s+(FLAG_\w+)\s+(0x[0-9A-Fa-f]+)\b',flags,re.M)
for name,num in [('FLAG_RECEIVED_LITTLEROOT_RALTS_EGG',32),('FLAG_BOUGHT_OLDALE_IMPORT_ULTRA_BALL',33),('FLAG_RECEIVED_PETALBURG_WATER_STONE',34),('FLAG_RECEIVED_ROUTE102_FULL_HEAL',35)]:
 assert [(n,int(v,16)) for n,v in defs if int(v,16)==num]==[(name,num)],name
op=(r/'include/constants/opponents.h').read_text()
assert re.search(r'#define TRAINER_ROUTE102_NEW_WORKER\s+855\b',op)
assert re.search(r'#define MAX_TRAINERS_COUNT_EMERALD\s+864\b',op)
assert re.search(r'#define TRAINERS_COUNT_EMERALD\s+864\b',op)
for name,value in [('TRAINER_PART3_BREEDER',857),('TRAINER_PART3_PLUSLE_MINUN',858),('TRAINER_PART3_HIKER',859),('TRAINER_PART3_MAGMA_ROOKIE',860)]:
 assert re.search(r'#define '+name+r'\s+'+str(value)+r'\b',op),name
# Previously assigned trainer IDs and the reserved flag capacity remain unchanged.
oldids=dict(re.findall(r'^#define (TRAINER_\w+)\s+(\d+)\b',before['include/constants/opponents.h'],re.M))
newids=dict(re.findall(r'^#define (TRAINER_\w+)\s+(\d+)\b',op,re.M))
assert all(newids[k]==v for k,v in oldids.items())
assert list(newids.values()).count('855')==1
layouts=json.loads((r/'data/layouts/layouts.json').read_text())['layouts']
for name in ['Route102','PetalburgCity']:
 path=f'data/maps/{name}/map.json';old=json.loads(before[path]);new=json.loads(part4_source(path,(r/path).read_text()));obj=new['object_events'][-1]
 assert new['object_events'][:-1]==old['object_events']
 assert {k:v for k,v in new.items() if k!='object_events'}=={k:v for k,v in old.items() if k!='object_events'}
 pos=(obj['x'],obj['y']); occupied={(x['x'],x['y']) for x in old['object_events']}
 assert pos not in occupied
 assert pos not in {(x['x'],x['y']) for key in ['warp_events','coord_events','bg_events'] for x in old[key]}
 layout=next(x for x in layouts if x['name']==name+'_Layout');w=layout['width'];h=layout['height']
 b=(r/layout['blockdata_filepath']).read_bytes();cells=struct.unpack('<'+'H'*(len(b)//2),b)
 ground={(x,y) for y in range(h) for x in range(w) if ((cells[y*w+x]>>10)&3)==0 and cells[y*w+x]>>12==3}
 assert pos in ground and obj['elevation']==3
 ground-=occupied
 def neighbors(p):return [(p[0]+dx,p[1]+dy) for dx,dy in [(1,0),(-1,0),(0,1),(0,-1)]]
 adjacent=set(neighbors(pos))&ground;assert len(adjacent)>=2
 # On collision/elevation grid, removing the NPC tile does not separate its approaches.
 remaining=ground-{pos};seen={next(iter(adjacent))};todo=deque(seen)
 while todo:
  for n in neighbors(todo.popleft()):
   if n in remaining and n not in seen:seen.add(n);todo.append(n)
 assert adjacent<=seen,(name,'NPC blocks a passage')
 if name=='Route102':
  assert pos==(16,7) and obj['trainer_sight_or_berry_tree_id']=='2'
  # The added stationary object does not occupy any original trainer cardinal sight ray.
  for x in old['object_events']:
   if x['trainer_type']!='TRAINER_TYPE_NORMAL':continue
   for d in ['UP','DOWN','LEFT','RIGHT']:
    if d not in x['movement_type']:continue
    dx,dy={'UP':(0,-1),'DOWN':(0,1),'LEFT':(-1,0),'RIGHT':(1,0)}[d]
    assert pos not in [(x['x']+dx*i,x['y']+dy*i) for i in range(1,int(x['trainer_sight_or_berry_tree_id'])+1)]
 else:
  boy=next(x for x in old['object_events'] if x.get('local_id')=='LOCALID_PETALBURG_BOY')
  assert (boy['x'],boy['y'])==(8,22) and pos==(9,22)
  assert obj['graphics_id']=='OBJ_EVENT_GFX_SPECIES(JOLTEON)'
print('Flags, trainer IDs, original map events, walkable coordinates and passage connectivity: PASS')
config=json.loads((r/'tools/poryscript/font_config.json').read_text());font=config['fonts'][config['defaultFontId']];linecount=0
for name in ['Route102','PetalburgCity']:
 s=(r/f'data/maps/{name}/scripts.inc').read_text();newtext=s[s.index('Route102_EventScript_NewWorker::'):] if name=='Route102' else s[s.index('PetalburgCity_EventScript_TryGiveWaterStone::'):]
 assert not re.search(r'\b(ARCHE|ANTI)\b',newtext,re.I)
 labels=re.findall(r'^([A-Za-z0-9_]+)::?$',s,re.M);assert len(labels)==len(set(labels))
 for block in re.findall(r'(?:\s*\.string "[^"\n]*"\n)+',newtext):
  text=''.join(re.findall(r'\.string "([^"\n]*)"',block))
  for page in text.split(r'\p'):
   lines=page.rstrip('$').split(r'\n');assert len(lines)<=2,lines
   for line in lines:
    width=sum(font['widths'][c] for c in line);assert width<=208,(line,width);linecount+=1
 for item,flag,prefix in [('ITEM_FULL_HEAL','FLAG_RECEIVED_ROUTE102_FULL_HEAL','Route102_EventScript_NewWorker'),('ITEM_WATER_STONE','FLAG_RECEIVED_PETALBURG_WATER_STONE','PetalburgCity_EventScript_WaterStone')]:
  if (name=='Route102')!=(item=='ITEM_FULL_HEAL'):continue
  give=s.index(f'giveitem {item}, 1');fail=s.index(f'goto_if_eq VAR_RESULT, FALSE, {prefix}BagFull',give);mark=s.index(f'setflag {flag}',fail)
  assert give<fail<mark and s.count(f'setflag {flag}')==1
  assert s.index(f'goto_if_set {flag}')<give
  failure=s[s.index(prefix+'BagFull::'):].split('\n\n')[0];assert 'setflag' not in failure
pet=(r/'data/maps/PetalburgCity/scripts.inc').read_text()
original=before['data/maps/PetalburgCity/scripts.inc']
reflection=lambda s: re.search(r'PetalburgCity_Text_WaterReflection:\n.*?(?=\n\n)',s,re.S).group(0)
import subprocess
reference=json.loads((r/'scripts/tests/fixtures/chinese-reflection.json').read_text())
assert reflection(pet)==reference['reflection']
assert 'applymovement LOCALID_PETALBURG_BOY, Common_Movement_FaceOriginalDirection' in pet
cry=pet[pet.index('PetalburgCity_EventScript_Jolteon::'):].split('\n\n')[0]
assert 'playmoncry SPECIES_JOLTEON, CRY_MODE_NORMAL' in cry and 'waitmoncry' in cry and 'msgbox' not in cry and 'message' not in cry
route=(r/'data/maps/Route102/scripts.inc').read_text()
def bytecode(s):
 return re.sub(r'\s+', '', re.sub(r'(?m)^\s*\.string[^\n]*\n?', '', s))
assert bytecode(route).startswith(bytecode(before['data/maps/Route102/scripts.inc']))
assert 'trainerbattle_single TRAINER_ROUTE102_NEW_WORKER' in route and 'special PlayerFaceTrainerAfterBattle' in route
assert (r/'graphics/pokemon/jolteon/overworld.png').is_file()
party=(r/'src/data/trainers.party').read_text()
without_names=lambda s: re.sub(r'(?m)^Name: .*$', 'Name:', s)
# PART1 boss changes are checked separately; prior opening worker remains exact.
oldworker=subprocess.check_output(['git','show','pre-part1-implementation:src/data/trainers.party'],cwd=r,text=True).split('=== TRAINER_ROUTE102_NEW_WORKER ===')[1].split('===')[0]
assert party.split('=== TRAINER_ROUTE102_NEW_WORKER ===')[1].split('===')[0].strip()==oldworker.strip()
added=party[party.index('=== TRAINER_ROUTE102_NEW_WORKER ==='):].split('=== TRAINER_PART1_ROUTE104_TRAVELER ===')[0]
assert 'Name: 埃文' in added and 'Class: Youngster' in added
assert re.findall(r'^Level: (\d+)$',added,re.M)==['4','4']
print(f'Gift success/failure branches, unchanged reflection, cry-only interaction and {linecount} dialogue lines: PASS')