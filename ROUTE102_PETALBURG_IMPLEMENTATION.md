# 102号道路与橙华市事件实现（2026-10-06）

**当前状态（2026-10-06 中文迁移后）**：下文英文/未汉化说明属于历史实施记录。现有事件结构、坐标、四 Flag 和奖励逻辑保持，显示文本已转简体中文；EVAN 显示名为“埃文”。当前 authoritative 迁移记录为 CHINESE_BASE_MIGRATION.md，仍禁止启动任何 GUI/模拟器/ROM。
本批仅增加普通训练家和水边礼物。底座仍为RHH Expansion 1.17.1，文本仍为英文。保留上一批送蛋、进口商店、禁GUI工作流；没有继续制作橙华市之后的剧情，没有汉化或组织内容。本轮没有执行模拟器、ROM、GUI或本机游戏测试程序。

## 修改文件

- `data/maps/Route102/map.json`：追加普通年轻男性NPC。
- `data/maps/Route102/scripts.inc`：战前、战败、战后、领取失败和简短后续脚本/文本。
- `src/data/trainers.party`：EVAN的名字、职业、立绘和队伍集中定义；`src/data/trainers.h`由构建自动生成，不手工维护。
- `include/constants/opponents.h`：追加训练家ID855，TRAINERS_COUNT_EMERALD从855改为856，MAX仍为864，已有ID不变。
- `data/maps/PetalburgCity/map.json`：追加雷伊布对象。
- `data/maps/PetalburgCity/scripts.inc`：在原水边NPC脚本中调用送石子程序，追加雷伊布叫声互动。
- `include/constants/flags.h`：命名0x22/0x23两个原未使用永久槽。
- `scripts/tests/check-route102-petalburg.py`：仅静态检查，无游戏/模拟器/本机可执行测试调用。
- `OPENING_IMPLEMENTATION.md`、`PROJECT_BLUEPRINT.md`、`DEV_LOG.md`及本文：维护记录。Windows工作区有文档镜像。

## 102号道路普通训练家

对象编号10：`LOCALID_ROUTE102_NEW_WORKER`，坐标(16,7)，高度3，固定朝下，视线2格。位置属于从古辰镇由东向西前往橙华市的中后段，位于普通草地边缘。追加对象不改变原9个对象编号、视线参数、地图连接、标牌、拾取物和地形。碰撞/高度数据确认立足点可走，四邻域连通检查确认占用该格不会分隔相邻道路，且不落在原训练家固定方向视线格上。NPC自动靠近和动态视线仍需人工实测。

模型 `OBJ_EVENT_GFX_YOUNGSTER`，Trainer Class / Pic均Youngster，名字EVAN，无特殊身份信息。普通单打，AI仅Check Bad Move，无携带物/回复道具/特殊战斗机制。两只宝可梦：Zigzagoon Lv.4、Poochyena Lv.4，IV参照原道路训练家为0。附近Calvin为Lv.5，Allen为Lv.4/3，Tiana和Rick均Lv.4/4；新队伍没有超出本地等级曲线。

使用原`trainerbattle_single`和原战后回调模式。新训练家ID855占用引擎原先预留的击败槽`TRAINER_FLAGS_START + 855 = 0x857`，仍在原0x500–0x85F训练家区；不扩存档、不移动系统Flag。胜利后正常发奖金并记录击败状态。再次交互不重复战斗，奖励未领时继续尝试领取；已领时只说简短后续台词。没有二周目或消失事件。

战后给予`giveitem ITEM_FULL_HEAL, 1`。必须额外使用领取Flag：击败状态本身只有“已击败/未击败”，不能同时区分已胜利但背包满和奖励已领；复用它作为领取状态会导致吞奖励或重复战斗。因此采用一个独立永久Flag，成功后设置，失败不设置。

## 水边NPC与雷伊布

通过`PetalburgCity_EventScript_Boy`和`PetalburgCity_Text_WaterReflection`准确定位原NPC：`LOCALID_PETALBURG_BOY`，`OBJ_EVENT_GFX_BOY_1`，(8,22)。原五段水面倒影文本逐字保留；每次仍先说原文本，随后首次送石/满包重试/已领后续；结束仍执行原`Common_Movement_FaceOriginalDirection`。

雷伊布对象编号10：`LOCALID_PETALBURG_JOLTEON`，(9,22)，高度3，固定朝下，使用`OBJ_EVENT_GFX_SPECIES(JOLTEON)`。原生`GetObjectEventGraphicsInfo`会将物种标记交给`SpeciesToGraphicsInfo`；已有`graphics/pokemon/jolteon/overworld.png`、普通色板及帧表直接复用。没有启用跟随、增添新美术、修改物种数据或扩大跟随系统。

互动脚本：lock / faceplayer / waitse / `playmoncry SPECIES_JOLTEON, CRY_MODE_NORMAL` / waitmoncry / release / end。没有人类对白或文本窗口。

水边NPC解释朋友送给伊布两块进化石、选雷之石后成为雷伊布、闲置水之石可送玩家；原`giveitem ITEM_WATER_STONE, 1`处理正常获得提示，成功才设置领取Flag。之后追加精力充沛、选择雷之石很合适的台词。

## 永久Flag登记

| 名称 | 编号 | 作用 |
| --- | --- | --- |
| FLAG_RECEIVED_LITTLEROOT_RALTS_EGG | 0x20 | 上一批送蛋，保留 |
| FLAG_BOUGHT_OLDALE_IMPORT_ULTRA_BALL | 0x21 | 上一批进口限购，保留 |
| FLAG_RECEIVED_PETALBURG_WATER_STONE | 0x22 | 本批水之石成功领取 |
| FLAG_RECEIVED_ROUTE102_FULL_HEAL | 0x23 | 本批战后Full Heal成功领取 |

新增前全项目搜索两个UNUSED名称，只存在于定义，没有事件使用；再检查数值定义唯一。下一槽需重新检索，不能把0x24以后所有编号当作默认空闲。没有新增永久VAR或special。两个地图LOCALID均由map.json生成常量。

## 背包满和领取顺序

两项奖励均为一个物品，先giveitem，再检查VAR_RESULT失败分支，再setflag。原`Std_ObtainItem`调用additem、保留结果并走原获得/无空间消息；失败不会设置永久Flag。失败后显示保留奖励提示，恢复交互；空出该物品袋空间后重试。水边脚本无论成功或失败都返回原脚本并恢复NPC方向；训练家胜利状态保留，不为重试清除击败Flag。

## 静态与构建验证

- `make -j4`成功：常规链接ROM26,750,464 B，EWRAM226,416 B，IWRAM28,376 B。
- `make release -j4`成功：Release链接ROM26,862,888 B。两个输出均按原工具填充至32MiB。
- 原有上游Release/newlib/LTO/Mystery Gift警告继续保留，本次无编译错误。
- 静态检查通过：四个项目Flag唯一、原训练家ID保留、预留容量不变、地图原事件逐项不变、坐标不重叠、普通地面/高度正确、邻接道路仍连通、原视线格无新对象占位、原倒影文本相同、原恢复朝向保留、赠礼成功/失败分支、纯叫声互动、32行新英文对话两行分页及<=208px。
- 可重跑：`python3 scripts/tests/check-route102-petalburg.py`。当前静态回归使用本轮编辑前证据`D:\Pokemon gba\logs\route102-petalburg-before.json`，该文件不随Git分发；迁移电脑时请带上或建立新的审查基准。
- 构建日志：`logs/route102-petalburg-build.log`、`logs/route102-petalburg-release.log`；静态结果：`logs/route102-petalburg-checks.log`。这些均在Windows工作区。

## 需要人工使用mGBA测试以下内容

1. 正常从古辰镇走到橙华市，NPC位置自然且可绕行，原训练家视线、原开局与满充捕捉教学流程正常；新增NPC视线接战和主动交谈都正常。
2. 战败于EVAN后复活、再次挑战；胜利后的脸朝向、音效、英文分页、奖金与Full Heal获得提示；重复交互不重打。
3. 道具袋满时战胜EVAN：奖励未领、空出空间可领取且无需重打；保存读档、用掉/出售Full Heal均不重复赠送。
4. 水边NPC仍先说原倒影台词，雷伊布外观、位置及朝向正常，互动只响雷伊布叫声，无人类对白。
5. 水之石正常领取、满道具袋失败后重试、存读档防重复、使用/出售后不再赠送；NPC原方向恢复正常。
6. 上一批拉鲁拉丝蛋与古辰镇进口高级球仍正常。

本轮没有游戏内验证，因此以上未标为通过。
