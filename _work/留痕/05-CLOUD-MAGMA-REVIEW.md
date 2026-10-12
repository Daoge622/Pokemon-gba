# 05 GitHub正本与熔岩队既有修复核查

2026-10-12 / Codex。

## 基线、规则与归属

开工执行 git pull --ff-only origin main，基线与远端均为 d1f7fa59ebf9ba3617b845bcee34991de91378d6。用户授权GitHub为正本、修改commit/push、重要修改分支待确认；分支为 codex/20261012-cloud-handoff-magma-review。用户后来要求先看DS是否已经修好，故没有重复改游戏代码。

main中的 project/data/maps/MagmaHideout_2F_1R/scripts.inc 已将两处trainerbattle_single第四参数设为 Part55_MagmaBento_Defeated / Part55_MagmaGloves_Defeated；part55.inc已有对应lock/msgbox/release/end和四个包装入口的cant_see_if_trainerflag_set。这些代码已在导入提交a22a0dd中存在。

04-GLOVES-FIX.md署名Claude，Git提交作者daoge不代表AI身份。已核查留痕和handoff中未找到DS明确署名，因此本轮不改记为DS/Codex执行。

## 源码与构建关联

已有源码构建版SHA256 826eb52c39b5e0b7bc9e2c64cd74b1ef27f738a9a5349791888a688c0e13220f，与04记录一致。GitHub main树与该构建目录30215个project文件比较：20327个字节一致，9888个仅CRLF/LF不同，无内容差异。E盘只作哈希比对缓存，正本始终是GitHub。本轮没有重新构建。

旧Codex补丁版SHA256 5948b8fd044a7b07d4cb75ed7f2439f5607ea15065f161728218bf41fe644614。两版代码地址大量不同，不得跨版导入RAM即时状态；本轮源码构建版用普通记录冷启动。

## 本轮验证

用户普通记录SHA256 1af02ad2542285426c7cedac74662c66d07548cb96dcc776704cfd2fffbddd4b，冷启动地图24/87、坐标11/8。沿用用户本会话无窗口ROM运行授权，未开GUI。mGBA正常走路触发并打赢手套，再正常打赢便当；未warp、改Flag、编辑HP/队伍或固定NPC行走。

- 手套：原获胜标志0x7D0置位；返回地图回调0x08190585，玩家锁0。
- 便当：原获胜标志0x7CF置位；返回地图回调0x08190585，玩家锁0。
- 战后等待1200帧无自动重开对话；开始菜单打开/关闭后从13/14走到12/14，锁0。
- 旧Codex补丁版用同一普通记录正常走路打赢两场也未在mGBA复现卡死。这不能否定用户MyBoy报告，也不能证明旧版手机验收通过。

验证JSON见同名目录cloud-user-replay.json和source-comparison-summary.json。本地截图/状态留在原调试工作区work/cloud-user-*、work/user-*-actual-*，原记录未写回；ROM/存档/DLL/凭据不入库。

## 文件、原因与限制

- PROJECT_STATE.md：纠正源码不完整、不能构建的过时当前状态；同步GitHub正本、既有修复和验证边界。
- CURRENT_TASK.md：改为核查既有修复、独立分支待确认，不再要求重复合入旧补丁。
- CHANGELOG.md：追加本轮事实。
- 本报告及两份JSON：追加下一位AI可复核的证据；不改写历史留痕。
- CANON_DECISIONS.md已读，没有新增剧情决定。

本轮完成的是核查既有修复与云端接力记录。MyBoy根因及最新版本手机验收未完成；原版大量trainerbattle_single缺省第四参数是合法用法，不能全判Bug。
