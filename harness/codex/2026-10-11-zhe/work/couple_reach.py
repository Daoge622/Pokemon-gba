from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-other-ended.state').read_bytes())
def move(k,n):c.run(n,[k]);c.run(10)
move(5,16);move(7,32);move(5,48);move(6,64);c.shot('couple-near.png')
for j in range(20):move(8,4);c.run(65)
c.shot('couple-reach-battle.png');(ROOT/'couple-reach-battle.state').write_bytes(c.state())
sb=c.rd(0x300238c);print('pos',c.rd(sb,2),c.rd(sb+2,2),'cb',hex(c.rd(0x3002418)),'trainerA',c.rd(0x200008e,2),'trainerB',c.rd(0x200009d,2),flush=True)
