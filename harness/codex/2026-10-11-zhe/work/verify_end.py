from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'water.state').read_bytes())
c.run(2)
sb=c.rd(0x0300238c);print('saveblock1',hex(sb),'flagbyte',hex(c.rd(sb+0x1270+0x1aa//8,1)), 'callback',hex(c.rd(0x03002418)),flush=True)
for i in range(20):c.run(4,[0]);c.run(30)
c.run(120);c.shot('postbattle-free.png')
print('context',hex(c.rd(0x3001ae8)),'mode',c.rd(0x3001ae1,1),'callback',hex(c.rd(0x03002418)),'flags',hex(c.rd(sb+0x1270+0x1aa//8,1)),flush=True)
(ROOT/'postbattle-free.state').write_bytes(c.state())
c.run(50,[5]);c.run(50);c.shot('postbattle-walk.png');print('after down','mode',c.rd(0x3001ae1,1),'script',hex(c.rd(0x3001ae8)),flush=True)
