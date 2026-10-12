# PART 3：绿荫镇至釜炎镇实施与验收

日期：2026-10-06。底座继续使用 RHH 官方 pokeemerald-expansion `expansion/1.17.1`，上游 `bb1093a7c72d3961d9a37d8e02ad2abc2c866682`，沿用当前简体中文字体、编码及 PART 1/PART 2 内容。

权威源码：`/home/pokemon/projects/emerald-story`；Windows工作入口：`D:\Pokemon gba`。实施前基线 `53e4aef8634b34273cdcc9beac03e8d860b4be9e`，标签 `pre-part3-implementation`。最终提交/标签：本地标签 `part3-verdanturf-lavaridge`（分支 `project/part3`）；可用 `git show part3-verdanturf-lavaridge` 查看完成提交。

范围到亚莎与第四枚徽章，未制作橙华道馆之后的新主线。本批全程仅终端编辑、Git、静默构建与无界面检查；没有启动任何GUI、模拟器或ROM，也不自动打开构建产物。殿堂脚本仅增加炎帝恢复钩子，没有扩写联盟剧情。

## 按要求54项最终报告

1. **修改文件清单**：见本文末尾的源码/地图/数据/测试清单。四份区域manifest与global manifest记录精确坐标和分配；ROOT的 `PROJECT_BLUEPRINT.md`、`DEV_LOG.md` 统一记录进度。
2. **117新增内容**：培育屋短说明、宝宝主题培育家、正负电双打、隐藏安抚之铃、以太1。原培育屋管理、蛋产生/领取、寄养宝可梦地图对象、所有原训练家、超级球、复活药与隐藏驱虫喷雾保留。
3. **培育屋对白**：原男/女管理员入口仅调用 `Route117_Part3_DaycareInfo`。首次用 `FLAG_PART3_DAYCARE_EXPLAINED` 记录简短孵蛋与继承提示；每次用原 `DoesPlayerPartyContainSpecies` 检查 `SPECIES_EGG`，有蛋追加走路建议，不修改蛋数据或孵化规则。
4. **新人培育家队伍**：拓也，Pokemon Breeder M，地图MAN_4，(55,10)，`TRAINER_PART3_BREEDER=857`。皮丘20、皮宝宝20、宝宝丁21，IV6，普通初始技能；胜负沿用原训练家Flag，无奖励。战后携蛋时追加同行对白。
5. **正负电拍拍双打**：优与奏，Twins，地图两个LASS，(3,10)/(4,10)，`TRAINER_PART3_PLUSLE_MINUN=858`，原生 `trainerbattle_double`。正电拍拍22/负电拍拍22，IV6；不足两只可战宝可梦时原生提示，不给奖励。
6. **安抚之铃位置**：117 (9,15)，偏离东西主路，原生hidden_item，1个，`FLAG_PART3_ROUTE117_SOOTHE_BELL=0x265`。以太道具球(53,14)，`0x41`；未发放“进化石”。
7. **绿荫新增内容**：满充与叔叔/堂姐短对白体现健康和信心增长，保持原剧情分支。听声音老人(15,9)按原 `ScriptGetPartyMonSpecies` 读取第一格；咕妞妞/吼爆弹/爆音怪吐槽“隔着两条街”，蛋和其他物种普通对白。帐篷外青年(4,9)失败5次，玩家完整获胜后再对话离场。
8. **帐篷首次奖励**：原BattleTent第三场获胜分支才设置 `FLAG_PART3_TENT_COMPLETED=0x3C`；接待员共享赠礼给PP提升剂1，成功才设 `FLAG_PART3_TENT_REWARD=0x3D`。满包可再次找接待员领取。原三连胜、保存、选队、自动战斗、随机奖品及其延迟领取全部保留；失败或主动退出不解锁奖励。
9. **卡绿隧道变化**：只润色情侣感谢，原碎岩触发、怪力HM、情侣移动/离开与 `FLAG_RUSTURF_TUNNEL_OPENED` 指令保留。Route116原PART1施工人员、矿工在该原生Flag之后改为贯通/运输对白，原矿工硬石头奖品仍只领一次且可满包补领。
10. **111新增内容**：胜利家族连续战保持，父亲傲骨燕/蛇纹熊21，母亲毒蔷薇22，女儿玛力露/蘑蘑菇/呆火驼23，祖母玛沙那24；原竞争背心不变。野餐一家三口(21,108)/(22,109)/(20,108)，蛇纹熊(21,111)只叫声；母亲仙贝1，`0x3F`，成功才Flag、满包重领。
11. **沙漠入口**：旅行者(9,63)提醒沙暴/装备/特殊物种；沙漠内可见活力块1(13,60)，`0x40`。原61行等全部沙暴坐标触发、护目镜判断和地形不变；获得护目镜前不能踏入取物的相邻地面。
12. **112新增内容**：登山客健太，(18,37)，`TRAINER_PART3_HIKER=859`，小拳石22/腕力22，IV6；战后讲背石头爬山。大石头对象(24,39)可调查训练次数，纯环境，无推石/奖励机制。缆车口普通工作人员(26,32)、游客(25,37)有事件状态对白。
13. **缆车切换**：外侧人员按 `FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY` 紧张/恢复营业。下站原员工在原 `FLAG_HIDE_ROUTE_112_TEAM_MAGMA` 未设置时暂不发车；原流星事件撤走封锁成员后，仍允许剧情必需的第一次上山，并提醒山顶冲突。山顶解决后恢复原乘车对话；没有把“解决山顶以后才能上山”写成死锁。
14. **热焰最终野生表**：见下方精确概率表，原等级14–16及10遇敌率保持。最终采用熔岩虫14%、煤炭龟10%、鸭嘴宝宝5%、戴鲁比5%；原12槽20/20/10/10/10/10/5/5/4/4/1/1无法同时精确表达15/8/5/5，选择邻近比例，保留两种稀少火系各5%。
15. **火之石/木炭**：新增易取得的火之石(27,22)，`0x4E`；木炭(6,31)，`0x4F`，较深、需要原怪力探索。原热焰(7,32)火之石保留；原生道具球成功后移除，满包不失去奖品。高温裂缝调查(27,18)无奖励。
16. **怪力回访区**：复用原热焰小径左侧推石支路与原六块怪力巨石，第四徽章的原户外怪力权限控制进入。仅将北端(8,2)原地面图块改为同tileset洞口，添加第三个warp；上下分别进入新洞穴和领取TM，不新增提前开放Flag或替换怪力系统。
17. **喷射火焰TM**：热焰回访下侧(8,33)，`ITEM_TM_FLAMETHROWER` 1，`FLAG_PART3_FIERY_FLAMETHROWER=0x54`，原生一次性道具球。原剧毒TM保留。
18. **炎帝洞穴**：新地图 `ScorchedGrotto`，正式地图名“灼热岩窟”，使用既有GBA洞穴资源、火山岩与高温调查文本，没有将物种名字写进地图名。入口热焰(8,2)；洞内入口(7,17)，最深处固定对象(7,4)。复用原未用 `MAPSEC_FIERY_PATH2` 区域名槽，不重排旧地图编号。
19. **Lv40**：脚本 `seteventmon SPECIES_ENTEI, PART3_ENTEI_LEVEL`，常量40，先原生叫声，再 `BattleSetup_StartLegendaryBattle`，标准可捕获固定遭遇。没有人为增加等级限制或禁止第四徽章后的挑战。
20. **捕获/失败/重生**：`VAR_PART3_ENTEI_STATE=0x4083` 区分0从未挑战、1未捕获等待、2已捕获、3新殿堂胜利后允许重现。`BeginPart3EnteiBattle` 战前先写等待，黑白回城中断也不会原地刷；`FinishPart3EnteiBattle` 用实际 `gBattleOutcome == B_OUTCOME_CAUGHT` 记捕获。同步 `FLAG_PART3_HIDE_ENTEI=0x55`：1/2隐藏，0/3出现。每次新的殿堂胜利只将1→3，含首次成为冠军；已捕获2永不变化。后续重挑战再次失败，可在下一次新的联盟胜利恢复，避免第二次失败永久错过；地图切换本身不恢复。
21. **失败提示**：保留要求的意思：“炎帝的身影消失在洞窟深处……”“空气中仍残留着炽热的气息。”“也许等你站上丰缘训练家的顶点之后，它还会再次回应你。”正常失败和黑白后返回都能读取，捕获后只剩普通热气文本。
22. **113新增内容**：画家(25,13)与风景调查(27,13)，看景后漂亮羽毛1，`0x42/0x43`，满包重领；晃晃斑小孩(56,12)与晃晃斑(57,12)，携带晃晃斑时额外花纹对白；隐藏物提示(65,13)，隐藏超级药(64,12)/以太(68,12)；扫灰老太太(39,14)/走路草(38,14)，地图宝可梦均原生叫声、无奖励。
23. **火山灰新增兑换**：原8项滚动菜单变9项（含退出），保留原玻璃哨和家具。新增“炽热岩石”，原 `VAR_ASH_GATHER_COUNT` 1500份兑换；确认才扣灰。继续用原制作/领取状态机，取消或灰不够不扣除；满包保存在原工匠制作状态17，回店领取，不重复扣灰。
24. **炽热岩石**：`ITEM_HEAT_ROCK` 1个，重复付灰兑换，不免费赠送。原道具、天气效果与价格未修改。烟囱山事件后工匠追加“今天火山灰好像特别多”的轻微环境对白，原集灰袋系统保持。
25. **秋叶新增内容**：普通研究者(18,10)、普通陨石爱好者(3,12，事件后吐槽)、收藏者(16,18，星星碎片1)，保持小镇生活感。收藏赠礼 `0x44` 成功后设置，满包可重领；没有传说/新组织话题。
26. **首次免费回忆**：原选择宝可梦/招式/取消/蛋/无可回忆招式分支保持。`FLAG_PART3_FREE_MOVE_RELEARN_USED=0x45` 未设置时不要求心之鳞片；只有 `TeachMoveRelearnerMove` 实际成功后才设置。拒绝/取消/选蛋/无招式均保留免费机会；成功之后每次仍消耗1心之鳞片，不强制扣第一片。
27. **黑暗球限购**：秋叶原店普通商品全部保留，追加黑暗球，按原道具价格1000，单存档1，`0x46`。沿用已有 `limited_shop` 的地图/道具/Flag表；取消、缺钱、满包不Flag，成功付款入包才Flag。没有卖月之石。
28. **114最终野生表**：猫鼬斩10%、饭匙蛇10%，可同时遇见；其余详表。保留陆地15–18等级，冲浪和碎岩表未改。钓鱼加入泥泥鳅：老钓竿70%泥泥鳅/30%角金鱼，好钓竿60%泥泥鳅/20%角金鱼/20%鲤鱼王，厉害钓竿100%泥泥鳅，原分级范围不变。概率指正常槽位权重，原诱饵/特性修正保持。
29. **兰奈**：原PC存储介绍、房间整理笑点、原玩偶与笔记保持；首次拜访额外高级球3，`0x47`，成功才Flag、满包再访补领；未引入壁纸重构。屋外向尾喵(28,39)只叫声。生态NPC(22,24)讲猫鼬斩/饭匙蛇争吵，化石迷保留赠挖洞TM并提示111沙漠。
30. **流星最终野生表**：仅第一房间陆地：超音蝠55%、太阳岩15%、月石15%、小拳石10%、皮皮5%，等级14–20沿用对应槽，原冲浪/钓鱼和深层表不变。
31. **原月之石**：原流星瀑布月之石道具球完全保留，没有新增第二颗，也未把秋叶商店改卖月之石。
32. **宝贝龙后期区域**：所有深层/攀瀑地图、warp、遭遇表保持；未提前放到第一房间。原高层和瀑布的视觉与游客回访提示保留，未给前期跨越能力。
33. **流星主线**：只增强陨石/烟囱山能源和水舰队阻止火岩队的目标文本；索蓝斯、双方移动、陨石流程、撤退与原传送不改。新增普通游客(11,27)有前后状态对白，岩石调查(8,27)给星星沙1，`0x4D`，满包可重领。
34. **烟囱地图演出**：复用原4个土狼犬对峙对象为大嘴鸥(30,5)、呆火驼(31,5)、利牙鱼(30,12)、大狼犬(29,12)，保留原站位及对应群体hideFlag；只播放各自叫声。成员短对白明确利用山体力量/反对榨干山体，没有新增第三方组织。
35. **女新人实现**：原 `OBJ_EVENT_GFX_MAGMA_MEMBER_F`，原生Team Magma类别、Magma Grunt F战斗图/手下，没有正式名字或新立绘。新人(10,10)处于上层单通道，`TRAINER_PART3_MAGMA_ROOKIE=860`；原训练家已击败状态判断战斗只一次，战后走到(9,9)让路，重入恢复让路位置。
36. **胖丁等级/6V**：只带胖丁Lv20，`trainers.party` 明确六项IV各31；普通初始技能，没有展示IV或剧情解释。长期设定只写设计文档：胖丁不进化且始终为她最高等级伙伴。
37. **新人战后/撤退**：战后紧张、不恼怒，解释胖丁是入队前伙伴、配发宝可梦还没到，后续抱怨其他人有大狼犬/呆火驼。原赤焰松群体撤退不隐藏她；玩家回到原(10,10)或主动对话播放“大家都走了？等、等等我啊！”，快速离开并设置 `0x48`，只演一次。
38. **赤焰松最终队伍与配招**：大狼犬25、大嘴蝠25、黑鲁加26、喷火驼27王牌；普通IV12、无竞技持物，两瓶超级药，AI检查差招/尝试击倒。精确配招见下表。战败对白保持冷静坚定，随后原撤退。
39. **烟囱战后状态**：原游客/训练家重现、群体撤退和缆车营业保持；原仙贝老太太(19,39)先赠仙贝3，`0x49`，满包补领，原200元购买继续。望远镜调查(11,6)事件前封锁，事件后描述南北风景，无奖励；复用地图调查点，未新增独立美术。
40. **凹凸最终野生表**：呆火驼55%、腕力10%、跳跳猪20%、小小象10%、铁甲犀牛5%；等级20–22、原20遇敌率保持。隐藏柔软沙子(11,25)，`0x268`。
41. **凹凸捷径**：从上方(18,7)朝南调查(18,8)开路；`0x4A` 永久记录并在onLoad恢复。将原14格越野车坡道替换为原普通坡路，不改warp或未来基地入口；底端到顶端步行连通由56格隔离区变为238格连通区。人工开凿痕迹(15,17)纯调查，疲惫登山客(11,35)不战斗。
42. **釜炎温泉功能**：(6,4)调查调用原 `HealPlayerParty` 及原治疗声，恢复全队HP/PP/状态、免费可重复；不改变亲密度、IV/EV或其他能力值。
43. **首位温泉反应**：原 `GetMonData` 读取第0格，排除蛋和空位，再通过实际物种双属性判火/冰，仅追加舒适/怕热文本。若火与冰同时具备，火判断优先；不改变任何宝可梦数据。
44. **原蛋是否保留**：原老太太实际 `giveegg SPECIES_WYNAUT`，即小果然（果然翁的宝宝），完整保留。设计稿称“果然翁蛋”，本批遵守保留原版要求，不替换为成年果然翁或其他种类，原满队处理与领取Flag不变。
45. **釜炎仙贝**：野餐1、山顶首次答谢3；原山顶购买200元保持，釜炎商店正常追加 `ITEM_LAVA_COOKIE` 按当前原道具价350，其他商品不变；没有修改仙贝本身数据。温泉附近老人提示火焰之躯加速孵蛋，实际原引擎孵蛋机制保持。
46. **雪童子NPC**：怕热训练家(17,10)/雪童子(18,10)，原生叫声。第四徽章后再次交流，两者离开并共用 `0x4B`；无奖励、不加入队伍。
47. **亚莎排练剧情**：原道馆1F深处(11–14,11)到馆主之前的坐标触发；`0x4C` 标记只播一次，已有第四徽章不播。正式战前紧张但努力，战后“对战时最轻松”；原机关/传送地洞及领奖骨架保持。
48. **亚莎最终队伍与配招**：熔岩虫26、九尾27、喷火驼28、煤炭龟29王牌。九尾少量晴天/状态、喷火驼强攻、煤炭龟耐久，普通IV12/王牌18、王牌橙橙果，两瓶超级药，无气腰/极端EV/天气锁/无限回复。准确配招见下表，原第四徽章、过热TM、怪力权限与后续护目镜场景保留。
49. **本批新增Flags**：27个永久Flag（23普通槽、4原隐藏物品槽），详表；另复用未用永久VAR `0x4083`、4个已有训练家区未用ID857–860，不扩大FLAGS_COUNT、MAX_TRAINERS_COUNT_EMERALD=864或存档结构；活动TRAINERS_COUNT_EMERALD由857增至861。新人战败用原训练家Flag，不浪费额外永久领取标记。
50. **未发放第一颗进化石**：本批赠礼、道具球、隐藏物、商店和火山灰兑换都没有 `ITEM_EVOLUTION_STONE/ITEM_LINKING_CORD`。仅提供原标准火之石、黑暗球等明确要求内容；PART2统一通讯进化机制保持，稳定来源留以后。
51. **普通构建**：`bash scripts/build.sh` 返回0，全部10套检查PASS；ROM32 MiB，SHA256 `cf146b42339da2aaa3f9c6f9bc14452aa6c7646511a2a5ca99775025eec76b38`。日志 `D:\Pokemon gba\logs\part3-normal-workflow.log`；未运行ROM。
52. **Release构建**：`bash scripts/build.sh --release` 返回0，全部10套检查PASS；ROM32 MiB，SHA256 `f57160ea5459d3994e61c319a1f622c2b30f0bff4b1996d2abb7ea22dfff6cde`。日志 `D:\Pokemon gba\logs\part3-release-workflow.log`；未运行ROM。
53. **静态检查**：中文、原开局、102/橙华、PART1、PART2以及本批West/Northwest/Volcano/Core/Data共10套全部PASS。覆盖实际C状态机40组合、真实事件满包/补领、防重复、合法推石路径、地图碰撞/对象容量/原推进、精确野生权重、当前Gen9配招、固定捕获重生和EXP回归；32 MiB源产物与Windows副本逐字节相同，GBA头及补丁格式检查PASS。静态成功不代替游戏验证。
54. **人工mGBA验证**：本文后附逐区域清单。本次禁止且未运行模拟器，人工验收仍待用户执行。

## 新增Flags与永久VAR

| 常量 | 数值 |
| --- | --- |
| `FLAG_PART3_DAYCARE_EXPLAINED` | `0x3B` |
| `FLAG_PART3_TENT_COMPLETED` | `0x3C` |
| `FLAG_PART3_TENT_REWARD` | `0x3D` |
| `FLAG_PART3_TENT_YOUNGSTER_LEFT` | `0x3E` |
| `FLAG_PART3_PICNIC_COOKIE` | `0x3F` |
| `FLAG_PART3_DESERT_VISIBLE_ITEM` | `0x40` |
| `FLAG_PART3_ROUTE117_ETHER` | `0x41` |
| `FLAG_PART3_ROUTE113_VIEW_EXAMINED` | `0x42` |
| `FLAG_PART3_RECEIVED_PRETTY_FEATHER` | `0x43` |
| `FLAG_PART3_RECEIVED_STAR_PIECE` | `0x44` |
| `FLAG_PART3_FREE_MOVE_RELEARN_USED` | `0x45` |
| `FLAG_PART3_BOUGHT_DUSK_BALL` | `0x46` |
| `FLAG_PART3_RECEIVED_LANETTE_ULTRA_BALLS` | `0x47` |
| `FLAG_PART3_MAGMA_ROOKIE_LEFT` | `0x48` |
| `FLAG_PART3_MT_CHIMNEY_COOKIES` | `0x49` |
| `FLAG_PART3_JAGGED_SHORTCUT_OPEN` | `0x4A` |
| `FLAG_PART3_SNORUNT_TRAINER_LEFT` | `0x4B` |
| `FLAG_PART3_FLANNERY_REHEARSAL_HEARD` | `0x4C` |
| `FLAG_PART3_METEOR_STARDUST` | `0x4D` |
| `FLAG_PART3_FIERY_FIRE_STONE` | `0x4E` |
| `FLAG_PART3_FIERY_CHARCOAL` | `0x4F` |
| `FLAG_PART3_FIERY_FLAMETHROWER` | `0x54` |
| `FLAG_PART3_HIDE_ENTEI` | `0x55` |
| `FLAG_PART3_ROUTE117_SOOTHE_BELL` | `0x265` |
| `FLAG_PART3_ROUTE113_HIDDEN_SUPER_POTION` | `0x266` |
| `FLAG_PART3_ROUTE113_HIDDEN_ETHER` | `0x267` |
| `FLAG_PART3_JAGGED_SOFT_SAND` | `0x268` |

| 永久VAR | 数值 | 状态 |
| --- | --- | --- |
| `VAR_PART3_ENTEI_STATE` | `0x4083` | 0未挑战/1等待联盟/2已捕获/3新联盟胜利可重现 |

全部从已核实原UNUSED槽重命名；原开局0x20–0x23、PART1 0x24–0x2E、PART2 0x2F–0x3A及其隐藏0x264不变。

## 新增对象及调查坐标

坐标按(x,y)，数据来自四份区域manifest和当前地图，原对象变更、地形坡道与新warp见各manifest。

| 地图 | 对象/调查 | 坐标 | 内容 |
| --- | --- | --- | --- |
| Route117 | `LOCALID_PART3_BREEDER` | (55,10) | `Route117_Part3_Breeder` |
| Route117 | `LOCALID_PART3_DOUBLE_LEFT` | (3,10) | `Route117_Part3_PlusleMinun` |
| Route117 | `LOCALID_PART3_DOUBLE_RIGHT` | (4,10) | `Route117_Part3_PlusleMinun` |
| Route117 | `LOCALID_PART3_ROUTE117_ETHER` | (53,14) | `ITEM_ETHER` |
| VerdanturfTown | `LOCALID_PART3_SOUND_ELDER` | (15,9) | `VerdanturfTown_Part3_SoundElder` |
| VerdanturfTown | `LOCALID_PART3_TENT_YOUNGSTER` | (4,9) | `VerdanturfTown_Part3_TentYoungster` |
| Route111 | `LOCALID_PART3_PICNIC_FATHER` | (21,108) | `Route111_Part3_PicnicFather` |
| Route111 | `LOCALID_PART3_PICNIC_MOTHER` | (22,109) | `Route111_Part3_PicnicMother` |
| Route111 | `LOCALID_PART3_PICNIC_CHILD` | (20,108) | `Route111_Part3_PicnicChild` |
| Route111 | `LOCALID_PART3_PICNIC_ZIGZAGOON` | (21,111) | `Route111_Part3_PicnicZigzagoon` |
| Route111 | `LOCALID_PART3_DESERT_TRAVELER` | (9,63) | `Route111_Part3_DesertTraveler` |
| Route111 | `LOCALID_PART3_DESERT_VISIBLE_ITEM` | (13,60) | `ITEM_MAX_REVIVE` |
| Route112 | `LOCALID_PART3_HIKER` | (18,37) | `Route112_Part3_Hiker` |
| Route112 | `LOCALID_PART3_TRAINING_ROCK` | (24,39) | `Route112_Part3_TrainingRock` |
| Route112 | `LOCALID_PART3_CABLE_WORKER` | (26,32) | `Route112_Part3_CableWorker` |
| Route112 | `LOCALID_PART3_CABLE_TOURIST` | (25,37) | `Route112_Part3_CableTourist` |
| Route117 | `ITEM_SOOTHE_BELL` | (9,15) | `ITEM_SOOTHE_BELL` |
| Route113 | `LOCALID_PART3_ASH_PAINTER` | (25,13) | `Route113_Part3_Painter` |
| Route113 | `LOCALID_PART3_SPINDA_KID` | (56,12) | `Route113_Part3_SpindaKid` |
| Route113 | `LOCALID_PART3_SPINDA` | (57,12) | `Route113_Part3_SpindaCry` |
| Route113 | `LOCALID_PART3_ASH_HINT` | (65,13) | `Route113_Part3_AshHint` |
| Route113 | `LOCALID_PART3_ASH_GRANDMA` | (39,14) | `Route113_Part3_AshGrandma` |
| Route113 | `LOCALID_PART3_ODDISH` | (38,14) | `Route113_Part3_OddishCry` |
| FallarborTown | `LOCALID_PART3_METEOR_RESEARCHER` | (18,10) | `FallarborTown_Part3_Researcher` |
| FallarborTown | `LOCALID_PART3_METEOR_FAN` | (3,12) | `FallarborTown_Part3_MeteorFan` |
| FallarborTown | `LOCALID_PART3_ROCK_COLLECTOR` | (16,18) | `FallarborTown_Part3_Collector` |
| Route114 | `LOCALID_PART3_ROUTE114_ECOLOGY` | (22,24) | `Route114_Part3_Ecology` |
| Route114 | `LOCALID_PART3_LANETTE_SKITTY` | (28,39) | `Route114_Part3_SkittyCry` |
| Route113 | `Route113_Part3_View` | (27,13) | `Route113_Part3_View` |
| Route113 | `ITEM_SUPER_POTION` | (64,12) | `ITEM_SUPER_POTION` |
| Route113 | `ITEM_ETHER` | (68,12) | `ITEM_ETHER` |
| MeteorFalls_1F_1R | `LOCALID_PART3_METEOR_VISITOR` | (11,27) | `MeteorFalls_Part3_Visitor` |
| MtChimney | `LOCALID_PART3_MAGMA_ROOKIE` | (10,10) | `MtChimney_Part3_Rookie` |
| JaggedPass | `LOCALID_PART3_JAGGED_HIKER` | (11,35) | `JaggedPass_Part3_TiredHiker` |
| LavaridgeTown | `LOCALID_PART3_ICE_TRAINER` | (17,10) | `LavaridgeTown_Part3_IceTrainer` |
| LavaridgeTown | `LOCALID_PART3_SNORUNT` | (18,10) | `LavaridgeTown_Part3_Snorunt` |
| LavaridgeTown | `LOCALID_PART3_FIRE_FAN` | (14,9) | `LavaridgeTown_Part3_FireFan` |
| LavaridgeTown | `LOCALID_PART3_FLANNERY_FAN` | (2,16) | `LavaridgeTown_Part3_FlanneryFan` |
| MeteorFalls_1F_1R | `MeteorFalls_Part3_Stardust` | (8,27) | `MeteorFalls_Part3_Stardust` |
| MtChimney | `MtChimney_Part3_Telescope` | (11,6) | `MtChimney_Part3_Telescope` |
| JaggedPass | `ITEM_SOFT_SAND` | (11,25) | `ITEM_SOFT_SAND` |
| JaggedPass | `JaggedPass_Part3_WallMarks` | (15,17) | `JaggedPass_Part3_WallMarks` |
| JaggedPass | `JaggedPass_Part3_OpenShortcut` | (18,8) | `JaggedPass_Part3_OpenShortcut` |
| LavaridgeTown | `LavaridgeTown_Part3_HotSpring` | (6,4) | `LavaridgeTown_Part3_HotSpring` |
| FieryPath | `LOCALID_PART3_FIERY_FIRE_STONE` | (27,22) | `ITEM_FIRE_STONE` |
| FieryPath | `LOCALID_PART3_FIERY_CHARCOAL` | (6,31) | `ITEM_CHARCOAL` |
| FieryPath | `LOCALID_PART3_FIERY_FLAMETHROWER` | (8,33) | `ITEM_TM_FLAMETHROWER` |
| ScorchedGrotto | `LOCALID_PART3_ENTEI` | (7,4) | `Part3_Entei` |
| FieryPath | `Part3_FieryHotFissure` | (27,18) | `Part3_FieryHotFissure` |
| ScorchedGrotto | `Part3_GrottoHeat` | (7,8) | `Part3_GrottoHeat` |
| ScorchedGrotto | `Part3_EnteiGone` | (7,4) | `Part3_EnteiGone` |

## 最终遭遇权重

以下为无诱饵/特性引导等修正的正常陆地槽位权重，不是地图每一步的遇敌概率。保留原各槽等级和遇敌率。

| 地图 | 宝可梦 | 权重 |
| --- | --- | --- |
| `MAP_ROUTE114` | 青绵鸟 (`SPECIES_SWABLU`) | 34% |
| `MAP_ROUTE114` | 莲叶童子 (`SPECIES_LOTAD`) | 25% |
| `MAP_ROUTE114` | 猫鼬斩 (`SPECIES_ZANGOOSE`) | 10% |
| `MAP_ROUTE114` | 饭匙蛇 (`SPECIES_SEVIPER`) | 10% |
| `MAP_ROUTE114` | 莲帽小童 (`SPECIES_LOMBRE`) | 20% |
| `MAP_ROUTE114` | 长鼻叶 (`SPECIES_NUZLEAF`) | 1% |
| `MAP_FIERY_PATH` | 呆火驼 (`SPECIES_NUMEL`) | 30% |
| `MAP_FIERY_PATH` | 瓦斯弹 (`SPECIES_KOFFING`) | 24% |
| `MAP_FIERY_PATH` | 腕力 (`SPECIES_MACHOP`) | 10% |
| `MAP_FIERY_PATH` | 熔岩虫 (`SPECIES_SLUGMA`) | 14% |
| `MAP_FIERY_PATH` | 鸭嘴宝宝 (`SPECIES_MAGBY`) | 5% |
| `MAP_FIERY_PATH` | 戴鲁比 (`SPECIES_HOUNDOUR`) | 5% |
| `MAP_FIERY_PATH` | 煤炭龟 (`SPECIES_TORKOAL`) | 10% |
| `MAP_FIERY_PATH` | 臭泥 (`SPECIES_GRIMER`) | 2% |
| `MAP_JAGGED_PASS` | 呆火驼 (`SPECIES_NUMEL`) | 55% |
| `MAP_JAGGED_PASS` | 腕力 (`SPECIES_MACHOP`) | 10% |
| `MAP_JAGGED_PASS` | 跳跳猪 (`SPECIES_SPOINK`) | 20% |
| `MAP_JAGGED_PASS` | 小小象 (`SPECIES_PHANPY`) | 10% |
| `MAP_JAGGED_PASS` | 铁甲犀牛 (`SPECIES_RHYHORN`) | 5% |
| `MAP_METEOR_FALLS_1F_1R` | 超音蝠 (`SPECIES_ZUBAT`) | 55% |
| `MAP_METEOR_FALLS_1F_1R` | 太阳岩 (`SPECIES_SOLROCK`) | 15% |
| `MAP_METEOR_FALLS_1F_1R` | 月石 (`SPECIES_LUNATONE`) | 15% |
| `MAP_METEOR_FALLS_1F_1R` | 小拳石 (`SPECIES_GEODUDE`) | 10% |
| `MAP_METEOR_FALLS_1F_1R` | 皮皮 (`SPECIES_CLEFAIRY`) | 5% |

## 最终Boss与新增训练家数据

表中的英文招式名对应当前Expansion正式常量；统一静态检查将按当前Gen9升级/可教授表校验。原胜利家族只调整本次级别及祖母IV，普通招式自动按原机制产生。

| 战斗 | 宝可梦 | 等级 | 招式/持物 |
| --- | --- | --- | --- |
| `TRAINER_PART3_BREEDER` | Pichu | 20 | 当前等级原生初始技能 |
| `TRAINER_PART3_BREEDER` | Cleffa | 20 | 当前等级原生初始技能 |
| `TRAINER_PART3_BREEDER` | Igglybuff | 21 | 当前等级原生初始技能 |
| `TRAINER_PART3_PLUSLE_MINUN` | Plusle | 22 | 当前等级原生初始技能 |
| `TRAINER_PART3_PLUSLE_MINUN` | Minun | 22 | 当前等级原生初始技能 |
| `TRAINER_PART3_HIKER` | Geodude | 22 | 当前等级原生初始技能 |
| `TRAINER_PART3_HIKER` | Machop | 22 | 当前等级原生初始技能 |
| `TRAINER_PART3_MAGMA_ROOKIE` | Jigglypuff | 20 | 当前等级原生初始技能 |
| `TRAINER_MAXIE_MT_CHIMNEY` | Mightyena | 25 | Bite, Sand Attack, Howl, Roar |
| `TRAINER_MAXIE_MT_CHIMNEY` | Golbat | 25 | Aerial Ace, Bite, Confuse Ray, Supersonic |
| `TRAINER_MAXIE_MT_CHIMNEY` | Houndoom | 26 | Ember, Bite, Smog, Roar |
| `TRAINER_MAXIE_MT_CHIMNEY` | Camerupt | 27 | Lava Plume, Bulldoze, Rock Slide, Focus Energy |
| `TRAINER_FLANNERY_1` | Slugma | 26 | Incinerate, Rock Throw, Smog, Light Screen |
| `TRAINER_FLANNERY_1` | Ninetales | 27 | Sunny Day, Flamethrower, Will O Wisp, Quick Attack |
| `TRAINER_FLANNERY_1` | Camerupt | 28 | Lava Plume, Bulldoze, Rock Slide, Take Down |
| `TRAINER_FLANNERY_1` | Torkoal @ Oran Berry | 29 | Overheat, Body Slam, Curse, Protect |

## 女熔岩队新人长期角色约束

初登场烟囱山，当前无正式名字，原普通女成员地图素材及其原发色不变。只带Lv20六项IV31胖丁；本批文本不告诉玩家IV、身份未来或组织配发机制背后的额外故事。

设计文档预留：以后可以在天气研究所、送神火山、熔岩队基地等节点成长；胖丁永不进化且永远为队伍最高等级。二周目退出熔岩队后才制作独立普通服装形象并赋名，发色与原女性素材一致。以上未来内容本批没有实现，也未放入玩家对白或源码剧透注释。

## 需要人工使用mGBA测试以下内容

所有这些项目都待人工进游戏验证；本批没有替用户运行ROM。

- 用PART2旧存档与新存档分别加载/保存；开局拉鲁拉丝蛋、特攻31、限购高级球、EVAN Full Heal、橙华水之石与雷伊布正常。
- PART1岩石/拳击徽章、原学习装置开关、100%参战/50%后台/蛋和濒死0经验、不设等级上限、日常奖品与旧一次性赠礼正常。
- PART2凯那支线与博物馆、完整劲敌6分支、紫堇/满充/铁旋、IV/EV实际页面与总计、六尾原生交换、进化石所有通讯目标及珍珠贝选择仍正常；本批无进化石来源。
- 117正常东西通行、原训练家视线、三位新增模型；培育家战斗与战后携蛋对白；双打主动交谈/视线触发、两只/不足两只可战宝可梦；原寄养/取回/产蛋/领取功能，第一次解释及有蛋/无蛋分支。
- 安抚之铃和以太的位置可调查/可取得，满包不丢失，拿后保存重入不再出现；原超级球等探索物不变。
- 绿荫满充/叔叔/堂姐在紫堇战后、亚莎前后原分支自然；声音老人第一格咕妞妞/吼爆弹/爆音怪、普通物种、蛋，文本显示正确。
- 对战帐篷失败/退赛/休息和真正第三胜；仅完整通关给PP Up；原随机奖品仍给且满包保留；满包后接待员可补PP Up；保存重入无重复；门口青年只在完整通关后离场。
- 隧道原碎岩/情侣动作/HM怪力/开通Flag正常；Route116施工/矿工开通前后对白；原硬石头奖品未重领；原飞天螳螂Lv18攻击IV31、满队补领正常。
- 胜利家族四连战级别、最后较强但可正常挑战；原竞争背心；野餐仙贝一次性/满包補领，蛇纹熊仅叫声，新增对象不遮原事件。
- 111没有护目镜时原沙暴仍阻止通过，能看到但不能提前拿到沙漠道具；护目镜后可正常探索/领活力块，其他原化石和物品保留。
- 112登山客战斗/石头调查；缆车口封锁时紧张文本、不发车；流星事件之后可首次上山；赤焰松后恢复营业，往返缆车原动画/下站重入不阻断。
- 热焰普通通行及原Scott状态；新火之石易得，木炭偏深，原火之石和剧毒TM仍可取得；新物种与近似遭遇比例；原巨石第四徽章前不能推，第四徽章后能推。
- 热焰左支路上下可走；TM喷射火焰一次性；灼热岩窟地图名、入口往返、地形图块、调查与视觉不剧透物种。
- 炎帝Lv40、叫声、正常可捕获；捕获/击败/逃跑/玩家败北分别测试，败北后返回有提示；未捕获地图重进不立即重生；第一次殿堂之后出现一次，后续失败要新的联盟胜利才出现；捕获后每次殿堂都不再出现；保存和旧档加载保持状态。
- 113原集灰袋、集灰和全部原玻璃/家具兑换；1500灰炽热岩石足够/不足/取消/满包/离店再取，灰不会重复扣；烟囱前后工匠文本；风景→画家奖品一次性且满包保留。
- 113新增地图晃晃斑/走路草叫声，携晃晃斑分支、普通队伍、蛋不被误识别；两处隐藏物品可取得且不重复；老太太和提醒NPC视觉位置正确。
- 秋叶三位新NPC普通生活语气，流星前后爱好者文本、星星碎片一次/满包重领；黑暗球正常1000售价、数量只能1、缺钱/取消/满包未买标记、成功保存后售罄，原商店商品仍在。
- 回忆第一次无心之鳞片可以成功一次；拒绝/取消/选蛋/无招式都不耗免费资格；成功后正常交1片，包括拥有原博物馆3片时；原回忆UI、PC选取、忘招流程正常。
- 114猫鼬斩和饭匙蛇同时可抓、三种钓竿泥泥鳅分布；兰奈原电脑/玩偶/笔记，首次高级球3和满包再访，向尾喵只叫声；化石迷原奖励与沙漠提示正常。
- 流星索蓝斯、双方抵达/讲话/撤退无移动卡死，原月之石只有原1颗；调查星星沙一次/满包补领；游客事件前后对白；太阳岩/月石/皮皮前期可遇，宝贝龙深层仍需后期攀瀑。
- 烟囱原双方对峙地图对象、四只宝可梦朝向与叫声；女性新人普通原发色、拦路、Lv20胖丁六项IV31、败北后让路、重入已败不重打；原赤焰松四只与所有动作、战败撤退；回头新人的快速离开只一次。
- 烟囱原群体撤退/游客回归；山顶仙贝3一次/满包補领、原200元购买；望远镜事件前后文本及调查位置。
- 凹凸小小象/铁甲犀牛分布，柔软沙子一次性、刻痕调查无提前开基地；上方开路后保存/重入恢复普通坡道，从釜炎方向可步行返回烟囱；原落差/其他训练家/未来基地口不坏。
- 釜炎温泉反复全队治疗HP/PP/状态；第一格火/冰/普通/蛋文本，仅文字反应，无IV/EV/亲密度改动；原小果然蛋、满队处理、老人孵蛋提示、商店350价仙贝。
- 釜炎训练家/雪童子共同离场只在第四徽章后再互动；六尾/九尾/煤炭龟爱好者分支；门口小孩；亚莎隔墙排练只一次，正式战前/战后文本正常。
- 亚莎最终4只与当前合法配招，原地洞机关、徽章、过热TM、第四徽章户外怪力权限、劲敌护目镜场景正常；本批没有自动继续橙华道馆新主线。

## 源码与数据文件清单

以下清单来自报告生成时已整合的Git diff/新增文件；最终提交时统一核对。机器可读manifest为依据，构建产物和Windows工具脚本不进入源码提交。

- `DEV_LOG.md`
- `PROJECT_BLUEPRINT.md`
- `data/event_scripts.s`
- `data/layouts/FieryPath/map.bin`
- `data/layouts/ScorchedGrotto/border.bin`
- `data/layouts/ScorchedGrotto/map.bin`
- `data/layouts/layouts.json`
- `data/maps/FallarborTown/map.json`
- `data/maps/FallarborTown/scripts.inc`
- `data/maps/FallarborTown_Mart/scripts.inc`
- `data/maps/FallarborTown_MoveRelearnersHouse/scripts.inc`
- `data/maps/FieryPath/map.json`
- `data/maps/FieryPath/scripts.inc`
- `data/maps/JaggedPass/map.json`
- `data/maps/JaggedPass/scripts.inc`
- `data/maps/LavaridgeTown/map.json`
- `data/maps/LavaridgeTown/scripts.inc`
- `data/maps/LavaridgeTown_Gym_1F/map.json`
- `data/maps/LavaridgeTown_Gym_1F/scripts.inc`
- `data/maps/LavaridgeTown_Mart/scripts.inc`
- `data/maps/MeteorFalls_1F_1R/map.json`
- `data/maps/MeteorFalls_1F_1R/scripts.inc`
- `data/maps/MtChimney/map.json`
- `data/maps/MtChimney/scripts.inc`
- `data/maps/Route111/map.json`
- `data/maps/Route111/scripts.inc`
- `data/maps/Route112/map.json`
- `data/maps/Route112/scripts.inc`
- `data/maps/Route112_CableCarStation/scripts.inc`
- `data/maps/Route113/map.json`
- `data/maps/Route113/scripts.inc`
- `data/maps/Route113_GlassWorkshop/scripts.inc`
- `data/maps/Route114/map.json`
- `data/maps/Route114/scripts.inc`
- `data/maps/Route114_FossilManiacsTunnel/scripts.inc`
- `data/maps/Route114_LanettesHouse/scripts.inc`
- `data/maps/Route116/scripts.inc`
- `data/maps/Route117/map.json`
- `data/maps/Route117/scripts.inc`
- `data/maps/RusturfTunnel/scripts.inc`
- `data/maps/ScorchedGrotto/map.json`
- `data/maps/ScorchedGrotto/scripts.inc`
- `data/maps/VerdanturfTown/map.json`
- `data/maps/VerdanturfTown/scripts.inc`
- `data/maps/VerdanturfTown_BattleTentBattleRoom/scripts.inc`
- `data/maps/VerdanturfTown_BattleTentLobby/scripts.inc`
- `data/maps/VerdanturfTown_WandasHouse/scripts.inc`
- `data/maps/map_groups.json`
- `data/scripts/day_care.inc`
- `data/scripts/hall_of_fame.inc`
- `data/specials.inc`
- `docs/project/PART3_VERDANTURF_LAVARIDGE_IMPLEMENTATION.md`
- `docs/project/part3-core-manifest.json`
- `docs/project/part3-global-manifest.json`
- `docs/project/part3-manifest.json`
- `docs/project/part3-northwest-manifest.json`
- `docs/project/part3-volcano-manifest.json`
- `docs/project/part3-volcano-notes.md`
- `docs/project/part3-west-manifest.json`
- `include/constants/flags.h`
- `include/constants/opponents.h`
- `include/constants/part3.h`
- `include/constants/vars.h`
- `include/part3.h`
- `scripts/build.sh`
- `scripts/tests/check-part1.py`
- `scripts/tests/check-part2.py`
- `scripts/tests/check-part3-core.py`
- `scripts/tests/check-part3-data.py`
- `scripts/tests/check-part3-northwest.py`
- `scripts/tests/check-part3-volcano.py`
- `scripts/tests/check-part3-west.py`
- `scripts/tests/check-route102-petalburg.py`
- `scripts/tests/test-opening.py`
- `src/data/region_map/region_map_sections.json`
- `src/data/trainers.party`
- `src/data/wild_encounters.json`
- `src/field_specials.c`
- `src/limited_shop.c`
- `src/part3.c`

## 最终构建与检查证据

- 普通构建：`bash scripts/build.sh`，返回0；`D:\Pokemon gba\logs\part3-normal-workflow.log`。
- 普通ROM：33554432字节；SHA256 `cf146b42339da2aaa3f9c6f9bc14452aa6c7646511a2a5ca99775025eec76b38`。
- Release构建：`bash scripts/build.sh --release`，返回0；`D:\Pokemon gba\logs\part3-release-workflow.log`。
- ReleaseROM：33554432字节；SHA256 `f57160ea5459d3994e61c319a1f622c2b30f0bff4b1996d2abb7ea22dfff6cde`。
- 终端检查：10套全部PASS；`git diff --check` PASS；GBA头/Windows副本一致PASS。
- 最终Git：`project/part3`，本地完成标签 `part3-verdanturf-lavaridge`；此前完整PART2备份标签 `pre-part3-implementation`。
- 游戏内人工验收：未执行；不得将构建/静态结果描述成mGBA实测。
