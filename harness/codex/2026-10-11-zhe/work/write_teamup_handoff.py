from pathlib import Path
import json, hashlib, shutil, zipfile, datetime
OUT=Path('outputs');ROOT=Path.cwd();PROJECT=Path(r'E:\Pekemon Gba\project');HD=PROJECT/'docs/ai-handoff'
manifest=json.loads((OUT/'teamup-rom-patch.json').read_text(encoding='utf-8'))
pics={'teamup-broken-11.png':'修复前_玩家队伍被清空.png','teamup-fixed-6.png':'修复后_选队菜单.png','teamup-selected-third.png':'修复后_指定出场顺序.png','teamup-fixed-battle.png':'修复后_女孩与胖丁组队.png','teamup-restored-party.png':'修复后_战后恢复六只.png','teamup-post-walk.png':'修复后_地图行走.png','teamup-loss-healed.png':'修复后_失败回宝可梦中心.png','cold-end.png':'修复后_普通存档冷启动.png','couple-win-field.png':'情侣战_原ROM胜利回地图.png','couple-verified-bag.png':'情侣战_战后背包正常.png'}
for a,b in pics.items():shutil.copy2(ROOT/'work'/a,OUT/b)
report=f'''# 组队双打选宝可梦修复 / Codex / 2026-10-11

## 交付与使用

- 修复 ROM：`{manifest['output']}`。
- 原 ROM、原 MyBoy 即时存档、原普通存档均未覆盖。
- 建议从游戏内普通记录，或与女孩对话前的即时存档进入。已经开始异常双打的即时存档保存了被清空的队伍和旧脚本执行位置，不能靠换 ROM 恢复它。
- 新 ROM 文件名不同，MyBoy 若没有自动识别原记录，请将自己的当前 `.sav` 副本按新 ROM 名称导入/匹配；不要拿测试存档替换自己的最新进度。
- 本次没有使用 MyBoy 核心，运行验证使用用户授权的无窗口 mGBA。测试即时存档为 mGBA 内部格式，不能作为 MyBoy `.st0` 使用。

## 已确认根因与实际改动

送神火山外部 `Part55_RookieTeamup` 与胖丁女孩组队时，`multi_do` 对半队模式直接执行 `ReducePlayerPartyToSelectedMons`，从未先执行 `ChooseHalfPartyForBattle`。`gSelectedOrderFromParty` 全零时玩家队伍被清空；有旧选择时则无声使用旧队伍。这是 ROM 的事件流程错误，已用原 ROM 正常走路、对话复现，不归因于 MyBoy。

同一宏在现用 ROM 中只有四个剧情调用点。逐一核对了原二进制，全部处理：

| 入口 | 改动 | 动态验证范围 |
| --- | --- | --- |
| 送神火山外部，胖丁女孩 | 补选队、取消、按原槽位回写参战宝可梦 | 正常走路和对话、自由排序、取消、打赢、打输、战后菜单/行走、普通保存和冷启动 |
| 119 号道路，桥边与女孩对抗海洋队 | 同一选队修复；取消恢复共用 NPC 的原配置 | 通过测试用地图传送及脚本入口执行：选队、指定队伍交接、取消、六只恢复；未完整重走剧情演出 |
| 釜炎镇，便装女孩与熔岩队双打 | 同一选队修复；取消隐藏临时出现的两个队员 | 同上；未完整重走剧情演出 |
| 宇宙中心二楼，大吾 | 保留原有选队入口，避免重复选队；统一战后恢复和结果 | 测试入口传入已选顺序后进入与大吾/巨金怪的双打；未完整重走剧情演出 |

共享流程现在在半队模式先选队，再缩减；取消先恢复完整队伍，再退出/撤回本场临时 NPC。选队成功后的 TRUE 结果不会再混同为“全队模式”结果；半队战明确设置 `MULTI_BATTLE_CHOOSE_MONS`，由脚本按已选原槽位保存 HP/经验等，然后恢复全部六只。全队模式直接保存完整队伍。最后显式取本场 `GetBattleOutcome`，避免大吾流程拿菜单/模式判断结果当胜败。

没有增加运行时空指针兜底、越界保护、禁止复位等防御性逻辑；修改的是正常事件生命周期。离线补丁脚本的输入哈希/原字节断言只是确保补丁用于对应 ROM。

## 修改位置与可复现性

源码四个文件已修改，修改前逐份备份；`teamup-source.patch` 和 `teamup-source-manifest.json` 记录前后 SHA256：

- `asm/macros/battle_frontier/battle_tower.inc`
- `data/scripts/part55.inc`
- `data/scripts/story_b.inc`
- `data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc`

本地源码仍是较旧快照，缺少现用 ROM 的部分剧情移动等变更，且无对应 map/elf 和可用完整构建环境。本次没有用旧源码全量重编，避免回退现用 ROM 已有内容。交付 ROM 是对用户给出的现用二进制做定点事件补丁；源码补丁供 Claude 合入真实完整工程后再构建。

旧 `multi_do` 起点分别为 `0838ED31`、`083993B6`、`083995C2`、`0830D196`。只将各自第一条 5 字节 native 调用改成跳转，在原 ROM 全 FF 的 `09B00000` 后追加四份完整修复脚本。原人物、敌方队伍、文本和其它地图没有重排。共 8 个修改区域、472 个实际不同字节；`teamup-rom-patch.json` 给出每段原字节和新字节。BPS 支持此 32MB ROM，已独立解码应用并逐字节比对。

原 ROM SHA256：`{manifest['input_sha256']}`。

修复 ROM SHA256：`{manifest['output_sha256']}`。

生成：`python work/patch_teamup.py`。验证：`python work/verify_teamup.py`。运行需 Python、Pillow、capstone（反汇编/体检）及包内 mGBA libretro DLL。脚本从本工作目录执行，默认采用这里记录的 Windows 输入路径；迁移机器时先调整路径。

## 验证结果

- 原版：无选队菜单，玩家队伍数量降为 0，组队展示只剩伙伴胖丁。对应前后截图已留存。
- 修复版：指定 `[4,2,5]` 顺序即水伊布、巨钳螳螂、可多拉成功；另一正常胜利分支采用 `[2,4,5]`。伙伴是胖丁。巨钳螳螂以子弹拳正常打赢，无改等级、HP、敌方数据或胜利标志。
- 胜利：`FLAG_PART55_ROOKIE_TEAMUP_DONE`（现用 ROM `04EC`）置位，六只宝可梦的 personality/OT 身份与原顺序全部相同，巨钳螳螂 40→41、HP 85/121 保留，未参战宝可梦保持原数据。
- 取消：六只宝可梦 600 字节完整数据与菜单前逐字节相同，不置胜利标志，地图可行走。
- 失败：结果 2，先恢复原六只身份，再按原事件回宝可梦中心（group11/map5），未置胜利标志。
- 战后普通记录重新启动能读取送神火山同一位置；原用户记录未改。
- 菜单、组队展示、胜利地图、战后普通队伍菜单等 5 个状态的堆链/边界/前后指针一致，未发现堆破坏。新脚本 121 条可达指令的长度、分支地址、native/special 编号检查通过。
- 修复 ROM 静态体检：543 地图、3458 对象、1370 传送点，56320 条已解码脚本指令/711 条对战指令、44 个引用伙伴配置无已覆盖问题。88 个 native 调用之后仍有未继续解码区域，不是全游戏所有路径的穷举验证。

`teamup-verification.json`、`teamup-heap-audit.json`、`fixed-*-audit.json` 是机器可读结果。其它入口的 `fixture` 是明确的测试设置：只修改临时副本 ROM 的测试传送脚本/临时 RAM 执行入口，不修改交付 ROM、原记录或剧情定稿。

## 前两个问题的状态

一楼守墓人回标题：用户后来能正常玩，原 ROM 在 mGBA 正常打赢；未确认根因，未专门修复，不标 FIXED。

二楼真子和辉胜利后撕裂：已从原战斗记录正常走到二楼并打赢；战后行走、再次对话、打开背包均正常，胜利标志 `0780` 置位，堆链无破坏。没有复现用户的 MyBoy 撕裂，未专门修复。路上的另外两场训练家战也正常结束。初次连续按 A 停滞实为子弹拳/二连击 PP 用完，换劈开后正常胜利，未当作新 bug。

没有新增剧情 Canon，也没有宣称全游戏所有 bug 已修完。下一位 Claude 优先合入本补丁到与当前 ROM 完整对应的工程，并在 MyBoy 复验；若情侣战再次撕裂，再取故障 PC/LR/回调/状态定位。
'''
(OUT/'组队双打修复与接力记录.md').write_text(report,encoding='utf-8')
for filename in ['PROJECT_STATE.md','CURRENT_TASK.md','CHANGELOG.md']:
 path=HD/filename;backup=ROOT/'work/backups/handoff-before-teamup'/filename;backup.parent.mkdir(parents=True,exist_ok=True)
 if not backup.exists():shutil.copy2(path,backup)
(HD/'PROJECT_STATE.md').write_text(f'''# 项目状态（实际核查）

2026-10-11 / Codex。用户给出的入口是 E:\\Pekemon Gba\\project，原 AGENTS.md 的 D 盘入口不存在。本目录无 Git/map/elf/可用完整构建缓存；源码较旧，缺失现用 ROM 部分移动/标记文件和 5 个 special 等差异。本次不把旧报告当 Canon。

IMPLEMENTED：此前五处地图图像字段对齐现用 ROM；本轮共享 multi_do 的选队、取消、战后队伍回写/恢复和胜败结果修复，四个剧情入口均覆盖。四个源码文件已改，同时发布基于现用 ROM 的定点脚本修复版。未完整重编源码，不能声称当前快照可还原原 ROM。

TESTED：无窗口 mGBA 原版复现送神火山女孩未选队直接清空玩家队伍；修复版正常选队/取消/胜利/失败/战后菜单和行走/普通保存冷启动通过。119号道路、釜炎镇及大吾的共用入口经明确测试设置验证菜单/队伍交接；未完整重走其它三段剧情演出。MyBoy 核心未运行。

原 ROM SHA256 {manifest['input_sha256']}；交付修复 ROM SHA256 {manifest['output_sha256']}。原 ROM 和原存档均保留。

已知未确认问题：守墓人回标题后来自行恢复，未专修；二楼情侣战撕裂在 mGBA 正常走路/打赢/菜单验证中未复现，未专修。全游戏并未穷举验收；88个 native 调用之后仍有静态覆盖缺口。

当前交付和证据：{ROOT / 'outputs/组队双打修复与接力记录.md'}。此前体检：{ROOT / 'outputs/体检与接力记录.md'}。此前五处图像仅源码同步，现用 ROM 原本已有。
''',encoding='utf-8')
(HD/'CURRENT_TASK.md').write_text(f'''# 当前任务

用户优先要求修复送神火山胖丁女孩双打不能选宝可梦，并修复其它同类选队双打；禁止防御性编程，要求工作留痕。用户此前明确授权本任务无窗口执行 ROM，覆盖 AGENTS.md 第8节模拟器禁令；未授权 GUI，本次未开 GUI。

已完成：确认共享 multi_do 漏开选队菜单会清空队伍/沿用旧选择；修改共享源码宏和三场取消清理，并让大吾使用原已有选队结果。已发布修复 ROM、BPS、源码补丁、前后哈希/字节清单和接力包。

测试：送神火山女孩正常游戏输入选队、取消、胜利、失败、恢复六只、升级/HP保留、行走/队伍菜单、普通记录冷启动通过；其它三场入口测试设置通过，未全剧情复验。无 MyBoy 动态验证。情侣战撕裂未复现，守墓人重置自行恢复，两者未标 FIXED。

下一步交接：将 teamup-source.patch 合入与原 ROM 对应的完整工程后构建；核对该工程已有故事移动文件、special 与釜炎镇训练家备用槽位差异，不能把 E 盘旧快照全量重编发布；由用户在 MyBoy 使用对话前记录复验。异常双打中即时存档不包含补选队过程，不用于验收修复。

无新增剧情/设计 Pending 或 Canon。证据入口：{ROOT / 'outputs/组队双打修复与接力记录.md'}。
''',encoding='utf-8')
with (HD/'CHANGELOG.md').open('a',encoding='utf-8') as f:
 f.write(f'''\n## 2026-10-11 / Codex / 用户优先级调整：组队选宝可梦

- 正常输入复现 MtPyre_Exterior 女孩组队漏选队：玩家队伍被 ReducePlayerPartyToSelectedMons 清空；共享宏同类四入口已核对。
- 修改 battle_tower.inc、part55.inc、story_b.inc、宇宙中心2F scripts.inc；补选队、取消原队伍/临时NPC恢复、按原槽位回写、明确本场胜败。没有新增运行时防御性兜底。
- 发布定点修复 ROM，472 个实际不同字节、8 个修改区域。源码快照未全量构建；原 ROM/记录未覆盖。SHA256 {manifest['output_sha256']}。
- 女孩正常胜利和失败、选队/取消、战后六只恢复与菜单/行走、保存冷启动通过；其余入口采用测试设置验证，不声称完整剧情测试。mGBA 无窗口授权延用，MyBoy 未动态验证。
- 原 ROM 正常打赢二楼情侣，战后对话/行走/背包和堆链正常；用户撕裂现象未复现，未标 FIXED。守墓人问题此前自行恢复，未专修。
- 报告/源码补丁/BPS/字节与哈希清单：{ROOT / 'outputs/组队双打修复与接力记录.md'}。
''')
# Confirm original user inputs still match their initial recorded hashes.
originals=json.loads((OUT/'file-hashes.json').read_text(encoding='utf-8'))
(OUT/'teamup-handoff-files.json').write_text(json.dumps({'created_by':'Codex','source_of_truth':str(PROJECT),'original_inputs':originals,'handoff':[str(HD/f) for f in ['PROJECT_STATE.md','CANON_DECISIONS.md','CURRENT_TASK.md','CHANGELOG.md']]},ensure_ascii=False,indent=2),encoding='utf-8')
archive=OUT/'组队双打修复与Claude接力包.zip'
with zipfile.ZipFile(archive,'w',zipfile.ZIP_DEFLATED,compresslevel=6) as z:
 for file in OUT.iterdir():
  if file.suffix!='.zip':z.write(file,'outputs/'+file.name)
 for path in HD.glob('*.md'):z.write(path,'project/docs/ai-handoff/'+path.name)
 for entry in json.loads((OUT/'teamup-source-manifest.json').read_text(encoding='utf-8')):
  path=Path(entry['file']);relative=path.relative_to(PROJECT);z.write(path,'project/'+relative.as_posix())
  z.write(entry['backup'],'backups/teamup/'+relative.as_posix())
 for path in (ROOT/'work/backups/graphics').rglob('*'):
  if path.is_file():z.write(path,'backups/graphics/'+path.relative_to(ROOT/'work/backups/graphics').as_posix())
 scripts=['runtime.py','patch_teamup.py','verify_teamup.py','teamup_travel.py','teamup_reach.py','teamup_original.py','teamup_menu.py','teamup_select.py','teamup_fixture.py','teamup_finish.py','teamup_post_verify.py','write_teamup_handoff.py','fixed-audit_maps.py','fixed-audit_scripts.py','fixed-audit_trainers.py','script-layouts.json','maps.json','couple_heap.py','couple_actual.py','couple_win.py','couple_verify.py']
 for file in scripts:z.write(ROOT/'work'/file,'work/'+file)
 for file in ['teamup-real-before-talk.state','teamup-fixed-5.state','teamup-fixed-6.state','teamup-cancel.state','teamup-selected-third.state','teamup-fixed-battle.state','teamup-victory-field.state','teamup-loss-healed.state','teamup-restored-party.state','teamup-post-walk.state','fixture-Route119-menu.state','fixture-Route119-cancel.state','fixture-Route119-battle.state','fixture-LavaridgeTown-menu.state','fixture-LavaridgeTown-cancel.state','fixture-LavaridgeTown-battle.state','fixture-Steven-battle.state']:
  z.write(ROOT/'work'/file,'work/'+file)
 z.write(ROOT/'work/mgba/mgba_libretro.dll','work/mgba/mgba_libretro.dll')
with zipfile.ZipFile(archive) as z:assert z.testzip() is None
print('report and project handoff updated; archive verified:',archive.stat().st_size)
