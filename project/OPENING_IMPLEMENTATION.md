# 开局内容实现记录（2026-10-06）

**当前维护指引**：当前分支project/part2。四个开局Flag/地图/奖励逻辑保持；通用限购表当前覆盖古辰高级球、武斗潜水球、凯那先机球、紫堇磁铁。后续实施与38项报告见 PART2_SLATEPORT_MAUVILLE_IMPLEMENTATION.md；下文为历史记录。

**当前状态（2026-10-06 中文迁移后）**：下文英文/未汉化说明属于历史实施记录。现有事件结构、坐标、四 Flag 和奖励逻辑保持，显示文本已转简体中文；EVAN 显示名为“埃文”。当前 authoritative 迁移记录为 CHINESE_BASE_MIGRATION.md，仍禁止启动任何 GUI/模拟器/ROM。
本次权威工程仍为 RHH expansion/1.17.1；没有切换底座，没有汉化，没有扩写后续主线。所有操作均在终端进行，未启动 GUI、模拟器或 ROM。

## 文件及机制

- `data/maps/LittlerootTown/scripts.inc`：科技胖子第一次符合条件的交互赠蛋，领取前/领取后保留原科技台词；当前沿用英文 charmap，新增文本按两行、208 像素分页。
- `src/project_gifts.c`、`include/project_gifts.h`、`data/specials.inc`：新增 special `GiveLittlerootRaltsEgg`，追加在 special 表末尾，不改变已有索引。
- `include/constants/flags.h`：原未使用永久槽 0x20 / 0x21 分别命名为 `FLAG_RECEIVED_LITTLEROOT_RALTS_EGG` / `FLAG_BOUGHT_OLDALE_IMPORT_ULTRA_BALL`。移除原 UNUSED 名称，没有增加 FLAGS_COUNT 或改变存档结构。没有新增永久 VAR。
- `data/maps/OldaleTown/scripts.inc`：保留宣传 NPC 赠 Potion、背包满和原移动流程；第一次成功赠药及后续交互追加普通海外企业/进口货介绍。没有组织、人名或阴谋提示。
- `data/maps/OldaleTown_Mart/scripts.inc`：两份原商品表各增加 Ultra Ball，原普通商品不变。
- `src/limited_shop.c`、`include/limited_shop.h`、`src/shop.c`：可复用按地图和商品查询的购买 Flag 表，使用原商店价格和售罄文本。

## 蛋

要求 `FLAG_SYS_POKEMON_GET` 已设置，避免尚未选择初始宝可梦时出现只有蛋的队伍。原救助/选初始宝可梦事件锁定玩家，在该流程结束后才能回镇交互。

先检查领取 Flag 和队伍空间，再调用上游 `CreateEgg(&egg, SPECIES_RALTS, FALSE)`。FALSE 表示不使用温泉蛋特殊地点；不改写原蛋等级、孵化周期、蛋标记、初始技能、随机 IV 或随机 personality 的生成方式。仅用 `SetMonData(MON_DATA_SPATK_IV, 31)` 覆写特攻 IV，保留其他 IV、性格、性别、闪光正常随机规则。按上游正常校验和写入并复制到队伍。

只有 `GiveCapturedMonToPlayer` 返回 `MON_GIVEN_TO_PARTY` 时才设置领取 Flag 和成功结果；队伍满不创建、不发蛋、不消耗资格，留出空位后可重试。不会把这颗蛋自动送到 PC。

## 单件限购与复用

`GetLimitedShopPurchaseFlag(map, item)` 返回配置的永久 Flag；没有配置返回 0，仍为普通商品。当前唯一配置是古辰镇商店 + Ultra Ball。

- 未购时显示原价，数量最大 1；不足钱使用原失败处理。
- 最终交付入口再次校验未购且数量为 1，防止绕过数量界面。
- 背包成功添加后才进入原扣钱回调，扣钱后设置 Flag；取消和背包满不会消耗资格。
- 列表绘制与选择入口使用 Flag 显示/拒绝售罄，离店、读档、出售或用掉球不会重置。
- 其他地图的 Ultra Ball 不受本条限购规则影响。

以后新增限购货：在相应 `.inc` 商品表加入商品；在 flags.h 经过全局检索后命名一个尚未使用的永久 Flag；在 `sLimitedShopItems` 加 `{ MAP_..., ITEM_..., FLAG_... }`。无需再修改商店 C 逻辑。若同一地图有多个不同商店卖同一商品，当前地图/商品键会共享限购资格；需要独立库存时再扩展商店标识，当前没有这个需求。限购 TM 等仍遵守引擎原有重要道具和容量规则。

## 静默工作流

`bash scripts/build.sh` 和 VS Code 默认构建任务仅编译/导出。`--run` 直接报错退出；Windows Test 已改为 Build 别名；工作区 `allowGui=false` 拒绝 Run、Map、Code 启动入口。历史环境验收中启动过的程序不属于本次操作。

## 验证

`make -j4` 与 `make release -j4` 成功。常规 ROM 链接占用 26,749,056 B；Release 26,861,552 B；填充文件均 32 MiB。

`python3 scripts/tests/test-opening.py`：本机 C 编译器执行实际 gift/table 模块，使用引擎桩验证未得初始宝可梦、满队伍、交付失败、成功、重复领取、单项 IV 写入及地图/商品查询；两个 Flag 编号唯一；18 行新增对话均满足字体宽度和两行分页。此测试不是游戏运行或模拟器测试。

商店的数量限制、交付失败分支、扣款后 Flag、两处售罄判断经源码检查；脚本和 C 编译/链接成功。Route101、Route103 及后续地图未修改。Release 仍有历史验收记录中的上游 LTO/newlib/Mystery Gift 警告，本次无新增编译错误。

## 需要人工使用 mGBA 测试以下内容

1. 新档搬家、救博士、选初始宝可梦、101/103 对手战等原流程；选初始宝可梦前胖子仍说原台词。
2. 获得初始宝可梦后与胖子交谈领取蛋，提示/分页/音效正常；再次交互及保存读档不重复领取。
3. 满六只队伍拒绝领取、空出一格后能领取；孵化拉鲁拉丝后通过调试数据核实特攻 IV31、其余正常，观察正常孵化流程。
4. 宣传 NPC 首次赠药、背包满重试、后续文本均正常。
5. 商店保留原货物，高级球收费、数量无法超过1；取消/缺钱/背包满保留购买资格；成功后本次会话、离店重入、保存读档均售罄，使用/出售后仍售罄。

未做游戏内测试，因此不把以上项目标记为已验证。

## 本次 Git 文件清单

- `.vscode/tasks.json`
- `DEV_LOG.md`
- `PROJECT_BLUEPRINT.md`
- `data/maps/LittlerootTown/scripts.inc`
- `data/maps/OldaleTown/scripts.inc`
- `data/maps/OldaleTown_Mart/scripts.inc`
- `data/specials.inc`
- `dev-workspace/project-env.installed.json`
- `dev-workspace/project-env.template.json`
- `dev-workspace/scripts/dev.ps1`
- `include/constants/flags.h`
- `scripts/build.sh`
- `scripts/windows/dev.ps1`
- `src/shop.c`
- `CHINESE_SUPPORT_RESEARCH.md`
- `OPENING_IMPLEMENTATION.md`
- `include/limited_shop.h`
- `include/project_gifts.h`
- `scripts/tests/`
- `src/limited_shop.c`
- `src/project_gifts.c`

Windows 工作区另外更新 project-env.json、scripts/dev.ps1 及三份文档镜像；research/chinese 和 logs 仅是研究证据、编译与检查日志。权威源码没有提交到远程，当前本地改动保留供审阅。


## 2026-10-06 — 102号道路和橙华市追加登记

保留本页上一批实现。新增永久Flag：`FLAG_RECEIVED_PETALBURG_WATER_STONE=0x22`、`FLAG_RECEIVED_ROUTE102_FULL_HEAL=0x23`；分别替换经过全局检索的原UNUSED槽，成功发放后才设置，失败可重试。新训练家ID855使用原预留击败Flag0x857，不扩大MAX_TRAINERS_COUNT或改变存档尺寸。当前四个项目永久Flag0x20–0x23互不冲突。

详细文件、原NPC准确定位、坐标/碰撞核对、奖励状态设计、双构建结果及人工验收见`ROUTE102_PETALBURG_IMPLEMENTATION.md`。限购表、赠蛋代码与禁GUI流程保持不变。没有继续扩写橙华之后的剧情或接入中文。
