from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'fight.state').read_bytes())
def tap(k,n=1):
 for _ in range(n):c.run(4,[k]);c.run(50)
tap(0,2);tap(8,4);c.shot('continue-start.png')
tap(7);tap(5)
for j in range(140):
 tap(8)
 if j%5==0:
  c.shot(f'continue-{j:03d}.png');s=c.state();(ROOT/'continue.state').write_bytes(s);print(j,hex(struct.unpack_from('<I',s,0x19000+0x2418)[0]),flush=True)
