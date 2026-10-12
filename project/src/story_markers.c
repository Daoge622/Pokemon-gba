// Visible markers (item-ball sprites) for quest pickups that used to be
// invisible sign events. Each marker object uses a temp flag that is set
// on map load once the pickup has been taken (or before it is available).
#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "fieldmap.h"
#include "constants/flags.h"
#include "constants/vars.h"
#include "constants/maps.h"
#include "constants/map_groups.h"

struct PickupMarker
{
    u16 map;
    s16 x, y;
    u16 hideFlag;   // the marker object's flag (a temp flag)
    u16 doneId;     // flag, or var (>= VARS_START) compared with doneValue
    u16 doneValue;
    u16 needFlag;   // must be set for the pickup to be available (0 = always)
};

static const struct PickupMarker sPickupMarkers[] =
{
    {MAP_FORTREE_CITY,               12, 15, FLAG_TEMP_C,  VAR_PART4_KITE,                 1, 0},
    {MAP_FORTREE_CITY,               10, 17, FLAG_TEMP_D,  VAR_PART4_PARCEL,               1, 0},
    {MAP_METEOR_FALLS_1F_1R,          8, 27, FLAG_TEMP_C,  FLAG_PART3_METEOR_STARDUST,     0, 0},
    {MAP_PACIFIDLOG_TOWN,             5, 30, FLAG_TEMP_C,  FLAG_PART6_PLANK_1,             0, 0},
    {MAP_PACIFIDLOG_TOWN,            18,  8, FLAG_TEMP_D,  FLAG_PART6_PLANK_2,             0, 0},
    {MAP_ROUTE108,                   39,  5, FLAG_TEMP_C,  FLAG_PART4_BOTTLEPEARL,         0, 0},
    {MAP_ROUTE111,                   28, 66, FLAG_TEMP_C,  VAR_PART4_CANTEEN,              1, 0},
    {MAP_ROUTE111,                   28, 37, FLAG_TEMP_D,  FLAG_PART4_FIRSTEVOLUTIONSTONE, 0, 0},
    {MAP_ROUTE118,                   30,  9, FLAG_TEMP_C,  VAR_PART4_BERRYBASKET,          1, 0},
    {MAP_ROUTE120,                    8, 35, FLAG_TEMP_C,  FLAG_PART4_MAWILITE,            0, FLAG_PART4_KECLEON_0},
    {MAP_ROUTE131,                   52, 25, FLAG_TEMP_C,  FLAG_PART6_PLANK_3,             0, 0},
    {MAP_ROUTE133,                   77,  6, FLAG_TEMP_C,  FLAG_PART7_BACKFLOW_NUGGETS,    0, 0},
    {MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM, 14, 22, FLAG_TEMP_C, VAR_PART55_FROZEN_STONE,       1, FLAG_PART55_SHELL_BELL_CRAFTED},
    {MAP_UNDERWATER_ROUTE127,        14, 39, FLAG_TEMP_C,  FLAG_PART6_DIVE_LAMP_TAKEN,     0, 0},
    {MAP_UNDERWATER_ROUTE127,        11, 38, FLAG_TEMP_D,  FLAG_PART6_TIDE_RECORDER_TAKEN, 0, 0},
    {MAP_UNDERWATER_ROUTE129,        26, 15, FLAG_TEMP_C,  FLAG_PART6_TOOLBOX_TAKEN,       0, 0},
    {MAP_UNDERWATER_SOOTOPOLIS_CITY,  4,  6, FLAG_TEMP_C,  FLAG_PART6_AID_KIT_TAKEN,       0, 0},
    {MAP_UNDERWATER_SOOTOPOLIS_CITY, 13,  5, FLAG_TEMP_D,  FLAG_PART6_CAMERA_TAKEN,        0, 0},
};

static bool32 ShouldHideMarker(const struct PickupMarker *m)
{
    bool32 done;
    if (m->needFlag != 0 && !FlagGet(m->needFlag))
        return TRUE;
    if (m->doneId >= VARS_START)
        done = VarGet(m->doneId) >= m->doneValue;
    else
        done = FlagGet(m->doneId);
    return done;
}

static u16 CurrentMap(void)
{
    return (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
}

// Called on every map transition, before the objects are spawned.
void Story_UpdatePickupMarkers(void)
{
    u32 i;
    u16 map = CurrentMap();
    for (i = 0; i < ARRAY_COUNT(sPickupMarkers); i++)
    {
        const struct PickupMarker *m = &sPickupMarkers[i];
        if (m->map != map)
            continue;
        if (ShouldHideMarker(m))
            FlagSet(m->hideFlag);
        else
            FlagClear(m->hideFlag);
    }
}

// special: after a pickup script runs, remove markers that should now be hidden.
void StoryRefreshPickupMarkers(void)
{
    u32 i;
    u16 map = CurrentMap();
    for (i = 0; i < ARRAY_COUNT(sPickupMarkers); i++)
    {
        const struct PickupMarker *m = &sPickupMarkers[i];
        u8 objId;
        if (m->map != map || !ShouldHideMarker(m))
            continue;
        FlagSet(m->hideFlag);
        objId = GetObjectEventIdByXY(m->x + MAP_OFFSET, m->y + MAP_OFFSET);
        if (objId < OBJECT_EVENTS_COUNT)
            RemoveObjectEvent(&gObjectEvents[objId]);
    }
}
