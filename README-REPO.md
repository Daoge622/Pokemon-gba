# Emerald Story（Pokemon GBA 改版）仓库说明

基于 pokeemerald-expansion 1.17.1 的中文剧情改版。本仓库收录源码工程与各 AI 协作留痕。

## 目录

| 路径 | 内容 |
| --- | --- |
| `project/` | 源码工程（权威源码）。AI 规则见 `project/CLAUDE.md`、`project/AGENTS.md`，接力文档在 `project/docs/` |
| `_work/` | 2026-10-11 源码对齐与构建的工作区：校验/审计脚本、补丁、`留痕/`（Claude 修改记录）、`codex-tools/`、截图验证 |
| `harness/codex/` | Codex 在 `Documents\Codex\2026-10-11\zhe` 的产出（补丁、审计、验证 JSON、脚本）及其本项目相关记忆摘要 |
| `Claude outputs/`、根目录 `*.md` | Claude 交付的修复说明 / 更新日志 |
| `*.bat` | 本地分片合并脚本（历史用途） |

## 未入库的内容

- **ROM（`*.gba`）、`.elf`、`.map`、存档（`*.sav`）**：版权与体积原因不入库。ROM 由 `project/` 源码构建得到（`make`），或用 `harness/codex/**/*.bps` 补丁。
- `project.tgz.part*`、`r_aa/r_ab`：源码与 ROM 的分片包，内容已在仓库中或可重新构建。
- `_backup/project-0909-快照`：已作为第一个提交保存在 git 历史里。
- `_work/dl/`（MSYS2 安装包、multiboot 下载）、`mgba_libretro.dll`、构建日志全文。
- `~/.codex`、`~/.claude` 的会话记录与登录凭据（`auth.json` 等）。

## 工作方式

今后所有编辑以 GitHub 上的 `main` 分支为准：

1. 改动通过分支 + Pull Request 提交，合并进 `main`；不直接改本地副本后手工拷贝。
2. 本地或任何 AI 工具开工前先 `git pull`，完工后提交并推送，不再用分片包 / 手工备份传递源码。
3. 修改留痕写在提交信息和 PR 描述里，长篇说明继续放 `project/docs/` 或 `_work/留痕/`。
4. 构建出的 ROM 不提交；需要发布时用 GitHub Release 附件或 BPS 补丁。
