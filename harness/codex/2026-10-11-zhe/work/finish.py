from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'continue.state').read_bytes())
def tap(k,n=1):
 for _ in range(n):c.run(4,[k]);c.run(50)
tap(0,3)
for j in range(400):
 tap(8)
 s=c.state();cb=struct.unpack_from('<I',s,0x19000+0x2418)[0]
 if j%5==0:c.shot(f'finish-{j:03d}.png');(ROOT/'finish.state').write_bytes(s);print(j,hex(cb),flush=True)
 if cb==0x81be4f9:tap(0,3)
 if cb not in (0x809718d,0x81be4f9):
  c.run(300);c.shot('battle-ended.png');(ROOT/'battle-ended.state').write_bytes(c.state());print('END',hex(cb),flush=True);break
