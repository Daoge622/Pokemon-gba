"""Headless controlled sight test; flags/warp/static poses are fixture-only."""
from runtime import *
from pathlib import Path
import hashlib
mode=sys.argv[1];index=int(sys.argv[2]);defeated=sys.argv[3]!='unbeaten'
manifest=json.loads(Path('outputs/dialogue-rom-patch.json').read_text())
site=manifest['sites'][index];maps=json.loads(Path('work/maps.json').read_text());m=maps[site['map']]
base=Path(manifest['output'] if mode=='fixed' else manifest['base']);rom=bytearray(base.read_bytes())
p=site['object_offset'];x,y=struct.unpack_from('<2h',rom,p+4)
if site['label']=='Part55_RookieFormal':x+=1
else:
 y+=1
 # Face-down enum is 8, verified against Aqua object's existing pose.
 assert rom[manifest['sites'][0]['object_offset']+9]==8
 rom[p+9]=8
warp=bytes([0x68,0x39,m['group'],m['num'],255])+struct.pack('<2H',x,y)+bytes.fromhex('276b02')
o=0x1b02000;assert set(rom[o:o+len(warp)])=={255};rom[o:o+len(warp)]=warp
name=f'dialogue-{mode}-{index}-'+('defeated' if defeated else 'unbeaten')
path=ROOT/(name+'.gba');path.write_bytes(rom)
c=Core(path);c.run(100);c.load((ROOT/'teamup-loss-healed.state').read_bytes())
state=c.state();sb=struct.unpack_from('<I',state,0x19000+0x238c)[0]
def flag(n,value):
 q=0x21000+sb-0x2000000+0x1270+n//8
 if value:state[q]|=1<<(n%8)
 else:state[q]&=255^(1<<(n%8))
# Isolate the target object's sight; fixture-only other trainer victory flags.
for t in manifest['sites']:flag(t['trainer']+0x500,True)
for j in range(m['counts'][0]):
 q=m['pointers'][0]-0x8000000+24*j;a=struct.unpack_from('<I',rom,q+16)[0]
 if a and rom[a-0x8000000]==0x5c:
  trainer=struct.unpack_from('<H',rom,a-0x8000000+3)[0]
  flag(trainer+0x500,True)
flag(site['trainer']+0x500,defeated)
for j in range(m['counts'][0]):
 q=m['pointers'][0]-0x8000000+24*j;hide=struct.unpack_from('<H',rom,q+20)[0]
 if hide:flag(hide,False)
q=0x19000+0xca4;state[q:q+4]=bytes([0,1,0,0]);struct.pack_into('<2I',state,q+4,0,0x8000000+o)
state[0x19000+0x8a6:0x19000+0x8a8]=bytes([0,1])
c.load(state);c.run(550)
def snap(tag):
 c.shot(name+'-'+tag+'.png');(ROOT/(name+'-'+tag+'.state')).write_bytes(c.state())
 s=c.state();sb=c.rd(0x300238c)
 d={'tag':tag,'xy':[c.rd(sb,2),c.rd(sb+2,2)],'map':[c.rd(sb+4,1),c.rd(sb+5,1)],'ctx':s[0x19000+0xca4:0x19000+0xca4+4].hex(),'script':hex(c.rd(0x300cac)),'lock':c.rd(0x30008a7,1),'cb':hex(c.rd(0x3002418))}
 print(json.dumps(d),flush=True);return d
log=[snap('arrival')]
for cycle in range(12):c.run(4,[8]);c.run(90)
log.append(snap('after-close'))
if mode=='fixed' and defeated:
 # At the adjacent tile the player faces the trainer after an Up/Left tap.
 c.run(3,[6 if site['label']=='Part55_RookieFormal' else 4]);c.run(20);c.run(4,[8]);c.run(120)
 log.append(snap('manual-dialogue'))
 for cycle in range(20):
  c.run(4,[8]);c.run(30)
  if c.rd(0x30008a7,1)==0:break
 c.run(300)
 log.append(snap('manual-closed'))
 c.run(16,[5]);c.run(60)
 sb=c.rd(0x300238c)
 if [c.rd(sb,2),c.rd(sb+2,2)]==[x,y]:c.run(16,[6]);c.run(60)
 sb=c.rd(0x300238c)
 if [c.rd(sb,2),c.rd(sb+2,2)]==[x,y]:c.run(16,[7]);c.run(60)
 log.append(snap('walk'))
Path('outputs/'+name+'-verification.json').write_text(json.dumps({'fixture':True,'setup':'engine warp, set battle flags, clear hide flags, static face-down for test target','source_rom_sha256':hashlib.sha256(base.read_bytes()).hexdigest(),'site':site,'log':log},ensure_ascii=False,indent=2),encoding='utf-8')
