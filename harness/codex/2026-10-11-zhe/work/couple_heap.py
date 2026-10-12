from pathlib import Path
import struct,json
def audit(name):
 b=Path('work/'+name).read_bytes()[0x21000:0x61000]
 def u32(p):return struct.unpack_from('<I',b,p)[0]
 heads=[p for p in range(0,len(b)-16,4) if b[p+2:p+4]==b'\xa3\xa3' and u32(p+8)==0x2000000+p]
 assert len(heads)==1,heads
 head=heads[0];p=head;seen=set();blocks=[];errors=[]
 while p not in seen:
  seen.add(p);magic=struct.unpack_from('<H',b,p+2)[0];size=u32(p+4)&0x3ffff;prev=u32(p+8)-0x2000000;next_=u32(p+12)-0x2000000
  allocated=b[p]&1;blocks.append({'address':hex(p+0x2000000),'size':size,'allocated':bool(allocated)})
  if magic!=0xa3a3:errors.append(['magic',hex(p+0x2000000)])
  if next_==head:
   if p+16+size!=head+0x1c500:errors.append(['end',hex(p+16+size),hex(head+0x1c500)])
   break
  if next_!=p+16+size:errors.append(['noncontiguous',hex(p+0x2000000),hex(next_+0x2000000)]);break
  if u32(next_+8)-0x2000000!=p:errors.append(['prev pointer',hex(next_+0x2000000)])
  p=next_
 return {'state':name,'head':hex(head+0x2000000),'blocks':len(blocks),'allocated_bytes':sum(x['size'] for x in blocks if x['allocated']),'errors':errors}
result=[audit(n) for n in ['couple-actual-battle.state','couple-win-0.state','couple-win-field.state','couple-verified-final.state']]
Path('work/couple-heap-audit.json').write_text(json.dumps(result,indent=2));print(json.dumps(result,indent=2))
