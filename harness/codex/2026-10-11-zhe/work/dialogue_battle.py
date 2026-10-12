from runtime import *
index=int(sys.argv[1]);name=f'dialogue-fixed-{index}-unbeaten'
c=Core(ROOT/(name+'.gba'));c.run(100);c.load((ROOT/(name+'-after-close.state')).read_bytes())
log=[]
for j in range(200):
 c.run(4,[8]);c.run(70)
 cb=c.rd(0x3002418)
 if cb==0x81be4f9:
  c.run(4,[0]);c.run(30);c.run(4,[0]);c.run(60)
  if c.rd(0x3002418)==0x81be4f9:
   c.run(4,[7]);c.run(30);c.run(4,[8]);c.run(30);c.run(4,[8]);c.run(100)
  cb=c.rd(0x3002418)
 if j%20==0:
  c.shot(name+f'-fight-{j}.png');print(j,hex(cb),flush=True)
 if cb==0x81b9521:
  for k in range(25):
   c.run(4,[8]);c.run(25)
   if c.rd(0x30008a7,1)==0:break
  c.run(600)
  c.shot(name+'-victory.png');(ROOT/(name+'-victory.state')).write_bytes(c.state())
  sb=c.rd(0x300238c);site=json.loads(pathlib.Path('outputs/dialogue-rom-patch.json').read_text(encoding='utf-8'))['sites'][index];f=site['trainer']+0x500
  result={'index':index,'cycles':j,'field':hex(c.rd(0x3002418)),'lock':c.rd(0x30008a7,1),'trainer_defeated':bool(c.rd(sb+0x1270+f//8,1)&(1<<(f%8))),'fixture':True,'description':'normal buttons through battle; fixture warp/flags/pose only, no enemy/player HP edits'}
  pathlib.Path('outputs/'+name+'-battle-verification.json').write_text(json.dumps(result,indent=2),encoding='utf-8');print(result,flush=True);break
else:
 c.shot(name+'-battle-pending.png');(ROOT/(name+'-battle-pending.state')).write_bytes(c.state());print('PENDING')
