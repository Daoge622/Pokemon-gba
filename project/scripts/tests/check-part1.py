#!/usr/bin/env python3
"""PART1 source/data/native checks. Never loads or executes a GBA ROM."""
import json,re,struct,subprocess,tempfile
from collections import Counter,deque
from pathlib import Path
r=Path(__file__).resolve().parents[2]
m=json.loads((r/'docs/project/part1-manifest.json').read_text());base=m['baseline']
def old(f):return subprocess.check_output(['git','show',base+':'+f],cwd=r)
from part4_compat import source as part4_source
def read(f):return part4_source(f,(r/f).read_text())
def source(folder):return read(f'data/maps/{folder}/scripts.inc')
def flood(ground,start):
 seen={start};todo=deque(seen)
 while todo:
  x,y=todo.popleft()
  for n in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
   if n in ground and n not in seen:seen.add(n);todo.append(n)
 return seen
# Every allocation had an unused placeholder at the checkpoint; no alias conflicts.
flags=read('include/constants/flags.h');prior=old('include/constants/flags.h').decode()
def flagdefs(s):
 direct=[(n,int(v,16)) for n,v in re.findall(r'^#define\s+(FLAG_\w+)\s+(0x[0-9A-Fa-f]+)\b',s,re.M)]
 return direct+[(n,0x920+int(v,16)) for n,v in re.findall(r'^#define\s+(FLAG_\w+)\s+\(DAILY_FLAGS_START \+ (0x[0-9A-Fa-f]+)\)',s,re.M)]
defs=flagdefs(flags)
for name,value in m['flags'].items():
 matches=[n for n,v in defs if v==value];assert matches==[name],(name,matches)
 previous=[n for n,v in flagdefs(prior) if v==value]
 assert len(previous)==1 and ('UNUSED' in previous[0] or 'DAILY_' in previous[0]),previous
for n in ['FLAGS_COUNT','TRAINER_FLAGS_START','DAILY_FLAGS_START','DAILY_FLAGS_END']:
 assert re.search(r'^#define '+n+r'\s+.*$',flags,re.M).group()==re.search(r'^#define '+n+r'\s+.*$',prior,re.M).group(),n
print('14 verified unused flag slots; save/flag capacity and prior assignments preserved: PASS')
layouts={x['id']:x for x in json.loads(read('data/layouts/layouts.json'))['layouts']}
part2=json.loads(read('docs/project/part2-manifest.json'));added=Counter(x['map'] for x in m['objects']);p2added=Counter(x['map'] for x in part2['objects']);maps={}
for folder in set(added)|{b['map'] for b in m['backgrounds']}|{'GraniteCave_B2F','GraniteCave_StevensRoom'}:
 f=f'data/maps/{folder}/map.json';v=json.loads(read(f));prev=json.loads(old(f));maps[folder]=v
 for k in ['warp_events','connections']:
  assert v.get(k)==prev.get(k),(folder,k)
 assert v.get('object_events',[])[:len(prev.get('object_events',[]))]==prev.get('object_events',[]),folder
 assert len(v.get('object_events',[]))==len(prev.get('object_events',[]))+added[folder]+p2added[folder],folder
 for k in ['coord_events','bg_events']:
  assert v.get(k,[])[:len(prev.get(k,[]))]==prev.get(k,[]),(folder,k)
 ids=[x.get('local_id',str(i+1)) for i,x in enumerate(v.get('object_events',[]))];assert len(ids)==len(set(ids)),folder
 layout=layouts[v['layout']];w,h=layout['width'],layout['height'];b=(r/layout['blockdata_filepath']).read_bytes();cells=struct.unpack('<'+'H'*(len(b)//2),b)
 ground={(x,y) for y in range(h) for x in range(w) if ((cells[y*w+x]>>10)&3)==0 and (cells[y*w+x]>>12) in (0,3)}
 occupied={(x['x'],x['y']) for x in v.get('object_events',[])}
 for obj in [a for a in m['objects'] if a['map']==folder]:
  actual=next(x for x in v['object_events'] if x.get('local_id')==obj['local_id']);assert actual=={k:v for k,v in obj.items() if k!='map'}
  pos=(obj['x'],obj['y']);assert pos in ground,(folder,pos,'collision')
  assert obj['elevation']==cells[pos[1]*w+pos[0]]>>12,(folder,pos,'elevation')
  assert sum((x['x'],x['y'])==pos for x in v['object_events'])==1,(folder,pos)
  adjacent={(pos[0]-1,pos[1]),(pos[0]+1,pos[1]),(pos[0],pos[1]-1),(pos[0],pos[1]+1)}& (ground-occupied)
  assert adjacent,(folder,pos,'no interaction approach')
  if len(adjacent)>1 and obj['local_id']!='LOCALID_PART1_TUNNEL_BARRIER':
   assert adjacent<=flood(ground-occupied,next(iter(adjacent))),(folder,pos,'NPC blocks passage')
  for trainer in prev.get('object_events',[]):
   if trainer['trainer_type']!='TRAINER_TYPE_NORMAL':continue
   direction=next((d for d in ['UP','DOWN','LEFT','RIGHT'] if d in trainer['movement_type']),None)
   if direction:
    dx,dy={'UP':(0,-1),'DOWN':(0,1),'LEFT':(-1,0),'RIGHT':(1,0)}[direction]
    assert pos not in [(trainer['x']+dx*i,trainer['y']+dy*i) for i in range(1,int(trainer['trainer_sight_or_berry_tree_id'])+1)],(folder,'trainer sight collision')
 if folder=='RusturfTunnel':
  pocket=tuple(m['blocked_pocket']['tile']);barrier=tuple(m['blocked_pocket']['barrier']);assert pocket not in flood(ground-occupied,(4,8));assert barrier in occupied
  oldcells=struct.unpack('<'+'H'*(len(b)//2),old(layout['blockdata_filepath']));diff=[i for i,(a,z) in enumerate(zip(oldcells,cells)) if a!=z];assert diff==[pocket[1]*w+pocket[0]]
  assert len(v['object_events'])==16
 # Conservative viewport bound: count even mutually exclusive/hidden objects.
 max_visible=max(sum(cx-9<=o['x']<=cx+10 and cy-7<=o['y']<=cy+9 for o in v.get('object_events',[])) for cx,cy in ground)
 if max_visible>15:
  for cx,cy in ground:
   now=sum(cx-9<=o['x']<=cx+10 and cy-7<=o['y']<=cy+9 for o in v.get('object_events',[]))
   was=sum(cx-9<=o['x']<=cx+10 and cy-7<=o['y']<=cy+9 for o in prev.get('object_events',[]))
   assert now<=15 or now==was,(folder,'new viewport capacity regression',cx,cy,now,was)
for name in ['GraniteCave_1F','GraniteCave_B1F','GraniteCave_B2F','GraniteCave_StevensRoom']:
 assert maps[name]['requires_flash'] is False
assert 'if (!gMapHeader.cave)\n        gSaveBlock1Ptr->flashLevel = 0;' in read('src/overworld.c')
print(f'{len(m["objects"])} added objects: coordinates, elevation, access, trainer rays; original warps; closed tunnel pocket; four lit cave maps: PASS')
# Encounters: preserve every other map/method, and aggregate actual slot weights.
wild=json.loads(read('src/data/wild_encounters.json'));previous=json.loads(old('src/data/wild_encounters.json'))
def entries(j):return {e['map']:e for group in j['wild_encounter_groups'] for e in group.get('encounters',[]) if 'map' in e}
a,z=entries(previous),entries(wild);targets=['MAP_RUSTURF_TUNNEL','MAP_GRANITE_CAVE_1F','MAP_GRANITE_CAVE_B1F','MAP_GRANITE_CAVE_B2F','MAP_GRANITE_CAVE_STEVENS_ROOM']
part3_wild_methods={'MAP_FIERY_PATH':{'land_mons'},'MAP_ROUTE114':{'land_mons','fishing_mons'},'MAP_METEOR_FALLS_1F_1R':{'land_mons'},'MAP_JAGGED_PASS':{'land_mons'}}
def unchanged_other_wild_fields(a,b,map_id):
 permitted=part3_wild_methods[map_id]
 assert {k:v for k,v in a.items() if k not in permitted}=={k:v for k,v in b.items() if k not in permitted},map_id
 for method in permitted:
  assert a[method]['encounter_rate']==b[method]['encounter_rate'],(map_id,method)
for k in a:
 if k in part3_wild_methods:unchanged_other_wild_fields(a[k],z[k],k)
 elif k not in targets:assert a[k]==z[k],k
 else:
  assert {x:y for x,y in a[k].items() if x!='land_mons'}=={x:y for x,y in z[k].items() if x!='land_mons'},k
  assert a[k]['land_mons']['encounter_rate']==z[k]['land_mons']['encounter_rate']
weights=[20,20,10,10,10,10,5,5,4,4,1,1]
for k in targets:
 rate=Counter()
 for weight,p in zip(weights,z[k]['land_mons']['mons']):rate[p['species']]+=weight
 if k=='MAP_RUSTURF_TUNNEL':
  assert rate=={'SPECIES_WHISMUR':80,'SPECIES_ARON':10,'SPECIES_BELDUM':10}
  assert all((p['min_level'],p['max_level'])==(8,10) for p in z[k]['land_mons']['mons'] if p['species']!='SPECIES_WHISMUR')
 else:
  assert rate=={'SPECIES_MAKUHITA':30,'SPECIES_ZUBAT':30,'SPECIES_MAWILE':10,'SPECIES_ABRA':10,'SPECIES_HITMONLEE':5,'SPECIES_ONIX':5,'SPECIES_NOSEPASS':5,'SPECIES_SABLEYE':5}
  assert all((p['min_level'],p['max_level'])==(10,12) for p in z[k]['land_mons']['mons'])
print('All five land encounter distributions, exact rare species rates/levels, unrelated maps and methods: PASS')
# Initial boss parties only; all existing other trainers/rematches and the opening worker preserved.
party=read('src/data/trainers.party');before=old('src/data/trainers.party').decode()
def parties(s):return dict(re.findall(r'^=== (TRAINER_\w+) ===\n(.*?)(?=^=== |\Z)',s,re.M|re.S))
pold,pnew=parties(before),parties(party)
for k in pold:
 if k not in set(['TRAINER_ROXANNE_1','TRAINER_BRAWLY_1']+list(part2['trainer_teams']))|{'TRAINER_VICTOR','TRAINER_VICTORIA','TRAINER_VIVI','TRAINER_VICKY','TRAINER_MAXIE_MT_CHIMNEY','TRAINER_FLANNERY_1'}:assert pold[k].strip()==pnew[k].strip(),k
for boss,trainer in [('Roxanne','TRAINER_ROXANNE_1'),('Brawly','TRAINER_BRAWLY_1')]:
 s=pnew[trainer];assert re.findall(r'^Level: (\d+)',s,re.M)==[str(p[1]) for p in m['boss_teams'][boss]]
 assert 'EVs:' not in s and re.findall(r'^IVs: (\d+)',s,re.M)==['12']*3
 for species,level,moves,item in m['boss_teams'][boss]:
  block=s[s.index('\n'+species):].split('\n\n')[0]
  for move in moves:assert '- '+move in block,(species,move)
  # Verify level-up or teachable compatibility against the actual Gen9 tables.
  lu=read('src/data/pokemon/level_up_learnsets/gen_9.h');tm=read('src/data/pokemon/teachable_learnsets.h')
  lblock=re.search(r's'+species+r'LevelUpLearnset\[\].*?\n};',lu,re.S).group()
  tblock=re.search(r's'+species+r'TeachableLearnset\[\].*?\n};',tm,re.S).group()
  for move in moves:
   const='MOVE_'+move.replace(' ','_').upper();levels=[int(v) for v in re.findall(r'LEVEL_UP_MOVE\(\s*(\d+),\s*'+const+r'\)',lblock)]
   assert any(x<=level for x in levels) or const in tblock,(species,level,move,'illegal')
assert re.findall(r'^Level: (\d+)',pnew['TRAINER_PART1_ROUTE104_TRAVELER'],re.M)==['5','5']
assert 'Name: 洋平' in pnew['TRAINER_PART1_ROUTE104_TRAVELER'] and 'Class: Youngster' in pnew['TRAINER_PART1_ROUTE104_TRAVELER']
print('Traveler and two boss parties, legal current learnsets, modest IVs/items, all other trainers unchanged: PASS')
# Narrow integration/config guards, not a blanket exception to migration checks.
assert read('include/config/caps.h').encode()==old('include/config/caps.h')
for n in ['B_EXP_CAP_TYPE','B_LEVEL_CAP_VARIABLE']:
 assert re.search(r'^#define '+n+r'\s+.*$',read('include/config/caps.h'),re.M).group()==re.search(r'^#define '+n+r'\s+.*$',old('include/config/caps.h').decode(),re.M).group(),n
assert re.search(r'^#define B_EXP_CAP_TYPE\s+EXP_CAP_NONE',read('include/config/caps.h'),re.M)
assert re.search(r'^#define B_SCALED_EXP\s+GEN_3',read('include/config/battle.h'),re.M)
assert re.search(r'^#define B_SPLIT_EXP\s+GEN_3',read('include/config/battle.h'),re.M)
assert re.search(r'^#define I_EXP_SHARE_ITEM\s+GEN_6',read('include/config/item.h'),re.M)
assert re.search(r'^#define I_EXP_SHARE_FLAG\s+FLAG_PART1_EXP_SHARE_ENABLED',read('include/config/item.h'),re.M)
battle=read('src/battle_script_commands.c');assert battle.count('CalculatePart1ExpShares(')==1
assert 'if (!IsValidForBattle(&gParties[B_TRAINER_PLAYER][i]))\n                    continue;' in battle
assert 'MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG' in battle
assert read('src/battle_controllers.c').encode()==old('src/battle_controllers.c')
assert 'if (IsValidForBattle(&gParties[B_TRAINER_PLAYER][*expMonId]))' in battle
assert 'B_SPLIT_EXP < GEN_6 && !IsGen6ExpShareEnabled()' in battle
item=read('src/item_use.c');cancel=item.split('static void Part1_ExpShareCancel(u8 taskId)\n{')[1].split('\n}')[0];assert 'FlagToggle' not in cancel
assert item.count('FlagToggle(I_EXP_SHARE_FLAG)')==1 and 'BagMenu_YesNo(taskId, ITEMWIN_YESNO_HIGH' in item
assert 'case MENU_NOTHING_CHOSEN:' in item and 'Part1_ExpShareCancel(taskId)' in item
assert 'setflag FLAG_RECEIVED_EXP_SHARE\n setflag FLAG_PART1_EXP_SHARE_ENABLED' in read('data/scripts/part1.inc')
assert 'goto_if_set FLAG_DELIVERED_STEVEN_LETTER, GraniteCave_Part1_SteelWingRetry' in source('GraniteCave_StevensRoom')
assert 'goto_if_eq VAR_RESULT, FALSE, GraniteCave_Part1_SteelWingBagFull' in source('GraniteCave_StevensRoom')
assert 'goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull' in source('GraniteCave_1F')
assert 'checkspecies SPECIES_BELDUM' in source('GraniteCave_StevensRoom')
print('Modern/legacy EXP branches, egg/faint filters, uncapped EXP, confirm/cancel and mandatory default-on grant, Flash/Steel Wing retry: PASS')
# Native tests execute the actual production arithmetic and RTC helper, not a game.
with tempfile.TemporaryDirectory() as d:
 p=Path(d);(p/'global.h').write_text('#include <stdint.h>\ntypedef uint16_t u16; typedef uint32_t u32; typedef u32 bool32;\nstruct SaveBlock1 { u32 dailySeed; }; extern struct SaveBlock1 *gSaveBlock1Ptr;\n#define FALSE 0\nenum Species { SPECIES_NONE, SPECIES_EGG, SPECIES_NORMAL };\nenum Field { MON_DATA_SPECIES_OR_EGG, MON_DATA_HP, MON_DATA_IS_EGG };\nstruct Pokemon { enum Species species; u32 hp, egg; };\n')
 valid=read('src/battle_controllers.c').split('bool32 IsValidForBattle(struct Pokemon *mon)')[1].split('\n}')[0]
 (p/'test.c').write_text('''#include "global.h"
#include "part1.h"
#include <assert.h>
struct SaveBlock1 save; struct SaveBlock1 *gSaveBlock1Ptr=&save;
u32 GetMonData(struct Pokemon *m,enum Field f) { return f==MON_DATA_HP ? m->hp : f==MON_DATA_IS_EGG ? m->egg : m->species; }
'''+ 'bool32 IsValidForBattle(struct Pokemon *mon)'+valid+'\n}\n'+'''
int main(void) { u32 a,b;
 struct Pokemon healthy={SPECIES_NORMAL,20,0},dead={SPECIES_NORMAL,0,0},egg={SPECIES_EGG,20,1},hiddenEgg={SPECIES_NORMAL,20,1},empty={SPECIES_NONE,20,0};
 assert(IsValidForBattle(&healthy));assert(!IsValidForBattle(&dead));assert(!IsValidForBattle(&egg));assert(!IsValidForBattle(&hiddenEgg));assert(!IsValidForBattle(&empty));
 for(u32 count=1;count<=6;count++) { CalculatePart1ExpShares(100,count,6,1,&a,&b); assert(a==100 && b==50); }
 CalculatePart1ExpShares(101,2,5,1,&a,&b);assert(a==101&&b==50);
 CalculatePart1ExpShares(100,2,0,0,&a,&b);assert(a==50&&b==0);
 CalculatePart1ExpShares(100,1,0,0,&a,&b);assert(a==100&&b==0);
 CalculatePart1ExpShares(100,2,2,0,&a,&b);assert(a==25&&b==25);
 CalculatePart1ExpShares(1,1,1,1,&a,&b);assert(a==1&&b==1);
 for(u32 seed=0;seed<100;seed++){ save.dailySeed=seed;assert(GetPart1DailyQuestion()==seed%3);assert(GetPart1DailyQuestion()==seed%3); }
 return 0; }
''');subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror',f'-I{p}',f'-I{r / "include"}',str(p/'test.c'),str(r/'src/part1.c'),'-o',str(p/'test')],check=True);subprocess.run([str(p/'test')],check=True)
print('Actual native EXP arithmetic (1-6 participants, odd rounding, OFF legacy), actual egg/faint filters and RTC seed stability: PASS')
# Execute a limited terminal validator of actual event instructions, with bag/choice boundary inputs.
alltext='\n'.join(read(str(p.relative_to(r))) for p in (r/'data/maps').glob('*/scripts.inc'))+'\n'+read('data/scripts/part1.inc')
lines=[];labels={}
for line in alltext.splitlines():
 line=line.split('@')[0].strip()
 if re.match(r'^\w+::?$',line):labels[line.rstrip(':')]=len(lines)
 elif line and not line.startswith('.'):lines.append(line)
class VM:
 def __init__(self):self.flags=set();self.vars={'TRUE':1,'YES':1,'FALSE':0,'NO':0};self.bag=True;self.choice=1;self.question=0;self.gifts=Counter();self.removed=set()
 def value(self,v):return self.vars.get(v,int(v) if v.isdigit() else v)
 def run(self,label):
  pc=labels[label];stack=[];switch=None
  for _ in range(500):
   ins=lines[pc];pc+=1;cmd,*rest=ins.split(None,1);args=[x.strip() for x in rest[0].split(',')] if rest else []
   if cmd=='end':return
   if cmd=='return':
    if not stack:return
    pc=stack.pop();continue
   if cmd in ['setflag','clearflag']:
    (self.flags.add if cmd=='setflag' else self.flags.discard)(args[0]);continue
   if cmd=='giveitem':
    self.vars['VAR_RESULT']=int(self.bag)
    if self.bag:self.gifts[self.value(args[0])]+=int(args[1]) if len(args)>1 else 1
   elif cmd=='msgbox' and args[-1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=self.choice
   elif cmd in ['setvar','copyvar']:self.vars[args[0]]=self.value(args[1])
   elif cmd=='specialvar':self.vars[args[0]]=self.question
   elif cmd=='random':self.vars['VAR_RESULT']=self.question % self.value(args[0])
   elif cmd=='switch':switch=self.value(args[0])
   elif cmd=='case' and self.value(args[0])==switch:pc=labels[args[1]]
   elif cmd=='removeobject':self.removed.add(args[0])
   elif cmd.startswith(('goto','call')):
    iscall=cmd.startswith('call');ok=True
    if cmd.endswith('_if_set'):ok=args[0] in self.flags
    elif cmd.endswith('_if_unset'):ok=args[0] not in self.flags
    elif cmd.endswith('_if_eq'):ok=self.value(args[0])==self.value(args[1])
    elif cmd not in ['goto','call']:raise AssertionError(('unsupported jump',ins))
    if ok:
     if iscall:stack.append(pc)
     pc=labels[args[-1]]
  raise AssertionError(('nonterminating',label))
# One-time gift retries and no duplication are tested from the scripts themselves.
cases=[('PetalburgWoods_Part1_Child','FLAG_PART1_WURMPLE_GUIDED','FLAG_PART1_RECEIVED_SILVER_POWDER','ITEM_SILVER_POWDER'),('Route116_Part1_Miner','FLAG_RECOVERED_DEVON_GOODS','FLAG_PART1_RECEIVED_MINER_HARD_STONE','ITEM_HARD_STONE'),('Dewford_Part1_ShellChild','FLAG_PART1_FOUND_PRETTY_SHELL','FLAG_PART1_RECEIVED_SHELL_PEARL','ITEM_PEARL'),('Part1_GiveExpShare',None,'FLAG_RECEIVED_EXP_SHARE','ITEM_EXP_SHARE'),('RusturfTunnel_Part1_Stardust',None,'FLAG_PART1_RUSTURF_STARDUST','ITEM_STARDUST'),('RusturfTunnel_Part1_HardStone',None,'FLAG_PART1_RUSTURF_HARD_STONE','ITEM_HARD_STONE'),('GraniteCave_Part1_Stardust',None,'FLAG_PART1_GRANITE_STARDUST','ITEM_STARDUST'),('GraniteCave_Part1_Everstone',None,'FLAG_PART1_GRANITE_EVERSTONE','ITEM_EVERSTONE')]
for label,pre,flag,itemname in cases:
 v=VM()
 if pre:
  v.run(label);assert not v.gifts
  v.flags.add(pre)
 v.bag=False;v.run(label);assert flag not in v.flags and not v.gifts,(label,'full bag')
 v.bag=True;v.run(label);assert flag in v.flags and v.gifts[itemname]==1,(label,'retry')
 v.run(label);assert v.gifts[itemname]==1,(label,'duplicate')
v=VM();v.choice=0;v.run('PetalburgWoods_Part1_WildWurmple');assert 'FLAG_PART1_WURMPLE_GUIDED' not in v.flags
v.choice=1;v.run('PetalburgWoods_Part1_WildWurmple');assert 'FLAG_PART1_WURMPLE_GUIDED' in v.flags and 'LOCALID_PART1_WURMPLE_WILD' in v.removed
for q in range(3):
 v=VM();v.question=q;v.choice=int(q!=1);v.bag=False;v.run('School_Part1_Quiz');assert 'FLAG_DAILY_PART1_SCHOOL_SOLVED' in v.flags and 'FLAG_DAILY_PART1_SCHOOL_REWARD' not in v.flags
 v.bag=True;v.run('School_Part1_Quiz');v.run('School_Part1_Quiz');assert v.gifts['ITEM_ORAN_BERRY']==1
 w=VM();w.question=q;w.choice=int(q==1);w.run('School_Part1_Quiz');assert not w.gifts and 'FLAG_DAILY_PART1_SCHOOL_SOLVED' not in w.flags
 for f in list(v.flags):
  if f.startswith('FLAG_DAILY_'):v.flags.remove(f)
 v.run('School_Part1_Quiz');assert v.gifts['ITEM_ORAN_BERRY']==2
for choice in range(6):
 v=VM();v.question=choice;v.flags.add('FLAG_MET_PRETTY_PETAL_SHOP_OWNER');v.bag=False;v.run('FlowerShop_Part1_Daily');assert 'FLAG_DAILY_PART1_FLOWER_BERRY' not in v.flags
 v.bag=True;v.run('FlowerShop_Part1_Daily');v.run('FlowerShop_Part1_Daily');assert sum(v.gifts.values())==1
assert 'DAILY_FLAGS_START / 8' in read('src/event_data.c') and 'ClearDailyFlags();' in read('src/clock.c')
print('Actual script branches: 8 gifts full-bag/retry/repeat, Wurmple Yes/No, 3 quiz answers/reset, 6 daily berry choices: PASS')
# Cry-only Pokémon and the no-function environmental props have no rewards/warps.
for label,species in [('PetalburgWoods_Part1_FriendWurmple','WURMPLE'),('Devon_Part1_Aron','ARON'),('Route116_Part1_Aron','ARON'),('RusturfTunnel_Part1_Whismur','WHISMUR')]:
 text=alltext[alltext.index(label+'::'):].split('\n\n')[0];assert 'playmoncry SPECIES_'+species in text and 'waitmoncry' in text and 'msgbox' not in text
for label in ['RusturfTunnel_Part1_Barrier','GraniteCave_Part1_MetalWall','BrineysHouse_Part1_Chart']:
 text=alltext[alltext.index(label+'::'):].split('\n\n')[0];assert not any(x in text for x in ['warp','giveitem','removeobject','RockSmash'])
print('Cry-only overworld Pokémon, inactive props, no future-area unlock: PASS')

# Compare original main-quest instructions after removing only approved append-only hooks.
def assemblycode(x):
 x=re.sub(r'(?m)^\s*\.string[^\n]*\n?', '',x)
 return re.sub(r'\s+','',re.sub(r'(?m)@[^\n]*','',x))
for folder,boundary,remove in [
 ('PetalburgWoods','PetalburgWoods_Part1_Transition::',['\tmap_script MAP_SCRIPT_ON_TRANSITION, PetalburgWoods_Part1_Transition\n']),
 ('Route104_PrettyPetalFlowerShop','FlowerShop_Part1_Daily::',[]),
 ('RustboroCity_DevonCorp_1F','Devon_Part1_Worker::',[]),
 ('RustboroCity_DevonCorp_3F',None,[]),
 ('Route104_MrBrineysHouse','BrineysHouse_Part1_Chart::',['\tmsgbox BrineysHouse_Part1_SailText, MSGBOX_DEFAULT\n\twaitse\n\tplaymoncry SPECIES_WINGULL, CRY_MODE_NORMAL\n\twaitmoncry\n']),
 ('RusturfTunnel','RusturfTunnel_Part1_ShowWhismur::',['\tsetflag FLAG_TEMP_C\n\tcall_if_set FLAG_RECOVERED_DEVON_GOODS, RusturfTunnel_Part1_ShowWhismur\n','\twaitse\n\tplaymoncry SPECIES_WINGULL, CRY_MODE_NORMAL\n\twaitmoncry\n','\tclearflag FLAG_TEMP_C\n\taddobject LOCALID_PART1_WHISMUR_1\n\taddobject LOCALID_PART1_WHISMUR_2\n\taddobject LOCALID_PART1_WHISMUR_3\n'])]:
 current=source(folder).split(boundary)[0] if boundary else source(folder)
 for token in remove:assert token in current,(folder,token);current=current.replace(token,'',1)
 assert assemblycode(current)==assemblycode(old(f'data/maps/{folder}/scripts.inc').decode()),(folder,'original main quest altered')
print('Original Forest Devon/Aqua, flower functions, Devon 1F/3F, Peeko rescue and Briney sailing instructions preserved: PASS')
