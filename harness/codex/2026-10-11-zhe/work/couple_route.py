from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-before-talk.state').read_bytes())
def snap(n):
 c.shot('couple-route-'+n+'.png');sb=c.rd(0x300238c);print(n,'xy',(c.rd(sb,2),c.rd(sb+2,2)),'cb',hex(c.rd(0x3002418)),flush=True);(ROOT/('couple-route-'+n+'.state')).write_bytes(c.state())
def tap(k,frames):c.run(frames,[k]);c.run(10)
tap(7,32);snap('right')
tap(7,32);snap('right2')
tap(5,32);snap('down')
for j in range(18):tap(8,4);c.run(60)
snap('dialogue')
