#!/usr/bin/env python3
"""PART5.5 current-source checks, event VM, allocations, maps, native regression boundary."""
from pathlib import Path
from collections import Counter,deque
import json,re,struct,hashlib,subprocess
import part55_compat
R=Path(__file__).resolve().parents[2];M=json.loads((R/'docs/project/part55-manifest.json').read_text());D=part55_compat.D
n=0
def read(f):return part55_compat.part6_source(f,(R/f).read_text())  # PART5.5 view: PART6 hunks reverted (check-part6.py covers PART6)
def old(f):return subprocess.check_output(['git','show',D['baseline']+':'+f],cwd=R,text=True,stderr=subprocess.PIPE)
def ok(label,condition=True):
 global n
 assert condition,label;n+=1;print('PASS',label)
for f in D['text']:part55_compat.source(f)
for f,h in D['sha256'].items():assert hashlib.sha256(part55_compat.part6_source(f,(R/f).read_text(encoding='utf-8')).encode()).hexdigest()==h,(f,'unrecorded edit')  # PART6 reverted first
# Reject new source edits that were never registered in the reviewed delta list.
changed=set(subprocess.check_output(['git','diff','--name-only',D['baseline']],cwd=R,text=True).splitlines())|set(subprocess.check_output(['git','ls-files','--others','--exclude-standard'],cwd=R,text=True).splitlines())
changed={f for f in changed if f.startswith(('src/','include/','data/','asm/'))}
_d6=json.loads((R/'docs/project/part6-deltas.json').read_text());changed-=(set(_d6['text'])|set(_d6['new_files']))-(set(D['text'])|set(D['binary'])|set(D['new_files']))  # PART6 scope is checked by check-part6.py
_d7=json.loads((R/'docs/project/part7-deltas.json').read_text());changed-=(set(_d7['text'])|set(_d7['new_files']))-(set(D['text'])|set(D['binary'])|set(D['new_files']))  # PART7 scope is checked by check-part7.py
assert changed==set(D['text'])|set(D['binary'])|set(D['new_files']),('unregistered source scope',changed^(set(D['text'])|set(D['binary'])|set(D['new_files'])))
assert not (R/'docs/story/PART5_FINAL.md').exists(),'PART5 must remain DRAFT'
ok('all approved source deltas strictly reversible; all new source hashes current')
ok('no existing binary terrain changed',not D['binary'])
for kind,f in [('flags','include/constants/flags.h'),('vars','include/constants/vars.h')]:
 slots=[]
 for name,value in M[kind].items():
  number=int(value,16);slots.append(number)
  assert re.search(r'^#define '+name+r'\s+0x0*'+format(number,'x')+r'\b',read(f),re.I|re.M),name
  before=next(x for x in old(f).splitlines() if re.match(r'^#define \w+\s+0x0*'+format(number,'x')+r'\b',x,re.I))
  assert 'Unused' in before,(name,before)
  alias=before.split()[1]
  refs=subprocess.run(['git','grep','-l','-w',alias,D['baseline'],'--','src','data','include','asm'],cwd=R,capture_output=True,text=True).stdout.splitlines()
  assert all(x.endswith(':'+f) for x in refs),(name,refs)
  defs=re.findall(r'^#define (\w+)\s+0x0*'+format(number,'x')+r'\b',read(f),re.I|re.M);defs=[x for x in defs if x.startswith('FLAG_' if kind=='flags' else 'VAR_')];assert defs==[name],(name,defs)
 assert len(set(slots))==len(slots)
 ok(f'{len(slots)} {kind}: baseline explicitly unused, no references/aliases/collisions')
ok('save ABI and mechanics configuration unchanged',all(read(f).encode()==subprocess.check_output(['git','show',D['baseline']+':'+f],cwd=R) for f in ['include/global.h','include/pokemon.h','include/constants/global.h','include/config/project.h','include/config/battle.h','include/config/species_enabled.h']))
ok('native 864 trainer save slots unchanged; extension roster only in ROM','#define MAX_TRAINERS_COUNT_EMERALD 864' in read('include/constants/opponents.h') and '#define PARTNER_COUNT 8' in read('include/constants/battle_partner.h'))
# Stable map IDs and original layouts remain prefixes; two small new rooms only.
layouts=json.loads(read('data/layouts/layouts.json'))['layouts'];ld={x['id']:x for x in layouts};groups=json.loads(read('data/maps/map_groups.json'));prior=json.loads(old('data/maps/map_groups.json'))
for k,v in prior.items():assert groups[k][:len(v)]==v if isinstance(v,list) else groups[k]==v
before=json.loads(old('data/layouts/layouts.json'))['layouts'];assert layouts[:len(before)]==before
ok('all existing map/layout IDs preserved; new room IDs appended')
allmaps={p.parent.name:json.loads(p.read_text()) for p in (R/'data/maps').glob('*/map.json')};byid={v['id']:v for v in allmaps.values()}
def grid(v):
 l=ld[v['layout']];raw=(R/l['blockdata_filepath']).read_bytes();return l['width'],l['height'],struct.unpack('<'+'H'*(len(raw)//2),raw)
def peak(obs):return max((sum(x<=t['x']<=x+19 and y<=t['y']<=y+16 for t in obs) for o in obs for x in [o['x'],o['x']-19] for y in [o['y'],o['y']-16]),default=0)
mapaudit={};actors=0
for name,v in allmaps.items():
 new=[o for o in v.get('object_events')or[] if o.get('script','').startswith('Part55_') or o.get('local_id','').startswith('LOCALID_PART55_')]
 backgrounds=[o for o in v.get('bg_events')or[] if o.get('script','').startswith('Part55_')]
 if not new and not backgrounds and name not in ['ArcheCampus_Maintenance','MagmaHideout_RescuePassage']:continue
 w,h,c=grid(v);obs=v.get('object_events')or[];occupied=Counter((o['x'],o['y']) for o in obs);warps={(o['x'],o['y']) for o in v.get('warp_events')or[]}
 for o in new:
  x,y=o['x'],o['y'];assert 0<=x<w and 0<=y<h,(name,o)
  assert ((c[y*w+x]>>10)&3)==0,(name,o,'collision')
  assert occupied[x,y]==1 and (x,y) not in warps,(name,o,'overlap')
  if o.get('local_id','').startswith('LOCALID_PART55_'):
   free={(xx,yy) for yy in range(h) for xx in range(w) if ((c[yy*w+xx]>>10)&3)==0}-set(occupied)
   adj={(x+1,y),(x-1,y),(x,y+1),(x,y-1)}&free
   assert adj,(name,o,'no free approach')
   visited={next(iter(adj))};todo=deque(visited)
   while todo:
    xx,yy=todo.popleft()
    for q in [(xx+1,yy),(xx-1,yy),(xx,yy+1),(xx,yy-1)]:
     if q in free and q not in visited:visited.add(q);todo.append(q)
   assert adj<=visited,(name,o,'new actor creates choke point')
  actors+=1
 for o in backgrounds:
  assert o['type']=='sign' and 0<=o['x']<w and 0<=o['y']<h,(name,o)
  assert any(0<=x<w and 0<=y<h and ((c[y*w+x]>>10)&3)==0 for x,y in [(o['x']-1,o['y']),(o['x']+1,o['y']),(o['x'],o['y']-1),(o['x'],o['y']+1)]),(name,o,'no interaction approach')
 try:p=json.loads(old(f'data/maps/{name}/map.json'));prev=peak(p.get('object_events')or[])
 except subprocess.CalledProcessError:prev=0
 current=peak(obs);assert current<=max(15,prev),(name,'viewport regression',current,prev)
 mapaudit[name]={'new_or_wrapped_actors':len(new),'backgrounds':len(backgrounds),'peak_npcs_conservative':current,'baseline_peak':prev}
 for warp in v.get('warp_events')or[]:
  if warp.get('dest_map') in byid and str(warp.get('dest_warp_id','')).isdigit():
   i=int(warp['dest_warp_id']);assert i in (127,255) or i<len(byid[warp['dest_map']].get('warp_events')or[]),(name,warp)
ok(f'{actors} actors and all new interaction points: bounds, passable tiles, distinct positions, no warp overlap')
ok(f'{len(mapaudit)} maps: viewport no regression, no new actor choke point, valid destination warp indices')
for name in ['ArcheCampus_Maintenance','MagmaHideout_RescuePassage']:
 v=allmaps[name];w,h,c=grid(v);assert w==10 and h==12 and all((c[6*w+x]>>10)&3 for x in range(1,9))
 assert f'.include "data/maps/{name}/scripts.inc"' in read('data/event_scripts.s')
 assert 'MAP_SCRIPT_ON_LOAD' in read(f'data/maps/{name}/scripts.inc')
ok('two physical gates closed in original grids, restored on load; native stair return warps included')
ok('Pokemon Center 2F / apartment upper closed',read('data/maps/ArcheCampus_PokemonCenter_1F/map.json')==old('data/maps/ArcheCampus_PokemonCenter_1F/map.json') and all('2F' not in w['dest_map'] for w in allmaps['ArcheCampus_Apartment']['warp_events']))
s=read('data/scripts/part55.inc');parts=dict(re.findall(r'^(Part55_\w+)::\n(.*?)(?=^\S[^\n]*:|\Z)',s,re.M|re.S))
def block(label):return parts['Part55_'+label]
texts=dict(re.findall(r'^(Part55_Text_\d+):\n\s*\.string "(.*)"$',s,re.M));font=json.loads(read('tools/poryscript/font_config.json'))['fonts']['1_chinese_rse']['widths'];count=0
for name,t in texts.items():
 assert t.endswith('$')
 for page in t[:-1].split('\\p'):
  ls=page.split('\\n');assert len(ls)<=2,(name,page)
  for line in ls:
   width=sum(font.get(c,6) for c in line);assert width<=208,(name,line,width);count+=1
ok(f'{len(texts)} Chinese texts / {count} lines fit 208px, two lines per page')
for item in M['items']:
 b=re.search(r'\[ITEM_'+item+r'\] =\n    \{.*?\n    \},',read('src/data/items.h'),re.S);assert b,item
 assert '.importance = 1' in b[0] and '.pocket = POCKET_KEY_ITEMS' in b[0] and '.price = 0' in b[0]
 name=re.search(r'ITEM_NAME\("([^"]*)"\)',b[0])[1];assert sum(2 if '\u4e00'<=c<='\u9fff' else 1 for c in name)<=20,(item,name)
ok(f'{len(M["items"])} inert quest/key items: unsellable/native name byte budgets')
# Every successful-gift branch guards bag failure before consuming token or completing state.
for m in re.finditer(r'^\tgiveitem (ITEM_\w+)(?:, \d+)?\n',s,re.M):
 following=s[m.end():];assert following.startswith('\tgoto_if_eq VAR_RESULT, FALSE, Part55_BagFull\n'),m[0]
ok('every added item gift immediately guards full-bag failure')
# Interpret actual field commands for full bag, retry, duplicate and out-of-order deliveries.
lines=[];labels={}
for raw in s.splitlines():
 line=raw.split('@')[0].strip()
 if re.fullmatch(r'\w+::?',line):labels[line.rstrip(':')]=len(lines)
 elif line and not line.startswith('.'):lines.append(line)
class VM:
 def __init__(self):self.vars=Counter();self.flags=set();self.defeated=set();self.items=Counter();self.gifts=Counter();self.bag=True;self.answer=1
 def val(self,a):return self.vars[a] if a.startswith('VAR_') else {'TRUE':1,'FALSE':0,'YES':1,'NO':0}.get(a,int(a) if a.isdigit() else a)
 def run(self,label):
  pc=labels['Part55_'+label];stack=[]
  for step in range(500):
   ins=lines[pc];pc+=1;cmd,*rest=ins.split(None,1);a=[x.strip() for x in rest[0].split(',')] if rest else []
   if cmd=='end':return
   if cmd=='return':
    if not stack:return
    pc=stack.pop();continue
   if cmd=='giveitem':
    self.vars['VAR_RESULT']=int(self.bag)
    if self.bag:self.items[a[0]]+=int(a[1]) if len(a)>1 else 1;self.gifts[a[0]]+=int(a[1]) if len(a)>1 else 1
   elif cmd=='checkitem':self.vars['VAR_RESULT']=int(self.items[a[0]]>=(int(a[1]) if len(a)>1 else 1))
   elif cmd=='removeitem':assert self.items[a[0]]>=int(a[1]);self.items[a[0]]-=int(a[1])
   elif cmd=='msgbox':
    if len(a)>1 and a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=self.answer
   elif cmd=='setvar':self.vars[a[0]]=self.val(a[1])
   elif cmd=='setflag':self.flags.add(a[0])
   elif cmd=='clearflag':self.flags.discard(a[0])
   elif cmd.startswith(('goto','call')):
    cond=True
    if cmd.endswith('_if_set'):cond=a[0] in self.flags
    elif cmd.endswith('_if_unset'):cond=a[0] not in self.flags
    elif cmd.endswith('_if_defeated'):cond=a[0] in self.defeated
    elif cmd.endswith('_if_eq'):cond=self.val(a[0])==self.val(a[1])
    elif cmd.endswith('_if_ne'):cond=self.val(a[0])!=self.val(a[1])
    elif cmd.endswith('_if_ge'):cond=self.val(a[0])>=self.val(a[1])
    elif cmd.endswith('_if_lt'):cond=self.val(a[0])<self.val(a[1])
    elif cmd not in ['goto','call']:raise AssertionError(ins)
    if cond:
     if cmd.startswith('call'):stack.append(pc)
     if a[-1]=='ShoalCave_LowTideEntranceRoom_EventScript_ShellBellExpert':return # explicitly reaches unchanged native recipe
     pc=labels[a[-1]]
   elif cmd in ['lock','lockall','release','releaseall','faceplayer','playmoncry','waitmoncry','applymovement','waitmovement','setobjectxy','setobjectxyperm','removeobject','hideobjectat','addobject','delay','fadescreen','closemessage','setmetatile','playse','dofieldeffectsparkle','waitfieldeffect']:pass
   else:raise AssertionError(('unsupported VM instruction on tested path',ins))
  raise AssertionError(('nonterminating',label))
for key,meta in M['quests'].items():
 if 'token' not in meta:continue
 v=VM();v.vars[meta['state']]=1;token='ITEM_'+meta['token'];reward='ITEM_'+meta['reward'];v.run(key);assert not v.gifts,(key,'out of order')
 v.items[token]=1;v.bag=False;v.run(key);assert v.vars[meta['state']]==1 and v.items[token]==1 and not v.gifts
 v.bag=True;v.run(key);v.run(key);assert v.vars[meta['state']]==3 and not v.items[token] and v.gifts[reward]==meta['count'],(key,v.gifts)
 ok(key+': actual script out-of-order/full-bag/retry/once/token-consumption')
for key,var,item,state,token in [('LuggageOwner','LUGGAGE','FULL_RESTORE',2,'CORRECT_LUGGAGE'),('Postman','AIR_MAIL','PIDGEOTITE',2,'DELIVERY_RECEIPT')]:
 v=VM();v.vars['VAR_PART55_'+var]=state;v.items['ITEM_'+token]=1;v.bag=False;v.run(key);assert v.vars['VAR_PART55_'+var]==state and v.items['ITEM_'+token]==1
 v.bag=True;v.run(key);v.run(key);assert v.gifts['ITEM_'+item]==1 and not v.items['ITEM_'+token]
 ok(key+': staged return token / full-bag retry / once')
for key,var,item,ready in [('BuoyResearcher','BUOY','DIVE_BALL',1),('SteelixForeman','STEELIX_REPAIR','STEELIXITE',1),('HoundourRescue','HOUNDOUR_RESCUE','HOUNDOOMINITE',1),('SampleStaff','SAMPLE_REWARD','RARE_CANDY',0)]:
 v=VM();v.vars['VAR_PART55_'+var]=ready
 if key=='SampleStaff':v.vars['VAR_PART55_SAMPLE_BITS']=7
 v.bag=False;v.run(key);assert not v.gifts and v.vars['VAR_PART55_'+var]!=3
 v.bag=True;v.run(key);v.run(key);assert v.vars['VAR_PART55_'+var]==3
 ok(key+': actual item once / pending on full bag')
v=VM();v.vars['VAR_PART55_DOLL']=1;v.items['ITEM_OLD_DOLL']=1;v.bag=False;v.run('DollGrandma');assert 'FLAG_PART5_BANETTITE' not in v.flags and v.items['ITEM_OLD_DOLL']==1
v.bag=True;v.run('DollGrandma');v.run('DollGrandma');assert v.gifts['ITEM_BANETTITE']==1 and 'FLAG_PART5_BANETTITE' in v.flags
v=VM();v.flags.add('FLAG_PART5_BANETTITE');v.vars['VAR_PART55_DOLL']=1;v.items['ITEM_OLD_DOLL']=1;v.run('DollGrandma');assert not v.gifts
ok('Banettite story full-bag/once and old collected-save migration')
# Other permanent rewards and battle-won/full-bag retry paths.
for key,var,ready,done,item in [('BeeRanger','BEE',7,15,'BEEDRILLITE'),('IceResearcher','ABOMASITE',0,3,'ABOMASITE'),('DeptChild','DEPT_CHILD',2,3,'RARE_CANDY'),('StarCalibration','STAR_CALIBRATION',15,31,'PP_UP'),('RescuedMagmaExit','HOUNDOUR_RESCUE',2,3,'HOUNDOOMINITE')]:
 v=VM();v.vars['VAR_PART55_'+var]=ready
 if key=='IceResearcher':v.vars['VAR_PART55_ICE_CRYSTALS']=7
 v.bag=False;v.run(key);assert not v.gifts and v.vars['VAR_PART55_'+var]!=done
 if key=='RescuedMagmaExit':assert 'FLAG_PART55_RESCUED_MAGMA_LEFT' not in v.flags
 v.bag=True;v.run(key)
 if key=='RescuedMagmaExit':assert 'FLAG_PART55_RESCUED_MAGMA_LEFT' in v.flags
 v.run(key);assert v.gifts['ITEM_'+item]==1 and v.vars['VAR_PART55_'+var]==done
 ok(key+': full-bag/retry/once with persistent progress')
for key,var,trainer,item in [('Advanced','ADVANCED_PATCH','ADVANCED_TRAINER','ABILITY_PATCH'),('Psychic','ALAKAZITE','PSYCHIC_RESEARCHER','ALAKAZITE'),('SafariExpert','SAFARI_EXPERT','SAFARI_EXPERT','KANGASKHANITE')]:
 v=VM();v.flags.add('FLAG_BADGE07_GET');v.defeated.add('TRAINER_PART55_'+trainer);v.bag=False;v.run(key);assert not v.gifts and v.vars['VAR_PART55_'+var]==0
 v.bag=True;v.run(key);v.run(key);assert v.gifts['ITEM_'+item]==1 and v.vars['VAR_PART55_'+var]==3
 ok(key+': won-battle state retains full-bag claim; no repeat')
v=VM();v.bag=False;v.run('WhiteRock');assert not v.flags;v.bag=True;v.run('WhiteRock');v.run('WhiteRock');assert v.gifts['ITEM_STAR_KEY']==1 and 'FLAG_PART55_STAR_KEY' in v.flags
ok('white rock Star Key: bag failure does not set flag; success once')
v=VM();v.vars['VAR_PART55_FROZEN_STONE']=1;v.items['ITEM_FROZEN_STONE']=1;v.bag=False;v.run('ShoalExpert');assert v.items['ITEM_FROZEN_STONE']==1 and v.vars['VAR_PART55_FROZEN_STONE']==1
v.bag=True;v.run('ShoalExpert');v.run('ShoalExpert');assert v.gifts['ITEM_GLALITITE']==1 and not v.items['ITEM_FROZEN_STONE'] and v.vars['VAR_PART55_FROZEN_STONE']==3
ok('Glalitite token retry/once; normal Shell Bell dialogue resumes afterwards')
# Living states / gates / cry-only mon NPCs / native mechanics preservation.
for label,token in [('UnderwaterResearcher','VAR_PART55_UNDERWATER_OBSERVATION'),('BasementLift','permission')]:
 if label=='UnderwaterResearcher':assert 'setvar '+token+', 1' in block(label) and 'setvar '+token+', 3' not in s
ok('underwater task accepted now, no completion/revelation; basement only inert interface','warp' not in block('BasementLift'))
for label in ['WorkSteelix','Houndour','BuoyMantyke','TeamupPuff','NetworkPorygon']:
 b=block(label);assert 'playmoncry' in b and 'msgbox' not in b,label
ok('map Pokemon native cries only; no human dialogue')
ok('temporary rookie ally opposes only two Aqua trainers; base fight retained','multi_2_vs_2 TRAINER_PART55_AQUA_OBSERVER_A' in block('RookieTeamup') and 'Part5_MagmaRookie' in s)
ok('Axew failed battles do not set hide/caught flag; captured flag is permanent','setwildbattle SPECIES_AXEW, PART55_AXEW_LEVEL' in block('Axew') and 'hideobjectat' in block('Axew') and 'setflag FLAG_PART55_AXEW_CAUGHT' not in block('Axew'))
ok('native Safari ball/step code untouched',read('src/safari_zone.c')==old('src/safari_zone.c') and 'special Part55_StartSafariBeedrill' in block('BeeTree3') and 'def_special Part55_StartSafariBeedrill, waitstate=1' in read('data/specials.inc'))
ok('native Shoal tide callbacks kept and Shell Bell recipe still four/four','giveitem ITEM_SHELL_BELL' in read('data/maps/ShoalCave_LowTideEntranceRoom/scripts.inc') and 'FLAG_PART55_SHELL_BELL_CRAFTED' in read('data/maps/ShoalCave_LowTideEntranceRoom/scripts.inc'))
ok('repeating Tri Attack and Helping Hand use native tutor, no once flag',all('move_tutor' in block(x) and 'FLAG_' not in block(x) for x in ['TriAttackTutor','HelpingHandTutor']))
items=read('src/data/items.h');ok('formal research-data name and same inert sealed-item hook','ITEM_NAME("来历不明的研究数据")' in items and 'ITEM_UNKNOWN_RESEARCH_DATA' in read('data/scripts/part4.inc'))
ok('formal Star Key name/once guard','ITEM_NAME("星之钥匙")' in items and 'FLAG_PART55_STAR_KEY' in s)
live='\n'.join(read(f) for f in D['text'])+s+items
ok('obsolete player-visible research name absent from live changed source','破坏因子' not in live and 'ITEM_DESTRUCTION_FACTOR' not in live)
# Party legal moves and Mega item availability are native data, no arbitrary generated game simulation.
learning=json.loads(read('src/data/pokemon/all_learnables.json'));p=read('src/data/battle_partners.party')
for roster in [p]+[read('src/data/trainers.party')]:
 for trainer,b in re.findall(r'^=== (\w+) ===\n(.*?)(?=^=== |\Z)',roster,re.M|re.S):
  if trainer not in M['trainer_aliases'] and not trainer.startswith('PARTNER_PART55_') and trainer not in ['PARTNER_STEVEN','TRAINER_TATE_AND_LIZA_1','TRAINER_MAXIE_MOSSDEEP','TRAINER_TABITHA_MOSSDEEP']:continue
  for mon in re.split(r'\n\s*\n',b):
   if 'Level:' not in mon:continue
   species=mon.splitlines()[0].split(' @ ')[0].upper();moves=re.findall(r'^- (.+)$',mon,re.M)
   for move in moves:assert 'MOVE_'+move.upper().replace(' ','_') in learning[species],(trainer,species,move)
ok('every new/changed trainer move legal for species')
rookie=re.search(r'=== PARTNER_PART55_ROOKIE ===\n(.*?)(?=^=== )',p,re.M|re.S)[1]
ok('rookie Jigglypuff only, Lv35 Eviolite, IV31 six stats; no evolution','Jigglypuff @ Eviolite\nLevel: 35\nIVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe' in rookie and rookie.count('Level:')==1)
gym=re.search(r'=== TRAINER_TATE_AND_LIZA_1 ===\n(.*?)(?=^=== )',read('src/data/trainers.party'),re.M|re.S)[1]
ok('six-member seventh gym native double; Alakazam stone','Double Battle: Yes' in gym and gym.count('Level:')==6 and 'Alakazam @ Alakazite' in gym and 'EVs:' not in gym)
ok('advanced Mega Medicham / Steven Mega Metagross / Maxie Mega Camerupt','Medicham @ Medichamite' in p and 'Metagross @ Metagrossite' in p and 'Camerupt @ Cameruptite' in re.search(r'=== TRAINER_MAXIE_MOSSDEEP ===\n(.*?)(?=^=== )',read('src/data/trainers.party'),re.M|re.S)[1])
# No new Mega stones in infinite marts and no premium gear stock regression.
s5=read('data/scripts/part5.inc');marts=re.findall(r'^(Part5_Mart_\w+):\n(.*?)pokemartlistend',s5,re.M|re.S);sold=''.join(b for _,b in marts)
ok('Mega stones not in ordinary shop lists',not set(re.findall(r'ITEM_\w+',sold)) & {item for item,body in re.findall(r'\[(ITEM_\w+)\] =\n    \{(.*?)\n    \},',items,re.S) if 'HOLD_EFFECT_MEGA_STONE' in body})
ok('premium limited stock table unchanged',read('src/limited_shop.c')==old('src/limited_shop.c'))
ok('TM51/unlimited native TM rule unchanged',read('include/config/item.h')==old('include/config/item.h') and 'ITEM_TM_TRICK_ROOM' in read('data/maps/MtPyre_Summit/map.json') and 'I_REUSABLE_TMS' in read('include/config/item.h'))
# Four Safari additions keep every previously unique species and exact PART5 slots.
wild=json.loads(read('src/data/wild_encounters.json'));before=json.loads(old('src/data/wild_encounters.json'))
entries=lambda v:{e['map']:e for g in v['wild_encounter_groups'] for e in g.get('encounters',[]) if 'map' in e}
a,b=entries(wild),entries(before)
for mapid,species in [('MAP_SAFARI_ZONE_SOUTH','WEEDLE'),('MAP_SAFARI_ZONE_SOUTHWEST','CHANSEY'),('MAP_SAFARI_ZONE_NORTH','TAUROS'),('MAP_SAFARI_ZONE_NORTHWEST','KANGASKHAN')]:
 aa=a[mapid]['land_mons']['mons'];bb=b[mapid]['land_mons']['mons'];assert aa[10]['species']=='SPECIES_'+species and all(x==y for i,(x,y) in enumerate(zip(aa,bb)) if i!=10);assert {x['species'] for x in bb}<={x['species'] for x in aa}
ok('Safari unique native/PART5 species preserved; four audited duplicate slots added')
ok('slowbro reward deferred; no invented wild encounter','giveitem ITEM_SLOWBRONITE' not in s)
(R/'docs/project/part55-capacity.json').write_text(json.dumps(mapaudit,ensure_ascii=False,indent=2)+'\n')
print(f'PART5.5 static/event checks: {n} groups PASS. Gameplay still requires manual testing.')