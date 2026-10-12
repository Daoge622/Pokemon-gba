from pathlib import Path
import hashlib,json,struct,zlib
OUT=Path('outputs');m=json.loads((OUT/'dialogue-rom-patch.json').read_text(encoding='utf-8'))
base=Path(m['base']).read_bytes();target=Path(m['output']).read_bytes()
assert len(base)==len(target)==0x2000000
assert hashlib.sha256(target).hexdigest()==m['output_sha256']
allowed=set()
for c in m['changes']:
 p=int(c['offset'],16);a=bytes.fromhex(c['before']);b=bytes.fromhex(c['after'])
 assert base[p:p+len(a)]==a and target[p:p+len(b)]==b
 allowed.update(range(p,p+len(b)))
different=[i for i,(a,b) in enumerate(zip(base,target)) if a!=b]
assert all(i in allowed for i in different)
previous=json.loads((OUT/'teamup-rom-patch.json').read_text(encoding='utf-8'))
for c in previous['changes']:
 p=int(c['offset'],16);b=bytes.fromhex(c['after']);assert target[p:p+len(b)]==b
def apply_bps(source,filename):
 patch=(OUT/filename).read_bytes();pos=4;assert patch[:4]==b'BPS1'
 def number():
  nonlocal pos
  value=0;shift=1
  while True:
   n=patch[pos];pos+=1;value+=(n&127)*shift
   if n&128:return value
   shift*=128;value+=shift
 assert number()==len(source) and number()==len(target)
 metadata=number();pos+=metadata;result=bytearray()
 while len(result)<len(target):
  n=number();size=(n>>2)+1
  if n&3==0:result.extend(source[len(result):len(result)+size])
  elif n&3==1:result.extend(patch[pos:pos+size]);pos+=size
  else:raise AssertionError('Unexpected BPS command')
 assert result==target and pos==len(patch)-12
 assert struct.unpack_from('<3I',patch,pos)==(zlib.crc32(source),zlib.crc32(target),zlib.crc32(patch[:-4]))
original=Path(r'E:\Pekemon Gba\EmeraldStory-一周目完整版.gba').read_bytes()
assert hashlib.sha256(original).hexdigest()==previous['input_sha256']
apply_bps(base,'dialogue-loop-from-teamup.bps');apply_bps(original,'teamup-and-dialogue-from-original.bps')
for i in range(4):
 before=json.loads((OUT/f'dialogue-original-{i}-defeated-verification.json').read_text(encoding='utf-8'))['log']
 after=json.loads((OUT/f'dialogue-fixed-{i}-defeated-verification.json').read_text(encoding='utf-8'))['log']
 assert before[0]['lock']==before[1]['lock']==1
 assert after[0]['lock']==after[1]['lock']==after[3]['lock']==after[4]['lock']==0
 assert after[2]['lock']==1 and after[4]['xy']!=after[0]['xy']
 battle=json.loads((OUT/f'dialogue-fixed-{i}-unbeaten-battle-verification.json').read_text(encoding='utf-8'))
 assert battle['lock']==0 and battle['trainer_defeated'] and battle['field']=='0x81b9521'
for kind,key in [('map','issues'),('script','errors'),('trainer','errors')]:
 a=json.loads((OUT/f'dialogue-{kind}-audit.json').read_text(encoding='utf-8'))
 if key in a:assert not a[key]
result={'status':'PASS','output_sha256':m['output_sha256'],'changed_bytes_from_teamup':len(different),'changed_regions':len(m['changes']),'old_teamup_fix_preserved':True,'both_BPS_independent_apply_and_CRC':'PASS','runtime':'4 original post-win sight loops reproduced; 4 fixed pre-win sight battles completed with actual buttons; victory flags, no automatic dialogue for 600 frames, manual post-win talk/close/walk PASS','setup':'controlled map warp; naturally healed party from prior loss state; isolated trainer flags; two walking grunts fixed in place only in fixture ROM; no combat HP edits','limitations':'mGBA headless authorized; no MyBoy core; 88 unknown native call sites remain outside static decoding; not an all-story playthrough'}
(OUT/'dialogue-verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8');print(json.dumps(result,ensure_ascii=False,indent=2))
