from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'teamup-fixed-6.state').read_bytes())
def tap(k,n=1):
 for _ in range(n):c.run(4,[k]);c.run(40)
def snap(name):
 c.shot(name+'.png');(ROOT/(name+'.state')).write_bytes(c.state())
 print(name,'count',c.rd(0x20207b4,1),'order',hex(c.rd(0x2020c34)),hex(c.rd(0x3002418)),flush=True)
if len(sys.argv)>3 and sys.argv[3]=='cancel':
 tap(0);tap(8);c.run(200);snap('teamup-cancel');c.run(16,[7]);c.run(30);snap('teamup-cancel-walk')
else:
 tap(7);tap(5,2);tap(8,2);snap('teamup-selected-first')
 tap(4,2);tap(8,2);snap('teamup-selected-second')
 tap(5,3);tap(8,2);snap('teamup-selected-third')
 snap('teamup-confirm-cursor');tap(8);c.run(350);snap('teamup-fixed-battle')
