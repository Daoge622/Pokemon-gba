// Small helpers that let cutscene NPCs walk to / away from the player
// (used instead of NPCs talking "across the screen" or popping in/out).
#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "fieldmap.h"
#include "field_player_avatar.h"
#include "constants/event_objects.h"
#include "constants/event_object_movement.h"

#define WIN 40              // BFS window (tiles)
#define MAX_STEPS 255

static EWRAM_DATA u8 sDist[WIN][WIN] = {0};
static EWRAM_DATA u16 sQueue[WIN * WIN] = {0};

static const s8 sDirDx[5] = {0, 0, 0, -1, 1};   // DIR_SOUTH=1, DIR_NORTH=2, DIR_WEST=3, DIR_EAST=4
static const s8 sDirDy[5] = {0, 1, -1, 0, 0};

static struct ObjectEvent *GetPlayerObj(void)
{
    return &gObjectEvents[gPlayerAvatar.objectEventId];
}

static struct ObjectEvent *GetObjByVar(u16 var)
{
    u8 id = GetObjectEventIdByLocalId(VarGet(var));
    if (id >= OBJECT_EVENTS_COUNT || !gObjectEvents[id].active)
        return NULL;
    return &gObjectEvents[id];
}

// Can `obj` step into (x, y) moving in `dir`? Ignores the NPC's wander range.
static bool32 CanEnter(struct ObjectEvent *obj, s16 x, s16 y, u8 dir)
{
    u8 flags = GetCollisionFlagsAtCoords(obj, x, y, dir);
    flags &= ~(1 << (COLLISION_OUTSIDE_RANGE - 1));
    return flags == 0;
}

static s32 Manhattan(s16 ax, s16 ay, s16 bx, s16 by)
{
    return abs(ax - bx) + abs(ay - by);
}

// In: VAR_0x8000 = local id, VAR_0x8001 = stop distance (>= 1).
// Out: VAR_RESULT = direction of the next step, or 0 when close enough / no way.
void StoryStepTowardPlayer(void)
{
    struct ObjectEvent *obj = GetObjByVar(VAR_0x8000);
    struct ObjectEvent *player = GetPlayerObj();
    s32 stop = VarGet(VAR_0x8001);
    s16 px, py, ox, oy, x0, y0;
    s32 head = 0, tail = 0, i, best = 0, bestDist = MAX_STEPS;

    gSpecialVar_Result = 0;
    if (obj == NULL)
        return;
    if (stop < 1)
        stop = 1;
    px = player->currentCoords.x;
    py = player->currentCoords.y;
    ox = obj->currentCoords.x;
    oy = obj->currentCoords.y;
    if (Manhattan(ox, oy, px, py) <= stop)
        return;

    x0 = ((ox + px) / 2) - WIN / 2;
    y0 = ((oy + py) / 2) - WIN / 2;
    memset(sDist, MAX_STEPS, sizeof(sDist));

    // Seed: every reachable tile within `stop` of the player (not the player's tile).
    for (i = 0; i < WIN * WIN; i++)
    {
        s16 x = x0 + (i % WIN), y = y0 + (i / WIN);
        s32 d = Manhattan(x, y, px, py);
        if (d >= 1 && d <= stop && !MapGridGetCollisionAt(x, y)
         && (x == ox && y == oy ? TRUE : CanEnter(obj, x, y, DIR_SOUTH)))
        {
            sDist[i / WIN][i % WIN] = 0;
            sQueue[tail++] = i;
        }
    }
    // Reverse BFS: dist[c] = steps from c to the goal area.
    while (head < tail)
    {
        s32 c = sQueue[head++];
        s16 cx = x0 + (c % WIN), cy = y0 + (c / WIN);
        u8 dir;
        // 255 is the unvisited sentinel, not a representable path distance.
        // Stop expanding before assigning it or wrapping an 8-bit distance.
        // Each cell is then enqueued at most once; the existing greedy fallback
        // handles paths longer than this bounded search can represent.
        if (sDist[cy - y0][cx - x0] >= MAX_STEPS - 1)
            continue;
        for (dir = DIR_SOUTH; dir <= DIR_EAST; dir++)
        {
            // neighbour n steps in `dir` to reach c, so n = c - delta(dir)
            s16 nx = cx - sDirDx[dir], ny = cy - sDirDy[dir];
            s32 gx = nx - x0, gy = ny - y0;
            if (gx < 0 || gy < 0 || gx >= WIN || gy >= WIN)
                continue;
            if (sDist[gy][gx] != MAX_STEPS)
                continue;
            if (!(nx == ox && ny == oy) && !CanEnter(obj, nx, ny, dir))
                continue;
            if (!(cx == ox && cy == oy) && !CanEnter(obj, cx, cy, dir))
                continue;
            sDist[gy][gx] = sDist[cy - y0][cx - x0] + 1;
            sQueue[tail++] = gy * WIN + gx;
        }
    }
    // Pick the neighbouring tile of the NPC that is closest to the goal.
    {
        u8 dir;
        for (dir = DIR_SOUTH; dir <= DIR_EAST; dir++)
        {
            s16 nx = ox + sDirDx[dir], ny = oy + sDirDy[dir];
            s32 gx = nx - x0, gy = ny - y0;
            if (gx < 0 || gy < 0 || gx >= WIN || gy >= WIN)
                continue;
            if (sDist[gy][gx] < bestDist && CanEnter(obj, nx, ny, dir))
            {
                bestDist = sDist[gy][gx];
                best = dir;
            }
        }
    }
    if (best == 0)
    {
        // No path: greedy step along the longer axis if it is free.
        u8 dirX = (px < ox) ? DIR_WEST : DIR_EAST;
        u8 dirY = (py < oy) ? DIR_NORTH : DIR_SOUTH;
        u8 first = (abs(px - ox) >= abs(py - oy)) ? dirX : dirY;
        u8 second = (first == dirX) ? dirY : dirX;
        if (px != ox || first == dirY)
            if (CanEnter(obj, ox + sDirDx[first], oy + sDirDy[first], first))
                best = first;
        if (best == 0 && CanEnter(obj, ox + sDirDx[second], oy + sDirDy[second], second))
            best = second;
    }
    gSpecialVar_Result = best;
}

// In: VAR_0x8000 = local id. Out: VAR_RESULT = a free direction that moves away
// from the player (keeps going straight when possible), or 0.
void StoryStepAwayFromPlayer(void)
{
    struct ObjectEvent *obj = GetObjByVar(VAR_0x8000);
    struct ObjectEvent *player = GetPlayerObj();
    s32 bestScore = -1000;
    u8 dir, best = 0;

    gSpecialVar_Result = 0;
    if (obj == NULL)
        return;
    for (dir = DIR_SOUTH; dir <= DIR_EAST; dir++)
    {
        s16 nx = obj->currentCoords.x + sDirDx[dir], ny = obj->currentCoords.y + sDirDy[dir];
        s32 score;
        if (!CanEnter(obj, nx, ny, dir))
            continue;
        score = Manhattan(nx, ny, player->currentCoords.x, player->currentCoords.y) * 4;
        if (dir == obj->movementDirection)
            score += 3;
        if (score > bestScore)
        {
            bestScore = score;
            best = dir;
        }
    }
    if (best != 0 && bestScore <= Manhattan(obj->currentCoords.x, obj->currentCoords.y,
                                            player->currentCoords.x, player->currentCoords.y) * 4 - 4)
        best = 0; // every free tile gets closer: stop
    gSpecialVar_Result = best;
}

// In: VAR_0x8000 = local id (its template elevation is used), VAR_0x8001/8002 = desired
// offset from the player (signed). Out: VAR_0x8004/8005 = nearest free map coords
// (template coordinates, i.e. without MAP_OFFSET), VAR_RESULT = TRUE if found.
void StoryFindSpawnNearPlayer(void)
{
    struct ObjectEvent *player = GetPlayerObj();
    s16 tx = player->currentCoords.x + (s16)VarGet(VAR_0x8001);
    s16 ty = player->currentCoords.y + (s16)VarGet(VAR_0x8002);
    s32 r, dx, dy;

    gSpecialVar_Result = FALSE;
    for (r = 0; r <= 6; r++)
    {
        for (dy = -r; dy <= r; dy++)
        {
            for (dx = -r; dx <= r; dx++)
            {
                s16 x = tx + dx, y = ty + dy;
                if (abs(dx) != r && abs(dy) != r)
                    continue;
                if (MapGridGetCollisionAt(x, y) || GetMapBorderIdAt(x, y) == CONNECTION_INVALID)
                    continue;
                if (IsElevationMismatchAt(player->currentElevation, x, y))
                    continue;
                if (GetObjectEventIdByXY(x, y) != OBJECT_EVENTS_COUNT)
                    continue;
                if (x == player->currentCoords.x && y == player->currentCoords.y)
                    continue;
                gSpecialVar_0x8004 = x - MAP_OFFSET;
                gSpecialVar_0x8005 = y - MAP_OFFSET;
                gSpecialVar_Result = TRUE;
                return;
            }
        }
    }
    gSpecialVar_0x8004 = tx - MAP_OFFSET;
    gSpecialVar_0x8005 = ty - MAP_OFFSET;
}

// In: VAR_0x8000 = local id. Turns the player towards that NPC.
void StoryPlayerFaceObject(void)
{
    struct ObjectEvent *obj = GetObjByVar(VAR_0x8000);
    struct ObjectEvent *player = GetPlayerObj();
    s16 dx, dy;

    if (obj == NULL)
        return;
    dx = obj->currentCoords.x - player->currentCoords.x;
    dy = obj->currentCoords.y - player->currentCoords.y;
    if (abs(dx) >= abs(dy))
        PlayerFaceDirection(dx < 0 ? DIR_WEST : DIR_EAST);
    else
        PlayerFaceDirection(dy < 0 ? DIR_NORTH : DIR_SOUTH);
}
