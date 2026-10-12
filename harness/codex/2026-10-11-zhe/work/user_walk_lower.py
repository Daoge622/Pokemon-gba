from runtime import *
c=Core(pathlib.Path('outputs/EmeraldStory-一周目完整版-组队与战后对话修复.gba'));c.run(100);c.load((ROOT/'user-gloves-east.state').read_bytes())
def snapshot(tag):
 c.shot('user-'+tag+'.png');(ROOT/('user-'+tag+'.state')).write_bytes(c.state())
 sb=c.rd(0x300238c);print(tag,'xy',c.rd(sb,2),c.rd(sb+2,2),'trainer',c.rd(0x200008e,2),'flags',hex(c.rd(0x20000b4)),'lock',c.rd(0x30008a7,1),flush=True)
def finish():
 for j in range(250):
  c.run(4,[8]);c.run(70)
  if c.rd(0x3002418)==0x81be4f9:
   c.run(4,[0]);c.run(35);c.run(4,[0]);c.run(60)
  if c.rd(0x3002418)==0x81b9521:
   if c.rd(0x30008a7,1)==0:return
 c.shot('user-stalled.png');(ROOT/'user-stalled.state').write_bytes(c.state());raise RuntimeError('did not return free field')
finish();snapshot('wild2-done')
for j in range(5):
 c.run(65,[5]);c.run(60)
 if c.rd(0x3002418)!=0x81b9521 or c.rd(0x30008a7,1):finish()
 snapshot('descend-'+str(j))
 if c.rd(c.rd(0x300238c)+2,2)>=15:break
c.run(60,[7]);c.run(60)
snapshot('gloves-near')
