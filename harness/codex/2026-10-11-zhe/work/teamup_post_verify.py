from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'teamup-victory-field.state').read_bytes())
def tap(key,n=1):
 for _ in range(n):c.run(4,[key]);c.run(50)
tap(8,4);c.run(80);tap(3);c.shot('teamup-post-start.png')
tap(5);tap(8);c.run(150);c.shot('teamup-post-party.png')
(ROOT/'teamup-post-party.state').write_bytes(c.state())
tap(0,2);c.run(150);c.run(16,[7]);c.run(45);c.shot('teamup-post-walk.png')
(ROOT/'teamup-post-walk.state').write_bytes(c.state())
sb=c.rd(0x300238c);print('cb2',hex(c.rd(0x3002418)),'xy',c.rd(sb,2),c.rd(sb+2,2),'count',c.rd(0x20207b4,1),'flag',hex(c.rd(sb+0x1270+0x4ec//8,1)),flush=True)
