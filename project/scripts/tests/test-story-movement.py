#!/usr/bin/env python3
"""Host-C regression of the real movement helper. No ROM or emulator."""
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
HEADER = r'''
#ifndef FIXTURE_GLOBAL_H
#define FIXTURE_GLOBAL_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
typedef uint8_t u8; typedef int8_t s8; typedef uint16_t u16;
typedef int16_t s16; typedef int32_t s32; typedef unsigned bool32;
#define EWRAM_DATA
#define TRUE 1
#define FALSE 0
#define OBJECT_EVENTS_COUNT 16
#define DIR_SOUTH 1
#define DIR_NORTH 2
#define DIR_WEST 3
#define DIR_EAST 4
#define COLLISION_OUTSIDE_RANGE 1
#define CONNECTION_INVALID 0
#define MAP_OFFSET 7
#define VAR_0x8000 0
#define VAR_0x8001 1
#define VAR_0x8002 2
struct ObjectEvent { unsigned active; struct {s16 x,y;} currentCoords; u8 movementDirection,currentElevation; };
struct Avatar {u8 objectEventId;};
struct ObjectEvent gObjectEvents[16]; struct Avatar gPlayerAvatar;
u16 gSpecialVar_Result, gSpecialVar_0x8004, gSpecialVar_0x8005;
static int mode; static u16 stopDistance = 1;
u16 VarGet(u16 v) { return v == VAR_0x8000 ? 1 : stopDistance; }
u8 GetObjectEventIdByLocalId(u8 id) { return id; }
static int clear(int x,int y) {
 if (x<0 || y<0 || x>=39 || y>=39) return 0;
 if (mode == 0) return 1;
 if (mode == 2) return x==0 && y==0;
 return y%2==0 || x==((y/2)%2==0 ? 38 : 0);
}
u8 GetCollisionFlagsAtCoords(struct ObjectEvent *o,s16 x,s16 y,u8 dir) {
 (void)o;(void)dir;return clear(x,y)?0:2;
}
u8 MapGridGetCollisionAt(s16 x,s16 y) { return !clear(x,y); }
u8 GetMapBorderIdAt(s16 x,s16 y) { return clear(x,y)?1:0; }
bool32 IsElevationMismatchAt(u8 e,s16 x,s16 y) { (void)e;(void)x;(void)y;return 0; }
u8 GetObjectEventIdByXY(s16 x,s16 y) { (void)x;(void)y;return OBJECT_EVENTS_COUNT; }
void PlayerFaceDirection(u8 d) { (void)d; }
#endif
'''
MAIN = r'''
int main(void) {
 gObjectEvents[1].active=1;
 gObjectEvents[0].currentCoords.x=3;gObjectEvents[0].currentCoords.y=3;
 gObjectEvents[1].currentCoords.x=10;gObjectEvents[1].currentCoords.y=3;
 StoryStepTowardPlayer();assert(gSpecialVar_Result==DIR_WEST);
 gObjectEvents[1].currentCoords.x=4;
 StoryStepTowardPlayer();assert(gSpecialVar_Result==0);
 gObjectEvents[1].active=0;StoryStepTowardPlayer();assert(gSpecialVar_Result==0);
 gObjectEvents[1].active=1;
 gObjectEvents[0].currentCoords.x=0;gObjectEvents[0].currentCoords.y=0;
 gObjectEvents[1].currentCoords.x=38;gObjectEvents[1].currentCoords.y=38;
 mode=1;StoryStepTowardPlayer();
 unsigned zeros=0,maximum=0;
 for(int y=0;y<WIN;y++)for(int x=0;x<WIN;x++) {
   zeros += sDist[y][x]==0;
   if(sDist[y][x]!=MAX_STEPS && sDist[y][x]>maximum)maximum=sDist[y][x];
 }
#ifdef EXPECT_OLD_WRAP
 assert(zeros>1);printf("Historical source reproduces distance wrap: %u zero-distance cells\n",zeros);
#else
 assert(zeros==1);assert(maximum==254);
 puts("Movement PASS: ordinary, adjacent, absent NPC, >255-step maze remains bounded");
#endif
 return 0;
}
'''

def run(source, historical=False):
    with tempfile.TemporaryDirectory() as folder:
        p = Path(folder)
        (p/'constants').mkdir()
        (p/'global.h').write_text(HEADER, encoding='utf-8')
        for name in ('event_data.h','event_object_movement.h','fieldmap.h','field_player_avatar.h',
                     'constants/event_objects.h','constants/event_object_movement.h'):
            (p/name).write_text('#include "global.h"\n', encoding='utf-8')
        (p/'helper.c').write_text(source+'\n'+MAIN, encoding='utf-8')
        cmd = ['gcc','-std=c11','-Wall','-Wextra','-Werror','-fsanitize=address,undefined','-g','-I',str(p),str(p/'helper.c'),'-o',str(p/'test')]
        if historical: cmd.insert(1,'-DEXPECT_OLD_WRAP')
        subprocess.run(cmd,check=True)
        subprocess.run([str(p/'test')],check=True,timeout=10)

if __name__ == '__main__':
    old = subprocess.check_output(['git','show','4e15154194480966babb593cf5de2cc8fca7ce8e:project/src/story_move.c'],cwd=ROOT,text=True)
    run(old, historical=True)
    run((ROOT/'src/story_move.c').read_text(encoding='utf-8'))
