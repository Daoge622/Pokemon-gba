# CLAUDE.md — 项目级长期规则

本文件是本项目的长期工作规则，每次进入项目都适用，无需用户再次提醒。

## 0. 路径说明（2026-10-12 起转线上）

- **唯一权威源码与 Git 仓库：GitHub `https://github.com/Daoge622/Pokemon-gba` 的 `main` 分支**，工程在 `project/` 目录。本地文件夹只是工作副本。
- 开工前先 `git pull`；完成修改后必须提交并推送到 GitHub，并告知用户提交编号。重要改动先走分支，用户确认后合并。
- 权威接力/剧情文档在仓库 `project/docs/`，不再有 `D:\Pokemon gba\docs` 镜像。
- 不得提交 ROM、存档、密钥或登录凭据。
- 旧的 `D:\Pokemon gba`、WSL 编译缓存与 `dev.ps1` 同步流程已不再是权威。禁止 GUI/模拟器/ROM 规则继续有效。

下文中的 `docs/...` 路径均指仓库 `project/docs/` 下的文件。

==================================================
AI HANDOFF / 项目记忆规则
==================================================

这是一个长期开发项目。

以后每一次进入本项目工作，无论用户是否再次提醒，都必须先阅读：

- docs/ai-handoff/PROJECT_STATE.md
- docs/ai-handoff/CANON_DECISIONS.md
- docs/ai-handoff/CURRENT_TASK.md
- docs/ai-handoff/CHANGELOG.md

如果当前任务涉及已经定稿的剧情 PART，还应主动阅读对应：

- docs/story/PART1_FINAL.md
- docs/story/PART2_FINAL.md
- docs/story/PART3_FINAL.md
- 以及未来新增的 PART*_FINAL.md

## 1. 信息优先级

发生冲突时优先级为：

1. 用户当前明确指令
2. CANON_DECISIONS.md 中已经锁定的设定
3. 对应 PART*_FINAL.md
4. PROJECT_STATE.md
5. CURRENT_TASK.md
6. CHANGELOG.md
7. 自己的推测

绝对不要因为自己的理解不同，擅自推翻已经确认的 Canon。

如果用户明确修改旧设定，则以用户最新决定为准，并同步维护 Canon。

## 2. 必须区分“设计”和“已实现”

这是最高优先级规则之一。

不要把“已经讨论”“已经设计”“已经定稿”“已经写进提示词”
误写成“已经由 Codex 实现”。

PROJECT_STATE.md 中必须明确区分：

- DESIGN / 已设计
- FINALIZED / 已定稿
- IMPLEMENTED / 已实际写入游戏
- TESTED / 已测试

只有看到实际代码修改、实现报告或用户明确确认完成，才能标记为 IMPLEMENTED。

## 3. 每次开始工作

开始实际工作之前，先读取 handoff 文档，快速确认：

- 当前项目技术状态
- 已锁定 Canon
- 当前做到哪个 PART
- 哪些只是设计
- 哪些已经实际实现
- 当前正在解决什么问题

不需要每次向用户长篇复述。理解后直接继续任务。

## 4. 每次结束工作必须进行 handoff 维护

每一次完成有实质变化的项目工作后，必须检查并维护：

- docs/ai-handoff/PROJECT_STATE.md
- docs/ai-handoff/CANON_DECISIONS.md
- docs/ai-handoff/CURRENT_TASK.md
- docs/ai-handoff/CHANGELOG.md

具体规则：

- **PROJECT_STATE.md**：只更新当前真实项目状态。记录真正实施完成的系统、当前技术状态和已知问题。
- **CANON_DECISIONS.md**：只加入用户已经明确接受、正式锁定的设定。不要把 brainstorming、候选方案、Claude 自己的建议写进 Canon。
- **CURRENT_TASK.md**：记录当前正在做什么、已确定什么、还没决定什么、下一位 AI 应该从哪里继续。
- **CHANGELOG.md**：按日期简短追加本轮真正发生的变化。不要复制整段聊天，不要写流水账。

如果本轮没有任何项目状态变化，仍然要完成 handoff 检查，
但不要为了留下记录而制造没有意义的修改。

## 5. PART 定稿

如果用户明确说：“定稿”“整合成 PART X”“总结成 PART X 文本”“这个版本全部保留”，
则应该把最终版本保存/维护到：`docs/story/PARTX_FINAL.md`

一旦成为 FINAL：后续不要因为提出了新想法，直接覆盖旧 Canon。
只有用户明确接受修改后才能更新。

## 6. Claude 与 ChatGPT / Codex 接力

不要假设只有 Claude 会维护项目。ChatGPT、Claude、Codex 会轮流接手。

因此所有对下一位 AI 有价值的信息，必须进入共享 Markdown，
不能只存在于 Claude 对话记忆里。

Markdown 是项目事实来源。聊天记录不是唯一事实来源。

## 7. 不确定内容

如果一个设定还没定：放进 CURRENT_TASK.md 的“未决定 / Pending”，
不要放进 CANON_DECISIONS.md。

如果实现状态不确定：明确写“未确认”，不要猜测已经完成。

## 8. 本项目的重要安全开发限制

除非用户明确改变规则，绝对不要自动启动：

- mGBA
- 任何模拟器
- ROM
- GUI 程序
- explorer
- start
- ShellExecute
- 自动打开构建产物

允许：编辑文件、CLI、git、build、static checks、自动化检查。

需要 mGBA 的测试只写进人工测试报告，由用户自己执行。

## 9. 文档维护风格

Handoff 文档应该：

- 短
- 清楚
- 可快速扫描
- 只保存长期有价值的信息
- 避免重复
- 不复制整段对话
- 不保存已经否决的废案，除非它仍是重要的 Pending

目标：任何新的 Claude / ChatGPT / Codex 只阅读这些文件，
就能在几分钟内正确接手项目。

## 云端构建规则（2026-10-22 用户确认工作方向）

- 日常 ROM 编译使用 `.github/workflows/rom-build.yml`；推送 main/codex/claude 分支源码后云端构建普通版与 Release。默认不在本机编译 ROM，不调用旧 WSL 同步构建入口。
- 开工先核查远程 main 与 CURRENT_TASK 中尚未合并的最新修复分支，不把较旧 main 或本机副本覆盖到用户正在试玩的新修复分支。重要变更仍待用户确认后合并。
- 每次交付检查 Actions 成功、BUILD_SOURCE 源提交号/分支/variant、SHA256 与产物一致，再对齐本机 artifacts/current；禁止只靠文件日期选择“最新版”。普通存档与即时存档兼容性分别说明。
- 本轮最新已构建源码 baa6c65160、run 39712885042；接续文档提交与构建提交可不同，必须核对源码是否发生变化，不能把未编译的新代码当成已交付。
