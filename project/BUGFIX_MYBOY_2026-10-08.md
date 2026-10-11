# 2026-10-08 MyBoy 重置排查与全游戏运行扫描

执行 AI：Claude。用户授权：静默、不弹窗地运行 mGBA 做检查。分支 project/part7，Codex 的未提交修复（2026-10-07）原样保留，本轮在其基础上改动。

## 用户报告
用户用手机 MyBoy、release ROM、Codex 重建的武斗镇存档游玩，到石之洞窟后：
- 和石头互动会重置；
- 大吾离开洞窟时会重置。
用户提供了 bug 存档 Downloads/EmeraldStory-Dewford.sav（存档位置：石之洞窟 1F (8,4)，信未交）。

## 结论
用同一 release ROM（`1188b1dd…`）和用户存档，在 mGBA 里用真实按键复现：
- 走进大吾房间 → 对话 → 交信 → 登记 → 大吾离开：正常；
- 捕获新种（图鉴登记页）：正常；
- 石头 / 碎岩互动：正常。

所以石之洞窟的重置**无法在准确的模拟器上复现**。合理怀疑是 MyBoy 兼容性问题，或者金手指 / 快速存档；尚未在 MyBoy 上确认。

已排除的方向：
- 16MB 以上的 ROM 区域：全是音频，平时就在使用；
- 栈溢出：最坏场景仍剩约 1.4KB；
- 存档本身。

## 真实修复（游戏代码）
- **阿尔刻园区宝可梦中心护士（PART5）**：治疗后 release 版 CPU 跑飞（RunTextPrinters 回调指针是垃圾值）。
  原因：地图缺少 `MAP_SCRIPT_ON_RESUME, CableClub_OnResume`。没进过其他宝可梦中心时，sUnionRoomPlayerName 是全零的 EWRAM 数据，BufferUnionRoomPlayerName 无界拷贝后覆盖内存。
  修复：
  - 地图补上 ON_RESUME；
  - `src/union_room.c` 只信任缓冲区内有终止符的名字。
  - 修复后两个版本都已复现通过。

## 运行扫描（工具在 scripts/qa/sweep/）
- 全图事件扫描：每张绿宝石地图的每个人物 / 告示 / 坐标触发脚本，执行后按 A / B。
  - 第一轮（Codex 的恢复存档）发现上面的护士问题；
  - 修复后用用户存档，normal 4100 / 4100 正常，release 4100 / 4100 正常；
  - normal 版开着断言，未报断言。
  - 2061 个被跳过的是 FRLG 地图脚本，绿宝石里用不到。
- 全训练家对战：900 位训练家 / 名册对手（含四天王首通与强化、米可利、大吾、满充各档、PART5–7 新训练家）。
  全部进入战斗主流程，打几回合无崩溃。
- 静态地图审计（543 张地图）：传送目标、道具球 Flag、道具共用 Flag、未定义 Flag，均无问题。
- Codex 的修复已逐项核对存在：捕获、KO 动画、水跃鱼碎岩、蛋提醒、哈奇 / 皮皮绕石。
- normal / release 构建 + 18 套检查全部 PASS。
  - 正式 release SHA256 `1188b1dd18160efc11386f27dc471b6fa3c517036543952fe471d0608d4a00f1`
  - normal SHA256 `32155af16308ddaa2359906de6ecb5aa81caa37e6e6f26d997388d6af3bc402d`

## 交付
桌面 `EmeraldStory-测试包-2026-10-08.zip`：
- `EmeraldStory-Dewford.gba`：正式 release，与用户存档同名；
- `EmeraldStory-TEST.gba`：同内容 release 并开启中文调试菜单（R+START），SHA256 `35c6bd11…`。构建时临时改 DEBUG_OVERWORLD_MENU，之后已还原并确认正式版哈希不变；
- `EmeraldStory-TEST.sav`：用户存档副本；
- `使用说明.txt`。

## 待用户验证 / Pending
- 用户晚上在 MyBoy 实测。如仍重置，需要记录地图、操作、金手指 / 快速存档情况，以及崩溃画面截图。
- 网上的原版绿宝石金手指不适用于本 ROM（存档区地址每次开机随机），已在说明里提示关闭。
