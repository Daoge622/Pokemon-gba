from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'postbattle-free.state').read_bytes())
def snap(name):
 sb=c.rd(0x300238c);print(name,c.rd(sb+4,1),c.rd(sb+5,1),c.rd(sb,2),c.rd(sb+2,2),hex(c.rd(0x3002418)),flush=True)
 c.shot(name+'.png');(ROOT/(name+'.state')).write_bytes(c.state())
c.run(128,[6]);c.run(50);snap('teamup-1f-left')
c.run(48,[5]);c.run(180);snap('teamup-exterior-entry')
c.run(96,[6]);c.run(50);snap('teamup-1f-exit-near')
c.run(32,[5]);c.run(180);snap('teamup-outside')
