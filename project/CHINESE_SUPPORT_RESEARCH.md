# 简体中文底座调查（2026-10-06，仅调查）

**当前状态（2026-10-06 中文迁移后）**：下文英文/未汉化说明属于历史实施记录。现有事件结构、坐标、四 Flag 和奖励逻辑保持，显示文本已转简体中文；EVAN 显示名为“埃文”。当前 authoritative 迁移记录为 CHINESE_BASE_MIGRATION.md，仍禁止启动任何 GUI/模拟器/ROM。
## 结论

现在适合确定中文技术底座，并在大量原创剧情前做一次隔离的中文支持试接入。本轮没有合并汉化分支、没有导入字体、没有替换游戏文本。生产工程仍是英文 RHH 1.17.1。

目前最值得复用的是社区 `rh-hideout-chinese/pokeemerald-expansion` 的实现，而不是旧商业 ROM 字库补丁。它是官方项目的社区 fork，并非 RHH 官方中文发行版。建议保持本项目的 RHH 上游和固定版本，在隔离分支中分阶段审查/移植其中文字体、编码和渲染支持，再逐模块导入译文；不要直接覆盖工作树或改用它的 upcoming。

## 已核对的版本证据

- 本项目固定基线：`bb1093a7c72d3961d9a37d8e02ad2abc2c866682`，expansion/1.17.1。
- 中文 master 当前固定提交：`e8671a6d9d5f645ff60468cf1aac03c8c0897eb7`；2026-09-30 推送，提交为合并 RHH master，其近期历史含 `Expansion 1.17.1 Release (#10851)`。
- GitHub compare 实测相对本项目官方基线 ahead 526 / behind 0，说明包含该基线的提交历史，兼容起点明显好于旧版实现。526 是提交数，不是文件数；compare 文件列表最多300条，不能当作完整改动审计。
- 来源：[社区仓库](https://github.com/rh-hideout-chinese/pokeemerald-expansion)、[固定合并提交](https://github.com/rh-hideout-chinese/pokeemerald-expansion/commit/e8671a6d9d5f645ff60468cf1aac03c8c0897eb7)、[版本比较](https://github.com/rh-hideout-chinese/pokeemerald-expansion/compare/bb1093a7c72d3961d9a37d8e02ad2abc2c866682...e8671a6d9d5f645ff60468cf1aac03c8c0897eb7)。证据副本在 Windows `research/chinese`、`logs/chinese-compare.json`、`logs/chinese-tree.json`，仅供研究。

不能据此承诺“一键补丁直接兼容”：还未对中文分支独立编译、审计全部差异，未实测 Poryscript 与中文宽度、各种菜单和存档名字。

## 当前工程与可复用实现

| 范围 | 现状与调查结果 |
| --- | --- |
| 中文字体 | 当前生产工程未接入中文。候选的 `graphics/fonts/chinese_normal.png` / `chinese_small.png` 由 `src/chinese_text.c` 加载；大字高15宽12、小字高13通常宽10，标点另有宽度。仍是 GBA 点阵渲染。 |
| 编码/charmap | 候选 charmap 把中文映射成专用双字节值，部分标点单字节；不是把 UTF-8 原样放进 ROM，也不是简单改成 GBK。首字节范围0x01–0x1E，排除0x06/0x1B，末字节<=0xF6；必须连同字体和识别函数移植。 |
| 对话渲染 | 候选 text.c 在打印字符和测量字符串宽度路径调用 IsChineseChar / DecompressGlyph_Chinese / GetChineseFontWidthFunc；日文和盲文分支排除在中文识别之外。只改 charmap 无法工作。 |
| 菜单 | 候选 strings.c 已有中文购买等菜单文本；宽度/窗口布局必须一起核对，通用打印支持不代表所有窄窗口自然合适。 |
| 物种/技能/道具/特性 | 实际查看 species_info/gen_3_families.h、moves_info.h、items.h、abilities.h，看到木守宫、喷射火焰、高级球、茂盛等中文数据；README 声明覆盖原版及扩展相关数据。本轮没有逐个校对所有Gen1–9条目。 |
| 地图名 | README 声明地点名称已重译；需后续逐项核对 mapsec 名称、地图弹出标签与区域地图窄窗。本轮不能当作完整覆盖验收。 |
| 图鉴 | species_info/gen_3_families.h 的 categoryName 和 description 已有中文；需后续校验扩展图鉴所有页面、形态与动态描述。 |
| 换行/宽度 | 大字12px意味着208px纯汉字行通常最多17字，变量、标点、提示箭头会继续占宽，不能统一按17字硬切。需保持原控制码/分页，并为 Poryscript 自定义字体配置和静态检查建立中文度量。候选树中未找到现成 font_config.json/Poryscript 集成，因此本项目自动换行兼容性仍未验证。 |

源码证据：[字库与宽度](https://github.com/rh-hideout-chinese/pokeemerald-expansion/blob/e8671a6d9d5f645ff60468cf1aac03c8c0897eb7/src/chinese_text.c)、[打印与字符串测宽](https://github.com/rh-hideout-chinese/pokeemerald-expansion/blob/e8671a6d9d5f645ff60468cf1aac03c8c0897eb7/src/text.c)、[charmap](https://github.com/rh-hideout-chinese/pokeemerald-expansion/blob/e8671a6d9d5f645ff60468cf1aac03c8c0897eb7/charmap.txt)、[物种/图鉴样本](https://github.com/rh-hideout-chinese/pokeemerald-expansion/blob/e8671a6d9d5f645ff60468cf1aac03c8c0897eb7/src/data/pokemon/species_info/gen_3_families.h)。

另一个 `xxyzx/pokeemerald-expansion` README 标注1.11.1，作为译文参考可以，直接作为当前1.17.1底座不如上述候选稳妥：[旧实现](https://github.com/xxyzx/pokeemerald-expansion)。未找到比上述版本证据更强、经过本项目验证的官方中文补丁。

## 五个问题的答复

1. **现在接入是否合适：**合适，现在原创文本少、改动集中，最容易建立字体、编码、换行和命名规范；建议先在隔离分支试接入并验收，再决定生产合并。此处是建议，不是本轮执行授权。
2. **拖后期的返工：**NPC分页和变量宽度、菜单窗口、物种/技能/道具名长度、文本图片、图鉴长文、脚本生成器配置会重复调整；还会与更多原创脚本和上游更新形成合并冲突。存档昵称/玩家名必须区分字节长度与可见字数，不能让双字节被截断或误判终止。
3. **最稳妥方案：**继续以官方1.17.1为主线，固定上述中文候选提交；审查核心编码/字体/渲染/字符串处理和控制码；先少量菜单、一个NPC和物种/道具样本，建立中文像素宽度测试及构建，然后逐模块本地化。已有剧情 Flag、送蛋和限购逻辑保持独立。
4. **现成实现：**有，候选包含字体、charmap、渲染和大量数据/剧情译文且包含1.17.1基线；可以显著减少从零造轮子的工作。但尚不能称为本项目实测通过的直接替换底座，其字库与译文来源/许可及署名要求需在发布前逐项记录。
5. **是否影响 Expansion 功能：**理论上文本本地化不应删除妖精、物特分家、Mega、新世代机制；候选确实继续合并Expansion。不过公共打印/字符串测宽也服务现代战斗和图鉴，名称数组和文本图片会影响菜单布局与ROM容量。需要验收Mega相关提示、现代技能/道具、形态/图鉴/储存菜单、中文昵称/读档以及当前关闭的Z/极巨/太晶配置。保留实现代码不等于这些功能已通过中文回归。

当前常规链接ROM约25.51MiB，Release约25.62MiB，距离32MiB上限约6.38MiB；这是加入字库前的空间估算，不是汉化后的容量保证。现有中英文候选 POKEMON_NAME_LENGTH=12、PLAYER_NAME_LENGTH=7 相同，但多字节姓名的输入、截断和保存仍需单独验收。

## 后续验收门槛（未执行）

隔离编译、字符/控制码及缓冲区检查、中文Poryscript生成测试、像素宽度检查、ROM/RAM占用对比完成后，由用户方便时手动使用mGBA确认对话/菜单/图鉴/战斗/名字输入和存档。没有这些结果，不将候选声明为本项目稳定中文底座。
