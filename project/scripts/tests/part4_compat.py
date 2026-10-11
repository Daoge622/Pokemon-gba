"""Explicit PART4 delta removal for historical fixed-snapshot tests.
Actual PART4 is checked first by check-part4.py. Every inverse is constrained;
this never substitutes arbitrary current engine changes with an old snapshot.
"""
from pathlib import Path
import json,re,subprocess
from part5_compat import source as part5_source
R=Path(__file__).resolve().parents[2]
BASE='pre-part4-implementation'
M=json.loads((R/'docs/project/part4-manifest.json').read_text())
def baseline(f):return subprocess.check_output(['git','show',BASE+':'+f],cwd=R,text=True)
def shop(s):
 s=s.replace('return flag != 0 && GetLimitedShopRemaining((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum, item) == 0;','return flag != 0 && FlagGet(flag);')
 a='    if (GetCurrentLimitedShopFlag(tItemId) != 0)\n    {\n        u16 remaining = GetLimitedShopRemaining((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum, tItemId);\n        if (sShopData->maxQuantity > remaining)\n            sShopData->maxQuantity = remaining;\n    }'
 s=s.replace(a,'    if (GetCurrentLimitedShopFlag(tItemId) != 0)\n        sShopData->maxQuantity = 1;')
 s=s.replace('tItemCount == 0 || tItemCount > GetLimitedShopRemaining((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum, tItemId)','FlagGet(purchaseFlag) || tItemCount != 1')
 s=s.replace('RecordLimitedShopPurchase((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum, tItemId, tItemCount);','FlagSet(GetCurrentLimitedShopFlag(tItemId));')
 assert s==baseline('src/shop.c'),'unexpected engine change outside stock extension'
 return s
NEW_ITEMS=['TRAVELER_CANTEEN','BERRY_BASKET','LOST_KITE','POSTAL_PARCEL','DESTRUCTION_FACTOR']
def items(s):
 for name in NEW_ITEMS:
  pat=r'    \[ITEM_'+name+r'\] =\n    \{.*?\n    \},\n'
  s,n=re.subn(pat,'',s,count=1,flags=re.S);assert n==1,name
 assert s.strip()==baseline('src/data/items.h').strip()
 return baseline('src/data/items.h')
def wild(s):
 v=json.loads(s);b=json.loads(baseline('src/data/wild_encounters.json'));entries={e['map']:e for g in b['wild_encounter_groups'] for e in g.get('encounters',[]) if 'map' in e}
 for g in v['wild_encounter_groups']:
  if 'encounters' not in g:continue
  g['encounters']=[e for e in g['encounters'] if e.get('map') not in ['MAP_NEW_MAUVILLE_MAINTENANCE','MAP_NEW_MAUVILLE_HIGH_VOLTAGE']]
  for e in g['encounters']:
   if e.get('map') in ['MAP_ROUTE111','MAP_ROUTE119']:e['land_mons']=entries[e['map']]['land_mons']
 assert v==b,'unapproved wild encounter changes'
 return json.dumps(v)
def parties(s):
 b=baseline('src/data/trainers.party')
 for name in M['trainers']:
  pat=r'^=== '+name+r' ===\n.*?(?=^=== |\Z)';prior=re.search(pat,b,re.M|re.S)
  s,n=re.subn(pat,lambda _:prior[0] if prior else '',s,count=1,flags=re.M|re.S);assert n==1,name
 assert re.sub(r'\s+','',s)==re.sub(r'\s+','',b),'unapproved trainer edits'
 return b
def map_json(f,s):
 name=f.split('/')[2]
 if name not in M['maps']:return s
 v=json.loads(s);b=json.loads(baseline(f));meta=M['maps'][name]
 v['object_events']=[o for o in v['object_events'] if not str(o.get('local_id','')).startswith('LOCALID_PART4_')]
 if name=='Route111':
  o=next(o for o in v['object_events'] if o.get('local_id')=='LOCALID_PART3_DESERT_VISIBLE_ITEM');assert o['trainer_sight_or_berry_tree_id']=='ITEM_BRIGHT_POWDER';o['trainer_sight_or_berry_tree_id']='ITEM_MAX_REVIVE'
 for entry in meta['backgrounds']:
  assert entry in v['bg_events'];v['bg_events'].remove(entry)
 v['coord_events']=[x for x in v['coord_events'] if not x.get('script','').startswith('Part4_')]
 if name in ['NewMauville_Inside','ScorchedSlab']:v['warp_events']=v['warp_events'][:-1]
 assert v==b,(name,'native map events changed beyond explicit PART4 additions')
 return baseline(f)
def source(f,s=None):
 if s is None:s=(R/f).read_text()
 s=part5_source(f,s)  # PART5 hunks removed first; see part5_compat.py
 if f=='src/shop.c':return shop(s)
 if f=='src/data/items.h':return items(s)
 if f=='src/data/wild_encounters.json':return wild(s)
 if f=='src/data/trainers.party':return parties(s)
 if f.startswith('data/maps/') and f.endswith('/map.json'):return map_json(f,s)
 if f=='data/maps/MauvilleCity/scripts.inc':return s.replace('\tcall Part4_WattsonReaction\n','')
 if f=='include/limited_shop.h':
  s=s.replace('u16 GetLimitedShopRemaining(u16 map, enum Item item);\n','').replace('void RecordLimitedShopPurchase(u16 map, enum Item item, u16 count);\n','')
  assert re.sub(r'\s+','',s)==re.sub(r'\s+','',baseline(f))
  return baseline(f)
 if f=='include/constants/opponents.h':
  s=re.sub(r'^#define TRAINER_PART4_\w+[^\n]*\n','',s,flags=re.M);s=re.sub(r'(#define TRAINERS_COUNT_EMERALD\s+)864\b',r'\g<1>861',s)
  assert re.sub(r'\s+','',s)==re.sub(r'\s+','',baseline(f));return baseline(f)
 return s
