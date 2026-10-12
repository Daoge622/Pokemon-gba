from pathlib import Path
import struct,json
R=Path(r'E:\Pekemon Gba\project');b=Path(r'E:\Pekemon Gba\EmeraldStory-一周目完整版.gba').read_bytes()
def refs(addr):
 p=struct.pack('<I',addr);i=-1;a=[]
 while True:
  i=b.find(p,i+1)
  if i<0:return a
  a.append(i)
def u32(i):return struct.unpack_from('<I',b,i)[0]
def addr(i):return i+0x8000000
group=json.loads((R/'data/maps/map_groups.json').read_text());g,n=next((i,group[k].index('MtPyre_1F')) for i,k in enumerate(group['group_order']) if 'MtPyre_1F' in group[k]);print('map',g,n)
for ref in refs(0x838f04e):
 obj=ref-16;print('object',hex(addr(obj)),b[obj:obj+24].hex())
 # grave worker is seventh object in source; locate event aggregate count + refs.
 for er in refs(addr(obj-6*24)):
  events=er-4;print('events',hex(addr(events)),b[events:events+20].hex())
  for hr in refs(addr(events)):
   header=hr-4;print('header',hex(addr(header)),b[header:header+36].hex())
   for mr in refs(addr(header)):
    ga=mr-n*4;print('group array',hex(addr(ga)))
    for ar in refs(addr(ga)):
     table=ar-g*4
     print('map table',hex(addr(table)))
     mp={};errors=[]
     for gi,key in enumerate(group['group_order']):
      arr=u32(table+gi*4)-0x8000000
      if arr==-0x8000000:continue
      if not 0<=arr<len(b)-len(group[key])*4:errors.append((key,'group'));continue
      for ni,name in enumerate(group[key]):
       ho=u32(arr+ni*4)-0x8000000
       if not 0<=ho<len(b)-32:errors.append((name,'header'));continue
       ev=u32(ho+4)-0x8000000
       if not 0<=ev<len(b)-20:errors.append((name,'events'));continue
       counts=b[ev:ev+4];pointers=[u32(ev+4+j*4) for j in range(4)]
       mp[name]={'group':gi,'num':ni,'header':addr(ho),'events':addr(ev),'counts':list(counts),'pointers':pointers,'scripts':u32(ho+8),'layout':u32(ho)}
     print('maps',len(mp),'errors',errors[:5]);Path('work/maps.json').write_text(json.dumps(mp,indent=2));Path('work/maptable.json').write_text(json.dumps({'address':addr(table)}))
