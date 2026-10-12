from pathlib import Path
from collections import Counter
import json,re,subprocess
r=Path(__file__).resolve().parents[2]
if not (r/'Makefile').exists():r=Path('/home/pokemon/projects/emerald-story')
m=json.loads((r/'docs/project/part3-northwest-manifest.json').read_text());font=json.loads((r/'tools/poryscript/font_config.json').read_text())['fonts']['1_chinese_rse']['widths']
def read(f):return (r/f).read_text()
def old(f):return subprocess.check_output(['git','show',m['baseline']+':'+f],cwd=r,text=True)
folders=['Route113','Route113_GlassWorkshop','FallarborTown','FallarborTown_Mart','FallarborTown_MoveRelearnersHouse','Route114','Route114_LanettesHouse','Route114_FossilManiacsTunnel']
alltext='\n'.join(read('data/maps/'+f+'/scripts.inc') for f in folders)
labels={};current=None
for raw in alltext.splitlines():
 z=re.fullmatch(r'(\w+)::?',raw.strip())
 if z:current=z.group(1);labels[current]=[]
 elif current and raw.strip() and not raw.strip().startswith(('.', '@')):labels[current].append(raw.strip().split('@')[0].strip())
class VM:
 def __init__(self):self.flags=set();self.vars={'VAR_RESULT':0};self.bag=True;self.gifts=Counter();self.removals=Counter();self.choice=1;self.menu=7;self.egg=False;self.chosen=True;self.moves=True;self.teach=True;self.learns=0;self.species=set();self.messages=[];self.switch_var='VAR_RESULT'
 def value(self,x):
  if x.startswith('ITEM_'):return x
  return {'FALSE':0,'TRUE':1,'YES':1,'NO':0,'PARTY_NOTHING_CHOSEN':255,'HEAT_ROCK_PRICE':1500,'LOWEST_ASH_PRICE':250,'ITEM_NONE':0}.get(x,self.vars.get(x,0)) if not x.isdecimal() else int(x)
 def run(self,label):
  stack=[];pc=0
  for step in range(600):
   if pc>=len(labels[label]):
    if not stack:return
    label,pc=stack.pop();continue
   line=labels[label][pc];pc+=1;a=[t.strip() for t in re.split(r'[ ,]+',line)];cmd=a.pop(0)
   def jump(t):
    nonlocal label,pc
    label=t;pc=0
   if cmd in ('lock','lockall','faceplayer','release','releaseall','applymovement','waitmovement','waitstate','waitmessage','closemessage','fadescreen','playse','waitse','playfanfare','waitfanfare','delay','setmoverelearnerstate','bufferitemname','bufferdecorationname','buffernumberstring'):continue
   if cmd=='end':return
   if cmd=='return':
    if not stack:return
    label,pc=stack.pop();continue
   if cmd=='goto':jump(a[0]);continue
   if cmd=='call':
    if a[0].startswith('Common_EventScript_'):continue
    stack.append((label,pc));jump(a[0]);continue
   if cmd in ('goto_if_set','goto_if_unset','call_if_set','call_if_unset'):
    good=(a[0] in self.flags)==cmd.endswith('_set')
    if good:
     if cmd.startswith('call'):stack.append((label,pc))
     jump(a[1])
    continue
   if cmd.startswith('goto_if_') or cmd.startswith('call_if_'):
    lhs,rhs=self.value(a[0]),self.value(a[1]);good={'eq':lhs==rhs,'ne':lhs!=rhs,'lt':lhs<rhs,'ge':lhs>=rhs,'gt':lhs>rhs,'le':lhs<=rhs}[cmd.rsplit('_',1)[1]]
    if good:
     if cmd.startswith('call'):stack.append((label,pc))
     jump(a[2])
    continue
   if cmd=='setflag':self.flags.add(a[0]);continue
   if cmd=='clearflag':self.flags.discard(a[0]);continue
   if cmd=='setvar':self.vars[a[0]]=self.value(a[1]);continue
   if cmd=='subvar':self.vars[a[0]]=self.value(a[0])-self.value(a[1]);continue
   if cmd in ('msgbox','message'):
    self.messages.append(a[0])
    if len(a)>1 and a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=self.choice
    continue
   if cmd=='giveitem':
    item=a[0] if a[0].startswith('ITEM_') else self.vars[a[0]];qty=self.value(a[1]) if len(a)>1 else 1
    self.vars['VAR_RESULT']=int(self.bag)
    if self.bag:self.gifts[item]+=qty
    continue
   if cmd=='removeitem':self.removals[a[0]]+=self.value(a[1]) if len(a)>1 else 1;continue
   if cmd=='checkitem':self.vars['VAR_RESULT']=int(self.gifts[a[0]]-self.removals[a[0]]>0);continue
   if cmd=='checkspecies':self.vars['VAR_RESULT']=int(a[0] in self.species);continue
   if cmd=='chooseboxmon':self.vars['VAR_0x8004']=0 if self.chosen else 255;continue
   if cmd=='special':
    name=a[0]
    if name=='IsSelectedMonEgg':
     self.vars['VAR_RESULT']=int(self.egg)
     if self.egg:self.chosen=False
    elif name=='Special_HasMoveToRelearn':
     self.vars['VAR_RESULT']=int(self.moves)
     if not self.moves:self.chosen=False
    elif name=='TeachMoveRelearnerMove':
     self.vars['VAR_RESULT']=int(self.teach)
     if self.teach:self.learns+=1
     else:self.chosen=False
    elif name=='ShowScrollableMultichoice':self.vars['VAR_RESULT']=self.menu
    else:raise AssertionError(name)
    continue
   if cmd=='switch':self.switch_var=a[0];continue
   if cmd=='case':
    if self.value(self.switch_var)==self.value(a[0]):jump(a[1])
    continue
   if cmd in ('playmoncry','waitmoncry'):continue
   raise AssertionError((label,line))
  raise AssertionError(('infinite loop',label))
# Actual script transaction checks.
for script,item,qty,flag,pre in [
 ('Route113_Part3_Painter','ITEM_PRETTY_FEATHER',1,'FLAG_PART3_RECEIVED_PRETTY_FEATHER','FLAG_PART3_ROUTE113_VIEW_EXAMINED'),
 ('FallarborTown_Part3_Collector','ITEM_STAR_PIECE',1,'FLAG_PART3_RECEIVED_STAR_PIECE',None),
 ('Route114_LanettesHouse_Part3_TryGift','ITEM_ULTRA_BALL',3,'FLAG_PART3_RECEIVED_LANETTE_ULTRA_BALLS',None)]:
 v=VM()
 if pre:v.run(script);assert not v.gifts;v.flags.add(pre)
 v.bag=False;v.run(script);assert flag not in v.flags and not v.gifts
 v.bag=True;v.run(script);v.run(script);assert v.gifts[item]==qty and flag in v.flags
v=VM();v.run('Route113_Part3_View');assert 'FLAG_PART3_ROUTE113_VIEW_EXAMINED' in v.flags
for found in [False,True]:
 v=VM()
 if found:v.species.add('SPECIES_SPINDA')
 v.run('Route113_Part3_SpindaKid');assert ('Route113_Part3_SpindaKidPartyText' in v.messages)==found
# Free success remains free with/without heart scale; second success consumes one.
for scales in [0,3]:
 v=VM();v.gifts['ITEM_HEART_SCALE']=scales;v.run('FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove');assert v.learns==1 and 'FLAG_PART3_FREE_MOVE_RELEARN_USED' in v.flags and not v.removals
 if scales:
  v.run('FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove');assert v.learns==2 and v.removals['ITEM_HEART_SCALE']==1
 else:v.run('FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove');assert v.learns==1
for boundary in ['choice','chosen','egg','moves','teach']:
 v=VM()
 if boundary=='choice':v.choice=0
 if boundary=='chosen':v.chosen=False
 if boundary=='egg':v.egg=True
 if boundary=='moves':v.moves=False
 if boundary=='teach':v.teach=False
 v.run('FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove');assert not v.learns and 'FLAG_PART3_FREE_MOVE_RELEARN_USED' not in v.flags and not v.removals
# Glass item: ash insufficient, cancellation, full bag pending, retry and repeat.
for ash,choice in [(1499,1),(1500,0)]:
 v=VM();v.vars['VAR_ASH_GATHER_COUNT']=ash;v.vars['VAR_GLASS_WORKSHOP_STATE']=2;v.choice=choice;v.menu=8
 v.run('Route113_GlassWorkshop_Part3_HeatRock');assert v.vars['VAR_ASH_GATHER_COUNT']==ash and not v.gifts
v=VM();v.vars['VAR_ASH_GATHER_COUNT']=3000;v.vars['VAR_GLASS_WORKSHOP_STATE']=2;v.bag=False
v.run('Route113_GlassWorkshop_Part3_HeatRock');assert v.vars['VAR_ASH_GATHER_COUNT']==1500 and v.vars['VAR_GLASS_WORKSHOP_STATE']==17 and not v.gifts
v.bag=True;v.run('Route113_GlassWorkshop_EventScript_GiveItemAfterNoRoom');assert v.gifts['ITEM_HEAT_ROCK']==1 and v.vars['VAR_ASH_GATHER_COUNT']==1500 and v.vars['VAR_GLASS_WORKSHOP_STATE']==2
v.run('Route113_GlassWorkshop_Part3_HeatRock');assert v.gifts['ITEM_HEAT_ROCK']==2 and v.vars['VAR_ASH_GATHER_COUNT']==0
# Verify actual positions, independent of the placement helper, against the final collision grid.
import struct
layouts={x['id']:x for x in json.loads(read('data/layouts/layouts.json'))['layouts']}
for folder in sorted({o['map'] for o in m['objects']}):
 v=json.loads(read(f'data/maps/{folder}/map.json'));l=layouts[v['layout']];w,h=l['width'],l['height'];cells=struct.unpack('<'+'H'*(w*h),(r/l['blockdata_filepath']).read_bytes())
 ground={(x,y) for y in range(h) for x in range(w) if (cells[y*w+x]>>10)&3==0 and cells[y*w+x]>>12 in (0,3)}
 occupied={(o['x'],o['y']) for o in v['object_events']}
 for o in [o for o in m['objects'] if o['map']==folder]:
  assert {k:z for k,z in o.items() if k!='map'} in v['object_events']
  p=o['x'],o['y'];assert p in ground and o['elevation']==cells[p[1]*w+p[0]]>>12
  adjacent={(p[0]-1,p[1]),(p[0]+1,p[1]),(p[0],p[1]-1),(p[0],p[1]+1)}&(ground-occupied);assert adjacent
  seen={next(iter(adjacent))};q=list(seen)
  for x,y in q:
   for n in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
    if n in ground-occupied and n not in seen:seen.add(n);q.append(n)
  assert adjacent<=seen,(folder,p,'blocks path')
 maximum=max(sum(x-9<=o['x']<=x+10 and y-7<=o['y']<=y+9 for o in v['object_events']) for x,y in ground)
 assert maximum<=15,(folder,'viewport saturation',maximum)
 print(folder,'collision/access/viewport:',maximum,'simultaneously visible objects maximum')
# Native cry-only interactions.
for label,species in [('Route113_Part3_SpindaCry','SPINDA'),('Route113_Part3_OddishCry','ODDISH'),('Route114_Part3_SkittyCry','SKITTY')]:
 block='\n'.join(labels[label]);assert 'playmoncry SPECIES_'+species+', CRY_MODE_NORMAL' in block and 'waitmoncry' in block and all(x not in block for x in ['msgbox','giveitem','setwildbattle'])
for f in ['Route113','FallarborTown','Route114']:
 cur=json.loads(read(f'data/maps/{f}/map.json'));prior=json.loads(old(f'data/maps/{f}/map.json'))
 for key in ['object_events','bg_events','warp_events','coord_events']:assert cur[key][:len(prior[key])]==prior[key],(f,key)
 assert cur['warp_events']==prior['warp_events'] and cur['coord_events']==prior['coord_events']
# Lanette original decoration and PC registration instructions preserved exactly.
s=read('data/maps/Route114_LanettesHouse/scripts.inc').split('Route114_LanettesHouse_Part3_TryGift::')[0].replace('\tcall Route114_LanettesHouse_Part3_TryGift\n','')
def instructions(s):return re.sub(r'\s+','',re.sub(r'(?m)^\s*\.string[^\n]*\n?','',s))
assert instructions(s)==instructions(old('data/maps/Route114_LanettesHouse/scripts.inc'))
# All changed/new text blocks stay within font budget, including substitution names.
for label in m['texts']:
 match=re.search(r'(?m)^'+re.escape(label)+r':\n\s*\.string "([^"\n]*)"',alltext);assert match,label
 for line in re.split(r'\\[npl]',match[1]):
  width=sum(42 if x=='{PLAYER}' else 78 if x.startswith('{') else font.get(x,6) for x in re.findall(r'\{[^}]*\}|.',line.replace('$','')));assert width<=196,(label,width)
assert 'task->tNumItems = 9;' in read('src/field_specials.c')
print('PART3 northwest: gift full-bag/retry/repeat, scene/party conditions, free→paid learning/cancel, paid ash pending/retry, cry-only, original objects/warps/triggers/PC gift, Chinese width: PASS')
