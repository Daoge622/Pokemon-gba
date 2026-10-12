from pathlib import Path
import struct,json,re
b=Path(r'C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba').read_bytes();R=Path(r'E:\Pekemon Gba\project')
def u32(p):return struct.unpack_from('<I',b,p)[0]
def u16(p):return struct.unpack_from('<H',b,p)[0]
seq=bytes.fromhex('0c1d09af0b4bff');hits=[];p=-1
while True:
 p=b.find(seq,p+1)
 if p<0:break
 hits.append(p)
print('grave names',list(map(hex,hits)))
partners=hits[0]-32-50*52-60*52
print('partners table',hex(partners+0x8000000))
for d in range(3):
 p=partners+(d*60+50)*52
 print('difficulty',d,'name',b[p+32:p+43].hex(),'party',hex(u32(p+8)),'size',u16(p+29)>>11&7)
# Enum-indexed array signature: all of the 180 trainer records have ROM party
# pointers (or null for the unused partner slot zero), with name EOS within 11.
errors=[];checked=0
used=sorted({t-864 for v in json.loads(Path('outputs/dialogue-script-audit.json').read_text(encoding='utf8'))['battles'].values() for t in v['trainers'] if 864<t<924})
for d in range(3):
 for trainer in used:
  p=partners+(d*60+trainer)*52;party=u32(p+8);size=u16(p+29)>>11&7
  if not party and d!=1:continue # Sparse easy/hard overrides use normal.
  checked+=1
  if not (0x8000000<=party<0xa000000 and 1<=size<=6):errors.append([d,trainer,'party',hex(party),size])
  if 255 not in b[p+32:p+43]:errors.append([d,trainer,'name lacks EOS'])
result={'partner_table':hex(partners+0x8000000),'record_size':52,'difficulties':3,'used_partner_ids':used,'records_checked':checked,'errors':errors}
Path('outputs/dialogue-trainer-audit.json').write_text(json.dumps(result,indent=2));print(result)
