from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-otherbattle.state').read_bytes())
for j in range(180):
 c.run(4,[8]);c.run(80)
 cb=c.rd(0x3002418)
 if j%15==0:c.shot(f'couple-other-{j}.png');print(j,hex(cb),flush=True)
 if cb==0x81b9521:
  c.run(4,[0]);c.run(80);c.shot('couple-other-ended.png');(ROOT/'couple-other-ended.state').write_bytes(c.state());print('FIELD',j,flush=True);break
else:(ROOT/'couple-other-ended.state').write_bytes(c.state());c.shot('couple-other-ended.png')
