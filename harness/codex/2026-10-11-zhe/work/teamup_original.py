from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'teamup-route-west.state').read_bytes())
c.run(2,[4]);c.run(20)
c.shot('teamup-before-talk.png');(ROOT/'teamup-before-talk.state').write_bytes(c.state())
for j in range(18):
 c.run(4,[8]);c.run(75)
 if j%2==0:
  c.shot(f'teamup-original-{j}.png');(ROOT/f'teamup-original-{j}.state').write_bytes(c.state())
 print(j,hex(c.rd(0x3002418)),hex(c.rd(0x20000b4)),hex(c.rd(0x2000006,2)),flush=True)
