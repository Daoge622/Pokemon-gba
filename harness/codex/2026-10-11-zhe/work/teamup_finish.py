from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'teamup-fixed-battle.state').read_bytes())
log=[]
for j in range(170):
 c.run(4,[8]);c.run(95)
 cb=c.rd(0x3002418);count=c.rd(0x20207b4,1)
 if j%10==0:
  c.shot(f'teamup-finish-{j}.png');(ROOT/f'teamup-finish-{j}.state').write_bytes(c.state());print(j,hex(cb),count,flush=True)
 log.append({'cycle':j,'cb2':hex(cb),'count':count,'result':c.rd(0x2000006,2)})
 if count==6 and cb==0x81b9521:
  c.run(120);c.shot('teamup-victory-field.png');(ROOT/'teamup-victory-field.state').write_bytes(c.state());print('finished',j,flush=True);break
(ROOT/'teamup-finish-log.json').write_text(json.dumps(log,indent=2))
