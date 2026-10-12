#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "pokedex.h"
#include "part5.h"
#include "constants/flags.h"
#include "constants/region_map_sections.h"
#include "constants/species.h"
#include "constants/vars.h"
#include "constants/part5.h"
#include "constants/part2.h"

#define PART5_SAFARI_SPECIES_LIMIT 8

static bool32 IsPart5SafariCatch(struct BoxPokemon *boxMon)
{
    if (!GetBoxMonData(boxMon, MON_DATA_SANITY_HAS_SPECIES) || GetBoxMonData(boxMon, MON_DATA_SANITY_IS_EGG))
        return FALSE;
    if (GetBoxMonData(boxMon, MON_DATA_MET_LOCATION) != MAPSEC_SAFARI_ZONE)
        return FALSE;
    return GetBoxMonData(boxMon, MON_DATA_OT_ID) == READ_OTID_FROM_SAVE;
}

static u32 AddPart5SafariSpecies(u16 *seen, u32 count, u16 species)
{
    u32 i;
    for (i = 0; i < count; i++)
    {
        if (seen[i] == species)
            return count;
    }
    if (count < PART5_SAFARI_SPECIES_LIMIT)
        seen[count++] = species;
    return count;
}

// Counts distinct species the player caught in the Safari Zone that are still owned.
// Uses the native met-location record, so no extra save data is needed.
void Part5_CountSafariSpecies(void)
{
    u16 seen[PART5_SAFARI_SPECIES_LIMIT];
    u32 count = 0;
    u32 i, box, pos;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct BoxPokemon *boxMon = &gParties[B_TRAINER_PLAYER][i].box;
        if (IsPart5SafariCatch(boxMon))
            count = AddPart5SafariSpecies(seen, count, GetBoxMonData(boxMon, MON_DATA_SPECIES));
    }
    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
    {
        for (pos = 0; pos < IN_BOX_COUNT; pos++)
        {
            struct BoxPokemon *boxMon = GetBoxedMonPtr(box, pos);
            if (IsPart5SafariCatch(boxMon))
                count = AddPart5SafariSpecies(seen, count, GetBoxMonData(boxMon, MON_DATA_SPECIES));
        }
    }
    gSpecialVar_Result = count;
}

static bool32 Part5Caught(u16 species)
{
    return GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT);
}

void Part5_CheckHeracrossPinsirCaught(void)
{
    gSpecialVar_Result = Part5Caught(SPECIES_HERACROSS) && Part5Caught(SPECIES_PINSIR);
}

static bool32 Part5PartyHasSpecies(const u16 *species, u32 count)
{
    u32 i, j;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        u16 mon = GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES_OR_EGG);
        for (j = 0; j < count; j++)
        {
            if (mon == species[j])
                return TRUE;
        }
    }
    return FALSE;
}

void Part5_CheckPartyRaltsLine(void)
{
    static const u16 sRalts[] = {SPECIES_RALTS, SPECIES_KIRLIA, SPECIES_GARDEVOIR, SPECIES_GALLADE};
    gSpecialVar_Result = Part5PartyHasSpecies(sRalts, ARRAY_COUNT(sRalts));
}

// Ribbon box quest: the girl walks into the hall; the next map load shows her back outside.
void Part5_SyncContestGirl(void)
{
    if (VarGet(VAR_PART5_RIBBON) == PART5_RIBBON_INSIDE)
        VarSet(VAR_PART5_RIBBON, PART5_RIBBON_BACK);
    if (VarGet(VAR_PART5_RIBBON) == PART5_RIBBON_INSIDE)
        FlagSet(FLAG_PART5_HIDE_CONTEST_GIRL);
    else
        FlagClear(FLAG_PART5_HIDE_CONTEST_GIRL);
}

// Peace charm: the boyfriend waits beside her in Slateport once the charm is delivered
// and Team Aqua has left the Lilycove hideout.
void Part5_SyncSlateport(void)
{
    if (VarGet(VAR_PART2_PEACE_CHARM_STATE) >= PART2_CHARM_DELIVERED && FlagGet(FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE))
        FlagClear(FLAG_PART5_HIDE_SLATEPORT_BOYFRIEND);
    else
        FlagSet(FLAG_PART5_HIDE_SLATEPORT_BOYFRIEND);
}

void Part5_CheckSolrockLunatoneCaught(void)
{
    gSpecialVar_Result = Part5Caught(SPECIES_SOLROCK) && Part5Caught(SPECIES_LUNATONE);
}

void Part5_CheckPartySolrockLunatone(void)
{
    static const u16 sSpecies[] = {SPECIES_SOLROCK, SPECIES_LUNATONE};
    gSpecialVar_Result = Part5PartyHasSpecies(sSpecies, ARRAY_COUNT(sSpecies));
}

// The rescued Swablu waits beside the child; FLAG_TEMP_1F hides it until then.
void Part5_SyncMossdeep(void)
{
    if (FlagGet(FLAG_PART5_SWABLU_RETURNED))
        FlagClear(FLAG_TEMP_1F);
    else
        FlagSet(FLAG_TEMP_1F);
}
