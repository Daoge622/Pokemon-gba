# Windows 普通目录迁移 / 2026-10-10 / Codex

唯一可编辑工程：`D:\Pokemon gba\project`。连接此文件夹即可访问源码、Git、美术、剧情及共享文档，无需 UNC。

WSL 保留工具链与编译缓存，构建前单向同步 Windows → Linux。禁止直接修改 Linux 缓存或旧 source。

在工程根运行：
```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File scripts/windows/dev.ps1 -Action Build
powershell -NoProfile -ExecutionPolicy Bypass -File scripts/windows/dev.ps1 -Action Release
```
VS Code 默认构建任务转发同一入口；只同步使用 Sync。PART7 差异使用 RecordDeltas 后复核。所有入口禁止自动 GUI/模拟器/ROM。

ROM 输出：`D:\Pokemon gba\artifacts\current`。旧 Build-and-Test.cmd 转发新入口，名称沿用但不启动游戏。

迁移前完整仓库（含 Git、未提交修复、美术）保存在 `artifacts/migration-20261010/repository-before.tar`；原差异/HEAD 同目录保存。不提交或丢弃已有变更。

## 验证结果

- 全仓归档逐文件 SHA256 校验：39,199 文件，无意外差异；校验期间已执行的5项入口/说明编辑单独记录为预期差异。原游戏源码、资产、Canon、Git 对象保持。证据：artifacts/migration-20261010/copy-verification.json。
- 原游戏/构建修复相关20个已修改文件的 Git 差异与迁移前逐字节一致；HEAD 578496443f1e7deb6bb06fa1f02311262fad6ae6、分支 project/part7 保持。新 Windows Git 配置关闭自动换行和 filemode，启用 ignorecase；无提交/重置/丢弃。
- 实际从新 Windows 工程执行 Build、从旧入口转发执行 Release：两者退出0，各20套既有构建/静态/宿主检查通过。日志：入口 logs/migration-normal.log、logs/migration-release.log。
- normal SHA256：16b35f7ebff2e8d0c4047c4a934d924e81ccb466ffe0364fea4aba61a9b6e598。
- release SHA256：88b4f485c7ac46cd255510faa09ab432d1f3d98f734c21467251bba4e1b6cda8。
- 两份ROM各32MiB，均与迁移前一致；普通save无需因迁移转换。未执行ROM/模拟器/GUI，游戏内验收仍 Pending。
- 首次同步校验内容，日常采用大小/纳秒修改时间增量同步；输出只进入入口 artifacts/current，旧源码目录生成物移入备份 initial-generated-outputs，防止误拿旧ROM。

迁移 IMPLEMENTED；上述复制/构建/入口检查 TESTED。游戏内容、剧情、存档结构与 Canon 无变化。WSL 工具链继续需要，Windows 文件夹是真实源码，不是链接或VHD。
