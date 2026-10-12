# 开发日志

## 2026-10-06 — 环境搭建，等待 Windows 重启

- 从 RHH 官方仓库克隆固定稳定版 `expansion/1.17.1`，上游提交 `bb1093a7c72d3961d9a37d8e02ad2abc2c866682`；创建 `project/main`、保留 `upstream`。
- 复用已有 Git / VS Code / 7-Zip；安装 WSL 3.0.1.0、启用 VirtualMachinePlatform，系统要求重启。没有自动重启。
- 下载官方 Ubuntu 24.04 WSL 镜像并校验；Ubuntu 注册和 ARM 编译依赖安装尚未执行。
- 安装 mGBA 0.10.5、Porymap 6.3.1、Poryscript 3.6.1 便携版及 VS Code WSL / Poryscript 扩展。
- Porymap 日志已确认读取 Windows 暂存工程、监测 34/34 文件、打开 PetalburgCity。浅克隆造成版本历史识别警告，完整历史的网络补齐本次已停止；重启后继续处理。
- 增加可恢复的 Z 招式、极巨化、太晶化游戏禁用开关；保留 Mega、妖精属性、物理/特殊分家和全部现代机制源代码。保留官方 Gen 1–9 数据默认值。
- 配置 Poryscript Make 规则、未绑定 NPC 的环境测试脚本、VS Code 构建任务、Windows 编译/测试入口、忽略规则和换行规则。
- 已验证：Windows Poryscript 把测试 `.pory` 编译为 `.inc`；官方发布文件哈希；WSL 功能启用日志。
- **未验证**：Linux bootstrap、完整 ROM 编译、`.gba` 生成、mGBA 游戏启动/进入游戏、Release 构建、迁移后 Porymap 工程、VS Code WSL 扩展宿主。一键工作流已编写，尚未实际跑通。
- 原版剧情与地图未改动。测试脚本 `DevEnvironmentSmoke` 只参与构建，不绑定角色。
- 已用官方镜像尝试注册 Ubuntu，返回 `HCS_E_SERVICE_NOT_AVAILABLE`；系统虚拟机平台仍待重启。保留日志，没有改用其他编译方案。
- PowerShell / Bash 脚本语法检查通过；未就绪环境的工作流正确返回失败，没有启动模拟器。

## 2026-10-06 14:09 — WSL 系统组件复查

- Ubuntu 注册仍报 `HCS_E_SERVICE_NOT_AVAILABLE`。交叉检查 Windows 启动事件、LastBootUpTime、TickCount64，当前系统内核仍从 2026-09-23 17:24:19 运行，安装后的系统重启尚未发生。
- VirtualMachinePlatform 已启用；补齐官方 WSL 安装说明涉及的 Microsoft-Windows-Subsystem-Linux 组件，结果为 Enabled / RestartNeeded=true。
- 已保存完整诊断和组件结果；没有降低编译方案，没有覆盖或移除已有工程。下一步必须从 Windows 电源菜单执行完整“重新启动”。
- 官方稳定 tag 提交已再次核对一致。完整 Git 历史补齐遇到网络 TLS 报错，浅克隆稳定版本源码仍完整。

## 2026-10-06 — 重启后完成环境验收

- 14:14 完整 Windows 重启已确认；Ubuntu 24.04.5 / WSL2 注册成功，源码迁移至 `/home/pokemon/projects/emerald-story`；日常入口保留在 `D:\Pokemon gba`。
- 安装官方 Ubuntu 编译依赖，补齐项目工具实际使用的 `pkg-config`；GCC ARM 13.2.1、binutils 2.42、newlib 4.4.0、Make 4.3。全部包版本写入 `logs/linux-package-versions.txt`。
- 补齐完整 RHH 官方 Git 历史；稳定版本仍为 `expansion/1.17.1`，不升级至开发分支。
- 修正 Poryscript 生成规则：仅对实际存在的 `.pory` 源建立静态模式目标，避免误处理原版 `.inc`。Linux Poryscript 3.6.1 成功生成并链接未绑定 NPC 的验证脚本。
- 完整常规构建、Windows 一键增量编译/启动、完整 Release 构建全部返回 0。ROM 各 32 MiB；SHA256 及占用见 PROJECT_BLUEPRINT.md。
- Windows mGBA 0.10.5 实际显示开场和标题，约 60 fps；mGBA 0.10.2 公共核心 API 驱动相同常规 ROM 运行 2880 帧，成功进入开局搬家货车，截图和即时状态保存在 `artifacts/verification/`。没有改写 ROM 数据。
- Windows Porymap 能读 WSL UNC 工程，但不能稳定监听跨系统文件；按官方 Ubuntu 文档编译官方 Porymap 6.3.1 / Qt 6.4.2，改日常入口为 WSLg。日志确认版本识别成功、监听 34/34 文件、打开 PetalburgCity。
- VS Code 成功连接 Ubuntu 工程；Ubuntu 扩展宿主安装 Poryscript 3.2.0 和 Microsoft C/C++ 1.34.4。Porymap 脚本跳转使用正确 `%F` / `%L` 占位符，接入同一 WSL 工程。
- 增加 Porymap 重建、打开和脚本跳转入口；不新增免密码 sudo，不改全局 Git 身份，不修改系统级执行策略。
- Gen 1–9 官方物种数据、Mega、妖精、物理/特殊分家及现代战斗实现保留；Z、Dynamax、Tera 在游戏激活判定中关闭，可通过项目配置重新开启。
- 当前无阻塞问题。Release 存在上游原有链接/LTO/Mystery Gift 警告，保留日志，本次不改正式游戏内容；实体 GBA 未实机测试。
- 用户按物理 Escape 停止窗口自动化后，已停止窗口控制，仅完成文件整理和日志记录。
- 原始剧情与地图均未改动。工程 Git、文档和工具入口已完成。
## 后续记录模板

日期 / 分支 / 提交：

修改目的：

受影响的系统和文件：

配置、存档兼容性与迁移：

验证方法与结果（编译、模拟器、游戏路径、必要的回归测试）：

已知问题和后续行动：

## 2026-10-06 — 开局赠蛋、进口限购、中文调查

- 仅修改未白镇科技 NPC、古辰镇宣传 NPC/商店；没有修改101/103及后续地图或正式组织剧情。
- 增加普通拉鲁拉丝蛋礼物：初始宝可梦之后开放，特攻IV31，其他随机参数沿用上游CreateEgg；满队伍重试；永久Flag0x20防重复。
- 保留赠疗伤药事件，增加普通海外企业/进口货背景介绍。
- 增加地图/商品/购买Flag表，古辰镇高级球正常收费且每档一颗；数量限制1，成功交付扣钱后设置永久Flag0x21，后续售罄。没有更改商品基础数据或存档尺寸。
- 禁止自动GUI：默认构建不启动ROM，--run拒绝，Windows Test变为Build，Run/Map/Code由allowGui=false阻止，VSCode默认任务仅构建。
- make常规和release均成功；本机C桩测试实际gift/table模块、Flag唯一性、18行文本宽度通过。未运行任何模拟器或游戏，实际游戏验证留给用户。
- 中文仅调查：固定社区汉化master e8671a6，确认包含官方1.17.1基线，核对中文字体、专用双字节charmap、打印与测宽、菜单及数据样本。未合并汉化或替换文本；需隔离分支编译及中文回归后才决定接入。
- 详细边界和人工验收清单：OPENING_IMPLEMENTATION.md；中文方案、来源与未验证项：CHINESE_SUPPORT_RESEARCH.md。

## 2026-10-06 — 102号道路普通训练家与橙华水边礼物

- 根据原地图/脚本准确定位水边NPC LOCALID_PETALBURG_BOY (8,22)，保留原倒影文本与恢复朝向流程。
- Route102追加Youngster EVAN (16,7)，普通单打Zigzagoon Lv.4 + Poochyena Lv.4；追加ID855，保持原MAX864及所有已有ID。击败Flag0x857仍在预留区。
- 战后Full Heal×1成功后设置FLAG_RECEIVED_ROUTE102_FULL_HEAL=0x23；独立领取状态保证满包重试不需重复战斗。
- 橙华追加原生物种地图雷伊布(9,22)，仅playmoncry/waitmoncry互动；水边NPC给予Water Stone×1，成功才设置FLAG_RECEIVED_PETALBURG_WATER_STONE=0x22。没有修改物种/道具/跟随系统。
- 两个新增Flag均经全项目UNUSED检索及数值唯一性检查；存档尺寸及系统Flag布局不变，上一批0x20/0x21保持。
- 常规/Release构建成功，32MiB ROM；地图原事件保留、地面和通路连通、赠礼失败分支、原倒影和32行文本宽度静态检查通过。修正trainer.party注释为其预处理器兼容的块注释。
- 本轮只编辑、编译及静态检查，未启动任何GUI、ROM、模拟器或本机游戏测试程序。运行时验证留给用户。
- 详细说明和人工验证：ROUTE102_PETALBURG_IMPLEMENTATION.md。中文调查未继续，橙华之后未扩写。

## 2026-10-06 — 简体中文底座迁移完成

- 先再次确认英文常规/Release 构建成功，将全部开局工作提交 checkpoint `e468929dec95196ffc7b3bfcd7d8aac25f573be7`；建立 `pre-chinese-base-migration` tag 和 `backup/pre-chinese-base-migration` branch，保存英文 ROM/哈希。
- 对中文仓库固定 commit `e8671a6d...` 进行 ancestry/源树/语义 diff，确认其实际为 1.17.2 未发布周期，含官方 1.17.1 祖先与长期中文提交；采用方案 A，保留本项目 1.17.1 主体。
- 引入中文字体/charmap/打印器/测宽/UI/翻译；地图只替换文本，训练家只替换名字；未开启跟随/HGSS 图鉴。记录逐文件 manifest，修复 5 个中文结束符、重排 635 个超宽汇编文本块。
- 所有原创文本转自然中文，EVAN 显示名改为埃文；四 Flag 0x20–0x23、送蛋特攻31、限购支付及满包重试保持。
- 恢复中文来源夹带的招式/道具规则与世代分支：82,698 项非文本数据字段与英文检查点一致。恢复 16 个与中文无关的动画/脚印/道具图标及 Z 禁用入口，并纳入保持检查；增加玩家名/昵称完整双字节截断，不扩大任何存档字段；中文命名输入法未实现，键盘仍使用字母。
- VS Code UTF-8 与 Poryscript 中文 font_config 配置完成；format() 不能自动切中文长句，原创文本必须明确断行。
- 普通常规和 Release 再次构建成功；字库覆盖、10651 个中文汇编文本块、名称字节预算、真实编译探针、本机字符串/赠礼边界、Flag 唯一性、事件流程/坐标/限购静态检查通过。保留上游 warning，没有改无关系统。
- `scripts/build.sh` 编译后自动执行全部检查，仅复制 ROM；没有运行模拟器、GBA ROM、make check 或任何 GUI。完整边界、人工验收与恢复方案见 CHINESE_BASE_MIGRATION.md。

## 2026-10-06 — PART1：104号道路至武斗镇

- 中文底座基线构建及全部既有检查通过后建立pre-part1-implementation（a1ddc7b0），在project/part1实施；上游固定1.17.1，原四开局Flag/地图/事件保持。
- 新增104旅行训练家、森林观察者/刺尾虫支线、花店额外每日树果、卡那兹老师与日问答、得文/矿工/地图宝可梦、小皮环境、港口限购潜水球/贝壳支线、洞穴探索与大吾彩蛋。没有凯那新剧情或组织介绍。
- 复用现代重要道具ExpShare+独立开关：默认ON，确认后才切换；参战各100%、有效后台各50%、蛋/濒死0；OFF传统分摊，无等级上限/惩罚。提取纯算术和原RTC日题为src/part1.c，共享赠礼脚本data/scripts/part1.inc。
- 新增永久0x24–0x2E及每日0x923–0x925，均来自未用槽，没有永久VAR或扩大存档。追加Trainer856，保持MAX864。所有新礼物成功才设Flag、失败可补领。
- 卡绿咕妞妞80/可可多拉10/铁哑铃10（新增8–10级）；四层石之洞窟无黑暗，沙瓦郎5/大嘴娃10/大岩蛇5/朝北鼻5，10–12级。改两馆主初次3只队伍，逐项当前招式合法性检查，原再战/徽章/TM和谜题保持。
- 增加真实C算术/蛋濒死过滤、事件指令分支、坐标/连通/对象容量/遭遇槽/原主线指令检查；检查发现并修复咕妞妞与两采集点挡路位置。钢翼和闪光背包满分支补领完善。
- 常规与Release完整构建命令均返回0、四套检查全通过；32MiB产物及SHA256记录在本批实现文档和logs/part1-verification.json。始终未运行模拟器、ROM、make check或GUI；人工测试项目见PART1_RUSTBORO_DEWFORD_IMPLEMENTATION.md。

## 2026-10-06 — PART2：凯那至紫堇及Route116回填

- 保留PART1提交cd07d4043e，建立pre-part2-implementation，在project/part2实施。读取原工程/文档/Flag/限购机制后确认原墨镜NPC为Route116东侧(74,13)，旁边普通NPC赠Scyther18，仅攻击IV31，创建前满队检查、加入成功后设置Flag和图鉴。
- 海之家额外Mystic Water、凯那市场原价限购Quick Ball/格斗家Focus Punch、平安符重要道具、长翅鸥支线/Great Ball3、原博物馆展板与Heart Scale3；满包保留领取资格。平安符仅状态0→1，未来基地剧情未做。
- 110新增Super Potion/Ether/隐藏Rare Candy，第一机关原奖励之外另加糖果及入口补领盒；劲敌六分支4只19/19/20/22，保留原探宝器。自行车新增免费切换提示。
- 复用原Summary数值IV/EV页面A切换，EV合计/510并恢复原经验面板；紫堇教程/磁铁原价限购/老人咩利羊/Mawile换Vulpix18“小焰”、满充18/17、铁旋21/21/23/24，按实际Gen9学习表替换不合法参考招式。
- 原LinkingCord796保留ID改名进化石，29源物种/30通讯进化目标统一直接道具，无原持物/交换物种要求；Clamperl双分支原生是/否选择+B取消，临时目标不写存档，原其他进化/Mega保留。本批不投放稳定进化石来源。
- 新Flag0x2F–0x3A及隐藏槽0x264、永久VAR0x404E、重要道具874；从未用槽命名，未增加存档或重排旧ID。沿用原通用限购表，不重写付款/容量机制。
- 坐标检查发现凯那女性初始位置造成视野对象容量回归，改为中心旁(8,20)，维持原NPC/通路；中文、旧开局和PART1检查保留窄范围新功能例外，PART2独立验证实际C生成/遇敌/进化循环/六项IV/EV及总计、真实脚本满包/补领/重复、地图连通/视线/容量和原剧情指令。
- 构建证据、完整38项报告与必须人工验收清单见PART2_SLATEPORT_MAUVILLE_IMPLEMENTATION.md。全程终端，不运行模拟器/ROM/make check/GUI；无新后续区域剧情。

- 最终普通及Release一键静默工作流返回0；五套检查通过，Windows最新32MiB副本及GBA头校验有效；SHA256及日志见实施报告，人工运行时验收尚未执行。

## 2026-10-06 — PART3：绿荫至釜炎第四徽章

- 从PART2完整检查点53e4aef建立project/part3，固定Expansion1.17.1和当前简体中文底座，全程终端；保留前三批源码，不开始第四徽章后的主线。
- 117培育说明/宝宝队/正负双打/安抚铃、绿荫满充家/听声老人/帐篷三胜额外PP Up及青年、卡绿开通后的两处旧NPC状态、111野餐/沙漠提示与活力块、112登山客/石头/缆车状态。
- 热焰火系生态、火之石/木炭/热气调查、原怪力支路TM和灼热岩窟炎帝40。原地图仅1入口图块替换，原2warp和原巨石保持；新小图/布局仅追加。传奇战前保存WAITING覆盖whiteout，捕获永久消失，未捕获待新殿堂恢复，不原地无限生成。战败白屏时提示在下一次回洞窟显示。
- 113画家/晃晃斑/扫灰NPC、原玻璃交易新增1500灰炽热岩石；秋叶研究/星星碎片/首次成功免费回忆/限购黑暗球；114共存生态/钓鱼/兰奈高级球3/向尾喵/化石提示。满包奖励均不吞，免费取消不消耗，兑换满包保待交付。
- 流星瀑布原陨石/索蓝主线和原月之石/后期宝贝龙区域保持，只增强双方目标对白、环境和一次星星沙。烟囱复用原4精灵对象/增加女新人胖丁20六31/胜后让路/赤焰松后追赶离场、旅游和仙贝；凹凸生态/柔软沙子/原14坡道清理后可步行回访；釜炎免费温泉/类型对白/原小果然蛋/原价仙贝/雪童子离场/亚莎排练及初战。
- 验证当前Gen9招式支持，具体将光代Meditate→Work Up、大嘴蝠Wing Attack→Aerial Ace、熔岩虫Flame Burst→Incinerate、煤炭龟Mist→Curse；保留设计职责与稳定原生招式表。原槽权重下火系概率采用14/10/5/5（熔岩虫/煤炭龟/鸭嘴宝宝/戴鲁比）。
- 新永久23、隐藏4Flags及未用VAR4083，不扩save；trainer857–860/MAX864。旧验证仅加入明确本批地图、六队原训练家和四遭遇表例外，其余严格保持；真实脚本VM和生产C状态机/地图可达/容量/原主线保持等检查进入一键构建。
- 完整54项报告、构建证据、人工验收列表见PART3_VERDANTURF_LAVARIDGE_IMPLEMENTATION.md。当前运行时验收待人工；没有启动GUI、模拟器、GBA ROM或make check。

- PART3最终交付：普通/Release一键工作流返回0，全部10套无界面检查PASS；32 MiB ROM/GBA头与Windows副本一致。完成标签part3-verdanturf-lavaridge；实机/模拟器运行时验收仍待人工。没有运行GUI或ROM。

## 2026-10-07 — PART4 实施完成

Codex按用户定稿实施至第六徽章与明确回填。normal/release及12套无界面检查PASS，未运行ROM。当前分支project/part4，保留1.17.1存档/引擎结构，复用限购表扩2单位与传说恢复；完整事实见docs/ai-handoff/PROJECT_STATE.md和PART4_PETALBURG_FORTREE_IMPLEMENTATION.md，人工验收与正式美术待完成。旧章节的分支/范围为历史，不能覆盖当前handoff。

## 2026-10-07 — Codex PART5.5

PART5追加世界密度/支线/Mega与钥匙钩子；主线仍止七馆、设计稿仍DRAFT。normal/release/15套CLI检查PASS，游戏内未测试。完整变更、分配、风险与人工清单见 PART5_5_IMPLEMENTATION.md 与四AI handoff，验证见 docs/project/part55-verification.json。没有启动GUI/模拟器/ROM。

## 2026-10-07 — Codex：早期游玩修复 / 授权运行验证

- 复现捕获图鉴页二次释放崩溃，修正Pokédex释放后的悬空指针；关闭KO额外动画，水跃鱼系升级表不再自动碎岩，首次跑鞋场景提醒私人蛋，哈奇/皮皮绕过PART1封路石头。
- 原Flag/VAR/ID/save结构不变；旧检查采用严格差异适配，新增19组playability静态检查，normal/release18套全部PASS。
- 用户本轮明确允许ROM/模拟器；未开GUI，以隔离mGBA核心复现旧失败、新版normal8/release7用例PASS。normal完整救援逐帧避石、事件状态正确；release救援夹具LTO helper缺失SKIP，不冒称运行验证。
- 修复前生成的武斗普通.sav在两种新ROM续档PASS，真实个人存档未拿到；现有Windows .sav原始hash保持、旧ROM/source备份在artifacts/bugfix-2026-10-07/before。既有碎岩不自动改写。
- 美术保持暂停，Canon未改；报告 BUGFIX_PLAYABILITY_2026-10-07.md，运行证据 artifacts/bugfix-2026-10-07/runtime/。本轮测试权限不解除长期默认禁止GUI/ROM规则。

## 2026-10-07 — Codex：手机MyBoy武斗恢复档

按用户请求重建刚到武斗镇普通.sav，原生保存并校验；男主PLAYER/岩石徽章1/沼跃鱼18无碎岩/蛇纹熊11/私人Ralts蛋SpA31，保留藤树和送信等后续。现有修复ROM与同名save打包；native检查和release5项续档/捕获PASS，手机导入未验证。未修原个人档、未改游戏源码/Canon/ROM，工具只增RAM指针命令。事实与交付见DEWFORD_RECOVERY_2026-10-07.md，美术保持暂停。

## 2026-10-10 / Codex：普通 Windows 工程入口

唯一权威源码/Git/美术/文档迁移到 `D:\Pokemon gba\project`；WSL 仅单向同步编译缓存。Build/Release 使用 `scripts/windows/dev.ps1`，禁止自动 GUI/ROM。保留所有未提交修复与资产，迁移不改游戏源码；验证见 WINDOWS_SOURCE_MIGRATION_2026-10-10.md。
