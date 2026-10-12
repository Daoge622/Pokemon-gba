# 04 手套小兵战后卡死修复（根因 + 改动 + 产物）

日期：2026-10-11
用户报告：「胖丁女孩打完没卡死，但是打手套小兵卡死了」，并要求同类一并排查。
实际执行：Claude。

## 1. 用户提供的对照事实（关键）

| NPC | 用户实测 | 脚本结构 |
| --- | --- | --- |
| 胖丁女孩 `Part55_RookieFormal` | **正常** ✅ | `trainerbattle_single …, Part5_MagmaRookie_Defeated`（**有第 4 参**） |
| 手套小兵 `Part55_MagmaGloves` | **卡死** ❌ | `trainerbattle_single …`（**省略第 4 参**） |

## 2. 根因

`trainerbattle_single` 的宏签名是：

```asm
.macro trainerbattle_single trainer:req, intro_text:req, lose_text:req, event_script=FALSE, music=TRUE
```

- **第 4 参有值**（女孩）：`trainerbattle` 会带上 `event_script`，战斗胜利后**跳转**到专用战后脚本，那条路径自带 `lock → msgbox → release → end` 配对。
- **第 4 参缺省**（手套/便当）：展开成 `event_script = FALSE` → 宏内走 `trainerbattle … NULL …` 分支，战斗胜利后**继续留在当前脚本**里，裸跑：

```asm
MagmaHideout_2F_1R_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, …Intro, …Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end
```

调用方 `Part55_MagmaGloves` 在这之前已经 `release` 过，所以战斗结束时玩家处于**无脚本锁**状态，战后 `msgbox` 没有 `lock` 包围 —— 与女孩那条"跳转进带锁战后脚本"的路径不一致。这就是同一房间里三个小兵表现不同的原因。

## 3. 改动（2 个文件，4 处）

### 3.1 `data/maps/MagmaHideout_2F_1R/scripts.inc`

补第 4 参（其余字节不变）：

```diff
 MagmaHideout_2F_1R_EventScript_Grunt4::
-	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, …Grunt4Intro, …Grunt4Defeat
+	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, …Grunt4Intro, …Grunt4Defeat, Part55_MagmaBento_Defeated
 	msgbox MagmaHideout_2F_1R_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
 	end

 MagmaHideout_2F_1R_EventScript_Grunt5::
-	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, …Grunt5Intro, …Grunt5Defeat
+	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, …Grunt5Intro, …Grunt5Defeat, Part55_MagmaGloves_Defeated
 	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
 	end
```

保留 `msgbox … MSGBOX_AUTOCLOSE; end` 作为非胜利路径（逃跑/战败）的既有行为，未改动。

### 3.2 `data/scripts/part55.inc`

在既有 `_After` 之后各新增一段带锁配对的战后入口：

```asm
Part55_MagmaBento_Defeated::
	lock
	msgbox Part55_Text_0256, MSGBOX_DEFAULT
	release
	end

Part55_MagmaGloves_Defeated::
	lock
	msgbox Part55_Text_0258, MSGBOX_DEFAULT
	release
	end
```

文本复用既有的 `_After` 文本（0256 / 0258），不新增文本、不新增 Flag/Var、不改地图对象与行走类型。

## 4. 影响面核查

- `MagmaHideout_2F_1R_EventScript_Grunt4/5` 在**全仓库仅被** `part55.inc:2958 / 2974` 引用（`grep` 结果 2 处），改动不会波及其它流程。
- 新增标签各出现 2 次（定义 1 + 引用 1），闭合正确。

## 5. 构建产物

| 版本 | SHA1 | SHA256 |
| --- | --- | --- |
| 修复前（源码构建首版） | `B526D5A36D589ED14B9238AE32C416C8DAC25B89` | `6FF9EE5BC9F9C976A37D2A6C7B3ADEA2DCFB51967992B1C0CEE5E7AA702B952F` |
| **本次修复版** | `79E0CF16D369A26617DB7B9A1FD0261FE17C98EB` | `826EB52C39B5E0B7BC9E2C64CD74B1EF27F738A9A5349791888A688C0E13220F` |

- 目录占用：ROM 27495860 B（81.94%），较修复前 +32 B —— 与"新增 2 个脚本块"一致。
- 归档：`_work\artifacts\EmeraldStory-源码构建-手套修复-20261011.gba`、`pokeemerald-glovesfix.map`
- 备份（改动前原文）：`_work\留痕\backups\gloves-fix\`
- 构建日志：`_work\logs\rom-build-3.log` 之后本次为 `/tmp/gloves-fix-build.log`（`make_exit=0`）

## 6. 未验证项（不得声称已完成）

- 本次**未做战斗内实机验证**（无窗口 mGBA 里把这场战斗从开打到胜负完整打一遍需要精确的战斗按键脚本，尚未建立）。
- 修复依据是「用户对照实测 + 两处脚本结构差异」，属强证据但**非全流程实测**。
- 便当小兵 `Part55_MagmaBento` 结构同源，一并按同一方式修复，同样待实测。
- 全库其它 `trainerbattle_single` 缺省第 4 参的用法**未做等价性判定**（原版地图脚本大量使用该写法，不能一概视为缺陷；本次只改了用户实测异常的这两个）。
