from part4_compat import source as part4_source
#!/usr/bin/env python3
"""Chinese source/font/ABI checks and native helper/compiler tests. Never runs a ROM."""
import json,re,struct,subprocess,tempfile
from pathlib import Path
r=Path(__file__).resolve().parents[2]
def git(ref,f):return subprocess.check_output(['git','show',ref+':'+f],cwd=r)
checkpoint='pre-chinese-base-migration'
# The entire save/type definitions, mechanics and previously implemented C modules stay intact.
unchanged=['include/global.h','include/global.pokemon.h','include/pokemon.h','include/constants/global.h','include/config/species_enabled.h','include/config/battle.h','include/config/project.h','include/config/overworld.h','include/config/pokedex_plus_hgss.h','include/constants/flags.h','include/constants/opponents.h','src/battle_util.c','src/battle_dynamax.c','src/battle_terastal.c','include/limited_shop.h','include/project_gifts.h','data/specials.inc','src/shop.c','src/project_gifts.c','src/limited_shop.c','src/daycare.c','src/data/pokemon/evolution.h']
# PART1 changes are independently guarded by check-part1.py.
part1_allowed={'include/config/battle.h','include/constants/flags.h','include/constants/opponents.h','data/specials.inc','src/limited_shop.c'}
unchanged=[f for f in unchanged if f not in part1_allowed]
checked=0
for f in unchanged:
 if not (r/f).exists():continue
 assert part4_source(f).encode()==git(checkpoint,f),f
 checked+=1
# Z text was localized, but its gameplay tokens and project disable gate must stay identical.
def c_tokens(s):
 s=re.sub(r'"(?:\\.|[^"\\])*"', '""',s)
 s=re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
 return re.findall(r'[A-Za-z_]\w*|\d+|[^\s]',s)
assert c_tokens((r/'src/battle_z_move.c').read_text())==c_tokens(git(checkpoint,'src/battle_z_move.c').decode())
assert '#define EXPANSION_VERSION_PATCH 1' in (r/'include/constants/expansion.h').read_text()
# No map object, connection, warp, trigger, collision or local-ID changes in this migration.
for folder in ['LittlerootTown','OldaleTown','OldaleTown_Mart','Route102','PetalburgCity']:
 f=f'data/maps/{folder}/map.json';assert part4_source(f).encode()==git(checkpoint,f)
def code(s):
 s=re.sub(r'(?m)^\s*\.string[^\n]*\n?', '',s)
 s=re.sub(r'(?m)@[^\n]*', '',s)
 return re.sub(r'\s+','',s)
for folder in ['LittlerootTown','OldaleTown','OldaleTown_Mart','Route102','PetalburgCity']:
 f=f'data/maps/{folder}/scripts.inc';assert code(re.sub(r'(?m)^\s*call(?: Part4_\w+|_if_set FLAG_BADGE04_GET, PetalburgCity_EventScript_(?:GymBoy|Gentleman)_Part4)\n','',part4_source(f,(r/f).read_text())))==code(git(checkpoint,f).decode()),f
print(f'Save/name ABI, {checked} retained core files and all five opening map bytecodes: PASS')
files=['src/data/items.h','src/data/moves_info.h','src/data/abilities.h','src/data/types_info.h']+[f'src/data/pokemon/species_info/gen_{i}_families.h' for i in range(1,10)]
ignore={'name','namePlural','description','speciesName','categoryName','pokedexText','dexCategoryName','text','pluralName','generic'}
def values(s):
 s=re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
 tokens=re.findall(r'"(?:\\.|[^"\\])*"|[A-Za-z_]\w*|\d+|[^\s]',s)
 result=[]
 for i in range(len(tokens)-3):
  if tokens[i]!='.' or tokens[i+2]!='=' or tokens[i+1] in ignore:continue
  j=i+3;depth=0;value=[]
  while j<len(tokens):
   t=tokens[j]
   if depth==0 and (t in [',','}','#',chr(92)] or (t=='[' and value)):break
   depth+=int(t in ['(','{','['])-int(t in [')','}',']'])
   value.append(t);j+=1
  result.append((tokens[i+1],''.join(value)))
 return result
total_fields=0
for f in files:
 old=values(git(checkpoint,f).decode());current=part4_source(f,(r/f).read_text())
 # PART2's approved evolution/item changes are verified independently; retain all other baseline comparisons.
 part2=json.loads((r/'docs/project/part2-manifest.json').read_text())
 if f=='src/data/items.h':
  current=re.sub(r'    \[ITEM_PEACE_CHARM\] =\n    \{.*?\n    \},\n', '', current, flags=re.S)
  current=re.sub(r'    \[ITEM_LINKING_CORD\] =\n    \{.*?\n    \},',lambda _:part2['linking_cord_original'],current,flags=re.S)
 for evo in part2['evolution_changes']:
  if evo['file']==f:
   assert evo['new'] in current,(f,evo['species']);current=current.replace(evo['new'],evo['old'],1)
 new=values(current)
 assert old==new,(f,'non-text data changed')
 total_fields+=len(new)
for f in ['src/data/items.h','src/data/moves_info.h']:
 directives=lambda x: re.findall(r'(?m)^\s*#(?:if|elif|else|endif)[^\n]*',x)
 assert directives(git(checkpoint,f).decode())==directives((r/f).read_text()),(f,'generation guard changed')
print(f'{total_fields} non-text item/move/ability/type/Gen 1-9 species fields and item/move generation guards: PASS')

mapping={}
for m in re.finditer(r"^'(.+)'\s*=\s*([0-9A-Fa-f][0-9A-Fa-f ]*)",(r/'charmap.txt').read_text(),re.M):
 key=m[1][1:] if len(m[1])==2 and m[1].startswith(chr(92)) else m[1]
 if len(key)==1:mapping[key]=bytes.fromhex(m[2].strip())
pairs={c:b for c,b in mapping.items() if len(b)==2}
for name in ['chinese_normal','chinese_small']:
 w,h=struct.unpack('>II',(r/f'graphics/fonts/{name}.png').read_bytes()[16:24]);capacity=w*h//256
 assert (r/f'build/assets/graphics/fonts/{name}.png.latfont').stat().st_size==capacity*64
 for char,b in pairs.items():
  hi,lo=b;assert 1<=hi<=0x1e and hi not in (6,0x1b) and lo<=0xf6,(char,b)
  hi-=int(b[0]>0x1b);hi-=int(b[0]>6);hi-=1
  assert ((hi<<8)|lo)<capacity,(char,b)
print(f'{len(pairs)} double-byte characters covered by both 7088-glyph fonts: PASS')
config=json.loads((r/'tools/poryscript/font_config.json').read_text());font=config['fonts'][config['defaultFontId']]
assert all(font['widths'][c]==12 for c in pairs)
def width(s):
 return sum(font['widths'].get(t,0 if t.startswith('{') else 6) for t in re.findall(r'\{[^}]*\}|.',s))
def check_text(s):
 text=''.join(re.findall(r'\.string "(.*)"',s))
 for line in re.split(r'\\[nlp]',text.rstrip('$')):
  assert width(line)<=208,(line,width(line))
 for token in re.findall(r'\{[^}]*\}|\\.|.',text):
  if token.startswith(('{','\\')) or token=='$':continue
  assert token in mapping,(token,'missing charmap')
manifest=json.loads((r/'docs/project/chinese-import-manifest.json').read_text());textblocks=0
for f in manifest.get('restored_unrelated_art',[]):
 assert (r/f).read_bytes()==git(checkpoint,f),(f,'unrelated artwork changed')
pattern=re.compile(r'(?m)^([A-Za-z_]\w*):{1,2}[ \t]*\n((?:[ \t]*\.string[^\n]*\n?)+)')
assembly_paths=set(manifest['text_only'])|{str(p.relative_to(r)) for p in (r/'data').rglob('*') if p.suffix in ('.inc','.s')}
for f in sorted(assembly_paths):
 if not f.endswith(('.inc','.s')):continue
 for m in pattern.finditer((r/f).read_text()):
  if any('\u4e00'<=c<='\u9fff' for c in m[2]):check_text(m[2]);textblocks+=1
print(f'{textblocks} Chinese assembly text blocks: glyph coverage and conservative variable widths PASS')
# Ensure translated fixed-size name arrays fit their original BYTE budgets.
for f,regex,limit in [('src/data/items.h',r'ITEM_NAME\("([^"\n]*)"\)',20),('src/data/moves_info.h',r'\.name\s*=\s*COMPOUND_STRING\("([^"\n]*)"\)',16),('src/data/abilities.h',r'\.name\s*=\s*_\("([^"\n]*)"\)',16)]:
 for name in re.findall(regex,(r/f).read_text()):
  assert sum(len(mapping[c]) for c in name)<=limit,(f,name)
trainer_names=0
for f in ['src/data/trainers.party','src/data/battle_partners.party']:
 for name in re.findall(r'^Name: (.*)$',(r/f).read_text(),re.M):
  assert sum(len(mapping[c]) for c in name)<=10,(f,name)
  trainer_names+=1
print(f'Item/move/ability and {trainer_names} trainer names remain inside original byte budgets: PASS')
with tempfile.TemporaryDirectory() as d:
 p=Path(d)
 # Extract actual production helper functions, not a reimplementation.
 chinese=(r/'src/chinese_text.c').read_text();recognize=chinese[chinese.index('bool8 IsChineseChar('):chinese.index('//检测是否为单字节中文符号编码')]
 string=(r/'src/string_util.c').read_text();helpers=string[string.index('static u32 GetNamePrefixByteLength('):string.index('u8 *StringCopy(u8 *dest')]
 source='''#include <stdint.h>
#include <assert.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef u8 bool8; typedef u32 bool32;
#define TRUE 1
#define FALSE 0
#define EOS 255
#define FONT_NORMAL 1
#define FONT_BRAILLE 6
#define CHAR_EXTRA_SYMBOL 247
#define POKEMON_NAME_LENGTH 12
#define PLAYER_NAME_LENGTH 7
'''+recognize+helpers+'''
int main(void) {
 u8 out[14], mixed[]={'A','B','C','D',9,0xd9,9,0xd9,EOS};
 assert(StringCopy_PlayerName(out,mixed)==out+6 && out[6]==EOS);
 u8 chinese[]={9,0xd9,9,0xd9,9,0xd9,9,0xd9,EOS};
 assert(StringCopy_PlayerName(out,chinese)==out+6 && out[6]==EOS);
 u8 nick[]={'A','B','C','D','E','F','G','H','I','J','K',9,0xd9,EOS};
 assert(StringCopy_Nickname(out,nick)==out+11 && out[11]==EOS);
 assert(StringGet_Nickname(nick)==nick+11 && nick[11]==EOS);
 assert(IsChineseChar(9,0xd9,FONT_NORMAL,FALSE));
 assert(!IsChineseChar(6,0xd9,FONT_NORMAL,FALSE));
 assert(!IsChineseChar(9,EOS,FONT_NORMAL,FALSE));
 assert(!IsChineseChar(9,0xd9,FONT_BRAILLE,FALSE));
 assert(!IsChineseChar(9,0xd9,FONT_NORMAL,TRUE));
 return 0;
}
'''
 (p/'name.c').write_text(source);subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror',str(p/'name.c'),'-o',str(p/'name')],check=True);subprocess.run([str(p/'name')],check=True)
 # Validate the real Poryscript -> charmap preprocessor -> ARM assembler pipeline.
 subprocess.run(['tools/poryscript/poryscript','-lm=false','-i','scripts/tests/fixtures/chinese-probe.pory','-o',str(p/'probe.inc'),'-fc','tools/poryscript/font_config.json','-cc','tools/poryscript/command_config.json'],cwd=r,check=True)
 for match in pattern.finditer((p/'probe.inc').read_text()):check_text(match[2])
 header=(r/'data/event_scripts.s').read_text().split('\t.section script_data')[0]
 (p/'probe.s').write_text(header+'\n\t.section script_data, "aw", %progbits\n'+(p/'probe.inc').read_text())
 a=subprocess.check_output(['tools/preproc/preproc','-s',str(p/'probe.s'),'charmap.txt'],cwd=r)
 b=subprocess.check_output(['arm-none-eabi-cpp','-iquote','include','-DMODERN=1','-DTESTING=0','-DEMERALD','-std=gnu17','-I','include','-'],cwd=r,input=a)
 c=subprocess.check_output(['tools/preproc/preproc','-ie',str(p/'probe.s'),'charmap.txt'],cwd=r,input=b)
 subprocess.run(['arm-none-eabi-as','-mcpu=arm7tdmi','-march=armv4t','-meabi=5','--defsym','MODERN=1','--defsym','EMERALD=1','-o',str(p/'probe.o'),'-'],input=c,check=True,cwd=r)
 subprocess.run(['arm-none-eabi-objcopy','-O','binary','--only-section=script_data',str(p/'probe.o'),str(p/'probe.bin')],check=True)
 assert mapping['你'] in (p/'probe.bin').read_bytes()
print('Native name-boundary checks and Chinese/mixed/control/variable/choice ARM compilation: PASS')