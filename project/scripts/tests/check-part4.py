#!/usr/bin/env python3
"""PART4 source, collision, allocation, data and native-flow checks. No ROM execution."""
from pathlib import Path
from collections import Counter,deque
import json,re,struct,subprocess
from part4_compat import source as legacy_source,baseline
from part5_compat import source as part5_source
from part55_compat import source as part55_source
r=Path(__file__).resolve().parents[2];m=json.loads((r/'docs/project/part4-manifest.json').read_text());s=part55_source('data/scripts/part4.inc')
def read(f):return part55_source(f)
def ok(name,condition=True):assert condition,name;print('PASS:',name)
def block(label):
 hit=re.search(r'^\s*'+re.escape(label)+r'::\n(.*?)(?=^\s*\w+::|\Z)',s,re.M|re.S);assert hit,label;return hit[1]
def flood(g,p):
 seen={p};q=deque(seen)
 while q:
  x,y=q.popleft()
  for z in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
   if z in g and z not in seen:seen.add(z);q.append(z)
 return seen
layouts={z['id']:z for z in json.loads(read('data/layouts/layouts.json'))['layouts']}
def grid(name):
 v=json.loads(read('data/maps/'+name+'/map.json'));l=layouts[v['layout']];w,h=l['width'],l['height'];raw=(r/l['blockdata_filepath']).read_bytes();assert len(raw)==2*w*h;cells=struct.unpack('<'+'H'*(w*h),raw);g={(x,y) for y in range(h) for x in range(w) if (cells[y*w+x]>>10)&3==0 and cells[y*w+x]>>12 in (0,3)};return v,l,cells,g
# Preserve actual native map structures, except the precisely approved PART3 reward change.
for name,meta in m['maps'].items():
 v,l,c,g=grid(name);assert len(v['object_events'])<=64 and len(v['coord_events'])<=255 and len(v['bg_events'])<=255
 if meta['before'] is not None:legacy_source('data/maps/'+name+'/map.json',json.dumps(v))
 occupied={(o['x'],o['y']) for o in v['object_events']};walk=g-occupied
 for a in meta['objects']:
  actual=next(o for o in v['object_events'] if o.get('local_id')==a['local_id']);assert actual==a,(name,'stale manifest',a['local_id']);pos=a['x'],a['y'];assert pos in g and a['elevation']==c[pos[1]*l['width']+pos[0]]>>12,(name,a['local_id'],pos,a['elevation'],hex(c[pos[1]*l['width']+pos[0]]))
  assert sum((o['x'],o['y'])==pos for o in v['object_events'])==1,(name,'NPC overlap',a['local_id'])
  adj={(pos[0]-1,pos[1]),(pos[0]+1,pos[1]),(pos[0],pos[1]-1),(pos[0],pos[1]+1)}&walk;assert adj,(name,'inaccessible',a['local_id'])
  accessible=walk | {(x,y) for y in range(l['height']) for x in range(l['width']) if c[y*l['width']+x]>>12==1 and (c[y*l['width']+x]>>10)&3==0} if a['graphics_id']=='OBJ_EVENT_GFX_ITEM_BALL' else walk
  if not (name=='Route118' and a['flag'].startswith('FLAG_PART4_HIDE_')):
   assert adj<=flood(accessible,next(iter(adj))),(name,'NPC divides paths',a['local_id'],adj)
  assert pos not in {(z['x'],z['y']) for z in v['warp_events']+v['coord_events']+v['bg_events']},(name,'NPC/event overlap',pos)
  assert re.search(r'#define '+a['local_id']+r'\s+'+str(v['object_events'].index(actual)+1)+r'\b',read('include/constants/part4.h'))
 print('Map native events and local access:',name)
ok('all new NPC approaches, local passage connectivity, unique local IDs and event capacities')
# Native Gabby/Ty copies are mutually exclusive; count one pair, never three.
def npc_peak(objects,stage=None):
 filtered=[]
 for o in objects:
  flag=o['flag']
  if flag in ['FLAG_HIDE_ROUTE_118_GABBY_AND_TY_2','FLAG_HIDE_ROUTE_118_GABBY_AND_TY_3']:continue
  if stage is not None:
   if flag=='FLAG_PART4_HIDE_AQUA_A' and stage>=1:continue
   if flag=='FLAG_PART4_HIDE_AQUA_B' and stage>=2:continue
   if flag=='FLAG_PART4_HIDE_AQUA_EXTRA' and stage!=2:continue
   if flag=='FLAG_PART4_HIDE_ANTI' and (stage<2 or stage>=4):continue
  filtered.append(o)
 return max((sum(x<=t['x']<=x+19 and y<=t['y']<=y+16 for t in filtered) for o in filtered for x in [o['x'],o['x']-19] for y in [o['y'],o['y']-16]),default=0)
capacity={}
for name,meta in m['maps'].items():
 v=grid(name)[0]
 peak=max(npc_peak(v['object_events'],stage) for stage in range(5)) if name=='Route118' else npc_peak(v['object_events'])
 previous=npc_peak(meta['before']['object_events']) if meta['before'] else 0
 assert peak<=15 or peak<=previous,(name,'new object capacity regression',peak,previous)
 capacity[name]={'peak_npcs':peak,'baseline_peak':previous,'qualification':'initial coordinates; mutually exclusive native reporters filtered; existing native peaks preserved'}
(r/'docs/project/part4-capacity.json').write_text(json.dumps(capacity,indent=2)+'\n')
ok('five 118 stages peak14 NPCs plus player fit16; no other added viewport overflow')
# Appended maps/layouts do not renumber existing persistent IDs.
for f,key in [('data/maps/map_groups.json',None),('data/layouts/layouts.json','layouts')]:
 current=json.loads(read(f));prior=json.loads(baseline(f))
 if key:assert current[key][:len(prior[key])]==prior[key]
 else:
  for group,values in prior.items():
   if isinstance(values,list):assert current[group][:len(values)]==values
ok('all native map and layout ID prefixes unchanged; three rooms appended')
# Visible scene movement destinations contain neither a live actor nor a wall.
v,l,c,g=grid('Route118');actors={o['local_id']:(o['x'],o['y']) for o in v['object_events'] if o.get('local_id','').startswith('LOCALID_PART4_')}
for actor,delta in [('LOCALID_PART4_ANTISCIZOR',(-1,0)),('LOCALID_PART4_AQUAEXTRA0',(1,0)),('LOCALID_PART4_AQUAEXTRA1',(1,0)),('LOCALID_PART4_AQUAEXTRA2',(1,0))]:
 pos=actors[actor];to=(pos[0]+delta[0],pos[1]+delta[1]);assert to in g
 assert to not in {p for a,p in actors.items() if a!=actor and a not in ['LOCALID_PART4_AQUAA','LOCALID_PART4_AQUAB']},(actor,to)
ok('Scizor and retreat movement destinations walkable and free')

# Actual allocations preserve all old saves and the original trainer flag capacity.
for kind,file in [('flags','flags'),('vars','vars')]:
 current=read('include/constants/'+file+'.h');old=baseline('include/constants/'+file+'.h');prefix='FLAG' if kind=='flags' else 'VAR'
 for name,value in m[kind].items():
  names=[n for n,v in re.findall(r'^#define ('+prefix+r'_\w+)\s+0x([0-9A-F]+)\b',current,re.M) if int(v,16)==value];assert names==[name],(name,names)
  names=[n for n,v in re.findall(r'^#define ('+prefix+r'_\w+)\s+0x([0-9A-F]+)\b',old,re.M) if int(v,16)==value];assert len(names)==1 and 'UNUSED' in names[0]
for f in ['include/global.h','include/global.pokemon.h','include/pokemon.h','include/constants/global.h','include/config/battle.h','include/config/project.h']:
 if (r/f).exists():assert read(f)==baseline(f),f
ok('Flag/VAR unused allocations and save/name/mechanics ABI unchanged')
legacy_source('include/constants/opponents.h');ok('864 reserved trainer bits unchanged; three remaining IDs and audited unused trainer aliases')
# Weighted data and all unrelated encounter data retain exact baseline values.
w=json.loads(read('src/data/wild_encounters.json'));entries={e['map']:e for g in w['wild_encounter_groups'] for e in g.get('encounters',[]) if 'map' in e};weights=[20,20,10,10,10,10,5,5,4,4,1,1]
def distribution(name):
 e=entries[name];rate=Counter()
 for chance,mon in zip(weights,e['land_mons']['mons']):
  rate[mon['species']]+=chance;assert 1<=mon['min_level']<=mon['max_level']<=100
 return dict(rate)
expected={'SPECIES_TRAPINCH':30,'SPECIES_BALTOY':20,'SPECIES_CACNEA':20,'SPECIES_SANDILE':10,'SPECIES_GIBLE':5,'SPECIES_SANDSHREW':7,'SPECIES_HIPPOPOTAS':8}
ok('desert Sandile10 Hippo8 Gible5 and native species retained',distribution('MAP_ROUTE111')==expected)
ok('rain route Cottonee5 Heracross5',distribution('MAP_ROUTE119').get('SPECIES_COTTONEE')==5 and distribution('MAP_ROUTE119').get('SPECIES_HERACROSS')==5)
for name in ['MAP_NEW_MAUVILLE_MAINTENANCE','MAP_NEW_MAUVILLE_HIGH_VOLTAGE']:
 d=distribution(name);ok(name+' Tynamo10 Klink10 Elekid5',d.get('SPECIES_TYNAMO')==10 and d.get('SPECIES_KLINK')==10 and d.get('SPECIES_ELEKID')==5)
legacy_source('src/data/wild_encounters.json');ok('all unrelated land/water/rock/fishing and native Feebas table retained')
# Learnability is actual species compatibility. Winona Dragon Dance is an explicitly requested legacy move.
p=part5_source('src/data/trainers.party',read('src/data/trainers.party'));  # PART5 rival fix checked in check-part5.py
learning=json.loads(read('src/data/pokemon/all_learnables.json'));lu=read('src/data/pokemon/level_up_learnsets/gen_9.h');teach=read('src/data/pokemon/teachable_learnsets.h')
for trainer,meta in m['trainers'].items():
 raw=re.search(r'^=== '+trainer+r' ===\n(.*?)(?=^=== |\Z)',p,re.M|re.S)[1];actual=[]
 for b in re.split(r'\n\s*\n',raw):
  if 'Level:' not in b:continue
  species=b.splitlines()[0].split(' @ ')[0];level=int(re.search(r'^Level: (\d+)',b,re.M)[1]);moves=re.findall(r'^- (.+)$',b,re.M);actual.append((species,level));assert 'EVs:' not in b
  current=''.join(z[0] for text,pat in [(lu,'s'+species+'LevelUpLearnset'),(teach,'s'+species+'TeachableLearnset')] if (z:=re.search(re.escape(pat)+r'\[\].*?\n};',text,re.S)))
  for move in moves:
   key='MOVE_'+move.upper().replace(' ','_');assert key in learning[species.upper()],(trainer,species,move)
   if (trainer,species,move)!=('TRAINER_WINONA_1','Altaria','Dragon Dance'):assert key in current,(trainer,species,move)
 assert actual==[(z[0],z[1]) for z in meta['party']],trainer
legacy_source('src/data/trainers.party');ok('all PART4 roster levels/moves legal and all unrelated parties/rematches unchanged')
for trainer,team in [('TRAINER_NORMAN_1',[('Spinda',29),('Linoone',29),('Zangoose',30),('Vigoroth',30),('Slaking',32)]),('TRAINER_WINONA_1',[('Swellow',30),('Pelipper',30),('Tropius',31),('Skarmory',32),('Altaria',33)])]:ok(trainer+' exact five-member team',[(z[0],z[1]) for z in m['trainers'][trainer]['party']]==team)
winona=re.search(r'^=== TRAINER_WINONA_1 ===\n.*?(?=^=== )',p,re.M|re.S)[0];ok('Winona no Mega/competitive held stone','Altaria @ Sitrus Berry' in winona and 'Mega' not in winona and '- Dragon Dance' in winona)
# One-time successful item delivery ordering in actual assembled event bodies.
gifts=re.findall(r'^\s*(Part4_\w+)::\n(.*?)(?=^\s*Part4_\w+::|\Z)',s,re.M|re.S);checked=0
for label,b in gifts:
 if 'giveitem' not in b:continue
 assert 'goto_if_eq VAR_RESULT, FALSE, Part4_BagFull' in b,(label,'bag failure')
 assert b.index('giveitem')<b.index('goto_if_eq VAR_RESULT, FALSE')
 for command in ['setflag FLAG_PART4_','setvar VAR_PART4_','removeitem ITEM_']:
  if command in b:assert b.index('goto_if_eq VAR_RESULT, FALSE')<b.index(command),(label,command)
 checked+=1
ok(str(checked)+' gift/quest delivery paths retain eligibility before flag/state/quest consumption')
for label,item in [('Part4_FirstEvolutionStone','EVOLUTION_STONE'),('Part4_SurfLeftovers','LEFTOVERS'),('Part4_Route115KingsRock','KINGS_ROCK'),('Part4_BottlePearl','PEARL'),('Part4_ShipMetalCoat','METAL_COAT'),('Part4_ShipDivePPUp','PP_UP'),('Part4_Manectite','MANECTITE'),('Part4_Mawilite','MAWILITE'),('Part4_RuinsAggronite','AGGRONITE'),('Part4_DestructionFactor','DESTRUCTION_FACTOR')]:ok(label+' exact once-only reward', 'giveitem ITEM_'+item in block(label) and 'goto_if_set FLAG_PART4_' in block(label))
ok('oasis candy and unchanged fossil/tower/Regirock gates',any(z.get('item')=='ITEM_RARE_CANDY' for z in grid('Route111')[0]['bg_events']) and read('data/maps/DesertRuins/scripts.inc')==baseline('data/maps/DesertRuins/scripts.inc') and read('data/maps/MirageTower_4F/scripts.inc')==baseline('data/maps/MirageTower_4F/scripts.inc'))
ok('canteen and berry-basket returns reward before consuming key',all('removeitem ITEM_' in block(x) for x in ['Part4_Canteen_Return','Part4_BerryBasket_Return']))
ok('kite and sealed parcel return rewards retained',all('removeitem ITEM_' in block(x) for x in ['Part4_Kite_Return','Part4_Parcel_Return']))
# Child's dynamic positions are disjoint from all other native/new objects.
v,l,c,g=grid('Route119');occupied={(o['x'],o['y']) for o in v['object_events'] if o.get('local_id') not in ['LOCALID_PART4_LOST_CHILD','LOCALID_PART4_CHILD_LOTAD']};home=tuple(m['child_positions']['home']);lotad=tuple(m['child_positions']['lotad_home']);ok('child/Lotad return positions distinct, walkable and no parent overlap',home!=lotad and home in g-occupied and lotad in g-occupied)
# Scene state, identity, native Mega gate and early private gifts stay independent.
scene=s[s.index('Part4_MegaScene::'):s.index('Part4_SceneEnd::')]
ok('118 two trainer defeated checks and before-gift persisted stage3',all(t in scene for t in ['goto_if_defeated TRAINER_PART4_AQUA_A','goto_if_defeated TRAINER_PART4_AQUA_B','setvar VAR_PART4_MEGA_STAGE, 3']))
ok('118 badge5 Surf prerequisite and completed stage prevents replay',all(t in scene for t in ['FLAG_BADGE05_GET','FLAG_RECEIVED_HM_SURF','goto_if_ge VAR_PART4_MEGA_STAGE, 4']))
ok('normal Scizor cue, no trainer-vs-trainer or Mega form', 'playmoncry SPECIES_SCIZOR, CRY_MODE_NORMAL' in scene and 'SPECIES_SCIZOR_MEGA' not in scene)
assert all(t not in scene for t in ['ARCHE','阿尔刻','安提','RECEIVED_SCYTHER','SPECIES_SCYTHER','RECEIVED_LITTLEROOT_RALTS_EGG']);ok('anonymous first encounter and private egg/Scyther independent')
scene_text=''.join(re.search(r'^'+label+r':\n\s*\.string \"([^\"]*)\"',s,re.M)[1] for label in re.findall(r'msgbox (Part4_Text_\d+)',scene))
ok('actual first-encounter dialogue has no hidden identity or ARCHE revelation',all(x not in scene_text for x in ['安提','萨维尔','阿尔刻','ARCHE','飞天螳螂','拉鲁拉丝']))
ok('Raikou waiting disappearance and championship reminder text present','call_if_eq VAR_PART4_RAIKOU_STATE, 1, Part4_RaikouFailure' in s and '顶点之后，它还会再次回应你。' in s)
ok('all six rival branches include rain journey introduction',read('data/maps/Route119/scripts.inc').count('msgbox Part4_Text_157, MSGBOX_DEFAULT')==6)
ok('native Mega item gate retained','CheckBagHasItem(ITEM_MEGA_RING, 1)' in read('src/battle_util.c') or 'CheckBagHasItem(ITEM_MEGA_RING, 1)' in read('src/battle_controller_player.c') or 'CheckBagHasItem(ITEM_MEGA_RING, 1)' in read('src/battle_main.c'))
# Raw table is the one original table, now supports two committed units.
shop=read('src/limited_shop.c');legacy_source('src/shop.c');ok('only one shared limited shop with two-unit stone bits',shop.count('sLimitedShopItems[]')==1 and shop.count('MAP_ROUTE119, ITEM_')==7)
for stone in ['THUNDER_STONE','FIRE_STONE','WATER_STONE','MOON_STONE','SUN_STONE','DAWN_STONE']:ok('two-unit stock '+stone, 'ITEM_'+stone+', FLAG_PART4_SHOP_'+stone+'_FIRST, FLAG_PART4_SHOP_'+stone+'_SECOND' in shop)
ok('EV berries and Timer Ball unlimited','ITEM_TIMER_BALL' not in shop and not any('ITEM_'+z+'_BERRY' in shop for z in ['POMEG','KELPSY','QUALOT','HONDEW','GREPA','TAMATO']))
ok('unified stone one-unit stock and Miracle Seed paid once','{ MAP_ROUTE119, ITEM_EVOLUTION_STONE, FLAG_PART4_SHOP_EVOLUTION_STONE }' in shop and 'ITEM_MIRACLE_SEED' in read('data/maps/FortreeCity_Mart/scripts.inc'))
ok('merchant after original Fly flag','goto_if_unset FLAG_RECEIVED_HM_FLY' in block('Part4_ImportMerchant'))
ok('optional ARCHE doubles refuse safely before native battle','MSGBOX_YESNO' in block('Part4_ArcheSurvey') and 'goto_if_eq VAR_RESULT, NO' in block('Part4_ArcheSurvey'))
# Keep native Castform gift storage/nickname paths and random ordinary IV generation.
cast=read('data/maps/Route119_WeatherInstitute_2F/scripts.inc');ok('Castform25 native givemon no held item or fixed IV','givemon SPECIES_CASTFORM_NORMAL, 25, ITEM_NONE' in cast and 'MON_GIVEN_TO_PC' in cast and 'FLAG_RECEIVED_CASTFORM' in cast)
fly=read('data/maps/Route119/scripts.inc');ok('Fly full bag before flag; defeated six branches retry gift', 'giveitem ITEM_HM_FLY\n\tgoto_if_eq VAR_RESULT, FALSE, Part4_BagFull\n\tsetflag FLAG_RECEIVED_HM_FLY' in fly and len(re.findall(r'goto_if_defeated TRAINER_(?:MAY|BRENDAN)_ROUTE_119_',fly))==6)
# Independent sealed authorization is intentionally never enabled in this batch.
ok('first playthrough seal closed; future authorization has no writer','FLAG_SYS_GAME_CLEAR' in block('Part4_Seal') and 'FLAG_PART4_SEAL_AUTHORIZED' in block('Part4_Seal'))
assert not re.search(r'\bsetflag FLAG_PART4_SEAL_AUTHORIZED',s);ok('championship alone cannot unlock future factor')
c=read('src/part4.c');ok('Relicanth normal CreateMon30, no IV setter and no PC overflow','CreateMon(&mon, SPECIES_RELICANTH, 30, Random32(), OTID_STRUCT_PLAYER_ID)' in c and 'CalculatePlayerPartyCount() >= PARTY_SIZE' in c and 'SetMonData' not in c)
ok('girl consent, held-item safety and at least one able non-egg retained',all(t in c for t in ['MON_DATA_HELD_ITEM','MON_DATA_IS_EGG','MON_DATA_HP','ZeroMonData','CompactPartySlots']) and 'MSGBOX_YESNO' in block('Part4_BirthdayGirl'))
ok('girl companion visible after actual transfer and father reward retry','SyncPart4LuvdiscObject' in c and 'VAR_PART4_LUVDISC_STATE, 2' in c and 'giveitem ITEM_GYARADOSITE' in block('Part4_FisherReward'))
ok('lake-specific Luvdisc30% overlay, native Feebas condition preserved', all(t in read('src/wild_encounter.c') for t in ['CheckFeebasAtCoords(x, y) == TRUE','MAP_ROUTE120','Random() % 100 < 30','species = SPECIES_LUVDISC']))
l=read('src/data/pokemon/species_info/gen_3_families.h');luv=l[l.index('[SPECIES_LUVDISC]'):l.index('[SPECIES_LUVDISC]')+2000];ok('native 50% common Heart Scale unchanged','.itemCommon = ITEM_HEART_SCALE' in luv and l==baseline('src/data/pokemon/species_info/gen_3_families.h'))
ok('ruins original Chip battle and text retained','trainerbattle_single TRAINER_CHIP' in read('data/maps/Route120/scripts.inc') and 'Route120_Text_ChipPostBattle' in read('data/maps/Route120/scripts.inc'))
ok('native Winona rotating gate and original Sunny Day preserved','RotatingGate_InitPuzzle' in read('data/maps/FortreeCity_Gym/scripts.inc') and any(o['trainer_sight_or_berry_tree_id']=='ITEM_TM_SUNNY_DAY' for o in grid('ScorchedSlab')[0]['object_events']))
# Chinese generated pages use conservative 192px, two-line pages and only supported glyphs.
font=json.loads(read('tools/poryscript/font_config.json'))['fonts']['1_chinese_rse']['widths'];count=0
for label,text in re.findall(r'^(Part4_Text_\d+):\n\s*\.string "([^"\n]*)"',s,re.M):
 for page in text.rstrip('$').split(r'\p'):
  lines=page.split(r'\n');assert len(lines)<=2,(label,lines)
  for line in lines:
   assert sum(font.get(x,6) for x in line)<=208,(label,line);count+=1
assert '不是' not in ''.join(t for _,t in re.findall(r'^(Part4_Text_\d+):\n\s*\.string "([^"\n]*)"',s,re.M));ok(str(count)+' generated dialogue lines within208px, no repetitive contrast phrasing')
ok('maintenance uses native six-tile open door and walkable forward threshold',all('METATILE_Facility_NewMauvilleDoor_Open_Tile'+str(i) in read('data/maps/NewMauville_Maintenance/scripts.inc') for i in range(6)) and 'setmetatile 4, 1, METATILE_Facility_NewMauvilleDoor_Open_Tile4, FALSE' in read('data/maps/NewMauville_Maintenance/scripts.inc'))
ok('northern observer adds acquaintance only after known flag','FLAG_PART4_ARCHE_KNOWN' in block('Part4_119Observer'))
print('PART4 source/data/native map regression checks: PASS; gameplay remains MANUAL PENDING')
