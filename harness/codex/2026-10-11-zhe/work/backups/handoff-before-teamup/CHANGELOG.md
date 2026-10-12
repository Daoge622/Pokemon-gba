# 变更记录

## 2026-10-11 / Codex

- 新建本目录四份 handoff 文档；不推断既往 Canon。
- 修改五个地图 JSON：Route120、Route124、Route126、ScorchedGrotto、Route126_StillWaterCave；各改一个 graphics_id，与原 ROM 已有的修复配置一致。补丁和前后哈希见 outputs/source-graphics-sync.patch、change-manifest.json。
- 原 ROM、原 MyBoy 即时存档、原普通存档未改动；未构建或发布修复 ROM。
- 静态体检覆盖 543 地图/3458 对象/1370 传送点及 56320 条已解码脚本指令/711 条对战指令。88 个 native 调用点之后的代码未继续解码，不宣称全游戏验证。
- 无窗口 mGBA 正常打赢守墓人，胜利标志置位并返回地图行走；生成独立战后普通存档且冷启动读取通过。MyBoy 的原问题未复现。
- 用户随后反馈已恢复正常，停止针对重置的进一步修改；根因仍未确认。源码与 ROM 不完整对应，已记录缺失文件/special/训练家槽位差异。
