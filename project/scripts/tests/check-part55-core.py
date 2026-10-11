#!/usr/bin/env python3
"""Host tests compile actual C helpers and native ownership paths; no ROM/emulator."""
from pathlib import Path
import re,subprocess,tempfile
R=Path(__file__).resolve().parents[2]
def read(f):return (R/f).read_text()
def fn(s,name):
 m=re.search(r'(?m)^[\w *]+\b'+name+r'\([^;]*?\)\n\{',s);assert m,name
 b=s.index('{',m.start());i=b+1;depth=1
 while depth:depth+=(s[i]=='{')-(s[i]=='}');i+=1
 return s[m.start():i]
base='''#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
typedef uint8_t u8;typedef uint16_t u16;typedef uint32_t u32;typedef unsigned bool8;typedef unsigned bool32;
#define TRUE 1
#define FALSE 0
#define TESTING 0
#define PARTY_SIZE 6
#define MAX_TRAINERS_COUNT 864
#define TRAINERS_COUNT 864
#define PARTNER_COUNT 8
#define PARTNER_NONE 0
#define TRAINER_NONE 0
#define TRAINER_PARTNER(n) (864+(n))
#define TRAINER_FLAGS_START 0x500
#define TRAINER_LINK_OPPONENT 65535
#define B_MULTI_HALF_TEAMS 0
#define assertf(c,...) if(!(c))
#define B_TRAINER_PLAYER 0
#define B_TRAINER_OPPONENT_A 1
#define B_OUTCOME_CAUGHT 7
#define MON_GIVEN_TO_PARTY 0
#define FLAG_SET_SEEN 1
#define FLAG_SET_CAUGHT 2
#define FLAG_GET_SEEN 3
#define OTID_STRUCT_PLAYER_ID 0
#define READ_OTID_FROM_SAVE 0x12345678
#define BATTLE_TYPE_DOUBLE 1
#define BATTLE_TYPE_MULTI 2
#define BATTLE_TYPE_TWO_OPPONENTS 4
#define BATTLE_TYPE_TRAINER 8
#define BATTLE_TYPE_INGAME_PARTNER 16
#define BATTLE_TYPE_TOWER_LINK_MULTI 32
#define MULTI_TEAM_SIZE_HALF 1
#define B_POSITION_PLAYER_LEFT 0
#define B_POSITION_PLAYER_RIGHT 2
#define ITEM_MEGA_RING 99
#define STATE_SKY_DROP_TARGET 3
#define FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM 1
#define FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE 2
enum Species {SPECIES_NONE,SPECIES_AXEW,SPECIES_FRAXURE,SPECIES_HAXORUS,SPECIES_PORYGON,SPECIES_KANGASKHAN,SPECIES_CHANSEY,SPECIES_TAUROS,SPECIES_BEEDRILL};
enum Item {ITEM_NONE,ITEM_RED_SHARD,ITEM_YELLOW_SHARD,ITEM_BLUE_SHARD,ITEM_GREEN_SHARD};
enum BattlerId {B0,B1,B2,B3};enum Gimmick {GIMMICK_NONE,GIMMICK_MEGA,GIMMICK_DYNAMAX};
enum HoldEffect {HOLD_EFFECT_NONE,HOLD_EFFECT_Z_CRYSTAL};enum BattlerPosition {P0,P1,P2,P3};enum Ability {ABILITY_NONE};
enum DifficultyLevel {DIFFICULTY_NORMAL,DIFFICULTY_HARD};
enum {MON_DATA_PERSONALITY,MON_DATA_ATK_IV,MON_DATA_IS_SHINY,MON_DATA_SPECIES_OR_EGG,MON_DATA_OT_ID};
struct Pokemon {u32 fields[16];};struct Pokemon gParties[2][6];
struct Trainer {void *party;unsigned multiTeamSize;};struct Trainer gTrainers[2][864],gBattlePartners[2][8];
static bool8 gIsDebugBattle;static struct Trainer *GetDebugAiTrainer(void){return &gTrainers[0][0];}
static enum DifficultyLevel GetCurrentDifficultyLevel(void){return DIFFICULTY_NORMAL;}
static u8 flags[4096],gBattleOutcome;static u16 vars[65536],gSpecialVar_Result,gSpecialVar_0x8004,gSpecialVar_0x8005,gSpecialVar_0x8008,gNumSafariBalls;
static unsigned creates,dex,delivery,safari,nativeEnd,started,calc,setWrites;static void(*callback)(void);
static struct {void(*savedCallback)(void);}gMain;
static bool8 FlagGet(u16 f){assert(f<4096);return flags[f];}static void FlagSet(u16 f){assert(f<4096);flags[f]=1;}
static u16 VarGet(u16 v){return vars[v];}static void VarSet(u16 v,u16 n){vars[v]=n;}
static u32 GetMonData(struct Pokemon *m,unsigned f){return m->fields[f];}
static void SetMonData(struct Pokemon *m,unsigned f,const void *v){assert(f==MON_DATA_ATK_IV||f==MON_DATA_IS_SHINY);m->fields[f]=f==MON_DATA_ATK_IV?*(const u8*)v:*(const bool8*)v;setWrites++;}
static void CalculateMonStats(struct Pokemon *m){assert(m==&gParties[1][0]);calc++;}
static u8 CalculatePlayerPartyCount(void){u8 n=0;for(unsigned i=0;i<6;i++)n+=gParties[0][i].fields[MON_DATA_SPECIES_OR_EGG]!=0;return n;}
static u32 Random32(void){return 0xAABBCD12;}
static void CreateMon(struct Pokemon *m,enum Species s,u8 lv,u32 pid,u8 ot){assert(s==SPECIES_PORYGON&&lv==30&&ot==0);memset(m,0,sizeof(*m));m->fields[MON_DATA_PERSONALITY]=pid;m->fields[MON_DATA_SPECIES_OR_EGG]=s;creates++;}
static u8 GiveCapturedMonToPlayer(struct Pokemon *m){if(!delivery)gParties[0][CalculatePlayerPartyCount()]=*m;return delivery;}
static void HandleSetPokedexFlagFromMon(struct Pokemon *m,unsigned f){assert(m->fields[MON_DATA_SPECIES_OR_EGG]==SPECIES_PORYGON&&(f==1||f==2));dex++;}
static unsigned seen[20];static unsigned SpeciesToNationalPokedexNum(enum Species s){return s;}static unsigned GetSetPokedexFlag(unsigned s,unsigned f){assert(f==FLAG_GET_SEEN);return seen[s];}
static void CB2_ReturnToFieldContinueScriptPlayMapMusic(void){}static void nativeOther(void){}
static void CB2_EndSafariBattle(void){nativeEnd++;callback=nativeOther;}
static void SetMainCallback2(void(*cb)(void)){callback=cb;}
static bool8 GetSafariZoneFlag(void){return safari;}
static void CreateScriptedWildMon(enum Species s,u8 lv,enum Item item){assert(s==SPECIES_BEEDRILL&&lv==30&&item==ITEM_NONE);started++;}
static void BattleSetup_StartWildBattle(void){assert(safari);started++;}
static u32 gBattleTypeFlags;static struct{struct {u8 activated[4][3],toActivate,usableGimmick[4];}gimmick;}battleStruct,*gBattleStruct=&battleStruct;
static struct{unsigned species;struct{unsigned semiInvulnerable;}volatiles;}gBattleMons[4];
static unsigned bagRing,active[4],hold[4],megaSpecies[4];
static bool32 IsOnPlayerSide(enum BattlerId b){return (b&1)==0;}static bool32 IsDoubleBattle(void){return (gBattleTypeFlags&BATTLE_TYPE_DOUBLE)!=0;}
static enum BattlerId GetPartnerBattler(enum BattlerId b){return b^2;}static enum BattlerPosition GetBattlerPosition(enum BattlerId b){return (enum BattlerPosition)b;}
static enum HoldEffect GetBattlerHoldEffectIgnoreNegation(enum BattlerId b){return hold[b];}
static bool32 CheckBagHasItem(unsigned item,unsigned count){assert(item==ITEM_MEGA_RING&&count==1);return bagRing;}
static enum Gimmick GetActiveGimmick(enum BattlerId b){return active[b];}static enum Ability GetBattlerAbility(enum BattlerId b){(void)b;return ABILITY_NONE;}
static unsigned GetBattleFormChangeTargetSpecies(enum BattlerId b,unsigned method,enum Ability a){(void)a;return method==1?megaSpecies[b]:gBattleMons[b].species;}
static struct{u16 opponentA,opponentB;u8 *defeatTextA,*defeatTextB;}params;
#define TRAINER_BATTLE_PARAM params
static u16 gPartnerTrainerId;struct ScriptContext{unsigned i;u16 ids[3];};
static void InitTrainerBattleParameter(void){memset(&params,0,sizeof(params));}
static u16 ScriptReadHalfword(struct ScriptContext *c){return c->ids[c->i++];}static uintptr_t ScriptReadWord(struct ScriptContext *c){(void)c;return 0;}
'''
for f in ['include/constants/flags.h','include/constants/vars.h']:
 base+='\n'.join(re.findall(r'^#define (?:FLAG|VAR)_PART55_\w+\s+0x[0-9A-Fa-f]+',read(f),re.M))+'\n'
for i,name in enumerate(['ROOKIE','AQUA_OBSERVER_A','AQUA_OBSERVER_B','SAFARI_EXPERT','ADVANCED_TRAINER','PSYCHIC_RESEARCHER'],2):base+=f'#define TRAINER_PART55_{name} (864+{i})\n'
base+=fn(read('src/difficulty.c'),'GetBattlePartnerDifficultyLevel')+'\n'+fn(read('src/difficulty.c'),'GetTrainerDifficultyLevel')+'\n'
for name in ['IsPartnerTrainerId','SanitizeTrainerId','GetPartnerIdFromTrainerId','GetTrainerStructFromId']:base+=fn(read('include/data.h'),name)+'\n'
for f,names in [('src/battle_util.c',['IsPartnerMonFromSameTrainer']),('src/battle_gimmick.c',['HasTrainerUsedGimmick','SetGimmickAsActivated']),('src/battle_util.c',['CanMegaEvolve','AreMultiPartiesFullTeams']),('src/battle_setup.c',['SetMultiTrainerBattle'])]:
 for name in names:base+=fn(read(f),name)+'\n'
from part6_compat import source as _p6
base+=re.sub(r'^#include[^\n]*\n','',_p6('src/part55.c'),flags=re.M)
base+='''
static void reset(void){memset(flags,0,sizeof(flags));memset(vars,0,sizeof(vars));memset(gParties,0,sizeof(gParties));memset(&battleStruct,0,sizeof(battleStruct));creates=dex=delivery=0;}
int main(void){
reset();for(unsigned i=0;i<864;i++)assert(Part55_TrainerFlag(i)==0x500+i);
unsigned ext[]={FLAG_PART55_BATTLED_ROOKIE,FLAG_PART55_BATTLED_AQUA_OBSERVER_A,FLAG_PART55_BATTLED_AQUA_OBSERVER_B,FLAG_PART55_BATTLED_SAFARI_EXPERT,FLAG_PART55_BATTLED_ADVANCED_TRAINER,FLAG_PART55_BATTLED_PSYCHIC_RESEARCHER};
for(unsigned i=0;i<6;i++){assert(Part55_TrainerFlag(866+i)==ext[i]);gBattlePartners[0][i+2].multiTeamSize=1;assert(GetTrainerStructFromId(866+i)==&gBattlePartners[0][i+2]);}assert(!Part55_TrainerFlag(65535));
puts("Native trainer access: 864 old flags unchanged; six extension flags and ROM lookups PASS");
params.opponentA=868;params.opponentB=867;gBattleTypeFlags=BATTLE_TYPE_TRAINER;assert(!AreMultiPartiesFullTeams());
struct ScriptContext ctx={0,{867,868,2}};gBattleTypeFlags=0;SetMultiTrainerBattle(&ctx);assert(gBattleTypeFlags==31&&gPartnerTrainerId==866&&!AreMultiPartiesFullTeams());
puts("Actual multi setup: previous wild flags reset before Half team selection; partner IDs in bounds PASS");
reset();for(unsigned stage=0;stage<6;stage++){VarSet(VAR_PART55_PORYGON,stage);if(stage!=4){Part55_GivePorygon();assert(!creates&&!gSpecialVar_Result);}}
VarSet(VAR_PART55_PORYGON,4);for(unsigned i=0;i<6;i++)gParties[0][i].fields[MON_DATA_SPECIES_OR_EGG]=SPECIES_AXEW;
Part55_GivePorygon();assert(!creates&&VarGet(VAR_PART55_PORYGON)==4&&!gSpecialVar_Result);
memset(&gParties[0][5],0,sizeof(struct Pokemon));delivery=2;Part55_GivePorygon();assert(creates==1&&VarGet(VAR_PART55_PORYGON)==4&&!dex);
delivery=0;Part55_GivePorygon();assert(creates==2&&dex==2&&VarGet(VAR_PART55_PORYGON)==5&&gSpecialVar_Result);Part55_GivePorygon();assert(creates==2&&!gSpecialVar_Result);
puts("Actual Porygon: not ready/full party/delivery failure retain eligibility; success dex/repeat guard PASS");
reset();struct Pokemon *m=&gParties[1][0];for(unsigned seed=0;seed<32;seed++){for(unsigned j=0;j<16;j++)m->fields[j]=seed*100+j;struct Pokemon prior=*m;Part55_PrepareAxew();assert(m->fields[MON_DATA_ATK_IV]==31&&m->fields[MON_DATA_IS_SHINY]);for(unsigned j=0;j<16;j++)if(j!=MON_DATA_ATK_IV&&j!=MON_DATA_IS_SHINY)assert(m->fields[j]==prior.fields[j]);assert((VarGet(VAR_PART55_AXEW_PID_LO)|((u32)VarGet(VAR_PART55_AXEW_PID_HI)<<16))==prior.fields[MON_DATA_PERSONALITY]);}assert(calc==32&&setWrites==64);
for(unsigned o=0;o<10;o++){flags[FLAG_PART55_AXEW_CAUGHT]=0;gBattleOutcome=o;Part55_FinishAxew();assert(FlagGet(FLAG_PART55_AXEW_CAUGHT)==(o==7));}
FlagSet(FLAG_PART55_AXEW_CAUGHT);gParties[0][0]=*m;gParties[0][0].fields[MON_DATA_OT_ID]=READ_OTID_FROM_SAVE;for(unsigned s=SPECIES_AXEW;s<=SPECIES_HAXORUS;s++){gParties[0][0].fields[MON_DATA_SPECIES_OR_EGG]=s;Part55_CheckCapturedAxewParty();assert(gSpecialVar_Result);}gParties[0][0].fields[MON_DATA_PERSONALITY]++;Part55_CheckCapturedAxewParty();assert(!gSpecialVar_Result);
puts("Actual Axew: 32 random-field fixtures only Atk/shiny modified; ten outcomes; fixed PID/evolution/OT recognition PASS");
reset();for(unsigned mask=0;mask<8;mask++){seen[SPECIES_KANGASKHAN]=mask&1;seen[SPECIES_CHANSEY]=mask&2;seen[SPECIES_TAUROS]=mask&4;Part55_CheckSafariLargeSeen();assert(gSpecialVar_Result==(mask==7));}
puts("Actual Safari seen gate: all eight seen combinations; all three required PASS");
reset();for(unsigned type=1;type<=3;type++){gSpecialVar_0x8004=type;Part55_TakeSample();assert(gSpecialVar_Result==2);gSpecialVar_0x8004=type%3+1;Part55_DeliverSample();assert(gSpecialVar_Result==1&&VarGet(VAR_PART55_SAMPLE_CARRY)==type);gSpecialVar_0x8004=type;Part55_DeliverSample();assert(gSpecialVar_Result==2&&!VarGet(VAR_PART55_SAMPLE_CARRY));Part55_TakeSample();assert(!gSpecialVar_Result);}assert(VarGet(VAR_PART55_SAMPLE_BITS)==7);
for(unsigned c=1;c<=4;c++){gSpecialVar_0x8008=c;Part55_RecordShardTrade();Part55_RecordShardTrade();}assert(VarGet(VAR_PART55_SHARDS)==15);
puts("Actual sample delivery: wrong window keeps cargo; correct consumes once; all three bits; repeated shard colors idempotent PASS");
safari=0;Part55_StartSafariBeedrill();assert(!started);safari=1;Part55_StartSafariBeedrill();assert(started==2);gNumSafariBalls=8;gMain.savedCallback();assert(nativeEnd==1&&callback==CB2_ReturnToFieldContinueScriptPlayMapMusic);gNumSafariBalls=0;gMain.savedCallback();assert(nativeEnd==2&&callback==nativeOther);
puts("Actual Safari wrapper: native callback always runs; balls remaining resumes; last-ball native exit retained PASS");
for(unsigned i=0;i<4;i++){gBattleMons[i].species=1;megaSpecies[i]=2;}bagRing=1;
for(unsigned mask=0;mask<4;mask++){gBattleTypeFlags=BATTLE_TYPE_DOUBLE|((mask&1)?BATTLE_TYPE_MULTI:0)|((mask&2)?BATTLE_TYPE_TWO_OPPONENTS:0);for(unsigned b=0;b<4;b++){memset(&battleStruct,0,sizeof(battleStruct));assert(CanMegaEvolve(b));SetGimmickAsActivated(b,GIMMICK_MEGA);assert(!CanMegaEvolve(b));unsigned shared=(b&1)?!(mask&2):!(mask&1);assert(HasTrainerUsedGimmick(b^2,GIMMICK_MEGA)==shared);assert(CanMegaEvolve(b^2)==!shared);memset(&battleStruct,0,sizeof(battleStruct));battleStruct.gimmick.toActivate=1u<<(b^2);battleStruct.gimmick.usableGimmick[b^2]=GIMMICK_MEGA;assert(HasTrainerUsedGimmick(b,GIMMICK_MEGA)==shared);}}
memset(&battleStruct,0,sizeof(battleStruct));gBattleTypeFlags=0;assert(CanMegaEvolve(B0));SetGimmickAsActivated(B0,GIMMICK_MEGA);assert(!CanMegaEvolve(B0));
memset(&battleStruct,0,sizeof(battleStruct));gBattleTypeFlags=BATTLE_TYPE_DOUBLE|BATTLE_TYPE_MULTI|BATTLE_TYPE_TWO_OPPONENTS;SetGimmickAsActivated(B2,GIMMICK_MEGA);assert(CanMegaEvolve(B0));bagRing=0;memset(&battleStruct,0,sizeof(battleStruct));assert(!CanMegaEvolve(B0)&&CanMegaEvolve(B2));gBattleTypeFlags=BATTLE_TYPE_DOUBLE;assert(!CanMegaEvolve(B2));
puts("Actual native Mega: 16 double ownership/pending combinations; ordinary doubles share; player/Steven/2 opponents independent; player ring gate only PASS");
return 0;}
'''
with tempfile.TemporaryDirectory() as d:
 p=Path(d);(p/'main.c').write_text(base)
 subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-fsanitize=address,undefined','-g',str(p/'main.c'),'-o',str(p/'check')],check=True)
 subprocess.run([str(p/'check')],check=True)