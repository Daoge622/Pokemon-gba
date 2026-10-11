#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "field_weather.h"
#include "overworld.h"
#include "pokemon.h"
#include "pokedex.h"
#include "part3.h"
#include "part6.h"
#include "constants/battle.h"
#include "constants/flags.h"
#include "constants/maps.h"
#include "constants/vars.h"
#include "constants/weather.h"
#include "constants/part6.h"

// Space Center: the rookie waits outside while Team Magma is inside and stays until her scene ends.
void Part6_SyncMossdeep(void)
{
    if (VarGet(VAR_MOSSDEEP_CITY_STATE) >= 2 && !FlagGet(FLAG_PART6_ROOKIE_LEFT_MAGMA))
        FlagClear(FLAG_TEMP_1E);
    else
        FlagSet(FLAG_TEMP_1E);
}

void Part6_CountAnomaly(void)
{
    gSpecialVar_Result = FlagGet(FLAG_PART6_ANOMALY_HEAT) + FlagGet(FLAG_PART6_ANOMALY_CURRENT) + FlagGet(FLAG_PART6_ANOMALY_ENERGY);
}

// Suicune follows the Entei/Raikou rule: caught = permanent; any other outcome = gone until a new Hall of Fame.
void Part6_SyncSuicune(void)
{
    if (FlagGet(FLAG_PART6_SUICUNE_CAUGHT) || FlagGet(FLAG_PART6_SUICUNE_WAITING))
        FlagSet(FLAG_TEMP_1);
    else
        FlagClear(FLAG_TEMP_1);
}

void Part6_BeginSuicuneBattle(void)
{
    // Written before the battle so a whiteout cannot leave Suicune repeatable on reload.
    FlagSet(FLAG_PART6_SUICUNE_WAITING);
    Part6_SyncSuicune();
}

void Part6_FinishSuicuneBattle(void)
{
    if (gBattleOutcome == B_OUTCOME_CAUGHT)
    {
        FlagSet(FLAG_PART6_SUICUNE_CAUGHT);
        FlagClear(FLAG_PART6_SUICUNE_WAITING);
    }
    Part6_SyncSuicune();
}

void Part6_ResetSuicuneAfterHallOfFame(void)
{
    if (!FlagGet(FLAG_PART6_SUICUNE_CAUGHT))
        FlagClear(FLAG_PART6_SUICUNE_WAITING);
    Part6_SyncSuicune();
}

// ---------------------------------------------------------------- Primal Adjuster
static bool32 Part6_IsWeatherLockedMap(void)
{
    u16 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    switch (map)
    {
    case MAP_SKY_PILLAR_OUTSIDE:
    case MAP_SKY_PILLAR_TOP:
    case MAP_SOOTOPOLIS_CITY:
    case MAP_EVER_GRANDE_CITY:
        return TRUE;
    }
    switch (gMapHeader.weather)
    {
    case WEATHER_DROUGHT:
    case WEATHER_DOWNPOUR:
    case WEATHER_ABNORMAL:
    case WEATHER_VOLCANIC_ASH:
    case WEATHER_UNDERWATER_BUBBLES:
        return TRUE;
    }
    return FALSE;
}

// VAR_RESULT: 0 usable, 1 not an ordinary outdoor map, 2 extreme/legendary weather active.
void Part6_AdjusterCanUse(void)
{
    if (FlagGet(FLAG_SYS_WEATHER_CTRL))
        gSpecialVar_Result = 2;
    else if (!IsMapTypeOutdoors(gMapHeader.mapType) || gMapHeader.mapType == MAP_TYPE_UNDERWATER || Part6_IsWeatherLockedMap())
        gSpecialVar_Result = 1;
    else
        gSpecialVar_Result = 0;
}

// VAR_0x8004: 0 sun, 1 rain, 2 sandstorm, 3 snow, 4 restore the map's own weather.
void Part6_AdjusterApply(void)
{
    switch (gSpecialVar_0x8004)
    {
    case 0:
        SetSavedWeather(WEATHER_SUNNY);
        FlagSet(FLAG_PART6_ADJUSTER_SUN);
        break;
    case 1:
        SetSavedWeather(WEATHER_RAIN);
        FlagSet(FLAG_PART6_ADJUSTER_RAIN);
        break;
    case 2:
        SetSavedWeather(WEATHER_SANDSTORM);
        FlagSet(FLAG_PART6_ADJUSTER_SAND);
        break;
    case 3:
        SetSavedWeather(WEATHER_SNOW);
        break;
    default:
        SetSavedWeatherFromCurrMapHeader();
        break;
    }
    DoCurrentWeather();
}

void Part6_CountAdjusterWeathers(void)
{
    gSpecialVar_Result = FlagGet(FLAG_PART6_ADJUSTER_SUN) + FlagGet(FLAG_PART6_ADJUSTER_RAIN) + FlagGet(FLAG_PART6_ADJUSTER_SAND);
}

static void Part6_Show(u16 tempFlag, bool32 visible)
{
    if (visible)
        FlagClear(tempFlag);
    else
        FlagSet(tempFlag);
}

// One transition hook for every PART6 map whose actors depend on story state.
// Temporary flags are cleared on every map load, so no save space is used.
void Part6_SyncMap(void)
{
    u16 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    bool32 crisis = FlagGet(FLAG_SYS_WEATHER_CTRL);
    bool32 resolved = VarGet(VAR_SKY_PILLAR_STATE) >= 2;
    bool32 afterSpaceCenter = VarGet(VAR_MOSSDEEP_CITY_STATE) >= 3;

    switch (map)
    {
    case MAP_MOSSDEEP_CITY_SPACE_CENTER_1F:
        Part6_Show(FLAG_TEMP_11, afterSpaceCenter && !crisis && !resolved);
        break;
    case MAP_ROUTE128:
        Part6_Show(FLAG_TEMP_11, afterSpaceCenter && !resolved);
        break;
    case MAP_ROUTE127:
        Part6_Show(FLAG_TEMP_12, !FlagGet(FLAG_PART6_CALIBRATION_DONE));
        break;
    case MAP_ARCHE_CAMPUS_HQ_1F:
        Part6_Show(FLAG_TEMP_11, crisis || resolved);
        break;
    case MAP_SOOTOPOLIS_CITY:
        Part6_Show(FLAG_TEMP_11, crisis);
        Part6_Show(FLAG_TEMP_12, FlagGet(FLAG_PART6_SPHEAL_FOUND));
        Part6_Show(FLAG_TEMP_13, resolved && !FlagGet(FLAG_PART6_ADJUSTER_RECEIVED));
        break;
    case MAP_SKY_PILLAR_ENTRANCE:
        Part6_Show(FLAG_TEMP_11, VarGet(VAR_SOOTOPOLIS_CITY_STATE) >= 4 && !FlagGet(FLAG_PART6_SKY_PILLAR_ARCHE_LEFT));
        break;
    case MAP_LAVARIDGE_TOWN:
        Part6_Show(FLAG_TEMP_11, resolved && FlagGet(FLAG_PART6_ROOKIE_LEFT_MAGMA));
        break;
    }
}

void Part6_CountReview(void)
{
    gSpecialVar_Result = FlagGet(FLAG_PART6_REVIEW_119) + FlagGet(FLAG_PART6_REVIEW_SLATEPORT)
                       + FlagGet(FLAG_PART6_REVIEW_LILYCOVE) + FlagGet(FLAG_PART6_REVIEW_MOSSDEEP);
}

static bool32 Part6Caught(u16 species)
{
    return GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT);
}

void Part6_CheckRegisCaught(void)
{
    gSpecialVar_Result = Part6Caught(SPECIES_REGIROCK) && Part6Caught(SPECIES_REGICE) && Part6Caught(SPECIES_REGISTEEL);
}
