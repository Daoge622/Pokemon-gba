#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "pokedex.h"
#include "random.h"
#include "field_weather.h"
#include "part3.h"
#include "part4.h"
#include "constants/flags.h"
#include "constants/vars.h"
#include "constants/part4.h"
#include "constants/weather.h"

void SyncPart4RaikouObject(void)
{
    u16 state = VarGet(VAR_PART4_RAIKOU_STATE);
    if (state == 1 || state == 2)
        FlagSet(FLAG_PART4_HIDE_RAIKOU);
    else
        FlagClear(FLAG_PART4_HIDE_RAIKOU);
}

void BeginPart4RaikouBattle(void)
{
    VarSet(VAR_PART4_RAIKOU_STATE, 1);
    SyncPart4RaikouObject();
}

void FinishPart4RaikouBattle(void)
{
    VarSet(VAR_PART4_RAIKOU_STATE, Part3EnteiAfterBattle(VarGet(VAR_PART4_RAIKOU_STATE), gBattleOutcome));
    SyncPart4RaikouObject();
}

void ResetPart4RaikouAfterHallOfFame(void)
{
    VarSet(VAR_PART4_RAIKOU_STATE, Part3EnteiAfterHallOfFame(VarGet(VAR_PART4_RAIKOU_STATE)));
    SyncPart4RaikouObject();
}

void GivePart4Relicanth(void)
{
    struct Pokemon mon;
    gSpecialVar_Result = FALSE;
    if (!FlagGet(FLAG_SYS_POKEMON_GET) || FlagGet(FLAG_PART4_RELICANTH_RECEIVED)
        || CalculatePlayerPartyCount() >= PARTY_SIZE)
        return;
    CreateMonWithIVs(&mon, SPECIES_RELICANTH, 30, Random32(), OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    if (GiveCapturedMonToPlayer(&mon) != MON_GIVEN_TO_PARTY)
        return;
    HandleSetPokedexFlagFromMon(&mon, FLAG_SET_SEEN);
    HandleSetPokedexFlagFromMon(&mon, FLAG_SET_CAUGHT);
    FlagSet(FLAG_PART4_RELICANTH_RECEIVED);
    gSpecialVar_Result = TRUE;
}

void SyncPart4LuvdiscObject(void)
{
    if (VarGet(VAR_PART4_LUVDISC_STATE) >= 2)
        FlagClear(FLAG_PART4_HIDE_LUVDISC);
    else
        FlagSet(FLAG_PART4_HIDE_LUVDISC);
}

void GivePart4LuvdiscToGirl(void)
{
    u32 i, j, count = CalculatePlayerPartyCount();
    gSpecialVar_Result = 0; // no eligible unencumbered Luvdisc
    if (VarGet(VAR_PART4_LUVDISC_STATE) >= 2)
        return;
    for (i = 0; i < count; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_LUVDISC
            || GetMonData(mon, MON_DATA_IS_EGG))
            continue;
        // Ask the player to remove any held item first, preserving items and mail.
        if (GetMonData(mon, MON_DATA_HELD_ITEM) != ITEM_NONE)
        {
            gSpecialVar_Result = 3;
            continue;
        }
        for (j = 0; j < count; j++)
        {
            if (j != i && GetMonData(&gParties[B_TRAINER_PLAYER][j], MON_DATA_SPECIES) != SPECIES_NONE
                && !GetMonData(&gParties[B_TRAINER_PLAYER][j], MON_DATA_IS_EGG)
                && GetMonData(&gParties[B_TRAINER_PLAYER][j], MON_DATA_HP) != 0)
            {
                ZeroMonData(mon);
                CompactPartySlots();
                CalculatePlayerPartyCount();
                VarSet(VAR_PART4_LUVDISC_STATE, 2);
                SyncPart4LuvdiscObject();
                gSpecialVar_Result = 1;
                return;
            }
        }
        gSpecialVar_Result = 2; // would leave no able non-egg companion
    }
}

void SyncPart4MegaObjects(void)
{
    u16 stage = VarGet(VAR_PART4_MEGA_STAGE);
    if (stage >= 1) FlagSet(FLAG_PART4_HIDE_AQUA_A); else FlagClear(FLAG_PART4_HIDE_AQUA_A);
    if (stage >= 2) FlagSet(FLAG_PART4_HIDE_AQUA_B); else FlagClear(FLAG_PART4_HIDE_AQUA_B);
    if (stage != 2) FlagSet(FLAG_PART4_HIDE_AQUA_EXTRA); else FlagClear(FLAG_PART4_HIDE_AQUA_EXTRA);
    if (stage < 2 || stage >= 4) FlagSet(FLAG_PART4_HIDE_ANTI); else FlagClear(FLAG_PART4_HIDE_ANTI);
}

void GetPart4RainState(void)
{
    u8 weather = GetCurrentWeather();
    gSpecialVar_Result = weather == WEATHER_RAIN || weather == WEATHER_DOWNPOUR || weather == WEATHER_RAIN_THUNDERSTORM;
}

void CheckPart4LeadCastform(void)
{
    gSpecialVar_Result = GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES) == SPECIES_CASTFORM_NORMAL;
}
