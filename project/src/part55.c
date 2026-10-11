#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "pokemon.h"
#include "pokedex.h"
#include "event_data.h"
#include "random.h"
#include "main.h"
#include "overworld.h"
#include "safari_zone.h"
#include "script_pokemon_util.h"
#include "constants/vars.h"
#include "constants/species.h"
#include "constants/battle.h"
#include "constants/part55.h"
#include "part55.h"
#include "constants/opponents.h"
#include "constants/flags.h"

// Extended native roster lives in ROM. Persistent results use audited flags,
// never TRAINER_FLAGS_START + an out-of-range opponent ID. Save layout unchanged.
u16 Part55_TrainerFlag(u16 trainerId)
{
    switch (trainerId)
    {
    case TRAINER_PART55_ROOKIE: return FLAG_PART55_BATTLED_ROOKIE;
    case TRAINER_PART55_AQUA_OBSERVER_A: return FLAG_PART55_BATTLED_AQUA_OBSERVER_A;
    case TRAINER_PART55_AQUA_OBSERVER_B: return FLAG_PART55_BATTLED_AQUA_OBSERVER_B;
    case TRAINER_PART55_SAFARI_EXPERT: return FLAG_PART55_BATTLED_SAFARI_EXPERT;
    case TRAINER_PART55_ADVANCED_TRAINER: return FLAG_PART55_BATTLED_ADVANCED_TRAINER;
    case TRAINER_PART55_PSYCHIC_RESEARCHER: return FLAG_PART55_BATTLED_PSYCHIC_RESEARCHER;
    case TRAINER_PART6_RAIN: return FLAG_PART6_BEAT_RAIN;
    case TRAINER_PART6_GALLADE_MASTER: return FLAG_PART6_BEAT_GALLADE_MASTER;
    case TRAINER_PART6_SKY_GUARD_131: return FLAG_PART6_BEAT_SKY_GUARD_131;
    case TRAINER_PART6_SKY_SECURITY: return FLAG_PART6_BEAT_SKY_SECURITY;
    case TRAINER_PART6_SKY_LIFE_RESEARCHER: return FLAG_PART6_BEAT_SKY_LIFE_RESEARCHER;
    case TRAINER_PART6_SKY_TECH_GUARD: return FLAG_PART6_BEAT_SKY_TECH_GUARD;
    case TRAINER_PART6_SKY_SENIOR_RESEARCHER: return FLAG_PART6_BEAT_SKY_SENIOR_RESEARCHER;
    case TRAINER_PART6_EVELYN: return FLAG_PART6_BEAT_EVELYN;
    case TRAINER_PART7_FOREST_RANGER: return FLAG_PART7_BEAT_FOREST_RANGER;
    case TRAINER_PART7_FOREST_COOLTRAINER: return FLAG_PART7_BEAT_FOREST_COOLTRAINER;
    case TRAINER_PART7_FOREST_BUG_MANIAC: return FLAG_PART7_BEAT_FOREST_BUG_MANIAC;
    case TRAINER_PART7_DRIFTER: return FLAG_PART7_BEAT_DRIFTER;
    case TRAINER_PART7_BACKFLOW_SIBLINGS: return FLAG_PART7_BEAT_BACKFLOW_SIBLINGS;
    case TRAINER_PART7_PLATFORM_ACE: return FLAG_PART7_BEAT_PLATFORM_ACE;
    case TRAINER_PART7_VR_BUG_MANIAC: return FLAG_PART7_BEAT_VR_BUG_MANIAC;
    default: return trainerId < MAX_TRAINERS_COUNT ? TRAINER_FLAGS_START + trainerId : 0;
    }
}

void Part55_PrepareAxew(void)
{
    struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][0];
    u8 iv = 31;
    bool8 shiny = TRUE;
    u32 pid = GetMonData(mon, MON_DATA_PERSONALITY);
    SetMonData(mon, MON_DATA_ATK_IV, &iv);
    SetMonData(mon, MON_DATA_IS_SHINY, &shiny);
    CalculateMonStats(mon);
    VarSet(VAR_PART55_AXEW_PID_LO, pid & 0xFFFF);
    VarSet(VAR_PART55_AXEW_PID_HI, pid >> 16);
}

void Part55_FinishAxew(void)
{
    if (gBattleOutcome == B_OUTCOME_CAUGHT)
        FlagSet(FLAG_PART55_AXEW_CAUGHT);
}

void Part55_CheckCapturedAxewParty(void)
{
    u32 i, pid = VarGet(VAR_PART55_AXEW_PID_LO) | ((u32)VarGet(VAR_PART55_AXEW_PID_HI) << 16);
    gSpecialVar_Result = FALSE;
    if (!FlagGet(FLAG_PART55_AXEW_CAUGHT))
        return;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        enum Species species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);
        if ((species == SPECIES_AXEW || species == SPECIES_FRAXURE || species == SPECIES_HAXORUS)
         && GetMonData(mon, MON_DATA_PERSONALITY) == pid
         && GetMonData(mon, MON_DATA_OT_ID) == READ_OTID_FROM_SAVE)
            gSpecialVar_Result = TRUE;
    }
}

void Part55_GivePorygon(void)
{
    struct Pokemon mon;
    gSpecialVar_Result = FALSE;
    if (VarGet(VAR_PART55_PORYGON) != 4 || CalculatePlayerPartyCount() >= PARTY_SIZE)
        return;
    CreateMonWithIVs(&mon, SPECIES_PORYGON, 30, Random32(), OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    if (GiveCapturedMonToPlayer(&mon) != MON_GIVEN_TO_PARTY)
        return;
    HandleSetPokedexFlagFromMon(&mon, FLAG_SET_SEEN);
    HandleSetPokedexFlagFromMon(&mon, FLAG_SET_CAUGHT);
    VarSet(VAR_PART55_PORYGON, 5);
    gSpecialVar_Result = TRUE;
}

void Part55_CheckSafariLargeSeen(void)
{
    gSpecialVar_Result = GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_KANGASKHAN), FLAG_GET_SEEN)
                     && GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_CHANSEY), FLAG_GET_SEEN)
                     && GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_TAUROS), FLAG_GET_SEEN);
}

// Native Safari callback retains balls, steps, caught counters and out-of-balls warp.
// Only its normal-return path is made to resume this scripted observation.
static void Part55_EndSafariObservation(void)
{
    CB2_EndSafariBattle();
    if (gNumSafariBalls != 0)
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void Part55_StartSafariBeedrill(void)
{
    if (!GetSafariZoneFlag())
        return;
    CreateScriptedWildMon(SPECIES_BEEDRILL, 30, ITEM_NONE);
    BattleSetup_StartWildBattle();
    gMain.savedCallback = Part55_EndSafariObservation;
}

// Called only after the original shard trade succeeds; one bit per native color.
void Part55_RecordShardTrade(void)
{
    u16 bits = VarGet(VAR_PART55_SHARDS);
    u16 mask = 0;
    switch (gSpecialVar_0x8008)
    {
    case ITEM_RED_SHARD: mask = 1; break;
    case ITEM_YELLOW_SHARD: mask = 2; break;
    case ITEM_BLUE_SHARD: mask = 4; break;
    case ITEM_GREEN_SHARD: mask = 8; break;
    }
    VarSet(VAR_PART55_SHARDS, bits | mask);
}

void Part55_TakeSample(void)
{
    u16 type = gSpecialVar_0x8004, bits = VarGet(VAR_PART55_SAMPLE_BITS);
    gSpecialVar_Result = 0;
    if (type < 1 || type > 3 || (bits & (1u << (type - 1))))
        return;
    if (VarGet(VAR_PART55_SAMPLE_CARRY) != 0)
    {
        gSpecialVar_Result = 1;
        return;
    }
    VarSet(VAR_PART55_SAMPLE_CARRY, type);
    gSpecialVar_Result = 2;
}

void Part55_DeliverSample(void)
{
    u16 type = VarGet(VAR_PART55_SAMPLE_CARRY);
    gSpecialVar_Result = 0;
    if (type == 0)
        return;
    if (type != gSpecialVar_0x8004)
    {
        gSpecialVar_Result = 1;
        return;
    }
    VarSet(VAR_PART55_SAMPLE_BITS, VarGet(VAR_PART55_SAMPLE_BITS) | (1u << (type - 1)));
    VarSet(VAR_PART55_SAMPLE_CARRY, 0);
    gSpecialVar_Result = 2;
}

void Part55_RecordPoint(void)
{
    u16 var = gSpecialVar_0x8004;
    VarSet(var, VarGet(var) | gSpecialVar_0x8005);
}
