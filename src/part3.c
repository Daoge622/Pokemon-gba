#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "pokemon.h"
#include "part3.h"
#include "constants/battle.h"
#include "constants/flags.h"
#include "constants/part3.h"
#include "constants/vars.h"

u16 Part3EnteiAfterBattle(u16 state, u8 outcome)
{
    if (state == PART3_ENTEI_CAUGHT || outcome == B_OUTCOME_CAUGHT)
        return PART3_ENTEI_CAUGHT;
    return PART3_ENTEI_WAITING;
}

u16 Part3EnteiAfterHallOfFame(u16 state)
{
    return state == PART3_ENTEI_WAITING ? PART3_ENTEI_CHAMPION_RETURN : state;
}

void SyncPart3EnteiObject(void)
{
    u16 state = VarGet(VAR_PART3_ENTEI_STATE);
    if (state == PART3_ENTEI_WAITING || state == PART3_ENTEI_CAUGHT)
        FlagSet(FLAG_PART3_HIDE_ENTEI);
    else
        FlagClear(FLAG_PART3_HIDE_ENTEI);
}

void BeginPart3EnteiBattle(void)
{
    VarSet(VAR_PART3_ENTEI_STATE, PART3_ENTEI_WAITING);
    SyncPart3EnteiObject();
}

void FinishPart3EnteiBattle(void)
{
    VarSet(VAR_PART3_ENTEI_STATE, Part3EnteiAfterBattle(VarGet(VAR_PART3_ENTEI_STATE), gBattleOutcome));
    SyncPart3EnteiObject();
}

void ResetPart3EnteiAfterHallOfFame(void)
{
    // A new League victory permits one more uncaught attempt, never a map reload.
    // This includes the first championship and keeps later failures recoverable.
    VarSet(VAR_PART3_ENTEI_STATE, Part3EnteiAfterHallOfFame(VarGet(VAR_PART3_ENTEI_STATE)));
    SyncPart3EnteiObject();
}

void GetPart3LeadHotSpringType(void)
{
    enum Species species;
    gSpecialVar_Result = 0;
    if (GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_IS_EGG))
        return;
    species = GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES);
    if (species == SPECIES_NONE)
        return;
    if (GetSpeciesType(species, 0) == TYPE_FIRE || GetSpeciesType(species, 1) == TYPE_FIRE)
        gSpecialVar_Result = 1;
    else if (GetSpeciesType(species, 0) == TYPE_ICE || GetSpeciesType(species, 1) == TYPE_ICE)
        gSpecialVar_Result = 2;
}
