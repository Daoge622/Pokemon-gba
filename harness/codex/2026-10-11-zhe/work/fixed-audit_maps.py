import pathlib,struct,json,re,collections
R=pathlib.Path(r'E:\Pekemon Gba\project');b=pathlib.Path(r'C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队选宝可梦修复.gba').read_bytes();mp=json.loads(pathlib.Path('work/maps.json').read_text())
def refs(p):
 i=-1;found=[]
 while True:
  i=b.find(p,i+1)
  if i<0:return found
  found.append(i)
def u32(o):return struct.unpack_from('<I',b,o)[0]
def u16(o):return struct.unpack_from('<H',b,o)[0]
def valid(a,n=1):return 0x8000000<=a and a+n<=0xa000000
names=re.findall(r'^\s*(OBJ_EVENT_GFX_\w+|NUM_OBJ_EVENT_GFX)\s*,', (R/'include/constants/event_objects.h').read_text(),re.M);gfx={n:i for i,n in enumerate(names)};num=gfx['NUM_OBJ_EVENT_GFX']
candidates=[]
for info in refs(bytes.fromhex('ffff00110211000210002000')):
 for p in refs(struct.pack('<I',info+0x8000000)):
  if p%4:continue
  values=[u32(p+4*j) for j in range(num)]
  if all(x==0 or valid(x,36) for x in values) and sum(x!=0 for x in values)>100:candidates.append(p)
assert len(candidates)==1,candidates;table=candidates[0];print('gfx',hex(table+0x8000000),'count',num)
issues=[];source_diff=[];objects=warps=coords=bg=0;byid={(v['group'],v['num']):k for k,v in mp.items()}
for name,m in mp.items():
 counts=m['counts'];ptrs=m['pointers'];objects+=counts[0];warps+=counts[1];coords+=counts[2];bg+=counts[3]
 for j,(cnt,p,siz) in enumerate(zip(counts,ptrs,[24,8,16,12])):
  if cnt and not valid(p,cnt*siz):issues.append([name,'event array',j,p,cnt])
 source=json.loads((R/'data/maps'/name/'map.json').read_text())
 locals=[]
 for j in range(counts[0]):
  p=ptrs[0]-0x8000000+j*24;local=b[p];gf=u16(p+1);script=u32(p+16);flag=u16(p+20);locals.append(local)
  if not valid(script) and script!=0:issues.append([name,'object script pointer',j,script])
  if gf<num and u32(table+gf*4)==0:issues.append([name,'NULL graphics',j,local,gf,script])
  if not(gf<num or num+1<=gf<=num+16 or gf&0x4000):issues.append([name,'undefined graphics',j,local,gf])
  if j<len(source.get('object_events',[])):
   sg=source['object_events'][j]['graphics_id']
   if sg in gfx and gf!=gfx[sg]:source_diff.append([name,j,'graphics',sg,gf])
 for local,c in collections.Counter(locals).items():
  if c>1:issues.append([name,'duplicate local id',local])
 for j in range(counts[1]):
  p=ptrs[1]-0x8000000+j*8;wid,num_,grp=b[p+5:p+8]
  if (grp,num_)==(127,127):continue
  if (grp,num_) not in byid:issues.append([name,'warp target missing',j,grp,num_]);continue
  dest=byid[(grp,num_)]
  if wid>=mp[dest]['counts'][1] and wid!=255:issues.append([name,'warp index',j,wid,dest])
 for kind in [2,3]:
  for j in range(counts[kind]):
   p=ptrs[kind]-0x8000000+j*([16,12][kind-2]);script=u32(p+([12,8][kind-2]))
   if kind==3 and b[p+5]>=5:continue
   if script!=0 and not valid(script):issues.append([name,'script pointer',kind,j,hex(script)])
result={'rom_sha256':__import__('hashlib').sha256(b).hexdigest(),'maps':len(mp),'objects':objects,'warps':warps,'coordinates':coords,'background_events':bg,'gfx_table':hex(table+0x8000000),'gfx_count':num,'issues':issues,'source_graphics_differences':source_diff}
pathlib.Path('outputs/fixed-map-audit.json').write_text(json.dumps(result,ensure_ascii=False,indent=2));print(json.dumps(result,ensure_ascii=False,indent=2))
