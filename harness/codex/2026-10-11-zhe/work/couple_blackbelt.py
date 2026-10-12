from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-reach-battle.state').read_bytes())
for _ in range(6):c.run(4,[0]);c.run(80)
c.run(4,[8]);c.run(30);c.shot('couple-blackbelt-moves.png');(ROOT/'couple-blackbelt-moves.state').write_bytes(c.state())
c.run(4,[4]);c.run(15)
for j in range(150):
 c.run(4,[8]);c.run(80)
 if j%20==0:c.shot(f'couple-blackbelt-{j}.png');print(j,hex(c.rd(0x3002418)),flush=True)
 if c.rd(0x3002418)==0x81b9521:
  for _ in range(4):c.run(4,[0]);c.run(40)
  print('field',j,flush=True);break
c.shot('couple-blackbelt-end.png');(ROOT/'couple-blackbelt-end.state').write_bytes(c.state())
