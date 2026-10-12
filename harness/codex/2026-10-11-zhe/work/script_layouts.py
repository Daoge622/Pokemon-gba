from pathlib import Path
import re,json
R=Path(r'E:\Pekemon Gba\project')
constants=dict((n,int(v,16)) for n,v in re.findall(r'(SCR_OP_\w+)\s*=\s*(0x\w+)',(R/'include/constants/script_commands.h').read_text()))
text=(R/'asm/macros/event.inc').read_text()
layouts={};unknown=[]
for macro,body in re.findall(r'\.macro\s+(\w+)[^\n]*\n(.*?)\.endm',text,re.S):
 lines=[l.split('@')[0].strip() for l in body.splitlines()]
 for start,line in enumerate(lines):
  m=re.fullmatch(r'\.byte\s+(SCR_OP_\w+)',line)
  if not m:continue
  op=constants[m[1]];fields=[];extra=[]
  for l in lines[start+1:]:
   if re.search(r'\.byte\s+SCR_OP_|^\.(?:else|elseif|endif)',l):break
   if not l or l.startswith(('.if','.set')):continue
   a=re.fullmatch(r'\.(byte|2byte|4byte)\s+(.+)',l)
   if a:
    for arg in a[2].split(','):fields.append(({'byte':1,'2byte':2,'4byte':4}[a[1]],arg.strip()))
   elif l.startswith('map '):fields.extend([(1,'mapGroup'),(1,'mapNum')])
   elif l.startswith('stringvar '):fields.append((1,'stringVarId'))
   elif l.startswith('formatwarp '):fields.extend([(1,'mapGroup'),(1,'mapNum'),(1,'warpId'),(2,'x'),(2,'y')])
   else:extra.append(l)
  # trainerbattle has inline conditional bit assignments before its packed fields.
  extra=[x for x in extra if not x.startswith('.ifgt')]
  item={'macro':macro,'fields':fields,'size':1+sum(f[0] for f in fields)}
  if extra:unknown.append((m[1],macro,extra))
  else:
   if op in layouts and layouts[op]['size']!=item['size']:unknown.append((m[1],'conflict',layouts[op],item))
   else:layouts[op]=item
print('layouts',len(layouts),'uncovered',[(k,v) for k,v in constants.items() if v not in layouts]);print('unknown',unknown)
Path('work/script-layouts.json').write_text(json.dumps(layouts,indent=2))
