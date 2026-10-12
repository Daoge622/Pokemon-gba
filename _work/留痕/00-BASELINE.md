# 00 基线记录 — 源码工程对齐到现用 ROM

执行者：Claude（Little Code Sauce）
日期：2026-10-11（起于 15:40 左右，系统本地时间）
用户指令：全量推进（解压 tarball → 合入 Codex 三补丁 → 装 MSYS2+devkitARM → 构建验证），且**任何修改必须留痕**。

## 1. 为什么要重建

Codex 在 `E:\Pekemon Gba\project` 上报「源码快照缺移动文件/5个 special，不能完整还原现用 ROM」，因此改用二进制定点补丁发布 ROM。实测发现**缺失文件一直躺在工作区的分片包里没被解压**，本目录记录由此发起的源码对齐。

## 2. 版本谱系（实测哈希）

| 产物 | SHA1 / SHA256 | 说明 |
| --- | --- | --- |
| `EmeraldStory-一周目完整版.gba`（工作区根） | SHA1 `977610b33caf395b38683279b16aae90f5f34060` / SHA256 `cf9b34f57b57a71613e12fe078eba35835ec9e1283ac355b4436201bf854cbde` | 第二轮试玩修复交付版；不含 Codex 两轮补丁 |
| `EmeraldStory-…-组队选宝可梦修复.gba`（Codex outputs） | SHA256 `8c3142dcf6678093913e9f572865272d46dbe9862f60d03f5f9d251259037e8d` | Codex 第 1 轮 |
| `EmeraldStory-…-组队与战后对话修复.gba`（Codex outputs） | SHA256 `5948b8fd044a7b07d4cb75ed7f2439f5607ea15065f161728218bf41fe644614` | **现用 ROM**（Codex 第 2 轮） |
| `project.tgz.part00+01+02` 合并 | SHA1 `111533267e903ccf4fbc26ec6439606845dc6a07` | 权威源码基线；内部文件 mtime `2026-10-11 11:50:25` |
| `_backup\project-0909-快照`（原 project 目录） | 目录整体移入备份 | 旧快照（mtime `09:09:17`），含 Codex 直接改动的 4 个文件；**不删，保留回滚** |

## 3. 本次操作对文件系统的改动（已有）

1. `E:\Pekemon Gba\project` → 重命名为 `E:\Pekemon Gba\_backup\project-0909-快照`（Move-Item，未删除任何文件）。
2. `project.tgz.part00+01+02` → 合并为 `%TEMP%\pgtar_check\project.tar.gz`（SHA1 校验通过，副本另存见下），解压到 `E:\Pekemon Gba\project`（32376 个文件）。
3. 新建 `E:\Pekemon Gba\_work\`（构建与留痕工作区）。
4. 应用 Codex 补丁（明细见 `01-CHANGES.md`）。

原始分片 `project.tgz.part00/01/02` **未删除**（`解压项目.bat` 里的 `del` 步骤从未执行过，本次也保留原样）。

## 4. 环境事实（实测）

- 系统：Windows，工作区 `E:\Pekemon Gba`。
- `wsl` 仅有帮助输出 → WSL 发行版不可用；`D:\Pokemon gba` 不存在。
- `arm-none-eabi-gcc`、`make`、`msys2`、`devkitPro` 均**未安装**（受限深度全盘搜索无结果）。
- 可用：`git`（`C:\Program Files\Git\cmd\git.exe`）、Python 3.12、`tar`（bsdtar）、`certutil`。
- E 盘剩余空间 520.5 GB；C 盘剩余 202.1 GB。
- 现用 ROM 的用户存档仍在：`C:\Users\DaoGe\Downloads\EmeraldStory-一周目完整版.sav`（128 KB）。

## 5. 溯源材料位置

- Codex 接力包：`C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\战后对话修复与Claude接力包.zip`
- 本目录 `patches\` 下的补丁副本及其 SHA256（见 `01-CHANGES.md` 表末）。
