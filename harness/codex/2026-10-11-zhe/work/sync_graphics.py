from pathlib import Path
import json,hashlib,difflib,shutil
project=Path(r'E:\Pekemon Gba\project');root=Path(__file__).resolve().parent.parent;out=root/'outputs';out.mkdir(exist_ok=True)
backup=root/'work/backups/graphics';backup.mkdir(parents=True,exist_ok=True)
fixes=[('Route120',47,'OBJ_EVENT_GFX_COOLTRAINER_F','OBJ_EVENT_GFX_WOMAN_5'),('Route124',13,'OBJ_EVENT_GFX_SWIMMER_M_LAND','OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M'),('Route126',9,'OBJ_EVENT_GFX_SWIMMER_M_LAND','OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M'),('ScorchedGrotto',0,'OBJ_EVENT_GFX_ENTEI','OBJ_EVENT_GFX_SPECIES(ENTEI)'),('Route126_StillWaterCave',0,'OBJ_EVENT_GFX_SUICUNE','OBJ_EVENT_GFX_SPECIES(SUICUNE)')]
manifest=[];patch=[]
for name,index,old,new in fixes:
 rel=f'data/maps/{name}/map.json';path=project/rel;before=path.read_bytes();text=before.decode('utf8');data=json.loads(text);obj=data['object_events'][index];assert obj['graphics_id']==old,(name,obj)
 # Replace exactly the known graphics field; preserve formatting and encoding.
 needle='"graphics_id": "'+old+'"';replacement='"graphics_id": "'+new+'"';assert text.count(needle)==1,(name,text.count(needle))
 target=backup/rel;target.parent.mkdir(parents=True,exist_ok=True);target.write_bytes(before)
 after=text.replace(needle,replacement).encode('utf8');path.write_bytes(after)
 parsed=json.loads(after);obj['graphics_id']=new;assert parsed==data
 entry={'path':str(path),'relative_path':rel,'object_index':index,'local_id':obj['local_id'],'before':old,'after':new,'sha256_before':hashlib.sha256(before).hexdigest(),'sha256_after':hashlib.sha256(after).hexdigest(),'backup':str(target)};manifest.append(entry)
 patch.extend(difflib.unified_diff(before.decode('utf8').splitlines(True),after.decode('utf8').splitlines(True),fromfile='a/'+rel,tofile='b/'+rel))
(out/'source-graphics-sync.patch').write_text(''.join(patch),encoding='utf8',newline='')
(out/'change-manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf8')
print(json.dumps(manifest,ensure_ascii=False,indent=2))
