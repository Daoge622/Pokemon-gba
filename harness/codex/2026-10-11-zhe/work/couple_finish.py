from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-actual-battle.state').read_bytes())
events=[]
for j in range(200):
 c.run(4,[8]);c.run(65)
 cb=c.rd(0x3002418)
 if j%5==0:
  c.shot(f'couple-finish-{j}.png');(ROOT/'couple-finish.state').write_bytes(c.state());print(j,hex(cb),flush=True)
 events.append({'cycle':j,'callback':hex(cb)})
 if cb==0x81b9521:
  for _ in range(5):c.run(4,[0]);c.run(50)
  c.shot('couple-finish-field.png');(ROOT/'couple-finish-field.state').write_bytes(c.state());print('FIELD',j,flush=True);break
else:c.shot('couple-finish-field.png');(ROOT/'couple-finish-field.state').write_bytes(c.state())
(ROOT/'couple-finish-log.json').write_text(json.dumps(events,indent=2))
