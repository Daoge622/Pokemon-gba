# AI HANDOFF / PROJECT MEMORY RULES

这是一个长期项目。以下规则适用于 Codex 每次处理本项目任务，无论用户是否再次提醒。

## 项目入口与权威源码

- Windows 项目入口：`D:\Pokemon gba`。
- 唯一权威源码、Git、美术与接力文档：Windows 普通文件夹 `D:\Pokemon gba\project`。
- WSL `/home/pokemon/projects/emerald-story` 仅为编译缓存，禁止直接编辑或提交；通过 Windows `scripts/windows/dev.ps1 -Action Build/Release/Sync` 单向同步。根入口 `scripts/dev.ps1` 转发至此。
- 记录 PART7 差异使用 `-Action RecordDeltas`，然后复核返回 Windows 的清单；不自动接受基线。
- 权威文档在 `project/docs/`；入口 `D:\Pokemon gba\docs` 是镜像，先改权威再同步。
- `D:\Pokemon gba\source` 是旧初始快照，不得误作当前源码。
- 本文件在 Windows 入口和权威仓库根目录保持相同内容，不形成两套规则。接力文档的权威位置与镜像同步方式按 `PROJECT_STATE.md` 执行。

## 每次任务开始前必须阅读

每次开始处理本项目任务前，无论用户是否再次提醒，必须先读取：

1. `docs/ai-handoff/PROJECT_STATE.md`
2. `docs/ai-handoff/CANON_DECISIONS.md`
3. `docs/ai-handoff/CURRENT_TASK.md`
4. `docs/ai-handoff/CHANGELOG.md`

如果任务涉及已经定稿的剧情 PART，继续读取对应的：

- `docs/story/PART1_FINAL.md`
- `docs/story/PART2_FINAL.md`
- `docs/story/PART3_FINAL.md`
- 未来存在的 `docs/story/PART*_FINAL.md`

不得只依赖旧聊天、Agent 记忆或文件名来推断项目状态。

## 1. Source of Truth 优先级

冲突时按以下项目事实优先级处理：

1. 用户当前明确指令
2. `CANON_DECISIONS.md`
3. 对应 `PART*_FINAL.md`
4. `PROJECT_STATE.md`
5. `CURRENT_TASK.md`
6. `CHANGELOG.md`
7. Agent 自己的推断

禁止擅自修改已经锁定的 Canon。只有用户明确要求修改时，才能修改已确认设定。

## 2. 严格区分设计状态与实现状态

这是最高优先级的状态管理规则，必须明确区分：

| 状态 | 含义 |
| --- | --- |
| DESIGN | 只是讨论/设计 |
| FINALIZED | 用户已经接受并定稿 |
| IMPLEMENTED | 已实际修改源码/数据并完成实现 |
| TESTED | 已经过对应验证 |

绝对不能因为某个 PART 已经有 FINAL.md 就声称它已经写入 ROM。

只有代码实际存在、实现报告存在、或用户明确确认 Codex 已完成，才能标记 IMPLEMENTED；记录依据，不把实现计划当实现报告。

TESTED 必须说明验证范围与结果：构建成功、静态检查通过和游戏内人工验收分别记录。构建/静态检查不代表剧情、地图演出或游戏运行已验证。没有对应验证，不提前升级状态。

## 3. 每次开始任务

开始修改代码之前先阅读 Handoff 文档，确认：

- 当前技术底座
- 已实现功能
- 已定稿但尚未实现内容
- 当前任务
- 已锁定 Canon
- 已知 Bug / 风险
- 当前 build 状态

然后再开始工作。不要因为旧聊天里存在不同想法，覆盖 Markdown 中已经锁定的事实。修改前核对实际仓库和已有变更，不假设文件路径或完成进度。

## 4. 每次任务结束必须维护 Handoff

完成任何有实质变化的工作后，检查并维护：

- `docs/ai-handoff/PROJECT_STATE.md`：真实实现状态、技术状态、build 状态和已知问题。
- `docs/ai-handoff/CANON_DECISIONS.md`：只写用户明确确认的长期设计决定。
- `docs/ai-handoff/CURRENT_TASK.md`：当前完成到了哪里、尚未完成什么、下一步是什么、任何 blocker。
- `docs/ai-handoff/CHANGELOG.md`：按日期追加简洁变更记录。

Codex 自己做出的技术实现选择，如果只是内部实现细节，不要擅自把它提升成剧情/设计 Canon。

禁止直接复制整个终端日志或聊天内容。如果本轮没有真实状态变化，完成检查即可，不要制造无意义记录。

用户当前明确限制只修改指定文件时，遵守该范围；不得以维护 Handoff 为由修改未授权文件。例如，用户要求本轮只修改 AGENTS.md 时，只核查 Handoff，不编辑其他文档。

## 5. 实现完成后同步状态

如果某个 FINAL PART 被真正实现，例如 `PART2_FINAL.md`，完成代码实现和构建后，`PROJECT_STATE.md` 中才可以从 FINALIZED 更新为 IMPLEMENTED。

如果经过实际测试，才按对应验证范围更新为 TESTED。不要提前升级状态。部分实现须说明完成和未完成部分，不能将整个 PART 标成完成。

## 6. 多 AI 协作

本项目会由 ChatGPT、Claude、Codex 轮流工作。

不要把关键信息只放在自己的输出里。对下一位 Agent 有用的事实必须写进共享 Markdown。

不要建立一份“只有 Codex 才知道”的独立项目真相。记录实际执行 AI；署名无法核实就注明未知，不替其他 AI 认领变更。

## 7. Pending 规则

用户没有最终决定的内容，只允许放在 `CURRENT_TASK.md` 的 Pending / 未决定部分，不要放进 `CANON_DECISIONS.md`。

不得自行补全刻意未知的身份、年龄、出处或其他字段，也不得把候选方案写成用户已定稿。

如果遇到多个可行技术方案，可以自行选择安全、兼容、简单的实现方式。但如果会改变游戏设计或用户已经确认的体验，先遵守 Canon，不要自行重设计。

## 8. 禁止 GUI / 模拟器

这是长期硬规则。绝对禁止自动：

- 启动 mGBA
- 启动其他模拟器
- 运行 ROM
- 使用 start
- 使用 explorer
- 使用 ShellExecute 或类似 GUI 启动方式
- 打开 GUI
- 自动打开构建产物
- 弹出全屏窗口

允许在用户授权任务范围内使用：

- CLI
- 编辑源码
- git
- normal build
- release build
- static checks
- scripts
- automated tests

允许的脚本和自动测试必须无界面、不启动模拟器、不运行 ROM；执行前核对入口行为，不能借脚本间接触发禁止操作。

需要人工 mGBA 验证的内容只列入最终报告，由用户自己执行。编译结束不得自动启动游戏，不自动打开文件或程序。

## 9. 不破坏现有工程

修改前先检查现有实现和项目约定，优先复用：

- 已有 Flag 系统
- 已有 helper
- 已有限购商店系统
- 已有 NPC 脚本模式
- 已有中文文本基础
- 已有 Expansion 功能

不要重复造第二套同功能系统。不要因为实现一个小功能对核心引擎做不必要的大规模重构。新增 Flag / VAR / Trainer 前核对全局占用，保留原流程与存档兼容性。

## 10. 文档原则

Handoff 文档必须精炼、准确、不重复、可供另一个 AI 快速接手。

不要将聊天全文、终端全文、长篇推理放进 Handoff 文档。已有报告、日志或定稿用路径引用，不重复扩写独立真相。

目标：一个完全没有当前聊天上下文的 Agent，只读这些文件，也能准确继续项目。
