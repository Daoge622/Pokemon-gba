# Windows 工作区入口的版本备份

此目录保存搭建入口和官方包校验值，不保存工具二进制、ROM、存档或 WSL 虚拟磁盘。

实际安装位置为 `D:\Pokemon gba`。`setup/` 中的 PowerShell 文件按工作区根目录下的安装位置运行。`project-env.template.json` 是搭建模板，不是迁移后的实际配置；运行时配置位于工作区根目录 `project-env.json`。

Windows `scripts/dev.ps1` 只是转发器。实际工作流逻辑由 Git 管理，位于工程 `scripts/windows/dev.ps1`；转发器按照 `project-env.json` 查找当前权威源码。这样迁移后不会执行 Windows 暂存工程的旧构建逻辑。

`scripts/bootstrap/bootstrap-linux.sh` 负责依赖、Linux 用户和源码迁移；更新它时同时更新 DEV_LOG。Linux 用户没有预设共享密码，也没有新增免密码 sudo；安装包可通过 `wsl.exe -d Ubuntu-24.04 -u root` 管理。如要交互使用 sudo，需自行为用户设密码。

恢复入口时复制这些模板到工作区相应位置，下载清单指向的官方版本并校验，然后按 SETUP_STATUS 继续。不要复制 WSL 目录中的活动 ext4.vhdx 来“备份”；后续采用 `wsl --export` 和 Git 备份。
