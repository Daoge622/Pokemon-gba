#!/usr/bin/env python3
"""PART3 source/data checks only. Never loads or runs a ROM or emulator."""
from pathlib import Path
from collections import Counter
import json,re,subprocess
r=Path(__file__).resolve().parents[2]
if not (r/'Makefile').exists():r=Path('/home/pokemon/projects/emerald-story')
from part4_compat import source as part4_source
def read(f):return part4_source(f,(r/f).read_text())
def old(f):return subprocess.check_output(['git','show','pre-part3-implementation:'+f],cwd=r,text=True)
weights=[20,20,10,10,10,10,5,5,4,4,1,1]
wild=json.loads(read('src/data/wild_encounters.json'));baseline=json.loads(old('src/data/wild_encounters.json'))
def entries(j):return {e['map']:e for g in j['wild_encounter_groups'] for e in g.get('encounters',[]) if 'map' in e}
a,b=entries(baseline),entries(wild)
expected={
 'MAP_FIERY_PATH':{'SPECIES_NUMEL':30,'SPECIES_KOFFING':24,'SPECIES_MACHOP':10,'SPECIES_SLUGMA':14,'SPECIES_TORKOAL':10,'SPECIES_MAGBY':5,'SPECIES_HOUNDOUR':5,'SPECIES_GRIMER':2},
 'MAP_ROUTE114':{'SPECIES_SWABLU':34,'SPECIES_LOTAD':25,'SPECIES_ZANGOOSE':10,'SPECIES_SEVIPER':10,'SPECIES_LOMBRE':20,'SPECIES_NUZLEAF':1},
 'MAP_METEOR_FALLS_1F_1R':{'SPECIES_ZUBAT':55,'SPECIES_SOLROCK':15,'SPECIES_LUNATONE':15,'SPECIES_CLEFAIRY':5,'SPECIES_GEODUDE':10},
 'MAP_JAGGED_PASS':{'SPECIES_NUMEL':55,'SPECIES_MACHOP':10,'SPECIES_SPOINK':20,'SPECIES_PHANPY':10,'SPECIES_RHYHORN':5},
}
assert set(a)==set(b)
for name,target in expected.items():
 e=b[name];actual=Counter()
 assert len(e['land_mons']['mons'])==12
 for chance,m in zip(weights,e['land_mons']['mons']):
  actual[m['species']]+=chance
  assert 1<=m['min_level']<=m['max_level']<=100
 assert actual==target,(name,dict(actual),target)
 assert e['land_mons']['encounter_rate']==a[name]['land_mons']['encounter_rate']
 methods={'land_mons','fishing_mons'} if name=='MAP_ROUTE114' else {'land_mons'}
 assert {k:v for k,v in e.items() if k not in methods}=={k:v for k,v in a[name].items() if k not in methods},name
 print(name,'land %',dict(actual))
for name in a:
 if name not in expected:assert a[name]==b[name],('unrelated wild table',name)
fish=b['MAP_ROUTE114']['fishing_mons'];prior=a['MAP_ROUTE114']['fishing_mons'];assert fish['encounter_rate']==prior['encounter_rate']
for rod,slots,chances,target in [('Old Rod',[0,1],[70,30],{'SPECIES_BARBOACH':70,'SPECIES_GOLDEEN':30}),('Good Rod',[2,3,4],[60,20,20],{'SPECIES_BARBOACH':60,'SPECIES_GOLDEEN':20,'SPECIES_MAGIKARP':20}),('Super Rod',[5,6,7,8,9],[40,40,15,4,1],{'SPECIES_BARBOACH':100})]:
 actual=Counter()
 for slot,chance in zip(slots,chances):actual[fish['mons'][slot]['species']]+=chance
 assert actual==target,(rod,actual)
 print('Route114',rod,'%',dict(actual))
# Original later Bagon habitat stays exact, with no new early Bagon entries.
assert all(m['species']!='SPECIES_BAGON' for e in expected for m in b[e]['land_mons']['mons'])
for name,e in a.items():
 if any(m.get('species')=='SPECIES_BAGON' for method in ['land_mons','water_mons','fishing_mons','rock_smash_mons'] for m in e.get(method,{}).get('mons',[])):assert e==b[name],name
# Exact approved 10 trainer parties; no other pre-existing team edits.
party=read('src/data/trainers.party');before=old('src/data/trainers.party')
def parties(s):return dict(re.findall(r'^=== (TRAINER_\w+) ===\n(.*?)(?=^=== |\Z)',s,re.M|re.S))
pa,pb=parties(before),parties(party)
expected_teams={
 'TRAINER_PART3_BREEDER':[('Pichu',20,6,None),('Cleffa',20,6,None),('Igglybuff',21,6,None)],
 'TRAINER_PART3_PLUSLE_MINUN':[('Plusle',22,6,None),('Minun',22,6,None)],
 'TRAINER_PART3_HIKER':[('Geodude',22,6,None),('Machop',22,6,None)],
 'TRAINER_PART3_MAGMA_ROOKIE':[('Jigglypuff',20,31,None)],
 'TRAINER_VICTOR':[('Taillow',21,3,'Oran Berry'),('Zigzagoon',21,3,'Oran Berry')],
 'TRAINER_VICTORIA':[('Roselia',22,6,'Oran Berry')],
 'TRAINER_VIVI':[('Marill',23,12,None),('Shroomish',23,12,None),('Numel',23,12,None)],
 'TRAINER_VICKY':[('Meditite',24,12,None)],
 'TRAINER_MAXIE_MT_CHIMNEY':[('Mightyena',25,12,None),('Golbat',25,12,None),('Houndoom',26,12,None),('Camerupt',27,12,None)],
 'TRAINER_FLANNERY_1':[('Slugma',26,12,None),('Ninetales',27,12,None),('Camerupt',28,12,None),('Torkoal',29,18,'Oran Berry')],
}
old_changes={'TRAINER_VICTOR','TRAINER_VICTORIA','TRAINER_VIVI','TRAINER_VICKY','TRAINER_MAXIE_MT_CHIMNEY','TRAINER_FLANNERY_1'}
assert set(pb)-set(pa)==set(expected_teams)-old_changes
for name in pa:
 if name not in old_changes:assert pa[name].strip()==pb[name].strip(),('unrelated trainer',name)
constants=read('include/constants/trainers.h')+'\n'+read('include/constants/battle_ai.h')
lu=read('src/data/pokemon/level_up_learnsets/gen_9.h');teach=read('src/data/pokemon/teachable_learnsets.h');all_learnable=json.loads(read('src/data/pokemon/all_learnables.json'))
expected_classes={'TRAINER_PART3_BREEDER':('Pkmn Breeder','Pokemon Breeder M','Male'),'TRAINER_PART3_PLUSLE_MINUN':('Twins','Twins','Twins'),'TRAINER_PART3_HIKER':('Hiker','Hiker','Hiker'),'TRAINER_PART3_MAGMA_ROOKIE':('Team Magma','Magma Grunt F','Magma')}
explicit=0;default=0
for name,target in expected_teams.items():
 raw=pb[name]
 for field,prefix in [('Class','TRAINER_CLASS_'),('Pic','TRAINER_PIC_'),('Music','TRAINER_ENCOUNTER_MUSIC_')]:
  value=re.search(r'^'+field+r': (.+)$',raw,re.M).group(1);const=prefix+value.upper().replace(' ','_')
  assert re.search(r'\b'+const+r'\b',constants),(name,field,value,const)
 if name in expected_classes:
  assert tuple(re.search(r'^'+field+r': (.+)$',raw,re.M).group(1) for field in ['Class','Pic','Music'])==expected_classes[name]
 assert ('Double Battle: Yes' in raw)==(name=='TRAINER_PART3_PLUSLE_MINUN')
 chunks=re.split(r'\n\s*\n',raw.strip());mon_blocks=[q for q in chunks if '\nLevel:' in '\n'+q];actual=[]
 for block in mon_blocks:
  first=block.splitlines()[0];species,sep,item=first.partition(' @ ');level=int(re.search(r'^Level: (\d+)$',block,re.M).group(1));ivs=re.search(r'^IVs: (.+)$',block,re.M).group(1)
  iv_values={stat:int(n) for n,stat in re.findall(r'(\d+) (HP|Atk|Def|SpA|SpD|Spe)',ivs)};assert set(iv_values)=={'HP','Atk','Def','SpA','SpD','Spe'} and len(set(iv_values.values()))==1
  actual.append((species,level,next(iter(iv_values.values())),item if sep else None));assert 'EVs:' not in block
  assert species.upper() in all_learnable,species
  learning=re.search(r's'+species+r'LevelUpLearnset\[\].*?\n};',lu,re.S).group();teachable=re.search(r's'+species+r'TeachableLearnset\[\].*?\n};',teach,re.S).group()
  moves=re.findall(r'^- (.+)$',block,re.M)
  if not moves:
   default+=1;assert re.search(r'LEVEL_UP_MOVE\(\s*(\d+),\s*MOVE_\w+\)',learning),species
  else:
   assert len(moves)==4
   for move in moves:
    const='MOVE_'+move.upper().replace(' ','_');assert const in all_learnable[species.upper()],(name,species,move,'not in species compatibility source')
    assert re.search(r'\b'+const+r'\b',learning+'\n'+teachable),(name,species,move,'not in current Gen9 or enabled teaching table')
    explicit+=1
  assert item not in ['Focus Sash','Leftovers','Choice Specs','Choice Band','Choice Scarf']
 assert actual==target,(name,actual,target)
 print(name,actual)
# Boss items and intended legal replacements; these are supported species moves rather than
# a restriction that scripted NPCs must have learned every move at their displayed level.
assert '- Work Up' in pb['TRAINER_VICKY'] and '- Meditate' not in pb['TRAINER_VICKY']
assert '- Aerial Ace' in pb['TRAINER_MAXIE_MT_CHIMNEY'] and '- Wing Attack' not in pb['TRAINER_MAXIE_MT_CHIMNEY']
assert '- Incinerate' in pb['TRAINER_FLANNERY_1'] and '- Flame Burst' not in pb['TRAINER_FLANNERY_1'] and '- Mist' not in pb['TRAINER_FLANNERY_1'] and '- Curse' in pb['TRAINER_FLANNERY_1']
for name in ['TRAINER_MAXIE_MT_CHIMNEY','TRAINER_FLANNERY_1']:assert 'Items: Super Potion / Super Potion' in pb[name]
rookie=pb['TRAINER_PART3_MAGMA_ROOKIE'];assert 'Gender: Female' in rookie and 'Name: 手下' in rookie and '31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe' in rookie
# Dusk Ball uses the existing generic transaction and map+item lookup, original price unchanged.
shop=read('src/limited_shop.c');assert '{ MAP_FALLARBOR_TOWN_MART, ITEM_DUSK_BALL, FLAG_PART3_BOUGHT_DUSK_BALL }' in shop
mart=read('data/maps/FallarborTown_Mart/scripts.inc');assert '\t.2byte ITEM_DUSK_BALL\n' in mart and '\t.2byte ITEM_MOON_STONE' not in mart
assert mart.replace('\t.2byte ITEM_DUSK_BALL\n','',1)==old('data/maps/FallarborTown_Mart/scripts.inc')
assert read('src/data/items.h')==old('src/data/items.h') and read('src/shop.c')==old('src/shop.c')
print('PART3 data: four weighted land tables, three rods, later Bagon and all unrelated tables preserved; ten exact teams/classes/music/IV/items,',explicit,'supported explicit moves and',default,'native automatic movesets; Dusk generic limited shop: PASS')
