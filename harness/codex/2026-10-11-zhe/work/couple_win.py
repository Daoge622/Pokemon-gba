from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'couple-move-change.state').read_bytes());c.run(4,[7]);c.run(30)
events=[]
for j in range(130):
 c.run(4,[8]);c.run(65);cb=c.rd(0x3002418)
 if j%3==0:c.shot(f'couple-win-{j}.png');(ROOT/f'couple-win-{j}.state').write_bytes(c.state());print(j,hex(cb),flush=True)
 events.append({'cycle':j,'callback':hex(cb)})
 if cb==0x81b9521:
  for _ in range(5):c.run(4,[0]);c.run(50)
  c.shot('couple-win-field.png');(ROOT/'couple-win-field.state').write_bytes(c.state());print('FIELD',j,flush=True);break
else:c.shot('couple-win-field.png');(ROOT/'couple-win-field.state').write_bytes(c.state())
(ROOT/'couple-win-log.json').write_text(json.dumps(events,indent=2))
