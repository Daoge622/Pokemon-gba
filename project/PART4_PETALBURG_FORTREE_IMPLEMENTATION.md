# PART 4 橙华—茵郁实施报告

日期：2026-10-07。执行 AI：Codex。状态：**IMPLEMENTED；normal/release 与无界面检查 PASS；游戏内人工验收 PENDING。**

定稿依据：`docs/story/PART4_FINAL.md`（用户明确授权实施）。保留原主线骨架及开局/PART1–3。所有坐标为地图逻辑坐标，未加引擎边框偏移；权威配置见 `docs/project/part4-manifest.json`。

## 1. 修改文件清单

完整清单见文末；相对于 `pre-part4-implementation`。权威源码在 WSL，未修改旧 source 快照。

## 2. 武斗世界交流修补

原普通居民补船运/外地货物对白，不新增神秘组织人物。

## 3. 凯那世界交流修补

原城镇宣传 NPC 和海洋博物馆补贸易、釜炎仙贝和同行研究交流；原海洋博物馆流程保留。

## 4. 紫堇世界交流修补

原居民和风野自行车店补外地零件/订单对白；原赠车及铁旋事件保留。

## 5. 秋叶/兰奈世界交流修补

原居民、兰奈相关文本补样本交换/设备反馈；原流星事件不变。

## 6. 釜炎旅游对白

原温泉居民补朋友推荐旅行的普通旅游信息。

## 7. 沙漠最终野生表

TRAPINCH 30% Lv.20–21；BALTOY 20% Lv.20–20；CACNEA 20% Lv.21–21；SANDILE 10% Lv.19–19；GIBLE 5% Lv.19–19；SANDSHREW 7% Lv.19–22；HIPPOPOTAS 8% Lv.20–20

## 8. 光粉位置

原 PART3 可见球位置 (13,60) 改为光粉；沿用原领取 Flag 0x40，不新增第二份球。

## 9. 绿洲实现

两种 Route111 布局同步：2×2 原生水面 (27–28,58–59)，旁边少量草地；旅人/大颚蚁叫声及隐藏神奇糖果 (27,57)。

## 10. 水壶支线

水壶持有人 (19,40)，调查点 (28,66)；找回后奖沙沙岩石×1。成功入包后才消耗水壶并记完成。

## 11. 第一颗进化石

沙漠 (28,37) 调查获得进化石×1，一档一次，满包可重领；保留 ITEM_LINKING_CORD=796 的现有别名系统。

## 12. 幻影之塔是否保持正常

原两块化石、4F 选择/塌塔和雷吉洛克门谜题保留；只在 1F 增加普通墙面调查。

## 13. 橙华NPC状态变化

妈妈在四徽章回访/千里后有状态对白；橙华居民和败北训练家状态更新，保留妈妈治疗。

## 14. 千里最终队伍

晃晃斑29、直冲熊29、猫鼬斩30、过动猿30、请假王32。其余 IV12，王牌 IV18/文柚果；请假王懒惰不改。普通道馆房间七队小幅增强。

## 15. 千里最终配招

完整配招/持物/道馆队伍见文末原数据摘录。两瓶高级伤药；没有 Mega、属性作弊或异常努力值。

## 16. 冲浪获得

满充爸爸原 HM 冲浪流程保留；取得失败不提前设置领取 Flag，重试资格保留。

## 17. 吃剩的东西位置

橙华水塘小岛 (2,29) 新球，领取脚本要求已得冲浪；原以太/活力块不动。

## 18. 115号道路王者之证

115 北部冲浪可到的陆地 (19,8) 一次性王者之证；原训练家/道具不删。

## 19. 漂流瓶

108 号道路 (39,5) 瓶子调查，普通海流/船运信息，珍珠×1。原星星碎片保留。

## 20. 废弃船新增调查

1F 房间三处货物/零件/旧航线调查，普通贸易语气。

## 21. 金属膜位置

AbandonedShip_Rooms_1F (3,13)，金属膜×1。

## 22. 潜水区PP提升剂

AbandonedShip_HiddenFloorRooms (3,3) PP提升剂×1；该区域原本要潜水才能进入，未提前开放。

## 23. 新紫堇阿尔刻技术员

入口 (2,4) 用 SCIENTIST_1 临时素材；119 知道阿尔刻前不报组织名，之后追加外勤组一句话，不改变发电机任务。

## 24. 隐藏维护通道

关闭主发电机后，Inside (38,5) 调查进入维护通道，再走原生六块开放门到高压间；新增房间/布局追加 ID。

## 25. 维护通道野生表

MAGNEMITE 35% Lv.24–27；VOLTORB 40% Lv.24–27；TYNAMO 10% Lv.24–27；KLINK 10% Lv.24–27；ELEKID 5% Lv.24–27。高压间同表。

## 26. 雷公Lv.40

高压间 (4,3)，原生 RAIKOU overworld，叫声后普通 Lv40 固定传说战。

## 27. 雷公重生逻辑

复用炎帝纯状态规则：0未挑战/1等待/2捕获/3殿堂恢复；战前写1防黑白中断，未捕获只在新殿堂胜利恢复，捕获永久隐藏。有消失/电流/登顶提示。

## 28. 铁旋捕获彩蛋

捕获状态2后铁旋追加电压异常彩蛋，无额外奖励。

## 29. 118树果支线

农夫 (38,13)，篮子对岸 (30,9)；归还文柚果×3，奖励成功前保留篮子和资格。

## 30. 安提首次登场完整流程

第五徽章+冲浪→东岸坐标触发→玩家战胜A→战胜B→3名增援→匿名男子与普通巨钳螳螂救场→手环→简短 Mega 说明→离开；持久阶段0–4及两战原训练家败北位负责恢复。

## 31. 水舰队成员战斗

A：利牙鱼26/大狼犬27；B：超音蝠26/吼吼鲸27/巨牙鲨28。玩家正常打两场；无干部级配置。

## 32. 巨钳螳螂演出

原生 Scizor overworld/普通叫声、快速左移再返回；3增援各右撤一步并移除，不建立 NPC 对 NPC 战斗系统。

## 33. Mega手环获得

原 ITEM_MEGA_RING 入包成功后设置领取 Flag 和阶段4；满包停阶段3可回领，不重复战斗；原 Expansion Mega 物品门槛保留。

## 34. 是否确认没有暴露安提身份

检查实际引用的全部 118 对白，无安提名字/阿尔刻/组织身份/本原协议；不和蛋或飛天螳螂赠礼连线。

## 35. 123号道路雷电兽Mega石

123 西侧 (39,12) 可选球获雷电兽 Mega 石×1，原野生/训练家不动。

## 36. 119号道路新增内容

雨中免费休息、隐藏岩石/珍珠、迷路母子、普通捕虫少年、仪器调查、可选阿尔刻侧路、北段观察员与 Fly 后商人。

## 37. 潮湿岩石

隐藏潮湿岩石 (7,76)，隐藏物原生处理，一档一次。

## 38. 丑丑鱼机制

原丑丑鱼钓点判断保持第一优先、所有119钓鱼表和水域表不改；只有草地新增木棉球5%/赫拉克罗斯5%。

## 39. 迷路小孩

孩子 (25,55)/莲叶童子 (27,56)；淡入淡出安全送到南营 (11,89)/(9,88)，妈妈 (11,88)；哞哞鲜奶与后续奖励分段领取，满包保留。

## 40. 捕虫少年

捕虫少年 (7,66) 不堵窄路；电萤虫27/甜甜萤27/溜溜糖球28，普通级别。

## 41. 天气研究所干部队伍

泉：大嘴鸥27、利牙鱼28、巨牙鲨30；IV12/常规 AI，一瓶好伤药，原撤退/研究所放行保留。

## 42. 飘浮泡泡生成规则

原随机赠送机制，Lv25，无附带神秘水滴、不固定优秀 IV；原 PC/昵称/Flag 分支保持。首位飘浮泡泡增加天气观察对白。

## 43. 观测桩支线

事件后可调查三处南边设备 (13,55)/(26,53)/(25,74)；各独立 Flag，确认/接线对白不同，回1F (9,7) 领 PP提升剂×1。静态观测说明，不新造动态预测系统。

## 44. 阿尔刻首次正式登场

研究所解决后，在119可选侧路友好双打；打完/再交流只报阿尔刻外勤和降雨观测。不提安提。

## 45. 阿尔刻调查员/技术员/护卫员实现

原模型临时替代三岗位；新增角色类常量，沿用原 name[13] 字节预算，简洁显示调查员/技术员/护卫员，完整组织名放对白；正式素材 TODO。

## 46. 第一次双打队伍

多边兽28+齿轮儿28，双打数据入口表示调查员/护卫员组合，技术员只管设备；普通男训练家 encounter 音乐，无水舰队音乐。

## 47. 是否可以拒绝对战

是/否邀请；拒绝礼貌祝福、不堵路、保留以后再战。少于两只可战斗宝可梦沿用原双打提醒。

## 48. 劲敌最终队伍

男女六分支均5只：大王燕28、雷电兽28、两补位29、对应御三家二阶段31/文柚果；完整6表见文末。新增雨路追上主角对白。

## 49. 飞翔获得

原劲敌赠飞翔/Scott 流程保持；满包不设置领取 Flag/路线完成 VAR，六败北检查避免赠礼重试重打劲敌。

## 50. 走私商人位置

119北段 (26,24)，Fly 前只普通停留，取得后开放，不堵主路。

## 51. 时间球售卖

时间球按原价正常付费、不限购。

## 52. EV树果售卖

榴石果/藻根果/比巴果/哈密果/萄葡果/茄番果六项降低EV树果正常出售，不限购。

## 53. 普通进化石限购

雷/火/水/月/太阳/觉醒石，每档每种最多2；可一次买2或分两次买1，卖出不会返库存。

## 54. 进化石限购

统一进化石正常售价8000，每档限1；复用现有表，商人是物流来源，不称发明者。

## 55. 茵郁风筝任务

孩子 (5,9)，地面 (8,17) 捡风筝，归还锐利鸟嘴×1；青绵鸟只叫声。

## 56. 包裹任务

邮递员 (7,9)/大嘴鸥 (6,8)，捡 (10,17) 密封包裹，归还高级球×3，不打开包裹、不增公司身份。

## 57. 奇迹种子限购

茵郁原友好商店普通列表保留，加奇迹种子原价付费限1；耗尽显示原售罄，取消/缺钱/满包不消耗。

## 58. 大吾对白

原镜子/变隐龙流程前，大吾留意手环并感叹主角成长；不介绍赠环者身份。

## 59. 得文侦测镜额外用途

两只可选隐藏变隐龙 (9,34)/(27,31)，需得文侦测镜、是/否使用镜子→原出现动作/叫声→普通30战；原桥上及城内变隐龙不替换。

## 60. 大嘴娃Mega石

可选深处分支调查 (6,39)，需解决第一只新增变隐龙后获大嘴娃 Mega 石×1；不堵主线。

## 61. 120号道路阿尔刻护卫战

120 (25,35) 护卫：初次提醒测量，再次交流可以接受普通战；铜镜怪29/三合一磁怪29/勇基拉30，战后移除让路。不正式敌对。

## 62. 旧石碑

普通石碑 (25,38)，雨天从原天气接口辨出风/云/山，其余时间模糊；不接阿尔刻。

## 63. 可选强敌

可选精英 (32,41)，阿勃梭鲁30/赫拉克罗斯30/七夕青鸟31；没有竞争配置/主路强制堵路。

## 64. 爱心鱼钓鱼表

只在120北湖 (x10–25,y17–24) 向前钓鱼格30%覆盖爱心鱼25–29，其余70%原该竿分布；不影响119丑丑鱼及别的地图。

## 65. 心之鳞片携带率

保留爱心鱼原 itemCommon=HEART_SCALE，普通携带率50%；不人为改数据。

## 66. 三暴鲤龙NPC

湖边钓鱼人 (5,20)，暴鲤龙30/31/32，抱怨仪器占钓位、女儿生日，无普通初战直接奖 Mega 石。

## 67. 水静女孩生日任务

水静女孩 (36,15)，生日/父亲原湖钓鱼信息；用户同意后转交正常爱心鱼，女孩旁 (37,15) 出现叫声 NPC。

## 68. 爱心鱼交付逻辑

仅队伍非蛋、未持物爱心鱼；必须保留至少一只活着的非蛋伙伴。成功才清目标槽/压紧队伍/更新人数与任务状态；持物（含邮件）先取下，满队无需 PC 转移；多只取首个合格者。

## 69. 暴鲤龙Mega石

转交状态2后回父亲获暴鲤龙 Mega 石×1，成功入包才Flag/状态3；满包保留回领。

## 70. Ancient Tomb原NPC修改

确认原 Ancient Tomb 外 Route120 Ruin Maniac Chip (9,60)；保留原战斗/遗迹/巨石原对白，只在战后追加赠礼。不新建重复 NPC。

## 71. 波士可多拉Mega石

原Chip战后波士可多拉 Mega 石×1，Flag一次，满包回领，原遗迹门谜题不动。

## 72. 二周目封印

原ScorchedSlab增加封印 (7,3)。需要冠军+单独未来授权 Flag；本批没有设置该授权的入口，冠军本身也打不开。不是提前编造二周目故事。

## 73. 来历不明的研究数据实现状态

已建内部房间和来历不明的研究数据重要物品（惰性、不可直接使用），未来授权后可一次领取；本批正常游玩不可取得。原晴天TM保留。

## 74. 确认用途仍为PENDING

用途仍 Pending，不添加机械神/究极之洞/实验/安提任务或传说关联解释。

## 75. 娜琪最终队伍

大王燕30/大嘴鸥30/热带龙31/盔甲鸟32/七夕青鸟33，IV12/王牌IV18文柚果，2高级伤药。

## 76. 娜琪配招

见完整数据；七夕青鸟龙舞/燕返/龙息/神秘守护，使用用户指定旧世代合法龙舞，不因此修改当前可教学表。原旋转门/第六徽章/TM保留，原门内训练家飞行主题对白保留，娜琪战前对白增加迎风前行。

## 77. 确认娜琪没有Mega

娜琪没有 Mega，也不赠 Mega 手环；道馆原奖励流程保留。

## 78. 暮水镇萨维尔NPC实现

暮水 (10,16) 安静赠礼 NPC，与原钓鱼人分开；程序标识 SAVIEL 只用于内部，不在台词显示名字。

## 79. 当前使用什么临时素材

OBJ_EVENT_GFX_GENTLEMAN，占位普通绅士；没有伪称专属素材完成。

## 80. 是否记录未来专属美术TODO

manifest/current task 已登记萨维尔专属地图/战斗素材 TODO；阿尔刻岗位、安提和来历不明的研究数据图标一并等待统一美术。

## 81. 古空棘鱼Lv.30赠送

正常 CreateMon：古空棘鱼30，Random32性格相关 personality、正常随机IV/性别/闪光逻辑、玩家OT；需队伍空位，不自动PC，成功才领取Flag和图鉴记录。

## 82. 是否确认没有显示萨维尔真实身份

仅“……这个给你。”“你会需要它的。”等短句；不显示姓名、身份或来历不明的研究数据关联。

## 83. 本批新增Flags / Vars

46个永久/隐藏物Flag、9个VAR，全部从原明确 UNUSED 槽分配；详表见文末。三剩余Trainer ID861–863+已审计未使用别名，无存档结构扩容。

## 84. 普通构建结果

成功，返回0；32MiB，GBA头PASS，Windows镜像逐字节相同。SHA与日志见验证表。

## 85. Release构建结果

成功，返回0；32MiB，GBA头PASS，Windows镜像逐字节相同。未处理原有无关LTO枚举签名提示，不掩盖成无警告。

## 86. 静态检查结果

12套不同无界面检查全部通过，含32地图模板/坐标/通路、Flag/VAR、全部新增队伍/原流程、283文本行208px、实际C状态边界与商店1/2库存。

## 87. 原版回归检查结果

中文、开局、102/橙华、PART1/2、五套PART3均通过；旧快照断言仅对PART4明确授权增量做精确逆变换，其他源码仍严格相等；新增PART4检查直接检查现码。

## 88. 需要用户人工在mGBA验证的全部项目

未运行 ROM。完整人工清单见下方；构建/静态及宿主C通过不代表地图演出、进化、菜单或存档实机验收。

## 验证产物

| 构建 | SHA256 | 大小/头/镜像 |
| --- | --- | --- |
| normal | `c868f3651f058edc20d9c2c32e62c8f69a6fbe9e2d8b6023eb6186e1185a771a` | 32MiB / PASS / byte-identical |
| release | `4fc30c44a6d3363aaad6d4fe4770e98386bf97088fc539893277792d8577b4ee` | 32MiB / PASS / byte-identical |

日志：`D:\Pokemon gba\logs\part4-normal-build.log`、`part4-release-build.log`；结构化证据：`docs/project/part4-verification.json` / Windows logs 同名文件。12检查只运行CLI Python/宿主C，不启动GBA、模拟器或GUI。

## Flag / VAR 完整表

| 常量 | 槽 |
| --- | --- |
| `FLAG_PART4_OASIS_CANDY` | `0x0269` |
| `FLAG_PART4_DAMP_ROCK` | `0x026A` |
| `FLAG_PART4_HIDE_RAIKOU` | `0x0493` |
| `FLAG_PART4_RELICANTH_RECEIVED` | `0x0494` |
| `FLAG_PART4_HIDE_LUVDISC` | `0x0495` |
| `FLAG_PART4_SEAL_AUTHORIZED` | `0x0496` |
| `FLAG_PART4_DESTRUCTION_FACTOR_RECEIVED` | `0x0497` |
| `FLAG_PART4_HIDE_ANTI` | `0x0498` |
| `FLAG_PART4_HIDE_AQUA_A` | `0x0499` |
| `FLAG_PART4_HIDE_AQUA_B` | `0x049A` |
| `FLAG_PART4_HIDE_AQUA_EXTRA` | `0x049B` |
| `FLAG_PART4_MEGA_RING_RECEIVED` | `0x049C` |
| `FLAG_PART4_ARCHE_KNOWN` | `0x049D` |
| `FLAG_PART4_SHOP_THUNDER_STONE_FIRST` | `0x049E` |
| `FLAG_PART4_SHOP_THUNDER_STONE_SECOND` | `0x049F` |
| `FLAG_PART4_SHOP_FIRE_STONE_FIRST` | `0x04A0` |
| `FLAG_PART4_SHOP_FIRE_STONE_SECOND` | `0x04A1` |
| `FLAG_PART4_SHOP_WATER_STONE_FIRST` | `0x04A2` |
| `FLAG_PART4_SHOP_WATER_STONE_SECOND` | `0x04A3` |
| `FLAG_PART4_SHOP_MOON_STONE_FIRST` | `0x04A4` |
| `FLAG_PART4_SHOP_MOON_STONE_SECOND` | `0x04A5` |
| `FLAG_PART4_SHOP_SUN_STONE_FIRST` | `0x04A6` |
| `FLAG_PART4_SHOP_SUN_STONE_SECOND` | `0x04A7` |
| `FLAG_PART4_SHOP_DAWN_STONE_FIRST` | `0x04A8` |
| `FLAG_PART4_SHOP_DAWN_STONE_SECOND` | `0x04A9` |
| `FLAG_PART4_SHOP_EVOLUTION_STONE` | `0x04AA` |
| `FLAG_PART4_SHOP_MIRACLE_SEED` | `0x04AB` |
| `FLAG_PART4_FIRSTEVOLUTIONSTONE` | `0x04AC` |
| `FLAG_PART4_DEFEATED_VISITOR_LEFT` | `0x04AD` |
| `FLAG_PART4_SURFLEFTOVERS` | `0x04AE` |
| `FLAG_PART4_ROUTE115KINGSROCK` | `0x04AF` |
| `FLAG_PART4_BOTTLEPEARL` | `0x04B0` |
| `FLAG_PART4_SHIPMETALCOAT` | `0x04B1` |
| `FLAG_PART4_SHIPDIVEPPUP` | `0x04B2` |
| `FLAG_PART4_MANECTITE` | `0x04B3` |
| `FLAG_PART4_119BIGPEARL` | `0x04B4` |
| `FLAG_PART4_OBSERVATION_0` | `0x04B5` |
| `FLAG_PART4_OBSERVATION_1` | `0x04B6` |
| `FLAG_PART4_OBSERVATION_2` | `0x04B7` |
| `FLAG_PART4_OBSERVATION_REWARD` | `0x04B8` |
| `FLAG_PART4_KECLEON_0` | `0x04B9` |
| `FLAG_PART4_KECLEON_1` | `0x04BA` |
| `FLAG_PART4_MAWILITE` | `0x04BB` |
| `FLAG_PART4_GUARD_PASSED` | `0x04BC` |
| `FLAG_PART4_GYARADOSITE` | `0x04BD` |
| `FLAG_PART4_RUINSAGGRONITE` | `0x04BE` |
| `VAR_PART4_RAIKOU_STATE` | `0x408B` |
| `VAR_PART4_MEGA_STAGE` | `0x4091` |
| `VAR_PART4_LUVDISC_STATE` | `0x409B` |
| `VAR_PART4_CANTEEN` | `0x409D` |
| `VAR_PART4_BERRYBASKET` | `0x40A1` |
| `VAR_PART4_CHILD_STAGE` | `0x40A8` |
| `VAR_PART4_KITE` | `0x40B8` |
| `VAR_PART4_PARCEL` | `0x40BB` |
| `VAR_PART4_GUARD_VISITS` | `0x40DB` |

## 最终训练家数据摘录

原生数据是本节的唯一来源；技术英文名与中文游戏名称对应，未另造队伍。

```text
=== TRAINER_RANDALL ===
Name: 俊树
Class: Cooltrainer
Pic: Cooltrainer M
Gender: Male
Music: Cool
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Swellow
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Quick Attack
- Agility
- Wing Attack
- Double Team
```

```text
=== TRAINER_PARKER ===
Name: 秀树
Class: Cooltrainer
Pic: Cooltrainer M
Gender: Male
Music: Cool
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Delcatty
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Sing
- Shock Wave
- Covet
- Fake Out
```

```text
=== TRAINER_ALEXIA ===
Name: 海晴
Class: Cooltrainer
Pic: Cooltrainer F
Gender: Female
Music: Cool
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Wigglytuff
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Defense Curl
- Body Slam
- Rollout
- Disable
```

```text
=== TRAINER_GEORGE ===
Name: 数马
Class: Cooltrainer
Pic: Cooltrainer M
Gender: Male
Music: Cool
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Slakoth @ Sitrus Berry
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Slack Off
- Yawn
- Body Slam
- Counter
```

```text
=== TRAINER_BERKE ===
Name: 直树
Class: Cooltrainer
Pic: Cooltrainer M
Gender: Male
Music: Cool
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Vigoroth
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Focus Energy
- Slash
- Aerial Ace
- Encore
```

```text
=== TRAINER_MARY ===
Name: 绫香
Class: Cooltrainer
Pic: Cooltrainer F
Gender: Female
Music: Cool
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Linoone
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Slash
- Headbutt
- Pin Missile
- Sand Attack
```

```text
=== TRAINER_JODY ===
Name: 沙织
Class: Cooltrainer
Pic: Cooltrainer F
Gender: Female
Music: Cool
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Zangoose
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Slash
- Quick Attack
- Swords Dance
- Detect
```

```text
=== TRAINER_NORMAN_1 ===
Name: 千里
Class: Leader
Pic: Leader Norman
Gender: Male
Music: Male
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Hyper Potion / Hyper Potion

Spinda
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Teeter Dance
- Psybeam
- Facade
- Copycat

Linoone
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Slash
- Headbutt
- Pin Missile
- Sand Attack

Zangoose
Level: 30
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Slash
- Aerial Ace
- Quick Attack
- Detect

Vigoroth
Level: 30
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Slash
- Aerial Ace
- Encore
- Brick Break

Slaking @ Sitrus Berry
Level: 32
IVs: 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- Facade
- Yawn
- Aerial Ace
- Brick Break
```

```text
=== TRAINER_PART4_AQUA_A ===
Name: 队员
Class: Team Aqua
Pic: Aqua Grunt M
Gender: Male
Music: Male
Double Battle: No
AI: Check Bad Move / Try To Faint

Carvanha
Level: 26
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Bite
- Aqua Jet
- Scary Face
- Ice Fang

Mightyena
Level: 27
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Bite
- Howl
- Sand Attack
- Assurance
```

```text
=== TRAINER_PART4_AQUA_B ===
Name: 队员
Class: Team Aqua
Pic: Aqua Grunt M
Gender: Male
Music: Male
Double Battle: No
AI: Check Bad Move / Try To Faint

Zubat
Level: 26
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Absorb
- Confuse Ray
- Bite
- Air Cutter

Wailmer
Level: 27
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Water Pulse
- Rollout
- Mist
- Whirlpool

Sharpedo
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Bite
- Aqua Jet
- Ice Fang
- Focus Energy
```

```text
=== TRAINER_PART4_BUG ===
Name: 小亮
Class: Bug Catcher
Pic: Bug Catcher
Gender: Male
Music: Male
Double Battle: No
AI: Check Bad Move / Try To Faint

Volbeat
Level: 27
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Struggle Bug
- Confuse Ray
- Moonlight
- Quick Attack

Illumise
Level: 27
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Struggle Bug
- Wish
- Charm
- Quick Attack

Surskit
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Bubble Beam
- Quick Attack
- Mist
- Agility
```

```text
=== TRAINER_GRUNT_UNUSED ===
Name: 工作人员
Class: Arche Surveyor
Pic: Scientist Frlg
Gender: Female
Music: Male
Double Battle: Yes
AI: Check Bad Move / Try To Faint

Porygon
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Psybeam
- Recover
- Agility
- Tri Attack

Klink
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Gear Grind
- Charge Beam
- Bind
- Thunder Shock
```

```text
=== TRAINER_SHELLY_WEATHER_INSTITUTE ===
Name: 阿泉
Class: Aqua Admin
Pic: Aqua Admin F
Gender: Female
Music: Aqua
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Pelipper
Level: 27
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Water Pulse
- Wing Attack
- Protect
- Mist

Carvanha
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Bite
- Aqua Jet
- Ice Fang
- Scary Face

Sharpedo
Level: 30
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Crunch
- Aqua Jet
- Ice Fang
- Focus Energy
```

```text
=== TRAINER_BRENDAN_ROUTE_119_MUDKIP ===
Name: 小悠
Class: Rival
Pic: Brendan
Gender: Male
Music: Male
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Swellow
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Wing Attack
- Quick Attack
- Double Team
- Focus Energy

Manectric
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Shock Wave
- Bite
- Thunder Wave
- Quick Attack

Breloom
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Slugma
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Marshtomp @ Sitrus Berry
Level: 31
IVs: 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
```

```text
=== TRAINER_BRENDAN_ROUTE_119_TREECKO ===
Name: 小悠
Class: Rival
Pic: Brendan
Gender: Male
Music: Male
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Swellow
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Wing Attack
- Quick Attack
- Double Team
- Focus Energy

Manectric
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Shock Wave
- Bite
- Thunder Wave
- Quick Attack

Wailmer
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Slugma
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Grovyle @ Sitrus Berry
Level: 31
IVs: 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
```

```text
=== TRAINER_BRENDAN_ROUTE_119_TORCHIC ===
Name: 小悠
Class: Rival
Pic: Brendan
Gender: Male
Music: Male
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Swellow
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Wing Attack
- Quick Attack
- Double Team
- Focus Energy

Manectric
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Shock Wave
- Bite
- Thunder Wave
- Quick Attack

Wailmer
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Breloom
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Combusken @ Sitrus Berry
Level: 31
IVs: 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
```

```text
=== TRAINER_MAY_ROUTE_119_MUDKIP ===
Name: 小遥
Class: Rival
Pic: May
Gender: Female
Music: Female
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Swellow
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Wing Attack
- Quick Attack
- Double Team
- Focus Energy

Manectric
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Shock Wave
- Bite
- Thunder Wave
- Quick Attack

Breloom
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Slugma
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Marshtomp @ Sitrus Berry
Level: 31
IVs: 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
```

```text
=== TRAINER_MAY_ROUTE_119_TREECKO ===
Name: 小遥
Class: Rival
Pic: May
Gender: Female
Music: Female
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Swellow
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Wing Attack
- Quick Attack
- Double Team
- Focus Energy

Manectric
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Shock Wave
- Bite
- Thunder Wave
- Quick Attack

Wailmer
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Slugma
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Grovyle @ Sitrus Berry
Level: 31
IVs: 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
```

```text
=== TRAINER_MAY_ROUTE_119_TORCHIC ===
Name: 小遥
Class: Rival
Pic: May
Gender: Female
Music: Female
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Super Potion

Swellow
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Wing Attack
- Quick Attack
- Double Team
- Focus Energy

Manectric
Level: 28
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Shock Wave
- Bite
- Thunder Wave
- Quick Attack

Wailmer
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Breloom
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe

Combusken @ Sitrus Berry
Level: 31
IVs: 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
```

```text
=== TRAINER_DUDLEY ===
Name: 工作人员
Class: Arche Guard
Pic: Scientist Frlg
Gender: Male
Music: Swimmer
Double Battle: No
AI: Check Bad Move / Try To Faint

Bronzor
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Confusion
- Confuse Ray
- Gyro Ball
- Hypnosis

Magneton
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Spark
- Light Screen
- Thunder Wave
- Supersonic

Kadabra
Level: 30
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Psybeam
- Recover
- Disable
- Reflect
```

```text
=== TRAINER_KAYLEE ===
Name: 小岚
Class: Cooltrainer
Pic: Cooltrainer F
Gender: Female
Music: Swimmer
Double Battle: No
AI: Check Bad Move / Try To Faint

Absol
Level: 30
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Slash
- Night Slash
- Quick Attack
- Detect

Heracross
Level: 30
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Brick Break
- Aerial Ace
- Horn Attack
- Leer

Altaria
Level: 31
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Dragon Breath
- Aerial Ace
- Sing
- Safeguard
```

```text
=== TRAINER_TERRY ===
Name: 阿成
Class: Fisherman
Pic: Fisherman
Gender: Female
Music: Intense
Double Battle: No
AI: Check Bad Move / Try To Faint

Gyarados
Level: 30
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Bite
- Twister
- Water Pulse
- Leer

Gyarados
Level: 31
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Ice Fang
- Water Pulse
- Bite
- Twister

Gyarados
Level: 32
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Aqua Tail
- Bite
- Twister
- Scary Face
```

```text
=== TRAINER_CINDY_2 ===
Name: 小羽
Class: Bird Keeper
Pic: Bird Keeper
Gender: Female
Music: Female
Double Battle: No
AI: Check Bad Move / Try To Faint

Swellow
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Wing Attack
- Quick Attack
- Double Team
- Focus Energy

Swablu
Level: 29
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Aerial Ace
- Sing
- Safeguard
- Take Down
```

```text
=== TRAINER_WINONA_1 ===
Name: 娜琪
Class: Leader
Pic: Leader Winona
Gender: Female
Music: Female
Double Battle: No
AI: Check Bad Move / Try To Faint
Items: Hyper Potion / Hyper Potion

Swellow
Level: 30
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Aerial Ace
- Quick Attack
- Double Team
- Focus Energy

Pelipper
Level: 30
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Water Pulse
- Wing Attack
- Protect
- Mist

Tropius
Level: 31
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Razor Leaf
- Aerial Ace
- Synthesis
- Whirlwind

Skarmory
Level: 32
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Steel Wing
- Aerial Ace
- Sand Attack
- Agility

Altaria @ Sitrus Berry
Level: 33
IVs: 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- Dragon Dance
- Aerial Ace
- Dragon Breath
- Safeguard
```

## 人工 mGBA 验证清单（由用户执行）

- [ ] 旧存档升级/新档均检查中文菜单和对白；学习装置开关、IV/EV、蛋/水之石/Evan及PART1–3奖励与限购不回退。
- [ ] 四徽章沙漠两种布局、绿洲水面/草地、坑、野生比例、光粉/隐藏糖/进化石；化石选择/塌塔、雷吉洛克谜题仍正常。
- [ ] 水壶/树果篮/风筝/密封包裹/观测桩，分别取消、满包、获得后重谈、换图存读档；不得吞奖/重奖或意外消耗任务物品。
- [ ] 妈妈回访/千里NPC前后状态、七间道馆房与首战千里难度/懒惰、第五徽章/冲浪及满包回领。
- [ ] 冲浪可到橙华小岛/115王者之证/108漂流瓶；原物品不消失。废弃船普通调查与金属膜、潜水区域PP提升剂和原拼钥匙流程。
- [ ] 新紫堇原开门/按钮/发电机/雷之石/铁旋任务；关机前不能进入维护通道，之后可往返维护/高压间，不落在墙里；普通野生实际出现。
- [ ] 雷公叫声/40战：捕获、击倒、逃跑、黑白、断续存读档与离图；没捕获必须新的殿堂胜利才恢复；抓过永不重生；铁旋彩蛋。
- [ ] 118从各正常冲浪落脚点触发，原大吾/记者/好钓竿仍可继续；A/B输掉后重返、两战胜后救场、演员完整显示/移动/撤退。
- [ ] Mega手环满包阶段3回领、存读档/换图不重打或刷手环；场景不报安提/阿尔刻身份；符合原条件的宝可梦持对应石后Mega可用。
- [ ] 123西侧雷电兽石可在本进度取得，不越过后续关卡；额外变隐龙镜子确认/拒绝/捕获/击倒/逃跑/黑白恢复，以及可选大嘴娃石。
- [ ] 119雨营治疗、母子与莲叶童子返回位置和每段奖励；捕虫少年站位/视线；原河流/桥/床/丑丑鱼随机钓点。
- [ ] 泉战与水舰队撤退、飘浮泡泡随机IV/无持物/满队PC与昵称；首位对白/三设备奖励。
- [ ] 119阿尔刻侧路：忙碌状态/拒绝/只有一只可战斗伙伴/双打胜败/再谈，临时素材和身份透露顺序；北观察员前后对白。
- [ ] 男女/三种御三家六条劲敌队伍分支、黑白、Fly入包失败后的重谈不重战；Scott与茵郁推进保留。
- [ ] 商人Fly前后开放，时间球及6EV树果无限；6石单次2或1+1，耗尽售罄、取消/缺钱/满包不减库存、卖出不返库存，进化石限1、茵郁奇迹种子限1。
- [ ] 茵郁原树桥/树屋通路、风筝/邮递/地图精灵叫声；大吾/侦测镜/桥上与城内原变隐龙，道馆旋转门、娜琪五只无Mega、徽章6与原TM。
- [ ] 120护卫初次提示/再谈同意或拒绝/胜后让路、旧石碑晴雨差异、可选强敌与原Ancient Tomb Chip战后波士可多拉石满包回领。
- [ ] 120北湖三种竿钓鱼/其他水域保持原表，爱心鱼普通50%心之鳞片；渔夫三暴鲤龙和生日任务。
- [ ] 水静女孩拒绝/没有鱼/鱼蛋/持物（含邮件）/多鱼/只剩唯一可战斗伙伴/其他全濒死；成功实际减少恰好一只、队伍压紧、女孩旁叫声NPC，父亲 Mega 石满包再领。
- [ ] 灼热岩洞封印一周目和单纯冠军后都不开，原晴天TM可拿。授权开门/来历不明的研究数据只在未来获批Postgame实现后验收，本批无正常解锁入口。
- [ ] 暮水绅士不堵路：满队不给也不设Flag、空位古空棘鱼30一次、保存重谈不重复；不公开萨维尔身份。正式角色美术与最终难度评估后续处理。

## 修改文件完整清单

另在实施前保存 `docs/story/PART4_FINAL.md`（用户定稿原文，已纳入 pre-part4 检查点）。以下为后续实施差异。

- `DEV_LOG.md`
- `PART4_PETALBURG_FORTREE_IMPLEMENTATION.md`
- `PROJECT_BLUEPRINT.md`
- `data/event_scripts.s`
- `data/layouts/NewMauville_HighVoltage/border.bin`
- `data/layouts/NewMauville_HighVoltage/map.bin`
- `data/layouts/NewMauville_Maintenance/border.bin`
- `data/layouts/NewMauville_Maintenance/map.bin`
- `data/layouts/Route111/map.bin`
- `data/layouts/Route111_NoMirageTower/map.bin`
- `data/layouts/ScorchedSlab_SealedRoom/border.bin`
- `data/layouts/ScorchedSlab_SealedRoom/map.bin`
- `data/layouts/layouts.json`
- `data/maps/AbandonedShip_HiddenFloorRooms/map.json`
- `data/maps/AbandonedShip_Rooms_1F/map.json`
- `data/maps/DewfordTown/scripts.inc`
- `data/maps/FallarborTown/scripts.inc`
- `data/maps/FortreeCity/map.json`
- `data/maps/FortreeCity/scripts.inc`
- `data/maps/FortreeCity_Gym/scripts.inc`
- `data/maps/FortreeCity_House1/map.json`
- `data/maps/FortreeCity_House1/scripts.inc`
- `data/maps/FortreeCity_Mart/scripts.inc`
- `data/maps/LavaridgeTown/scripts.inc`
- `data/maps/LilycoveCity/map.json`
- `data/maps/LilycoveCity/scripts.inc`
- `data/maps/MauvilleCity/scripts.inc`
- `data/maps/MauvilleCity_BikeShop/scripts.inc`
- `data/maps/MirageTower_1F/map.json`
- `data/maps/NewMauville_Entrance/map.json`
- `data/maps/NewMauville_HighVoltage/map.json`
- `data/maps/NewMauville_HighVoltage/scripts.inc`
- `data/maps/NewMauville_Inside/map.json`
- `data/maps/NewMauville_Inside/scripts.inc`
- `data/maps/NewMauville_Maintenance/map.json`
- `data/maps/NewMauville_Maintenance/scripts.inc`
- `data/maps/PacifidlogTown/map.json`
- `data/maps/PacifidlogTown/scripts.inc`
- `data/maps/PetalburgCity/map.json`
- `data/maps/PetalburgCity/scripts.inc`
- `data/maps/PetalburgCity_Gym/scripts.inc`
- `data/maps/PetalburgCity_PokemonCenter_1F/map.json`
- `data/maps/PetalburgCity_WallysHouse/scripts.inc`
- `data/maps/Route108/map.json`
- `data/maps/Route111/map.json`
- `data/maps/Route114_LanettesHouse/scripts.inc`
- `data/maps/Route115/map.json`
- `data/maps/Route118/map.json`
- `data/maps/Route118/scripts.inc`
- `data/maps/Route119/map.json`
- `data/maps/Route119/scripts.inc`
- `data/maps/Route119_WeatherInstitute_1F/map.json`
- `data/maps/Route119_WeatherInstitute_2F/map.json`
- `data/maps/Route119_WeatherInstitute_2F/scripts.inc`
- `data/maps/Route120/map.json`
- `data/maps/Route120/scripts.inc`
- `data/maps/Route123/map.json`
- `data/maps/ScorchedSlab/map.json`
- `data/maps/ScorchedSlab/scripts.inc`
- `data/maps/ScorchedSlab_SealedRoom/map.json`
- `data/maps/ScorchedSlab_SealedRoom/scripts.inc`
- `data/maps/SlateportCity/scripts.inc`
- `data/maps/SlateportCity_OceanicMuseum_1F/scripts.inc`
- `data/maps/map_groups.json`
- `data/scripts/hall_of_fame.inc`
- `data/scripts/part4.inc`
- `data/scripts/players_house.inc`
- `data/specials.inc`
- `docs/ai-handoff/CANON_DECISIONS.md`
- `docs/ai-handoff/CHANGELOG.md`
- `docs/ai-handoff/CURRENT_TASK.md`
- `docs/ai-handoff/PROJECT_STATE.md`
- `docs/project/part4-capacity.json`
- `docs/project/part4-manifest.json`
- `docs/project/part4-verification.json`
- `include/constants/flags.h`
- `include/constants/items.h`
- `include/constants/opponents.h`
- `include/constants/part4.h`
- `include/constants/trainers.h`
- `include/constants/vars.h`
- `include/limited_shop.h`
- `include/part4.h`
- `scripts/build.sh`
- `scripts/tests/check-chinese.py`
- `scripts/tests/check-part1.py`
- `scripts/tests/check-part2.py`
- `scripts/tests/check-part3-data.py`
- `scripts/tests/check-part3-west.py`
- `scripts/tests/check-part4-core.py`
- `scripts/tests/check-part4.py`
- `scripts/tests/check-route102-petalburg.py`
- `scripts/tests/part4_compat.py`
- `scripts/tests/test-opening.py`
- `src/battle_main.c`
- `src/data/items.h`
- `src/data/trainers.party`
- `src/data/wild_encounters.json`
- `src/limited_shop.c`
- `src/part4.c`
- `src/shop.c`
- `src/wild_encounter.c`
