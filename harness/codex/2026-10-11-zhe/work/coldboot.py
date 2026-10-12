from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(360)
c.run(4,[3]);c.run(80)
for j in range(30):
 c.run(4,[8]);c.run(80)
 if j%5==0:c.shot(f'cold-{j}.png');print(j,hex(c.rd(0x3002418)),flush=True)
 if c.rd(0x3002418)==0x81b9521:break
c.shot('cold-end.png');sb=c.rd(0x300238c)
print('cb',hex(c.rd(0x3002418)),'saveblock',hex(sb),'flag',hex(c.rd(sb+0x1270+0x1aa//8,1)),flush=True)
