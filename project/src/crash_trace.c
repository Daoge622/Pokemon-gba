// Opt-in, RAM-only diagnostic snapshot. Never write flash from the main loop:
// doing so adds synchronous flash/timer work during gameplay and destroys
// Trainer Hill / recorded-battle sectors. This is not a MyBoy crash fix.
// Inspect gCrashTraceSnapshot with a debugger; normal .sav files contain no
// new trace records. read-crash-trace.py reads historical flash-trace saves.
#include "global.h"
#include "main.h"
#include "task.h"
#include "m4a.h"
#include "load_save.h"

#if CRASH_TRACE

#define TRACE_MAGIC      0xC7A5
#define TRACE_ENTRY_SIZE 64
#define TRACE_INTERVAL   30

struct TraceEntry
{
    u16 magic;
    u16 seq;
    u32 frame;
    u8 mapGroup, mapNum;
    s16 x, y;
    u8 avatarFlags;
    u8 numTasks;
    u32 callback1, callback2, vblankCallback, hblankCallback;
    u32 tasks[4];
    u32 bgmSong, se1Song, se2Song, bgmStatus;
};
STATIC_ASSERT(sizeof(struct TraceEntry) == TRACE_ENTRY_SIZE, TraceEntrySize);

EWRAM_DATA struct TraceEntry gCrashTraceSnapshot = {0};
static EWRAM_DATA u16 sSeq = 0;
static EWRAM_DATA u8 sTimer = 0;

void CrashTrace_Frame(void)
{
    struct TraceEntry e = {0};
    u32 i;

    if (gSaveBlock1Ptr == NULL || ++sTimer < TRACE_INTERVAL)
        return;
    sTimer = 0;

    e.magic = TRACE_MAGIC;
    e.seq = sSeq++;
    e.frame = gMain.vblankCounter1;
    e.mapGroup = gSaveBlock1Ptr->location.mapGroup;
    e.mapNum = gSaveBlock1Ptr->location.mapNum;
    e.x = gSaveBlock1Ptr->pos.x;
    e.y = gSaveBlock1Ptr->pos.y;
    e.avatarFlags = gPlayerAvatar.flags;
    e.numTasks = 0;
    for (i = 0; i < 4; i++)
        e.tasks[i] = 0;
    for (i = 0; i < NUM_TASKS; i++)
    {
        if (gTasks[i].isActive)
        {
            if (e.numTasks < 4)
                e.tasks[e.numTasks] = (u32)gTasks[i].func;
            e.numTasks++;
        }
    }
    e.callback1 = (u32)gMain.callback1;
    e.callback2 = (u32)gMain.callback2;
    e.vblankCallback = (u32)gMain.vblankCallback;
    e.hblankCallback = (u32)gMain.hblankCallback;
    e.bgmSong = (u32)gMPlayInfo_BGM.songHeader;
    e.se1Song = (u32)gMPlayInfo_SE1.songHeader;
    e.se2Song = (u32)gMPlayInfo_SE2.songHeader;
    e.bgmStatus = gMPlayInfo_BGM.status;

    gCrashTraceSnapshot = e;
}

#endif // CRASH_TRACE
