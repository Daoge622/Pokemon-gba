"""Actual NPC movement; fixture warp only, no isolated sight/pose changes."""
from runtime import *
from pathlib import Path
name=sys.argv[1] if len(sys.argv)>1 else 'gloves'
kind=sys.argv[2] if len(sys.argv)>2 else 'v1'
positions={'gloves':(12,15),'bento':(18,20),'girl':(9,8),'aquagrunt':(28,17)}
group,num=(24,24) if name=='aquagrunt' else (24,87)
base=Path('outputs/EmeraldStory-一周目完整版-组队与战后对话修复.gba') if kind=='v1' else Path(sys.argv[2])
rom=bytearray(base.read_bytes());x,y=positions[name];o=0x1b02000
script=bytes([0x68,0x39,group,num,255])+struct.pack('<2H',x,y)+bytes.fromhex('276b02')
assert set(rom[o:o+len(script)])=={255};rom[o:o+len(script)]=script
tag=f'moving-{name}-{kind}' if kind=='v1' else f'moving-{name}-candidate'
path=ROOT/(tag+'.gba');path.write_bytes(rom);c=Core(path);c.run(100);c.load((ROOT/'teamup-loss-healed.state').read_bytes())
state=c.state();sb=struct.unpack_from('<I',state,0x19000+0x238c)[0]
def flag(n,value):
 q=0x21000+sb-0x2000000+0x1270+n//8
 if value:state[q]|=1<<(n%8)
 else:state[q]&=255^(1<<(n%8))
for n in [719,720,729,718,3,1,2,4]:flag(n+0x500,False)
maps=json.loads((ROOT/'maps.json').read_text());m=maps['AquaHideout_B1F' if name=='aquagrunt' else 'MagmaHideout_2F_1R']
for j in range(m['counts'][0]):
 q=m['pointers'][0]-0x8000000+j*24;hide=struct.unpack_from('<H',rom,q+20)[0]
 if hide:flag(hide,False)
flag(0x4ec,True)
q=0x19000+0xca4;state[q:q+4]=bytes([0,1,0,0]);struct.pack_into('<2I',state,q+4,0,0x8000000+o)
state[0x19000+0x8a6:0x19000+0x8a8]=bytes([0,1]);c.load(state);c.run(500)
c.shot(tag+'-entry.png');(ROOT/(tag+'-entry.state')).write_bytes(c.state())
for j in range(260):
 c.run(4,[8]);c.run(65)
 cb=c.rd(0x3002418)
 if cb==0x81be4f9:
  c.run(4,[0]);c.run(30);c.run(4,[0]);c.run(60)
  if c.rd(0x3002418)==0x81be4f9:
   c.run(4,[7]);c.run(30);c.run(4,[8]);c.run(30);c.run(4,[8]);c.run(100)
 if j%20==0:
  c.shot(tag+f'-{j}.png');(ROOT/(tag+f'-{j}.state')).write_bytes(c.state())
  sb=c.rd(0x300238c);print(j,'cb',hex(c.rd(0x3002418)),'lock',c.rd(0x30008a7,1),'trainer',c.rd(0x200008e,2),'ctx',c.state()[0x19000+0xca4:0x19000+0xca4+12].hex(),flush=True)
c.shot(tag+'-end.png');(ROOT/(tag+'-end.state')).write_bytes(c.state())
