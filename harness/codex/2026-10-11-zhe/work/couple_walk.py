from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-flee.state').read_bytes())
c.run(4,[8]);c.run(180)
def snap(n):
 c.shot('couple-walk-'+n+'.png');sb=c.rd(0x300238c);print(n,'xy',(c.rd(sb,2),c.rd(sb+2,2)),'cb',hex(c.rd(0x3002418)),flush=True);(ROOT/('couple-walk-'+n+'.state')).write_bytes(c.state())
snap('field')
c.run(35,[5]);c.run(5);snap('y7')
c.run(35,[7]);c.run(5);snap('x7')
c.run(50,[5]);c.run(5);snap('y10')
c.run(65,[6]);c.run(5);snap('x3')
