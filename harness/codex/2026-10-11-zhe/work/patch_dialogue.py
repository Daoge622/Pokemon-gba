"""Restore the engine's existing cant_see_if primitive at four wrapped trainers.

The ROM has no symbols and the source snapshot cannot reproduce it. The small
Thumb implementation has the semantics of Script_EndTrainerCanSeeIf, including
all six comparison conditions; it adds no flags or defensive fallback.
"""
from pathlib import Path
import struct, hashlib, json, difflib, zlib
from keystone import Ks, KS_ARCH_ARM, KS_MODE_THUMB
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

BASE = Path('outputs/EmeraldStory-一周目完整版-组队选宝可梦修复.gba')
SOURCE = Path(r'E:\Pekemon Gba\project')
OUT = Path('outputs')
before = BASE.read_bytes()
assert hashlib.sha256(before).hexdigest() == '8c3142dcf6678093913e9f572865272d46dbe9862f60d03f5f9d251259037e8d'
rom = bytearray(before)
changes = []
native_offset = 0x1b00400
assembly = '''
ldr r1, [r0, #8]
ldrb r2, [r1]
adds r1, #1
str r1, [r0, #8]
ldrb r1, [r0, #3]
lsls r1, r1, #31
bpl done
adds r3, r2, r2
adds r3, r3, r2
ldrb r2, [r0, #2]
adds r3, r3, r2
adr r1, conditions
ldrb r1, [r1, r3]
cmp r1, #1
bne done
movs r1, #0
strb r1, [r0, #1]
str r1, [r0, #8]
done:
bx lr
.balign 4
conditions:
.byte 1,0,0, 0,1,0, 0,0,1, 1,1,0, 0,1,1, 1,0,1
'''
native = bytes(Ks(KS_ARCH_ARM, KS_MODE_THUMB).asm(assembly, 0x8000000 + native_offset)[0])
disasm = list(Cs(CS_ARCH_ARM, CS_MODE_THUMB).disasm(native[:38], 0x8000000 + native_offset))
assert all(i.size == 2 for i in disasm), 'ARM7TDMI: no Thumb-2 instructions'
(OUT/'dialogue-cant-see-thumb.s').write_text(assembly, encoding='utf-8')
(OUT/'dialogue-cant-see-disassembly.txt').write_text('\n'.join(f'{i.address:08x} {i.bytes.hex()} {i.mnemonic} {i.op_str}' for i in disasm), encoding='utf-8')

def record(p, data, reason, free=False):
    old = bytes(rom[p:p+len(data)])
    if free: assert set(old) == {255}
    rom[p:p+len(data)] = data
    changes.append({'offset':hex(p), 'address':hex(0x8000000+p), 'before':old.hex(), 'after':data.hex(), 'reason':reason})

record(native_offset, native, 'Script_EndTrainerCanSeeIf equivalent; all comparison conditions', True)
audit = json.loads(Path('work/wrapped-trainers.json').read_text())
sites = [x for x in audit['wrapped'] if not x['map'].startswith('BattlePyramidSquare')]
assert len(sites) == 4
cursor = (native_offset + len(native) + 3) & ~3
for site in sites:
    root = int(site['script'],16)
    assert before[root-0x8000000:root-0x8000000+3] == bytes.fromhex('6a5a60')
    trainer = struct.unpack_from('<H', before, root-0x8000000+3)[0]
    # Existing cant_see_if_trainerflag_set: checktrainerflag; instrumented
    # callnative Script_EndTrainerCanSeeIf; EQUAL; goto unmodified script.
    prefix = b'\x60'+struct.pack('<H', trainer)+b'\x23'+struct.pack('<I',0xa000001+native_offset)+b'\x01\x05'+struct.pack('<I',root)
    record(cursor,prefix,site['label']+' sight condition before lock',True)
    record(site['object_offset']+16,struct.pack('<I',0x8000000+cursor),site['map']+' object '+str(site['local_id'])+' script pointer')
    site.update(trainer=trainer, wrapper=hex(0x8000000+cursor))
    cursor=(cursor+len(prefix)+3)&~3

target=OUT/'EmeraldStory-一周目完整版-组队与战后对话修复.gba'
target.write_bytes(rom)
manifest={'base':str(BASE.resolve()),'base_sha256':hashlib.sha256(before).hexdigest(),'output':str(target.resolve()),'output_sha256':hashlib.sha256(rom).hexdigest(),'sites':sites,'changes':changes,'audit_trainer_objects':audit['trainer_objects'],'audit_wrapped_objects':len(audit['wrapped']),'excluded':'64 BattlePyramid objects: independent facility trainer flags'}
(OUT/'dialogue-rom-patch.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')

relative='data/scripts/part55.inc'
source=SOURCE/relative
backup=Path('work/backups/dialogue-loop')/relative
backup.parent.mkdir(parents=True,exist_ok=True)
old=source.read_bytes()
if not backup.exists(): backup.write_bytes(old)
else: assert backup.read_bytes()==old
text=old.decode()
trainers={'Part55_RookieFormal':'TRAINER_GRUNT_MAGMA_HIDEOUT_14','Part55_MagmaBento':'TRAINER_GRUNT_MAGMA_HIDEOUT_4','Part55_MagmaGloves':'TRAINER_GRUNT_MAGMA_HIDEOUT_5','Part55_Seasick':'TRAINER_GRUNT_AQUA_HIDEOUT_2'}
for label,trainer in trainers.items():
    pattern=label+'::\n\tlock'
    assert text.count(pattern)==1
    text=text.replace(pattern,label+'::\n\tcant_see_if_trainerflag_set '+trainer+'\n\tlock')
new=text.encode();source.write_bytes(new)
(OUT/'dialogue-source.patch').write_text(''.join(difflib.unified_diff(old.decode().splitlines(True),text.splitlines(True),'a/'+relative,'b/'+relative)),encoding='utf-8',newline='')
(OUT/'dialogue-source-manifest.json').write_text(json.dumps({'file':str(source),'backup':str(backup.resolve()),'before_sha256':hashlib.sha256(old).hexdigest(),'after_sha256':hashlib.sha256(new).hexdigest()},ensure_ascii=False,indent=2),encoding='utf-8')

def number(v):
    result=bytearray()
    while True:
        d=v&127;v>>=7
        if not v:return result+bytes([d|128])
        result.append(d);v-=1

def bps(original,name):
    data=bytearray(b'BPS1')+number(len(original))+number(len(rom))+number(0)
    p=0
    while p<len(rom):
        start=p;different=original[p]!=rom[p]
        while p<len(rom) and (original[p]!=rom[p])==different:p+=1
        data.extend(number(((p-start-1)<<2)|int(different)))
        if different:data.extend(rom[start:p])
    data.extend(struct.pack('<2I',zlib.crc32(original),zlib.crc32(rom)));data.extend(struct.pack('<I',zlib.crc32(data)))
    (OUT/name).write_bytes(data)
bps(before,'dialogue-loop-from-teamup.bps')
bps(Path(r'E:\Pekemon Gba\EmeraldStory-一周目完整版.gba').read_bytes(),'teamup-and-dialogue-from-original.bps')
print(json.dumps({'sha256':manifest['output_sha256'],'sites':len(sites),'native_bytes':len(native),'end':hex(cursor)},ensure_ascii=False))
