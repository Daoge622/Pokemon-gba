from pathlib import Path
import struct,re,json
from capstone import *
R=Path(r'E:\Pekemon Gba\project');rom=Path(r'E:\Pekemon Gba\EmeraldStory-一周目完整版.gba').read_bytes()
state=Path('work/water.state').read_bytes()
def rd(b,o):return struct.unpack_from('<I',b,o)[0]
count=len(re.findall(r'\bSCR_OP_\w+', (R/'include/constants/script_commands.h').read_text()))
print('opcount',count)
for off,sz,base in [(0x19000,0x8000,0x3000000),(0x21000,0x40000,0x2000000)]:
 for i in range(off,off+sz-116,4):
  table,end=rd(state,i+92),rd(state,i+96)
  if 0x8000000<table<0xa000000 and end-table==count*4:
   print('context',hex(base+i-off),'stack/mode',state[i:i+4].hex(),'native',hex(rd(state,i+4)),'script',hex(rd(state,i+8)),'table',hex(table))
   t=table-0x8000000
   print('lockfn',hex(rd(rom,t+0x6a*4)), 'trainerbattle',hex(rd(rom,t+0x5c*4)))
   Path('work/script-table.json').write_text(json.dumps({'address':table,'count':count,'functions':[rd(rom,t+n*4) for n in range(count)]}))
for target in [0x0838f04f,0x0838f082]:
 p=struct.pack('<I',target);start=0;refs=[]
 while True:
  i=rom.find(p,start)
  if i<0:break
  refs.append(hex(i));start=i+1
 print('refs',hex(target),refs)
