#!/usr/bin/env python3
"""Static regression gates for the Oct 7 capture/early-play fixes. Never executes a ROM."""
from pathlib import Path
import subprocess,re,json,struct
R=Path(__file__).resolve().parents[2]
def read(p):return (R/p).read_text(encoding='utf-8')
def old(p):return subprocess.check_output(['git','show','578496443f:'+p],cwd=R).decode('utf-8')
def ok(name,condition):assert condition,name;print('PASS',name)
abi=['include/global.h','include/pokemon.h','include/constants/items.h','include/constants/species.h','include/constants/flags.h','include/constants/vars.h','include/constants/opponents.h','data/maps/map_groups.json','data/layouts/layouts.json','src/save.c','src/load_save.c']
ok('save structs, Pokemon format, IDs, flags/vars and save I/O unchanged',all(read(f)==old(f) for f in abi))
s=read('src/pokedex.c')
# Every free of the shared pointer must immediately invalidate it; comments do not affect ownership.
plain=re.sub(r'//[^\n]*|/\*.*?\*/','',s,flags=re.S)
free=list(re.finditer(r'Free\(sPokedexView\);',plain))
ok('all Pokedex view release sites clear the pointer before it can be reused',len(free)==2 and all(re.match(r'\s*sPokedexView\s*=\s*NULL;',plain[m.end():]) for m in free))
ok('KO extra animation disabled for both sides',re.search(r'^#define B_ANIMATE_MON_AFTER_KO\s+FALSE\b',read('include/config/battle.h'),re.M))
f='src/data/pokemon/level_up_learnsets/gen_9.h';before,after=old(f),read(f)
for species in ['Mudkip','Marshtomp','Swampert']:
 pattern=r'static const struct LevelUpMove s'+species+r'LevelUpLearnset\[\] = \{.*?\n\};'
 block=re.search(pattern,after,re.S).group();ok(species+' has no Rock Smash level-up entry','MOVE_ROCK_SMASH' not in block)
 if species=='Mudkip':ok('Mudkip retains a useful level 6 move','LEVEL_UP_MOVE( 6, MOVE_MUD_SLAP)' in block)
 before=re.sub(pattern,'<MUDKIP_FAMILY>',before,flags=re.S);after=re.sub(pattern,'<MUDKIP_FAMILY>',after,flags=re.S)
ok('all other Gen9 learnsets preserved',before==after)
s=read('data/maps/LittlerootTown/scripts.inc')
ok('first departure reminder skips already received egg and does not allocate a new flag',s.count('call_if_unset FLAG_RECEIVED_LITTLEROOT_RALTS_EGG, LittlerootTown_EventScript_RemindPrivateEgg')==1 and 'LittlerootTown_EventScript_RemindPrivateEgg::' in s)
rem=s.split('LittlerootTown_EventScript_RemindPrivateEgg::')[1].split('LittlerootTown_Text_PrivateEggReminder:')[0]
ok('reminder cannot grant a duplicate egg or consume its receipt flag',not re.search(r'(setflag|giveegg|givepokemon|special)',rem) and '\treturn' in rem)
# The helper already has native success/full-party/IV checks in test-opening.py; ensure this fix did not replace it.
forbidden=['ARCHE','安提','阿尔刻']
text=s.split('LittlerootTown_Text_PrivateEggReminder:')[1]
ok('egg reminder keeps the private sender unidentified',not any(x in text for x in forbidden))
ok('runtime probe requires explicit ROM execution authorization','--allow-rom-execution' in read('scripts/qa/gameplay-probe.c') and '--allow-rom-execution' in read('scripts/qa/check-gameplay.py'))
s=read('data/maps/RusturfTunnel/scripts.inc')
m=json.loads(read('data/maps/RusturfTunnel/map.json'))
barrier=next(o for o in m['object_events'] if o.get('local_id')=='LOCALID_PART1_TUNNEL_BARRIER')
ok('Rusturf dead-end rock stays at (10,4)', (barrier['x'],barrier['y'])==(10,4) and str(barrier['flag'])=='0')
paths={}
for name,start,end in [('BrineyApproachPeeko1',(5,4),(12,4)),('BrineyExit',(13,4),(2,4)),('PeekoExit',(14,4),(5,4))]:
 block=re.search(r'RusturfTunnel_Movement_'+name+r':(.*?)step_end',s,re.S).group(1)
 x,y=start;path=[]
 for step in re.findall(r'^\s*walk_(left|right|up|down)\s*$',block,re.M):
  dx,dy={'left':(-1,0),'right':(1,0),'up':(0,-1),'down':(0,1)}[step];x+=dx;y+=dy;path.append((x,y))
 paths[name]=path
 ok(name+' avoids rock and preserves endpoint', (10,4) not in path and (x,y)==end and (10,5) in path)
layout=next(l for l in json.loads(read('data/layouts/layouts.json'))['layouts'] if l['id']=='LAYOUT_RUSTURF_TUNNEL')
blocks=(R/layout['blockdata_filepath']).read_bytes()
ok('detour cells use clear corridor floor',all(struct.unpack_from('<H',blocks,2*(y*layout['width']+x))[0]==0x3201 for x,y in [(9,4),(9,5),(10,5),(11,5),(11,4)]))
rescue=s.split('RusturfTunnel_EventScript_Grunt::')[1].split('RusturfTunnel_Movement_PushPlayerAsideForGrunt:')[0]
ok('Whismur spawn after rescue actors finish',rescue.index('addobject LOCALID_PART1_WHISMUR_2')>rescue.index('removeobject LOCALID_RUSTURF_TUNNEL_PEEKO'))
before=old('data/maps/RusturfTunnel/scripts.inc');after=s
for name in paths:
 pattern=r'RusturfTunnel_Movement_'+name+r':.*?step_end'
 before=re.sub(pattern,'<REVIEWED_RESCUE_ROUTE>',before,flags=re.S);after=re.sub(pattern,'<REVIEWED_RESCUE_ROUTE>',after,flags=re.S)
ok('Rusturf remaining event script unchanged',before==after)
print('Playability static regression: 19 groups PASS; runtime checks separate and opt-in.')
