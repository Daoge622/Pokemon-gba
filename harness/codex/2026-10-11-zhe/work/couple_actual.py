from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-blackbelt-end.state').read_bytes())
def move(k,n):c.run(n,[k]);c.run(10)
move(7,16);move(5,50);move(6,65);c.shot('couple-actual-near.png')
for j in range(22):move(8,4);c.run(70)
c.shot('couple-actual-battle.png');(ROOT/'couple-actual-battle.state').write_bytes(c.state())
sb=c.rd(0x300238c);print('pos',c.rd(sb,2),c.rd(sb+2,2),'cb',hex(c.rd(0x3002418)),'trainerA',c.rd(0x200008e,2),'trainerB',c.rd(0x200009d,2),flush=True)
