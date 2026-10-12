from runtime import *
label=sys.argv[3]
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'teamup-real-before-talk.state').read_bytes())
for j in range(12):
 c.run(4,[8]);c.run(75)
 print(label,j,hex(c.rd(0x3002418)),hex(c.rd(0x20000b4)),hex(c.rd(0x2000006,2)),flush=True)
 c.shot(f'{label}-{j}.png');(ROOT/f'{label}-{j}.state').write_bytes(c.state())
