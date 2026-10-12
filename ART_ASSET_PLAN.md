# ART ASSET PLAN / 美术资产计划

更新：2026-10-09；执行 AI：Codex。范围：美术，不修改游戏代码。

## 权威位置与状态

权威：Windows普通文件夹 `D:\Pokemon gba\project` 的 ART 文档与 `art/`；入口 `D:\Pokemon gba` 同路径仅镜像。WSL仅编译缓存，不直接编辑；不得编辑旧 `source` 快照。

先读 Handoff Canon，再读本计划、ART_PROGRESS.md、ART_STYLE_GUIDE.md。游戏剧情当前推进 PART7，不以本轮美术任务改变游戏进度或构建记录。

状态：未开始 → 待参考 → 制作中 → 待确认 → 需修改 / 已确认 → 技术制作 → 技术检查通过 → 已归档。用户视觉确认与引擎兼容检查分别记录；已确认不等于已导入 ROM。一次只提交一个资产，只有当前资产获用户确认后才继续下一项；修改稿保留版本，不覆盖历史稿。

## 完整清单（严格按此顺序）

| 顺序 / ID | 批次 / 分类 | 资产 | 单资产拆分与用途 | 优先级 | 目录（art/ 下） | 状态 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 / ORG-01 | 第一批 / 组织 | 阿尔刻 Logo | 已确认无字符号 v3；以后按确认设计适配制服徽记、招牌、设施标识，不提前制作应用总图 | P0 | organization/arce_logo | v3 已确认 / 已归档；PNG与GBA转换检查通过；未集成 |
| 2 / CH-01 | 第一批 / 人物 | 安提 Anti | 正面战斗图＋完整地图小人，分别确认 | P0 | characters/anti | front-small-dual-v1 / ow-dual-v1已确认；未集成 |
| 3 / CH-02 | 第一批 / 人物 | 莱因 Rein | Trainer 正面战斗图 → Overworld 帧表，分别制作确认 | P0 | characters/rein | front-small-v7 / ow-v6已确认；未集成 |
| 4 / CH-03 | 第一批 / 人物 | 伊芙琳 Evelyn | Trainer正面与地图小人 | P0 | characters/evelyn | front-v2 / small-v1 / OW-v1均已确认归档；文件格式PASS；未集成 |
| 5 / CH-04 | 第一批 / 人物 | 萨维尔 Xavier | Trainer正面、标准OW、暮水钓鱼等待图 | P0 | characters/xavier | front-v1 / small-v1 / OW-v1 / fishing-v1均已确认归档；文件格式PASS；未集成 |
| 6 / UNI-01 | 第二批 / 组织 | 阿尔刻研究员制服 | 男 → 女，各自先确认单一制服基准；战斗/地图规格按实际使用点拆分，不提前批量制作 | P1 | organization/arce_uniforms | 男女外观/战斗/OW全部确认归档；文件格式PASS，未集成 |
| 7 / UNI-02 | 第二批 / 组织 | 阿尔刻战斗员制服 | 男 → 女，逐个确认；普通训练家服装语言，无机甲/组织干部夸张装饰 | P1 | organization/arce_uniforms | 男女外观/战斗/OW全部确认归档；文件格式PASS，未集成 |
| 8 / CH-05 | 第二批 / 人物 | 女熔岩团背面投球 | 仅补原制服背面四帧，不扩展其他素材 | P1 | characters/magma_female_back | back-v1已确认归档；64×256/16色/4bpp往返PASS；未集成 |
| 9 / IT-01 | 第三批 / 道具 | 本原调律器 | 单一道具图标，按用户概念板简化 | P1 | items/primal_tuner | icon-v1已确认归档；24×24/16色规格/4bpp往返PASS；未集成 |
| 10 / IT-02 | 第三批 / 道具 | 彼岸花 | 用户授权本批道具并行候选；按原概念板简化 | P1 | items/asphodel_flower | icon-v1已确认归档；24×24/16色规格/4bpp往返PASS；未集成 |
| 11 / IT-03 | 第三批 / 道具 | 星之钥匙 | 用户授权本批道具并行候选；按原概念板简化 | P1 | items/star_key | icon-v1已确认归档；24×24/16色规格/4bpp往返PASS；未集成 |
| 12 / IT-04 | 第三批 / 道具 | 来历不明的研究数据 | 用户授权本批道具并行候选；按原概念板简化 | P1 | items/unknown_research_data | icon-v1已确认归档；24×24/16色规格/4bpp往返PASS；未集成 |
| 13 / PK-01 | 第四批 / 宝可梦 | 白色复制裂空座 | 原GBA素材，仅白/冷灰调色板，不重设计 | P1 | pokemon/white_rayquaza | palette-v1正面两帧/背面已确认归档；文件检查PASS；field-v1图标两帧/OW六帧已确认归档；基础素材齐；未集成 |
| 14 / TILE-01 | 第五批 / 建筑 | 阿尔刻总部外观方向 | 卡纳兹原作风格参考；总部地点水静不变 | P4 | tilesets/arce_hq_exterior | city-v3视觉定稿；总部原生已批准；native-city-v1退回；训练馆待确认；redraw-v2已确认；native-v2待确认；未集成 |
| 15 / TILE-02 | 第五批 / 室内 | 阿尔刻总部室内基础设施 | 使用原绿宝石室内尺度，先基础模块；不开放当前封闭楼层 | P4 | tilesets/arce_hq_interior | 原生整批v1已退回，redraw-v2已确认；native-v2已制作待视觉确认；未集成 |
| 16 / TILE-03 | 第五批 / 城市 | 卡纳兹市阿尔刻街区素材 | 用户已要求园区整张城市地图统一阿尔刻风格；全图方向先确认，原生模块随后制作 | P4 | tilesets/rustboro_arce_cityset | 原生整批v1已退回，redraw-v2已确认；native-v2已制作待视觉确认；未集成 |
| 17 / PROP-01 | 第五批 / 小物件 | 常用科技 / 研究设施 | 终端 → 门禁 → 培养舱 → 标识牌等单件；具体清单随参考确认，禁止一轮批量出图 | P4 | tilesets/props | 原生整批v1已退回，redraw-v2已确认；native-v2已制作待视觉确认；未集成 |

## 交付与归档

- 待确认候选保存所属目录 `review/`，文件名含版本；记录实际参考来源、提示词、尺寸、格式、验证范围。`approved/` 只存用户确认且完成相应技术检查的版本。
- `confirmed-design/` 可保存用户已确认但未完成GBA技术制作的设计参考，必须标明不是可用游戏资源；不与 `approved/` 混用。
- 新参考原件保留不覆盖；复制到 `art/docs/references/<asset-id>/` 后记录来源。原作资源通过仓库路径引用，不重复伪造一份官方原件。
- 单次交付：名称、用途、本轮内容、参考来源、风格理由、版本、相对上版变化、状态、保存位置、通过建议。用户说通过前不升级已确认，不推进下一资产。
- 全部完成并确认后才制作 `art/sheets/` 总览和 `ART_INDEX.md`，更新本表与进度；现在不制造整批“已定稿”索引。

## 明确不做

不做 CG、表情差分、半身像 / 对话头像、复杂服装阶段、大批路人原创。无限船票复用原作。普通 NPC 优先复用官方素材。不得新增设定、剧情、游戏代码或开放楼层。

2026-10-08更新：CH-01最新确认外观为visual-v3；原生技术v1视觉退回，v2内部试稿需修改；OW未开始。

最新CH-01：v4审阅候选待确认；v3保持已确认外观；原生v1/v2视觉作废，未进入approved，OW未开始。

CH-01最新交付：small-v3 64×64试稿，文件格式检查通过、视觉待确认；见art/docs/CH-01_SMALL_V3.md。

## 最新视觉方向校正（2026-10-09）
阿尔刻按研究机构视觉推进，不以已做工装夹克自动扩成整套队服。用户概念板已保存；图内角色/制服分别确认、GBA像素风要求保持。既有批准资产不覆盖，当前只修伊芙琳。

2026-10-09：CH-03 伊芙琳原生战斗图 small-v1 已制作，格式PASS，待视觉确认；OW未制作。见 art/docs/CH-03_SMALL_V1.md。

2026-10-09：CH-03 伊芙琳small-v1用户已确认归档；OW-v1九帧文件检查PASS、视觉待确认，未集成。见 art/docs/CH-03_OW_V1.md。

2026-10-09用户调整制作顺序：重做安提→莱因，旧稿保留。安提一周目无组织标志、二周目有；正面front-v4双版候选待确认，原生64×64与新OW未制作。伊芙琳OW-v1仍待确认。报告art/docs/CH-01_FRONT_V4_DUAL.md。

2026-10-09：用户接受安提v4人物/二周目方向，要求一周目便服。front-v5便服候选待确认；原生双版未制作。报告art/docs/CH-01_FRONT_V5_CASUAL.md。

2026-10-09：安提v5便服被退回；v6米色短外套候选待确认。见art/docs/CH-01_FRONT_V6_CASUAL.md；原生双版未制作。

2026-10-09：安提front-v6一周目便服用户确认并归档confirmed-design；二周目白外套方向已确认。下一步制作新版64×64双版；OW双版尚未制作。

2026-10-09：CH-01 安提实际64×64双版small-dual-v1完成，格式PASS，视觉待确认；新OW双版未制作。报告art/docs/CH-01_SMALL_DUAL_V1.md。

2026-10-09：安提战斗small-dual-v1用户确认归档；OW-dual-v1两版各九帧制作及格式PASS，视觉待确认。报告art/docs/CH-01_OW_DUAL_V1.md。

2026-10-09：安提新版战斗/OW双版均确认归档。莱因重做front-v4研究服方向候选待确认；新版原生战斗/OW未制作。报告art/docs/CH-02_FRONT_V4.md。

2026-10-09：莱因front-v4用户确认归档；原生64×64 small-v5格式PASS、视觉待确认，新OW未制作。见art/docs/CH-02_SMALL_V5.md。

2026-10-09：莱因small-v5脸部退回；small-v6仅重做头部，身体不变，格式/范围PASS、视觉待确认。报告art/docs/CH-02_SMALL_V6.md。

2026-10-09：莱因small-v6头身衔接被指出问题；small-v7仅颈部/衣领局部修订，格式/范围PASS、视觉待确认。报告art/docs/CH-02_SMALL_V7.md。

2026-10-09：莱因small-v7战斗图已确认归档；新版OW-v6九帧文件/连通检查PASS，视觉待确认。报告art/docs/CH-02_OW_V6.md。

2026-10-09：莱因OW-v6用户确认并归档approved/ow-v6；新版战斗及OW均通过。下一项是伊芙琳OW-v1的用户确认，随后萨维尔；不提前批准或制作新资产。

### 2026-10-09 — Codex：伊芙琳OW确认 / 萨维尔front-v1
用户“通过，请继续”确认伊芙琳OW-v1，九帧归档approved/ow-v1。萨维尔front-v1外观候选已保存待确认；原生战斗图/OW未制作。见art/docs/CH-04_FRONT_V1.md。未集成ROM，未改游戏代码/构建，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：萨维尔外观确认 / small-v1
用户“可以”确认front-v1外观并归档confirmed-design；实际64×64 small-v1已制作，16色/4bpp索引往返检查PASS，视觉待确认。见art/docs/CH-04_SMALL_V1.md；OW未制作，未集成ROM。游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：萨维尔战斗确认 / OW-v1
用户确认small-v1并归档approved/front-small-v1；OW-v1完整九帧和四向素材步态预览完成，16色/4bpp往返/头部一致性/主体头脚连通检查PASS，视觉待确认。见art/docs/CH-04_OW_V1.md；未集成ROM。游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：萨维尔OW确认 / 钓鱼素材补项
标准OW-v1用户通过并归档。核对PART4_FINAL及暮水Actor，确认钓鱼姿态曾漏列；增加南向持竿等待fishing-v1（32×32/16色/4bpp往返PASS），视觉待确认。见art/docs/CH-04_FISHING_V1.md。当前地图仍绅士占位；未集成、未改游戏代码或构建，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：萨维尔钓鱼确认 / 第一批人物完成
用户“全部通过”确认fishing-v1，归档approved/fishing-v1并记录批准原话。Logo、安提双版、莱因、伊芙琳、萨维尔现有战斗/标准OW及萨维尔钓鱼等待图均已确认；文件检查范围见各资产报告，未集成ROM。下一资产为研究员制服男，未开始。游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：男性研究员制服候选
按既定第二批顺序制作UNI-01 male front-v1单张制服外观，参考用户概念板/已批准干部研究服及原作Scientist；待确认，非原生GBA资源。见art/docs/UNI-01_MALE_FRONT_V1.md。尚未制作女性制服或战斗员，未改Canon/游戏代码/构建，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：男性研究员外观确认 / small-v1
用户“通过”确认front-v1并归档。实际64×64 /16色 small-v1完成并修整原生镜框/眼睛，4bpp往返检查PASS，视觉待确认；见art/docs/UNI-01_MALE_SMALL_V1.md。OW/女研究员未制作，未集成；游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：男性研究员战斗确认 / OW-v1
用户“通过”确认small-v1并归档。OW-v1九帧和四向步态素材预览完成，16色/4bpp往返/头部一致性/头脚连通检查PASS，视觉待确认；见art/docs/UNI-01_MALE_OW_V1.md。女研究员未开始，未集成；游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：男性研究员OW确认 / 女性制服候选
用户“通过，请继续”确认男OW-v1并归档；男性制服外观/战斗/OW均确认。女性研究员front-v1单张候选已保存待确认，原生战斗/OW未制作；见art/docs/UNI-01_FEMALE_FRONT_V1.md。未集成ROM，游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：女性制服外观确认 / small-v1
用户确认front-v1并归档。制作实际64×64女性研究员small-v1，复用男版16色并修整原生双眼/眉毛；4bpp往返PASS，视觉待确认，见art/docs/UNI-01_FEMALE_SMALL_V1.md。女OW未制作，未集成；游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：女性研究员战斗确认 / OW-v1
用户确认女small-v1并归档。女OW-v1九帧和四向步态素材预览完成，16色/4bpp往返/头部一致性/头脚连通检查PASS，视觉待确认；见art/docs/UNI-01_FEMALE_OW_V1.md。战斗员未开始，未集成；游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：女性研究员OW确认 / 男战斗员候选
用户确认女OW-v1并归档，男女研究员三项均确认。男战斗员front-v1单张外观候选已保存待确认，原生/OW未制作；见art/docs/UNI-02_MALE_FRONT_V1.md。女战斗员未开始，未集成；游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：男战斗员外观确认 / small-v1
用户确认front-v1并归档。实际64×64男small-v1完成，固定16色并补回精灵球红白，4bpp往返PASS，视觉待确认；见art/docs/UNI-02_MALE_SMALL_V1.md。男OW/女战斗员未制作，未集成；游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：男战斗员战斗确认 / OW-v1
用户确认small-v1并归档。OW-v1完整九帧和四向素材步态完成，清理3颗游离杂点，16色/4bpp往返/头部一致性/头脚连通PASS，视觉待确认；见art/docs/UNI-02_MALE_OW_V1.md。女战斗员未开始，未集成；游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：男战斗员OW确认 / 女性制服候选
用户确认男OW-v1并归档。女战斗员front-v1外观候选已保存待确认；带背景光晕，去背景编辑被图像工具拒绝，未产出修订，非透明/原生合格资源。见art/docs/UNI-02_FEMALE_FRONT_V1.md。原生/OW未制作，未集成；游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：女战斗员外观确认 / 小图工具阻塞
用户确认front-v1并归档confirmed-design。内置imagegen小图生成被输出安全审核拒绝（moderation_blocked/other），无成图；原生战斗图及OW仍未完成，不标PASS。见art/docs/UNI-02_FEMALE_SMALL_STATUS.md。未集成，游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：女性战斗员小图重试成功
用户要求重试，内置imagegen按原小图要求成功返回；实际small-v1已生成64×64/16色二值透明PNG及GBA二进制，索引往返PASS，视觉待确认。见art/docs/UNI-02_FEMALE_SMALL_V1.md。历史工具失败保留，当前阻塞解除；女OW未制作，未集成，游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：女性战斗员战斗确认 / OW-v1
用户确认small-v1并归档。OW-v1完整九帧和四向素材动画完成，16色/4bpp往返/头部一致性/头脚连通检查PASS，视觉待确认；见art/docs/UNI-02_FEMALE_OW_V1.md。下一资产女熔岩团背面投球尚未开始，未集成；游戏代码/构建不变，无GUI/模拟器/ROM执行。

### 2026-10-09 — Codex：女战斗员OW确认 / 女Magma背面调查
用户确认女OW-v1并归档；两类男女制服均完成视觉确认。核对原May四帧背面投球64×256及Hoenn帧序，记录原女Magma红兜帽/深蓝紫发要求。新图生成被imagegen输出审核拒绝（other），无产物；见art/characters/magma_female_back/SPEC.md。未集成/未改游戏代码构建，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：女Magma背面投球重试成功 / back-v1
用户要求多次重试，本轮第1次仍被输出审核拒绝，第2次返回图像后停止。back-v1四张64×64帧完成分辨率转换，复用原女Magma16色调色板；64×256 PNG、8192字节4bpp、32字节调色板及索引往返检查PASS。视觉待确认，投球帧序0→1→2→0→3素材预览已保存。见art/docs/CH-05_BACK_V1.md。尚未导入ROM；游戏代码/构建状态不变，无GUI/模拟器/ROM执行。历史失败保留，当前生成阻塞解除。


### 2026-10-09 — Codex：女Magma back-v1确认
用户“通过，请继续”确认背面投球四帧back-v1，归档art/characters/magma_female_back/approved/back-v1。视觉确认及文件格式PASS分别记录，未集成ROM。下一资产本原调律器；只制作道具美术，不改天气系统/剧情/游戏代码，不启动GUI/模拟器/ROM。


### 2026-10-09 — Codex：本原调律器icon-v1
沿用用户概念板白灰外壳/深色面板/青蓝圆环方向，参考原Devon Scope和VS Seeker的24×24图标规格，生成单一候选并转换为可编辑索引稿。PNG/288字节4bpp/32字节调色板及往返检查PASS；视觉待确认，未集成。见art/docs/IT-01_ICON_V1.md。调律器功能Canon、游戏代码及构建均未改；无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：关键道具三件批量候选
用户明确要求道具一次多做几个，本轮例外批量制作IT-02彼岸花、IT-03星之钥匙、IT-04来历不明的研究数据icon-v1；均24×24、透明、16色预算、288字节4bpp/32字节调色板与往返PASS。原生索引修回绿花茎和钥匙蓝色中心；三件视觉待确认，本原调律器也仍待确认。见art/docs/ITEM_BATCH_V1.md。不把批量授权视为资产批准；未集成、不改游戏代码/构建，不启动GUI/模拟器/ROM。


### 2026-10-09 — Codex：四件关键道具icon-v1全部确认
用户“全部通过”确认IT-01本原调律器、IT-02彼岸花、IT-03星之钥匙、IT-04来历不明的研究数据icon-v1；分别归档art/items/<对应目录>/approved/icon-v1，保存原话approval.json。四件24×24/16色预算/透明/4bpp与往返检查PASS；视觉批准与未集成ROM分别记录。下一待办白色复制裂空座，尚未开始；其他游戏设计Canon不变，未改游戏代码或构建，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：白色复制裂空座palette-v1
复用原GBA版anim_front_gba.png两帧及back_gba.png，只把normal_gba.pal的绿色索引1–5换为白/冷灰；其余颜色及全部原像素索引完全一致。正面64×128/背面64×64、透明、4bpp往返和32字节调色板PASS；视觉待确认，未集成。见art/docs/PK-01_PALETTE_V1.md。imagegen颜色参考编辑另被输出审核拒绝，未返回AI成图；交付来自可编辑原生调色板。现有P_GBA_STYLE_SPECIES_GFX=FALSE未改，集成时需局部选择GBA素材，禁止为此全局切换；等级/种族值/Mega等Pending不变。无游戏代码/构建变更，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：白色复制裂空座palette-v1确认
用户“通过”确认原GBA正面两帧/背面白冷灰重配色；归档art/pokemon/white_rayquaza/approved/palette-v1，保存原话及范围。原像素索引一致/文件格式PASS，视觉CONFIRMED，未集成ROM。队伍图标/地图小人尚未制作；Mega资格和其他Pending机制不因美术批准变更。下一步先按批准配色补普通队伍图标/地图小人，再继续地图素材。游戏代码/构建不变，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：白色裂空座field-v1
沿用已批准白/冷灰配色，原生调色板派生icon_gba.png队伍图标两帧及Expansion现有overworld.png地图六帧；不重绘、不新增跟随系统。各自原像素索引完全一致、非身体颜色不变、透明/逐帧4bpp往返PASS；视觉待确认，未集成。见art/docs/PK-01_FIELD_V1.md。此前战斗palette-v1仍已批准；Mega及其他未知机制不变，无游戏代码/构建变更，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：白色裂空座field-v1全部确认
用户“全部通过”确认队伍图标两帧与地图六帧field-v1，归档art/pokemon/white_rayquaza/approved/field-v1，保存确认原话。与此前已批准战斗palette-v1一起，普通形态正面/背面/图标/地图基础素材全部视觉确认及文件格式PASS，仍未集成ROM。Mega/等级/种族值等Pending不变。下一待办总部外观方向（卡纳兹建筑风格参考；丰缘总部地点按Canon水静，不迁移）。未改游戏代码/构建，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：总部外观exterior-v1候选
核对原Rustboro与ArcheCampus地图及tileset，以无GUI静态渲染提供原作Devon建筑参考；生成一栋白灰墙/灰蓝屋顶/简洁入口/小A牌的总部外观方向候选，保存art/tilesets/arce_hq_exterior/review/exterior-v1。仅大图视觉参考，未拆原生tile、未检16色bank/碰撞/门动画，不标引擎资源PASS；用户待确认。总部位置保持水静，卡纳兹仅风格参考。现ArcheCampus仍沿用Rustboro布局，本轮未修改。见art/docs/TILE-01_EXTERIOR_V1.md。游戏代码/构建不变，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：总部外观保留 / 园区全图city-v1
用户明确要求整个城市地图有阿尔刻风格，并保留exterior-v1总部外观；已归档confirmed-design/exterior-v1（视觉方向通过，原生tile未制作）。以现有ArcheCampus 40×60布局为范围，生成campus-city-v1全图候选，统一建筑/铺地/绿化/公共设施；地图原12入口及连接约束另存JSON。仅外观候选待确认，不是地图实现/碰撞或tile验收。总部仍水静，未迁移、不改游戏代码/地图/构建，无GUI/模拟器/ROM执行。见art/docs/TILE-01_CAMPUS_CITY_V1.md。


### 2026-10-09 — Codex：园区整图city-v2重排
用户反馈city-v1太像卡纳兹，标为需修改并保留历史；生成city-v2，保留已接受总部建筑，改北侧总部+中央草地水池花园环路/错落建筑/西侧滨水步道，减少大面积石板与原卡纳兹中轴布局。仅全图视觉候选待确认，未制作原生tile，未改游戏地图或事件。新布局未来需重排原入口/NPC/连接与碰撞，不假设原坐标可直接沿用。见art/docs/TILE-01_CAMPUS_CITY_V2.md。总部城市Canon不变，无代码/构建变化，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：园区city-v3训练馆微调
用户认可v2基本方向，要求训练馆小改且不要全城同灰蓝。city-v3保留v2视觉布局与已接受总部，只将训练馆改暖赭/陶土屋顶、短顶窗/普通雨棚入口，降低道馆感；原生tile未制作，整图视觉最终待确认。见art/docs/TILE-01_CAMPUS_CITY_V3.md。v2记需小改，历史保留；本轮不自动标整图通过。游戏地图/代码/构建不变，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：园区city-v3视觉定稿
用户“通过”确认整图campus-city-v3，归档art/tilesets/arce_hq_exterior/confirmed-design/campus-city-v3（FINALIZED视觉方案）。保留总部exterior-v1、中央花园环路/滨水步道/错落街区及暖赭训练馆特色，不全灰蓝。该批准不等于原生tile、map.bin、入口/碰撞实现或测试；全部仍未实施，当前游戏地图不变。下一步为外观原生tile/整图技术制作，随后室内/配套素材；已有原12入口和NPC约束须重映射验证。无代码/构建变化，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：总部native-hq-v1像素技术稿
按已定稿外观独立构建160×144原生可编辑索引稿，未缩小概念图；拆成113个去重8×8 tile、一套16色bank和10×9本地metatile布局。4bpp3616字节、调色板32字节、二进制metatile重建与PNG像素逐一一致/透明检查PASS。技术稿视觉待确认，未集成ROM；实际bank/tileset偏移/碰撞/门动画未分配。见art/docs/TILE-01_HQ_NATIVE_V1.md。整张园区原生地图仍未完成，不升级为游戏IMPLEMENTED或TESTED。无代码/构建变化，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：总部native-hq-v1批准归档
用户“没问题通过”确认160×144原生总部稿，归档art/tilesets/arce_hq_exterior/approved/native-hq-v1，记录原话。113个tile/一套调色板/本地metatile与像素重建检查PASS；原生美术已制作并视觉批准，不等于游戏地图IMPLEMENTED。实际bank/offset、碰撞、门动画及整张园区未完成，未导入ROM。下一项暖色训练馆原生模块，沿用city-v3形制与配色原则。游戏代码/地图/构建不变，无GUI/模拟器/ROM执行。


### 2026-10-09 — Codex：训练馆native-training-v1
按city-v3已定稿暖色训练馆重建128×80原生索引稿，保留暖赭低平屋顶/短顶窗、普通双门雨棚、宽窗与小侧A牌，无道馆标识。54个去重tile、一套16色bank、8×5本地metatile，4bpp1728字节/调色板32字节/二进制重建与透明检查PASS，视觉待确认。见art/docs/TILE-01_TRAINING_NATIVE_V1.md。整城未完成，实际bank/offset/碰撞/门动画未绑定，未导入ROM；无游戏代码/地图/构建改动，无GUI/模拟器/ROM执行。

## 当前批量交付规则 / 2026-10-09
用户“一次性做完”覆盖本轮逐件暂停规则：剩余园区、配套建筑、室内基础与设施统一交付，但不自动视觉批准。索引ART_INDEX.md是现有批准资产与新候选的状态索引，不代表全体最终通过。详细范围见art/docs/NATIVE_CAMPUS_BATCH_V1.md。

## 最新纠正 / 2026-10-09
原生整批v1美术已退回，旧zip仅留历史不可作为通过资源。两张重绘v2见art/docs/CAMPUS_REDRAW_V2.md，仅视觉候选，尚无新原生替代包。

## 最新原生版本 / 2026-10-09
redraw-v2参考已获用户批准。当前原生外景art/tilesets/arce_hq_exterior/review/native-city-v2/，室内art/tilesets/arce_hq_interior/review/native-interior-v2/；11栋建筑在rustboro_arce_cityset/review/native-batch-v2，10类设施在props/review/native-batch-v2。原生v2文件检查PASS、视觉待确认、未集成。新清单art/docs/native-campus-v2-manifest.json及规格NATIVE_CAMPUS_V2.md。旧v1退回；此前总部与其他批准素材保留。

## 原作对照v3 / 2026-10-09
外景native-city-v3、建筑rustboro_arce_cityset/review/native-batch-v3、大厅original-based-v3为最新待审阅底稿。原作材质/尺度已落实，概念完整适配未完成。native-interior-v3与props/native-batch-v3是生成器复用v2中间输出，不作为本轮交付。详见art/docs/ORIGINAL_STYLE_V3.md。

## 当前设计约束 / 2026-10-09
用户否决native-city-v3的卡纳兹搬用外观。原作仅用于像素比例/阴影/材质参考；建筑必须保留已批准阿尔刻三翼总部、灰蓝屋顶、米白墙、蓝玻璃、小A牌与暖色训练馆设计。总部hq-identity-v4为最新单模块候选（原生格式PASS、视觉未批准）；整城没有完成。见art/docs/HQ_IDENTITY_V4.md。

## CH-06 / 2026-10-10：退队女新人便服概念
用户授权先设计概念，并指定多参考瑟蕾娜/小光。保留原深蓝紫发、胖丁伙伴，不新增姓名/年龄/剧情。内置imagegen三次输出审核拒绝，无成图；状态DESIGN/工具阻塞，不是已完成资产。服装提案未获确认，无原生Sprite/ROM集成。报告 art/docs/CH-06_CASUAL_CONCEPT_STATUS.md。

## CH-06 / 2026-10-10：便服概念确认 / 战斗图v2
用户“就以这个开做吧”确认便服概念，归档art/characters/magma_female_casual/confirmed-design/concept-v1。简短中文生成成功，旧输出审核失败记录保留；仅外观确认，不新增姓名/年龄/剧情。
small-v1实际小图脸/鞋细节不足，保留并标需修改；small-v2完成64×64、16项调色板、二值透明、GBA五位色及4bpp/gbapal往返检查PASS，视觉待确认、未集成。实际8倍预览位于review/small-v2/casual-small-v2-preview-8x.png。报告art/docs/CH-06_SMALL_V2.md。OW未制作，先确认/修订战斗小图；游戏代码/构建/存档不变，无GUI/模拟器/ROM执行。


CH-06 / 2026-10-10：small-v2 脸部需修改；small-v3 脸部修订、原生格式检查 PASS，视觉待确认，未集成。见 art/docs/CH-06_SMALL_V3.md。

CH-06 small-v4：实际 64×64 眼神修订，8 个眼部像素变更，格式检查 PASS，视觉待确认；v3 需修订，未集成。见 art/docs/CH-06_SMALL_V4.md。

CH-06 small-v5：64×64 闭口微笑修订，格式 PASS，视觉待确认；v4 需修改，未集成。见 art/docs/CH-06_SMALL_V5.md。
