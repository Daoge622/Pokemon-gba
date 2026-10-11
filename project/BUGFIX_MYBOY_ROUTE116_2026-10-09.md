# 2026-10-09 MyBoy 116号道路草丛卡死排查（未复现）

执行 AI：Claude（Cowork 云端会话）。用户授权：静默、无窗口 mGBA。未改游戏源码、未构建、未在用户电脑上启动任何程序；无界面 mGBA 0.10.5 核心在云端容器里运行。
本会话够不到 WSL 权威仓库，所以 docs/ai-handoff 四份文档**没有更新**，下一位能进 WSL 的 AI 请把本文件要点同步进 CHANGELOG / CURRENT_TASK。

## 用户报告
手机 MyBoy，116号道路西段草丛，玩家约在 (13,7)（短裤小子 Joey (12,7) 右侧一格），偶尔在更靠下的草丛；画面定住、音乐照常。截图里没有对话框，Joey 背对玩家。

## 测试（ROM 为 artifacts/current，normal 32155af1… / release 1188b1dd…）
存档：Codex 的武斗镇恢复档，用 RAM 传送到 Route116 后游戏内正常保存得到测试档。不是用户的个人档。
- Joey 遭遇战（被看见→对话→战斗→回到地图）：normal 正常。
- 草丛随机行走 + 野生遭遇后逃跑：normal 约 50 场、release 约 20 场，无卡死。
- 首发等级改为 2（野生等级更高，走另一种转场 WHITE_BARS_FADE）：normal / release 均正常。
- 首发换成拉鲁拉丝（同步 / 复制 两种特性各试过）：正常。
- mGBA 非法内存访问日志：遭遇期间只有 VBlankCB_Slice 在转场结束后读 NULL 的 sTransitionData（原版绿宝石就有，只持续几帧），没有本项目新增的非法访问。

## 结论
同一 ROM 在准确的模拟器里走不出这个卡死；与 10-08 石之洞窟重置一样，只在用户的 MyBoy 环境出现。原因**未确定**。未排除：
1. MyBoy 金手指仍开着（原版绿宝石的码地址对不上本 ROM，会乱写内存）；
2. 读了旧版 ROM 时存的即时存档（10-07、10-08 连换过 ROM，代码地址变了）或 Quick load on start；
3. 用户个人档里的状态（队伍 / Flag）触发的真实 Bug —— 需要用户的 .sav 才能验证；
4. MyBoy 自身兼容性。

## Pending
- 需要用户从 MyBoy 导出当前普通 .sav 放进 D:\Pokemon gba，用它在无界面 mGBA 原位重放。
- 需要用户确认：当前用的是哪个 .gba、金手指 / 即时存档情况、卡死瞬间是否刚踩进草丛或刚被训练家看到。

## 追加（同日，用户提供个人档与 MyBoy 即时存档）
- 用户说明：10-08 新 ROM 上从头开的新档，没开金手指，没读过旧即时存档 → “旧即时存档 / 金手指”两条排除。
- 用户 `测试版.sav`（116号道路 (16,16)，首发 Lv13 猛火特性、拉鲁拉丝 Lv1、另一只 Lv4）：normal ROM 草丛 78 场野生遭遇无卡死；release ROM 与 Jose 对话、走动正常。
- MyBoy 即时存档格式已解出（gzip；头部大端寄存器在 0x20；IWRAM 0xB8，EWRAM 0x80B8，VRAM 0x480B8，OAM 0x600B8，调色板 0x604B8，IO 0x608B8）。栈上的函数地址与 artifacts/current 的 release ROM 完全对得上，可直接用 release ROM 分析。
- 把 st0 / st1 / st10 的内存和寄存器灌进无界面 mGBA（release ROM）继续运行：三个都能正常走动，不卡。三个存档的 CPU 都停在主循环等 VBlank 的位置，是正常状态，不是卡死瞬间。st0 / st1 是与捕虫少年 Jose 对战结束、画面淡入的时刻。
- 仍未复现。下一步需要**卡死当时**存的即时存档，才能直接看到卡在哪。

## 全盘复查（同日晚，Claude）—— 仍未复现，以下为已排除项与新事实
用户坚持认为是 ROM 问题并要求全面复查。全部在云端无界面 mGBA 完成，夹具源码在 artifacts/qa-myboy-2026-10-09/。

已排除（同一 ROM、用户存档或用户 MyBoy 内存原样灌入后运行）：
- 存档类型 / ROM 头：只有 FLASH1M_V103 一处，BPEE 头校验正确。
- 栈溢出：release 版菜单、对战、升级路径的栈最低到 0x030073EC，MyBoy 存档里的历史最低约 0x030073C8，IWRAM 数据止于约 0x03006E80，余量约 1.3KB，未越界。
- 一天 24 个整点的时段切换、RTC 跳变（+1 天 / +400 天 / +30 年 / 倒退）：不卡。
- 用户档草丛遇敌（normal 78 场、release 多轮含打赢升级）：不卡。
- 三个 MyBoy 存档各自灌入后长时间随机行走 / 对战（含 MyBoy 的 IE、SIO 寄存器值）：不卡。
- 无线联机路径：进过宝可梦中心后 gWirelessCommType 一直为 1、IE=0xC5、主循环改用忙等（上游默认行为，OW_UNION_DISABLE_CHECK=FALSE）。MyBoy 存档里的 RFU / STWI 状态与 mGBA 完全一致、处于空闲；之后的野生 / 训练家对战期间没有发出任何 STWI 指令。未发现阻塞点。

新事实：
- 三个存档都是健康的野外空闲状态（任务表、回调与 mGBA 一致）。st1 / st0 存于 10-08 19:45:49 / 50，位置 (13,16)（Jose 正上方）；st10 存于 10-09 16:55:44，位置 (16,16)，与 .sav 同位置。三者同一次开机，vblank 计数 0x52FDE / 0x5301D / 0x534DF。
- 用户是 10-08 晚玩了约 1 小时没卡，10-09 早上读档后才开始反复卡。
- 从 st0 起有两个确定的定时事件：环境叫声倒计时还剩 2775 帧（约 46 秒野外时间）；vblank 计数到 0x54000 时执行 DoTimeBasedEvents（约 68 秒后，含跨天处理）。两者在 mGBA 中都正常执行。

Pending：让用户读 st0 后原地不动计时；关掉 MyBoy 声音再试；卡死时另存一个即时存档发来。

## 诊断版 ROM（同日，Claude）—— 不是修复，未改源码
用户要求给一个 ROM 测试。因本会话进不了 WSL，直接在 artifacts/current 的 release ROM（1188b1dd…）上改 6 字节：
- 0x08171854：`bl PlayCry…` 改为两个 nop → 关闭野外环境叫声。
- 0x0826DB88：InitUnionRoom 在把 sUnionRoomPlayerName[0] 置 EOS 后直接跳到函数结尾 → 不建任务、不开无线，gWirelessCommType 保持 0（等效 OW_UNION_DISABLE_CHECK=TRUE）。
产物 SHA256 3b926a95…，放在用户桌面 EmeraldStory-诊断版-2026-10-09\（ROM + 用户 .sav 副本 + 说明）。无界面 mGBA 验证：进出中心、护士治疗、野生对战、对话正常。MyBoy 未测。
**artifacts/current 与权威源码都没动。** 若用户反馈不卡：再各做单项版本二分；确认后在源码里正式处理（联合房间用 OW_UNION_DISABLE_CHECK，环境叫声另议），并写入 handoff。
