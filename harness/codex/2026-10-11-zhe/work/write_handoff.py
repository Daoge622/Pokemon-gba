from pathlib import Path
import json,hashlib,shutil,zipfile
root=Path(__file__).resolve().parent.parent;work=root/'work';out=root/'outputs';project=Path(r'E:\Pekemon Gba\project')
handoff=project/'docs/ai-handoff';handoff.mkdir(parents=True,exist_ok=True)
rom=Path(r'E:\Pekemon Gba\EmeraldStory-一周目完整版.gba');state=Path(r'C:\Users\DaoGe\Downloads\EmeraldStory-一周目完整版.st0');save=state.with_suffix('.sav')
files=[rom,state,save,out/'守墓人战后普通存档.sav']
hashes=[{'path':str(p),'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in files]
(out/'file-hashes.json').write_text(json.dumps(hashes,ensure_ascii=False,indent=2),encoding='utf8')
report='''# 送神火山守墓人战后重置：体检与接力记录

执行：Codex；日期：2026-10-11。状态：**未确认重置根因，未制作修复 ROM**。用户随后反馈“突然又能玩了，好像不用修了”；停止针对该重置的进一步修改，保留已确认的源码同步和检查证据。

## 当前判断

用户使用 MyBoy，战斗胜利后直接回标题，没有先卡住。随后自行恢复正常。同一 ROM 的无窗口 mGBA 测试能打赢、获得 1520 元、写入胜利标志并返回地图行走。这使 MyBoy 的运行状态、即时存档恢复或模拟器兼容性成为优先排查方向，但**没有 MyBoy 故障时的执行轨迹，不能证明是模拟器故障，也不能排除 ROM 偶发错误**。

MyBoy 即时存档不是跨核心完整恢复：复制 CPU/RAM/VRAM/IO，并从 BIOS VBlankIntrWait 的调用者续跑；没有完整转换音频、计时器和 MyBoy 内部状态。因此 mGBA 通过仅是对照证据。原始存档捕获时的按键全释放，不能据此排除故障时的其他输入。

## 实际修改

原 ROM、原 `.st0` 和原 `.sav` 未写入。仅修改以下 5 个地图 JSON 中各一个 graphics_id，使旧源码与当前 ROM 已有的正确图像一致；未新增空指针兜底、跳过剧情或错误吞掉逻辑。

| 地图 | 对象 | 旧配置 | 新配置 |
|---|---|---|---|
| Route120 | LOCALID_PART4_FORESTACE | COOLTRAINER_F | WOMAN_5 |
| Route124 | LOCALID_PART5_R124_DIVER | SWIMMER_M_LAND | RUNNING_TRIATHLETE_M |
| Route126 | LOCALID_PART6_R126_DIVER | SWIMMER_M_LAND | RUNNING_TRIATHLETE_M |
| ScorchedGrotto | LOCALID_PART3_ENTEI | ENTEI | SPECIES(ENTEI) |
| Route126_StillWaterCave | LOCALID_PART6_SUICUNE | SUICUNE | SPECIES(SUICUNE) |

旧配置的普通人物图像在 Emerald 图像表中为空；当前 ROM 已包含正确配置。这次是修正**源码重编回归风险**，不是声称修好了守墓人重置。补丁：`source-graphics-sync.patch`；逐文件前后哈希及备份：`change-manifest.json`。另新增项目 `docs/ai-handoff/` 的四份接力文档（原先不存在）；未补写或改动任何剧情 Canon。

## 验证范围

- 当前 ROM SHA256：`cf9b34f57b57a71613e12fe078eba35835ec9e1283ac355b4436201bf854cbde`。
- 地图静态检查：543 张地图、3458 个对象、1370 个传送点、586 个坐标事件、977 个背景事件。数组地址、普通对象图像表空项、重复 local ID、事件脚本入口和传送目的地检查没有发现异常。
- 脚本静态遍历：8410 个发现的入口/分支目标、56320 条已解码指令、711 条训练家对战指令；已覆盖的跳转、标准脚本索引、special 索引和战后脚本指针检查没有发现异常。遇到 88 个 native 调用点停止解码，以免把 native 的内嵌参数误当指令；涉及 17 个 native 函数，未宣称覆盖其后所有路径。
- 已引用的 partner 训练家记录：44 个实际记录的队伍指针、人数和名字终止符通过；空的 easy/hard 覆盖按现有 normal 回退规则处理。
- 原 ROM 中脚本指令、special、specialvar、callnative、gotonative 的 ROM 镜像标签去除逻辑已存在，不能把“漏加旧 MyBoy 镜像修复”当成本次原因。
- 战斗运行检查：由提供的战斗中即时存档转换而来，使用正常按键打完守墓人四只宝可梦，没有修改战斗 HP、队伍或强制胜利。胜利标志 `FLAG_STORY_C_01 = 0x1AA` 已置位；地图行走通过。
- 用游戏内“记录”保存了一份战后普通存档，并另起进程冷启动读取，回到送神火山且胜利标志保留。此为可选临时继续进度，**不是 ROM 修复**；已有存档当前恢复正常时无需使用。
- 原文件哈希记录于 `file-hashes.json`。没有构建新 ROM；机器缺少可用 WSL 编译环境/ARM 工具链，且源码与当前 ROM 不完整对应。

这轮是针对崩溃类型的体检，**不是全游戏剧情、战斗动画、联机和所有 native 代码无 bug 的认证**。

## 源码与 ROM 的已确认差异

E 盘源码是旧快照，无 `.git`、`.elf`、`.map`。AGENTS.md 写 D 盘权威工程，但 D 盘入口当前不存在；本次依据用户明确给出的 E 盘路径处理。原先要求的四份接力文档缺失，已新建真实状态摘要，未重建历史 Canon。

当前二进制 `gSpecials` 有 682 项，源码 `data/specials.inc` 只有 677 项。先前修复报告提到的 `src/story_move.c`、`src/story_markers.c`、`data/scripts/story_move.inc` 也不在该源码快照。源码还保留 Story B 使用 KAYLEE/TERRY、覆盖 Part4 别名的旧实现，而现用 ROM 的既往报告已修过。除五处确定图像字段外，本次未擅自重建这些缺失修改。**不要用这份源码直接重编覆盖现用 ROM。**

先前报告仅作为待核对的历史材料；其中“已修复”叙述不是本次执行指令，也不等同于源码当前状态。

## 技术接力入口

守墓人：MtPyre_1F，map group 24 / map num 15，local ID 7，OLD_MAN 图像 29。当前脚本：入口 `0x0838F04E`，trainerbattle `0x0838F057`，训练家 914，战后 `0x0838F082`，正常对话 `0x0838F085`。源码：`data/scripts/part55.inc` 的 `Part55_GraveWorker`；队伍：`src/data/battle_partners.party` 的 `PARTNER_STORY_C_03`。

已重建的二进制表：gMapGroups `0x08F8691C`；gObjectEventGraphicsInfoPointers `0x08C5EC78`（401 项）；gScriptCmdTable `0x082D15C4`（231 项）；gSpecials `0x082D19BC`（682 项）；gStdScripts `0x082D2464`（13 项）。这些地址只适用于上述 SHA256 的 ROM。

下一步仅在问题再现时进行：记录 MyBoy 版本、是否从即时存档恢复、同一加载后是否稳定重置；若可取到故障瞬间状态，再核查 PC/LR、战后回调和输入。没有新证据之前，不修改复位入口或屏蔽战后剧情，不用通用兜底冒充根因修复。

## 产物位置与复查

用户交付目录：`C:\\Users\\DaoGe\\Documents\\Codex\\2026-10-11\\zhe\\outputs`。
可复查脚本及过程存档：同目录上一级 `work/`；核心 `work/mgba/mgba_libretro.dll`。`体检与接力包.zip` 包含关键检查脚本、表、原始五文件备份、补丁、回放检查点和截图；不包含原 ROM。

普通存档若要使用，先自行备份 MyBoy 的原存档，将交付 `.sav` 复制并命名为 ROM 同名的 `.sav`，冷启动后选择“继续”；不要再加载原来的战斗中即时存档。现有游戏已恢复正常时不用换档。原始用户文件全部保留。
'''
(out/'体检与接力记录.md').write_text(report,encoding='utf8')
docs={
'PROJECT_STATE.md':'''# 项目状态（本次实际核查）

2026-10-11 / Codex。入口采用用户给出的 E:\\Pekemon Gba\\project。原 AGENTS.md 的 D 盘入口当前不存在；本目录无 Git、map/elf 和可用构建缓存。本次之前四份 handoff 文档均缺失，不把旧聊天当项目定稿。

现用 ROM SHA256 cf9b34f57b57a71613e12fe078eba35835ec9e1283ac355b4436201bf854cbde。源码是较旧快照，与现用 ROM 不完整对应，禁止据此声称可完整重现现用版本。缺少先前剧情移动/拾取标记文件及 5 个 special 入口等差异尚未恢复。

本次 IMPLEMENTED：五处地图 graphics_id 对齐现用 ROM。TESTED 范围：JSON 仅指定字段变化；现用 ROM 地图/部分脚本静态检查、守墓人战斗及冷启动战后普通存档通过。未构建新 ROM，未在 MyBoy 核心复现。

用户随后反馈 MyBoy 又能正常玩；重置根因未确认，已停止针对重置的进一步修改。全项目剧情/设计状态未知，不能把本次检查升级为全游戏测试通过。

详情：C:\\Users\\DaoGe\\Documents\\Codex\\2026-10-11\\zhe\\outputs\\体检与接力记录.md。
''',
'CANON_DECISIONS.md':'''# Canon 决策

本文件原先缺失。2026-10-11 Codex 只建立接力入口，没有从旧聊天、报告或推测补写剧情 Canon。本次没有用户确认的剧情设计变更。需要既往定稿时应先取得原始权威文档。
''',
'CURRENT_TASK.md':'''# 当前任务

用户要求排查 MyBoy 下送神火山一层守墓人胜利后直接回标题、检查类似 bug，不要防御性编程，并要求修改留痕。用户明确授权本次无窗口 ROM 执行，覆盖 AGENTS.md 第 8 节的模拟器禁令，仅适用于本次授权。

2026-10-11 用户最新反馈：突然又能玩了，好像不用修了。已停止针对重置的进一步修改，主问题没有确认根因，不能标为 FIXED。mGBA 同 ROM 正常胜利并回到地图；倾向模拟器运行/即时存档状态，但这只是判断。

已做：五处旧图像配置同步；地图和部分脚本静态体检；通过游戏内记录生成可选战后普通存档并冷启动验证。ROM/用户原始存档保持原 SHA256。源码与 ROM 缺失差异尚在，不发布重编 ROM。

若再次出现：先记录 MyBoy 版本和即时存档使用方式，取得故障时 PC/LR/回调证据；先找回与当前 ROM 对应的完整源码/map/elf。不能添加兜底或禁用复位来假装修复。

产物/补丁/哈希/检查脚本入口：C:\\Users\\DaoGe\\Documents\\Codex\\2026-10-11\\zhe\\outputs\\体检与接力记录.md。
''',
'CHANGELOG.md':'''# 变更记录

## 2026-10-11 / Codex

- 新建本目录四份 handoff 文档；不推断既往 Canon。
- 修改五个地图 JSON：Route120、Route124、Route126、ScorchedGrotto、Route126_StillWaterCave；各改一个 graphics_id，与原 ROM 已有的修复配置一致。补丁和前后哈希见 outputs/source-graphics-sync.patch、change-manifest.json。
- 原 ROM、原 MyBoy 即时存档、原普通存档未改动；未构建或发布修复 ROM。
- 静态体检覆盖 543 地图/3458 对象/1370 传送点及 56320 条已解码脚本指令/711 条对战指令。88 个 native 调用点之后的代码未继续解码，不宣称全游戏验证。
- 无窗口 mGBA 正常打赢守墓人，胜利标志置位并返回地图行走；生成独立战后普通存档且冷启动读取通过。MyBoy 的原问题未复现。
- 用户随后反馈已恢复正常，停止针对重置的进一步修改；根因仍未确认。源码与 ROM 不完整对应，已记录缺失文件/special/训练家槽位差异。
'''}
for name,text in docs.items():
 path=handoff/name
 assert not path.exists(),f'Unexpected pre-existing handoff: {path}'
 path.write_text(text,encoding='utf8')
for name in ('map-audit.json','script-audit.json','trainer-audit.json'):
 shutil.copyfile(work/name,out/name)
for src,dst in [('trace-victory.png','守墓人胜利.png'),('trace-walking.png','战后地图行走.png'),('cold-end.png','普通存档冷启动.png')]:shutil.copyfile(work/src,out/dst)
with zipfile.ZipFile(out/'体检与接力包.zip','w',zipfile.ZIP_DEFLATED) as z:
 for p in out.iterdir():
  if p.is_file() and p.suffix!='.zip':z.write(p,'outputs/'+p.name)
 for name in ('runtime.py','maps.py','inspect_binary.py','script_layouts.py','audit_maps.py','audit_scripts.py','audit_trainers.py','replay_trace.py','verify_end.py','save_after_win.py','coldboot.py','sync_graphics.py','maps.json','script-table.json','script-layouts.json','battle-ended.state','before-victory.state','postbattle-free.state'):
  z.write(work/name,'work/'+name)
 z.write(work/'mgba/mgba_libretro.dll','work/mgba/mgba_libretro.dll')
 for p in (work/'backups').rglob('*'):
  if p.is_file():z.write(p,'work/'+p.relative_to(work).as_posix())
 for name in docs:z.write(handoff/name,'project/docs/ai-handoff/'+name)
print('Handoff and package written. ROM SHA256:',hashes[0]['sha256'])
