# 开发环境搭建完成

验收日期：2026-10-06。所有环境完成标准已通过。

- 官方底座：RHH pokeemerald-expansion `expansion/1.17.1`，提交 `bb1093a7c72d3961d9a37d8e02ad2abc2c866682`。
- 权威源码：`\\wsl.localhost\Ubuntu-24.04\home\pokemon\projects\emerald-story`（Ubuntu 中 `/home/pokemon/projects/emerald-story`）。
- Windows 工作入口：`D:\Pokemon gba`。`source` 是最初搭建快照，不用于日常编辑。
- `Open-VSCode.cmd`：连接权威 WSL 工程。
- VS Code **Ctrl+Shift+B** / `Build-and-Test.cmd`：编译成功后启动最新 ROM。
- `Open-Porymap.cmd`：通过 WSLg 打开 Porymap 和当前工程；地图文件监听正常。
- 产物：`artifacts/current/pokeemerald.gba`、`pokeemerald-release.gba`，各 32 MiB。
- 常规编译：WSL 工程中 `make -j$(nproc)`；封装入口 `bash scripts/build.sh --run`。
- Release：`bash scripts/build.sh --release` 或 VS Code `GBA: Release for hardware`。
- 原始剧情/地图保留；现代系统及 Mega 保留，Z/Dynamax/Tera 游戏中关闭，Gen 1–9 数据保留。
- `PROJECT_BLUEPRINT.md` 和 `DEV_LOG.md` 是权威 Git 文档的 Windows 阅读副本；修改应在 VS Code 的 WSL 工程中进行。
- 证据：`logs/build-initial-success.log`、`logs/one-click-test.log`、`logs/build-release-success.log`、`artifacts/verification/field.png`。
- 无阻塞环境问题；Release 上游编译警告已记录，实体 GBA 硬件未测试。窗口自动控制已按用户 Escape 操作停止。
