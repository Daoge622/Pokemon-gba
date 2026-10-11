#include "global.h"
#include "part3.h"
#include "event_data.h"
#include "overworld.h"
#include "event_object_movement.h"
#include "part55.h"
#include "constants/opponents.h"
#include "constants/maps.h"

// A battle reloads object callbacks. Restore stationary behavior from existing
// trainer defeat flags on entry and after battle; no new save state is needed.
void StopDefeatedRoute113Trainers(struct ScriptContext *ctx)
{
    static const struct { u16 trainer; u8 localId; } trainers[] =
    {
        {TRAINER_MADELINE_1, 5},
        {TRAINER_SOPHIE, 15},
        {TRAINER_COBY, 16},
    };
    u32 i;
    (void)ctx; // callnative passes its current script context; this helper never waits.
    if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(MAP_ROUTE113)
     || gSaveBlock1Ptr->location.mapNum != MAP_NUM(MAP_ROUTE113))
        return;
    for (i = 0; i < ARRAY_COUNT(trainers); i++)
    {
        u8 objectId;
        if (!FlagGet(Part55_TrainerFlag(trainers[i].trainer)))
            continue;
        SetObjEventTemplateMovementType(trainers[i].localId, MOVEMENT_TYPE_FACE_DOWN);
        if (!TryGetObjectEventIdByLocalIdAndMap(trainers[i].localId,
             MAP_NUM(MAP_ROUTE113), MAP_GROUP(MAP_ROUTE113), &objectId))
        {
            struct ObjectEvent *object = &gObjectEvents[objectId];
            SetTrainerMovementType(object,
                GetTrainerFacingDirectionMovementType(object->facingDirection));
        }
    }
}
