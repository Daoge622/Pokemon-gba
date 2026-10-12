# 简体中文底座迁移报告

日期：2026-10-06。范围：中文底座移植、现有原创内容中文化和终端验证。未新增剧情、地图或后续主线；未启动 GUI、浏览器 GUI、模拟器或 ROM。当前开发分支为 `project/chinese-base`。这是已构建、已静态检查的中文工程，尚未进行游戏内视觉验收。

## 1. 原始项目具体基线

官方 RHH 仓库 `https://github.com/rh-hideout/pokeemerald-expansion`，固定 tag `expansion/1.17.1`，commit `bb1093a7c72d3961d9a37d8e02ad2abc2c866682`。原始工程包含此前两批开局事件和项目机制开关。权威源码 `/home/pokemon/projects/emerald-story`；Windows 可访问 `\\wsl.localhost\Ubuntu-24.04\home\pokemon\projects\emerald-story`。`D:\Pokemon gba\source` 是历史快照，不是当前开发工程。

## 2. 中文仓库具体基线

社区仓库 `https://github.com/rh-hideout-chinese/pokeemerald-expansion`，本次固定取样 commit `e8671a6d9d5f645ff60468cf1aac03c8c0897eb7`。实际源码版本宏为 **1.17.2、EXPANSION_TAGGED_RELEASE=FALSE**，不能当作官方 1.17.1 完全相同的稳定包。结论依据 Git 历史、版本头和逐文件 diff，未仅依赖 README。

## 3. 两者关系

中文仓库是长期维护的社区 fork，历史上反复合并官方更新，并包含大量中文提交。官方 1.17.1 commit 是中文取样 commit 的祖先；merge-base 为 `bb1093a7...`，比较结果为官方基线落后 526 个提交、领先 0 个提交。中文取样包含官方基线后的三个官方提交：`0f6d505b33`（开始 1.17.2 周期）、`c5f026363a`（1.17.1 release PR）和 `dfb0f84374`（玩家对象初始化修复）。以上仅说明血缘，不等于中文分支逐模块兼容。

## 4. 最终采用方案 A

保留当前官方 1.17.1 工程、存档定义、事件结构、项目开关和自定义系统；有选择地引入中文字体、编码、打印器、测宽、UI 与翻译资源。没有整体 merge/rebase 到中文 master，也没有升级官方基线。

## 5. 选择原因及实际处理

中文分支相对官方固定基线差异为 1001 个文件、59009 行增加、69701 行删除，且开启了跟随系统和 HGSS 图鉴。整体替换会混入版本、功能配置及战斗数据差异。移植清单记录于 `docs/project/chinese-import-manifest.json`：257 个核心/资源文件，655 个仅文本导入文件，88 个排除文件。地图汇编只替换同名文本块，`.party` 只替换名字；地图事件和队伍数据沿用本项目。

未引入跟随/HGSS 开关、1.17.2 版本宏、新构建/测试入口及玩家对象修复。另已恢复中文文件覆盖时的 Z 招式禁用入口，并新增其全部非文本 token 对比；极巨化和太晶化入口保持原文件。道具和招式表额外重建为本项目原始非文本字段及全部世代条件分支，仅保留中文名称/描述；另外恢复 16 个与中文无关的战斗动画、脚印和道具图标资源，保持原美术；中文不需要英文复数形式，既有复数字段使用相同中文名称。少量翻译描述沿用当前现代世代语义，未来切换较旧规则时需要同步审阅描述。

## 6. 备份与恢复点

- 英文 checkpoint commit：`e468929dec95196ffc7b3bfcd7d8aac25f573be7`。
- tag：`pre-chinese-base-migration`。
- branch：`backup/pre-chinese-base-migration`；`project/main` 也保留在英文 checkpoint。
- 中文开发 branch：`project/chinese-base`；完成提交后建立 `chinese-base-1.17.1` tag。
- 英文常规/Release ROM、哈希和事件基线：`D:\Pokemon gba\artifacts\pre-chinese-base-migration`。

需要回到英文底座时，先保存当前新增工作，再在源码目录执行 `git switch backup/pre-chinese-base-migration`。不要使用无备份的 reset/文件覆盖。重新构建对应分支，避免使用另一个分支生成的旧 ROM。本次没有推送远程，也没有修改全局 Git 身份。

## 7. 移植的核心模块与修改文件

| 模块 | 主要路径 | 处理 |
| --- | --- | --- |
| 编码 | `charmap.txt` | UTF-8 源码转换成原游戏字节及扩展双字节汉字 |
| 字库 | `graphics/fonts/chinese_normal.png`、`chinese_small.png`、既有 Latin 字库 | 普通/小字汉字和中文标点 |
| 打印/测宽 | `src/chinese_text.c`、`include/chinese_text.h`、`src/text.c`、`src/fonts.c` | 汉字识别、解压、宽度和打印器推进 |
| 名称安全 | `src/string_util.c` | 玩家名/昵称按原字节预算截断，保留完整汉字 |
| UI | `src/menu.c`、`item_menu.c`、`party_menu.c`、`pokemon_summary_screen.c`、`pokemon_storage_system.c`、`pokedex.c` 等 | 社区中文布局、字节缓冲和界面文本 |
| 全局/战斗文本 | `src/strings.c`、`src/battle_message.c`、`src/text_input_strings.c`、`data/text/` | 中文提示、战斗、背包等资源 |
| 名称和图鉴 | `src/data/pokemon/species_info/`、`moves_info.h`、`abilities.h`、`items.h`、`types_info.h` | Gen 1–9 名称、分类、图鉴与描述 |
| 地图文本 | `data/maps/*/scripts.inc`、`data/event_scripts.s`、`src/data/region_map/region_map_sections.json` | 原版地图/事件翻译、地图名称；不增加地图/事件 |
| 训练家 | `src/data/trainers.party` 等 | 名称翻译，ID/队伍保持 |
| 工具支持 | `.vscode/settings.json`、`tools/poryscript/font_config.json` | UTF-8、中文字体测宽和语言服务配置 |
| 验证/构建 | `scripts/tests/check-chinese.py`、既有两组开局检查、`scripts/build.sh` | 编译后自动中文与事件检查，成功后复制 ROM；不运行 |

社区字库/翻译归属其原作者；本项目继续保留上游许可证，固定来源和导入路径，不声称自行制作这些资源。完整路径清单在 manifest，原始审核证据在工作区 `logs/chinese-*audit.txt`、`chinese-tree-diff.txt`。

## 8. 是否可以直接输入中文

可以。NPC `.inc` 文本和 `.pory` 文本均直接用 UTF-8 简体中文。C 文本继续使用既有 `_()` / `COMPOUND_STRING()`，原标签、控制码和 `$` 结束符规则不变。原版编译链通过扩展 charmap 转换，不是把 UTF-8 字节直接塞入 ROM。

Poryscript 3.6.1 已使用 `1_chinese_rse` 默认字体和语言服务字体配置。**format() 依赖空格分词，不能自动拆开没有空格的长中文段落**。原创剧情必须明确写 `\n`、`\l`、`\p`，依据实际像素预算分页；不能把“源码支持中文”理解为自动排版。中文编译探针在 `scripts/tests/fixtures/chinese-probe.pory`，不绑定 NPC，不改变游戏内容。

示例：

```asm
Example_Text:
    .string "你好！\n"
    .string "祝你旅途愉快。$"
```

普通对话行检查预算 208 像素，汉字普通字体 12 像素；玩家变量预留 42 像素，常见字符串变量保守预留 120 像素。字体选择、提示箭头和不同窗口仍需实机视觉验收。

## 9. 字体支持范围

当前 charmap 含 **6771 个双字节映射字符**，并有单字节中文标点、数字、英文字母及控制码。两套汉字 PNG 均为 256×7088，折算各 7088 个字形槽；构建字库各 453632 字节。静态测试验证每个双字节映射都落在普通/小字字体实际索引范围内。普通汉字宽 12 像素，小字宽度按社区打印器使用。

这不是完整 Unicode 字体。未来剧情如使用罕见人名汉字，应先核查 charmap 和真实字形；缺字需要同时添加编码与字形，不能只改映射。字体覆盖检查确认编码/资源存在，不等于已肉眼审阅每个字形美观或笔画正确。

## 10. 原版文本汉化程度

已移植社区提供的原版地图对白、主线/支线文本资源、通用提示、战斗、菜单、背包、商店、图鉴、概要、队伍和 PC 等中文内容。10651 个含中文的汇编文本块已检查映射和保守行宽；635 个过宽文本块重新断行，5 个缺少结束符的文本块补齐 `$`。

这是广泛汉化资源的接入，**没有宣称原版每个可达界面 100% 完成视觉验收**。未逐项游玩全部原版事件；开发/调试字样、专有缩写和少量占位文本可能保留英文。

## 11. Expansion 新增内容汉化程度

Gen 1–9 种族名称、分类/图鉴文本以及现代招式、特性、道具名称和描述已引入。源码统计：873 条直接定义的道具名称全部含中文；935 条招式名称中 934 条含中文；320 条特性名称中 317 条含中文，其余含占位/符号等。上述为源码匹配统计，不能当作可见内容的最终完成率，也不包含所有宏展开条目。

82,698 项非文本道具、招式、特性、属性、Gen 1–9 种族字段与英文 checkpoint 一致。妖精、Mega、物理/特殊分家和现代机制仍使用原配置。Z/极巨化/太晶化继续由项目开关禁用，数据和实现保留。没有因汉化开启跟随或 HGSS 图鉴，也未删去扩展能力。

## 12. 原创内容保留及中文化

全部保留并转为自然简体中文。未白镇科技胖子私人赠蛋，不增加委托人身份或反派暗示；古辰镇赠疗伤药和普通海外贸易/进口货对白保留；102号道路青年显示名改为“埃文”，常量 ID 不变，仍为 Youngster，Zigzagoon Lv.4 / Poochyena Lv.4，原坐标 (16,7) 和事件结构不变，战后赠万能药；橙华水边倒影原对白保留，追加伊布两块进化石故事和水之石，雷伊布位置与原生 `playmoncry / waitmoncry` 保留，没有人类对白。

赠蛋仍走 `CreateEgg(... SPECIES_RALTS, FALSE)`，只覆写 `MON_DATA_SPATK_IV=31`，其他 IV/personality/性格/性别保持正常生成；队伍满不消耗资格。Full Heal/Water Stone 均只在 `giveitem` 成功后设 Flag，失败可重试。五张开局地图对象 JSON 和全部非文本事件指令与 checkpoint 一致。

## 13. 四个永久 Flag

| Flag | 数值 | 当前作用 |
| --- | --- | --- |
| `FLAG_RECEIVED_LITTLEROOT_RALTS_EGG` | `0x20` | 成功收下拉鲁拉丝蛋 |
| `FLAG_BOUGHT_OLDALE_IMPORT_ULTRA_BALL` | `0x21` | 成功购买进口高级球 |
| `FLAG_RECEIVED_PETALBURG_WATER_STONE` | `0x22` | 成功获得水之石 |
| `FLAG_RECEIVED_ROUTE102_FULL_HEAL` | `0x23` | 成功获得万能药 |

既有分配和唯一性检查通过，flags.h 与英文 checkpoint 完全相同。本次没有新增永久 Flag/Var，也没有改变 FLAGS_COUNT、训练家 ID/击败 Flag 或存档布局。埃文仍使用 trainer ID 855，击败状态和奖励状态分开处理。

## 14. 古辰镇限购机制

`src/limited_shop.c`、`include/limited_shop.h`、`src/shop.c` 的既有机制保留：按地图/道具查询限购表，一次最大购买 1 个；原价扣款；成功加入背包并走原支付回调后设购买 Flag；取消、钱不足、背包满均不设 Flag；再次访问售罄。两份原商店普通商品表保持，中文只改变显示文本。以后其他城镇增加表项和经核查的新 Flag 即可复用。

## 15. 常规构建

在 WSL 源码目录执行 `bash scripts/build.sh` 或 `make -j4`。前者编译后运行中文/开局检查并复制产物。构建成功；工作区 ROM：`D:\Pokemon gba\artifacts\current\pokeemerald.gba`，GBA 文件由 gbafix 正常补齐为 32 MiB。完整日志 `logs/chinese-final-build.log`。

## 16. Release 构建

执行 `bash scripts/build.sh --release` 或 `make release -j4`。构建成功；工作区 ROM：`D:\Pokemon gba\artifacts\current\pokeemerald-release.gba`。完整日志 `logs/chinese-final-release.log`。保留已有 newlib stubs/LTO/神秘礼物代码警告；没有为压掉上游 warning 改写无关系统。

Windows 已有 `Build-and-Test.cmd` / Test 和 VS Code 构建任务只编译及检查，绝不运行 ROM。`scripts/build.sh --run` 明确失败拒绝启动 GUI。没有调用 `make check` 或模拟器验收程序；本机测试只执行提取的字符串/赠礼函数与工具编译器，不执行 GBA 游戏。

## 17. 名称长度、验证边界及兼容风险

| 名称 | 原字节预算 | 中文含义/处理 |
| --- | --- | --- |
| 玩家名 | 7 字节 | 最多 3 个双字节汉字加 1 单字节字符；未扩大存档 |
| 宝可梦昵称 | 12 字节 | 最多 6 个双字节汉字；复制/裁剪避免半个汉字 |
| 训练家名 | 10 字节 | 通常最多 5 个汉字；856 条队伍文件名称检查通过，自定义“埃文”符合 |
| 招式名 | 16 字节 | 当前直接名称均通过字节预算检查 |
| 特性名 | 16 字节 | 同上 |
| 道具名 | 20 字节 | 同上，英文复数预算原样保留 |
| 种族名 | 种族数据名称 + 昵称复制预算 | 种族标签按数据/窗口显示，成为昵称时依原 12 字节完整截断 |
| 地图名 | 指针文本及窗口宽度 | 不是玩家存档中的可扩字段；沿用中文地图弹窗/区域地图测宽 |

`StringLength` 等底层仍以编码字节计数，UTF-8 编辑器字符数、游戏字节数和像素宽度是三件事。只对玩家名/昵称的边界复制做安全处理，未改变全局长度定义或存档 ABI。输入界面提示已中文化，但 **游戏内键盘仍是原字母键盘，没有拼音/汉字输入法**；现阶段可以中文源码/种族名显示及使用字母昵称，任意中文玩家命名不是已完成功能。

已完成检查：20 个核心/存档/配置文件逐字节保留；五张地图对象和非文本指令一致；82,698 项数据字段及招式/道具条件分支一致；字库索引、映射、名称字节预算、10651 个中文汇编块行宽；四 Flag 唯一性；赠礼失败/成功分支及限购支付顺序；实际 Poryscript→charmap→ARM 汇编的中英文、数字、标点、玩家/种族/道具变量、控制码、换行、分页、Yes/No 编译探针；提取真实函数的本机名称边界测试。

无法仅凭静态检查确认所有 UI 对齐、运行时变量长度、文本滚动、特殊控制码组合、联机语言标识和完整汉化美术效果。特别是 `IsStringJapanese` 仍沿用上游低字节启发式，记录混合、部分电视/对战设施的昵称语言推断可能把中文编码识别为日文；这些路径需要专项人工测试，不能承诺与日版或原版游戏联机兼容。旧英文存档结构未改，但旧昵称仍保留原字母，旧存档的每个 UI 场景未运行验证。未来更新 Expansion/中文来源必须重新逐模块审阅，不要直接覆盖。

## 18. 需要人工使用 mGBA 测试以下内容

1. 开始新游戏、继续旧档、保存/读档；中文/数字/英文混排、玩家变量、选择框、翻页提示和字体笔画。
2. 未白镇蛋：六只队伍领取失败后重试、成功一次、正常孵化拉鲁拉丝、特攻 IV31；旧档 Flag 状态不变。
3. 古辰镇赠疗伤药流程及中文进口货对白；高级球付费限购 1 个，取消、钱不足、背包满、再次入店售罄。
4. 102号道路埃文视线/靠近/战斗/败北分支、两个 Lv.4 队员；战后满包保留万能药资格、领取后不能重复；中文文本分页。
5. 橙华原倒影对白、雷伊布对象/叫声、赠水之石满包重试、成功一次、原 NPC 朝向恢复。
6. 战斗菜单/战斗变量、妖精相性、Mega（需合法获得手环/对应石的测试档）、现代招式/特性/道具；确认项目禁用的 Z/极巨化/太晶化仍不能激活。
7. 背包、商店、图鉴、宝可梦概要、队伍、PC、地图名称长文本；更长名称与小字体/窄窗口，不越界、不截断半个汉字。
8. 字母命名/重命名的输入、删除、确认、取消，以及已有中文默认种族名显示；不把当前键盘当作已支持中文输入法。

本报告没有声称完成上述游戏内测试。请在允许打开模拟器时由用户人工验证。
