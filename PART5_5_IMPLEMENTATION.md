# PART5.5 实施报告

2026-10-07，执行 AI：Codex。基础 RHH Expansion 1.17.1，分支 project/part5。

状态：**DESIGN CONFIRMED / IMPLEMENTED**。PART5 和 PART5.5 文稿仍为 **DRAFT**，没有创建 PART5_FINAL。构建/静态验证单独记录；**游戏内人工验收 PENDING**，没有启动 GUI、模拟器或执行 ROM。

## A. 协作状态

开始时工作区干净，HEAD=8c6394cd8f（Claude 已提交的 PART5）。保存 pre-part5-5-implementation 标签；没有 checkout/reset/clean/stash 或覆盖未提交修改。所有新增内容以此基线登记在 docs/project/part55-deltas.json，旧 PART5 增量清单保持原样。当前交付提交以 git log 为准。

PART5 所需地图和系统均存在，无依赖 BLOCKED。呆壳兽进化石按用户条件暂缓：当前开放丰缘范围没有合理的呆呆兽来源，FRLG 表不等于玩家现阶段可获取。海底异常任务仅接取，完成属于未来 PART6；二周目仅保留钥匙钩子。

## B. 121 / Safari

- 121：三名货运休息点普通工作人员，不新增主线 Warp；另有电源模块任务拾取点。
- 记录册：原野区西北角记录册 → 入口护林员 → PP Up ×1，交付成功才消费记录册/完成。
- 大针蜂：依次调查三处树边，记录观察；第三处可自愿触发原生 Safari 大针蜂 Lv30 遭遇。使用 Safari Ball 和原生出球/退出回调，保留步数、捕获计数；回护林员得 Beedrillite ×1。普通 dowildbattle 会转成普通野战，因此此处有一个小型 Safari 回调适配。
- 袋兽：图鉴已见过袋兽/吉利蛋/肯泰罗三者后自愿挑战原野区专家；胜利获得 Kangaskhanite ×1，满包重领，不要求永久交出宝可梦。
- 生态：只替换四张原野区表的第 10 号重复槽，分别增加独角虫、吉利蛋、肯泰罗、袋兽；原唯一物种以及 PART5 坐骑小羊/小约克/毛头小鹰槽保留。真实捕获、球数归零和步数到期仍须人工验证。

## C. 水静市

港口原潜艇流程保留；公告与等船父女按港口/潜艇原状态改变，不揭露组织深层信息。海滨运输清单交回港口 → 金珠1；旅馆错拿行李 → 港口换正确行李 → 旅馆全复药1；旅馆纪念品送游客 → 高级球3。均检查实际任务物品，满包不交出、不完成。

独自旅行少年与伊布按不同回访推进：想家、打电话、转去原野区入口；母子按二楼孩子/五楼母亲/返回孩子推进 → 神奇糖果1，母亲回二楼后五楼隐藏；老人从百货指路后移至港口。所有重新加载后位置和显隐需人工验收。

保留原购物清单、送午饭、母女丝带沙奈朵石任务；追加第一次工资、买错装备、博物馆游客与临摹学生（原生展画识别）、比赛失利者/摄影者/幕后工作人员、演奏者与吼爆弹。

新增布料 → 海滨服装设计师与卷卷耳 → Lopunnite1；抓痕与粉末 → 宝石发现点/可选勾魂眼普通遭遇 → 咬痕石 → 原海滨珠宝摊 → Sablenite1。

三角攻击与帮助使用 Expansion 原生 move_tutor，省略一次性 Flag，免费、可重复；兼容性/已学技能/取消交回原菜单处理。教学 NPC 在园区交流馆。

原实用柜台追加白色香草、心灵香草、强力香草、烟雾球、光之黏土、潮湿/炽热/沙沙/冰冷岩石、红牌、逃脱按键。原高级竞技装备限购表未改变，不新增普通 Mega 石商店。

## D. 海滨大道 / 阿尔刻园区

**PLACEHOLDER ART — FUTURE VISUAL PASS**：沿用 PART5 园区与海滨的原版素材占位；本批只新增两个 10×12 原生洞穴素材小通道。制服、正式城市布局、美食/商品美术、精灵正式演员尺寸以后统一处理。

海滨三类街头摊位（食物/纪念品/旅行用品）；园区食堂沿用已有 Cafe，三位用餐者讨论咖喱等生活细节。新员工按三次地图回访推进第一天感想；居民有租金、安静与外来协作者观点。

员工证在园区公共区域拾取 → 总部持证人 → PP Up1；总部二楼封装药送公寓病人 → 高级伤药3，后续送药友人移到公寓。公寓一楼有售货机说明、周三维护通知、厨房宠物告示及快递人员，楼上保持关闭。

总部研究点地图明确水静是丰缘总部；三类公开展位为封闭环境测试、生命参数、古代文字数字化，不出现传奇试验或具体实验对象。总部二楼开放三个接收窗口：液体、细胞、拓片；物流站每次仅携一箱，送错不消费，三箱完成后神奇糖果2一次。

怪力在物流站、电龙在总部二楼工作，互动只叫声。121电源模块交技术员 → Ampharosite1。物流站侧门维护沟：龙头地鼠 Lv35 普通固定战，击败或捕获后真正打开排水口；逃跑/失败可重试；师傅给 Steelixite1。

多边兽：程序员接任务 → 总部一楼/交流馆/总部二楼三个终端顺序修复 → Lv30 普通多边兽。最后终端即时显示地图多边兽。队伍满保留阶段4，绝不送 PC；成功入队才阶段5并更新图鉴。

无聊保安按实际来访次数变化；地下电梯只有权限说明，无 Warp/授权。原公开三项训练保留；第七徽章后可选高级测试（Mega恰雷姆）→ 特性膏药1。食堂/训练/接待的原 NPC 增加七徽章认可后继续原对话。中心2F、公寓高层均仍未开放。

## E. 送神火山

增加三块生活墓碑、三种留言选择与持久记录、老人彼岸花任务的脚印/花卉补充、守墓人正常/危机/平息/殿堂状态对白。平息用原领取攀瀑标记判断，不要求捕获可选神兽。

诅咒娃娃石改为完整旧玩偶故事：原地面石对象改为怨影娃娃；叫声/旧玩偶、让开位置、交回孩子与祖母 → Banettite1。继续使用 FLAG_PART5_BANETTITE，旧存档已拿过不会再发石。成功交付奖励后消费玩偶；满包不丢。怨影娃娃移到原生可通行且不是交互玩家所在的斜侧位置（10,25），重新加载保持位置。

原阿勃梭鲁任务、彼岸花奖励和二周目未授权墓碑入口保留。

## F. 火岩队 / 胖丁新人

122附近可自愿与女新人临时合作，只对付两名水舰队成员；没有背叛火岩队、与玩家秘密结盟或公开身份。Route122 岛上没有四个可靠的干地演员位置，因此场景放在紧邻的送神火山外部侧区；不修改122主通路。真实 Multi Battle，使用原生选三只/备份恢复队伍流程。

搭档胖丁 Lv35 @进化奇石，六项IV31，本次只有胖丁，因此始终最高等级、永不进化。对手 A：利牙鱼32、大嘴鸥33；B：臭臭泥32、铁螯龙虾33，均无Mega。战斗胜利才合作完成 Flag，输后白屏回家，未完成可重试。原基地正式第二战阵容/等级保留，合作过才追加回忆。

基地加入同事被胖丁打败的反应、胖丁纯叫声与新人前后评论、便当/手套/轮班/硬石头生活点；原战斗和高层危险性不改。固拉多苏醒后增加恐惧与嘴硬成员。

小救援通道：操作开关真正打开岩板 → 救队员/戴鲁比 → Houndoominite1；无需额外战斗。成功入包才阶段3。苏醒后的出口反应中，若此前满包保留阶段2，则先补领石头、成功后才离开；不能把待领取奖励藏掉。房内与出口演员分阶段互斥。

## G. 水舰队

在原基地加入晕船成员与同事、宠物粮与漏吃午饭的反差、湿袜子/防水袋/便当/轮班/床边空瓶调查。明信片无署名、仅调查文本，不给道具、不绑定平安符男友。晕船原成员仍进入原战斗，不跳过主线。

平安符男友的离开只补犹豫、朝北、短暂停顿再进入原归还/离开流程；原 Storage 粮食员工与 Sharpedonite、小海屋等流程保留。

## H. 124水路

可重复免费恢复；弯斜浮标、球飞鱼叫声与离开、调整浮标后向观测员领取潜水球5一次。

海底异常：本批可接取，记录0/3，完成点等待PART6；不解释温流/海流/残留与神兽或阿尔刻的因果。原四色碎片兑换人不复制；每次原兑换成功记录相应颜色位，四色全交至少一次=15。呆壳兽石 PENDING：当前丰缘没有合理的呆呆兽来源，未凭空添加种族/奖励。

## I. 绿岭 / 125 / 浅滩洞穴

绿岭地质游客、火箭倒计时爱好者、下班研究员、看星星者与打瞌睡朋友、航海老人；宇宙中心原阿尔刻联络人补合作站说明，无重复独立科研楼。

校准星图：三处（海面、原白色岩石、宇宙中心外）位记录 → PP Up1；紧急航空邮件由海滨邮差/大比鸟送宇宙中心 → 收条交回 → Pidgeotite1。原长翅鸥邮递任务不替换、不合并。

白色岩石：原岩石及其调查点，轻微原生 sparkle/音效、{PLAYER}感受温暖力量/星光，取得重要道具“星之钥匙”；两侧调查共用一次性状态，同时可记录星图观察。不可丢弃出售，一周目不解释用途。女孩/父亲和中心训练家有轻度反应。

125固定闪光幼牙龙（当前中文种族名牙牙）Lv34：原生随机野生创建，仅攻击IV改31与原生shinyModifier设闪光，其他IV/性格/性别/特性/PID不固定。失败/逃跑/击败/白屏不设置捕获Flag，离图重载可再战；成功捕获永久完成，不在殿堂重生。观察者/咬痕石按玩家是否携带同一PID+OT的牙牙/斧牙龙/双斧战龙反馈。

原贝壳之铃仍四贝壳+四海盐、可重复制作；第一次成功后记录资格，冰室的冻石交原老人 → Glalitite1，之后回正常制铃。冰室三处结晶调查、研究员/雪笠怪 → Abomasite1；潮汐不改。七徽章后灵能力研究员可选四只普通队伍挑战 → Alakazite1；原七夕青鸟石支线保留。

## J. Mega战斗

第七馆仍原生合法双打，同一个道馆训练家拥有一次Mega。六只最终队伍如下：天然鸟40、念力土偶41、太阳岩42、沙奈朵41、月石42、胡地43@胡地进化石。经典四只保留、双墙/顺风与普通覆盖，无完美EV或道具锁死。

高级测试：青铜钟42、路卡利欧43、恰雷姆44@恰雷姆进化石。灵能力研究员：太阳伊布41、麒麟奇41、青铜钟42、胡地43，无Mega。

宇宙中心仅提前回填明确队伍，原主线触发门槛未改：大吾 巨金怪45@巨金怪进化石/盔甲鸟43/波士可多拉44；赤焰松 大狼犬43/叉字蝠44/喷火驼46@喷火驼进化石；火村 大狼犬42/大嘴蝠43/喷火驼44，无Mega。事后普通亲子、联络人、居民有状态反应。

使用 Expansion 原生按训练家所有权计算的 Mega 次数，不另造Mega引擎。普通双打两席共享次数；Multi玩家/大吾各一次；两名对手分别计数；大吾无需借玩家手环资格。宿主测试提取实际 CanMegaEvolve / HasTrainerUsedGimmick / SetGimmickAsActivated，验证这些分支与待激活限制。

新训练家不能扩现有864个存档败北位：新增六项ROM原生 BattlePartner名册（其中女新人为搭档），扩展对手败北结果映射到审计普通Flag。修正两处原生直接数组读取（队伍模式、遭遇音乐）和脚本败北读取；组队参数初始化先确定训练家模式，避免前一场野战影响选三只。普通0–863的旧Flag映射保持不变；存档结构不变。

## K. 二周目钥匙 / 命名

游戏内继续“熔岩标志”。正式物品“来历不明的研究数据”沿用原ItemID与领取Flag值，封印授权仍从不由本批设置，冠军不会自动打开。

锁定未来联系：彼岸花→骑拉帝纳/反转世界；星之钥匙→基拉祈/帝牙卢卡；研究数据→超梦。具体入口、传奇等级、剧情、起源、钥匙因果均未擅自实现。

旧研究物品名称和旧运行源码符号已从实际 src/data/include/地图事件删除；旧常量只在历史清单与精确逆向回归证据中保留以核对原基线，不是游戏文本/可用别名。原用户附件/ Git历史作为历史证据不重写。不得把历史名重新写回ROM。

## L. 技术 / 验证 / 人工清单

新增22永久Flag、37VAR、15惰性任务/重要道具、6个原生ROM训练家记录、2张小地图。实际新增/包装124演员、50调查点，涉及46地图（包含已有NPC包装）。精确文件与增量：part55-deltas.json；分配与任务：part55-manifest.json；碰撞/容量：part55-capacity.json；构建：part55-verification.json。

主要新文件：data/scripts/part55.inc、src/part55.c、include/part55.h、include/constants/part55.h、两个地图/布局、两套检查与严格part55_compat。旧未白镇蛋/古辰限购/橙华雷伊布、PART1–5回归与核心系统保留。

构建命令：bash scripts/build.sh；Release：bash scripts/build.sh --release。两者均只编译和检查，--run拒绝。Windows静默入口仍 scripts/dev.ps1 -Action Build / Release。产物 artifacts/current，不自动打开。

| 验证 | 结果 |
| --- | --- |
| normal / release | 返回0，各32MiB；GBA头与校验字节PASS；Windows镜像逐字节相同 |
| 新批静态/事件 | 58组PASS：分配、46地图/124演员/50调查点、314中文文本、满包/重领/乱序/一次奖励等 |
| 新批宿主原C | 8组PASS，ASan/UBSan：旧864败北位、扩展名册、组队初始化、Mega所有权、Axew、多边兽、图鉴、箱子、Safari回调 |
| 原批回归 | PART1–5及开局/中文基础，全15套检查在两个构建中均PASS；已授权差异先严格精确还原 |
| 游戏内测试 | PENDING；未运行ROM或启动任何GUI/模拟器 |

normal SHA256：`5c68aa567dba6b6a3975e02e2f6d93bbc3acb76021ba54b5ed40f62fd716cbd4`。

release SHA256：`147ebfa1433fbf219d4cc3da315b6838f89ee9b6e1fc2df870fd9b072f5881ed`。

Release仍有原未修改代码的newlib系统调用占位/LTO类型/神秘礼物读区警告；不是本批编译错误，但也不宣称完全零warning。相关代码与基线一致，本批未开启那些额外功能。日志保留原文。

需要人工使用 mGBA 测试以下内容（由用户自己启动）：

1. 旧存档升级、原主线到第七馆、Safari入口/球数/步数/最后一球捕获或逃走/出区重进；所有观察任务不重复发石。
2. 水静港口三个阶段、跨城行李/布料/药品/货单/邮件的乱序与满包；母子/少年伊布/老人回访显隐、存读档位置。
3. 园区每个门、两个小通道往返和原生阶梯出口、排水/救援开关的真实画面；队伍满时多边兽阶段4可重新领取；三箱错误窗口仍保留货物。
4. 中心2F、公寓高层和地下电梯未开放；第七徽章后的训练和认可对白。
5. 女新人临时组队选三只/战败/胜利/离图保存恢复，之后基地正式战与胖丁评论；阵容6V/进化奇石/最高等级；救援满包后出口重领、不提前离开。
6. 白色岩石两侧闪光/分页/一档一次、星图三点与收条回交；怪物地图叫声与演员大小。
7. 牙牙闪光、能力页攻击IV31与其他随机IV、正常捕获入队/PC、逃跑击败白屏后重进、捕获永久隐藏、进化后带同一个体触发评论。
8. 浅滩涨落潮、正常贝壳之铃反复制作/满包、两条冰室石奖励回领；诅咒娃娃旧存档不重复奖励/怨影娃娃移位。
9. 第七馆Mega胡地、进阶Mega恰雷姆；未来宇宙中心大吾/玩家分别Mega、赤焰松Mega喷火驼，普通双打同一训练家只一次。
10. 中文分页/菜单/名字长度、实际平衡、实际NPC视线与通行，美术仍占位。

### 美术 TODO

PLACEHOLDER ART — FUTURE VISUAL PASS：园区/海滨正式地图、员工制服/角色模型、女新人未来便服（发色不改）、员工宝可梦演员比例、星之钥匙/彼岸花等图标、两通道门/开关/排水表演统一美术。不把占位当最终画面验收。

### 新增永久 Flag

| 常量 | 数值 |
| --- | --- |
| FLAG_PART55_BATTLED_ROOKIE | 0x4df |
| FLAG_PART55_BATTLED_AQUA_OBSERVER_A | 0x4e0 |
| FLAG_PART55_BATTLED_AQUA_OBSERVER_B | 0x4e1 |
| FLAG_PART55_BATTLED_SAFARI_EXPERT | 0x4e2 |
| FLAG_PART55_BATTLED_ADVANCED_TRAINER | 0x4e3 |
| FLAG_PART55_BATTLED_PSYCHIC_RESEARCHER | 0x4e4 |
| FLAG_PART55_AXEW_CAUGHT | 0x4e5 |
| FLAG_PART55_STAR_KEY | 0x4e6 |
| FLAG_PART55_SHELL_BELL_CRAFTED | 0x4e7 |
| FLAG_PART55_HIDE_PORYGON | 0x4e8 |
| FLAG_PART55_HIDE_ELDER_PORT | 0x4e9 |
| FLAG_PART55_HIDE_EXCADRILL | 0x4ea |
| FLAG_PART55_HIDE_RESCUED_MAGMA | 0x4eb |
| FLAG_PART55_ROOKIE_TEAMUP_DONE | 0x4ec |
| FLAG_PART55_HIDE_ROOKIE_TEAMUP | 0x4ed |
| FLAG_PART55_HIDE_MAGMA_AFTERMATH | 0x4ee |
| FLAG_PART55_RESCUED_MAGMA_LEFT | 0x4ef |
| FLAG_PART55_HIDE_DEPT_MOTHER | 0x4f9 |
| FLAG_PART55_HIDE_PATIENT_FRIEND | 0x4fa |
| FLAG_PART55_HIDE_SAFARI_TRAVELER | 0x4ff |
| FLAG_PART55_KEY_GLIMMER_SEEN | 0x68 |
| FLAG_PART55_HIDE_BUOY_MANTYKE | 0xe9 |

### 新增 VAR

| 常量 | 数值 |
| --- | --- |
| VAR_PART55_AXEW_PID_LO | 0x40f8 |
| VAR_PART55_AXEW_PID_HI | 0x40f9 |
| VAR_PART55_PORYGON | 0x40fa |
| VAR_PART55_SHARDS | 0x40fb |
| VAR_PART55_BEE | 0x40fc |
| VAR_PART55_SAFARI_EXPERT | 0x40fd |
| VAR_PART55_MANIFEST | 0x40fe |
| VAR_PART55_LUGGAGE | 0x40ff |
| VAR_PART55_SOUVENIR | 0x4052 |
| VAR_PART55_SOLO_TRAVEL | 0x4055 |
| VAR_PART55_DEPT_CHILD | 0x4056 |
| VAR_PART55_FABRIC | 0x4059 |
| VAR_PART55_EMPLOYEE_BADGE | 0x405b |
| VAR_PART55_MEDICINE | 0x405c |
| VAR_PART55_MODULE | 0x405f |
| VAR_PART55_NEW_EMPLOYEE | 0x4061 |
| VAR_PART55_SAMPLE_BITS | 0x4062 |
| VAR_PART55_SAMPLE_CARRY | 0x4064 |
| VAR_PART55_SAMPLE_REWARD | 0x4065 |
| VAR_PART55_ADVANCED_PATCH | 0x4066 |
| VAR_PART55_ALAKAZITE | 0x4067 |
| VAR_PART55_UNDERWATER_OBSERVATION | 0x4068 |
| VAR_PART55_BUOY | 0x406a |
| VAR_PART55_FROZEN_STONE | 0x406b |
| VAR_PART55_ICE_CRYSTALS | 0x406c |
| VAR_PART55_ABOMASITE | 0x406d |
| VAR_PART55_NOTEBOOK | 0x406e |
| VAR_PART55_LOST_ELDER | 0x4070 |
| VAR_PART55_SABLE_CLUES | 0x4073 |
| VAR_PART55_SABLEYITE | 0x4075 |
| VAR_PART55_STAR_CALIBRATION | 0x4076 |
| VAR_PART55_AIR_MAIL | 0x4077 |
| VAR_PART55_STEELIX_REPAIR | 0x4078 |
| VAR_PART55_HOUNDOUR_RESCUE | 0x4079 |
| VAR_PART55_DOLL | 0x407a |
| VAR_PART55_MEMORIAL_MESSAGE | 0x407c |
| VAR_PART55_HQ_GUARD_VISITS | 0x407d |

### 新增任务物品（原879研究数据只改名不改ID）

| 常量 | ID |
| --- | --- |
| ITEM_STAR_KEY | 885 |
| ITEM_SHIPPING_MANIFEST | 886 |
| ITEM_WRONG_LUGGAGE | 887 |
| ITEM_CORRECT_LUGGAGE | 888 |
| ITEM_WRAPPED_SOUVENIR | 889 |
| ITEM_SOFT_FABRIC | 890 |
| ITEM_BITTEN_STONE | 891 |
| ITEM_EMPLOYEE_BADGE | 892 |
| ITEM_MEDICINE_PARCEL | 893 |
| ITEM_POWER_MODULE | 894 |
| ITEM_OLD_DOLL | 895 |
| ITEM_URGENT_AIR_MAIL | 896 |
| ITEM_DELIVERY_RECEIPT | 897 |
| ITEM_FROZEN_STONE | 898 |
| ITEM_RANGER_NOTEBOOK | 899 |

### 改动文件索引

- data/event_scripts.s
- data/layouts/layouts.json
- data/maps/AquaHideout_B1F/map.json
- data/maps/AquaHideout_Storage/map.json
- data/maps/ArcheCampus/map.json
- data/maps/ArcheCampus_Apartment/map.json
- data/maps/ArcheCampus_Apartment/scripts.inc
- data/maps/ArcheCampus_Cafe/map.json
- data/maps/ArcheCampus_ExchangeHall/map.json
- data/maps/ArcheCampus_FamilyHouse/map.json
- data/maps/ArcheCampus_HQ_1F/map.json
- data/maps/ArcheCampus_HQ_1F/scripts.inc
- data/maps/ArcheCampus_HQ_2F/map.json
- data/maps/ArcheCampus_HQ_2F/scripts.inc
- data/maps/ArcheCampus_Logistics/map.json
- data/maps/ArcheCampus_SeasideHouse/map.json
- data/maps/ArcheCampus_TrainingHall/map.json
- data/maps/LilycoveCity/map.json
- data/maps/LilycoveCity_ContestLobby/map.json
- data/maps/LilycoveCity_CoveLilyMotel_1F/map.json
- data/maps/LilycoveCity_CoveLilyMotel_2F/map.json
- data/maps/LilycoveCity_CoveLilyMotel_2F/scripts.inc
- data/maps/LilycoveCity_DepartmentStore_1F/map.json
- data/maps/LilycoveCity_DepartmentStore_1F/scripts.inc
- data/maps/LilycoveCity_DepartmentStore_2F/map.json
- data/maps/LilycoveCity_DepartmentStore_2F/scripts.inc
- data/maps/LilycoveCity_DepartmentStore_3F/map.json
- data/maps/LilycoveCity_DepartmentStore_5F/map.json
- data/maps/LilycoveCity_DepartmentStore_5F/scripts.inc
- data/maps/LilycoveCity_Harbor/map.json
- data/maps/LilycoveCity_Harbor/scripts.inc
- data/maps/LilycoveCity_LilycoveMuseum_1F/map.json
- data/maps/LilycoveCity_LilycoveMuseum_2F/map.json
- data/maps/LilycoveCity_SeasideAvenue/map.json
- data/maps/MagmaHideout_1F/map.json
- data/maps/MagmaHideout_1F/scripts.inc
- data/maps/MagmaHideout_2F_1R/map.json
- data/maps/MagmaHideout_2F_2R/map.json
- data/maps/MagmaHideout_3F_1R/map.json
- data/maps/MossdeepCity/map.json
- data/maps/MossdeepCity/scripts.inc
- data/maps/MossdeepCity_PokemonCenter_1F/map.json
- data/maps/MossdeepCity_SpaceCenter_1F/map.json
- data/maps/MtPyre_1F/map.json
- data/maps/MtPyre_2F/map.json
- data/maps/MtPyre_Exterior/map.json
- data/maps/MtPyre_Exterior/scripts.inc
- data/maps/MtPyre_Summit/map.json
- data/maps/MtPyre_Summit/scripts.inc
- data/maps/Route121/map.json
- data/maps/Route121_SafariZoneEntrance/map.json
- data/maps/Route121_SafariZoneEntrance/scripts.inc
- data/maps/Route124/map.json
- data/maps/Route124/scripts.inc
- data/maps/Route124_DivingTreasureHuntersHouse/scripts.inc
- data/maps/Route125/map.json
- data/maps/SafariZone_Northwest/map.json
- data/maps/SafariZone_South/map.json
- data/maps/ScorchedSlab_SealedRoom/map.json
- data/maps/ShoalCave_LowTideEntranceRoom/map.json
- data/maps/ShoalCave_LowTideEntranceRoom/scripts.inc
- data/maps/ShoalCave_LowTideIceRoom/map.json
- data/maps/SlateportCity/map.json
- data/maps/map_groups.json
- data/scripts/part4.inc
- data/scripts/part5.inc
- data/specials.inc
- include/constants/battle_partner.h
- include/constants/flags.h
- include/constants/items.h
- include/constants/opponents.h
- include/constants/vars.h
- src/battle_setup.c
- src/battle_util.c
- src/data/battle_partners.party
- src/data/items.h
- src/data/trainers.party
- src/data/wild_encounters.json
- src/pokemon.c

新源文件：

- data/layouts/ArcheCampus_Maintenance/border.bin
- data/layouts/ArcheCampus_Maintenance/map.bin
- data/layouts/MagmaHideout_RescuePassage/border.bin
- data/layouts/MagmaHideout_RescuePassage/map.bin
- data/maps/ArcheCampus_Maintenance/map.json
- data/maps/ArcheCampus_Maintenance/scripts.inc
- data/maps/MagmaHideout_RescuePassage/map.json
- data/maps/MagmaHideout_RescuePassage/scripts.inc
- data/scripts/part55.inc
- include/constants/part55.h
- include/part55.h
- src/part55.c

一次性实施编辑工具已移出工程归档于Windows logs/part55-tools-archive，禁止直接重跑；日常直接编辑源码。完整修改文件索引另见 docs/project/part55-files.json（含文档/测试），不只含运行源码。
