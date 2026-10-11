#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "pokedex.h"
#include "random.h"
#include "part2.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/part2.h"

// Transient menu selection only: never stored in a save or used by link evolution.
EWRAM_DATA enum Species gPart2EvolutionTarget = SPECIES_NONE;

bool32 Part2EvolutionTargetAllowed(enum Species species, enum Item item, enum Species target)
{
    return species != SPECIES_CLAMPERL || item != ITEM_EVOLUTION_STONE
        || gPart2EvolutionTarget == SPECIES_NONE || target == gPart2EvolutionTarget;
}

void GivePart2Scyther(void)
{
    struct Pokemon mon;
    u32 attackIV = MAX_PER_STAT_IVS;
    gSpecialVar_Result = FALSE;
    if (!FlagGet(FLAG_SYS_POKEMON_GET)
     || FlagGet(FLAG_PART2_RECEIVED_SCYTHER)
     || CalculatePlayerPartyCount() >= PARTY_SIZE)
        return;
    CreateMonWithIVs(&mon, SPECIES_SCYTHER, PART2_SCYTHER_LEVEL, Random32(), OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    SetMonData(&mon, MON_DATA_ATK_IV, &attackIV);
    CalculateMonStats(&mon);
    if (GiveCapturedMonToPlayer(&mon) != MON_GIVEN_TO_PARTY)
        return;
    HandleSetPokedexFlagFromMon(&mon, FLAG_SET_SEEN);
    HandleSetPokedexFlagFromMon(&mon, FLAG_SET_CAUGHT);
    FlagSet(FLAG_PART2_RECEIVED_SCYTHER);
    gSpecialVar_Result = TRUE;
}
