from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'battle-ended.state').read_bytes())
def tap(k,n=1):
 for _ in range(n):c.run(4,[k]);c.run(70)
tap(7);tap(5,2);tap(8,2);c.run(180);c.shot('water-start.png')
for j in range(300):
 tap(8)
 s=c.state();cb=struct.unpack_from('<I',s,0x19000+0x2418)[0]
 if j%5==0:c.shot(f'water-{j:03d}.png');(ROOT/'water.state').write_bytes(s);print(j,hex(cb),flush=True)
 if j>20 and cb==0x81be4f9:tap(0,3)
c.shot('water-end.png')
