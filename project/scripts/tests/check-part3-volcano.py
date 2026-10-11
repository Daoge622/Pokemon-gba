#!/usr/bin/env python3
"""Terminal-only checks of real PART3 volcano scripts, map data and persistent state."""
from pathlib import Path
from collections import Counter,deque
import json,re,struct,subprocess
r=Path(__file__).resolve().parents[2];m=json.loads((r/'docs/project/part3-volcano-manifest.json').read_text());base=m['baseline']
def read(f):return __import__('part6_compat').source(f,(r/f).read_text())  # PART6 hunks reverted (see check-part6.py)
def old(f):return subprocess.check_output(['git','show',base+':'+f],cwd=r,text=True)
def flood(g,p):
 seen={p};q=deque(seen)
 while q:
  x,y=q.popleft()
  for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
   if p in g and p not in seen:seen.add(p);q.append(p)
 return seen
def block(s,label):
 a=s.index(label+'::')+len(label)+2;b=re.search(r'^\w+::',s[a:],re.M);return [z.strip() for z in s[a:a+b.start() if b else len(s)].splitlines() if z.strip() and not z.lstrip().startswith('@')]
layouts={x['id']:x for x in json.loads(read('data/layouts/layouts.json'))['layouts']}
grounds={}
for folder in m['maps']:
 f=f'data/maps/{folder}/map.json';v=json.loads(read(f));p=json.loads(old(f));layout=layouts[v['layout']];w,h=layout['width'],layout['height'];raw=(r/layout['blockdata_filepath']).read_bytes();cells=struct.unpack('<'+'H'*(w*h),raw)
 assert raw==subprocess.check_output(['git','show',base+':'+layout['blockdata_filepath']],cwd=r),(folder,'original terrain changed')
 g={(x,y) for y in range(h) for x in range(w) if (cells[y*w+x]>>10)&3==0 and cells[y*w+x]>>12 in (0,3)};grounds[folder]=g
 assert v.get('connections')==p.get('connections') and v['warp_events']==p['warp_events'],folder
 for key,mk in [('object_events','objects'),('bg_events','backgrounds'),('coord_events','coordinate_events')]:
  assert len(v[key])==len(p[key])+sum(z['map']==folder for z in m[mk]),(folder,key)
  for before,after in zip(p[key],v[key]):
   if before!=after:assert {'map':folder,'before':before,'after':after} in m['object_replacements'],(folder,key)
 occupied={(o['x'],o['y']) for o in v['object_events']}
 for o in [z for z in m['objects'] if z['map']==folder]:
  pos=o['x'],o['y'];assert pos in g and o['elevation']==cells[o['y']*w+o['x']]>>12
  assert sum((z['x'],z['y'])==pos for z in v['object_events'])==1
  adjacent={(pos[0]-1,pos[1]),(pos[0]+1,pos[1]),(pos[0],pos[1]-1),(pos[0],pos[1]+1)}&(g-occupied)
  if o['local_id']=='LOCALID_PART3_MAGMA_ROOKIE':
   assert pos==(10,10) and len(adjacent)==2 # The requested battle gate; stepping aside restores the same path.
   assert all(p in g for p in [(10,9),(9,9),(8,9),(7,9),(7,8),(7,7)])
  else:assert adjacent and adjacent<=flood(g-occupied,next(iter(adjacent))),(folder,pos,'blocks path')
 assert len({o.get('local_id',str(i+1)) for i,o in enumerate(v['object_events'])})==len(v['object_events'])
print('Volcano maps: native terrain/warps unchanged; 7 objects/4 duel substitutions/6 backgrounds/5 triggers verified')
# Capacity is checked in real map states, rather than counting mutually hidden trainers simultaneously.
v=json.loads(read('data/maps/MtChimney/map.json'));p=json.loads(old('data/maps/MtChimney/map.json'))
for flags in [{'FLAG_HIDE_MT_CHIMNEY_TRAINERS','FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY'},{'FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA','FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA','FLAG_HIDE_MT_CHIMNEY_TRAINERS'},{'FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA','FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA','FLAG_PART3_MAGMA_ROOKIE_LEFT'}]:
 for x,y in grounds['MtChimney']:
  counts=[sum(x-9<=o['x']<=x+10 and y-7<=o['y']<=y+9 and o['flag'] not in flags for o in z['object_events']) for z in [v,p]]
  assert counts[0]<=15 or counts[0]<=counts[1],(x,y,counts,'viewport capacity regression')
# Original scenes, awards and subsequent progression stay byte-identical at the command level.
for folder,labels in {'MeteorFalls_1F_1R':['MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene','MeteorFalls_1F_1R_EventScript_OpenStevensCave'],'MtChimney':['MtChimney_EventScript_Maxie'],'LavaridgeTown':['LavaridgeTown_EventScript_EggWoman','LavaridgeTown_EventScript_ReceivedEgg','LavaridgeTown_EventScript_NoRoomForEgg','LavaridgeTown_EventScript_RivalGiveGoGoggles'],'LavaridgeTown_Gym_1F':['LavaridgeTown_Gym_1F_EventScript_Flannery','LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated','LavaridgeTown_Gym_1F_EventScript_GiveOverheat','LavaridgeTown_Gym_1F_EventScript_GiveOverheat2']}.items():
 f=f'data/maps/{folder}/scripts.inc'
 for label in labels:assert block(read(f),label)==block(old(f),label),(folder,label)
assert 'giveegg SPECIES_WYNAUT' in read('data/maps/LavaridgeTown/scripts.inc')
assert any(o['trainer_sight_or_berry_tree_id']=='ITEM_MOON_STONE' and o['flag']=='FLAG_ITEM_METEOR_FALLS_1F_1R_MOON_STONE' for o in json.loads(read('data/maps/MeteorFalls_1F_1R/map.json'))['object_events'])
for folder in ['MeteorFalls_1F_2R','MeteorFalls_B1F_1R','MeteorFalls_B1F_2R']:
 for file in ['map.json','scripts.inc']:
  f=f'data/maps/{folder}/{file}'
  if (r/f).exists():assert read(f)==old(f),(folder,'late Bagon area changed')
print('Original meteorite/Cozmo/Archie/Maxie, Moon Stone, late Bagon areas, Wynaut egg, Go Goggles and fourth badge/TM flow: PASS')
# The change opens an existing walkable slope route; no teleport or future base terrain is added.
attrs=(r/'data/tilesets/secondary/lavaridge/metatile_attributes.bin').read_bytes();f='data/maps/JaggedPass/map.json';v=json.loads(read(f));l=layouts[v['layout']];w=l['width'];cells=struct.unpack('<'+'H'*(w*l['height']),(r/l['blockdata_filepath']).read_bytes());slopes=set()
for t in m['shortcut_tiles']:
 x,y=t['x'],t['y'];slopes.add((x,y));assert cells[y*w+x]==t['before'] and (struct.unpack_from('<H',attrs,2*((t['before']&0x3ff)-0x200))[0]&0xff)==0xd1
 assert t['after_metatile']==0x2af and (x,y) not in [(16,17),(16,18)]
assert len(slopes)==14;g=grounds['JaggedPass'];assert (13,5) not in flood(g-slopes,(14,39)) and (13,5) in flood(g,(14,39))
s=read('data/maps/JaggedPass/scripts.inc');assert 'call_if_set FLAG_PART3_JAGGED_SHORTCUT_OPEN, JaggedPass_Part3_RestoreShortcut' in s
for x,y in slopes:assert f'setmetatile {x}, {y}, 0x2AF, FALSE' in s
assert 'goto_if_ne VAR_0x8005, 7,' in s and any(o.get('script')=='JaggedPass_Part3_OpenShortcut' and o['x']==18 and o['y']==8 and o['player_facing_dir']=='BG_EVENT_PLAYER_FACING_SOUTH' for o in v['bg_events'])
print('14 existing bumpy slopes cleared from above; persisted on load; foot return reaches summit; native hideout unmodified: PASS')
# Execute the actual authored event instructions with a small state model.
source='\n'.join(read(f'data/maps/{folder}/scripts.inc') for folder in m['maps']);lines=[];labels={}
for row in source.splitlines():
 row=row.split('@')[0].strip()
 if re.fullmatch(r'\w+::?',row):labels[row.rstrip(':')]=len(lines)
 elif row and not row.startswith('.'):lines.append(row)
class VM:
 def __init__(self):self.flags=set();self.vars={'TRUE':1,'FALSE':0};self.gifts=Counter();self.bag=True;self.messages=[];self.defeated=set();self.battles=0;self.removed=set();self.moves=[];self.tiles={};self.species=set();self.heals=0;self.lead_type=0;self.player=(18,7)
 def val(self,a):return self.vars.get(a,int(a,0) if re.fullmatch(r'(?:0x[0-9a-fA-F]+|\d+)',a) else 0 if a.startswith('VAR_') else a)
 def run(self,label):
  pc=labels[label];stack=[]
  for _ in range(500):
   ins=lines[pc];pc+=1;cmd,*rest=ins.split(None,1);args=[z.strip() for z in rest[0].split(',')] if rest else []
   if cmd=='end':return
   if cmd=='return':
    if not stack:return
    pc=stack.pop();continue
   if cmd in ['setflag','clearflag']:(self.flags.add if cmd=='setflag' else self.flags.discard)(args[0])
   elif cmd=='giveitem':
    self.vars['VAR_RESULT']=int(self.bag)
    if self.bag:self.gifts[args[0]]+=int(args[1]) if len(args)>1 else 1
   elif cmd=='msgbox':self.messages.append(args[0])
   elif cmd in ['setvar','copyvar']:self.vars[args[0]]=self.val(args[1])
   elif cmd=='getplayerxy':self.vars[args[0]],self.vars[args[1]]=self.player
   elif cmd=='setmetatile':self.tiles[int(args[0]),int(args[1])]=self.val(args[2])
   elif cmd=='removeobject':self.removed.add(args[0])
   elif cmd=='applymovement':self.moves.append(tuple(args))
   elif cmd=='trainerbattle_no_intro':self.defeated.add(args[0]);self.battles+=1
   elif cmd=='checkspecies':self.vars['VAR_RESULT']=int(args[0] in self.species)
   elif cmd=='special' and args[0]=='HealPlayerParty':self.heals+=1
   elif cmd=='specialvar' and args[1]=='GetPart3LeadHotSpringType':self.vars[args[0]]=self.lead_type
   elif cmd.startswith(('goto','call')):
    ok=True
    if cmd.endswith('_if_set'):ok=args[0] in self.flags
    elif cmd.endswith('_if_unset'):ok=args[0] not in self.flags
    elif cmd.endswith('_if_eq'):ok=self.val(args[0])==self.val(args[1])
    elif cmd.endswith('_if_ne'):ok=self.val(args[0])!=self.val(args[1])
    elif cmd.endswith('_if_defeated'):ok=args[0] in self.defeated
    elif cmd not in ['goto','call']:raise AssertionError(('unhandled jump',ins))
    if ok:
     if cmd.startswith('call'):stack.append(pc)
     pc=labels[args[-1]]
  raise AssertionError(('nonterminating',label))
for gift in m['gifts']:
 v=VM();pre=gift['prerequisite']
 if pre:v.run(gift['script']);assert not v.gifts;v.flags.add(pre)
 v.bag=False;v.run(gift['script']);assert not v.gifts and gift['flag'] not in v.flags
 v.bag=True;v.run(gift['script']);assert v.gifts[gift['item']]==gift['quantity'] and gift['flag'] in v.flags
 v.run(gift['script']);assert v.gifts[gift['item']]==gift['quantity']
v=VM();v.run('MtChimney_Part3_RookieReturnTrigger');assert not v.removed
v.run('MtChimney_Part3_Rookie');assert v.battles==1 and ('LOCALID_PART3_MAGMA_ROOKIE','MtChimney_Part3_RookieStepAside') in v.moves
v.run('MtChimney_Part3_Rookie');assert v.battles==1 and v.messages[-1]=='MtChimney_Part3_RookieFollowup'
v.flags.add('FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY');v.run('MtChimney_Part3_RookieReturnTrigger');assert 'FLAG_PART3_MAGMA_ROOKIE_LEFT' in v.flags and 'LOCALID_PART3_MAGMA_ROOKIE' in v.removed
before=len(v.moves);v.run('MtChimney_Part3_RookieReturnTrigger');assert len(v.moves)==before
v=VM();v.player=(18,9);v.run('JaggedPass_Part3_OpenShortcut');assert not v.tiles and 'FLAG_PART3_JAGGED_SHORTCUT_OPEN' not in v.flags
v.player=(18,7);v.run('JaggedPass_Part3_OpenShortcut');assert len(v.tiles)==14 and 'FLAG_PART3_JAGGED_SHORTCUT_OPEN' in v.flags
v.tiles.clear();v.run('JaggedPass_Part3_RestoreShortcut');assert len(v.tiles)==14
for kind,suffix in [(0,'HealedText'),(1,'FireText'),(2,'IceText')]:
 v=VM();v.lead_type=kind;v.run('LavaridgeTown_Part3_HotSpring');v.run('LavaridgeTown_Part3_HotSpring');assert v.heals==2 and v.messages[-1]=='LavaridgeTown_Part3_HotSpring'+suffix
v=VM();v.run('LavaridgeTown_Part3_IceTrainer');assert not v.removed;v.flags.add('FLAG_BADGE04_GET');v.run('LavaridgeTown_Part3_IceTrainer');assert v.removed=={'LOCALID_PART3_ICE_TRAINER','LOCALID_PART3_SNORUNT'} and 'FLAG_PART3_SNORUNT_TRAINER_LEFT' in v.flags
for species,post in [('SPECIES_VULPIX','VulpixText'),('SPECIES_NINETALES','VulpixText'),('SPECIES_TORKOAL','TorkoalText')]:
 v=VM();v.species.add(species);v.run('LavaridgeTown_Part3_FireFan');assert v.messages[-1]=='LavaridgeTown_Part3_FireFan'+post
v=VM();v.run('LavaridgeTown_Gym_Part3_Rehearsal');v.run('LavaridgeTown_Gym_Part3_Rehearsal');assert len(v.messages)==1 and 'FLAG_PART3_FLANNERY_REHEARSAL_HEARD' in v.flags
v=VM();v.flags.add('FLAG_BADGE04_GET');v.run('LavaridgeTown_Gym_Part3_Rehearsal');assert not v.messages
print('Actual scripts: full-bag retry/once-only gifts, rookie battle/retreat, shortcut persistence, repeat healing, party flavor, snow departure, rehearsal guards: PASS')
for folder,species in [('MtChimney','MIGHTYENA'),('MtChimney','NUMEL'),('MtChimney','CARVANHA'),('MtChimney','PELIPPER'),('LavaridgeTown','SNORUNT')]:
 label='MtChimney_Part3_'+species if folder=='MtChimney' else 'LavaridgeTown_Part3_Snorunt';b=block(read(f'data/maps/{folder}/scripts.inc'),label);assert f'playmoncry SPECIES_{species}, CRY_MODE_NORMAL' in b and 'waitmoncry' in b and not any('msgbox' in z or 'setwildbattle' in z for z in b)
shop=read('data/maps/LavaridgeTown_Mart/scripts.inc');assert '.2byte ITEM_LAVA_COOKIE' in shop and '.price = (I_PRICE >= GEN_7) ? 350 : 200' in read('src/data/items.h')
print('Five cry-only existing species sprites; standard town Cookie shop price unchanged: PASS')
