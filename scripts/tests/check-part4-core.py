#!/usr/bin/env python3
"""Compiles actual PART4 C helpers on host with deterministic field/party adapters; no ROM."""
from pathlib import Path
import re,subprocess,tempfile
r=Path(__file__).resolve().parents[2]
def read(f):return (r/f).read_text()
def function(s,name):
 m=re.search(r'(?m)^u16 '+name+r'\([^;]*?\)\n\{',s);assert m;b=s.index('{',m.start());depth=1;i=b+1
 while depth:depth+=(s[i]=='{')-(s[i]=='}');i+=1
 return s[m.start():i]
with tempfile.TemporaryDirectory() as path:
 d=Path(path);(d/'constants').mkdir()
 (d/'global.h').write_text('''#ifndef STUB_GLOBAL
#define STUB_GLOBAL
#include <stdint.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef unsigned bool32;
#define TRUE 1
#define FALSE 0
#define PARTY_SIZE 6
#define B_TRAINER_PLAYER 0
#define SPECIES_NONE 0
#define SPECIES_RELICANTH 369
#define SPECIES_LUVDISC 370
#define SPECIES_CASTFORM_NORMAL 351
#define SPECIES_ZIGZAGOON 263
#define ITEM_NONE 0
#define ITEM_HEART_SCALE 93
#define OTID_STRUCT_PLAYER_ID 0
#define MON_DATA_SPECIES 0
#define MON_DATA_IS_EGG 1
#define MON_DATA_HELD_ITEM 2
#define MON_DATA_HP 3
#define MON_GIVEN_TO_PARTY 0
struct Pokemon { u16 fields[4]; u32 personality; };
extern struct Pokemon gParties[1][PARTY_SIZE];
extern u16 gSpecialVar_Result;
extern u8 gBattleOutcome;
u8 FlagGet(u16); void FlagSet(u16); void FlagClear(u16); u16 VarGet(u16); void VarSet(u16,u16);
u16 GetMonData(struct Pokemon *,int); void ZeroMonData(struct Pokemon *); u8 CalculatePlayerPartyCount(void);
void CreateMon(struct Pokemon *,u16,u8,u32,u8); u8 GiveCapturedMonToPlayer(struct Pokemon *);
void HandleSetPokedexFlagFromMon(struct Pokemon *,u8); void CompactPartySlots(void); u8 GetCurrentWeather(void); u32 Random32(void);
#endif
''')
 for f in ['battle.h','event_data.h','pokemon.h','pokemon_storage_system.h','random.h','field_weather.h']:(d/f).write_text('#include "global.h"\n')
 (d/'pokedex.h').write_text('#define FLAG_SET_SEEN 1\n#define FLAG_SET_CAUGHT 2\n')
 (d/'part3.h').write_text('u16 Part3EnteiAfterBattle(u16,u8);\nu16 Part3EnteiAfterHallOfFame(u16);\n')
 for f,prefix in [('flags.h','FLAG'),('vars.h','VAR')]:
  defs='\n'.join(x for x in read('include/constants/'+f).splitlines() if re.match(r'#define '+prefix+r'_PART4_',x) or x.startswith('#define FLAG_SYS_POKEMON_GET '));(d/'constants'/f).write_text(('#define SYSTEM_FLAGS 0x860\n' if f=='flags.h' else '')+defs+'\n')
 for f in ['part3.h','part4.h','weather.h']:(d/'constants'/f).write_text(read('include/constants/'+f))
 caught=re.search(r'^#define B_OUTCOME_CAUGHT\s+\d+[^\n]*',read('include/constants/battle.h'),re.M)[0]
 (d/'state.c').write_text('#include "global.h"\n#include "constants/part3.h"\n'+caught+'\n'+function(read('src/part3.c'),'Part3EnteiAfterBattle')+'\n'+function(read('src/part3.c'),'Part3EnteiAfterHallOfFame'))
 (d/'main.c').write_text('''#include "global.h"
#include "part4.h"
#include "constants/flags.h"
#include "constants/vars.h"
#include "constants/weather.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
struct Pokemon gParties[1][6];u16 gSpecialVar_Result;u8 gBattleOutcome;
static u8 flags[4096],weather,delivery;static u16 vars[65536];static unsigned creates,dex,seed;
u8 FlagGet(u16 f){return flags[f];}void FlagSet(u16 f){flags[f]=1;}void FlagClear(u16 f){flags[f]=0;}
u16 VarGet(u16 v){return vars[v];}void VarSet(u16 v,u16 n){vars[v]=n;}
u16 GetMonData(struct Pokemon *p,int field){return p->fields[field];}
void ZeroMonData(struct Pokemon *p){memset(p,0,sizeof(*p));}
u8 CalculatePlayerPartyCount(void){unsigned n=0;for(unsigned i=0;i<6;i++)n+=gParties[0][i].fields[0]!=0;return n;}
void CompactPartySlots(void){unsigned j=0;for(unsigned i=0;i<6;i++)if(gParties[0][i].fields[0])gParties[0][j++]=gParties[0][i];while(j<6)ZeroMonData(&gParties[0][j++]);}
u32 Random32(void){return ++seed;}
void CreateMon(struct Pokemon *p,u16 species,u8 level,u32 personality,u8 ot){assert(species==369 && level==30 && ot==0);ZeroMonData(p);p->fields[0]=species;p->fields[3]=50;p->personality=personality;creates++;}
u8 GiveCapturedMonToPlayer(struct Pokemon *p){if(delivery==0)gParties[0][CalculatePlayerPartyCount()]=*p;return delivery;}
void HandleSetPokedexFlagFromMon(struct Pokemon *p,u8 f){assert(p->fields[0]==369);assert(f==1||f==2);dex++;}
u8 GetCurrentWeather(void){return weather;}
void reset(void){memset(flags,0,sizeof(flags));memset(vars,0,sizeof(vars));memset(gParties,0,sizeof(gParties));creates=0;dex=0;delivery=0;}
void mon(unsigned i,unsigned species,unsigned hp,unsigned egg,unsigned held){gParties[0][i].fields[0]=species;gParties[0][i].fields[1]=egg;gParties[0][i].fields[2]=held;gParties[0][i].fields[3]=hp;}
int main(void){
reset();for(unsigned state=0;state<4;state++)for(unsigned outcome=0;outcome<10;outcome++){VarSet(VAR_PART4_RAIKOU_STATE,state);gBattleOutcome=outcome;FinishPart4RaikouBattle();assert(VarGet(VAR_PART4_RAIKOU_STATE)==((state==2||outcome==7)?2:1));assert(FlagGet(FLAG_PART4_HIDE_RAIKOU));}
for(unsigned state=0;state<4;state++){VarSet(VAR_PART4_RAIKOU_STATE,state);ResetPart4RaikouAfterHallOfFame();assert(VarGet(VAR_PART4_RAIKOU_STATE)==(state==1?3:state));assert(FlagGet(FLAG_PART4_HIDE_RAIKOU)==(state==2));}
VarSet(VAR_PART4_RAIKOU_STATE,0);BeginPart4RaikouBattle();assert(VarGet(VAR_PART4_RAIKOU_STATE)==1);SyncPart4RaikouObject();assert(FlagGet(FLAG_PART4_HIDE_RAIKOU));ResetPart4RaikouAfterHallOfFame();assert(VarGet(VAR_PART4_RAIKOU_STATE)==3&&!FlagGet(FLAG_PART4_HIDE_RAIKOU));
for(unsigned i=0;i<12;i++){BeginPart4RaikouBattle();gBattleOutcome=1;FinishPart4RaikouBattle();ResetPart4RaikouAfterHallOfFame();assert(VarGet(VAR_PART4_RAIKOU_STATE)==3);}VarSet(VAR_PART4_RAIKOU_STATE,2);for(unsigned i=0;i<12;i++){ResetPart4RaikouAfterHallOfFame();assert(VarGet(VAR_PART4_RAIKOU_STATE)==2&&FlagGet(FLAG_PART4_HIDE_RAIKOU));}
puts("Actual C Raikou: 40 state/outcome pairs; blackout pending; repeated championship retry; caught never returns: PASS");
for(unsigned stage=0;stage<5;stage++){VarSet(VAR_PART4_MEGA_STAGE,stage);SyncPart4MegaObjects();assert(FlagGet(FLAG_PART4_HIDE_AQUA_A)==(stage>=1));assert(FlagGet(FLAG_PART4_HIDE_AQUA_B)==(stage>=2));assert(FlagGet(FLAG_PART4_HIDE_AQUA_EXTRA)==(stage!=2));assert(FlagGet(FLAG_PART4_HIDE_ANTI)==(stage<2||stage>=4));}
puts("Actual C Mega actors: all five persistent stages, gift-retry stage3, cleanup stage4: PASS");
reset();GivePart4Relicanth();assert(!creates&&!gSpecialVar_Result);FlagSet(FLAG_SYS_POKEMON_GET);for(unsigned i=0;i<6;i++)mon(i,263,10,0,0);GivePart4Relicanth();assert(!creates&&!FlagGet(FLAG_PART4_RELICANTH_RECEIVED));ZeroMonData(&gParties[0][5]);delivery=2;GivePart4Relicanth();assert(creates==1&&!FlagGet(FLAG_PART4_RELICANTH_RECEIVED));delivery=0;GivePart4Relicanth();assert(creates==2&&FlagGet(FLAG_PART4_RELICANTH_RECEIVED)&&gSpecialVar_Result&&dex==2);GivePart4Relicanth();assert(creates==2&&!gSpecialVar_Result);
puts("Actual C Relicanth: pre-starter/full party/delivery failure/retry/success/repeat; normal personality passed and dex updated: PASS");
reset();GivePart4LuvdiscToGirl();assert(gSpecialVar_Result==0);mon(0,370,30,0,0);GivePart4LuvdiscToGirl();assert(gSpecialVar_Result==2&&CalculatePlayerPartyCount()==1);mon(1,263,0,0,0);GivePart4LuvdiscToGirl();assert(gSpecialVar_Result==2);mon(1,263,20,1,0);GivePart4LuvdiscToGirl();assert(gSpecialVar_Result==2);mon(1,263,20,0,0);mon(0,370,30,0,93);GivePart4LuvdiscToGirl();assert(gSpecialVar_Result==3&&GetMonData(&gParties[0][0],2)==93);mon(0,370,30,0,0);GivePart4LuvdiscToGirl();assert(gSpecialVar_Result==1&&CalculatePlayerPartyCount()==1&&gParties[0][0].fields[0]==263&&VarGet(VAR_PART4_LUVDISC_STATE)==2&&!FlagGet(FLAG_PART4_HIDE_LUVDISC));GivePart4LuvdiscToGirl();assert(gSpecialVar_Result==0&&CalculatePlayerPartyCount()==1);
reset();mon(0,370,0,0,0);mon(1,370,30,0,93);mon(2,263,30,0,0);GivePart4LuvdiscToGirl();assert(gSpecialVar_Result==1&&CalculatePlayerPartyCount()==2&&gParties[0][0].fields[2]==93);
reset();mon(0,370,30,1,0);mon(1,263,30,0,0);GivePart4LuvdiscToGirl();assert(!gSpecialVar_Result&&CalculatePlayerPartyCount()==2);
for(unsigned state=0;state<4;state++){VarSet(VAR_PART4_LUVDISC_STATE,state);SyncPart4LuvdiscObject();assert(FlagGet(FLAG_PART4_HIDE_LUVDISC)==(state<2));}
puts("Actual C Luvdisc: no mon/last mon/fainted or egg companion/held item/multiple candidates/success/compaction/repeat visibility: PASS");
for(weather=0;weather<WEATHER_COUNT;weather++){GetPart4RainState();assert(gSpecialVar_Result==(weather==WEATHER_RAIN||weather==WEATHER_DOWNPOUR||weather==WEATHER_RAIN_THUNDERSTORM));}
puts("Actual C outdoor weather classification: PASS");
}
''')
 subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-I',str(d),'-I',str(r/'include'),str(r/'src/part4.c'),str(d/'state.c'),str(d/'main.c'),'-o',str(d/'check')],check=True)
 subprocess.run([str(d/'check')],check=True)
