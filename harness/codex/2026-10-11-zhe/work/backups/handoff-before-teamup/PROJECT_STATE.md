# 项目状态（本次实际核查）

2026-10-11 / Codex。入口采用用户给出的 E:\Pekemon Gba\project。原 AGENTS.md 的 D 盘入口当前不存在；本目录无 Git、map/elf 和可用构建缓存。本次之前四份 handoff 文档均缺失，不把旧聊天当项目定稿。

现用 ROM SHA256 cf9b34f57b57a71613e12fe078eba35835ec9e1283ac355b4436201bf854cbde。源码是较旧快照，与现用 ROM 不完整对应，禁止据此声称可完整重现现用版本。缺少先前剧情移动/拾取标记文件及 5 个 special 入口等差异尚未恢复。

本次 IMPLEMENTED：五处地图 graphics_id 对齐现用 ROM。TESTED 范围：JSON 仅指定字段变化；现用 ROM 地图/部分脚本静态检查、守墓人战斗及冷启动战后普通存档通过。未构建新 ROM，未在 MyBoy 核心复现。

用户随后反馈 MyBoy 又能正常玩；重置根因未确认，已停止针对重置的进一步修改。全项目剧情/设计状态未知，不能把本次检查升级为全游戏测试通过。

详情：C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\体检与接力记录.md。
