#include "global.h"
#include "daycare.h"
#include "event_data.h"
#include "pokemon.h"
#include "project_gifts.h"
#include "constants/flags.h"

void GiveLittlerootRaltsEgg(void)
{
    struct Pokemon egg;
    u32 specialAttackIV = MAX_PER_STAT_IVS;

    gSpecialVar_Result = FALSE;
    // No egg-only party before the original starter/rescue sequence.
    // Party-only delivery matches the original gift egg; full parties can retry.
    if (!FlagGet(FLAG_SYS_POKEMON_GET)
     || FlagGet(FLAG_RECEIVED_LITTLEROOT_RALTS_EGG)
     || CalculatePlayerPartyCount() >= PARTY_SIZE)
        return;

    CreateEgg(&egg, SPECIES_RALTS, FALSE);
    SetMonData(&egg, MON_DATA_SPATK_IV, &specialAttackIV);
    if (GiveCapturedMonToPlayer(&egg) != MON_GIVEN_TO_PARTY)
        return;

    FlagSet(FLAG_RECEIVED_LITTLEROOT_RALTS_EGG);
    gSpecialVar_Result = TRUE;
}
