from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'postbattle-free.state').read_bytes());c.run(5)
c.run(60,[4]);c.run(150);c.shot('couple-2f-entry.png')
print('cb',hex(c.rd(0x3002418)),flush=True)
(ROOT/'couple-2f-entry.state').write_bytes(c.state())
