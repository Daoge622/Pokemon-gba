from pathlib import Path
import json,struct,collections,hashlib,re
R=Path(r'E:\Pekemon Gba\project');b=Path(r'C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba').read_bytes()
mp=json.loads(Path('work/maps.json').read_text());layouts={int(k):v for k,v in json.loads(Path('work/script-layouts.json').read_text()).items()}
layouts[0x25]={'macro':'special','size':3,'fields':[(2,'special')]}
layouts[0x26]={'macro':'specialvar','size':5,'fields':[(2,'output'),(2,'special')]}
source_special_count=len(re.findall(r'^\s*def_special\s+', (R/'data/specials.inc').read_text(),re.M))
# Actual binary gSpecials follows special vars and ends at gStdScripts.
special_count=(0x2d2464-0x2d19bc)//4
def u16(p):return struct.unpack_from('<H',b,p)[0]
def u32(p):return struct.unpack_from('<I',b,p)[0]
def valid(a):return 0x8000000<=a<0xa000000
std=[u32(0x2d2464+i*4) for i in range(13)]
roots={};errors=[];deferred=[];seen={};battles={};queue=collections.deque()
def enqueue(a,origin):
 if not a:return
 if not valid(a):errors.append({'kind':'invalid script pointer','address':hex(a),'origin':origin});return
 if a not in roots:roots[a]=origin;queue.append(a)
for name,m in mp.items():
 for kind,size,offset in [(0,24,16),(2,16,12),(3,12,8)]:
  for j in range(m['counts'][kind]):
   p=m['pointers'][kind]-0x8000000+j*size
   if kind==3 and b[p+5]>=5:continue
   enqueue(u32(p+offset),f'{name}/{kind}/{j}')
 p=m['scripts']-0x8000000
 for j in range(16):
  typ=b[p];p+=1
  if not typ:break
  if typ>7:errors.append({'kind':'map script type','map':name,'type':typ});break
  target=u32(p);p+=4
  if typ in (2,4):
   q=target-0x8000000
   for k in range(32):
    if u16(q)==0:break
    enqueue(u32(q+4),f'{name}/map table/{typ}/{k}');q+=8
  else:enqueue(target,f'{name}/map script/{typ}')
for a in std:enqueue(a,'standard script')
while queue:
 a=queue.popleft();origin=roots[a];p=a-0x8000000
 pending_warp=False
 for step in range(20000):
  if p in seen:break
  op=b[p];address=hex(p+0x8000000)
  if op==0xe3:
   # Header has eleven operand bytes, followed by option-count pointers.
   layouts[op]={'macro':'dynmultichoice','size':12+4*b[p+11],'fields':[]}
  if op not in layouts:
   deferred.append({'address':address,'opcode':hex(op),'origin':origin,'reason':'unimplemented variable format or unsupported opcode'});break
  layout=layouts[op];seen[p]=op;sz=layout['size'];end=p+sz
  if op==0x23 and u32(p+1)==0x0bb00401:
   p+=6;continue # existing cant_see_if consumes one comparison byte
  if op==0x23:
   ptr=u32(p+1);canonical=ptr-0x2000000 if (ptr&0xe000000)==0xa000000 else ptr
   if not valid(canonical) or not ptr&1:errors.append({'kind':'native pointer','address':address,'pointer':hex(ptr),'origin':origin})
   deferred.append({'address':address,'function':hex(canonical),'origin':origin,'reason':'native may consume inline operands; stop instead of decoding operands as opcodes'});break
  if op in (4,5):enqueue(u32(p+1),origin)
  if op in (6,7):
   if b[p+1]>5:errors.append({'kind':'condition','address':address,'value':b[p+1],'origin':origin})
   enqueue(u32(p+2),origin)
  if op in (8,9,10,11):
   index=b[end-1]
   if index>=len(std):errors.append({'kind':'standard script index','address':address,'value':index,'origin':origin})
   else:enqueue(std[index],origin)
  if op in (0x25,0x26):
   index=u16(end-2)
   if index>=special_count:errors.append({'kind':'special index','address':address,'value':index,'origin':origin})
  if op==0x5c:
   assert sz==41,sz
   flags=b[p+1];trainers=[u16(p+3),u16(p+18)];battles[address]={'origin':origin,'flags':flags,'trainers':trainers}
   for delta in (13,28):enqueue(u32(p+delta),origin+'/post battle')
   for delta in (5,9,20,24,32,36):
    ptr=u32(p+delta)
    if ptr and not valid(ptr):errors.append({'kind':'trainer text','address':address,'pointer':hex(ptr),'origin':origin})
   if trainers[0]==0:errors.append({'kind':'trainer A is none','address':address,'origin':origin})
  if op in (0x39,0x3a,0x3b,0x3c,0x3d):pending_warp=True
  if op==0x27 and pending_warp:break
  if op in (2,3,5,8,0xc,0xd,0x5e,0x5f):break
  p=end
result={'sha256':hashlib.sha256(b).hexdigest(),'root_count':len(roots),'decoded_commands':len(seen),'trainer_battles':len(battles),'source_special_count':source_special_count,'actual_special_count':special_count,'errors':errors,'deferred':deferred,'battles':battles}
Path('outputs/dialogue-script-audit.json').write_text(json.dumps(result,ensure_ascii=False,indent=2))
print(json.dumps({k:v for k,v in result.items() if k not in ('battles','deferred')},ensure_ascii=False,indent=2));print('deferred',len(deferred),'native functions',len({x.get('function') for x in deferred}))
