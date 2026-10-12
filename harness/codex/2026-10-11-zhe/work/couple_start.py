from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-2f-entry.state').read_bytes());c.run(200,[5]);c.run(40);c.shot('couple-before-talk.png')
(ROOT/'couple-before-talk.state').write_bytes(c.state())
for j in range(14):
 c.run(4,[8]);c.run(80)
 if j in (2,6,13):c.shot(f'couple-intro-{j}.png');print(j,hex(c.rd(0x3002418)),flush=True)
(ROOT/'couple-battle.state').write_bytes(c.state())
