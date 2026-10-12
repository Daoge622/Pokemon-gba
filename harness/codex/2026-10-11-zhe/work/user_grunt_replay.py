from runtime import *
rom=pathlib.Path('outputs/EmeraldStory-一周目完整版-组队与战后对话修复.gba')
c=Core(rom);c.run(100);c.load((ROOT/'user-base-load.state').read_bytes())
def snap(tag):
 c.shot('user-'+tag+'.png');(ROOT/('user-'+tag+'.state')).write_bytes(c.state())
 sb=c.rd(0x300238c)
 print(tag,'xy',c.rd(sb,2),c.rd(sb+2,2),'lock',c.rd(0x30008a7,1),'cb',hex(c.rd(0x3002418)),'trainer',c.rd(0x200008e,2),flush=True)
c.run(80,[5]);c.run(45);snap('base-south')
c.run(60,[7]);c.run(45);snap('base-east')
c.run(40,[5]);c.run(50);snap('base-south2')
for j in range(300):
 c.run(4,[8]);c.run(65)
 cb=c.rd(0x3002418)
 if cb==0x81be4f9:
  c.run(4,[0]);c.run(30);c.run(4,[0]);c.run(60)
  if c.rd(0x3002418)==0x81be4f9:
   c.run(4,[7]);c.run(30);c.run(4,[8]);c.run(30);c.run(4,[8]);c.run(100)
 if j%20==0:snap(f'grunt-{j}')
snap('grunt-final')
