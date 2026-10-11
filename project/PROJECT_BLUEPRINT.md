# 项目技术蓝图

当前源码入口：`D:\Pokemon gba\project`（Windows 普通文件夹，2026-10-10迁移）；WSL 仅编译缓存。先读该目录 AGENTS 和四份 Handoff，历史路径不作为当前入口。

当前工作规则：仅终端编译和静态/本机单元检查，禁止自动启动 GUI、模拟器和 ROM；工作区 `allowGui=false`，Windows Test 仅为 Build 别名。早先环境验收记录属于历史，不代表本轮运行过游戏。开局实现见 OPENING_IMPLEMENTATION.md；历史调查见 CHINESE_SUPPORT_RESEARCH.md。当前已完成简体中文底座迁移，原创剧情直接使用 UTF-8 中文；迁移与限制见 CHINESE_BASE_MIGRATION.md。

最后更新：2026-10-07。当前真实实现至PART7，状态以docs/ai-handoff/PROJECT_STATE.md为准；早期Bug修复与本轮授权无界面运行验证见BUGFIX_PLAYABILITY_2026-10-07.md。长期默认禁GUI/ROM规则保留。

2026-10-06：环境搭建历史验收：WSL2 依赖、完整常规/Release 编译、GBA ROM、mGBA 运行与开局地图、Porymap 工程读取、VS Code 支持和一键测试均已验证。

## 技术底座

- 官方仓库：https://github.com/rh-hideout/pokeemerald-expansion
- 稳定版：`expansion/1.17.1`，2026-09-29 发布。
- 固定上游提交：`bb1093a7c72d3961d9a37d8e02ad2abc2c866682`。
- 开发分支：`project/part7`；`project/main` 保留英文 checkpoint。上游 remote：`upstream`。不自动升级、不使用 upcoming。
- Windows 工作区和工具入口：`D:\Pokemon gba`。`source` 仅保留初次搭建快照，不能用于日常编辑。
- 权威源码已迁移到 WSL2 原生 ext4：`/home/pokemon/projects/emerald-story`。
- 对应 Windows 路径：`\\wsl.localhost\Ubuntu-24.04\home\pokemon\projects\emerald-story`。
- 日常只编辑 Linux 工程；当前禁止运行会打开 GUI 的入口，已有编辑器中可继续编辑。完整官方 Git 历史已补齐，开发分支仍固定在 1.17.1，不随远程分支漂移。

## 设计目标

长期维护的 GBA 原生 ROM Hack，输出 `.gba`，保留绿宝石 GBA 像素风格。剧情为核心，未来改写 NPC、地图事件、主线和支线。战斗系统采用 Expansion 的现代实现。当前源码实施至PART7冠军及名人堂后自由丰缘，详细实现/定稿/验收边界见PROJECT_STATE.md与各批报告；二周目阿尔刻篇未实施。保留原主线，扩展支线、训练家、世界密度与现代机制。

## 机制和数据边界

| 内容 | 当前配置 | 主要入口 |
| --- | --- | --- |
| Gen 1–6 宝可梦 | 启用 | `include/config/species_enabled.h` |
| Gen 7–9 数据 | 保留官方默认启用；原版野生表和剧情投放未扩写 | 同上及 `src/data/pokemon/` |
| 妖精属性 | 保留官方现代属性数据 | `src/data/pokemon/species_info/`、属性相性表 |
| 物理/特殊分家 | `B_PHYSICAL_SPECIAL_SPLIT = GEN_LATEST`，启用 | `include/config/battle.h` |
| 现代技能、特性、道具、进化方式 | 保留官方实现与默认配置 | `include/config/`、`src/data/` |
| Mega Evolution | `P_MEGA_EVOLUTIONS = TRUE`，实现保留可用 | `species_enabled.h`、`src/battle_util.c`、`src/data/pokemon/form_change_tables.h` |
| Z 招式 | 游戏中禁用 | `PROJECT_ENABLE_Z_MOVES = FALSE` |
| 极巨化/超极巨化 | 游戏中禁用；形态资源保留 | `PROJECT_ENABLE_DYNAMAX = FALSE` |
| 太晶化 | 游戏中禁用；形态资源保留 | `PROJECT_ENABLE_TERASTAL = FALSE` |

项目开关集中在 `include/config/project.h`，分别在官方三个 `Can...` 判定函数中拒绝激活，对应入口位于 `src/battle_z_move.c`、`src/battle_dynamax.c`、`src/battle_terastal.c`，覆盖玩家和对手；没有删除实现、道具、资源或枚举。上游 `TESTING` 测试构建保持原始机制可测。未来重新开启时改开关，再配置获得道具、允许的战斗、对手数据等条件并做测试。

`GEN_LATEST` 保持上游 `GEN_9`；“支持 Gen 1–6”不等于把全局战斗规则降到第六世代。Mega 仍遵循上游的 Mega 手环、对应 Mega 石和物种条件。当前未添加发放道具的正式剧情，因此新档开局不能直接 Mega。后续剧情阶段再设计获得途径。

## 工具链

- 已有 Windows Git 2.55.0.windows.3、VS Code 1.138.0，复用。
- WSL 3.0.1.0 / WSL2 已验证运行。Ubuntu 24.04.5 LTS，Linux 用户 `pokemon`，源码位于原生 ext4，WSLg 用于 Porymap。
- ARM GCC 13.2.1、binutils 2.42、newlib 4.4.0；本机编译 GCC 13.3、Make 4.3、Python 3.12.3、Git 2.43.0。
- 官方依赖：`build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi git libpng-dev python3`。补齐 `pkg-config`、`unzip`、`ripgrep`。
- 工程自带的构建工具由 `make` 自动编译。无需商业原始 ROM 或独立 BIOS 下载。
- mGBA 0.10.5 Windows x64 便携版：`D:\Pokemon gba\tools\mgba-0.10.5\mGBA-0.10.5-win64\mGBA.exe`。
- Porymap 6.3.1 Linux 版，从官方 tag 编译，提交 `139eda92b3b06a5fd675a9825a07ac62e98c1566`；Qt 6.4.2。路径 `/home/pokemon/tools/porymap-6.3.1/porymap`。Windows 便携版保留，但日常入口使用 WSLg，确保文件监听正常。
- Poryscript 3.6.1：官方 Linux 二进制用于 WSL，Windows 二进制已验证能编译测试脚本。
- VS Code Windows 已有 WSL 扩展；Ubuntu 扩展宿主已安装 Poryscript 3.2.0、C/C++ 1.34.4。
- Linux 包版本已记录于 `D:\Pokemon gba\logs\linux-package-versions.txt`。

## 编译与日常工作流

以下入口已经实际跑通。Windows 入口使用当前进程的 ExecutionPolicy Bypass，不修改系统级执行策略。

WSL 中：

```bash
cd /home/pokemon/projects/emerald-story
make -j"$(nproc)"          # 官方常规构建：pokeemerald.gba
bash scripts/build.sh       # 仅编译导出；禁止自动运行 ROM
bash scripts/build.sh --release # make release，关闭开发日志；真实 GBA 发布使用此产物
```

Windows：双击 `D:\Pokemon gba\Build-and-Test.cmd`，或运行：

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass -File 'D:\Pokemon gba\scripts\dev.ps1' -Action Test
```

VS Code 已打开的工程中，按 **Ctrl+Shift+B** 执行 `GBA: Build (quiet, no emulator)`，仅编译导出。保留 Release 构建任务，移除自动打开 Porymap 任务。当前禁止任何 GUI 启动。

编译日志写入 `logs/build-latest.log`，当前测试 ROM 导出到 `artifacts/current/pokeemerald.gba`，存档留在同一目录并排除版本控制。编译失败时工作流返回错误，绝不启动旧 ROM。Release ROM 为 `artifacts/current/pokeemerald-release.gba`；模拟器实测不替代真实硬件实测。

Porymap：双击 `Open-Porymap.cmd`，或运行 VS Code 任务 `GBA: Open Porymap`。自动打开权威 Linux 工程。日志确认官方历史识别成功、监听 34/34 文件、显示 PetalburgCity；不需要同步两份源码。

Porymap 的脚本跳转配置用官方 `%F` / `%L` 占位符调用 `scripts/open-vscode-file.sh`，连接同一 WSL VS Code 工程。Poryscript 的 `use_poryscript=1` 已启用；新地图可采用 `.pory`，旧 `.inc` 保留。

## 原创剧情与数据的主要入口

- **地图和 NPC 摆放、触发区域、传送点**：Porymap；`data/maps/<地图名>/map.json`。
- **地图事件与 NPC 对话**：`data/maps/<地图名>/scripts.inc` 或新建 `scripts.pory`；可配合 `text.inc` / `text.pory`。
- **地图布局与碰撞**：`data/layouts/`、`data/tilesets/`，优先让 Porymap 保存。
- **共享剧情脚本和文本**：`data/scripts/`、`data/text/`；在 `data/event_scripts.s` 注册 include。
- **剧情状态**：`include/constants/flags.h`、`include/constants/vars.h`。先检查闲置编号，集中命名；不要复用正在使用的标志。
- **新增脚本底层功能**：`src/scrcmd.c`、`src/field_specials.c`、`data/script_cmd_table.inc`、`asm/macros/event.inc`。
- **宝可梦属性、进化、形态**：`src/data/pokemon/species_info/`、`form_change_tables.h`。
- **升级技能**：`src/data/pokemon/level_up_learnsets/`；可学技能源数据 `all_learnables.json`。不要编辑生成的 `teachable_learnsets.h`。
- **野生分布**：`src/data/wild_encounters.json`；生成头文件由工具负责。
- **训练家和队伍**：`src/data/trainers/` 及训练家源文件；生成头文件由 `trainerproc` 负责。
- **招式、特性、道具与系统配置**：`src/data/`、`include/config/`、对应 `src/battle_*.c`。
- **美术**：`graphics/` 和 `data/tilesets/`，保留 4bpp、GBA 调色板和既有尺寸限制。

入门先用 Porymap 找到 NPC 和脚本标签，再在 VS Code 编辑。示例 `data/scripts/dev_environment_smoke.pory` 仅验证工具链，未绑定任何 NPC、未改变剧情；它编译成 `.inc` 后参与 ROM 构建。

当前字体/字符表沿用官方英文基线。技术文档用中文不代表游戏已支持中文显示；未来中文剧情需要另行规划字体、字符表和文本工具链。

## 长期维护

每次系统变更先建分支、查看 diff、运行合适的测试，并更新 `DEV_LOG.md`。生成物、工具二进制、模拟器存档不提交；项目配置、`.pory` 源、构建入口和工具版本需提交。不要重新 `git init` 覆盖已经克隆的历史。

首次搭建提交采用明确的本地自动化署名 `Project Setup <setup@localhost>`；不替用户填写全局 Git 身份。后续个人提交前可自行设置仓库级 `user.name` / `user.email`。

更新上游前备份存档，阅读 release notes，先在分支合并固定 release tag，完成编译和剧情/战斗测试后再合入项目。调整启用物种或存档布局可能要求新档，须记录迁移决定。

参考：官方 `INSTALL.md`、`docs/install/windows/WSL.md`、`docs/install/linux/UBUNTU.md`；Poryscript 官方 README；https://huderlem.github.io/porymap/ 。

## 验收证据和当前限制

- 常规 ROM / Release ROM：均为 33,554,432 字节（32 MiB）；常规 ROM 使用约 79.72% ROM 空间，Release 约 80.05%。两次完整编译返回 0。
- 常规 ROM SHA256：`e0d6f5ab29a2228e91305c92a94e030dc9a9f3abbb91942dfafc9b98dd05d16c`。
- Release ROM SHA256：`6a648d3ec1c3ff12e3f1c668b40fe8e7755f0fffd27bdd9e27df2db3741ab83a`。
- Windows mGBA 0.10.5 实际启动该常规 ROM，观察到开场和标题界面，约 60 fps。
- 为避免窗口按键过短而被游戏帧采样漏掉，用 Ubuntu 官方包的 mGBA 0.10.2 核心公开 API 持续输入 Select，运行 2880 帧，成功进入原版开局搬家货车地图。截图 `artifacts/verification/field.png`，测试即时状态 `field.ss0`，没有改 ROM 或注入游戏数据。辅助检查源码：`scripts/verify-rom.c`；库依赖 `libmgba-dev`，不参与日常编译。
- 常规一键测试日志：`logs/one-click-test.log`；首次完整构建：`logs/build-initial-success.log`；Release：`logs/build-release-success.log`；Porymap 日志：`/home/pokemon/.local/share/pret/porymap/porymap.log`。
- 原始 NPC、地图、主线和支线未修改。未绑定的 Poryscript 测试源正常生成并链接进 ROM。
- 无阻塞环境问题。Release 构建有上游现有的 newlib 系统调用、LTO 类型和 Mystery Gift 警告，完整日志已保留；本次不改写这些游戏系统。实体 GBA 硬件未实机测试。
- 本次用户按 Escape 停止 Windows 窗口自动控制后，已停止窗口操作，仅继续文件和日志收尾。
- 配置恢复：依赖入口 `scripts/bootstrap/bootstrap-linux.sh`；Porymap 官方源码复建 `bash scripts/bootstrap/build-porymap.sh`。日常无需重复安装。


## 开局事件维护登记

上一批见 OPENING_IMPLEMENTATION.md；102号道路与橙华市见 ROUTE102_PETALBURG_IMPLEMENTATION.md。项目永久Flag为0x20送蛋、0x21古辰进口高级球、0x22橙华水之石、0x23道路Full Heal；新普通训练家ID855，原预留上限864不变。文本继续英文，中文仅保留调查结果。

## 当前中文底座（2026-10-06）

采用方案 A，固定引入 rh-hideout-chinese `e8671a6d...` 的中文模块，仍保持官方 1.17.1 的存档及战斗规则。6771 个双字节映射，普通/小字字库；保留 Gen 1–9、妖精、Mega，未开启跟随/HGSS 图鉴。备份 tag `pre-chinese-base-migration`，中文分支 `project/chinese-base`。原有四 Flag 0x20–0x23 和全部开局内容保留，中文青年名为埃文。

源码文本使用 UTF-8、原有 charmap 编译流程。Poryscript 默认字体 `1_chinese_rse`；长中文必须明确断行，format() 不自动拆中文长句。命名键盘仍为字母键盘，不扩大玩家名/昵称存档字段。普通/Release 构建和中文/事件检查成功；未运行 ROM，UI 视觉与旧存档运行验收待人工完成。

终端构建：`bash scripts/build.sh` / `bash scripts/build.sh --release`；自动检查编码、字库、数据保持和原创事件，再复制产物至 Windows artifacts/current。所有 GUI 自动启动继续禁用。详细报告和手工验收项见 CHINESE_BASE_MIGRATION.md。

## PART1 当前规则（2026-10-06）

- 实现与验收：`PART1_RUSTBORO_DEWFORD_IMPLEMENTATION.md`；机器可读分配/坐标：`docs/project/part1-manifest.json`。
- 实施前 checkpoint：`pre-part1-implementation`（a1ddc7b0）；当前分支 `project/part1`，仍基于官方 Expansion 1.17.1 和已验证中文底座。
- 重要道具学习装置：原 `FLAG_RECEIVED_EXP_SHARE` 表示领取，新 `FLAG_PART1_EXP_SHARE_ENABLED` 表示开启；领取后默认开启，只在玩家确认使用时切换。参战各100%基础经验，后台各50%，蛋/濒死0；关闭恢复传统分摊；未启用等级上限或等级差经验惩罚。
- 原普通商店机制不变；限购配置在 `src/limited_shop.c` 中现有古辰高级球和武斗港口潜水球两条；同地图同道具共享资格。
- 永久 Flag 0x24–0x2E、每日 Flag 0x923–0x925；没有永久 VAR、没有扩大存档。`FLAG_TEMP_C` 按地图管理暂时隐藏物种，`VAR_TEMP_F` 仅控制当前地图老师触发。
- 花店新增每日随机树果独立于原店员每日赠礼；学校每日题目取原RTC dailySeed模3，正确但满包可当日直接补领。依赖原版RTC前进；模拟器RTC关闭时不会跨日刷新。
- 新系统入口：`src/part1.c` / `include/part1.h`（日题/经验算术），`data/scripts/part1.inc`（共享老师赠礼），新增地图脚本统一 `*_Part1_*` 标签。野生表 `src/data/wild_encounters.json`；初次馆主队伍 `src/data/trainers.party`。
- `scripts/build.sh` 在正常/Release构建后执行中文、开局、102/橙华、PART1全部检查，只复制产物，拒绝 `--run`。所有Windows GUI入口继续禁用。

## PART2 当前规则（2026-10-06）

当前开发分支 `project/part2`，实施前 `pre-part2-implementation` 保存PART1提交cd07d4043e。当前状态与38项验收见 `PART2_SLATEPORT_MAUVILLE_IMPLEMENTATION.md`；分配/地图/队伍及原进化表见 `docs/project/part2-manifest.json`。

新增凯那/110/紫堇事件和Route116回填；不改117/绿荫/烟囱山/水舰队基地。固定1.17.1与现有中文底座，全部此前赠礼/学习装置规则保留。

- Flag0x2F–0x3A、隐藏道具Flag0x264；任务VAR0x404E，平安符0/1/2/3，本批只0→1。ITEM_PEACE_CHARM追加874，旧物品ID不变；存档布局不扩大。
- 特殊商品同一通用表当前四条：古辰高级球、武斗潜水球、凯那先机球、紫堇磁铁；均原价每档1个。
- Summary能力页按A循环能力/数值IV/数值EV，EV合计/510；沿用原导航和中文字体。
- ITEM_EVOLUTION_STONE别名原LinkingCord796，正式名进化石；29个通讯源物种/30目标全改为直接使用1个，不需原通讯携带物。Clamperl使用原是/否菜单选两个目标，B取消；其他进化与Mega保留。本批未设进化石稳定来源。
- 飞天螳螂18级只固定攻击IV31，队伍满可补领。NPC原生交易追加大嘴娃→六尾18“小焰”，旧交易保留匹配等级。
- 当前默认构建附带五套终端验证（中文/开局/102橙华/PART1/PART2）；普通和Release只导出，不自动执行ROM。运行时/视觉/旧存档载入验收仍需人工。

## PART3 当前规则（2026-10-06）

当前分支 `project/part3`，实施前标签 `pre-part3-implementation` 保存完整PART2提交53e4aef8634b34273cdcc9beac03e8d860b4be9e。范围从117/绿荫至釜炎第四徽章，原主线顺序和后续地图保持；中文版底座继续固定Expansion1.17.1。完整54项报告见 `PART3_VERDANTURF_LAVARIDGE_IMPLEMENTATION.md`，分配/坐标见 `docs/project/part3-manifest.json`。

- 新永久Flag23个：0x3B–0x4F、0x54–0x55；隐藏道具4个：0x265–0x268。均替换已验证未使用的上游槽；旧Flag/Trainer ID、存档结构不重排。Trainer追加857–860，count861、MAX864。
- 炎帝状态复用未用VAR0x4083：0从未挑战、1未捕获等待、2已捕获、3联盟重生可挑战。战前即记等待，覆盖战败白屏中断；捕获永久离开，其他结果不得跨地图刷新。每次新殿堂胜利只将等待→重生，包含首次冠军，也避免重生后再次失误永久错过；从未挑战和已捕获保持原值。
- 热焰原怪力支路上方新增灼热岩窟15×19地图，下方喷射火焰TM；保留第四徽章/怪力检查和原2个warp/原火之石。新地图及layout仅追加，使用原Lavaridge火山岩tileset，复用没有原地图使用的MAPSEC_FIERY_PATH2中文名，不移动地图区域ID。
- 首次成功回忆招式免费，取消/蛋/无招式均保留资格；其后原心之鳞片收费。玻璃兑换保留原7种，炽热岩石1500灰，满包复用原pending变量值17、重领不重复扣灰。
- 泛用限购表新增秋叶黑暗球，原价每档1；没有新增第一颗通用进化石（ITEM_EVOLUTION_STONE）来源，新增的火之石仍是独立原生ITEM_FIRE_STONE。
- 新人胖丁20六项IV31，只是普通女火岩队手下；本批不赋正式名字/改立绘，不做未来出场。长期角色限制仅记文档。赤焰松和亚莎初战、胜利家族调整，原再战/撤退/徽章/TM保持。
- 野生只热焰/114/流星1F1R/凹凸，后期宝贝龙区与其余地图保持。PART1学习装置100/50、蛋濒死0、关闭传统分摊及PART2进化石/IV/EV系统均继续回归。
- 日常 `bash scripts/build.sh` 与 `bash scripts/build.sh --release` 在构建后运行此前5套和本批5套无界面检查，只复制ROM到Windows；`--run`持续拒绝。未运行ROM，视觉与真实战斗须人工验收。

- PART3最终交付：普通/Release一键工作流返回0，全部10套无界面检查PASS；32 MiB ROM/GBA头与Windows副本一致。完成标签part3-verdanturf-lavaridge；实机/模拟器运行时验收仍待人工。没有运行GUI或ROM。

## 2026-10-07 — PART4 实施完成

Codex按用户定稿实施至第六徽章与明确回填。normal/release及12套无界面检查PASS，未运行ROM。当前分支project/part4，保留1.17.1存档/引擎结构，复用限购表扩2单位与传说恢复；完整事实见docs/ai-handoff/PROJECT_STATE.md和PART4_PETALBURG_FORTREE_IMPLEMENTATION.md，人工验收与正式美术待完成。旧章节的分支/范围为历史，不能覆盖当前handoff。
