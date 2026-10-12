# 02 工具链与构建环境

日期：2026-10-11
目的：让 `E:\Pekemon Gba\project`（基线 + 补丁）能够编译。

## 1. 为什么不是 WSL

原环境是 WSL Ubuntu-24.04（`/home/pokemon/projects/emerald-story`）。实测本机 `wsl.exe` 只返回帮助文本 → 无可用发行版；`D:\Pokemon gba` 不存在。因此改用官方支持的 Windows 路径：MSYS2 + arm-none-eabi 工具链（`INSTALL.md` 列为可行系统之一，仅速度慢于 WSL2）。

## 2. 安装位置与来源（全部留痕）

| 项目 | 值 |
| --- | --- |
| MSYS2 版本 | `msys2-x86_64-latest`（2026-09-27 构建，tar.xz 40.9 MiB） |
| 下载地址 | `https://mirrors.tuna.tsinghua.edu.cn/msys2/distrib/msys2-x86_64-latest.tar.xz`（清华镜像，46 MB/s） |
| 本地归档 | `E:\Pekemon Gba\_work\dl\msys2-x86_64-latest.tar.xz` |
| SHA256 | `EA2F31A0B6ADE63914CE441FFB022F0F6AA96982BFEFA2326460A26D5FB01322` |
| 解压方式 | 系统 bsdtar 缺 xz 过滤器 → 先用 Python `lzma` 转成 tar，再 `tar -xf` |
| 安装目录 | `E:\msys64`（无空格路径；未使用管理员权限、未注册系统级快捷方式） |

## 3. 对环境配置文件的改动（含备份）

改的是 MSYS2 自身的 pacman 镜像列表，把清华镜像提到首行以加速（原文件内容完整保留在备份目录）。

| 文件 | 改动 | 备份 |
| --- | --- | --- |
| `E:\msys64\etc\pacman.d\mirrorlist.mingw` | 首行置顶 tuna 源 | `_work\留痕\config-backup\msys2-pacman\mirrorlist.mingw` |
| `E:\msys64\etc\pacman.d\mirrorlist.msys` | 首行置顶 tuna 源 | `_work\留痕\config-backup\msys2-pacman\mirrorlist.msys` |

这两个文件只影响包下载速度，不影响编译结果；如需还原，直接复制备份覆盖即可。

## 4. 无空格构建入口（junction）

`E:\Pekemon Gba\project` 路径含空格，MSYS2 下构建风险高。用 NTFS junction 建无空格入口，**不复制文件、不改变权威路径**：

```
mklink /J "E:\es" "E:\Pekemon Gba\project"
```

两者指向同一份文件：在 `E:\es` 下的构建产物会真实落在 `E:\Pekemon Gba\project` 内。

## 5. 安装的软件包

| 包 | 用途 |
| --- | --- |
| `make`（msys） | GNU make，Makefile 要求 `SHELL := bash -o pipefail` |
| `mingw-w64-ucrt-x86_64-gcc` | 编译 `tools/`（gbagfx、rsfont 等宿主机工具） |
| `mingw-w64-ucrt-x86_64-libpng` | gbagfx / rsfont 的 PNG 依赖 |
| `mingw-w64-ucrt-x86_64-arm-none-eabi-gcc` | ROM 的交叉编译器（对应 Makefile 的 `TOOLCHAIN`） |
| `mingw-w64-ucrt-x86_64-arm-none-eabi-newlib` | 交叉编译 C 库 |
| `pkgconf` | 依赖探测 |

安装与验证日志：`E:\msys64\tmp\install.log`（MSYS2 内部路径 `/tmp/install.log`）。

## 6. 构建方式（待验证）

```bash
cd /e/es
export PATH=/ucrt64/bin:$PATH
make TOOLCHAIN=/ucrt64 -j$(nproc)
```

`Makefile` 关键约束（已核对源码）：
- `TOOLCHAIN` 目录必须含 `bin/`，Makefile 会自动把 `$(TOOLCHAIN)/bin` 前置到 PATH。
- `CFLAGS` 含 `-Werror -Wall`，`-flto=auto` 默认启用 → GCC 版本差异可能把新警告放大成错误，届时按需处理（优先降版本，不擅自关 `-Werror`）。

## 7. 风险与对策

| 风险 | 对策 |
| --- | --- |
| 可用 ARM GCC 为 16.1.0（ucrt64 仓库），可能比原 WSL 环境新 | 先直接构建；若 `-Werror` 反复失败，回退安装 xpack 13.3/14.2 或 devkitARM |
| 路径含空格 | 已用 `E:\es` junction 规避 |
| pacman 首次 `-Sy` 曾无输出卡住 | 用 `pacman -Syy` 强制刷新后正常（exit=0） |
