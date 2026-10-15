// Debug-only crash breadcrumbs (CRASH_TRACE=1 builds). Every 30 frames a
// 64-byte snapshot of what the game is doing is appended to flash sectors
// 30/31 (Trainer Hill / recorded battle data, which these builds give up), so
// the .sav left behind after a hard freeze shows the last moments before it.
// Read it back with scripts/tests/read-crash-trace.py.
#include "global.h"
#include "main.h"
#include "task.h"
#include "m4a.h"
#include "load_save.h"
#include "gba/flash_internal.h"

#if CRASH_TRACE

#define TRACE_MAGIC      0xC7A5
#define TRACE_SECTOR_A   30
#define TRACE_SECTOR_B   31
#define TRACE_ENTRY_SIZE 64
#define TRACE_PER_SECTOR (0x1000 / TRACE_ENTRY_SIZE)
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

static EWRAM_DATA u8 sInit = 0;
static EWRAM_DATA u8 sSector = 0;
static EWRAM_DATA u8 sSlot = 0;
static EWRAM_DATA u16 sSeq = 0;
static EWRAM_DATA u8 sTimer = 0;

// Last used slot in a sector, or -1 if the sector holds no entry.
static s32 LastSlot(u8 sector, u16 *seq)
{
    s32 i, last = -1;
    struct TraceEntry e;
    for (i = 0; i < TRACE_PER_SECTOR; i++)
    {
        ReadFlash(sector, i * TRACE_ENTRY_SIZE, (u8 *)&e, 4);
        if (e.magic != TRACE_MAGIC)
            break;
        last = i;
        *seq = e.seq;
    }
    return last;
}

static void StartSector(u8 sector)
{
    EraseFlashSector(sector);
    sSector = sector;
    sSlot = 0;
}

static void Init(void)
{
    u16 seqA = 0, seqB = 0;
    s32 a = LastSlot(TRACE_SECTOR_A, &seqA);
    s32 b = LastSlot(TRACE_SECTOR_B, &seqB);
    // Each boot begins in a fresh sector so the previous session's last
    // entries (the freeze) survive in the other one.
    if (a >= 0 && (b < 0 || (s16)(seqA - seqB) > 0))
    {
        sSeq = seqA + 1;
        StartSector(TRACE_SECTOR_B);
    }
    else
    {
        sSeq = (b >= 0) ? seqB + 1 : 0;
        StartSector(TRACE_SECTOR_A);
    }
    sInit = TRUE;
}

void CrashTrace_Frame(void)
{
    struct TraceEntry e;
    u32 i;
    const u8 *src;

    if (gFlashMemoryPresent != TRUE || ++sTimer < TRACE_INTERVAL)
        return;
    sTimer = 0;
    if (!sInit)
        Init();
    if (sSlot >= TRACE_PER_SECTOR)
        StartSector(sSector == TRACE_SECTOR_A ? TRACE_SECTOR_B : TRACE_SECTOR_A);

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

    src = (const u8 *)&e;
    for (i = 0; i < TRACE_ENTRY_SIZE; i++)
        ProgramFlashByte(sSector, sSlot * TRACE_ENTRY_SIZE + i, src[i]);
    sSlot++;
}

#endif // CRASH_TRACE
