from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-walk-x3.state').read_bytes())
for j in range(24):c.run(4,[8]);c.run(80)
c.shot('couple-otherbattle.png');print('cb',hex(c.rd(0x3002418)),flush=True)
(ROOT/'couple-otherbattle.state').write_bytes(c.state())
