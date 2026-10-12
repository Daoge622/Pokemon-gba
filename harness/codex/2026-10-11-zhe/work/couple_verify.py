from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-win-field.state').read_bytes())
def tap(k,n=1):
 for _ in range(n):c.run(4,[k]);c.run(55)
sb=c.rd(0x300238c);print('initial flag',hex(c.rd(sb+0x1270+0x780//8,1)),flush=True)
# Walk and return to the same couple using game inputs.
c.run(16,[5]);c.run(40);c.shot('couple-verified-walk.png');print('walk xy',c.rd(sb,2),c.rd(sb+2,2),flush=True)
c.run(16,[4]);c.run(40);tap(8);tap(8,6);c.shot('couple-postdialogue.png');tap(0,4)
tap(3);c.shot('couple-verified-menu.png');tap(5);tap(8);c.run(80);c.shot('couple-verified-bag.png');tap(0,3);c.run(150);c.shot('couple-verified-final.png')
sb=c.rd(0x300238c)
print('final cb',hex(c.rd(0x3002418)),'flag',hex(c.rd(sb+0x1270+0x780//8,1)),flush=True)
(ROOT/'couple-verified-final.state').write_bytes(c.state())
