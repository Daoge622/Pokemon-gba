# 变更记录

## 2026-10-11 / Codex

- 新建本目录四份 handoff 文档；不推断既往 Canon。
- 修改五个地图 JSON：Route120、Route124、Route126、ScorchedGrotto、Route126_StillWaterCave；各改一个 graphics_id，与原 ROM 已有的修复配置一致。补丁和前后哈希见 outputs/source-graphics-sync.patch、change-manifest.json。
- 原 ROM、原 MyBoy 即时存档、原普通存档未改动；未构建或发布修复 ROM。
- 静态体检覆盖 543 地图/3458 对象/1370 传送点及 56320 条已解码脚本指令/711 条对战指令。88 个 native 调用点之后的代码未继续解码，不宣称全游戏验证。
- 无窗口 mGBA 正常打赢守墓人，胜利标志置位并返回地图行走；生成独立战后普通存档且冷启动读取通过。MyBoy 的原问题未复现。
- 用户随后反馈已恢复正常，停止针对重置的进一步修改；根因仍未确认。源码与 ROM 不完整对应，已记录缺失文件/special/训练家槽位差异。

## 2026-10-11 / Codex / 用户优先级调整：组队选宝可梦

- 正常输入复现 MtPyre_Exterior 女孩组队漏选队：玩家队伍被 ReducePlayerPartyToSelectedMons 清空；共享宏同类四入口已核对。
- 修改 battle_tower.inc、part55.inc、story_b.inc、宇宙中心2F scripts.inc；补选队、取消原队伍/临时NPC恢复、按原槽位回写、明确本场胜败。没有新增运行时防御性兜底。
- 发布定点修复 ROM，472 个实际不同字节、8 个修改区域。源码快照未全量构建；原 ROM/记录未覆盖。SHA256 8c3142dcf6678093913e9f572865272d46dbe9862f60d03f5f9d251259037e8d。
- 女孩正常胜利和失败、选队/取消、战后六只恢复与菜单/行走、保存冷启动通过；其余入口采用测试设置验证，不声称完整剧情测试。mGBA 无窗口授权延用，MyBoy 未动态验证。
- 原 ROM 正常打赢二楼情侣，战后对话/行走/背包和堆链正常；用户撕裂现象未复现，未标 FIXED。守墓人问题此前自行恢复，未专修。
- 报告/源码补丁/BPS/字节与哈希清单：C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\组队双打修复与接力记录.md。

## 2026-10-11 / Codex / 战后循环对话

- 用户确认情侣撕裂已经修复；作者/具体补丁未知，更新状态但不认领。
- 核查550个视线训练家对象，4个普通剧情包装脚本的lock阻断获胜标志识别；对战金字塔64个对象使用独立获胜判断。
- part55.inc四个入口补已有cant_see_if_trainerflag_set：女孩、便当、手套、海洋队晕船小兵。ROM定点前缀和原primitive等价Thumb，130实际不同字节/9区域，前次选队补丁保持。
- 四个原循环复现；四场按键打赢/获胜标志/600帧无再触发/手动交谈关闭和移动通过，测试warp/隔离标志/两名NPC静态姿势仅测试副本。无MyBoy或全剧情验收。
- 累计ROM SHA256 5948b8fd044a7b07d4cb75ed7f2439f5607ea15065f161728218bf41fe644614。原ROM和记录保留；BPS独立重建和CRC通过。报告：C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\战后对话修复与Claude接力记录.md。

- 本轮女孩战后使用交付ROM游戏内普通记录，再新建核心冷启动读档：回到基地24/87，等待600帧无对话循环、锁为0；存档中的女孩脚本指针已更新为0x09B0046C。dialogue-coldboot-verification.json与截图已归档。
