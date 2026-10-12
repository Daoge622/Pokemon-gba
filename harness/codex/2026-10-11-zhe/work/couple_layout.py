from pathlib import Path
import struct,json
b=Path(r'E:\Pekemon Gba\EmeraldStory-一周目完整版.gba').read_bytes();m=json.loads(Path('work/maps.json').read_text())['MtPyre_2F'];p=m['layout']-0x8000000
w,h,bd,md=struct.unpack_from('<4I',b,p);print('layout',w,h,hex(md))
grid=[struct.unpack_from('<'+str(w)+'H',b,md-0x8000000+y*w*2) for y in range(h)]
for y,row in enumerate(grid):print(f'{y:2}', ''.join('#' if v&0xc00 else '.' for v in row), ' '.join(f'{v:04x}' for v in row))
for j in range(m['counts'][0]):
 p=m['pointers'][0]-0x8000000+j*24;print(j+1,'gfx',struct.unpack_from('<H',b,p+1)[0],'xy',struct.unpack_from('<2h',b,p+4),'script',hex(struct.unpack_from('<I',b,p+16)[0]))
