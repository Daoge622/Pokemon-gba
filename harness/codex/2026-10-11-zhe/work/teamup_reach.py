from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'teamup-outside.state').read_bytes())
def snap(name):
 sb=c.rd(0x300238c);print(name,c.rd(sb,2),c.rd(sb+2,2),hex(c.rd(0x3002418)),flush=True)
 c.shot(name+'.png');(ROOT/(name+'.state')).write_bytes(c.state())
for name,key,n in [('down',5,16),('east',7,288),('north',4,112),('west',6,112)]:
 c.run(n,[key]);c.run(150);snap('teamup-route-'+name)
