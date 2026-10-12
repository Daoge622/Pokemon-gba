thread_id: 01a12953-cbc7-7870-81e9-94ee23898b95
updated_at: 2026-10-11T08:28:25+00:00
rollout_path: \\?\C:\Users\DaoGe\.codex\sessions\2026\10\11\rollout-2026-10-11T12-58-39-01a12953-cbc7-7870-81e9-94ee23898b95.jsonl
cwd: \\?\C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe

# 排查送神火山一层老头 NPC 战斗胜利后重置问题，并审计同类 Bug

Rollout context: 用户提供 ROM `E:\Pekemon Gba\EmeraldStory-一周目完整版.gba`、MyBoy 即时存档 `C:\Users\DaoGe\Downloads\EmeraldStory-一周目完整版.st0`，补充说明即时存档发生在战斗中，NPC 是送神火山一层老头。用户要求定位根因、全游戏体检并修复，不要防御性编程；后来明确授权本次仅运行无窗口模拟器核心复现。用户强调所有修改要留工作痕迹，方便 Claude 接手。

## Task 1: 送神火山一层战斗重置定位

Outcome: partial

Preference signals:

- 用户要求“不要防御性编程”，因此修复应针对确认的根因，不添加吞错、兜底或隐藏异常逻辑。
- 用户要求“你改了什么东西记得工作留痕，我后面让Claude对接的时候方便” -> 后续必须记录文件、ROM 地址、原因、验证结果和未验证范围。
- 用户授权“只运行无窗口的模拟器核心”，但项目 AGENTS.md 默认禁止自动运行模拟器；类似任务应先取得明确例外授权，并使用存档副本。

Key steps:

- 确认工程位于 `E:\Pekemon Gba\project`，包含完整 pokeemerald-expansion 源码、测试脚本、mGBA headless 工具和既有 MyBoy 修复记录。
- 读取 `MtPyre_1F` / `MtPyre_2F` 地图脚本。送神火山一层脚本本身为空地图脚本；老头战斗入口来自 `data/scripts/part55.inc` 的 `Part55_GraveWorker`，使用 `trainerbattle_single TRAINER_STORY_C_03, StoryC_Text_GraveIntro, StoryC_Text_GraveDefeat, Part55_GraveWorker_Won`。
- 对应训练家是 `TRAINER_STORY_C_03` / `PARTNER_STORY_C_03`，战斗队伍在 `src/data/battle_partners.party`，名称“守墓人”，Expert，Yamask/Lampent 等。
- 复核 `battle_setup.c`：战斗参数保存 `sTrainerBattleEndScript`，战后通过 `BattleSetup_GetScriptAddrAfterBattle()` 返回脚本；普通胜利路径进入 `CB2_ReturnToFieldContinueScriptPlayMapMusic`，随后设置训练家旗标。
- 解压 `.st0` 成 MyBoy 状态数据，确认格式为 gzip；ROM SHA256 为 `cf9b34f57b57a71613e12fe078eba35835ec9e1283ac355b4436201bf854cbde`，普通 `.sav` 为 131072 字节。状态寄存器和 EWRAM 中的训练家战斗参数可与当前 ROM 对上。
- 通过临时 `work/runtime.py` 加载 ROM、普通存档和 MyBoy 状态，尝试把 MyBoy 状态映射到 libretro/mGBA 核心。运行后 CPU 能继续执行，未得到“战斗胜利后重置”的直接复现。
- 后续对另一个已修复 ROM 与状态做了无窗口回放，观察到状态可继续运行，但没有形成送神火山问题的确定根因或提交修复。

Failures and how to do differently:

- 本轮没有完成确定的根因确认、源码修复、release 构建或全游戏体检报告；不能把“可继续运行 headless”当作 MyBoy 问题已解决。
- MyBoy 状态导入依赖手工推断状态布局和 CPU 恢复点，当前结果不足以证明与手机 MyBoy 的实际崩溃瞬间完全一致。后续应优先获得真正卡死/重置瞬间保存的 `.st0`，并记录当时 PC、LR、SP、脚本指针、战斗参数和回调。
- 现有源码中 `Part55_GraveWorker_Won` 先设置 `FLAG_STORY_C_01`，再执行普通战后流程；需重点对比该脚本的继续脚本参数、训练家旗标映射、`sTrainerBattleEndScript` 生命周期及 MyBoy 对 ROM mirror / tagged function pointer 的执行兼容性。

Reusable knowledge:

- 权威源码/工程实际位于 `E:\Pekemon Gba\project`；本 rollout 的 `rollout_cwd` `C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe` 只是临时工作区，不能当作源码权威目录。
- 项目 AGENTS.md 要求开始任务前读取 handoff 文档，并禁止自动启动模拟器/运行 ROM；本轮用户明确授权了无窗口核心例外。
- 既有项目记录指出：pokeemerald-expansion 的 effect-instrumented 脚本命令/特殊函数可能带 `0x0A/0x0B` ROM mirror 标签，MyBoy 可能错误地从 mirror 执行代码；已有修复方案是通过 `SCRIPT_UNTAG_FUNC` 在调用前还原地址。但本轮未证明该机制就是 Mt. Pyre 老头问题的根因。
- `scripts/tests/check-immediate-scripts.py` 可做源代码立即脚本审计；`scripts/qa/sweep` 包含全地图事件扫描和训练家战斗扫描，但必须遵守项目的无 GUI/无 ROM 自动运行限制，除非用户再次授权。

References:

- ROM: `E:\Pekemon Gba\EmeraldStory-一周目完整版.gba`
- Instant state: `C:\Users\DaoGe\Downloads\EmeraldStory-一周目完整版.st0`
- Save: `C:\Users\DaoGe\Downloads\EmeraldStory-一周目完整版.sav`
- Battle script: `E:\Pekemon Gba\project\data\scripts\part55.inc`, labels `Part55_GraveWorker`, `Part55_GraveWorker_Won`
- Story text: `E:\Pekemon Gba\project\data\scripts\story_c.inc`, `StoryC_Text_GraveIntro`, `StoryC_Text_GraveDefeat`
- Battle engine: `E:\Pekemon Gba\project\src\battle_setup.c`, especially `TrainerBattleLoadArgs`, `BattleSetup_GetScriptAddrAfterBattle`, `CB2_EndTrainerBattle`
- Temporary replay harness created in workspace: `C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\runtime.py`
- Evidence: user supplied “战斗中 老头npc”; no explicit confirmation that the issue was fixed.
