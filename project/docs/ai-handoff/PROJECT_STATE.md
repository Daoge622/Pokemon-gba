# 项目状态（实际核查）

## 2026-10-14 / Claude（分支 claude/bugfix-ocean-relayout-48ip2m，待用户确认后合并 main）

权威源码：GitHub Daoge622/Pokemon-gba `main` 的 `project/`。本分支在云端 `make release` 可完整构建 32MB ROM。

IMPLEMENTED（源码已改、已构建，**未经游戏内测试**）：
- 绿岭情侣双打补上第二名 NPC；送神山诅咒娃娃不再移位堵路；暮水镇浮水 NPC 挪到木板上；宇宙中心莱因旁加阿尔刻研究员，对话时互相转向。
- 炎帝入口（FieryPath）改为可见洞口。
- 126/127/128 海底异常点、校准点改为可见观测装置实物；提示写明具体位置与进度数。
- 海洋重布局：124/126/127/128/129/131 的 Codex 补丁地形全部还原为原版；新建原版风格沙岛（126 东、127 西南两座、128 东侧礁石带北边、129）和 131 木台；相关任务 NPC 全部挪上岛，127 校准组对话有朝向演出；131 样本箱改为可见标记。
- 全部 Codex 剧情对话重写（part1/2/4/5/55/6/7、campus、story_a/b/c 及地图内 Part* 文本），只改文本不改脚本结构。
- 新增工具：scripts/tests/maptool.py（可达性）、maprender.py（地图渲染）、check-text.py、check-text-only-diff.py。

TESTED：静态检查（文字宽度/字库、只改文本、单图可达性 BFS、跨地图冲浪可达性 scripts/tests/sea-reach.py）。2026-10-15 用用户存档在 mGBA 无窗口核心实测：读档、绿岭/宇宙中心走动、从琉璃冲浪经 127 到 128 莱因新岛登岛成功；其它岛未逐个实机登岛。
- 注意：maptool.unreachable() 把每张图边缘都当入口，查不出被礁石跨图围住的水域；改海图后必须再跑 sea-reach.py（输出里的 124/126/127 原版潜水道具、琉璃/彩幽城对象是原版就需潜水/攀瀑，属正常）。

已知问题：守墓人重置根因未确认（Codex 记录）。check-chinese.py 等依赖缺失的 docs/project/part7-deltas.json，暂不能运行。

## 历史（2026-10-11 / Codex，本地 E 盘时期）

2026-10-11 / Codex。用户入口 E:\Pekemon Gba\project，原 AGENTS 的 D 盘入口不存在。无 Git/map/elf/完整构建缓存；E 盘源码与现用 ROM 不完整对应，不能全量重编发布。

IMPLEMENTED：此前五处图像字段源码同步；共享 multi_do 四入口选队/取消/战后队伍恢复；本轮 part55.inc 四入口补 cant_see_if_trainerflag_set，修复基地战后自动循环对话。无新增 Flag、剧情改写或防御性兜底。

TESTED：此前送神火山组队选队/取消/胜败/六只恢复/保存冷启动通过，其它三入口为测试设置验证。本轮全游戏 550 个视线训练家入口核查，找到四个普通剧情包装缺陷全部覆盖；四场按键打赢、获胜标志、600帧无再触发、战后手动对话/关闭/行走通过。受控地图 warp/隔离标志，两名走动小兵仅测试副本固定姿势，不是全剧情或 MyBoy 验证。静态检查 543 地图、56332条脚本、711对战无已检错误，88个未知 native 后未覆盖。

累计 ROM SHA256 5948b8fd044a7b07d4cb75ed7f2439f5607ea15065f161728218bf41fe644614；基于前次 8c3142dcf6678093913e9f572865272d46dbe9862f60d03f5f9d251259037e8d，前次修复逐字节保留。原 ROM cf9b34f57b57a71613e12fe078eba35835ec9e1283ac355b4436201bf854cbde 和原记录均未覆盖。

情侣撕裂：用户本轮明确确认已修复，执行者/具体补丁未知，非本轮认领。守墓人重置此前自行恢复，根因未确认。全游戏未穷举验收。

当前报告：C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\战后对话修复与Claude接力记录.md；此前记录仍在 outputs/组队双打修复与接力记录.md、体检与接力记录.md。

- 本轮女孩战后使用交付ROM游戏内普通记录，再新建核心冷启动读档：回到基地24/87，等待600帧无对话循环、锁为0；存档中的女孩脚本指针已更新为0x09B0046C。dialogue-coldboot-verification.json与截图已归档。
