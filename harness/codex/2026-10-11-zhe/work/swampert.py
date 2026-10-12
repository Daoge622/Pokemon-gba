from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'finish.state').read_bytes())
def tap(k,n=1):
 for _ in range(n):c.run(4,[k]);c.run(60)
tap(0);tap(5,2);tap(8,2);c.run(150);c.shot('swampert-start.png')
for j in range(220):
 tap(8)
 s=c.state();cb=struct.unpack_from('<I',s,0x19000+0x2418)[0]
 if j%5==0:c.shot(f'swampert-{j:03d}.png');(ROOT/'swampert.state').write_bytes(s);print(j,hex(cb),flush=True)
 if cb not in (0x809718d,0x81be4f9):
  c.run(120);c.shot('battle-ended.png');(ROOT/'battle-ended.state').write_bytes(c.state());print('END',hex(cb),flush=True);break
