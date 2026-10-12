# 01 变更记录 — 源码工程对齐（进行中）

基线：`project.tgz` 解压内容（SHA1 `111533267e903ccf4fbc26ec6439606845dc6a07`，内部 mtime 2026-10-11 11:50:25）。
工作目录：`E:\Pekemon Gba\project`。

## A. Codex 补丁的应用结果

| # | 补丁 | 作用文件 | 结果 | 备注 |
| --- | --- | --- | --- | --- |
| 1 | `patches\teamup-source.patch` | `asm/macros/battle_frontier/battle_tower.inc` | 已应用 | 选队宏 `multi_do`/`multi_2_vs_2`/`multi_2_vs_1`/`multi_wild` 新增 `cancelScript`、`chooseParty` 参数 |
| 2 | 同上 | `data/scripts/part55.inc` | 已应用（hunk 偏移 +6 行） | `Part55_RookieTeamup` 传入 `cancelScript=Part55_RookieTeamup_Cancel`，新增 Cancel 段 |
| 3 | 同上 | `data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc` | 已应用 | Steven 双打改为 `chooseParty=FALSE` |
| 4 | 同上 | `data/scripts/story_b.inc` | **待手工变基** | 第二个 hunk 失败：第二轮修复已把 `TRAINER_KAYLEE/TERRY` 换成 `TRAINER_STORY_A_SPARE1/2`，需按新上下文手工合并 |
| 5 | `patches\dialogue-source.patch` | `data/scripts/part55.inc` | 已应用（4 个 hunk 偏移 +7 行） | 四处入口 `Part55_RookieFormal / Part55_MagmaBento / Part55_MagmaGloves / Part55_Seasick` 在 `lock` 前补 `cant_see_if_trainerflag_set` |
| 6 | `patches\source-graphics-sync.patch` | `data/maps/{Route120,Route124,Route126,ScorchedGrotto,Route126_StillWaterCave}/map.json` | **未应用（无需）** | 基线已含等价修复：`WOMAN_5` / `RUNNING_TRIATHLETE_M` / `SPECIES(ENTEI)` / `SPECIES(SUICUNE)`；逐文件 SHA256 与基线一致 |

## B. 文件级前后哈希（SHA256 前 16 位）

| 文件 | 基线（11:50） | 当前 | 状态 |
| --- | --- | --- | --- |
| `asm/macros/battle_frontier/battle_tower.inc` | `B9CA5B834B33CB0B` | `5BB4E3664C5DF9D1` | CHANGED（补丁 #1） |
| `data/scripts/part55.inc` | `3A21988D5CD4EC4A` | `1265F357AA8E6BC7` | CHANGED（补丁 #2、#5） |
| `data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc` | `15394E9AE1A8233F` | `79F4A86FD661D1E9` | CHANGED（补丁 #3） |
| `data/scripts/story_b.inc` | `DD4E98D38B412C26` | `DD4E98D38B412C26` | 未改（待 #4） |
| `data/maps/Route120/map.json` | `21B116EC7CB7C0E1` | 同左 | 未改 |
| `data/maps/Route124/map.json` | `3961628C22F377EC` | 同左 | 未改 |
| `data/maps/Route126/map.json` | `C95D6D0312CD8D4B` | 同左 | 未改 |
| `data/maps/ScorchedGrotto/map.json` | `7462A79ED1B2980A` | 同左 | 未改 |
| `data/maps/Route126_StillWaterCave/map.json` | `F343132031F83189` | 同左 | 未改 |

## C. 补丁文件校验值（SHA256 前 32 位）

| 补丁 | SHA256 |
| --- | --- |
| `teamup-source.patch` | `999D79A683ACEBE9535EAD2C124C58C3` |
| `dialogue-source.patch` | `AA5CB7A07E4781B2BDABBE8957BDB3FA` |
| `source-graphics-sync.patch` | `F35471BDCE118E64721E10A74B869CB4` |

## D. 复现命令（可重放）

```
# 基线重建
copy /b project.tgz.part00 + project.tgz.part01 + project.tgz.part02 project.tar.gz
certutil -hashfile project.tar.gz SHA1      # 应为 111533267e903ccf4fbc26ec6439606845dc6a07
tar -xzf project.tar.gz                     # 解到 E:\Pekemon Gba\project

# 补丁应用（在 project 目录内）
git apply --include=asm/macros/battle_frontier/battle_tower.inc <patches>\teamup-source.patch
git apply --include=data/scripts/part55.inc                     <patches>\teamup-source.patch
git apply --include=data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc <patches>\teamup-source.patch
git apply <patches>\dialogue-source.patch
# story_b.inc 手工合并（见下文 F 节）
```

## E. 待办

- [ ] `story_b.inc` 手工变基（Rookie119 段 + RookieLava 段）
- [x] 工具链安装
- [ ] 构建
- [ ] 与现用 ROM 对比验证

## F. story_b.inc 手工合并明细（已执行）

补丁 `teamup-source.patch` 的第二个 hunk 无法直接应用，原因：Codex 产出该补丁时基于旧快照（`TRAINER_KAYLEE/TERRY`），而基线 11:50 版已被第二轮修复换成 `TRAINER_STORY_A_SPARE1/2`。按补丁意图在新上下文重新落位：

1. 第 477 行 `StoryB_Rookie119`：行尾追加 `, cancelScript=StoryB_Rookie119_Cancel`；在 `special SetCB2WhiteOut` 之后新增段：
   ```
   StoryB_Rookie119_Cancel::
   	fadescreen FADE_TO_BLACK
   	removeobject LOCALID_STORYB_119_SHARED
   	setflag FLAG_TEMP_1F
   	call_if_unset FLAG_STORY_B_11, StoryB_Rookie119_RestoreSaori
   	fadescreen FADE_FROM_BLACK
   	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
   	waitmovement 0
   	releaseall
   	end
   ```
2. 第 559 行 `StoryB_RookieLava`（保留第二轮的 `TRAINER_STORY_A_SPARE1/2` 槽位）：行尾追加 `, cancelScript=StoryB_RookieLava_Cancel`；新增段：
   ```
   StoryB_RookieLava_Cancel::
   	fadescreen FADE_TO_BLACK
   	removeobject LOCALID_STORYB_LAVA_GRUNT_A
   	removeobject LOCALID_STORYB_LAVA_GRUNT_B
   	setflag FLAG_TEMP_1E
   	fadescreen FADE_FROM_BLACK
   	releaseall
   	end
   ```

合并后校验：`story_b.inc` SHA256 前 16 位由基线 `DD4E98D38B412C26` 变为 `6DB8B3E7E82C5A0A`（以实测为准）；
与基线逐文件比对的结果：`src / data/scripts / data/maps / asm / include / constants` 六个目录共 3063 个文件，**仅 4 个文件不同**，与本表 A 节完全一致，无意外改动。

## G. docs/ai-handoff 迁移

基线 tarball **不含 `docs/` 内容**（`tar -tzf` 验证为空），因此从备份 `_backup\project-0909-快照\docs\ai-handoff\*.md` 复制四件套到 `project\docs\ai-handoff\`，作为历史接力记录保留；本轮结束前会按实际状态改写。

## H. 意外与偏差记录

- 补丁 `source-graphics-sync.patch` 未应用：基线已是正确值（第 5 行 A 表已注明），属"目标状态已达成"，非失败。
- 基线与旧快照在 `data/scripts/part55.inc` 的入口函数头完全同形，故 `dialogue-source.patch` 能带偏移干净应用（+7 行）。

## I. Windows 移植性修复（构建工具链相关）

| 文件 | 行 | 改动 | 原因 | 影响范围 |
| --- | --- | --- | --- | --- |
| `tools/preproc/c_file.cpp` | 210 | 格式符 `%ld` → `%zu` | Windows 是 LLP64：`long` 4 字节、`size_t` 8 字节。`-Werror=format=` 直接把该行判为编译错误，构建中止 | 仅宿主机工具 `preproc.exe`。该值是 `sh_entsize`，`%zu` 与 Linux(LP64) 下 `%ld` 输出同一十进制数，不改变 ROM 内容 |

原始行（基线，可据此还原）：

```cpp
std::printf("static const unsigned char __attribute__((section(\".rodata.compound_string.%016" PRIx64 ",\\\"aM\\\",%%progbits,%ld @\"))) sCompoundString_%016" PRIx64 "[] = {", it.second, it.first.size(), it.second);
```

修改后同行为 `%zu`，其余字节不变。这是本次为"在 Windows 上构建"付出的唯一源码改动；工具链改为 WSL 后可考虑还原，但保留亦无害（两种写法在 LP64 下等价）。

验证：`make tools` 由 exit=2 变为 exit=0，产出 15 个工具可执行文件。

## J. 命令行长度修复（Windows 32 KiB 限制）

**现象**：`make` 在生成 `include/constants/map_groups.h` / `map_event_ids.h` 时报
`tools/mapjson/mapjson.exe: Argument list too long`（错误 126），构建中止。

**实测根因**：`data/maps/*/map.json` 共 **964** 个，展开进命令行后
`total arg chars = 41343` > Windows `CreateProcess` 的 32767 上限。
（WSL/Linux 的 ARG_MAX 约 2 MiB，所以原 WSL 构建从未暴露这个问题；这与项目采用 expansion 后地图数量远多于官方版有关。）

**修复方式**：给 `mapjson` 增加 `@file` 参数展开（每个文件里的参数以空白分隔），Makefile 改用参数文件传递。

| 文件 | 改动 |
| --- | --- |
| `tools/mapjson/mapjson.cpp` | `main()` 开头新增 `@file` 展开：把 argv 收进 `vector<string> args`；以 `@` 开头的参数读入对应文件并按空白切分后插入；后续所有 `argv[i]` / `argc` 改为 `args[i]` / `nargs`。参数语义、错误信息、各模式判断均未改 |
| `map_data_rules.mk` | 新增 `MAP_JSON_LIST_GROUPS` / `MAP_JSON_LIST_EVENTS`（用延迟展开 `=`，因为 `OBJ_DIR` 在 recipe 期才确定）；`groups` 与 `event_constants` 两条规则改为先用 make 的 `$(file >…)` 写参数文件，再以 `@…` 传入；补 `@mkdir -p $(OBJ_DIR)` |

**为什么用 make 的 `$(file …)` 而不是 shell 重定向**：把 964 个路径写进 shell 命令行同样会超限；`$(file …)` 在 make 进程内完成，不经过命令行。

**等价性**：参数集合、顺序、内容完全一致，只是传输通道改变；`mapjson` 的输出字节不变。Linux 上该写法同样有效（向后兼容）。

**验证**：
- `tools/mapjson/mapjson.exe event_constants emerald @/tmp/test_list.txt /tmp/test_ids.h` → exit=0，产出 56 717 字节；
- 同一命令换成老式展开仍报 `Argument list too long`，证明问题定位准确。
- 完整 ROM 构建结果见 `_work/logs/rom-build-2.log`。

## K. 补齐三个 multiboot 二进制（tarball 遗漏）

**现象**：第 2 次构建（`rom-build-2.log`，耗时 1497 s，24184 行输出）编译全部通过，仅在汇编阶段报 3 个文件缺失：

```
data/multiboot_berry_glitch_fix.s:4: Error: file not found: data/mb_berry_fix.gba
data/multiboot_ereader.s:5: Error: file not found: data/mb_ereader.gba
data/multiboot_pokemon_colosseum.s:4: Error: file not found: data/mb_colosseum.gba
```

**根因**：`.gitignore` 含 `*.gba`，三份 multiboot 数据在打包 tarball 时被排除（全盘搜索、tarball 清单、旧快照三方都没有）。它们不是构建产物，是该仓库签入的固定二进制数据，全项目只有这 3 处 `.incbin "*.gba"` 引用。

**补齐清单**（已存入 `data/`，来源与校验见 `multiboot-files.txt`）：

| 文件 | 字节 | SHA1 | pret master vs expansion/1.17.1 |
| --- | --- | --- | --- |
| `mb_ereader.gba` | 12512 | `D4CDDDC84B3736CE17DF4403526B2C714ADA14DF` | IDENTICAL |
| `mb_colosseum.gba` | 163840 | `6CF444E998C39B74046C9715F3A07033B3262D12` | IDENTICAL |
| `mb_berry_fix.gba` | 15348 | `2EB0A94A913BEBFB4CB59CEB57F3F965DA55EF6D` | IDENTICAL |

两个上游分支逐字节相同，说明是长期固定的成品数据，取任一版本等价。

**来源 URL**：
`https://raw.githubusercontent.com/rh-hideout/pokeemerald-expansion/expansion/1.17.1/data/<name>`
