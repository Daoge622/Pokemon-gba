from pathlib import Path
import json,hashlib,zipfile,shutil
ROOT=Path.cwd();OUT=ROOT/'outputs';SOURCE=Path(r'E:\Pekemon Gba\project');DOC=SOURCE/'docs/ai-handoff'
m=json.loads((OUT/'dialogue-rom-patch.json').read_text(encoding='utf-8'));v=json.loads((OUT/'dialogue-verification.json').read_text(encoding='utf-8'))
report=f'''# 战后循环对话修复 / Claude 接力

2026-10-11 / Codex / IMPLEMENTED；下述范围 TESTED。用户明确要求优先修复熔岩队基地女孩和新增小兵的战后无限对话，并排查同类。沿用用户本会话无窗口运行 ROM 的明确授权；未开 GUI。没有新增剧情 Canon 或防御性兜底。

## 使用的版本与产物

- 交付：`{m['output']}`，32 MiB，SHA256 `{m['output_sha256']}`。
- 累积在上次选队修复 ROM 上：SHA256 `{m['base_sha256']}`。前次全部八个 ROM 修复区域经逐字节核对仍保留。
- 原版输入 `{SOURCE.parent / 'EmeraldStory-一周目完整版.gba'}` 未覆盖；原 MyBoy 即时存档和普通记录未覆盖。
- `teamup-and-dialogue-from-original.bps` 对原版 cf9b34... 应用，包含选队和本轮修复；`dialogue-loop-from-teamup.bps` 仅对上次 8c3142... 应用。两个补丁均独立重建目标 ROM，并验证三项 CRC。不要重复叠加。
- MyBoy 建议从基地对话前的游戏内普通记录进入。即使使用同一普通存档，ROM 名称不同也需对应存档文件名。对话中即时存档包含旧脚本上下文，不作为修复验收起点。

## 根因与精确范围

视线检测 `src/trainer_see.c::CheckTrainer` 在第一个可见副作用处停止分析。四个脚本都以 lock/faceplayer 开始，再判断训练家已击败，再 goto 实际 trainerbattle。检测看到 lock 时尚未看到训练家编号，进入非 trainerbattle 的 ObjectApproachPlayer 分支；战后 release 解锁，下一帧又主动接近并执行同一对话。不是显式 goto 环，也不是本轮选队宏或新 Flag 引起。

全游戏核查 543 地图、3458 对象，其中 550 个具有视线的 NORMAL/SEE_ALL_DIRECTIONS/BURIED 对象。482 个直接 trainerbattle；68 个包装入口，其中 64 个属于对战金字塔，走独立 facility 胜利标志；普通剧情中余下四个全部修复：

| 地图/对象 | 脚本 | 训练家编号 |
| --- | --- | --- |
| MagmaHideout_2F_1R / 3 | Part55_RookieFormal（胖丁女孩） | 729 |
| MagmaHideout_2F_1R / 1 | Part55_MagmaBento（便当小兵） | 719 |
| MagmaHideout_2F_1R / 2 | Part55_MagmaGloves（手套小兵） | 720 |
| AquaHideout_B1F / 1 | Part55_Seasick（晕船小兵） | 3 |

权威源码只改 `data/scripts/part55.inc`：四个入口 lock 前加引擎已有 `cant_see_if_trainerflag_set`。它仅在视线分析上下文且训练家已获胜时 StopScript；正常手动对话上下文照旧继续。没有将 trainer_type 改成 NONE、取消挑战、改剧情/文字、添加 Flag 或跳过对战。

E 盘源码不能完整还原现用 ROM（缺移动文件/5个special，之前已留痕），因此发布定点二进制修复而未全量构建。四个地图对象的 script 指针指向 14 字节前缀，然后 goto 原脚本，原对话/战斗字节不改。0x09B00400 放置 58 字节 Thumb 实现，等价于已有 Script_EndTrainerCanSeeIf 的全部六条件比较与 StopScript 两字段动作；声明为 requests_effects native，调用指针 0x0BB00401，由现有 SCRIPT_UNTAG_FUNC 正常去标签。之前搜索无符号 ROM 未能可靠定位现存函数，故仅在二进制发布物重建已有 primitive；源码不新增第二套 helper。分配区结束 0x09B0047C，原区域全 FF，与选队代码及测试 warp 区不重叠。

相对上次 ROM 130 个实际不同字节、9 个区域，精确地址/原字节/新字节在 dialogue-rom-patch.json。源码前后 SHA/备份见 dialogue-source-manifest.json，补丁仅四行。

## 验证与边界

- 原版四处：设已获胜标志、进入视线后自动反复对话，连续关闭后仍锁定；修复版同场景无自动触发。
- 四处未获胜：保留视线主动挑战，以正常按键打赢全部四战，未修改对战双方 HP；原训练家获胜标志置位，返回地图等待 600 帧无再次对话。
- 四处获胜后手动交谈有正确对话，关闭后等待 300 帧不重开，并可走到邻格。
- 测试为无窗口 mGBA 受控入口：引擎 warp、隔离其它训练家胜利标志、清除隐藏标志、从既有正常失败后治疗记录载入六只；便当/手套小兵只在测试 ROM 固定面朝下，交付 ROM 的行走类型和视线范围完全未改。不是全流程剧情验收，不是 MyBoy 核心验证。
- 新 ROM 静态地图检查无问题；56332 条已解码脚本/711 对战入口无已检错误，44 个已用组队伙伴记录无错误；88 个未知 native 调用之后仍未覆盖，不能声称全游戏无 Bug。
- 用户本轮明确反馈情侣画面撕裂“已经修复”；标为用户确认，具体修复执行者/补丁未知，本轮未认领其修复。守墓人重置此前自行恢复，根因仍未知。

## 复现入口与下一步

脚本：work/patch_dialogue.py（发布补丁，源码已改时不可盲重跑）、dialogue_fixture.py、dialogue_battle.py、verify_dialogue.py、dialogue-audit_*.py。运行验证脚本用 Python `-X utf8`。二进制生成需要 keystone-engine/capstone，运行核心用 ctypes/Pillow；无窗口核心位于 work/mgba/mgba_libretro.dll。接力包中的工作状态/测试 ROM 只用于复现，不替换用户记录。

Claude 先读 project/docs/ai-handoff 四文件、本报告、dialogue-rom-patch.json 和 dialogue-source.patch。找到与原版 ROM 真正对应的完整工程后，合入前次选队源码修复及本次四行宏，用已有 Script_EndTrainerCanSeeIf 直接链接构建；勿把 E 盘旧快照全量重编替换现有剧情。用户在 MyBoy 从对话前普通记录复验，尤其女孩/便当/手套/晕船战后不自动接近，手动交谈仍正常。
'''
(OUT/'战后对话修复与Claude接力记录.md').write_text(report,encoding='utf-8')
state=f'''# 项目状态（实际核查）

2026-10-11 / Codex。用户入口 E:\\Pekemon Gba\\project，原 AGENTS 的 D 盘入口不存在。无 Git/map/elf/完整构建缓存；E 盘源码与现用 ROM 不完整对应，不能全量重编发布。

IMPLEMENTED：此前五处图像字段源码同步；共享 multi_do 四入口选队/取消/战后队伍恢复；本轮 part55.inc 四入口补 cant_see_if_trainerflag_set，修复基地战后自动循环对话。无新增 Flag、剧情改写或防御性兜底。

TESTED：此前送神火山组队选队/取消/胜败/六只恢复/保存冷启动通过，其它三入口为测试设置验证。本轮全游戏 550 个视线训练家入口核查，找到四个普通剧情包装缺陷全部覆盖；四场按键打赢、获胜标志、600帧无再触发、战后手动对话/关闭/行走通过。受控地图 warp/隔离标志，两名走动小兵仅测试副本固定姿势，不是全剧情或 MyBoy 验证。静态检查 543 地图、56332条脚本、711对战无已检错误，88个未知 native 后未覆盖。

累计 ROM SHA256 {m['output_sha256']}；基于前次 8c3142dcf6678093913e9f572865272d46dbe9862f60d03f5f9d251259037e8d，前次修复逐字节保留。原 ROM cf9b34f57b57a71613e12fe078eba35835ec9e1283ac355b4436201bf854cbde 和原记录均未覆盖。

情侣撕裂：用户本轮明确确认已修复，执行者/具体补丁未知，非本轮认领。守墓人重置此前自行恢复，根因未确认。全游戏未穷举验收。

当前报告：{OUT / '战后对话修复与Claude接力记录.md'}；此前记录仍在 outputs/组队双打修复与接力记录.md、体检与接力记录.md。
'''
(DOC/'PROJECT_STATE.md').write_text(state,encoding='utf-8')
(DOC/'CURRENT_TASK.md').write_text(f'''# 当前任务

用户要求修复熔岩队基地胖丁女孩和新增小兵的战后无限对话，并修复全游戏同类；保留此前选队修复，工作留痕，不做防御性编程。

已完成：视线分析遇 lock 未识别训练家获胜标志，导致非对战主动接近反复触发；四处包装入口（女孩/便当/手套/海洋队晕船小兵）lock 前补引擎已有 cant_see_if_trainerflag_set。源码四行、累计 ROM、两种基线 BPS、字节/哈希清单和完整接力包已交付。

测试：四处原循环复现，四场未获胜主动挑战按键打赢，战后600帧无自动触发；手动对话/关闭/走开通过。使用受控入口和无窗口 mGBA，不代表完整剧情或 MyBoy 验证。用户确认情侣撕裂已修复，作者未知；守墓人重置仍未确诊。

下一步：用户 MyBoy 从基地对话前普通记录复验；Claude 找到与现用ROM对应的完整工程，合入此前选队修复和本次四行宏后构建。源码快照缺文件/special差异仍在，禁止直接全量重编替换剧情。原记录/ROM未覆盖；无新增 Pending 或 Canon。

证据：{OUT / '战后对话修复与Claude接力记录.md'}。
''',encoding='utf-8')
with (DOC/'CHANGELOG.md').open('a',encoding='utf-8') as f:
 f.write(f'''\n## 2026-10-11 / Codex / 战后循环对话\n\n- 用户确认情侣撕裂已经修复；作者/具体补丁未知，更新状态但不认领。\n- 核查550个视线训练家对象，4个普通剧情包装脚本的lock阻断获胜标志识别；对战金字塔64个对象使用独立获胜判断。\n- part55.inc四个入口补已有cant_see_if_trainerflag_set：女孩、便当、手套、海洋队晕船小兵。ROM定点前缀和原primitive等价Thumb，130实际不同字节/9区域，前次选队补丁保持。\n- 四个原循环复现；四场按键打赢/获胜标志/600帧无再触发/手动交谈关闭和移动通过，测试warp/隔离标志/两名NPC静态姿势仅测试副本。无MyBoy或全剧情验收。\n- 累计ROM SHA256 {m['output_sha256']}。原ROM和记录保留；BPS独立重建和CRC通过。报告：{OUT / '战后对话修复与Claude接力记录.md'}。\n''')

# Self-contained handoff: no nested old ZIPs and no original private save files.
files={}
def add(p,name):
 p=Path(p);assert p.is_file();files[name]=p
for p in OUT.iterdir():
 if p.name.startswith(('dialogue-','teamup-','source-graphics','change-manifest')) and p.suffix in ('.json','.bps','.patch','.s','.txt'):add(p,'outputs/'+p.name)
for name in ['战后对话修复与Claude接力记录.md','组队双打修复与接力记录.md','体检与接力记录.md']:
 add(OUT/name,'outputs/'+name)
add(Path(m['output']),'outputs/'+Path(m['output']).name)
add(Path(m['base']),'outputs/'+Path(m['base']).name)
for p in DOC.glob('*.md'):add(p,'project/docs/ai-handoff/'+p.name)
add(SOURCE/'AGENTS.md','project/AGENTS.md')
for relative in ['data/scripts/part55.inc','data/scripts/story_b.inc','data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc','asm/macros/battle_frontier/battle_tower.inc']:
 add(SOURCE/relative,'project/'+relative)
 for kind in ['teamup','dialogue-loop']:
  p=ROOT/'work/backups'/kind/relative
  if p.exists():add(p,'work/backups/'+kind+'/'+relative)
for p in (ROOT/'work/backups/graphics').rglob('*'):
 if p.is_file():add(p,str(p.relative_to(ROOT)).replace('\\','/'));relative=p.relative_to(ROOT/'work/backups/graphics');add(SOURCE/relative,'project/'+str(relative).replace('\\','/'))
for name in ['patch_dialogue.py','dialogue_fixture.py','dialogue_battle.py','verify_dialogue.py','runtime.py','maps.json','script-layouts.json','wrapped-trainers.json','teamup-loss-healed.state','teamup-fixed-5.state']:
 add(ROOT/'work'/name,'work/'+name)
for p in (ROOT/'work').glob('dialogue-audit_*.py'):add(p,'work/'+p.name)
for name in ['dialogue-coldboot.png','dialogue-normal-save.sav','dialogue-save-done.png']:
 add(ROOT/'work'/name,'work/'+name)
add(ROOT/'work/mgba/mgba_libretro.dll','work/mgba/mgba_libretro.dll')
for i in range(4):
 for suffix in ['defeated-arrival','defeated-manual-dialogue','defeated-walk','unbeaten-victory']:
  for ext in ['png','state']:
   p=ROOT/'work'/f'dialogue-fixed-{i}-{suffix}.{ext}';add(p,'work/'+p.name)
 for suffix in ['defeated-arrival','defeated-after-close']:
  p=ROOT/'work'/f'dialogue-original-{i}-{suffix}.png';add(p,'work/'+p.name)
 p=ROOT/'work'/f'dialogue-fixed-{i}-unbeaten-after-close.state';add(p,'work/'+p.name)
archive=OUT/'战后对话修复与Claude接力包.zip'
with zipfile.ZipFile(archive,'w',zipfile.ZIP_DEFLATED,compresslevel=6) as z:
 for name,p in sorted(files.items()):z.write(p,name)
 z.writestr('CONTENTS-SHA256.json',json.dumps({name:hashlib.sha256(p.read_bytes()).hexdigest() for name,p in files.items()},ensure_ascii=False,indent=2))
with zipfile.ZipFile(archive) as z:
 assert z.testzip() is None
 for name,p in files.items():assert hashlib.sha256(z.read(name)).hexdigest()==hashlib.sha256(p.read_bytes()).hexdigest()
print(json.dumps({'archive':str(archive),'files':len(files)+1,'bytes':archive.stat().st_size,'hash_manifest_verified':True},ensure_ascii=False))
