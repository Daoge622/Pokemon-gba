#!/usr/bin/env python3
"""PART3 Strength gate/new cave/native C Entei state checks. No ROM or GUI execution."""
from pathlib import Path
from collections import deque
import json,re,struct,subprocess,tempfile
r=Path(__file__).resolve().parents[2];m=json.loads((r/'docs/project/part3-core-manifest.json').read_text());base=m['baseline']
def read(f):return (r/f).read_text()
def old(f):return subprocess.check_output(['git','show',base+':'+f],cwd=r,text=True)
def flood(g,p):
 seen={p};q=deque(seen)
 while q:
  x,y=q.popleft()
  for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
   if p in g and p not in seen:seen.add(p);q.append(p)
 return seen
layouts={x['id']:x for x in json.loads(read('data/layouts/layouts.json'))['layouts']}
def grid(folder):
 v=json.loads(read(f'data/maps/{folder}/map.json'));l=layouts[v['layout']];w,h=l['width'],l['height'];raw=(r/l['blockdata_filepath']).read_bytes();assert len(raw)==2*w*h;cells=struct.unpack('<'+'H'*(w*h),raw);g={(x,y) for y in range(h) for x in range(w) if (cells[y*w+x]>>10)&3==0 and cells[y*w+x]>>12 in (0,3)};return v,l,cells,g
v,l,c,g=grid('FieryPath');p=json.loads(old('data/maps/FieryPath/map.json'));before=struct.unpack('<'+'H'*len(c),subprocess.check_output(['git','show',base+':'+l['blockdata_filepath']],cwd=r));diff=[i for i,(a,b) in enumerate(zip(before,c)) if a!=b];assert diff==[2*l['width']+8] and before[diff[0]]==m['fiery_entrance']['old'] and c[diff[0]]==0x3309
assert v['object_events'][:len(p['object_events'])]==p['object_events'];assert v['warp_events'][:2]==p['warp_events'];assert v['coord_events']==p['coord_events']
assert v['warp_events'][2]=={'x':8,'y':2,'elevation':3,'dest_map':'MAP_SCORCHED_GROTTO','dest_warp_id':'0'}
rocks={(o['x'],o['y']) for o in v['object_events'] if o['graphics_id']=='OBJ_EVENT_GFX_PUSHABLE_BOULDER'};main=flood(g-rocks,(26,36));assert (26,4) in main and (27,22) in main and all(x not in main for x in [(8,2),(8,33),(6,31)])
assert (10,15) in rocks and next(o for o in v['object_events'] if (o['x'],o['y'])==(10,15))['script']=='EventScript_StrengthBoulder'
# Prove one legal native pushing route, rather than merely deleting every boulder.
player=(26,36)
def push(pos,delta,times=1):
 global player
 for _ in range(times):
  reachable=flood(g-rocks,player);behind=pos[0]-delta[0],pos[1]-delta[1];to=pos[0]+delta[0],pos[1]+delta[1]
  assert pos in rocks and behind in reachable and to in g-rocks,(pos,delta,'illegal push')
  rocks.remove(pos);rocks.add(to);player=pos;pos=to
 return pos
push((17,15),(-1,0),6);push((10,15),(0,-1));push((11,15),(1,0),6);push((8,11),(-1,0),3)
assert (8,2) in flood(g-rocks,player),'new cave reachable after legal Strength puzzle'
push((3,12),(0,1),10);push((3,22),(1,0),3);push((6,23),(1,0));push((5,24),(0,-1))
after=flood(g-rocks,player);assert (8,33) in after and (6,31) in after
moves=read('src/field_move.c');strength=re.search(r'\[FIELD_MOVE_STRENGTH\].*?\n    },',moves,re.S).group();assert '.unlockType = BADGE_UNLOCK' in strength and 'FLAG_TO_BADGE(FLAG_BADGE04_GET)' in strength
assert 'checkfieldmove FIELD_MOVE_STRENGTH, TRUE' in read('data/scripts/field_move_scripts.inc')
print('Fiery Path: one native entrance tile changed; early Fire Stone accessible; cave/Charcoal/TM gated; legal Strength push sequence reaches both branches: PASS')
# Same native ladder tile as both existing Fiery entrances; warps fire on walking, not map arrival.
a=(r/'data/tilesets/secondary/lavaridge/metatile_attributes.bin').read_bytes();assert struct.unpack_from('<H',a,2*(0x309-0x200))[0]&0xff==0x65
assert 'MetatileBehavior_IsLadder(metatileBehavior)' in read('src/field_control_avatar.c')
new,nl,nc,ng=grid('ScorchedGrotto');assert (nl['width'],nl['height'])==(15,19) and nl['primary_tileset']=='gTileset_General' and nl['secondary_tileset']=='gTileset_Lavaridge'
assert new['warp_events']==[{'x':7,'y':17,'elevation':3,'dest_map':'MAP_FIERY_PATH','dest_warp_id':'2'}]
assert nc[17*15+7]==0x3309 and (7,16) in ng and (7,5) in flood(ng-{(7,4)},(7,17))
# Arrival is a nonanimated ladder: it stays on the warp tile until the next player step.
screen=read('src/field_screen_effect.c');assert 'func = Task_ExitNonDoor' in screen
assert new['connections'] is None and not new['coord_events'] and len(new['object_events'])==1
assert new['object_events'][0]['graphics_id']=='OBJ_EVENT_GFX_ENTEI' and (r/'graphics/pokemon/entei/overworld.png').exists()
for mid in set(z&0x3ff for z in nc):
 folder='primary/general' if mid<0x200 else 'secondary/lavaridge';local=mid if mid<0x200 else mid-0x200;attrs=(r/f'data/tilesets/{folder}/metatile_attributes.bin').read_bytes();tiles=(r/f'data/tilesets/{folder}/metatiles.bin').read_bytes()
 assert local*2+2<=len(attrs) and local*16+16<=len(tiles)
 assert all((z&0x3ff)<1024 and (z>>12)<16 for z in struct.unpack_from('<8H',tiles,local*16))
assert all((x,y) not in ng for x in range(15) for y in [0,18]);assert all((x,y) not in ng for y in range(19) for x in [0,14])
groups=json.loads(read('data/maps/map_groups.json'));oldgroups=json.loads(old('data/maps/map_groups.json'))
for name,oldlist in oldgroups.items():
 if isinstance(oldlist,list):assert groups[name][:len(oldlist)]==oldlist,(name,'map IDs shifted')
assert sum(group.count('ScorchedGrotto') for group in groups.values() if isinstance(group,list))==1
print('New 15x19 volcanic cave: reciprocal native ladder warps, approach/escape, object capacity, metatile/palette bounds and appended map IDs: PASS')
# Check the actual assembled sequence: Begin is committed before the native battle can white out.
s=read('data/maps/ScorchedGrotto/scripts.inc');battle=s[s.index('Part3_Entei::'):s.index('Part3_EnteiGone::')];assert 'seteventmon SPECIES_ENTEI, PART3_ENTEI_LEVEL' in battle
assert battle.index('special BeginPart3EnteiBattle')<battle.index('special BattleSetup_StartLegendaryBattle')<battle.index('special FinishPart3EnteiBattle')
assert 'waitstate' not in battle,'native legendary special already pauses the script'
assert 'setvar VAR_TEMP_1, 1' in battle and 'msgbox Part3_EnteiFailureText' in battle
assert 'goto_if_ne VAR_PART3_ENTEI_STATE, PART3_ENTEI_WAITING, Part3_GrottoEnd' in s and 'special SyncPart3EnteiObject' in s
for t in ['炎帝的身影消失在洞窟深处……','空气中仍残留着炽热的气息。','也许等你站上丰缘训练家的顶点','之后，它还会再次回应你。']:assert t in s
hall=read('data/scripts/hall_of_fame.inc');assert hall.count('special ResetPart3EnteiAfterHallOfFame')==1 and hall.index('special ResetPart3EnteiAfterHallOfFame')<hall.index('setflag FLAG_IS_CHAMPION')
assert read('data/maps/EverGrandeCity_HallOfFame/scripts.inc')==old('data/maps/EverGrandeCity_HallOfFame/scripts.inc')
print('Entei Lv40: native encounter sequence, no extra wait, whiteout-safe prebattle waiting, immediate/deferred hint, one League hook per championship: PASS')
# Compile the real src/part3.c against narrow host stubs; exercise every state/outcome and lead-type branch.
def constant(path,name):return re.search(r'^#define '+name+r'\s+([^ \t\n]+)',read(path),re.M).group(1)
with tempfile.TemporaryDirectory(prefix='part3-core-') as td:
 d=Path(td);(d/'constants').mkdir();globalh='''#ifndef CORE_STUB_H
#define CORE_STUB_H
#include <stdint.h>
#include <stdbool.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32;
enum Species { SPECIES_NONE=0, SPECIES_TEST_FIRE=1, SPECIES_TEST_ICE=2, SPECIES_TEST_OTHER=3 };
struct Pokemon { u32 species, egg; };
#define B_TRAINER_PLAYER 0
#define MON_DATA_SPECIES 0
#define MON_DATA_IS_EGG 1
#define TYPE_FIRE 11
#define TYPE_ICE 16
extern struct Pokemon gParties[4][6]; extern u8 gBattleOutcome; extern u16 gSpecialVar_Result;
u16 VarGet(u16); void VarSet(u16,u16); void FlagSet(u16);void FlagClear(u16);u32 GetMonData(struct Pokemon *,u16);u8 GetSpeciesType(enum Species,u8);
#endif
''';(d/'global.h').write_text(globalh)
 for f in ['battle.h','event_data.h','pokemon.h']:(d/f).write_text('#include "global.h"\n')
 (d/'part3.h').write_text(read('include/part3.h'));(d/'constants/part3.h').write_text(read('include/constants/part3.h'))
 for f,name in [('flags.h','FLAG_PART3_HIDE_ENTEI'),('vars.h','VAR_PART3_ENTEI_STATE'),('battle.h','B_OUTCOME_CAUGHT')]:
  source='include/constants/'+f;(d/'constants'/f).write_text(f'#define {name} {constant(source,name)}\n')
 (d/'part3.c').write_text(read('src/part3.c'))
 (d/'main.c').write_text('''#include <assert.h>
#include "global.h"
#include "part3.h"
#include "constants/part3.h"
#include "constants/vars.h"
#include "constants/flags.h"
#include "constants/battle.h"
struct Pokemon gParties[4][6];u8 gBattleOutcome;u16 gSpecialVar_Result;
static u16 state;static bool hidden;
u16 VarGet(u16 id){assert(id==VAR_PART3_ENTEI_STATE);return state;}
void VarSet(u16 id,u16 v){assert(id==VAR_PART3_ENTEI_STATE);state=v;}
void FlagSet(u16 id){assert(id==FLAG_PART3_HIDE_ENTEI);hidden=true;}
void FlagClear(u16 id){assert(id==FLAG_PART3_HIDE_ENTEI);hidden=false;}
u32 GetMonData(struct Pokemon *m,u16 field){return field==MON_DATA_IS_EGG?m->egg:m->species;}
u8 GetSpeciesType(enum Species s,u8 n){return s==SPECIES_TEST_FIRE?TYPE_FIRE:s==SPECIES_TEST_ICE?TYPE_ICE:0;}
int main(void){
for(unsigned s=0;s<4;s++)for(unsigned o=0;o<10;o++)assert(Part3EnteiAfterBattle(s,o)==((s==PART3_ENTEI_CAUGHT||o==B_OUTCOME_CAUGHT)?PART3_ENTEI_CAUGHT:PART3_ENTEI_WAITING));
for(unsigned s=0;s<4;s++){state=s;SyncPart3EnteiObject();assert(hidden==(s==PART3_ENTEI_WAITING||s==PART3_ENTEI_CAUGHT));ResetPart3EnteiAfterHallOfFame();assert(state==(s==PART3_ENTEI_WAITING?PART3_ENTEI_CHAMPION_RETURN:s));}
state=PART3_ENTEI_READY;BeginPart3EnteiBattle();assert(state==PART3_ENTEI_WAITING&&hidden);/* Simulated whiteout: Finish is not resumed. */SyncPart3EnteiObject();assert(state==PART3_ENTEI_WAITING&&hidden);
for(unsigned o=0;o<10;o++){state=PART3_ENTEI_READY;BeginPart3EnteiBattle();gBattleOutcome=o;FinishPart3EnteiBattle();assert(hidden&&state==(o==B_OUTCOME_CAUGHT?PART3_ENTEI_CAUGHT:PART3_ENTEI_WAITING));SyncPart3EnteiObject();assert(hidden);}
state=PART3_ENTEI_WAITING;for(unsigned i=0;i<10;i++){ResetPart3EnteiAfterHallOfFame();assert(state==PART3_ENTEI_CHAMPION_RETURN&&!hidden);BeginPart3EnteiBattle();gBattleOutcome=1;FinishPart3EnteiBattle();assert(state==PART3_ENTEI_WAITING&&hidden);}
state=PART3_ENTEI_CAUGHT;for(unsigned i=0;i<10;i++){ResetPart3EnteiAfterHallOfFame();SyncPart3EnteiObject();assert(state==PART3_ENTEI_CAUGHT&&hidden);}
for(unsigned s=0;s<4;s++){gParties[0][0].species=s;gParties[0][0].egg=0;GetPart3LeadHotSpringType();assert(gSpecialVar_Result==(s==1?1:s==2?2:0));gParties[0][0].egg=1;GetPart3LeadHotSpringType();assert(gSpecialVar_Result==0);}
return 0;}
''')
 subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Wno-unused-parameter','-Werror','-I',str(d),str(d/'part3.c'),str(d/'main.c'),'-o',str(d/'check')],check=True);subprocess.run([str(d/'check')],check=True)
print('Actual C: 40 state/outcome pairs, capture permanently hidden, whiteout interruption, map reload no respawn, repeated League retry, egg/Fire/Ice/empty lead: PASS')
