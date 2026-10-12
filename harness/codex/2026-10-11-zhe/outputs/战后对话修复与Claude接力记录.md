# 战后循环对话修复 / Claude 接力

2026-10-11 / Codex / IMPLEMENTED；下述范围 TESTED。用户明确要求优先修复熔岩队基地女孩和新增小兵的战后无限对话，并排查同类。沿用用户本会话无窗口运行 ROM 的明确授权；未开 GUI。没有新增剧情 Canon 或防御性兜底。

## 使用的版本与产物

- 交付：`C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba`，32 MiB，SHA256 `5948b8fd044a7b07d4cb75ed7f2439f5607ea15065f161728218bf41fe644614`。
- 累积在上次选队修复 ROM 上：SHA256 `8c3142dcf6678093913e9f572865272d46dbe9862f60d03f5f9d251259037e8d`。前次全部八个 ROM 修复区域经逐字节核对仍保留。
- 原版输入 `E:\Pekemon Gba\EmeraldStory-一周目完整版.gba` 未覆盖；原 MyBoy 即时存档和普通记录未覆盖。
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

- 本轮女孩战后使用交付ROM游戏内普通记录，再新建核心冷启动读档：回到基地24/87，等待600帧无对话循环、锁为0；存档中的女孩脚本指针已更新为0x09B0046C。dialogue-coldboot-verification.json与截图已归档。

## 复现入口与下一步

脚本：work/patch_dialogue.py（发布补丁，源码已改时不可盲重跑）、dialogue_fixture.py、dialogue_battle.py、verify_dialogue.py、dialogue-audit_*.py。运行验证脚本用 Python `-X utf8`。二进制生成需要 keystone-engine/capstone，运行核心用 ctypes/Pillow；无窗口核心位于 work/mgba/mgba_libretro.dll。接力包中的工作状态只用于复现，测试 ROM 可用所附脚本重新生成，现场文件仍在 work/，不替换用户记录。

Claude 先读 project/docs/ai-handoff 四文件、本报告、dialogue-rom-patch.json 和 dialogue-source.patch。找到与原版 ROM 真正对应的完整工程后，合入前次选队源码修复及本次四行宏，用已有 Script_EndTrainerCanSeeIf 直接链接构建；勿把 E 盘旧快照全量重编替换现有剧情。用户在 MyBoy 从对话前普通记录复验，尤其女孩/便当/手套/晕船战后不自动接近，手动交谈仍正常。
