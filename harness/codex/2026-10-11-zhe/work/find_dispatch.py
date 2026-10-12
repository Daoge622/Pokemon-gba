from pathlib import Path
from capstone import *
b=Path(r'E:\Pekemon Gba\EmeraldStory-一周目完整版.gba').read_bytes();c=Cs(CS_ARCH_ARM,CS_MODE_THUMB);c.skipdata=True
found=[]
for off in range(0x400,0x290000,0x10000):
 ins=list(c.disasm(b[off:off+0x10000],off+0x8000000))
 for n,i in enumerate(ins):
  if i.mnemonic=='ldr' and i.op_str.endswith('#0x5c]') and '[pc,' not in i.op_str:
   group=ins[max(0,n-25):n+65]
   if any(j.mnemonic=='ldr' and '#0x60]' in j.op_str and '[pc,' not in j.op_str for j in group):
    found.append('\n'.join(f'{j.address:08x} {j.bytes.hex()} {j.mnemonic} {j.op_str}' for j in group))
Path('work/dispatches.txt').write_text('\n\n'.join(found));print('candidates',len(found));print('\n'.join(s.splitlines()[25] for s in found))
