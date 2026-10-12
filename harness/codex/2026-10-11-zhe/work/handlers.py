import pathlib,json,struct
from capstone import *
b=pathlib.Path(r'E:\Pekemon Gba\EmeraldStory-一周目完整版.gba').read_bytes();t=json.loads(pathlib.Path('work/script-table.json').read_text())['functions'];d=Cs(CS_ARCH_ARM,CS_MODE_THUMB)
for op in [0x8,0x9,0x23,0x24,0x25,0x26,0x5e,0x5f,0x60]:
 a=(t[op]&~1)-0x8000000;a%=0x2000000
 print('OP',hex(op),'FUNCTION',hex(a+0x8000000))
 for i in d.disasm(b[a:a+120],a+0x8000000):
  print(hex(i.address),i.mnemonic,i.op_str)
  if i.mnemonic=='ldr' and '[pc,' in i.op_str:
   off=int(i.op_str.split('#')[1].split(']')[0],0);print(' literal',hex(struct.unpack_from('<I',b,(i.address+4&~3)+off-0x8000000)[0]))
  if i.mnemonic=='bx' and i.op_str=='r0':break
