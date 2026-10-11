# 实机反馈源码修复 / 2026-10-10

执行 AI：Codex。权威仓库 `/home/pokemon/projects/emerald-story`，分支 `project/part7`，底座官方 RHH Expansion 1.17.1。**本批修复 IMPLEMENTED；normal/release + 20 套无界面检查 PASS；新 ROM 游戏内 / MyBoy 实机 TESTED 未完成。全程未启动 GUI、模拟器或 ROM。**

## 已实施

1. **釜炎道馆卡死**：四个 `(11..14,11)` 事件从 `TRIGGER_RUN_IMMEDIATELY`（实际值0）改为 `VAR_TEMP_9 == 0`，进图清零。原 `VAR_TEMP_B–F` 保留，无新永久变量。Rehearsal 的两个原有 Flag guard、lockall/dialogue/setflag/releaseall 不改，切回普通调度上下文。
2. **联合房间检查关闭**：`OW_UNION_DISABLE_CHECK=TRUE`。保留环境叫声、已有 10-08 `InitUnionRoom` 单机清理修复。**116 草丛卡死原因未确认 / Pending**：旧诊断二进制同时禁用了两项，不能据用户通过就确定是哪项起作用；当前源码只关闭这一项。
3. **博物馆 2F 馆长**：先交付德文物品并保存原主线推进状态，再调用已有 `Part2_TryMuseumThanks` 给3心之鳞片；成功后离场对白 → 治疗 → 隐藏/移除。满包不隐藏、不治疗、不重复原战斗；再次对话补领。原 1F 工作人员补领保留；先在1F补领后可找仍在2F的馆长完成治疗/离场。旧档中馆长已消失但没领礼物的，仍在1F补领。
4. **装船物流员工**：按 `Part5_Text_199 -> Part5_SlateArcheLogistics -> Part6_Crisis_SlateportCity_31` 定位，实际地图为凯那市北端 `(18,4)`，不是另一名道路NPC。只将 `LOCALID_PART5_SLATE_ARCHE` 移到港口旁 `(32,14)`，保留所有时期对白。落点可走、无人、非warp，没有改变潜水艇演出。
5. **113灰地训练家停步**：双胞胎 `(45,6)/(46,6)` 附近转圈的 Madeline `(51,11)`，以及花圃一带往返的 Sophie `(7,6)` / Coby `(7,13)`。未附原截图，本轮按源码动作和位置匹配；两名步行训练家都停下。进入/战后 `ON_RESUME` 调用无等待的原生 helper，检查原败北 Flag，同步保存模板和当前 sprite callback，胜前行为不改。Sophie/Coby也一起覆盖，避免下方跑动反馈遗漏。无新增败北或奖励状态。
6. **烟囱山女新人撤退**：主路线返回触发 `(10,10)` 推玩家到 `(11,11)`；东侧直接交互 `(10,9)` 先推到 `(10,10)` 再侧移。新人从战后原位置 `(9,9)` 按13个快步沿可通行地形向南到 `(12,19)`、离开视野后隐藏，不再向左上跑。北/西侧主动交互不占逃跑通道，不强推到岩石上。保留原离场 Flag、原台词、战斗、胖丁6V/永不进化/队伍最高等级。没有添加主线。

## 待确认站位（没有实施）

`NPC_PLACEMENT_PROPOSAL_2026-10-10.md`：13个角色逐行当前/建议坐标和理由，包含紫堇老人/咩利羊、117双打、森林小支线和同类外围NPC。用户确认后再改。`docs/project/NPC_PLACEMENT_INVENTORY_2026-10-10.csv` 是106地图426个PART关联对象的索引，不代表全部都是新增或全部需要移动；保存官方比较分类。

## 新构建防线与验证边界

- `check-immediate-scripts.py`：扫描剩余36个零触发事件及所有立即执行地图hooks（包含用户指定四类及Dive/Warp表）；沿call、conditional goto/call及标签fallthrough查等待指令。762入口、5536条可达指令 PASS。自测证明嵌套call/branch和fallthrough等待能被发现，死分支不误报。
- 上游对战设施有10处原始异步入口命令：只对明确列出的上游hook核对官方1.17.1相同等待站点，**不允许零触发坐标例外**，不改这些原版特殊设施。不能将既有合法设施用法当新PART模板。
- Native/special C实现仍需读源码；该检查不是ROM执行或通用C副作用证明。当前PART入口未发现新增等待链，新增停步helper已单独验证无任务等待。
- `check-playtest-20261010.py` 使用当前源码、不经过历史compat还原：满包/成功/重试/1F补领/顺序；4条Gym调度；联合房间开关；港口落点；新人13步碰撞/演员避让。宿主C编译实际停步helper，测试8种败北组合、存在/不在视野对象、错误地图，不运行ROM。
- `record-part7-deltas.py` 已运行并复核：8个已有源码文件的授权改动，1个新增C文件，其他原登记源码/新文件hash保留。差异仍可严格反转至原基线；原10-07/10-08未提交修复保留。快照见 Windows `artifacts/qa-playtest-2026-10-10/before/prior-worktree.patch`；审阅摘要 `delta-review.json`。
- 没有新增 Flag / 持久 VAR / 训练家 / 地图 / 道具 / 物种 ID；存档结构、保存函数未改变，剩余24Flag/持久VAR耗尽的约束保持。

## 构建与交付

`bash scripts/build.sh`、`bash scripts/build.sh --release` 均退出0、20套检查PASS，ROM各33554432字节。保留原上游/newlib/LTO与既有字体警告，不声称零warning。完整日志在 Windows `logs/build-normal-20261010.log` / `logs/build-release-20261010.log`。

Normal SHA256：16b35f7ebff2e8d0c4047c4a934d924e81ccb466ffe0364fea4aba61a9b6e598

Release SHA256：88b4f485c7ac46cd255510faa09ab432d1f3d98f734c21467251bba4e1b6cda8

Windows最新产物：`D:\Pokemon gba\artifacts\current\pokeemerald.gba` 与 `pokeemerald-release.gba`。桌面release：`C:\Users\29051\Desktop\Pokemon_Emerald_Fix_2026-10-10.gba`（逐字节/hash一致）。

## MyBoy换ROM与人工测试

- 普通游戏内保存的 `.sav` 继续沿用；本轮未修改或覆盖存档。**旧即时存档 / save state 必须作废，不得载入新ROM。** 先备份普通sav，再在MyBoy完全关闭旧游戏，换新ROM并从标题画面读取正常保存。
- 自动读档通常需ROM与sav同名同目录；可保持旧ROM文件名覆盖为本版，或复制sav并改为新ROM相同基本文件名。不要把即时存档重命名伪装成sav。卡死后的即时存档不能当恢复依据。本轮没有执行用户个人存档验收，无法凭构建保证任意已损坏sav可恢复。
- 需要人工使用 MyBoy / mGBA 测试：釜炎四格依次接近、台词后自由移动、重复踩格不重播、可与亚莎战斗/存读档；博物馆满包/补领/正常奖励先于治疗和消失、旧档1F补领；港口员工不挡剧情；113三名训练家胜后/重进图/重读sav停止旋转或往返；烟囱山推开玩家并向南离场、直接交互路径；116草丛长时间行走/战斗/次日从普通sav继续是否再卡死。
- 若116仍卡死，请保留普通sav、ROM版本、触发位置/操作和MyBoy版本，下一步再决定环境叫声二分诊断，不能现在宣布已修。


## 本轮修改文件

- 游戏源码：`data/maps/LavaridgeTown_Gym_1F/map.json`、同目录`scripts.inc`；`data/maps/SlateportCity/map.json`；`data/maps/SlateportCity_OceanicMuseum_2F/scripts.inc`；`data/maps/Route113/scripts.inc`；`data/maps/MtChimney/scripts.inc`；`include/config/overworld.h`；`include/part3.h`；新`src/field_playtest_fixes.c`（原生回调签名遵循`callnative`的`struct ScriptContext *`接口）。
- 构建/检查：`scripts/build.sh`，新`check-immediate-scripts.py` / `check-playtest-20261010.py`；按规则更新`docs/project/part7-deltas.json`。
- 报告/接力：本报告、NPC站位建议、调查CSV/建议JSON；`PROJECT_STATE.md` / `CURRENT_TASK.md` / `CHANGELOG.md`更新并镜像；`CANON_DECISIONS.md`已核查原样保留并镜像，没有新增或推翻Canon。
- Claude两份输入排查记录只补充权威仓库存档，不改原文。旧DEV_LOG/PROJECT_BLUEPRINT及10-07/10-08源码/测试修改保持原样；保存了改前diff，复核12份旧diff逐字相同。
