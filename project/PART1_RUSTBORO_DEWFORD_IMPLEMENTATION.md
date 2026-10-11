# PART1：104号道路—武斗镇实施与验收

2026-10-06。以用户part1.txt为本批范围；保持1.17.1及现有中文底座和开局。终端静默实施，禁止GUI/模拟器/ROM运行。

## 1. 修改文件清单

权威工程 `/home/pokemon/projects/emerald-story`（Windows UNC `\\wsl.localhost\Ubuntu-24.04\home\pokemon\projects\emerald-story`）。固定官方1.17.1，实施前tag `pre-part1-implementation`，当前branch `project/part1`。

- `OPENING_IMPLEMENTATION.md`
- `PROJECT_BLUEPRINT.md`
- `data/event_scripts.s`
- `data/layouts/RusturfTunnel/map.bin`
- `data/maps/DewfordTown/map.json`
- `data/maps/DewfordTown/scripts.inc`
- `data/maps/DewfordTown_Gym/scripts.inc`
- `data/maps/GraniteCave_1F/map.json`
- `data/maps/GraniteCave_1F/scripts.inc`
- `data/maps/GraniteCave_B1F/map.json`
- `data/maps/GraniteCave_B1F/scripts.inc`
- `data/maps/GraniteCave_B2F/map.json`
- `data/maps/GraniteCave_StevensRoom/scripts.inc`
- `data/maps/PetalburgWoods/map.json`
- `data/maps/PetalburgWoods/scripts.inc`
- `data/maps/Route104/map.json`
- `data/maps/Route104/scripts.inc`
- `data/maps/Route104_MrBrineysHouse/map.json`
- `data/maps/Route104_MrBrineysHouse/scripts.inc`
- `data/maps/Route104_PrettyPetalFlowerShop/map.json`
- `data/maps/Route104_PrettyPetalFlowerShop/scripts.inc`
- `data/maps/Route116/map.json`
- `data/maps/Route116/scripts.inc`
- `data/maps/RustboroCity/map.json`
- `data/maps/RustboroCity/scripts.inc`
- `data/maps/RustboroCity_DevonCorp_1F/map.json`
- `data/maps/RustboroCity_DevonCorp_1F/scripts.inc`
- `data/maps/RustboroCity_DevonCorp_3F/scripts.inc`
- `data/maps/RustboroCity_Gym/scripts.inc`
- `data/maps/RustboroCity_PokemonSchool/map.json`
- `data/maps/RustboroCity_PokemonSchool/scripts.inc`
- `data/maps/RusturfTunnel/map.json`
- `data/maps/RusturfTunnel/scripts.inc`
- `data/scripts/part1.inc`
- `data/specials.inc`
- `docs/project/part1-manifest.json`
- `include/config/battle.h`
- `include/config/item.h`
- `include/constants/flags.h`
- `include/constants/opponents.h`
- `include/part1.h`
- `scripts/build.sh`
- `scripts/tests/check-chinese.py`
- `scripts/tests/check-part1.py`
- `scripts/tests/check-route102-petalburg.py`
- `scripts/tests/test-opening.py`
- `src/battle_script_commands.c`
- `src/data/trainers.party`
- `src/data/wild_encounters.json`
- `src/item_use.c`
- `src/limited_shop.c`
- `src/part1.c`
- 本实现文档、`DEV_LOG.md` 也随本批更新。

## 2. 104号道路旅行训练家

Youngster 洋平，普通 `OBJ_EVENT_GFX_YOUNGSTER`（24,60），朝右、视距2，Trainer ID856，预留MAX864不变。喵喵Lv5、尾立Lv5，IV0、无道具、正常AI；自然旅行/家乡空气对白，只有正常战斗奖金，没有额外特殊奖励。定义集中在 `TRAINER_PART1_ROUTE104_TRAVELER`，后续容易改名或更换队伍。

## 3. 橙华森林观察者

入口老人 `OBJ_EVENT_GFX_EXPERT_M`（21,35），安静/潮湿/孢子对白。复用 `checkspecies SPECIES_SHROOMISH`，队伍有蘑蘑菇追加伙伴对白，无奖励、无核心系统侵入。检测沿用原生种类检测（包含种类仍是蘑蘑菇的蛋，不检查PC）。

## 4. 刺尾虫支线

孩子（18,35）；可选固定地图刺尾虫（18,31）。选择否保持原状；选择是设置GUIDED、移除原对象、显示孩子旁的刺尾虫（19,35）。重新进图以原临时Flag恢复显示，既不捕获也不占队伍。友好刺尾虫只播放叫声。孩子只有GUIDED后赠银粉1，成功才设置RECEIVED_SILVER_POWDER，满包保留；前置、失败、成功和重复领取分支通过脚本检查。

## 5. 花店每日树果

新增普通店员（2,3），先与原店主见面才能领取。使用 `dotimebasedevents` 和原RTC每日Flag清理；随机六选一：樱子果、零余果、桃桃果、莓莓果、利木果、橙橙果，各1/6，每天新增礼物1枚。成功后设置0x925，满包不消耗机会。原店主、水壶、原店员每日赠礼和未来店主移动完整保留；新增礼物与原有每日赠礼是两份独立配额。

## 6. 学习装置实现

复用原 `ITEM_EXP_SHARE`，配置 `I_EXP_SHARE_ITEM=GEN_6`，进入重要道具栏、不可出售；已有中文描述为同行共享经验。领取复用 `FLAG_RECEIVED_EXP_SHARE`，开启独立0x26。户外老师（29,20）、道馆门前（27,20）坐标触发；道馆进门一次性兜底和杜鹃对战前兜底确保先领取。满包不给Flag，允许找老师或重进图/再对话补领。重要道具使用弹游戏内“是/否”确认，否/B取消不切换，背包和注册快捷键两种上下文都有关闭回调。

## 7. 默认开启

成功领取时同时设置原领取Flag和0x26，默认开启。所有老师后续对白读取当前开关，不强行开启玩家主动关闭的装置。没有新增保存结构或字段；旧存档既有Flag仍兼容。旧档若在本批之前已经领取过原版携带式学习装置，不会自动重发或重置其开关/袋内位置；本批完整流程以新档验收，旧档保留备份后测试。

## 8. 100%/50%经验

`Cmd_getexp` 计算原基础经验（种族expYield×对手等级/7，原适用训练家倍率仍保留），交给实际 `CalculatePart1ExpShares`。开启时每个存活参战者各取base，不按参战人数分；每个有效后台各取floor(base/2)，不按后台人数分，不扣参战经验，也不给参战者再叠50%。原蛋/濒死/满级过滤和个人正常倍率保持。关闭后base按有效参战人数传统分摊；旧存档携带式装置的传统半份规则仍兼容。整数极小经验沿用最小1；原道具/亲密度等奖励倍率照常。`B_SPLIT_EXP=GEN_3`、`B_SCALED_EXP=GEN_3`；caps.h未动，`EXP_CAP_NONE`、无等级差惩罚。原经验战斗动画/升级流程保持。

## 9. 训练家学校

新问答学生（0,6），原学校黑板/老师先制之爪/学生/亚希达事件保留。日题为原RTC dailySeed%3：水克岩、解毒药不治麻痹、濒死不能战斗。正确赠橙橙果1，答错解释正确答案，可再答；0x924记录当日正确待领，满包不设0x923，空位后直接补领。原每日Flag统一清理；跨日重置答对/领奖。学校老师追加当前开关说明，并尊重关闭状态。

## 10. 杜鹃最终队伍/技能

| 宝可梦 | 等级 | 技能 | 携带 |
| --- | --- | --- | --- |
| Geodude | 13 | Rock Tomb, Defense Curl, Tackle, Rock Polish | 无 |
| Anorith | 14 | Fury Cutter, Smack Down, Water Gun, Harden | 无 |
| Nosepass | 15 | Rock Tomb, Thunder Wave, Tackle, Harden | Oran Berry |

三只均IV12，EV默认0，保持原馆主基础AI和原治疗药品（杜鹃2疗伤药、藤树2好伤药），不使用完美配置、天气套路或等级上限。等级招式或当前teachables已逐项核对；Rock Tomb/Bulk Up为合法TM。藤树当前Gen9学习表没有Meditite的Meditate，因此用合法Work Up；Machop的Low Kick/Knock Off符合当前表。初次队伍改动，所有再战队伍未动。徽章/TM/道馆谜题原流程保持。

## 11. 116号道路

施工人员（44,10）说明照顾当地生态暂停施工；年轻矿工（50,13）与地图可可多拉（51,13）。救回小皮/追回货物（原FLAG_RECOVERED_DEVON_GOODS）后才赠硬石头1，成功后0x27；满包重试。磁场、工具吸附只是自然环境说明，没有组织伏笔。可可多拉仅原物种叫声。

## 12. 卡绿隧道遭遇率

草地/洞穴槽实际总权重：咕妞妞80%、可可多拉10%、铁哑铃10%。land encounter_rate原10保留；槽权重20/20/10/10/10/10/5/5/4/4/1/1，第2/3槽分别设置Aron/Beldum。没有改变其他地图或该图其他遭遇方法。

## 13. 实际等级

可可多拉、铁哑铃均8–10级；咕妞妞保持原槽5–8级。没有人为压低铁哑铃概率或修改其种族数据。

## 14. 隧道采集与封闭支路

星星沙（6,1）、硬石头（6,8）各1，独立Flag，成功拾取立即移除对象，满包留在地图。封路岩石（10,4）为普通现有岩石模型、独立只读脚本，不能碎岩或提前解锁；后面（10,3）仅新增一格可见地面，不创建未来区域或warp。完整布局只有这一个格子改变，连通性证明封路时该格不可达。救援后出现3只地图咕妞妞（5,8）、（7,5）、（18,5），只有叫声，重进图恢复。

## 15. 得文与乘船对白

1F新增普通员工（6,6）与可可多拉（7,6），精灵球制造、矿石处理、社长爱石头与大吾爱旅行/搜石头的轻松对白，正常合作伙伴介绍。社长请求送信/送货文案自然扩展感谢与差事，原导航/信/货物发放指令保持；已由学校领取学习装置时不重复发。哈奇屋旧航海图（3,2）只读；驶往武斗前小皮叫声及活泼出航对白，不改航线或动画时长。

## 16. 武斗限购潜水球

武斗原版没有商店，新增港口旅行用品商人（5,12）最小复用现有pokemart，不新增室内地图。普通精灵球/疗伤药/解毒药，加潜水球。`sLimitedShopItems` 追加 `{ MAP_DEWFORD_TOWN, ITEM_DIVE_BALL, FLAG_PART1_BOUGHT_DEWFORD_DIVE_BALL }`，0x28。原价格、扣钱、背包容量、数量最多1和成功付费后置Flag/售罄机制与古辰一致。没改潜水球道具数据；古辰限购高级球不受影响。以后同样追加地图/商品/Flag三元组即可。

## 17. 漂亮贝壳

孩子（15,12），海岸探索拾取标记（18,10），沿用已有道具球模型使调查位置可见。贝壳只用0x29表示，不添加新道具；找到后标记立即消失，回孩子处赠珍珠1，成功才0x2A，满包保留找到/领取资格。再次对话只有感谢，不追加剧情。

## 18. 石之洞窟照明

1F/B1F/B2F/StevensRoom四张map.json均requires_flash=false。地图生成器将其映射到gMapHeader.cave=false，原SetDefaultFlashLevel在进图/换层时清flashLevel为0；原系统照明和其他洞窟不改。藤树道馆的原黑暗谜题与照亮进度保持。

## 19. 闪光山男

原山男/原HM_FLASH/原FLAG_RECEIVED_HM_FLASH保留。改为复杂岩壁、强光/发现异常、旅行备用说明，不声称本洞必须闪光。新增失败跳转保证满包不设领取Flag、仍可重试；其他区域的闪光功能不改。

## 20. 石之洞窟最终分布

四层统一10–12级陆地表：幕下力士30%、超音蝠30%、大嘴娃10%、凯西10%、沙瓦郎5%、大岩蛇5%、朝北鼻5%、勾魂眼5%。保留原遭遇频率和其他方法；可可多拉/铁哑铃不在新增陆地表。1F星星沙（14,4）、B1F不变之石（8,12）各1，成功立即消失，满包重试；1F金属颗粒岩壁（11,6）只读。未新做美术或精灵跟随系统。

## 21. 大吾彩蛋与送信

复用 `checkspecies SPECIES_BELDUM`，仅当前队伍有铁哑铃时追加培养/珍惜对白，不检查PC，没有额外奖励或Mega手环。原送信/钢翼TM/宝可导航登记/离场保持。修复钢翼满包后仍离场的原失败流程：若信已交但TM未发成功，NPC留场，重试直接发TM，不重复收信；成功后才登记并离场。

## 22. 藤树最终队伍/技能

| 宝可梦 | 等级 | 技能 | 携带 |
| --- | --- | --- | --- |
| Machop | 17 | Low Kick, Leer, Knock Off, Focus Energy | 无 |
| Meditite | 18 | Confusion, Force Palm, Detect, Work Up | 无 |
| Makuhita | 19 | Force Palm, Arm Thrust, Fake Out, Bulk Up | Oran Berry |

三只均IV12，EV默认0，保持原馆主基础AI和原治疗药品（杜鹃2疗伤药、藤树2好伤药），不使用完美配置、天气套路或等级上限。等级招式或当前teachables已逐项核对；Rock Tomb/Bulk Up为合法TM。藤树当前Gen9学习表没有Meditite的Meditate，因此用合法Work Up；Machop的Low Kick/Knock Off符合当前表。初次队伍改动，所有再战队伍未动。徽章/TM/道馆谜题原流程保持。

## 23. 本批Flags及临时状态

原0x20–0x23四个开局Flag完全保持。新增分配均先核对原空闲槽、删除原UNUSED别名、全项目唯一数值检查。无新增永久VAR/存档结构。

| 常量 | 值 |
| --- | --- |
| `FLAG_PART1_WURMPLE_GUIDED` | `0x24` |
| `FLAG_PART1_RECEIVED_SILVER_POWDER` | `0x25` |
| `FLAG_PART1_EXP_SHARE_ENABLED` | `0x26` |
| `FLAG_PART1_RECEIVED_MINER_HARD_STONE` | `0x27` |
| `FLAG_PART1_BOUGHT_DEWFORD_DIVE_BALL` | `0x28` |
| `FLAG_PART1_FOUND_PRETTY_SHELL` | `0x29` |
| `FLAG_PART1_RECEIVED_SHELL_PEARL` | `0x2A` |
| `FLAG_PART1_RUSTURF_STARDUST` | `0x2B` |
| `FLAG_PART1_RUSTURF_HARD_STONE` | `0x2C` |
| `FLAG_PART1_GRANITE_STARDUST` | `0x2D` |
| `FLAG_PART1_GRANITE_EVERSTONE` | `0x2E` |
| `FLAG_DAILY_PART1_SCHOOL_REWARD` | `0x923` |
| `FLAG_DAILY_PART1_SCHOOL_SOLVED` | `0x924` |
| `FLAG_DAILY_PART1_FLOWER_BERRY` | `0x925` |

复用原FLAG_RECEIVED_EXP_SHARE（0x110）、FLAG_RECOVERED_DEVON_GOODS、FLAG_DELIVERED_STEVEN_LETTER、FLAG_REGISTERED_STEVEN_POKENAV。FLAG_TEMP_C仅在森林和隧道各自进图重设；VAR_TEMP_F仅城市/道馆老师触发，离图/进图重设。每日三个Flag位于原ClearDailyFlags清理区，不增加时钟字段。新Trainer856击败状态在预留区内，不扩MAX864。

## 24. 普通构建

以 `BUILD_JOBS=4 bash scripts/build.sh` 运行，构建及四套检查均成功；输出 `D:\Pokemon gba\artifacts\current\pokeemerald.gba`，32MiB。仅复制产物，没有执行ROM。

## 25. Release构建

以 `BUILD_JOBS=4 bash scripts/build.sh --release` 运行，构建及四套检查均成功；输出 `D:\Pokemon gba\artifacts\current\pokeemerald-release.gba`，32MiB。历史上游/中文层warning另存日志，不修改无关系统。

## 26. 检查范围与边界

`check-chinese.py`、`test-opening.py`、`check-route102-petalburg.py`、`check-part1.py` 自动执行。保存ABI、82698非文本物种/道具/技能字段、6771字库覆盖、10702中文汇编块宽度、名字字节预算、Poryscript实际中文编译、原四奖励与商店事务检查保持。新增检查：14Flag空闲/唯一、24对象碰撞/朝向/通路/原视线、原warp及事件、封路不可达、原主线指令、五遭遇表实际权重/等级、馆主合法招式/其他训练家未改；实际C函数检查100/50/关闭分摊、蛋/濒死过滤、日题种子；读取真实脚本指令验证8类礼包满包/补领/重复、刺尾虫选择、3题答对/答错/跨日、6随机树果。对象视窗检查未扩大原版已有密集窗口。脚本分支检查器只检查事件指令，不模拟游戏/地图动画；不能代替人工游戏内测试。

## 27. 需要人工使用mGBA测试以下内容

本次未启动任何GUI、模拟器或ROM。

- 新档正常流程：未白蛋/古辰限购/埃文万能药/橙华雷伊布与赠石仍正常；104号道路旅行对战不挡原NPC视线。
- 森林刺尾虫选择否、选择是、进出地图/存读档、满包银粉再领；原水舰队/得文研究员/原超级球照常。
- 花店原水壶/原树果/新增每日树果；学校问答答错、答对满包、当日补领、RTC跨日各仅一枚。
- 走向杜鹃道馆触发老师，满重要道具袋重试，默认ON；背包使用与注册快捷键的确认/取消/否/B、老师尊重OFF；2个参战+若干后台+蛋+濒死队伍实际经验分别100/50/0/0，关闭后恢复传统分摊，正常升级/进化。
- 杜鹃/藤树新队伍、技能与战败对白，原徽章/TM/道馆谜题；原亚希达/居合劈/抓货物/导航教程不被卡住。
- 隧道可可多拉/铁哑铃/咕妞妞遭遇、小皮救援/声音、三咕妞妞出现/不挡路、封路不能碎岩进入、满包两采集点重试。
- 哈奇旧图/航船正常；武斗流行词与钓竿正常；潜水球钱不够/取消/满包/买1后售罄/读档后仍售罄且古辰库存独立。
- 贝壳可见拾取点/一次性珍珠满包补领；石之洞窟四层无黑暗、上下楼/用逃洞绳/进出后照明正常、闪光仍可领；两采集点满包重试与金属岩壁无功能。
- 大吾带/不带铁哑铃分别对白；正常收信钢翼登记离场、TM袋满留场、重新进图后补领不重复收信；中文分页/滚动无乱码或溢出。


## 最终产物记录

- `pokeemerald.gba`：32MiB，SHA256 `287e69d4068f959bf848d0761e353e63ed47a9dd8bc6cc91e58ee3678b9f39da`，日志 `D:\Pokemon gba\logs\part1-normal-final.log`。
- `pokeemerald-release.gba`：32MiB，SHA256 `8ef2f6cd5868eed88b4cf08e1b6324a1c8759ced16f3bd6e94efaeed5fe5ced0`，日志 `D:\Pokemon gba\logs\part1-release-final.log`。

两个构建命令最终返回0；没有本批编译错误，已知上游/中文层warning保留。全部检查通过，但未执行游戏内验收。
