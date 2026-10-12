"""Controlled test setup: engine warp + script entry. Not a normal story playthrough."""
from runtime import *
name=sys.argv[3];mode=sys.argv[4] if len(sys.argv)>4 else 'cancel'
cases={'Route119':(0,34,11,35,0x083993a0), 'LavaridgeTown':(0,12,8,7,0x083995ac), 'Steven':(14,10,5,5,0x0830d180)}
group,num,x,y,entry=cases[name]
test_rom=bytearray(pathlib.Path(sys.argv[1]).read_bytes());test_offset=0x1b02000
test_script=b'\x68\x39'+bytes([group,num,255])+struct.pack('<2H',x,y)+bytes.fromhex('276b02')
assert set(test_rom[test_offset:test_offset+len(test_script)])=={255}
test_rom[test_offset:test_offset+len(test_script)]=test_script
path=ROOT/f'fixture-{name}.gba';path.write_bytes(test_rom)
c=Core(path,sys.argv[2]);c.run(100);c.load((ROOT/'teamup-fixed-5.state').read_bytes())
def jump(address):
 state=c.state();p=0x19000+0xca4
 state[p:p+4]=bytes([0,1,0,0]);struct.pack_into('<2I',state,p+4,0,address)
 c.load(state)
def tap(key,n=1):
 for _ in range(n):c.run(4,[key]);c.run(45)
def snap(suffix):
 tag=f'fixture-{name}-{suffix}';c.shot(tag+'.png');(ROOT/(tag+'.state')).write_bytes(c.state())
 sb=c.rd(0x300238c);print(tag,'map',c.rd(sb+4,1),c.rd(sb+5,1),'xy',c.rd(sb,2),c.rd(sb+2,2),'count',c.rd(0x20207b4,1),'cb',hex(c.rd(0x3002418)),'order',hex(c.rd(0x2020c34)),flush=True)
jump(0x8000000+test_offset);c.run(400);snap('warp')
# A second warp from an active script sets up entry after map scripts finish.
state=c.state();p=0x19000+0xca4;state[p:p+4]=bytes([0,1,0,0]);struct.pack_into('<2I',state,p+4,0,entry)
# Audited ScriptContext_SetupScript globals: status 030008a6, field lock 030008a7.
state[0x19000+0x8a6:0x19000+0x8a8]=bytes([0,1])
if name=='Steven':state[0x21000+0x20c34:0x21000+0x20c38]=bytes([2,4,5,0])
c.load(state);c.run(200)
if name=='Steven':
 # Its original map script chooses first; reproduce that selected order here.
 c.run(400);snap('preselected')
else:
 snap('menu')
 if mode=='cancel':tap(0);tap(8);c.run(250);snap('cancel')
 else:
  tap(7);tap(8,2);tap(5,2);tap(8,2);tap(5);tap(8,2);snap('chosen');tap(8);c.run(400);snap('battle')
