from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.import_myboy(sys.argv[3]);c.run(30);c.run(4,[4]);c.run(20)
last=None
for j in range(180):
 c.run(4,[8]);c.run(80)
 if j%5==0:
  s=c.state();cb=struct.unpack_from('<I',s,0x19000+0x2418)[0]
  print(j,hex(cb),flush=True);c.shot(f'fight-{j:03d}.png');(ROOT/'fight.state').write_bytes(s)
  if cb!=last:last=cb
c.shot('fight-end.png')
