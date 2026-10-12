#!/usr/bin/env python3
"""PART3 west region native-script and map checks; terminal only, no ROM execution."""
from pathlib import Path
import json,re,struct,subprocess
from collections import deque,Counter
r=Path(__file__).resolve().parents[2]
read=lambda f:(r/f).read_text()
layouts={x['id']:x for x in json.loads(read('data/layouts/layouts.json'))['layouts']}
font=json.loads(read('tools/poryscript/font_config.json'))['fonts']['1_chinese_rse']['widths']
def grid(folder):
 v=json.loads(read(f'data/maps/{folder}/map.json'));l=layouts[v['layout']];w,h=l['width'],l['height'];cells=struct.unpack('<'+'H'*(w*h),(r/l['blockdata_filepath']).read_bytes());floor={(x,y) for y in range(h) for x in range(w) if (cells[y*w+x]>>10)&3==0 and cells[y*w+x]>>12 in (0,3)};return v,l,cells,floor
def flood(g,start):
 seen={start};q=deque(seen)
 while q:
  x,y=q.popleft()
  for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
   if p in g and p not in seen:seen.add(p);q.append(p)
 return seen
m=json.loads(read('docs/project/part3-west-manifest.json'))
for o in m['objects']:
 if o.get('local_id')=='LOCALID_PART3_DESERT_VISIBLE_ITEM':o['trainer_sight_or_berry_tree_id']='ITEM_BRIGHT_POWDER'
for folder in sorted(set(o['map'] for o in m['objects'])):
 v,l,c,floor=grid(folder);occupied={(o['x'],o['y']) for o in v['object_events']};g=floor-occupied
 for o in [z for z in m['objects'] if z['map']==folder]:
  p=(o['x'],o['y']);adj={(p[0]-1,p[1]),(p[0]+1,p[1]),(p[0],p[1]-1),(p[0],p[1]+1)}&g
  assert len(adj)>=1,(folder,o['local_id'],'inaccessible')
  assert adj<=flood(g,next(iter(adj))),(folder,o['local_id'],'blocks a path collectively')
 print(folder,len(v['object_events']),'all new objects accessible and local paths remain connected')
for label in m['texts']:
 for p in (r/'data/maps').glob('*/scripts.inc'):
  match=re.search(r'(?m)^'+re.escape(label)+r':\n\s*\.string "([^"\n]*)"',p.read_text())
  if match:
   for line in re.split(r'\\[npl]',match.group(1)):
    width=sum(42 if t=='{PLAYER}' else 78 if t.startswith('{') else font.get(t,6) for t in re.findall(r'\{[^}]*\}|.',line.replace('$','')))
    assert width<=208,(label,line,width)
   break
 else:raise AssertionError(('missing text',label))
print('all',len(m['texts']),'text labels defined; 208px width bound satisfied')

global_manifest=json.loads(read('docs/project/part3-global-manifest.json'))
base=global_manifest['baseline']
def old(f):return subprocess.check_output(['git','show',base+':'+f],cwd=r,text=True)
# Manifest allocations are real unused native slots; hidden slots keep the native 0x1F4 offset.
permanent=['DAYCARE_EXPLAINED','TENT_COMPLETED','TENT_REWARD','TENT_YOUNGSTER_LEFT','PICNIC_COOKIE','DESERT_VISIBLE_ITEM','ROUTE117_ETHER','ROUTE117_SOOTHE_BELL']
for suffix in permanent:
 name='FLAG_PART3_'+suffix;value=global_manifest['flags'][name]
 aliases=[n for n,z in re.findall(r'^#define (FLAG_\w+)\s+(0x[0-9A-Fa-f]+)',read('include/constants/flags.h'),re.M) if int(z,16)==value]
 previous=[n for n,z in re.findall(r'^#define (FLAG_\w+)\s+(0x[0-9A-Fa-f]+)',old('include/constants/flags.h'),re.M) if int(z,16)==value]
 assert aliases==[name] and len(previous)==1 and 'UNUSED' in previous[0],name
 assert suffix!='ROUTE117_SOOTHE_BELL' or value>=0x1F4
for folder in sorted(set(o['map'] for o in m['objects'])):
 v,l,c,floor=grid(folder);prior=json.loads(old(f'data/maps/{folder}/map.json'))
 assert v['object_events'][:len(prior['object_events'])]==prior['object_events'],folder
 for key in ['warp_events','coord_events','connections']:assert v.get(key)==prior.get(key),(folder,key)
 assert v['bg_events'][:len(prior['bg_events'])]==prior['bg_events']
 for a in [o for o in m['objects'] if o['map']==folder]:
  assert {k:z for k,z in a.items() if k!='map'} in v['object_events']
  assert sum((o['x'],o['y'])==(a['x'],a['y']) for o in v['object_events'])==1
  assert a['elevation']==c[a['y']*l['width']+a['x']]>>12
  for t in prior['object_events']:
   if t['trainer_type']=='TRAINER_TYPE_NONE':continue
   dirs=[d for d in ['UP','DOWN','LEFT','RIGHT'] if d in t['movement_type']] or ['UP','DOWN','LEFT','RIGHT']
   for d in dirs:
    dx,dy={'UP':(0,-1),'DOWN':(0,1),'LEFT':(-1,0),'RIGHT':(1,0)}[d]
    assert (a['x'],a['y']) not in [(t['x']+i*dx,t['y']+i*dy) for i in range(1,int(t['trainer_sight_or_berry_tree_id'])+1)],(folder,'native trainer ray')
 for x,y in floor:
  visible=lambda obs:sum(x-9<=o['x']<=x+10 and y-7<=o['y']<=y+9 for o in obs)
  now,was=visible(v['object_events']),visible(prior['object_events'])
  assert now<=15 or now==was,(folder,'camera object capacity',x,y,now,was)
print('West flag uniqueness and native hidden offsets, original objects/warps/coord events, original trainer rays and viewport capacity: PASS')

alltext='\n'.join(p.read_text() for p in (r/'data/maps').glob('*/scripts.inc'))
lines=[];labels={}
for line in alltext.splitlines():
 line=line.split('@')[0].strip()
 if re.match(r'^\w+::?$',line):labels[line.rstrip(':')]=len(lines)
 elif line and not line.startswith('.'):lines.append(line)
s=(r/'scripts/tests/check-part2.py').read_text();s=s[s.index('class VM:'):s.index('\ncases=[')]
s=s.replace("elif cmd=='msgbox':self.messages.append(args[0])", "elif cmd=='specialvar':self.vars[args[0]]=int('SPECIES_EGG' in self.species) if args[1]=='DoesPlayerPartyContainSpecies' else self.lead\n   elif cmd=='msgbox':self.messages.append(args[0])")
exec(s)
for label,pre,flag,item in [('VerdanturfTown_BattleTentLobby_Part3_TryPrize','FLAG_PART3_TENT_COMPLETED','FLAG_PART3_TENT_REWARD','ITEM_PP_UP'),('Route111_Part3_PicnicMother',None,'FLAG_PART3_PICNIC_COOKIE','ITEM_LAVA_COOKIE')]:
 v=VM()
 if pre:
  v.run(label);assert not v.gifts
  v.flags.add(pre)
 v.bag=False;v.run(label);assert flag not in v.flags and not v.gifts
 v.bag=True;v.run(label);assert flag in v.flags and v.gifts[item]==1
 v.run(label);assert v.gifts[item]==1
for eggs in [False,True]:
 v=VM();v.species={'SPECIES_EGG'} if eggs else set();v.run('Route117_Part3_DaycareInfo')
 assert 'FLAG_PART3_DAYCARE_EXPLAINED' in v.flags
 assert ('Route117_Part3_DaycareEggText' in v.messages)==eggs
 v.messages.clear();v.run('Route117_Part3_DaycareInfo');assert 'Route117_Part3_DaycareIntro' not in v.messages
for species in ['SPECIES_WHISMUR','SPECIES_LOUDRED','SPECIES_EXPLOUD','SPECIES_EGG','SPECIES_ZIGZAGOON']:
 v=VM();v.lead=species;v.run('VerdanturfTown_Part3_SoundElder')
 assert ('VerdanturfTown_Part3_SoundElderLoudText' in v.messages)==(species in ['SPECIES_WHISMUR','SPECIES_LOUDRED','SPECIES_EXPLOUD'])
v=VM();v.run('VerdanturfTown_Part3_TentYoungster');assert not v.removed and 'FLAG_PART3_TENT_YOUNGSTER_LEFT' not in v.flags
v.flags.add('FLAG_PART3_TENT_COMPLETED');v.run('VerdanturfTown_Part3_TentYoungster');assert v.removed and 'FLAG_PART3_TENT_YOUNGSTER_LEFT' in v.flags
for label,normal,blocked in [('Route112_Part3_CableWorker','Route112_Part3_CableWorkerClearText','Route112_Part3_CableWorkerBlockedText'),('Route112_Part3_CableTourist','Route112_Part3_CableTouristClearText','Route112_Part3_CableTouristBlockedText')]:
 v=VM();v.run(label);assert blocked in v.messages
 v.flags.add('FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY');v.messages.clear();v.run(label);assert normal in v.messages and blocked not in v.messages
from part7_compat import source as part7_source
s=part7_source('data/maps/RusturfTunnel/scripts.inc');tunnel_baseline=__import__('subprocess').check_output(['git','show',global_manifest['baseline']+':data/maps/RusturfTunnel/scripts.inc'],cwd=r,text=True)
strip=lambda z:re.sub(r'(?m)^\s*\.string[^\n]*\n?','',z)
assert strip(s)==strip(tunnel_baseline),'native tunnel progression changed'
print('West actual event commands: tent/picnic full-bag retry and duplication, daycare once/egg, first-slot cries, tent youngster and cable state, original tunnel code: PASS')

# Small call-only hooks preserve every native daycare/tent instruction and original text.
s=read('data/scripts/day_care.inc').replace('\tcall Route117_Part3_DaycareInfo\n','')
assert s==old('data/scripts/day_care.inc'),'native daycare management drift'
s=read('data/maps/VerdanturfTown_BattleTentBattleRoom/scripts.inc').replace('\tsetflag FLAG_PART3_TENT_COMPLETED\n','')
assert s==old('data/maps/VerdanturfTown_BattleTentBattleRoom/scripts.inc'),'native tent battle flow drift'
s=read('data/maps/VerdanturfTown_BattleTentLobby/scripts.inc').split('\nVerdanturfTown_BattleTentLobby_Part3_TryPrize::')[0].rstrip()+'\n'
s=s.replace('\tcall VerdanturfTown_BattleTentLobby_Part3_TryPrize\n','')
assert s.rstrip()==old('data/maps/VerdanturfTown_BattleTentLobby/scripts.inc').rstrip(),'native tent reception/prize flow drift'
for folder in ['Route111','Route112','Route117']:
 s=read(f'data/maps/{folder}/scripts.inc');previous=old(f'data/maps/{folder}/scripts.inc')
 assert s.startswith(previous),(folder,'native route instructions drift')
s=read('data/maps/VerdanturfTown_WandasHouse/scripts.inc');previous=old('data/maps/VerdanturfTown_WandasHouse/scripts.inc')
assert strip(s)==strip(previous),'native Wally family event branches drift'
print('Entire native daycare/tent, route 111/112/117 progression and Wally family branches preserved after only declared hooks/text: PASS')
