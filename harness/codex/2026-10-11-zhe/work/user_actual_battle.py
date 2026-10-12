from runtime import *
entry=sys.argv[1];tag=sys.argv[2]
c=Core(pathlib.Path('outputs/EmeraldStory-一周目完整版-组队与战后对话修复.gba'));c.run(100);c.load((ROOT/entry).read_bytes())
trace=[];last=0;inbattle=False
for j in range(250):
 c.run(4,[8]);c.run(70)
 cb=c.rd(0x3002418)
 if cb==0x81be4f9:
  c.run(4,[0]);c.run(35);c.run(4,[0]);c.run(60)
  if c.rd(0x3002418)==0x81be4f9:c.run(4,[7]);c.run(35);c.run(4,[8]);c.run(35);c.run(4,[8]);c.run(80)
 if cb==0x809718d:inbattle=True
 if cb!=last:
  trace.append({'cycle':j,'cb':hex(cb),'trainer':c.rd(0x200008e,2),'lock':c.rd(0x30008a7,1)})
  print(trace[-1],flush=True);last=cb
 if inbattle and cb==0x81b9521:
  (ROOT/(tag+'-return.state')).write_bytes(c.state());c.shot(tag+'-return.png')
  for k in range(30):
   if c.rd(0x30008a7,1)==0:break
   c.run(4,[8]);c.run(30)
  c.run(1200)
  break
c.shot(tag+'-end.png');(ROOT/(tag+'-end.state')).write_bytes(c.state())
sb=c.rd(0x300238c);result={'trace':trace,'inbattle':inbattle,'callback':hex(c.rd(0x3002418)),'lock':c.rd(0x30008a7,1),'ctx':c.state()[0x19000+0xca4:0x19000+0xca4+12].hex(),'flags':{str(t):bool(c.rd(sb+0x1270+(0x500+t)//8,1)&(1<<((0x500+t)%8))) for t in [719,720,729]},'xy':[c.rd(sb,2),c.rd(sb+2,2)],'test':'user desktop save, actual delivered ROM, normal input, no warp/flag/party/pose edits'}
pathlib.Path('outputs/'+tag+'-verification.json').write_text(json.dumps(result,indent=2),encoding='utf-8');print(result,flush=True)
