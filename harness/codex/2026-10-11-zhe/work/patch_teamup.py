"""Apply the audited event-script fix to the exact supplied ROM, preserving all other bytes."""
from pathlib import Path
import struct, hashlib, json, difflib, zlib
SOURCE=Path(r'E:\Pekemon Gba\project')
INPUT=Path(r'E:\Pekemon Gba\EmeraldStory-一周目完整版.gba')
OUT=Path('outputs'); OUT.mkdir(exist_ok=True)
EXPECTED='cf9b34f57b57a71613e12fe078eba35835ec9e1283ac355b4436201bf854cbde'
original=INPUT.read_bytes(); assert hashlib.sha256(original).hexdigest()==EXPECTED
rom=bytearray(original); changes=[]; cursor=0x1b00000
def h(n):return struct.pack('<H',n)
def w(n):return struct.pack('<I',n)
class Script:
 def __init__(self,addr):self.addr=addr;self.data=bytearray();self.labels={};self.fixups=[]
 def emit(self,b):self.data.extend(b)
 def label(self,name):self.labels[name]=self.addr+len(self.data)
 def target(self,name):
  if isinstance(name,int):self.emit(w(name))
  else:self.fixups.append((len(self.data),name));self.emit(bytes(4))
 def go(self,name):self.emit(b'\x05');self.target(name)
 def eq(self,value,name):self.emit(b'\x21'+h(0x800d)+h(value)+b'\x06\x01');self.target(name)
 def special(self,n):self.emit(b'\x25'+h(n))
 def var(self,n,value):self.emit(b'\x16'+h(n)+h(value))
 def native(self,addr):self.emit(b'\x23'+w(addr))
 def finish(self):
  for p,name in self.fixups:struct.pack_into('<I',self.data,p,self.labels[name])
  return bytes(self.data)
def record(offset,data,description):
 before=bytes(rom[offset:offset+len(data)]);rom[offset:offset+len(data)]=data
 changes.append(dict(offset=hex(offset),address=hex(offset+0x8000000),before=before.hex(),after=data.hex(),description=description))
sites=[('MtPyre_Exterior',0x38ed1b,True),('Route119',0x3993a0,True),('LavaridgeTown',0x3995ac,True),('MossdeepCity_SpaceCenter_2F',0x30d180,False)]
for name,base,choose in sites:
 start=base+22;end=start+75
 assert original[base:base+8]==bytes.fromhex('252800230da10d08')
 assert original[start:start+5]==bytes.fromhex('2399600f08')
 assert original[end-3:end]==bytes.fromhex('252900')
 s=Script(0x8000000+cursor)
 s.native(0x080f6099);s.eq(1,'full')
 if choose:
  s.emit(bytes.fromhex('9701'));s.special(0x2a);s.emit(b'\x27');s.eq(0,'cancel')
 s.special(0xf9)
 s.var(0x8004,2);s.var(0x8005,4);s.special(0xe8)
 # Half-team selection owns restoration in this script, never in the battle callback.
 s.var(0x8005,0x80);s.native(0x080dd2b1);s.emit(b'\x27')
 s.var(0x8004,6);s.special(0xe8);s.special(0x29);s.go('outcome')
 s.label('full');s.var(0x8005,0);s.native(0x080dd2b1);s.emit(b'\x27')
 # Full teams keep their original slot order; save all six, not a stale Frontier order.
 s.special(0x28);s.special(0x29)
 s.label('outcome');s.emit(bytes.fromhex('260d80b500'));s.go(0x8000000+end)
 if choose:
  s.label('cancel');s.special(0x29)
  if name=='Route119':
   s.emit(bytes.fromhex('9701534000291f002b1e0907004694390897004f0f80b7a43408510000'))
  elif name=='LavaridgeTown':
   s.emit(bytes.fromhex('9701531100531200291e009700'))
  s.emit(bytes.fromhex('6b02'))
 code=s.finish(); assert set(original[cursor:cursor+len(code)])=={255}
 record(cursor,code,name+' complete multi_do with selection/restore/cancel')
 record(start,b'\x05'+w(s.addr),name+' redirect only the old AreMultiPartiesFullTeams instruction')
 cursor=(cursor+len(code)+3)&~3
target=OUT/'EmeraldStory-一周目完整版-组队选宝可梦修复.gba';target.write_bytes(rom)
manifest={'input':str(INPUT),'input_sha256':EXPECTED,'output':str(target.resolve()),'output_sha256':hashlib.sha256(rom).hexdigest(),'rom_length':len(rom),'sites':[{'map':n,'old_multi_do':hex(b+22+0x8000000),'selection_inserted':c} for n,b,c in sites],'changes':changes}
(OUT/'teamup-rom-patch.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
def number(value):
 result=bytearray()
 while True:
  digit=value&127;value>>=7
  if not value:result.append(digit|128);return result
  result.append(digit);value-=1
bps=bytearray(b'BPS1')+number(len(original))+number(len(rom))+number(0)
position=0
for change in sorted(changes,key=lambda c:int(c['offset'],16)):
 offset=int(change['offset'],16);data=bytes.fromhex(change['after'])
 if offset>position:bps.extend(number((offset-position-1)<<2))
 bps.extend(number(((len(data)-1)<<2)|1));bps.extend(data);position=offset+len(data)
if position<len(rom):bps.extend(number((len(rom)-position-1)<<2))
bps.extend(w(zlib.crc32(original))+w(zlib.crc32(rom)));bps.extend(w(zlib.crc32(bps)))
(OUT/'teamup-selection.bps').write_bytes(bps)
files=['asm/macros/battle_frontier/battle_tower.inc','data/scripts/part55.inc','data/scripts/story_b.inc','data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc']
diff=[];source_changes=[]
for f in files:
 old=Path('work/backups/teamup')/f;new=SOURCE/f;a=old.read_bytes();b=new.read_bytes()
 diff.extend(difflib.unified_diff(a.decode().splitlines(True),b.decode().splitlines(True),'a/'+f,'b/'+f))
 source_changes.append({'file':str(new),'before_sha256':hashlib.sha256(a).hexdigest(),'after_sha256':hashlib.sha256(b).hexdigest(),'backup':str(old.resolve())})
(OUT/'teamup-source.patch').write_text(''.join(diff),encoding='utf-8',newline='')
(OUT/'teamup-source-manifest.json').write_text(json.dumps(source_changes,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'rom':str(target),'sha256':manifest['output_sha256'],'changed_regions':len(changes),'inserted_bytes':cursor-0x1b00000},ensure_ascii=False))
