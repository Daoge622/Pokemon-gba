# PART 2：凯那市至紫堇市实施与验收

日期：2026-10-06。官方底座仍为 RHH Expansion `expansion/1.17.1`，上游 `bb1093a7c72d3961d9a37d8e02ad2abc2c866682`。沿用当前简体中文底座、所有开局和 PART 1 内容。

实施前保存 `pre-part2-implementation`，对应 `cd07d4043ec9198282c27fc4953aaedf7d07ab9e`；开发分支 `project/part2`。权威源码 `/home/pokemon/projects/emerald-story`，Windows 入口 `D:\Pokemon gba`。不编辑入口中的旧 source 副本。

本批只编辑源码、终端构建与静态/本机 C 检查。没有运行任何 GBA ROM、模拟器、GUI、make check 或自动打开构建产物。原版117号道路、绿荫镇、烟囱山与水舰队基地未新增内容。

## 最终报告（按要求38项）

1. **修改文件**：完整清单见本文末尾。共享事件在 `data/scripts/part2.inc`，C 生成/分支辅助在 `src/part2.c`；机器可读分配/坐标/阵容/原始进化数据在 `docs/project/part2-manifest.json`。
2. **飞天螳螂NPC**：准确确认原墨镜角色为 Route116 的 `Route116_EventScript_GlassesMan`（74,13），未修改该角色。旁边新增普通 `OBJ_EVENT_GFX_MAN_1` 路人（76,14）。不新增委托人身份。
3. **领取Flag**：`FLAG_PART2_RECEIVED_SCYTHER = 0x2F`。成功加入队伍才设置；之后仅显示交付完成台词。
4. **Lv.18**：使用 `CreateMon(SPECIES_SCYTHER, PART2_SCYTHER_LEVEL, Random32(), OTID_STRUCT_PLAYER_ID)`，常量为18。沿用正常初始技能和创建机制。
5. **攻击31IV**：创建后仅覆写 `MON_DATA_ATK_IV = MAX_PER_STAT_IVS`，随后 `CalculateMonStats` 刷新实际属性。其余五项IV、personality/性格、性别、普通特性和闪光按原创建规则；正常登记见过/捕获图鉴。
6. **满队伍**：创建前检查原初始宝可梦领取状态、领取Flag和队伍数量。六只时不创建、不设置Flag、不自动送PC，提示空出位置后返回。实际成功返回 `MON_GIVEN_TO_PARTY` 才完成。
7. **鲤鱼王概率**：凯那市及109号道路老钓竿正常状态40%鲤鱼王、60%玛瑙水母，原5–10级不变。JSON本来已含这两种，本次仅按地图覆盖原70/30权重；中高级钓竿/其他地图/其他遇敌方式原样保留。原诱饵的换槽加成继续保留，使用诱饵时两槽约44/56；40%指无诱饵的正常钓鱼。
8. **海之家神秘水滴**：打败三名原训练家、原6瓶汽水成功领取后附赠1个；满包可从老板后续互动补领，不影响汽水购买。成功才设置0x30。
9. **先机球限购**：市场普通商人卖Quick Ball，按原道具价收费，一档1个，0x31记录。继续使用原通用地图/商品/Flag表，没有第二套商店引擎。
10. **气合拳**：凯那市市场边格斗家（11,34）赠 `ITEM_TM_FOCUS_PUNCH` 1个；0x32成功后设置，满包重试。原后续固定获取点位于Route115的道具球，已登记待后续批次替换；本批未改后续区域。
11. **平安符**：宝可梦中心旁女性（8,20）委托送给在水静市工作的男友；只实现获得道具，不揭露真实身份。`ITEM_PEACE_CHARM` 是重要道具、价格0、importance1、无法出售/丢弃、正常存档保存。占位图标沿用洁净之符。
12. **任务状态**：复用未用永久 `VAR_PART2_PEACE_CHARM_STATE = 0x404E`。0尚未接、1携带、2未来已交付、3未来完成；仅成功获得后执行0→1。不额外占用领取Flag、不制作基地男友/隐藏奖励/重逢。
13. **长翅鸥**：市场附近（8,34）固定地图物种互动只播放叫声，设置已找回0x33、移除原对象、显示主人旁（34,40）对象。重进地图通过临时Flag恢复正确状态。送货员（35,40）给超级球3，0x34成功后设置，满包重试。无捕获和队伍操作。
14. **博物馆展板**：复用三块原海洋小知识展板，分别说明海洋覆盖、迁徙环境和古老海陆变化；不点名传说宝可梦，也无新组织。原票价/水舰队战斗/库斯诺吉/水梧桐推进指令保留。
15. **心之鳞片**：原送达得文物品的博物馆结尾附赠3个，0x35；满包从一楼原工作人员补领。只在 `FLAG_DELIVERED_DEVON_GOODS` 后开放。
16. **110探索**：超级药1（31,72）、以太1（5,41）、隐藏神奇糖果1（34,28）。沿用正常地面/隐藏道具机制；保留全部原道具和地图地形；以太偏离主要东侧进城路线。
17. **机关屋**：原第一套机关和原神奇糖果照常；进度≥1后额外1个神奇糖果，0x38。首次出口追加赠礼，满包仍可从入口（3,7）奖品盒补领，不改变原延迟领奖机制或以后阶段。
18. **劲敌队伍**：小遥/小悠的六个Route110分支均4只，19/19/20/22，固定大王燕、第二阶段初始宝可梦为最后王牌。下面列出每个玩家初始选择的对应阵容和全部配招。IV12，无竞技持有物/EV训练，保持原Basic Trainer AI（高于附近只检查差招的普通训练家）。原探宝器奖励及离开动作保持。
19. **拉鲁拉丝检测**：原战后脚本调用原生 `checkspecies`，只检查拉鲁拉丝或奇鲁莉安，命中才追加情绪感知对白。没有蛋来源或角色关联。
20. **IV/EV实现**：开启原Expansion成熟Summary开关，保留原六属性读取/原页面结构；分别显示数值IV和数值EV，不使用等级评价。关闭Hyper Train显示31的替代显示，IV页面显示真实IV。
21. **切换按键**：能力页面按A，循环“能力→个体值→努力值→能力”；原页面方向键/L/R导航和其他页面A操作保持。教程同步说明A。
22. **EV总值**：努力值模式将原经验面板替换为“努力值总计”及 `GetMonEVCount(currentMon)/510`，包含全部六项实际EV。切回能力/IV后恢复经验和下级经验数字与标签。中文标签宽66≤88px；三位总计/510最长42≤48px。
23. **教程NPC**：紫堇普通男性（17,16），说明A切换与六项数字/努力值总计；不透露代码或实现细节。
24. **磁铁限购**：紫堇普通商人（11,16）按原价卖Magnet1，0x39；复用与先机球/此前高级球/潜水球同一机制。取消、缺钱、满包均不设置购买Flag。
25. **满充队伍**：拉鲁拉丝18+毒蔷薇17，IV12、无极端持物。新增训练/健康/成长对白后继续原叔叔与道馆外原剧情。
26. **咩利羊**：紫堇老人（28,14）与原项目已有物种地图咩利羊（29,14），老人讲晚上的小灯；咩利羊只 `playmoncry/waitmoncry`。无新跟随系统和奖励；可选电系队伍附加台词未做。
27. **大嘴娃换六尾**：紫堇最右侧靠水普通女性（34,16），追加 `INGAME_TRADE_PART2_VULPIX`，沿用原 `ingame_trade` 的确认/选队伍或PC/错种/取消/交换演出。完成才设置0x3A。
28. **六尾数据**：Lv18，昵称“小焰”，原训练家“晓晴”，普通能力槽0、合理非完美IV、正常18级初始技能。为原静态交易数据加可选level字段；原13个交易level0仍与提交宝可梦等级相同，不改存档结构。
29. **进化石文件**：原 `ITEM_LINKING_CORD=796` 保留ID并改正式中文名“进化石”；新代码通过 `ITEM_EVOLUTION_STONE` 别名使用，原进化道具效果、8000价格保留，图标采用现成浑圆之石占位。涉及items.h、物种进化表、pokemon.c、party_menu.c及part2辅助。
30. **替换范围**：实际查得29个原通讯源物种/形态，共30个目标；全部改为 `EVO_ITEM, ITEM_EVOLUTION_STONE`。包括携带物通讯、与特定物种交换、四种南瓜形态和阿罗拉隆隆石。完整映射见下表；丑丑鱼美丽度、飞天螳螂劈斧螳螂等其他方法保留。
31. **取消通讯条件**：当前全部Gen1–9物种进化表不再有EVO_TRADE行，也不再要求/消耗原携带物或交换对象；每次只使用进化石1个。移除同目标原金属膜等直接道具替代路径，统一到进化石。珍珠贝使用原是/否选择：是猎斑鱼、否樱花鱼、B取消不消耗；临时目标选择不写存档。普通其他进化与Mega配置保留。
32. **飞天螳螂兼容**：直接使用进化石→巨钳螳螂，不需金属膜、携带物、通讯或第二道具。PART2未安排进化石领取/售卖，稳定获取渠道留待后续，未给前期增加大量来源。
33. **铁旋阵容**：霹雳电球21、落雷兽21、三合一磁怪23、雷电兽24王牌；具体配招下表。仅雷电兽普通橙橙果，IV12，无气腰/极端EV，保留原两瓶超级药。根据当前Gen9学习表，将不合法音爆等替换，未给霹雳电球不合法电光一闪。原电道馆机关/徽章/电击波/推进权限不改。
34. **新增分配**：永久0x2F–0x3A共12个，再加原隐藏道具兼容未用槽0x264；永久VAR0x404E。均从原UNUSED槽命名，全局直接定义唯一；不扩大FLAGS_COUNT、训练家Flag区或存档。物品追加874，不重排旧ID。
35. **常规构建**：见下方最终构建证据与Windows日志；ARM GCC完整编译生成32MiB `.gba`。只构建，不运行。
36. **Release构建**：见下方最终构建证据；完整Release同样32MiB。保留底座已有警告，不把构建成功当成实机测试。
37. **静态/本机检查**：五套检查覆盖中文字体/编码/宽度/名称预算、原开局/102/橙华/PART1、Flag/VAR、地图地面/连通/原视线/对象容量/原推进指令、实际赠礼脚本满包/补领/重复、实际C生成边界、精确遇敌权重、当前学习表、30进化目标引擎循环、实际六属性读取和EV0/129/510。静态检查不能证明所有实际游戏场景无卡死，完整玩法验收见人工清单。
38. **必须人工mGBA验收**：见下文详细清单；本次没有执行游戏或自动打开模拟器。

## 原始分配与坐标

| Flag | 十六进制 | 用途 |
|---|---|---|
| `FLAG_PART2_RECEIVED_SCYTHER` | `0x2F` | RECEIVED_SCYTHER |
| `FLAG_PART2_RECEIVED_MYSTIC_WATER` | `0x30` | RECEIVED_MYSTIC_WATER |
| `FLAG_PART2_BOUGHT_QUICK_BALL` | `0x31` | BOUGHT_QUICK_BALL |
| `FLAG_PART2_RECEIVED_FOCUS_PUNCH` | `0x32` | RECEIVED_FOCUS_PUNCH |
| `FLAG_PART2_WINGULL_FOUND` | `0x33` | WINGULL_FOUND |
| `FLAG_PART2_WINGULL_REWARD` | `0x34` | WINGULL_REWARD |
| `FLAG_PART2_RECEIVED_HEART_SCALES` | `0x35` | RECEIVED_HEART_SCALES |
| `FLAG_PART2_ROUTE110_SUPER_POTION` | `0x36` | ROUTE110_SUPER_POTION |
| `FLAG_PART2_ROUTE110_ETHER` | `0x37` | ROUTE110_ETHER |
| `FLAG_PART2_TRICK_EXTRA_CANDY` | `0x38` | TRICK_EXTRA_CANDY |
| `FLAG_PART2_BOUGHT_MAGNET` | `0x39` | BOUGHT_MAGNET |
| `FLAG_PART2_TRADED_VULPIX` | `0x3A` | TRADED_VULPIX |
| `FLAG_PART2_ROUTE110_HIDDEN_CANDY` | `0x264` | ROUTE110_HIDDEN_CANDY |

永久VAR：`VAR_PART2_PEACE_CHARM_STATE=0x404E`，四状态常量位于 `include/constants/part2.h`。`FLAG_TEMP_C`仅管理当前地图长翅鸥返回后的可见性，地图重进按0x33重新计算，不作永久任务状态。

| 地图 | 新对象 | 坐标(x,y) | 模型 |
|---|---|---|---|
| Route116 | `LOCALID_PART2_SCYTHER_COURIER` | (76,14) | `OBJ_EVENT_GFX_MAN_1` |
| Route110 | `LOCALID_PART2_SUPER_POTION` | (31,72) | `OBJ_EVENT_GFX_ITEM_BALL` |
| Route110 | `LOCALID_PART2_ETHER` | (5,41) | `OBJ_EVENT_GFX_ITEM_BALL` |
| SlateportCity | `LOCALID_PART2_QUICK_MERCHANT` | (6,46) | `OBJ_EVENT_GFX_MAN_3` |
| SlateportCity | `LOCALID_PART2_FOCUS_COACH` | (11,34) | `OBJ_EVENT_GFX_BLACK_BELT` |
| SlateportCity | `LOCALID_PART2_CHARM_WOMAN` | (8,20) | `OBJ_EVENT_GFX_WOMAN_2` |
| SlateportCity | `LOCALID_PART2_DELIVERY_MAN` | (35,40) | `OBJ_EVENT_GFX_MAN_2` |
| SlateportCity | `LOCALID_PART2_WINGULL_LOST` | (8,34) | `OBJ_EVENT_GFX_SPECIES(WINGULL)` |
| SlateportCity | `LOCALID_PART2_WINGULL_HOME` | (34,40) | `OBJ_EVENT_GFX_SPECIES(WINGULL)` |
| Route110_TrickHouseEntrance | `LOCALID_PART2_TRICK_BONUS_BOX` | (3,7) | `OBJ_EVENT_GFX_ITEM_BALL` |
| MauvilleCity | `LOCALID_PART2_IV_TUTOR` | (17,16) | `OBJ_EVENT_GFX_MAN_1` |
| MauvilleCity | `LOCALID_PART2_MAGNET_MERCHANT` | (11,16) | `OBJ_EVENT_GFX_MAN_3` |
| MauvilleCity | `LOCALID_PART2_MAREEP_ELDER` | (28,14) | `OBJ_EVENT_GFX_OLD_MAN` |
| MauvilleCity | `LOCALID_PART2_MAREEP` | (29,14) | `OBJ_EVENT_GFX_SPECIES(MAREEP)` |
| MauvilleCity | `LOCALID_PART2_VULPIX_TRADER` | (34,16) | `OBJ_EVENT_GFX_WOMAN_1` |

隐藏道具 `ITEM_RARE_CANDY`：Route110 (34,28)，FLAG_PART2_ROUTE110_HIDDEN_CANDY，数量1。

## 最终阵容与配招

| 战斗/玩家初始选择 | 宝可梦 | 等级 | 招式 | 持物 |
|---|---|---|---|---|
| `TRAINER_BRENDAN_ROUTE_110_MUDKIP` | Swellow | 19 | Wing Attack, Quick Attack, Growl, Focus Energy | 无 |
| `TRAINER_BRENDAN_ROUTE_110_MUDKIP` | Wingull | 19 | Water Gun, Wing Attack, Growl, Quick Attack | 无 |
| `TRAINER_BRENDAN_ROUTE_110_MUDKIP` | Slugma | 20 | Ember, Rock Throw, Yawn, Smog | 无 |
| `TRAINER_BRENDAN_ROUTE_110_MUDKIP` | Grovyle | 22 | Mega Drain, Quick Attack, Fury Cutter, Leer | 无 |
| `TRAINER_BRENDAN_ROUTE_110_TREECKO` | Swellow | 19 | Wing Attack, Quick Attack, Growl, Focus Energy | 无 |
| `TRAINER_BRENDAN_ROUTE_110_TREECKO` | Wingull | 19 | Water Gun, Wing Attack, Growl, Quick Attack | 无 |
| `TRAINER_BRENDAN_ROUTE_110_TREECKO` | Lombre | 20 | Water Gun, Mega Drain, Fake Out, Growl | 无 |
| `TRAINER_BRENDAN_ROUTE_110_TREECKO` | Combusken | 22 | Ember, Double Kick, Scratch, Focus Energy | 无 |
| `TRAINER_BRENDAN_ROUTE_110_TORCHIC` | Swellow | 19 | Wing Attack, Quick Attack, Growl, Focus Energy | 无 |
| `TRAINER_BRENDAN_ROUTE_110_TORCHIC` | Lombre | 19 | Water Gun, Mega Drain, Fake Out, Growl | 无 |
| `TRAINER_BRENDAN_ROUTE_110_TORCHIC` | Slugma | 20 | Ember, Rock Throw, Yawn, Smog | 无 |
| `TRAINER_BRENDAN_ROUTE_110_TORCHIC` | Marshtomp | 22 | Water Gun, Mud Shot, Rock Throw, Growl | 无 |
| `TRAINER_MAY_ROUTE_110_MUDKIP` | Swellow | 19 | Wing Attack, Quick Attack, Growl, Focus Energy | 无 |
| `TRAINER_MAY_ROUTE_110_MUDKIP` | Wingull | 19 | Water Gun, Wing Attack, Growl, Quick Attack | 无 |
| `TRAINER_MAY_ROUTE_110_MUDKIP` | Slugma | 20 | Ember, Rock Throw, Yawn, Smog | 无 |
| `TRAINER_MAY_ROUTE_110_MUDKIP` | Grovyle | 22 | Mega Drain, Quick Attack, Fury Cutter, Leer | 无 |
| `TRAINER_MAY_ROUTE_110_TREECKO` | Swellow | 19 | Wing Attack, Quick Attack, Growl, Focus Energy | 无 |
| `TRAINER_MAY_ROUTE_110_TREECKO` | Wingull | 19 | Water Gun, Wing Attack, Growl, Quick Attack | 无 |
| `TRAINER_MAY_ROUTE_110_TREECKO` | Lombre | 20 | Water Gun, Mega Drain, Fake Out, Growl | 无 |
| `TRAINER_MAY_ROUTE_110_TREECKO` | Combusken | 22 | Ember, Double Kick, Scratch, Focus Energy | 无 |
| `TRAINER_MAY_ROUTE_110_TORCHIC` | Swellow | 19 | Wing Attack, Quick Attack, Growl, Focus Energy | 无 |
| `TRAINER_MAY_ROUTE_110_TORCHIC` | Lombre | 19 | Water Gun, Mega Drain, Fake Out, Growl | 无 |
| `TRAINER_MAY_ROUTE_110_TORCHIC` | Slugma | 20 | Ember, Rock Throw, Yawn, Smog | 无 |
| `TRAINER_MAY_ROUTE_110_TORCHIC` | Marshtomp | 22 | Water Gun, Mud Shot, Rock Throw, Growl | 无 |
| `TRAINER_WALLY_MAUVILLE` | Ralts | 18 | Confusion, Disarming Voice, Double Team, Teleport | 无 |
| `TRAINER_WALLY_MAUVILLE` | Roselia | 17 | Mega Drain, Poison Sting, Stun Spore, Leech Seed | 无 |
| `TRAINER_WATTSON_1` | Voltorb | 21 | Tackle, Spark, Thunder Shock, Thunder Wave | 无 |
| `TRAINER_WATTSON_1` | Electrike | 21 | Shock Wave, Bite, Quick Attack, Howl | 无 |
| `TRAINER_WATTSON_1` | Magneton | 23 | Shock Wave, Supersonic, Thunder Wave, Metal Sound | 无 |
| `TRAINER_WATTSON_1` | Manectric | 24 | Shock Wave, Bite, Quick Attack, Howl | Oran Berry |

合法替换：[['Combusken', 'Peck', 'Scratch'], ['Voltorb', 'Sonic Boom', 'Thunder Shock'], ['Magneton', 'Sonic Boom', 'Thunder Wave']]。玩家MUDKIP→劲敌Grovyle，玩家TREECKO→劲敌Combusken，玩家TORCHIC→劲敌Marshtomp；原分支常量后缀指玩家选择，未按名字猜对手初始物种。

## 所有统一进化石映射

| 源物种/形态 | 目标 |
|---|---|
| `SPECIES_POLIWHIRL` | `SPECIES_POLITOED` |
| `SPECIES_KADABRA` | `SPECIES_ALAKAZAM` |
| `SPECIES_MACHOKE` | `SPECIES_MACHAMP` |
| `SPECIES_GRAVELER` | `SPECIES_GOLEM` |
| `SPECIES_GRAVELER_ALOLA` | `SPECIES_GOLEM_ALOLA` |
| `SPECIES_SLOWPOKE` | `SPECIES_SLOWKING` |
| `SPECIES_HAUNTER` | `SPECIES_GENGAR` |
| `SPECIES_ONIX` | `SPECIES_STEELIX` |
| `SPECIES_RHYDON` | `SPECIES_RHYPERIOR` |
| `SPECIES_SEADRA` | `SPECIES_KINGDRA` |
| `SPECIES_SCYTHER` | `SPECIES_SCIZOR` |
| `SPECIES_ELECTABUZZ` | `SPECIES_ELECTIVIRE` |
| `SPECIES_MAGMAR` | `SPECIES_MAGMORTAR` |
| `SPECIES_PORYGON` | `SPECIES_PORYGON2` |
| `SPECIES_PORYGON2` | `SPECIES_PORYGON_Z` |
| `SPECIES_FEEBAS` | `SPECIES_MILOTIC` |
| `SPECIES_DUSCLOPS` | `SPECIES_DUSKNOIR` |
| `SPECIES_CLAMPERL` | `SPECIES_HUNTAIL`, `SPECIES_GOREBYSS` |
| `SPECIES_BOLDORE` | `SPECIES_GIGALITH` |
| `SPECIES_GURDURR` | `SPECIES_CONKELDURR` |
| `SPECIES_KARRABLAST` | `SPECIES_ESCAVALIER` |
| `SPECIES_SHELMET` | `SPECIES_ACCELGOR` |
| `SPECIES_SPRITZEE` | `SPECIES_AROMATISSE` |
| `SPECIES_SWIRLIX` | `SPECIES_SLURPUFF` |
| `SPECIES_PHANTUMP` | `SPECIES_TREVENANT` |
| `SPECIES_PUMPKABOO_AVERAGE` | `SPECIES_GOURGEIST_AVERAGE` |
| `SPECIES_PUMPKABOO_SMALL` | `SPECIES_GOURGEIST_SMALL` |
| `SPECIES_PUMPKABOO_LARGE` | `SPECIES_GOURGEIST_LARGE` |
| `SPECIES_PUMPKABOO_SUPER` | `SPECIES_GOURGEIST_SUPER` |

## 以后复用与预留

- 限购：给对应NPC的pokemart商品表加入商品；分配已确认未用Flag；在 `sLimitedShopItems` 加 `{MAP_..., ITEM_..., FLAG_...}`。普通道具价/付款/背包检查沿用shop.c。当前地图+商品为键，同地图不同商人卖同一商品共享资格。
- 一次赠礼：沿用 giveitem 结果分支，成功后再设置Flag，失败保留领取资格。共享奖励函数以call/return运行，不重写原奖励。
- 平安符后续：状态1携带时在未来基地原必经路NPC检测道具与VAR，成功移交后再设置2；回凯那重逢后设置3。未来隐藏奖励未定义，基地角色/战斗/奖励/文本尚未创建。
- 气合拳：未来Route115批次替换原固定TM球，维持原拾取Flag，避免重复无意义TM；本次仅登记。
- 进化石：以后在隐藏点/支线/中后期商店配置获取，不与任何组织绑定。源物种使用同一ITEM规则，新增通讯类物种时必须同时改表并增加测试；Clamperl分支从临时UI选择，未加永久状态。

## 人工使用mGBA测试以下内容

1. **新档与旧PART1存档**：载入/保存/重启后任务状态和重要道具保留；原Ralts蛋、Full Heal、水之石及四种限购/学习装置100/50/OFF无回归。不要把中文迁移前的未知旧存档兼容视为已验证。
2. **Route116**：按原地图解锁条件回墨镜NPC附近；原墨镜角色正常，赠礼NPC不挡路；队伍6只失败后腾位置能领取；Scyther18、攻击IV31、普通技能，重复及读档不重复。该地点仍受原地图通行/碎岩进度限制，未为赠礼提前打开地图。
3. **海之家/市场**：三场原挑战与6汽水/300元购买流程；Mystic Water满包重领；Quick Ball正常价、取消/缺钱/满包/售罄与存档永久限制；Focus Punch满包补领。
4. **平安符/长翅鸥**：原中心进出不受挡；平安符重要道具不能丢弃/卖出，保存后状态1；Wingull叫声、原位置消失/主人旁出现、重进地图一致；超级球3满包保留资格。
5. **博物馆**：票务、两场原水舰队战、库斯诺吉/水梧桐和外部撤离正常；三展板中文分页；Heart Scale3满包后找一楼工作人员补领，不重复。
6. **Route110/机关屋/自行车**：原道具与训练家不受新增坐标影响；三个新道具包括隐藏糖果仅一次；第一机关原奖励+额外奖励与满包延迟领取；自行车单车选择和免费切换提示。
7. **劲敌六分支**：两性别×三玩家初始选择，四只正确，王牌22；Ralts/Kirlia在队伍与不在队伍时对白；原探宝器、移动离场和进城流程无卡死。
8. **Summary**：能力页面按A循环能力/IV/EV，六项数字正确，EV合计/510无重叠；切回经验标签恢复；换宝可梦/PC与退出重新进入正常；性格、特性、状态图标、中文名称和L/R/方向导航保持。
9. **紫堇**：教程与磁铁原价限购；老人/咩利羊只叫声；满充两只和原叔叔/道馆剧情；六尾交换取消/错误物种/正确Mawile/队伍和PC选择/保存一次，得到18级“小焰”。
10. **进化石**：在单独测试存档获得测试用道具后检查Scyther→Scizor无携带物、Kadabra等、原携带物类、特定交换物种、Clamperl两个选择及B取消不消耗；普通水火雷石/等级/亲密度/地点进化、Mega不回归。本批主线未提供进化石来源。
11. **铁旋**：原机关不改，四只及招式，徽章/电击波/碎岩权限正常；之后剧情不新增。

## 静默日常工作流

在WSL权威仓库执行 `bash scripts/build.sh` 或 `bash scripts/build.sh --release`。VS Code默认构建任务仅构建并执行五套终端检查，产物复制到 `D:\Pokemon gba\artifacts\current`；不启动ROM。`--run`仍被明确拒绝，Windows `allowGui=false`。

## 修改文件清单

- `DEV_LOG.md`
- `PART2_SLATEPORT_MAUVILLE_IMPLEMENTATION.md`
- `PROJECT_BLUEPRINT.md`
- `data/event_scripts.s`
- `data/maps/MauvilleCity/map.json`
- `data/maps/MauvilleCity/scripts.inc`
- `data/maps/MauvilleCity_BikeShop/scripts.inc`
- `data/maps/MauvilleCity_Gym/scripts.inc`
- `data/maps/Route109_SeashoreHouse/scripts.inc`
- `data/maps/Route110/map.json`
- `data/maps/Route110/scripts.inc`
- `data/maps/Route110_TrickHouseEnd/scripts.inc`
- `data/maps/Route110_TrickHouseEntrance/map.json`
- `data/maps/Route110_TrickHouseEntrance/scripts.inc`
- `data/maps/Route116/map.json`
- `data/maps/Route116/scripts.inc`
- `data/maps/SlateportCity/map.json`
- `data/maps/SlateportCity/scripts.inc`
- `data/maps/SlateportCity_OceanicMuseum_1F/scripts.inc`
- `data/maps/SlateportCity_OceanicMuseum_2F/scripts.inc`
- `data/scripts/part2.inc`
- `data/specials.inc`
- `docs/project/part2-manifest.json`
- `include/config/summary_screen.h`
- `include/constants/flags.h`
- `include/constants/items.h`
- `include/constants/part2.h`
- `include/constants/trade.h`
- `include/constants/vars.h`
- `include/part2.h`
- `scripts/build.sh`
- `scripts/tests/check-chinese.py`
- `scripts/tests/check-part1.py`
- `scripts/tests/check-part2.py`
- `scripts/tests/test-opening.py`
- `src/data/items.h`
- `src/data/pokemon/species_info/gen_1_families.h`
- `src/data/pokemon/species_info/gen_3_families.h`
- `src/data/pokemon/species_info/gen_5_families.h`
- `src/data/pokemon/species_info/gen_6_families.h`
- `src/data/trade.h`
- `src/data/trainers.party`
- `src/limited_shop.c`
- `src/part2.c`
- `src/party_menu.c`
- `src/pokemon.c`
- `src/pokemon_summary_screen.c`
- `src/trade.c`
- `src/wild_encounter.c`

- `OPENING_IMPLEMENTATION.md`（维护入口指向本批，历史事件保持）

## 最终构建证据

两种静默日常构建工作流均返回0，五套终端检查全部通过。生成物32MiB，GBA头代码BPEE及头部校验和有效，Windows副本与仓库产物逐字节相同。常规ROM使用约81.19%空间，Release约81.53%。

| 构建 | SHA256 | 日志 |
|---|---|---|
| pokeemerald.gba | `72e5a755754341279e8e61c62fd48ea1f8dcd22065a7445c6f8a5ac2faef180d` | `D:\Pokemon gba\logs\part2-workflow-normal.log` |
| pokeemerald-release.gba | `9a1abb64a860cca50c6ed904fd5f161bba7718f57f0c33126a349af5850bd2e1` | `D:\Pokemon gba\logs\part2-workflow-release.log` |

完整机器记录 `D:\Pokemon gba\logs\part2-verification.json`。普通/Release均保留原中文底座和上游已有warning，本批核心新增C入口未出现新warning。构建成功与静态头校验不代表实际游戏内验收完成。
