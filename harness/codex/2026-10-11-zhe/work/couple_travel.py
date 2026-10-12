from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-flee.state').read_bytes())
def tap(k,n=1):
 for _ in range(n):c.run(4,[k]);c.run(70)
tap(5);tap(7);tap(8);c.run(250);c.shot('couple-flee.png');print('flee cb',hex(c.rd(0x3002418)),flush=True)
(ROOT/'couple-flee.state').write_bytes(c.state())
