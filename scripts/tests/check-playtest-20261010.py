#!/usr/bin/env python3
"""Current-source regression checks; no ROM or emulator execution."""
from pathlib import Path
import json,re,struct,tempfile,subprocess
R=Path(__file__).resolve().parents[2]
def read(f):return (R/f).read_text()
def mp(m):return json.loads(read(f'data/maps/{m}/map.json'))
def blocks(s):
    labels=list(re.finditer(r'^([A-Za-z_]\w*):{1,2}\s*$',s,re.M))
    return {m[1]:s[m.end():labels[i+1].start() if i+1<len(labels) else len(s)] for i,m in enumerate(labels)}
class VM:
    def __init__(self,bag=True,flags=()):self.bag=bag;self.flags=set(flags);self.result=0;self.gifts=[];self.events=[]
    def run(self,label,depth=0):
        assert depth<30
        for raw in B[label].splitlines():
            line=raw.split('@')[0].strip()
            if not line or line.startswith('.'):continue
            op,_,args=line.partition(' ');a=[x.strip() for x in args.split(',')]
            if op in ('end','return'):return
            if op=='goto':return self.run(a[0],depth+1)
            if op=='goto_if_unset' and a[0] not in self.flags:return self.run(a[1],depth+1)
            if op=='goto_if_set' and a[0] in self.flags:return self.run(a[1],depth+1)
            if op=='goto_if_eq' and a[0]=='VAR_RESULT' and self.result=={'FALSE':0,'TRUE':1}.get(a[1],-1):return self.run(a[2],depth+1)
            if op=='call':self.run(a[0],depth+1)
            if op=='setflag':self.flags.add(a[0]);self.events.append(('flag',a[0]))
            if op=='giveitem':
                self.result=int(self.bag)
                if self.bag:self.gifts.append((a[0],int(a[1])));self.events.append(('gift',a[0]))
            if op in ('special','removeobject'):self.events.append((op,a[0]))
        order=list(B);i=order.index(label)
        if i+1<len(order):self.run(order[i+1],depth+1)
B=blocks(read('data/maps/SlateportCity_OceanicMuseum_2F/scripts.inc')+'\n'+read('data/scripts/part2.inc'))
flag='FLAG_PART2_RECEIVED_HEART_SCALES';delivered='FLAG_DELIVERED_DEVON_GOODS';root='SlateportCity_OceanicMuseum_2F_EventScript_FinishThanks'
v=VM(False,[delivered]);v.run(root);assert flag not in v.flags and not v.gifts and not any(x[0] in ('special','removeobject') for x in v.events)
v.bag=True;v.run(root);assert v.gifts==[('ITEM_HEART_SCALE',3)] and flag in v.flags
assert v.events.index(('gift','ITEM_HEART_SCALE'))<v.events.index(('special','HealPlayerParty'))<v.events.index(('removeobject','LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN'))
v.run(root);assert len(v.gifts)==1
v=VM(True,[delivered]);v.run('Part2_TryMuseumThanks');v.run(root);assert len(v.gifts)==1 and ('special','HealPlayerParty') in v.events
assert 'goto_if_set FLAG_DELIVERED_DEVON_GOODS, '+root in B['SlateportCity_OceanicMuseum_2F_EventScript_CaptStern']
print('Museum full bag/retry/floor1 fallback/once-only; gift -> heal -> departure PASS')
gym=mp('LavaridgeTown_Gym_1F');c=[c for c in gym['coord_events'] if c.get('script')=='LavaridgeTown_Gym_Part3_Rehearsal'];assert len(c)==4 and {(c['x'],c['y']) for c in c}=={(x,11) for x in range(11,15)}
assert all(c['var']=='VAR_TEMP_9' and c['var_value']=='0' for c in c)
assert 'setvar VAR_TEMP_9, 0' in read('data/maps/LavaridgeTown_Gym_1F/scripts.inc')
assert re.search(r'#define OW_UNION_DISABLE_CHECK\s+TRUE\b',read('include/config/overworld.h'))
print('Gym scheduled triggers/reset and Union Room option PASS')
layouts={l['id']:l for l in json.loads(read('data/layouts/layouts.json'))['layouts']}
def terrain(m):
    l=layouts[mp(m)['layout']];raw=(R/l['blockdata_filepath']).read_bytes();cells=struct.unpack('<'+'H'*(len(raw)//2),raw)
    return l,lambda x,y:cells[y*l['width']+x]
def moves(label,start,occupied=()):
    b=blocks(read('data/maps/MtChimney/scripts.inc'))[label];l,g=terrain('MtChimney');x,y=start;route=[]
    for step in b.splitlines():
        step=step.strip()
        if not step or step.startswith('@'):continue
        if step=='step_end':break
        dx,dy={'walk_fast_right':(1,0),'walk_fast_left':(-1,0),'walk_fast_down':(0,1),'walk_fast_up':(0,-1)}[step]
        x+=dx;y+=dy;assert 0<=x<l['width'] and 0<=y<l['height'];assert not(g(x,y)&0xc00),(label,x,y,'collision');assert (x,y) not in occupied;route.append((x,y))
    return (x,y),route
p,_=moves('MtChimney_Part3_PlayerStepAside',(10,10));assert p==(11,11)
end,path=moves('MtChimney_Part3_RookieRunAway',(9,9),[p]);assert end==(12,19) and end[1]>9 and min(y for _,y in path)>=9
assert len(path)==13
active={(o['x'],o['y']) for o in mp('MtChimney')['object_events'] if o['flag']=='0'};assert not active.intersection(path)
print('Retreat: player side step, 13-step southbound escape, walkable actor-clear tiles PASS')
worker=next(o for o in mp('SlateportCity')['object_events'] if o.get('local_id')=='LOCALID_PART5_SLATE_ARCHE');assert (worker['x'],worker['y'])==(32,14)
l,g=terrain('SlateportCity');assert not(g(32,14)&0xc00)
assert sum((o['x'],o['y'])==(32,14) for o in mp('SlateportCity')['object_events'])==1
assert not any((w['x'],w['y'])==(32,14) for w in mp('SlateportCity')['warp_events'])
print('Harbor relocation: correct actor, walkable unoccupied tile, no warp overlap PASS')
with tempfile.TemporaryDirectory() as td:
    d=Path(td);(d/'constants').mkdir()
    (d/'global.h').write_text('''#ifndef STUB_H
#define STUB_H
#include <stdint.h>
#include <stdbool.h>
typedef uint8_t u8;typedef uint16_t u16;typedef uint32_t u32;
#define ARRAY_COUNT(x) (sizeof(x)/sizeof((x)[0]))
struct ScriptContext;
struct ObjectEvent {u8 movementType,facingDirection;};
struct Save {struct {u8 mapGroup,mapNum;} location;};
extern struct ObjectEvent gObjectEvents[16];extern struct Save *gSaveBlock1Ptr;
bool FlagGet(u16);void SetObjEventTemplateMovementType(u8,u8);
bool TryGetObjectEventIdByLocalIdAndMap(u8,u8,u8,u8*);
void SetTrainerMovementType(struct ObjectEvent*,u8);
u8 GetTrainerFacingDirectionMovementType(u8);u16 Part55_TrainerFlag(u16);
#endif
''')
    for h in ('part3.h','event_data.h','overworld.h','event_object_movement.h','part55.h'):(d/h).write_text('#include "global.h"\n')
    (d/'constants/opponents.h').write_text('#define TRAINER_MADELINE_1 1\n#define TRAINER_SOPHIE 2\n#define TRAINER_COBY 3\n#define MOVEMENT_TYPE_FACE_DOWN 7\n')
    (d/'constants/maps.h').write_text('#define MAP_ROUTE113 0x123\n#define MAP_GROUP(m) ((m)>>8)\n#define MAP_NUM(m) ((m)&255)\n')
    (d/'fix.c').write_text(read('src/field_playtest_fixes.c'))
    (d/'main.c').write_text('''#include "global.h"
#include <assert.h>
void StopDefeatedRoute113Trainers(struct ScriptContext *ctx);
struct ObjectEvent gObjectEvents[16];struct Save save;struct Save *gSaveBlock1Ptr=&save;
bool flags[4];u8 templates[17];bool loaded;
bool FlagGet(u16 id){assert(id<4);return flags[id];}
u16 Part55_TrainerFlag(u16 id){return id;}
void SetObjEventTemplateMovementType(u8 id,u8 m){templates[id]=m;}
bool TryGetObjectEventIdByLocalIdAndMap(u8 id,u8 n,u8 g,u8*out){assert(n==0x23&&g==1);*out=id-1;return !loaded;}
void SetTrainerMovementType(struct ObjectEvent*o,u8 m){o->movementType=m;}
u8 GetTrainerFacingDirectionMovementType(u8 f){return f+10;}
int main(void){
save.location.mapGroup=1;save.location.mapNum=0x23;loaded=true;
for(unsigned mask=0;mask<8;mask++){
for(unsigned i=0;i<3;i++){u8 id=(u8[]){5,15,16}[i];flags[i+1]=(mask>>i)&1;templates[id]=99;gObjectEvents[id-1].movementType=99;gObjectEvents[id-1].facingDirection=i+1;}
StopDefeatedRoute113Trainers(0);
for(unsigned i=0;i<3;i++){u8 id=(u8[]){5,15,16}[i];assert(templates[id]==(flags[i+1]?7:99));assert(gObjectEvents[id-1].movementType==(flags[i+1]?i+11:99));}
}
loaded=false;StopDefeatedRoute113Trainers(0);
save.location.mapNum=0;templates[5]=99;StopDefeatedRoute113Trainers(0);assert(templates[5]==99);
return 0;}
''')
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-I',str(d),str(d/'fix.c'),str(d/'main.c'),'-o',str(d/'test')],check=True)
    subprocess.run([str(d/'test')],check=True)
print('Actual C: eight defeat combinations; callback/template stop; missing sprites; wrong map PASS')
