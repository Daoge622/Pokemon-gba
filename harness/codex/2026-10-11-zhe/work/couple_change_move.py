from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-finish.state').read_bytes())
def tap(k):c.run(4,[k]);c.run(40)
tap(0);tap(0);tap(8);tap(4);c.shot('couple-move-change.png');(ROOT/'couple-move-change.state').write_bytes(c.state())
