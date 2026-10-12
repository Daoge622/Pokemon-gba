# 项目状态（实际核查）

2026-10-12 / Codex。正本为 GitHub `https://github.com/Daoge622/Pokemon-gba` 的 main，工程在 project/。E/D 盘都是工作副本；开工先 pull，实质修改须 commit/push，重要改动经分支确认后再合并。ROM、存档与凭据不提交。

IMPLEMENTED：原有图像字段修复、共享 multi_do 四入口选队/取消/队伍恢复、四个包装入口的获胜后视线停止判断均在当前源码中。手套/便当小兵已有专用 _Defeated 战后入口，由地图 trainerbattle_single 第四参数引用；已存在于 main，本轮不重复改游戏代码。历史留痕 04-GLOVES-FIX.md 署名 Claude，DS 是否执行同一修复未确认。

构建状态：原“源码缺文件、无工具链、不能构建”的结论已过时。此前已从分片恢复完整源码、配置 MSYS2/ARM GCC 并构建，见 _work/留痕/00-BASELINE.md、02-TOOLCHAIN.md、03-BUILD-OUTPUT.md、04-GLOVES-FIX.md。本轮比对30215个project文件与GitHub树：20327个字节相同、9888个仅CRLF/LF不同，无内容差异。核查的是既有构建产物，没有声称本轮重新构建。

TESTED：既有源码构建版 SHA256 826eb52c39b5e0b7bc9e2c64cd74b1ef27f738a9a5349791888a688c0e13220f，从用户桌面普通记录冷启动，正常走路触发并打赢手套/便当两场，原获胜标志置位，战后等待1200帧不自动重开对话，菜单及继续行走通过。保留NPC实际走动，未warp、改Flag/队伍/HP/姿势；使用本会话已授权无窗口mGBA，未开GUI。证据见 _work/留痕/05-CLOUD-MAGMA-REVIEW.md。

限制：用户报告旧Codex补丁版5948b8...在MyBoy手套战后卡死，同一桌面记录在mGBA未复现。不能把“缺trainerbattle第四参数”当作已动态证明的手机根因，不能把mGBA通过写成MyBoy验收。用户后称可能由DS修好，当前只能确认仓库已有修复，手机状态待反馈。情侣撕裂此前用户明确确认已修复，作者未知；守墓人重置自行恢复但根因未知。全游戏未穷举验收。

旧补丁与源码不完整的历史调查仅作版本记录，见 harness/codex/2026-10-11-zhe/outputs/ 与 _work/留痕/。不得用旧地址即时状态验证新工具链构建的ROM。历史留痕只追加，不改写。
