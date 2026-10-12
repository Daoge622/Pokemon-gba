# 2026-10-07 早期游玩 Bug 修复与体验检查

执行 AI：Codex。权威源码 / Git：WSL /home/pokemon/projects/emerald-story，分支project/part7，任务起点578496443f；底座官方RHH Expansion 1.17.1，保留当前中文移植、开局至PART7全部实现。美术暂停。本轮用户明确允许模拟器 / ROM测试，实际采用无界面mGBA核心，未开GUI。此授权不修改长期默认禁GUI/ROM规则。

## 已实现的修复

1. **捕获卡死**：普通图鉴关闭后释放sPokedexView却没有清空；首次捕获新种退出登记页再次释放悬空地址，破坏仍在使用的战斗堆。旧ROM以“打开/关闭图鉴→正常精灵球捕获幕下力士”复现：battleOutcome仍0，displaydexinfo卡住，CPU异常。Task_ClosePokedex释放后立刻置NULL；两处释放均检查。相同输入新ROM返回野外、outcome7，空位/满队/蛋/经验全队分配/已捕获种类均通过。没有修改捕获率、球数据或经验规则。
2. **KO后摇晃**：Expansion默认B_ANIMATE_MON_AFTER_KO=TRUE，任一方倒下时让对面存活宝可梦额外播放动画。改FALSE，保留正常招式/登场/破球动画。双方KO结束流程已运行通过；全部视觉观感仍请人工确认。
3. **水跃鱼系早期碎岩**：当前活跃Gen9升级表水跃鱼Lv6碎岩改掷泥，去除沼跃鱼/巨沼怪Lv1碎岩。其他种族升级表、HM教学兼容性和野外徽章权限不变。旧存档已学碎岩不会自动删除；原秘传遗忘限制仍保留。
4. **私人蛋提醒**：现有首次领取跑鞋场景中，母亲在未领取蛋时提示科学大叔与预留队伍空位；复用FLAG_RECEIVED_LITTLEROOT_RALTS_EGG=0x20。领取逻辑/SpA31/满队重领/未知私人送礼人保持，不添加组织关联。旧档已过场景不会倒带；可以返回未白镇领蛋，没有截止时间。
5. **哈奇穿石头**：PART1石头在(10,4)，旧接近和离场路径直穿此格。哈奇接近/离场、皮皮离场均经(9,5)→(10,5)→(11,5)绕行；保持原终点、玩家/水舰队成员移动、得文包裹、救援/航船状态。皮皮救援起点是(14,4)，已考虑VAR=2进图先移到13、随后后退的原生流程。后加咕妞妞在救援演员结束移除之后出现，不挡绕行。

## 修改文件

游戏源码（仅5个）：
- src/pokedex.c
- include/config/battle.h
- src/data/pokemon/level_up_learnsets/gen_9.h
- data/maps/LittlerootTown/scripts.inc
- data/maps/RusturfTunnel/scripts.inc

验证 / 工具：scripts/build.sh；scripts/tests/check-playability.py（新增19组）；check-chinese.py、check-part55.py、check-part3-west.py（历史源码对比复用严格审阅适配，未放宽存档ABI）；docs/project/part7-deltas.json（登记本轮精确差异）；scripts/qa/gameplay-probe.c、check-gameplay.py、README.md（明确授权才可执行的隔离运行夹具）。

文档：本报告、四handoff的状态/日志（Canon本轮检查但未变）、DEV_LOG.md、PROJECT_BLUEPRINT.md；同步Windows入口。保留上一轮美术文件及既有修改。

**新增永久Flag / VAR / ID：无。** 保存/读取实现、SaveBlock/Pokemon结构、物品/物种/地图/训练家编号均与起点保持相同。

## 构建与验证结果

- bash scripts/build.sh：返回0，18套检查全部PASS。
- bash scripts/build.sh --release：返回0，18套检查全部PASS。
- 新静态检查19组，包括两处图鉴释放、升级表范围、蛋flag/文案边界、绕行格地形/终点/不穿石/咕妞妞出现时序、其余救援指令不变。
- 运行核心：WSL libmgba 0.10.2+dfsg-1.1build3（无窗口）。不是Windows mGBA GUI验收。
- 修复前ROM：2用例，旧测试.sav续档PASS，图鉴后首次捕获卡死EXPECTED_FAIL_REPRODUCED。
- 最新normal：8用例PASS；旧测试.sav续档、图鉴后新种捕获、队伍空位捕获、满队+学习装置+蛋、已拥有种类捕获、对方KO后返回地图、我方全灭后返回地图、哈奇/皮皮完整救援。救援逐帧坐标未踏(10,4)，得文失窃Flag清除、找回Flag设定、卡纳兹state4、哈奇屋state1、玩家解锁。
- 最新release：前7项PASS；救援运行夹具SKIP（LTO删除初始化helper），不能声称此项release运行通过；正常版救援+两种编译/静态均已验证。
- 运行夹具仅改隔离模拟器RAM：复制预制宝可梦记录、构造战斗/地图状态、控制输入；源ROM/输入.sav哈希不变。这是针对问题的回归，不是整条主线自然游玩验收。
- 历史检查仍严格反向校验已登记差异；本轮没有把整个PART标成玩法TESTED。Release既有newlib/LTO/神秘礼物区域warning保持，不声称零warning。

最新32MiB ROM与Windows副本：
- artifacts/current/pokeemerald.gba：ab7966caf4fdd4d357834fb2abb01110d19a6414d6e83008ee289274c9919528
- artifacts/current/pokeemerald-release.gba：2f82ad52ca710347ff2ef46531d31811ed24cbf13c2b2e6c14d5a1d25d8715da
- 编译汇总日志：artifacts/bugfix-2026-10-07/runtime/build-normal.log、build-release.log。
- 运行证据：同目录suite-baseline/、suite-normal/、suite-release/的results.json与各用例result.log/截图；未复制终端全文进handoff。

## 武斗镇存档兼容

本轮不更改持久结构、编号/Flag位置与存储规则，**普通游戏内.sav应继续兼容，不要求重开**。已用修复前ROM生成的武斗镇测试.sav（沼跃鱼20、蛇纹熊10、拉鲁拉丝蛋、首徽章/学习装置）在两种修复ROM从Continue真实加载返回武斗镇。

**该测试档不是用户的个人武斗存档**；当前未拿到那一份或准确路径，不能声称已逐字验证。Windows已找到的artifacts/current/pokeemerald.sav及其备份哈希仍相同：B5A41C3758763BBEC72769FAB4A2533BF2DB0B6312D93D25A695F9E4B9E02260。旧ROM/源码/.sav在artifacts/bugfix-2026-10-07/before/保留，未覆盖为夹具。

更新方式：先保留个人普通.sav副本，关闭正在跑旧ROM的模拟器，加载新ROM，通过标题画面“继续”读普通存档；ROM和.sav保持对应文件名。**不要跨版本读旧即时存档.ss0/.ss1**，它会带回旧程序地址或已经损坏的战斗RAM。修复防止新堆损坏，不承诺修复本来已损坏的文件。现有队伍技能不自动迁移、已结束救援不重演、跑鞋提示不倒带。

## 已发现的体验风险 / 本轮未擅改

| 内容 | 对玩家的影响 / 建议 |
| --- | --- |
| 已有碎岩与秘传遗忘 | 改升级表不会消除旧队伍技能；原HM规则会限制替换，当前个人沼跃鱼需要另行处理，不能假装已自动修好。 |
| 满队捕获换入受HM限制 | B_CATCH_SWAP_CHECK_HMS=TRUE；知道任意HM的宝可梦不能在捕获界面退回PC，即使尚无对应徽章。取消替换/直接送PC可以正常完成，测试通过；不是新的冻结。 |
| 全队学习装置默认开启 | 每位有效参战100%、后台每只50%带来较快成长；Canon要求保留，可在背包切换，不自动调等级曲线。 |
| Gen9升级表 | 丰缘宝可梦早期也有现代招式，例如水跃鱼Lv9落石；保留其余现代技能，未来可按实际体验单独审平衡。 |
| 私人蛋发现性 | 新开局有明确提醒；旧档返回领取即可，不设期限/不绑组织。 |
| 后续地图 / 双打 / Mega /中文UI | 18套静态/宿主检查覆盖数据与状态，但不证明所有地图演出、界面像素、完整双打AI/全主线无Bug。需要分段运行验收，尤其满包/满队、存读档、演员显隐和地图通行。 |
| 姓名输入 | 目前仍是拉丁输入，中文输入未实现；中文底座未改。 |

## 仍需人工mGBA验证

1. **用户自己的武斗镇普通存档**：继续后打开并关闭图鉴，捕获一种未登记及一种已登记宝可梦；确认命名/送PC/替换/经验升级都能结束，保留个人备份。
2. 敌我KO后画面观感，确认所指“摇晃”就是已关闭的KO额外动画；若还有另一种抖动，需要具体招式/录像定位。
3. 新开局跑鞋场景中文提醒的显示/分页，以及未白镇领蛋；已领不会再提醒、满队仍可回领。
4. 未救皮皮的普通档，完整卡绿事件，两者绕石的画面与哈奇接船服务；本轮normal夹具已验证，release仍需人工补验。
5. 后续PART1–7按各实施报告逐段验收；本轮没有声称全面清零所有潜在Bug。
