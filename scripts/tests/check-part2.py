#!/usr/bin/env python3
"""PART2 terminal-only data, actual C helpers and event-branch checks. Never runs a ROM."""
import json,re,struct,subprocess,tempfile
from collections import Counter,deque
from pathlib import Path
r=Path(__file__).resolve().parents[2];m=json.loads((r/'docs/project/part2-manifest.json').read_text());base=m['baseline']
from part4_compat import source as part4_source
from part5_compat import source as part5_source
def read(f):return part4_source(f,(r/f).read_text())
def old(f):return subprocess.check_output(['git','show',base+':'+f],cwd=r,text=True)
def function(s,name):
 match=re.search(r'(?m)^[\w *]+\b'+name+r'\([^;{}]*\)\n\{',s);assert match,name
 a=match.start();b=s.index('{',a);depth=1;i=b+1
 while depth:depth+=(s[i]=='{')-(s[i]=='}');i+=1
 return s[a:i]
def flood(ground,p):
 seen={p};q=deque(seen)
 while q:
  x,y=q.popleft()
  for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
   if p in ground and p not in seen:seen.add(p);q.append(p)
 return seen
flags=read('include/constants/flags.h');previous=old('include/constants/flags.h')
for name,value in m['flags'].items():
 defs=lambda s:[n for n,v in re.findall(r'^#define (FLAG_\w+)\s+(0x[0-9A-Fa-f]+)',s,re.M) if int(v,16)==value]
 assert defs(flags)==[name],name;assert len(defs(previous))==1 and 'UNUSED' in defs(previous)[0],name
for name,value in m['vars'].items():
 assert re.search(r'^#define '+name+r'\s+0x404E\b',read('include/constants/vars.h'),re.M)
 assert re.search(r'^#define VAR_UNUSED_0x404E\s+0x404E\b',old('include/constants/vars.h'),re.M)
for f in ['include/global.h','include/global.pokemon.h','include/pokemon.h','src/project_gifts.c','src/shop.c','src/part1.c','include/config/battle.h','include/config/project.h']:
 if (r/f).exists():assert read(f)==old(f),(f,'prior system or save ABI altered')
# PART3 reuses exactly four reserved IDs; every previous define stays byte-identical.
old_opponents=old('include/constants/opponents.h');new_opponents=read('include/constants/opponents.h')
part3_ids={'TRAINER_PART3_BREEDER':857,'TRAINER_PART3_PLUSLE_MINUN':858,'TRAINER_PART3_HIKER':859,'TRAINER_PART3_MAGMA_ROOKIE':860}
for name,value in part3_ids.items():
 pattern=r'^#define '+name+r'\s+'+str(value)+r'\b[^\n]*\n'
 assert len(re.findall(pattern,new_opponents,re.M))==1,name
 new_opponents=re.sub(pattern,'',new_opponents,flags=re.M)
old_count=re.search(r'^#define TRAINERS_COUNT_EMERALD[^\n]*',old_opponents,re.M).group()
assert re.search(r'^#define TRAINERS_COUNT_EMERALD\s+861\b',new_opponents,re.M)
new_opponents=re.sub(r'^#define TRAINERS_COUNT_EMERALD[^\n]*',old_count,new_opponents,flags=re.M)
# An optional explanatory comment accompanying the four new constants carries no data.
new_opponents=re.sub(r'(?m)^// PART 3[^\n]*\n','',new_opponents)
assert re.sub(r'\s+','',new_opponents)==re.sub(r'\s+','',old_opponents)
print('13 unused permanent flags, one unused quest VAR, unchanged save ABI and PART1/limited-shop core; four reserved PART3 trainer IDs: PASS')
layouts={x['id']:x for x in json.loads(read('data/layouts/layouts.json'))['layouts']};added=Counter(o['map'] for o in m['objects'])
for folder in set(added)|{o['map'] for o in m['backgrounds']}:
 f=f'data/maps/{folder}/map.json';v=json.loads(read(f));prev=json.loads(old(f));layout=layouts[v['layout']];w,h=layout['width'],layout['height'];cells=struct.unpack('<'+'H'*(w*h),(r/layout['blockdata_filepath']).read_bytes())
 assert v['object_events'][:len(prev['object_events'])]==prev['object_events'];assert len(v['object_events'])==len(prev['object_events'])+added[folder]
 for key in ['connections','warp_events','coord_events']:assert v.get(key)==prev.get(key),(folder,key)
 assert v['bg_events'][:len(prev['bg_events'])]==prev['bg_events']
 ground={(x,y) for y in range(h) for x in range(w) if (cells[y*w+x]>>10)&3==0 and cells[y*w+x]>>12 in (0,3)};occupied={(o['x'],o['y']) for o in v['object_events']}
 for a in [o for o in m['objects'] if o['map']==folder]:
  pos=a['x'],a['y'];assert pos in ground,(folder,pos,'collision')
  assert a['elevation']==cells[a['y']*w+a['x']]>>12
  assert {k:z for k,z in a.items() if k!='map'} in v['object_events'];assert sum((o['x'],o['y'])==pos for o in v['object_events'])==1
  adjacent={(pos[0]-1,pos[1]),(pos[0]+1,pos[1]),(pos[0],pos[1]-1),(pos[0],pos[1]+1)}&(ground-occupied)
  assert adjacent and adjacent<=flood(ground-occupied,next(iter(adjacent))),(folder,pos,'blocks route')
  for t in prev['object_events']:
   if t['trainer_type']!='TRAINER_TYPE_NORMAL':continue
   dirs=[d for d in ['UP','DOWN','LEFT','RIGHT'] if d in t['movement_type']] or ['UP','DOWN','LEFT','RIGHT']
   for d in dirs:
    dx,dy={'UP':(0,-1),'DOWN':(0,1),'LEFT':(-1,0),'RIGHT':(1,0)}[d]
    assert pos not in [(t['x']+i*dx,t['y']+i*dy) for i in range(1,int(t['trainer_sight_or_berry_tree_id'])+1)],(folder,pos,'trainer ray')
 # Existing oversized maps must not gain new simultaneous viewport saturation.
 for x,y in ground:
  def visible(objects):return sum(x-9<=o['x']<=x+10 and y-7<=o['y']<=y+9 for o in objects)
  now,was=visible(v['object_events']),visible(prev['object_events'])
  assert now<=15 or now==was,(folder,'viewport capacity',x,y,now,was)
 assert len({o.get('local_id',str(i+1)) for i,o in enumerate(v['object_events'])})==len(v['object_events'])
for a in m['backgrounds']:
 assert a['type']=='hidden_item' and a['item']=='ITEM_RARE_CANDY' and a['quantity']==1 and a['underfoot'] and m['flags'][a['flag']]>=0x1F4
# Scope: no edits outside the declared maps (plus original text changes at gym/bike/museum/sea house).
changed=subprocess.check_output(['git','diff','--name-only',base],cwd=r,text=True).splitlines()
allowed=set(added)|{'Route109_SeashoreHouse','Route110_TrickHouseEnd','MauvilleCity_BikeShop','MauvilleCity_Gym','SlateportCity_OceanicMuseum_1F','SlateportCity_OceanicMuseum_2F'}
allowed|={'Route117','Route117_PokemonDayCare','VerdanturfTown','VerdanturfTown_WandasHouse','VerdanturfTown_BattleTentLobby','VerdanturfTown_BattleTentBattleRoom','RusturfTunnel','Route116','Route111','Route111_WinstrateFamilyHouse','Route112','Route112_CableCarStation','FieryPath','ScorchedGrotto','Route113','Route113_GlassWorkshop','FallarborTown','FallarborTown_Mart','FallarborTown_MoveRelearnersHouse','Route114','Route114_LanettesHouse','Route114_FossilManiacsHouse','Route114_FossilManiacsTunnel','MeteorFalls_1F_1R','MtChimney','JaggedPass','LavaridgeTown','LavaridgeTown_Mart','LavaridgeTown_Gym_1F','LavaridgeTown_Gym_B1F'}
allowed |= set(json.loads((r/'docs/project/part4-manifest.json').read_text())['maps']) | {'PetalburgCity_Gym','PetalburgCity_WallysHouse','FortreeCity_Gym','FortreeCity_Mart'}
# PART5: every map folder recorded in the PART5 delta manifest (checked by check-part5.py)
_d5=json.loads((r/'docs/project/part5-deltas.json').read_text())
allowed |= {p.split('/')[2] for p in list(_d5['text'])+list(_d5['maps'])+_d5['new_files'] if p.startswith('data/maps/') and p.count('/')>=3}
_d55=json.loads((r/'docs/project/part55-deltas.json').read_text())
allowed |= {p.split('/')[2] for p in list(_d55['text'])+_d55['new_files'] if p.startswith('data/maps/') and p.count('/')>=3}
_d6=json.loads((r/'docs/project/part6-deltas.json').read_text())
allowed |= {p.split('/')[2] for p in list(_d6['text'])+_d6['new_files'] if p.startswith('data/maps/') and p.count('/')>=3}
_d7=json.loads((r/'docs/project/part7-deltas.json').read_text())  # PART7 scope is checked by check-part7.py
allowed |= {p.split('/')[2] for p in list(_d7['text'])+_d7['new_files'] if p.startswith('data/maps/') and p.count('/')>=3}
assert all(p=='data/maps/map_groups.json' or p.split('/')[2] in allowed for p in changed if p.startswith('data/maps/'))
print(f'{len(m["objects"])} objects and hidden pickup: ground, approach, nonblocking paths, sight rays, viewport capacity; original events and scope: PASS')
# Native old-rod tables unchanged: exact conditional weights are tested below in C.
part3_wild_methods={'MAP_FIERY_PATH':{'land_mons'},'MAP_ROUTE114':{'land_mons','fishing_mons'},'MAP_METEOR_FALLS_1F_1R':{'land_mons'},'MAP_JAGGED_PASS':{'land_mons'}}
def unchanged_other_wild_fields(a,b,map_id):
 permitted=part3_wild_methods[map_id]
 assert {k:v for k,v in a.items() if k not in permitted}=={k:v for k,v in b.items() if k not in permitted},map_id
 for method in permitted:
  assert a[method]['encounter_rate']==b[method]['encounter_rate'],(map_id,method)
def wild_entries(source):return {e['map']:e for group in json.loads(source)['wild_encounter_groups'] for e in group.get('encounters',[]) if 'map' in e}
old_wild=wild_entries(old('src/data/wild_encounters.json'));new_wild=wild_entries(read('src/data/wild_encounters.json'))
assert set(old_wild)==set(new_wild)
for map_id,before in old_wild.items():
 if map_id in part3_wild_methods:unchanged_other_wild_fields(before,new_wild[map_id],map_id)
 else:assert before==new_wild[map_id],map_id

for group in json.loads(read('src/data/wild_encounters.json'))['wild_encounter_groups']:
 for e in group.get('encounters',[]):
  if e.get('map') in ['MAP_SLATEPORT_CITY','MAP_ROUTE109']:
   assert [o['species'] for o in e['fishing_mons']['mons'][:2]]==['SPECIES_MAGIKARP','SPECIES_TENTACOOL']
# Only eight approved trainer entries change; all rematches and other areas remain identical.
def parties(s):return dict(re.findall(r'^=== (TRAINER_\w+) ===\n(.*?)(?=^=== |\Z)',s,re.M|re.S))
a,b=parties(old('src/data/trainers.party')),parties(read('src/data/trainers.party'))
for id in a:
 if id not in set(m['trainer_teams'])|{'TRAINER_VICTOR','TRAINER_VICTORIA','TRAINER_VIVI','TRAINER_VICKY','TRAINER_MAXIE_MT_CHIMNEY','TRAINER_FLANNERY_1'}:assert a[id].strip()==b[id].strip(),id
lu=read('src/data/pokemon/level_up_learnsets/gen_9.h');tm=read('src/data/pokemon/teachable_learnsets.h')
for id,team in m['trainer_teams'].items():
 assert re.findall(r'^Level: (\d+)',b[id],re.M)==[str(z[1]) for z in team]
 for name,level,moves,item in team:
  block=b[id][b[id].index('\n'+name):].split('\n\n')[0]
  assert all('- '+move in block for move in moves) and '12 HP' in block and 'EVs:' not in block
  learning=re.search(r's'+name+r'LevelUpLearnset\[\].*?\n};',lu,re.S).group()+re.search(r's'+name+r'TeachableLearnset\[\].*?\n};',tm,re.S).group()
  assert all('MOVE_'+v.upper().replace(' ','_') in learning for v in moves),(id,name,moves)
  assert item in [None,'Oran Berry']
 if 'ROUTE_110' in id:assert len(team)==4 and [o[1] for o in team]==[19,19,20,22] and team[0][0]=='Swellow' and team[-1][0] in ['Grovyle','Combusken','Marshtomp']
print('All six rival branches, Wally/Wattson parties and actual current legal learnsets; all other trainers retained: PASS')
# Every changed evolution array can be reverted to byte-identical baseline; all nontrade entries stay intact.
for f in set(e['file'] for e in m['evolution_changes']):
 s=read(f)
 for e in [e for e in m['evolution_changes'] if e['file']==f]:
  assert e['new'] in s and 'EVO_TRADE' not in e['new'];s=s.replace(e['new'],e['old'],1)
  rows=re.findall(r'\{EVO_ITEM, ITEM_EVOLUTION_STONE, (SPECIES_\w+)\}',e['new']);assert rows==e['targets'],e['species']
 assert s==old(f),(f,'nontrade data drift')
assert not any('EVO_TRADE' in p.read_text() for p in (r/'src/data/pokemon/species_info').glob('*.h'))
scyther=next(e for e in m['evolution_changes'] if e['species']=='SPECIES_SCYTHER');assert 'SPECIES_SCIZOR' in scyther['targets'] and 'ITEM_METAL_COAT' not in scyther['new']
items=read('src/data/items.h');charm=re.search(r'\[ITEM_PEACE_CHARM\] =\n    \{.*?\n    \},',items,re.S).group();assert all(x in charm for x in ['POCKET_KEY_ITEMS','.importance = 1','.price = 0','ItemUseOutOfBattle_CannotUse'])
assert 'ITEM_EVOLUTION_STONE ITEM_LINKING_CORD' in read('include/constants/items.h') and 'ITEM_PEACE_CHARM = 874' in read('include/constants/items.h')
cord=re.search(r'\[ITEM_LINKING_CORD\] =\n    \{.*?\n    \},',items,re.S).group();assert '进化石' in cord and '.price = 8000' in cord and 'ItemUseOutOfBattle_EvolutionStone' in cord
trade=re.search(r'\[INGAME_TRADE_PART2_VULPIX\].*?\n    \},',read('src/data/trade.h'),re.S).group();assert all(x in trade for x in ['SPECIES_MAWILE','SPECIES_VULPIX','小焰','.level = 18'])
assert 'inGameTrade->level != 0 ? inGameTrade->level : GetLevelFromBoxMonExp(boxmon)' in read('src/trade.c')
summary=read('src/pokemon_summary_screen.c');config=read('include/config/summary_screen.h')
for k in ['P_SUMMARY_SCREEN_IV_EV_INFO','P_SUMMARY_SCREEN_IV_EV_VALUES']:assert re.search(r'#define '+k+r'\s+TRUE',config)
assert re.search(r'#define P_SUMMARY_SCREEN_IV_HYPERTRAIN\s+FALSE',config)
assert 'else if (JOY_NEW(A_BUTTON))' in summary or 'JOY_NEW(A_BUTTON)' in summary
assert 'GetMonEVCount(&sMonSummaryScreen->currentMon)' in summary and '"/510"' in summary and '努力值总计' in summary
assert function(summary,'ExtractMonSkillIvData')==function(old('src/pokemon_summary_screen.c'),'ExtractMonSkillIvData') and function(summary,'ExtractMonSkillEvData')==function(old('src/pokemon_summary_screen.c'),'ExtractMonSkillEvData')
print('29 trade evolution source species/30 targets unified; other evolution data exact; key item and fixed-level native trade; Summary numeric modes: PASS')
# Interpret actual event commands, including full-bag and persistent-state branches.
alltext='\n'.join(part5_source(str(p.relative_to(r)),p.read_text()) for p in (r/'data/maps').glob('*/scripts.inc') if str(p.relative_to(r)) not in _d5['new_files'])+'\n'+read('data/scripts/part2.inc');lines=[];labels={}  # PART5 hunks reverted; PART5 flow checked in check-part5.py
for line in alltext.splitlines():
 line=line.split('@')[0].strip()
 if re.match(r'^\w+::?$',line):labels[line.rstrip(':')]=len(lines)
 elif line and not line.startswith('.'):lines.append(line)
class VM:
 def __init__(self):self.flags=set();self.vars={'TRUE':1,'FALSE':0,'PART2_CHARM_CARRIED':1};self.bag=True;self.gifts=Counter();self.removed=set();self.species=set();self.messages=[]
 def value(self,v):return self.vars.get(v,int(v) if v.isdigit() else 0 if v.startswith('VAR_') else v)
 def run(self,label):
  pc=labels[label];stack=[]
  for _ in range(500):
   ins=lines[pc];pc+=1;cmd,*rest=ins.split(None,1);args=[x.strip() for x in rest[0].split(',')] if rest else []
   if cmd=='end':return
   if cmd=='return':
    if not stack:return
    pc=stack.pop();continue
   if cmd in ['setflag','clearflag']:(self.flags.add if cmd=='setflag' else self.flags.discard)(args[0]);continue
   if cmd=='giveitem':
    self.vars['VAR_RESULT']=int(self.bag)
    if self.bag:self.gifts[self.value(args[0])]+=int(args[1]) if len(args)>1 else 1
   elif cmd=='msgbox':self.messages.append(args[0])
   elif cmd in ['setvar','copyvar']:self.vars[args[0]]=self.value(args[1])
   elif cmd=='removeobject':self.removed.add(args[0])
   elif cmd=='checkspecies':self.vars['VAR_RESULT']=int(args[0] in self.species)
   elif cmd.startswith(('goto','call')):
    ok=True
    if cmd.endswith('_if_set'):ok=args[0] in self.flags
    elif cmd.endswith('_if_unset'):ok=args[0] not in self.flags
    elif cmd.endswith('_if_eq'):ok=self.value(args[0])==self.value(args[1])
    elif cmd.endswith('_if_ge'):ok=self.value(args[0])>=self.value(args[1])
    elif cmd.endswith('_if_lt'):ok=self.value(args[0])<self.value(args[1])
    elif cmd not in ['goto','call']:raise AssertionError(('unhandled jump',ins))
    if ok:
     if cmd.startswith('call'):stack.append(pc)
     pc=labels[args[-1]]
  raise AssertionError(('nonterminating',label))
cases=[('Part2_TryMysticWater','FLAG_DEFEATED_SEASHORE_HOUSE','FLAG_PART2_RECEIVED_MYSTIC_WATER','ITEM_MYSTIC_WATER',1),('Slateport_Part2_FocusPunch',None,'FLAG_PART2_RECEIVED_FOCUS_PUNCH','ITEM_TM_FOCUS_PUNCH',1),('Slateport_Part2_Delivery','FLAG_PART2_WINGULL_FOUND','FLAG_PART2_WINGULL_REWARD','ITEM_GREAT_BALL',3),('Part2_TryMuseumThanks','FLAG_DELIVERED_DEVON_GOODS','FLAG_PART2_RECEIVED_HEART_SCALES','ITEM_HEART_SCALE',3),('Route110_Part2_SuperPotion',None,'FLAG_PART2_ROUTE110_SUPER_POTION','ITEM_SUPER_POTION',1),('Route110_Part2_Ether',None,'FLAG_PART2_ROUTE110_ETHER','ITEM_ETHER',1),('Part2_TryTrickBonus',None,'FLAG_PART2_TRICK_EXTRA_CANDY','ITEM_RARE_CANDY',1)]
for label,pre,flag,item,qty in cases:
 v=VM()
 if label=='Part2_TryTrickBonus':
  v.run(label);assert not v.gifts;v.vars['VAR_TRICK_HOUSE_LEVEL']=1
 if pre:v.run(label);assert not v.gifts;v.flags.add(pre)
 v.bag=False;v.run(label);assert flag not in v.flags and not v.gifts
 v.bag=True;v.run(label);assert flag in v.flags and v.gifts[item]==qty,(label,v.gifts)
 v.run(label);assert v.gifts[item]==qty
v=VM();v.bag=False;v.run('Slateport_Part2_Charm');assert v.value('VAR_PART2_PEACE_CHARM_STATE')==0 and not v.gifts
v.bag=True;v.run('Slateport_Part2_Charm');v.run('Slateport_Part2_Charm');assert v.gifts['ITEM_PEACE_CHARM']==1 and v.value('VAR_PART2_PEACE_CHARM_STATE')==1
for species in [set(),{'SPECIES_RALTS'},{'SPECIES_KIRLIA'},{'SPECIES_GARDEVOIR'}]:
 v=VM();v.species=species;v.run('Route110_Part2_RaltsCheck');assert bool(v.messages)==bool(species&{'SPECIES_RALTS','SPECIES_KIRLIA'})
v=VM();v.run('Slateport_Part2_WingullLost');assert 'FLAG_PART2_WINGULL_FOUND' in v.flags and 'LOCALID_PART2_WINGULL_LOST' in v.removed
assert 'FLAG_TEMP_C' not in v.flags
for label in ['Slateport_Part2_WingullHome','Mauville_Part2_Mareep']:
 b=alltext[alltext.index(label+'::'):].split('\n\n')[0];assert 'playmoncry' in b and 'waitmoncry' in b and 'msgbox' not in b
# Original critical story instructions: only the explicitly listed hooks and attendants change.
for folder,hooks in {'Route109_SeashoreHouse':['call Part2_TryMysticWater'],'SlateportCity_OceanicMuseum_2F':['call Part2_TryMuseumThanks'],'Route110':['call Route110_Part2_RaltsCheck'],'Route110_TrickHouseEnd':['call Part2_TryTrickBonus'],'MauvilleCity':[],'MauvilleCity_Gym':[],'MauvilleCity_BikeShop':[]}.items():
 f=f'data/maps/{folder}/scripts.inc';before=old(f);now=read(f);prefix=now[:len(now)]
 def commands(s):
  # Only the original label range, up to first PART2 appended block.
  s=s.split('\nRoute110_Part2_SuperPotion::')[0].split('\nMauville_Part2_IVTutor::')[0]
  return [x.strip() for x in s.splitlines() if x.strip() and not x.strip().startswith(('.string','@'))]
 expected=commands(before);actual=commands(prefix)
 for hook in hooks:actual=[x for x in actual if x!=hook]
 if folder=='Route110':actual=actual[:len(expected)]
 assert actual[:len(expected)]==expected,(folder,'original progression drift')
print('Actual script branches: seven gifts full/retry/repeat, charm save state, Wingull restoration, rival species checks, original plot instruction retention: PASS')
# Compile actual gift, selector, fishing function and summary numeric readers natively.
with tempfile.TemporaryDirectory() as d:
 p=Path(d);(p/'constants').mkdir()
 (p/'global.h').write_text('''#ifndef TEST_GLOBAL
#define TEST_GLOBAL
#include <stdint.h>
typedef uint8_t u8; typedef uint8_t bool8; typedef uint16_t u16; typedef uint32_t u32; typedef int32_t bool32;
#define TRUE 1
#define FALSE 0
#define PARTY_SIZE 6
#define MAX_PER_STAT_IVS 31
enum Species { SPECIES_NONE, SPECIES_CLAMPERL, SPECIES_HUNTAIL, SPECIES_GOREBYSS, SPECIES_SCYTHER, SPECIES_SCIZOR };
enum Item { ITEM_NONE, ITEM_EVOLUTION_STONE };
#define EWRAM_DATA
#define OTID_STRUCT_PLAYER_ID 0
struct Pokemon { int iv[6], atk, level, personality; };
extern u16 gSpecialVar_Result;
#endif
''')
 (p/'event_data.h').write_text('u8 FlagGet(u16); void FlagSet(u16);\n')
 (p/'pokemon.h').write_text('''#define MON_DATA_ATK_IV 1
#define MON_GIVEN_TO_PARTY 0
u8 CalculatePlayerPartyCount(void);
void CreateMon(struct Pokemon *, enum Species, u8, u32, int);
void SetMonData(struct Pokemon *, int, const void *);
void CalculateMonStats(struct Pokemon *);
u8 GiveCapturedMonToPlayer(struct Pokemon *);
void HandleSetPokedexFlagFromMon(struct Pokemon *,u32);
''')
 (p/'pokedex.h').write_text('#define FLAG_SET_SEEN 0\n#define FLAG_SET_CAUGHT 1\n');(p/'random.h').write_text('u32 Random32(void);\n');(p/'constants/flags.h').write_text('#define FLAG_SYS_POKEMON_GET 3\n#define FLAG_PART2_RECEIVED_SCYTHER 47\n');(p/'constants/items.h').write_text('')
 fish=function(read('src/wild_encounter.c'),'ChooseWildMonIndex_Fishing')
 fishdefs='\n'.join('#define '+k+' '+str(v) for k,v in {'OLD_ROD':0,'GOOD_ROD':1,'SUPER_ROD':2,'ENCOUNTER_CHANCE_FISHING_MONS_OLD_ROD_TOTAL':100,'ENCOUNTER_CHANCE_FISHING_MONS_GOOD_ROD_TOTAL':100,'ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_TOTAL':100,'ENCOUNTER_CHANCE_FISHING_MONS_OLD_ROD_SLOT_0':70,'ENCOUNTER_CHANCE_FISHING_MONS_GOOD_ROD_SLOT_2':60,'ENCOUNTER_CHANCE_FISHING_MONS_GOOD_ROD_SLOT_3':80,'ENCOUNTER_CHANCE_FISHING_MONS_GOOD_ROD_SLOT_4':100,'ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_5':40,'ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_6':80,'ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_7':95,'ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_8':99,'ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_9':100,'MAP_SLATEPORT_CITY':0x401,'MAP_ROUTE109':0x21D}.items())
 (p/'test.c').write_text('''#include "global.h"
#include "part2.h"
#include <assert.h>
#include <string.h>
u16 gSpecialVar_Result;
static u8 flags[64],party,delivery;static int created,delivered,calc,dex;static struct Pokemon received;
u8 FlagGet(u16 f){return flags[f];} void FlagSet(u16 f){flags[f]=1;}
u8 CalculatePlayerPartyCount(void){return party;} u32 Random32(void){return 1024+created;}
void CreateMon(struct Pokemon *p,enum Species s,u8 lv,u32 personality,int ot){assert(s==SPECIES_SCYTHER && lv==18 && ot==0); for(int i=0;i<6;i++)p->iv[i]=i+created; p->level=lv;p->personality=personality;created++;}
void SetMonData(struct Pokemon *p,int field,const void *v){assert(field==1);p->iv[1]=*(const u32*)v;}
void CalculateMonStats(struct Pokemon *p){p->atk=p->iv[1]+p->level;calc++;}
u8 GiveCapturedMonToPlayer(struct Pokemon *p){assert(p->iv[1]==31 && p->atk==49);received=*p;delivered++;return delivery;}
void HandleSetPokedexFlagFromMon(struct Pokemon *p,u32 c){assert(p->level==18 && c<2);dex++;}
struct Save {struct {u8 mapGroup,mapNum;} location;} save,*gSaveBlock1Ptr=&save;
static int randomValue,lure;
#define max(a,b) ((a)>(b)?(a):(b))
#define MAP_GROUP(x) ((x)>>8)
#define MAP_NUM(x) ((x)&255)
#define LURE_STEP_COUNT lure
static u32 Random(void){return randomValue;}
'''+fishdefs+'\n'+fish+'''
int main(void){
 GivePart2Scyther();assert(created==0 && !gSpecialVar_Result);
 flags[3]=1;party=6;GivePart2Scyther();assert(!created && !flags[47]);
 party=5;delivery=2;GivePart2Scyther();assert(created==1 && !flags[47] && !gSpecialVar_Result && !dex);
 delivery=0;GivePart2Scyther();assert(created==2 && flags[47] && gSpecialVar_Result && dex==2 && calc==2 && delivered==2);
 for(int i=0;i<6;i++)if(i!=1)assert(received.iv[i]==i+1);
 assert(received.personality==1025 && received.level==18);GivePart2Scyther();assert(created==2 && !gSpecialVar_Result);
 gPart2EvolutionTarget=SPECIES_GOREBYSS;assert(Part2EvolutionTargetAllowed(SPECIES_CLAMPERL,ITEM_EVOLUTION_STONE,SPECIES_GOREBYSS));assert(!Part2EvolutionTargetAllowed(SPECIES_CLAMPERL,ITEM_EVOLUTION_STONE,SPECIES_HUNTAIL));assert(Part2EvolutionTargetAllowed(SPECIES_SCYTHER,ITEM_EVOLUTION_STONE,SPECIES_SCIZOR));
 gPart2EvolutionTarget=SPECIES_HUNTAIL;assert(Part2EvolutionTargetAllowed(SPECIES_CLAMPERL,ITEM_EVOLUTION_STONE,SPECIES_HUNTAIL));
 gPart2EvolutionTarget=SPECIES_NONE;assert(Part2EvolutionTargetAllowed(SPECIES_CLAMPERL,ITEM_EVOLUTION_STONE,SPECIES_HUNTAIL));
 for(int map=0;map<3;map++){int mapId=map==0?MAP_SLATEPORT_CITY:map==1?MAP_ROUTE109:0x999;save.location.mapGroup=MAP_GROUP(mapId);save.location.mapNum=MAP_NUM(mapId);
 int hits[10]={0};for(int i=0;i<100;i++){randomValue=i;hits[ChooseWildMonIndex_Fishing(OLD_ROD)]++;}assert(hits[0]==(map<2?40:70) && hits[1]==(map<2?60:30));
 memset(hits,0,sizeof(hits));for(int i=0;i<100;i++){randomValue=i;hits[ChooseWildMonIndex_Fishing(GOOD_ROD)]++;}assert(hits[2]==60 && hits[3]==20 && hits[4]==20);
 memset(hits,0,sizeof(hits));for(int i=0;i<100;i++){randomValue=i;hits[ChooseWildMonIndex_Fishing(SUPER_ROD)]++;}assert(hits[5]==40 && hits[6]==40 && hits[7]==15 && hits[8]==4 && hits[9]==1);}
 return 0;}
''')
 subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror',f'-I{p}',f'-I{r/"include"}',str(p/'test.c'),str(r/'src/part2.c'),'-o',str(p/'test')],check=True);subprocess.run([str(p/'test')],check=True)
print('Actual native Scyther delivery boundaries/random data, both Clamperl selectors, coastal exact 40/60 and unaffected other maps/rods: PASS')

# Execute the production ITEM/TRADE evolution loop against every converted table entry.
pokemon=read('src/pokemon.c');start=pokemon.index('    case EVO_MODE_TRADE:',pokemon.index('enum Species GetEvolutionTargetSpecies('));end=pokemon.index('    // Battle evolution without leveling;',start);engine=pokemon[start:end]
species=sorted({'SPECIES_NONE'}|{e['species'] for e in m['evolution_changes']}|{t for e in m['evolution_changes'] for t in e['targets']})
with tempfile.TemporaryDirectory() as d:
 p=Path(d);entries=[];tests=[]
 for i,e in enumerate(m['evolution_changes']):
  rows=re.findall(r'\{EVO_ITEM, ITEM_EVOLUTION_STONE, (SPECIES_\w+)\}',e['new'])
  entries.append('static const struct Evolution evo'+str(i)+'[] = {'+','.join('{EVO_ITEM, ITEM_EVOLUTION_STONE,'+v+',0}' for v in rows)+',{EVOLUTIONS_END,0,SPECIES_NONE,0}};')
  for target in rows:tests.append(f'evolutions=evo{i};selected={target};assert(evaluate({e["species"]}, EVO_MODE_ITEM_USE, ITEM_EVOLUTION_STONE)=={target});assert(evaluate({e["species"]}, EVO_MODE_TRADE, ITEM_EVOLUTION_STONE)==SPECIES_NONE);assert(evaluate({e["species"]}, EVO_MODE_ITEM_USE, ITEM_OTHER)==SPECIES_NONE);')
 source='''#include <stdint.h>
#include <stddef.h>
#include <assert.h>
typedef int bool32;
#define TRUE 1
#define FALSE 0
#define PARTY_SIZE 6
enum Species {'''+','.join(species)+'''};
enum Item { ITEM_EVOLUTION_STONE, ITEM_OTHER };
enum {EVOLUTIONS_END,EVO_TRADE,EVO_ITEM,EVO_MODE_TRADE,EVO_MODE_ITEM_USE,EVO_MODE_ITEM_CHECK};
struct Evolution {int method; enum Item param; enum Species targetSpecies;void *params;};
static const struct Evolution *evolutions;
static enum Species selected;
static enum Species SanitizeSpeciesId(enum Species s){return s;}
static bool32 DoesMonMeetAdditionalConditions(void *a,void *b,void *c,int d,bool32 *e,int f){(void)a;(void)b;(void)c;(void)d;(void)e;(void)f;return TRUE;}
static bool32 Part2EvolutionTargetAllowed(enum Species s,enum Item i,enum Species t){return s!=SPECIES_CLAMPERL || i!=ITEM_EVOLUTION_STONE || t==selected;}
static enum Species evaluate(enum Species species,int mode,enum Item evolutionItem){
int i,evoState=0;void *mon=NULL,*tradePartner=NULL;bool32 stop=TRUE,*canStopEvo=&stop;enum Species targetSpecies=SPECIES_NONE;
switch(mode){'''+engine+'''} return targetSpecies;}
'''+ '\n'.join(entries)+'\nint main(void){'+''.join(tests)+'return 0;}'
 (p/'engine.c').write_text(source);subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror',str(p/'engine.c'),'-o',str(p/'engine')],check=True);subprocess.run([str(p/'engine')],check=True)
# Exercise actual six-stat numeric readers and the production EV summation (0, mixed, 510).
with tempfile.TemporaryDirectory() as d:
 p=Path(d);names=['HP','ATK','DEF','SPEED','SPATK','SPDEF'];prefix='''#include <stdint.h>
#include <assert.h>
typedef uint16_t u16;typedef uint32_t u32;
#define NUM_STATS 6
struct Pokemon {u16 iv[6],ev[6];};struct PokeSummary {u16 currentHP,atk,def,spatk,spdef,speed;};
'''+ '\n'.join('#define MON_DATA_'+name+'_EV '+str(i) for i,name in enumerate(names))+'\n'+'\n'.join('#define STAT_'+name+' '+str(i) for i,name in enumerate(names))+'''
static u32 GetMonData(struct Pokemon *m,int f,...){return m->ev[f];}
static u32 GetAdjustedIvData(struct Pokemon *m,int f){return m->iv[f];}
'''
 source=prefix+function(summary,'ExtractMonSkillIvData')+'\n'+function(summary,'ExtractMonSkillEvData')+'\n'+function(pokemon,'GetMonEVCount')+'''
int main(void){struct Pokemon m={{31,27,18,30,31,22},{0,124,0,134,252,0}};struct PokeSummary s;
ExtractMonSkillIvData(&m,&s);assert(s.currentHP==31 && s.atk==27 && s.def==18 && s.spatk==31 && s.spdef==22 && s.speed==30);
ExtractMonSkillEvData(&m,&s);assert(s.currentHP==0 && s.atk==124 && s.def==0 && s.spatk==252 && s.spdef==0 && s.speed==134);assert(GetMonEVCount(&m)==510);
for(int i=0;i<6;i++)m.ev[i]=0;assert(GetMonEVCount(&m)==0);m.ev[0]=5;m.ev[5]=124;assert(GetMonEVCount(&m)==129);return 0;}
''';(p/'summary.c').write_text(source);subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror','-Wno-misleading-indentation',str(p/'summary.c'),'-o',str(p/'summary')],check=True);subprocess.run([str(p/'summary')],check=True)
print('Production evolution ITEM/TRADE loops: all 30 targets/no trade/no second item; actual Summary six IV/EV values and totals 0/129/510: PASS')
print('PART2 static/native verification complete. Visual gameplay and save/load remain manual; no emulator was started.')
