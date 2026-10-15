@ PART 4 shared events. Terminal builds only.

Part4_Text_001:
	.string "背包已经满了。整理出空位再来吧。$"

Part4_BagFull::
	msgbox Part4_Text_001, MSGBOX_DEFAULT
	releaseall
	end

Part4_QuietEnd::
	releaseall
	end

Part4_Text_002:
	.string "这里地方不大，来往的船倒是不少。\p有时候外地的新鲜玩意儿，\n比本岛还先运到这里呢。$"

Part4_Text_003:
	.string "釜炎仙贝在外地也很好卖。\p就是走海运的时间一长，容易压碎。$"

Part4_Text_004:
	.string "有些设备是丰缘造的，零件却得从\n外地订。\p只要装好能正常运转，我就满意了。$"

Part4_Text_005:
	.string "流星瀑布采来的样本很特别。\p我们也会寄一些给外地的同行，\n大家一起分析。$"

Part4_Text_006:
	.string "朋友一直推荐我来丰缘旅行。\p这儿的温泉比传闻中还要舒服！$"

Part4_Text_007:
	.string "我们会定期和其他地区的研究机构\n交换海洋观测资料。$"

Part4_Text_008:
	.string "偶尔还会有外地客人专程跑来，\n就为了订我们的自行车！$"

Part4_Text_009:
	.string "系统常常收到其他地区开发者的反馈。\p每个地方的人用盒子的习惯，\n真的很不一样呢。$"

Part4_Text_010:
	.string "别看这里到处都是沙子。\p只要找得到水，总会有生命活下来。$"

Part4_OasisTraveler::
	msgbox Part4_Text_010, MSGBOX_NPC
	end

Part4_OasisTrapinch::
	lock
	faceplayer
	playmoncry SPECIES_TRAPINCH, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part4_PitTrapinch::
	lock
	faceplayer
	playmoncry SPECIES_TRAPINCH, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part4_Text_011:
	.string "我刚才差点一脚踩进大颚蚁挖的坑\n里，吓死我了！$"

Part4_PitCamper::
	msgbox Part4_Text_011, MSGBOX_NPC
	end

Part4_Text_012:
	.string "我的水壶在沙暴里弄丢了。\p风是往南刮的，应该落在南边那片\n沙地的东侧。\p你要是看到了，能帮我带回来吗？$"

Part4_Text_013:
	.string "太好了，是我的水壶！我都开始盘算\n要不要靠仙人掌撑到晚上了。\p这块石头是谢礼，请收下吧。$"

Part4_Text_014:
	.string "多亏了你，我总算不用渴着赶路了。$"

Part4_Text_015:
	.string "找到了一个水壶。\n先带回去还给失主吧。$"

Part4_Canteen::
	lock
	faceplayer
	goto_if_eq VAR_PART4_CANTEEN, 2, Part4_Canteen_Done
	checkitem ITEM_TRAVELER_CANTEEN
	goto_if_eq VAR_RESULT, TRUE, Part4_Canteen_Return
	msgbox Part4_Text_012, MSGBOX_DEFAULT
	release
	end
	Part4_Canteen_Return::
	msgbox Part4_Text_013, MSGBOX_DEFAULT
	giveitem ITEM_SMOOTH_ROCK, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	removeitem ITEM_TRAVELER_CANTEEN, 1
	setvar VAR_PART4_CANTEEN, 2
	Part4_Canteen_Done::
	msgbox Part4_Text_014, MSGBOX_DEFAULT
	release
	end

Part4_Canteen_Find::
	lockall
	goto_if_ge VAR_PART4_CANTEEN, 1, Part4_QuietEnd
	msgbox Part4_Text_015, MSGBOX_DEFAULT
	giveitem ITEM_TRAVELER_CANTEEN, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setvar VAR_PART4_CANTEEN, 1
	special StoryRefreshPickupMarkers
	releaseall
	end

Part4_Text_016:
	.string "沙子下面露出一块形状奇特的石头。\n摸上去还带着一点温度。$"

Part4_Text_017:
	.string "这里只剩下一些碎石了。$"

Part4_FirstEvolutionStone::
	lock
	faceplayer
	goto_if_set FLAG_PART4_FIRSTEVOLUTIONSTONE, Part4_FirstEvolutionStone_After
	msgbox Part4_Text_016, MSGBOX_DEFAULT
	giveitem ITEM_EVOLUTION_STONE, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_FIRSTEVOLUTIONSTONE
	special StoryRefreshPickupMarkers
	Part4_FirstEvolutionStone_After::
	msgbox Part4_Text_017, MSGBOX_DEFAULT
	release
	end

Part4_Text_018:
	.string "墙壁被风沙侵蚀得很厉害。\p细沙正不停地从石缝里落下来。$"

Part4_MirageWall::
	msgbox Part4_Text_018, MSGBOX_NPC
	end

Part4_Text_019:
	.string "终于要去挑战爸爸了吗？\p他嘴上不说，其实一直盼着这一天。\p别紧张，像平常那样去比赛就好！$"

Part4_Text_020:
	.string "你和爸爸真是一个样，\n对战的时候谁也不肯让谁。\p不过看你们打得那么开心，\n妈妈也就放心了。$"

Part4_MomVisit::
	goto_if_unset FLAG_BADGE04_GET, Part4_Return
	goto_if_set FLAG_BADGE05_GET, Part4_MomAfter
	msgbox Part4_Text_019, MSGBOX_DEFAULT
	return
	Part4_MomAfter::
	msgbox Part4_Text_020, MSGBOX_DEFAULT
	return

Part4_Return::
	return

Part4_Text_021:
	.string "咦，你回来啦！\n已经拿到四枚徽章了？\p这才过了多久啊，也太厉害了吧！$"

PetalburgCity_EventScript_GymBoy_Part4::
	msgbox Part4_Text_021, MSGBOX_DEFAULT
	return

Part4_Text_022:
	.string "千里馆主一直在等你回来。\p去道馆之前，可要做好准备哦。$"

PetalburgCity_EventScript_Gentleman_Part4::
	msgbox Part4_Text_022, MSGBOX_DEFAULT
	return

Part4_Text_023:
	.string "我刚从道馆被打出来……\p千里馆主那只请假王实在太可怕了。\n我现在听见脚步声都会发抖。$"

Part4_Text_024:
	.string "你打赢千里馆主了？\p那我也不能一直坐在这里发呆了。\n我回去再练练！$"

Part4_NormanVisitor::
	lock
	faceplayer
	goto_if_set FLAG_BADGE05_GET, Part4_NormanVisitorLeave
	msgbox Part4_Text_023, MSGBOX_DEFAULT
	release
	end
	Part4_NormanVisitorLeave::
	msgbox Part4_Text_024, MSGBOX_DEFAULT
	setflag FLAG_PART4_DEFEATED_VISITOR_LEFT
	release
	end

Part4_Text_025:
	.string "岸边放着一包保存得很好的食物。$"

Part4_Text_026:
	.string "这里已经什么都没有了。$"

Part4_SurfLeftovers::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_HM_SURF, Part4_QuietEnd
	goto_if_set FLAG_PART4_SURFLEFTOVERS, Part4_SurfLeftovers_After
	msgbox Part4_Text_025, MSGBOX_DEFAULT
	giveitem ITEM_LEFTOVERS, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_SURFLEFTOVERS
	Part4_SurfLeftovers_After::
	msgbox Part4_Text_026, MSGBOX_DEFAULT
	release
	end

Part4_Text_027:
	.string "学会冲浪以后，以前只能在岸边远远\n看着的地方，现在也能去了！$"

Part4_Text_028:
	.string "石缝里卡着一个小小的王冠状东西。$"

Part4_Text_029:
	.string "石缝里已经空了。$"

Part4_Route115KingsRock::
	lock
	faceplayer
	goto_if_set FLAG_PART4_ROUTE115KINGSROCK, Part4_Route115KingsRock_After
	msgbox Part4_Text_028, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_ROUTE115KINGSROCK
	Part4_Route115KingsRock_After::
	msgbox Part4_Text_029, MSGBOX_DEFAULT
	release
	end

Part4_Text_030:
	.string "沙滩上卡着一个旧玻璃瓶。\n瓶里的纸条被海水泡得模糊不清。\p只能认出一句话：\n“愿下一片海也有好天气。”$"

Part4_Text_031:
	.string "瓶子里已经空了。$"

Part4_BottlePearl::
	lock
	faceplayer
	goto_if_set FLAG_PART4_BOTTLEPEARL, Part4_BottlePearl_After
	msgbox Part4_Text_030, MSGBOX_DEFAULT
	giveitem ITEM_PEARL, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_BOTTLEPEARL
	special StoryRefreshPickupMarkers
	Part4_BottlePearl_After::
	msgbox Part4_Text_031, MSGBOX_DEFAULT
	release
	end

Part4_Text_032:
	.string "箱子上的字已经褪色了。\p还能勉强认出几个不同地区的港口名。$"

Part4_ShipCargo::
	msgbox Part4_Text_032, MSGBOX_NPC
	end

Part4_Text_033:
	.string "里面散落着一些旧机器零件。\p从包装来看，是从丰缘以外运来的。$"

Part4_ShipParts::
	msgbox Part4_Text_033, MSGBOX_NPC
	end

Part4_Text_034:
	.string "看样子，这艘船以前跑过很远的航线。$"

Part4_ShipList::
	msgbox Part4_Text_034, MSGBOX_NPC
	end

Part4_Text_035:
	.string "货舱里有一块完全没生锈的金属膜。$"

Part4_Text_036:
	.string "货舱的角落已经空了。$"

Part4_ShipMetalCoat::
	lock
	faceplayer
	goto_if_set FLAG_PART4_SHIPMETALCOAT, Part4_ShipMetalCoat_After
	msgbox Part4_Text_035, MSGBOX_DEFAULT
	giveitem ITEM_METAL_COAT, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_SHIPMETALCOAT
	Part4_ShipMetalCoat_After::
	msgbox Part4_Text_036, MSGBOX_DEFAULT
	release
	end

Part4_Text_037:
	.string "角落里有一瓶还没开封的营养剂。$"

Part4_Text_038:
	.string "这里已经什么都没有了。$"

Part4_ShipDivePPUp::
	lock
	faceplayer
	goto_if_set FLAG_PART4_SHIPDIVEPPUP, Part4_ShipDivePPUp_After
	msgbox Part4_Text_037, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_SHIPDIVEPPUP
	Part4_ShipDivePPUp_After::
	msgbox Part4_Text_038, MSGBOX_DEFAULT
	release
	end

Part4_Text_039:
	.string "把你最信任的伙伴派出来吧。\n让我看看你这一路的成果。$"

Part4_Text_040:
	.string "你真的变强了。\n看来是我多虑了。$"

Part4_Text_041:
	.string "机器停下来以后，这块松动的检修板\n就能打开了。\p要进去看看吗？$"

Part4_Text_042:
	.string "面板在剧烈地振动，现在打不开。$"

Part4_MaintenanceHatch::
	lockall
	goto_if_ne VAR_NEW_MAUVILLE_STATE, 2, Part4_MaintenanceLocked
	msgbox Part4_Text_041, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part4_QuietEnd
	warp MAP_NEW_MAUVILLE_MAINTENANCE, 0
	waitstate
	releaseall
	end
	Part4_MaintenanceLocked::
	msgbox Part4_Text_042, MSGBOX_DEFAULT
	releaseall
	end

Part4_MaintenanceTiles::
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, Part4_MaintenanceOpen
	setmetatile 38, 5, METATILE_BikeShop_Floor_Shadow_Top, TRUE
	return
	Part4_MaintenanceOpen::
	setmetatile 38, 5, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	return

Part4_Text_043:
	.string "这里的旧设备经常要检查。\p不过得等机器停下来才能进去，\n安全第一嘛。$"

Part4_Text_044:
	.string "你碰到阿尔刻的外勤人员了？\p我最近也在帮他们检查这里的旧设备。$"

Part4_PowerTechnician::
	lock
	faceplayer
	goto_if_set FLAG_PART4_ARCHE_KNOWN, Part4_PowerTechnicianKnown
	msgbox Part4_Text_043, MSGBOX_DEFAULT
	release
	end
	Part4_PowerTechnicianKnown::
	msgbox Part4_Text_044, MSGBOX_DEFAULT
	release
	end

Part4_Text_045:
	.string "空气里有一股刺鼻的气味。\n头发好像都要竖起来了。$"

Part4_StaticAir::
	msgbox Part4_Text_045, MSGBOX_NPC
	end

Part4_Text_046:
	.string "电缆上留着焦黑的痕迹。\n附近不时传来低沉的嗡嗡声。$"

Part4_ScorchedCable::
	msgbox Part4_Text_046, MSGBOX_NPC
	end

Part4_Raikou::
	lockall
	playmoncry SPECIES_RAIKOU, CRY_MODE_NORMAL
	waitmoncry
	seteventmon SPECIES_RAIKOU, PART4_RAIKOU_LEVEL
	special BeginPart4RaikouBattle
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	special FinishPart4RaikouBattle
	removeobject LOCALID_PART4_RAIKOU
	call_if_eq VAR_PART4_RAIKOU_STATE, 1, Part4_RaikouFailure
	releaseall
	end

Part4_Text_047:
	.string "墙壁上留着一道很深的电击痕迹。$"

Part4_RaikouTrace::
	lockall
	goto_if_eq VAR_PART4_RAIKOU_STATE, 1, Part4_RaikouTraceWaiting
	msgbox Part4_Text_047, MSGBOX_DEFAULT
	releaseall
	end
Part4_RaikouTraceWaiting::
	call Part4_RaikouFailure
	releaseall
	end
Part4_RaikouFailure::
	msgbox Part4_Text_156, MSGBOX_DEFAULT
	return

Part4_Text_048:
	.string "你说地下那阵电是宝可梦造成的？\n哇哈哈哈！\p难怪那些仪器怎么修都不对劲！$"

Part4_WattsonReaction::
	goto_if_ne VAR_PART4_RAIKOU_STATE, 2, Part4_Return
	msgbox Part4_Text_048, MSGBOX_DEFAULT
	return

Part4_118VOLBEAT::
	lock
	faceplayer
	playmoncry SPECIES_VOLBEAT, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part4_118ILLUMISE::
	lock
	faceplayer
	playmoncry SPECIES_ILLUMISE, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part4_Text_049:
	.string "我装树果的篮子被河水冲走了！\p好像漂到河那边的岸上了。\n你能帮我找回来吗？$"

Part4_Text_050:
	.string "是我的篮子！太谢谢你了。\p送你几颗树果吧。装在口袋里，\n就不怕被水冲走了！$"

Part4_Text_051:
	.string "谢谢你帮我找回篮子！$"

Part4_Text_052:
	.string "找到了一个装树果的篮子。\n先带回去还给失主吧。$"

Part4_BerryBasket::
	lock
	faceplayer
	goto_if_eq VAR_PART4_BERRYBASKET, 2, Part4_BerryBasket_Done
	checkitem ITEM_BERRY_BASKET
	goto_if_eq VAR_RESULT, TRUE, Part4_BerryBasket_Return
	msgbox Part4_Text_049, MSGBOX_DEFAULT
	release
	end
	Part4_BerryBasket_Return::
	msgbox Part4_Text_050, MSGBOX_DEFAULT
	giveitem ITEM_SITRUS_BERRY, 3
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	removeitem ITEM_BERRY_BASKET, 1
	setvar VAR_PART4_BERRYBASKET, 2
	Part4_BerryBasket_Done::
	msgbox Part4_Text_051, MSGBOX_DEFAULT
	release
	end

Part4_BerryBasket_Find::
	lockall
	goto_if_ge VAR_PART4_BERRYBASKET, 1, Part4_QuietEnd
	msgbox Part4_Text_052, MSGBOX_DEFAULT
	giveitem ITEM_BERRY_BASKET, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setvar VAR_PART4_BERRYBASKET, 1
	special StoryRefreshPickupMarkers
	releaseall
	end

Part4_AntiScizor::
	lock
	faceplayer
	playmoncry SPECIES_SCIZOR, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part4_Text_053:
	.string "水舰队队员：站住！我们正在找一批\n从河上运来的货。\p识相的话，就让你的宝可梦退开！$"

Part4_Text_054:
	.string "水舰队队员：一个人还挺能打嘛！\n换我来对付你！$"

Part4_Text_055:
	.string "啧，别得意，这还没完！$"

Part4_Text_056:
	.string "水舰队队员：就是这个训练家！\n大家一起上，把人围起来！$"

Part4_Text_057:
	.string "男子：好了，到此为止吧。\n巨钳螳螂，交给你了。$"

Part4_Text_057b:
	.string "水舰队队员：那、那是什么速度……！\n撤、撤退！先撤！$"

Part4_Text_058:
	.string "男子：刚才那场对战我都看到了。\n你和宝可梦的配合挺有意思的。\p正好我手上有样东西，放我这儿也\n是闲着，给你应该更合适。$"

Part4_Text_059:
	.string "有些宝可梦能在战斗中发生超越普通\n进化的变化，这就是超级进化。\p条件有两个：训练家要戴着这个手环，\n宝可梦要携带对应的超级石。\p当然，光有道具可不够，你和宝可梦\n的默契也很重要。自己去试试吧。\p我还得赶路，有缘再见啦。$"

Part4_MegaScene::
	goto_if_unset FLAG_BADGE05_GET, Part4_SceneEnd
	goto_if_unset FLAG_RECEIVED_HM_SURF, Part4_SceneEnd
	goto_if_ge VAR_PART4_MEGA_STAGE, 4, Part4_SceneEnd
	lockall
	goto_if_ge VAR_PART4_MEGA_STAGE, 3, Part4_MegaGift
	goto_if_ge VAR_PART4_MEGA_STAGE, 2, Part4_MegaRescue
	goto_if_defeated TRAINER_PART4_AQUA_A, Part4_MegaBattleB
	@ Two Aqua grunts searching the beach spot the player and come over.
	playse SE_PIN
	applymovement LOCALID_PART4_AQUAA, Common_Movement_ExclamationMark
	applymovement LOCALID_PART4_AQUAB, Common_Movement_ExclamationMark
	waitmovement 0
	setvar VAR_0x8000, LOCALID_PART4_AQUAA
	setvar VAR_0x8001, 1
	call Story_WalkToPlayer
	msgbox Part4_Text_053, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART4_AQUA_A, Part4_Text_055
	Part4_MegaBattleB::
	setvar VAR_PART4_MEGA_STAGE, 1
	setvar VAR_0x8000, LOCALID_PART4_AQUAA
	setvar VAR_0x8001, 2
	call Story_WalkAwayFromPlayerKeep
	goto_if_defeated TRAINER_PART4_AQUA_B, Part4_MegaMore
	setvar VAR_0x8000, LOCALID_PART4_AQUAB
	setvar VAR_0x8001, 1
	call Story_WalkToPlayer
	msgbox Part4_Text_054, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART4_AQUA_B, Part4_Text_055
	Part4_MegaMore::
	setvar VAR_PART4_MEGA_STAGE, 2
	special SyncPart4MegaObjects
	msgbox Part4_Text_056, MSGBOX_DEFAULT
	closemessage
	@ Reinforcements run in from both sides and surround the player.
	setvar VAR_0x8000, LOCALID_PART4_AQUAEXTRA0
	setvar VAR_0x8001, 6
	setvar VAR_0x8002, 0xFFFF
	call Story_SpawnNearPlayer
	setvar VAR_0x8000, LOCALID_PART4_AQUAEXTRA1
	setvar VAR_0x8001, 6
	setvar VAR_0x8002, 2
	call Story_SpawnNearPlayer
	setvar VAR_0x8000, LOCALID_PART4_AQUAEXTRA2
	setvar VAR_0x8001, 2
	setvar VAR_0x8002, 5
	call Story_SpawnNearPlayer
	setvar VAR_0x8000, LOCALID_PART4_AQUAEXTRA0
	setvar VAR_0x8001, 2
	call Story_WalkToPlayer
	setvar VAR_0x8000, LOCALID_PART4_AQUAEXTRA1
	setvar VAR_0x8001, 2
	call Story_WalkToPlayer
	setvar VAR_0x8000, LOCALID_PART4_AQUAEXTRA2
	setvar VAR_0x8001, 2
	call Story_WalkToPlayer
	Part4_MegaRescue::
	@ A man with a Scizor walks in and breaks it up.
	setvar VAR_0x8000, LOCALID_PART4_ANTI
	setvar VAR_0x8001, 6
	setvar VAR_0x8002, 0xFFFE
	call Story_SpawnNearPlayer
	setvar VAR_0x8000, LOCALID_PART4_ANTISCIZOR
	setvar VAR_0x8001, 7
	setvar VAR_0x8002, 0xFFFE
	call Story_SpawnNearPlayer
	setvar VAR_0x8000, LOCALID_PART4_ANTI
	setvar VAR_0x8001, 3
	call Story_WalkToPlayer
	msgbox Part4_Text_057, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8000, LOCALID_PART4_ANTISCIZOR
	setvar VAR_0x8001, 2
	call Story_WalkToPlayer
	playmoncry SPECIES_SCIZOR, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_PART4_ANTISCIZOR, Part4_ScizorFlash
	waitmovement 0
	msgbox Part4_Text_057b, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8001, 8
	setvar VAR_0x8000, LOCALID_PART4_AQUAEXTRA0
	call Story_WalkAwayAndRemove
	setvar VAR_0x8001, 8
	setvar VAR_0x8000, LOCALID_PART4_AQUAEXTRA1
	call Story_WalkAwayAndRemove
	setvar VAR_0x8001, 8
	setvar VAR_0x8000, LOCALID_PART4_AQUAEXTRA2
	call Story_WalkAwayAndRemove
	setvar VAR_0x8001, 8
	setvar VAR_0x8000, LOCALID_PART4_AQUAB
	call Story_WalkAwayAndRemove
	setvar VAR_0x8001, 8
	setvar VAR_0x8000, LOCALID_PART4_AQUAA
	call Story_WalkAwayAndRemove
	setvar VAR_PART4_MEGA_STAGE, 3
	special SyncPart4MegaObjects
	Part4_MegaGift::
	setvar VAR_0x8000, LOCALID_PART4_ANTI
	setvar VAR_0x8001, 1
	call Story_WalkToPlayer
	msgbox Part4_Text_058, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_MEGA_RING_RECEIVED
	setvar VAR_PART4_MEGA_STAGE, 4
	msgbox Part4_Text_059, MSGBOX_DEFAULT
	closemessage
	special SyncPart4MegaObjects
	@ He leaves the way he came, Scizor following.
	setvar VAR_0x8001, 9
	setvar VAR_0x8000, LOCALID_PART4_ANTI
	call Story_WalkAwayAndRemove
	setvar VAR_0x8001, 9
	setvar VAR_0x8000, LOCALID_PART4_ANTISCIZOR
	call Story_WalkAwayAndRemove
	releaseall
	end
	Part4_SceneEnd::
	end

Part4_Text_060:
	.string "这里有一块带着闪电纹路的石头。$"

Part4_Text_061:
	.string "岩石上还残留着细小的电击痕迹。$"

Part4_Manectite::
	lock
	faceplayer
	goto_if_set FLAG_PART4_MANECTITE, Part4_Manectite_After
	msgbox Part4_Text_060, MSGBOX_DEFAULT
	giveitem ITEM_MANECTITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_MANECTITE
	Part4_Manectite_After::
	msgbox Part4_Text_061, MSGBOX_DEFAULT
	release
	end

Part4_Text_062:
	.string "淋成这样了？快过来歇一会儿吧。\p等伙伴们缓过来再出发也不迟。$"

Part4_RainCamp::
	lock
	faceplayer
	msgbox Part4_Text_062, MSGBOX_DEFAULT
	special HealPlayerParty
	playfanfare MUS_HEAL
	waitfanfare
	release
	end

Part4_Text_063:
	.string "水边的泥里露出一颗很大的珍珠。$"

Part4_Text_064:
	.string "泥里已经什么都没有了。$"

Part4_119BigPearl::
	lock
	faceplayer
	goto_if_set FLAG_PART4_119BIGPEARL, Part4_119BigPearl_After
	msgbox Part4_Text_063, MSGBOX_DEFAULT
	giveitem ITEM_BIG_PEARL, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_119BIGPEARL
	Part4_119BigPearl_After::
	msgbox Part4_Text_064, MSGBOX_DEFAULT
	release
	end

Part4_Text_065:
	.string "下雨天也没法把它们叫回来！\p你看，我的虫宝可梦自己都想对战呢！$"

Part4_Text_066:
	.string "唔，雨声太大，把我的指令盖住了吗？$"

Part4_Text_067:
	.string "下雨天，宝可梦的状态也会跟着变。\n下次我得多留心才行。$"

Part4_RainBug::
	lock
	faceplayer
	trainerbattle_single TRAINER_PART4_BUG, Part4_Text_065, Part4_Text_066
	msgbox Part4_Text_067, MSGBOX_DEFAULT
	release
	end

Part4_ChildLotad::
	lock
	faceplayer
	playmoncry SPECIES_LOTAD, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part4_ChildPositions::
	goto_if_eq VAR_PART4_CHILD_STAGE, 0, Part4_Return
	setobjectxyperm LOCALID_PART4_LOST_CHILD, 11, 89
	setobjectxyperm LOCALID_PART4_CHILD_LOTAD, 9, 88
	return

Part4_Text_068:
	.string "我和莲叶童子一起来看河水，\n一回头就找不到妈妈了……\p妈妈在南边的营地。\n你能带我们回去吗？$"

Part4_Text_069:
	.string "你把小孩和莲叶童子送回了营地。$"

Part4_Text_070:
	.string "下次出门前，我一定先跟妈妈说一声！$"

Part4_LostChild::
	lockall
	goto_if_ge VAR_PART4_CHILD_STAGE, 1, Part4_ChildHome
	msgbox Part4_Text_068, MSGBOX_DEFAULT
	setvar VAR_PART4_CHILD_STAGE, 1
	fadescreen FADE_TO_BLACK
	setobjectxy LOCALID_PART4_LOST_CHILD, 11, 89
	setobjectxy LOCALID_PART4_CHILD_LOTAD, 9, 88
	call Part4_ChildPositions
	fadescreen FADE_FROM_BLACK
	msgbox Part4_Text_069, MSGBOX_DEFAULT
	releaseall
	end
	Part4_ChildHome::
	msgbox Part4_Text_070, MSGBOX_DEFAULT
	releaseall
	end

Part4_Text_071:
	.string "是你把孩子送回来的？太感谢了！\p孩子自己一点都不怕，倒是我快急坏\n了。这几瓶哞哞鲜奶请收下吧。$"

Part4_Text_072:
	.string "你走路也要注意脚下哦，\n别光顾着看宝可梦啦。$"

Part4_Text_073:
	.string "我家孩子带着莲叶童子往北走了，\n到现在还没回来。\p要是你在北边看到那孩子，\n能帮我把孩子带回营地吗？$"

Part4_ChildParent::
	lock
	faceplayer
	goto_if_eq VAR_PART4_CHILD_STAGE, 0, Part4_ChildMissing
	goto_if_eq VAR_PART4_CHILD_STAGE, 2, Part4_ChildThanks
	msgbox Part4_Text_071, MSGBOX_DEFAULT
	giveitem ITEM_MOOMOO_MILK, 3
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setvar VAR_PART4_CHILD_STAGE, 2
	Part4_ChildThanks::
	msgbox Part4_Text_072, MSGBOX_DEFAULT
	release
	end
	Part4_ChildMissing::
	msgbox Part4_Text_073, MSGBOX_DEFAULT
	release
	end

Part4_Text_074:
	.string "屏幕上正在记录降雨量。\n图表边上留着手写的校正记号。$"

Part4_Instrument1F0::
	msgbox Part4_Text_074, MSGBOX_NPC
	end

Part4_Text_075:
	.string "屏幕上的降雨量曲线还在更新。\n边上有人用笔做了校正记号。$"

Part4_Instrument2F0::
	msgbox Part4_Text_075, MSGBOX_NPC
	end

Part4_Text_076:
	.string "一份海洋温度记录。\n不同日期的数据被整理得井井有条。$"

Part4_Instrument2F1::
	msgbox Part4_Text_076, MSGBOX_NPC
	end

Part4_Text_077:
	.string "观测日志上写着：\n“连续降雨，河流水位需要复核。”$"

Part4_Instrument2F2::
	msgbox Part4_Text_077, MSGBOX_NPC
	end

Part4_Text_078:
	.string "观测桩运转正常，刻度读数很稳定。$"

Part4_Observation0::
	lockall
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Part4_QuietEnd
	msgbox Part4_Text_078, MSGBOX_DEFAULT
	setflag FLAG_PART4_OBSERVATION_0
	releaseall
	end

Part4_Text_079:
	.string "雨水把观测桩的外壳冲得干干净净。\n读数没有问题。$"

Part4_Observation1::
	lockall
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Part4_QuietEnd
	msgbox Part4_Text_079, MSGBOX_DEFAULT
	setflag FLAG_PART4_OBSERVATION_1
	releaseall
	end

Part4_Text_080:
	.string "这根观测桩的线路有点松了。\n你把它重新接好了。$"

Part4_Observation2::
	lockall
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Part4_QuietEnd
	msgbox Part4_Text_080, MSGBOX_DEFAULT
	setflag FLAG_PART4_OBSERVATION_2
	releaseall
	end

Part4_Text_081:
	.string "三根观测桩你都确认过了？\n真是帮了大忙！\p这瓶营养剂是谢礼，请收下吧。$"

Part4_Text_082:
	.string "这场雨还要下上一阵子。\n过河的时候要多留心哦。$"

Part4_Text_083:
	.string "观测桩一共有三根，都在研究所南边\n的河岸上。\p能帮我去查看一下那三处的刻度吗？\n不着急，有空的时候再去就好。$"

Part4_Observations::
	lock
	faceplayer
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Part4_QuietEnd
	goto_if_set FLAG_PART4_OBSERVATION_REWARD, Part4_ObservationDone
	goto_if_unset FLAG_PART4_OBSERVATION_0, Part4_ObservationOffer
	goto_if_unset FLAG_PART4_OBSERVATION_1, Part4_ObservationOffer
	goto_if_unset FLAG_PART4_OBSERVATION_2, Part4_ObservationOffer
	msgbox Part4_Text_081, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_OBSERVATION_REWARD
	Part4_ObservationDone::
	msgbox Part4_Text_082, MSGBOX_DEFAULT
	release
	end
	Part4_ObservationOffer::
	msgbox Part4_Text_083, MSGBOX_DEFAULT
	release
	end

Part4_Text_084:
	.string "它在外面变过样子吗？\p如果变过，记得告诉我们那天的天气！$"

Part4_CastformComment::
	special CheckPart4LeadCastform
	goto_if_eq VAR_RESULT, FALSE, Part4_Return
	msgbox Part4_Text_084, MSGBOX_DEFAULT
	return

Part4_Text_085:
	.string "雨声这么大，下指令可得喊清楚。\n来试试吧！$"

Part4_Text_086:
	.string "记下了。双打里的配合，比我们想的\n还要重要。$"

Part4_Text_087:
	.string "我们正在这里做野外观测。\p要不要来一场双打？\n不方便的话也没关系。$"

Part4_Text_088:
	.string "我们是阿尔刻的外勤人员，经常在这\n条路上观测连续降雨。\p那位技术员负责照看仪器，我们两个\n负责调查和安全。\p有兴趣的话，下次再慢慢聊吧。$"

Part4_Text_089:
	.string "双打需要两只还能战斗的宝可梦。\n准备好了再来找我们吧。$"

Part4_Text_090:
	.string "好，赶路要紧。祝你一路顺风！$"

Part4_Text_091:
	.string "研究所那边好像出事了。\n我们得先守着这几台仪器。$"

Part4_ArcheSurvey::
	lock
	faceplayer
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Part4_ArcheBusy
	goto_if_defeated TRAINER_PART4_ARCHE_PAIR, Part4_ArcheReveal
	msgbox Part4_Text_087, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part4_ArcheDecline
	trainerbattle_double TRAINER_PART4_ARCHE_PAIR, Part4_Text_085, Part4_Text_086, Part4_Text_089, Part4_ArcheReveal
	Part4_ArcheReveal::
	setflag FLAG_PART4_ARCHE_KNOWN
	msgbox Part4_Text_088, MSGBOX_DEFAULT
	release
	end
	Part4_ArcheDecline::
	msgbox Part4_Text_090, MSGBOX_DEFAULT
	release
	end
	Part4_ArcheBusy::
	msgbox Part4_Text_091, MSGBOX_DEFAULT
	release
	end

Part4_Text_092:
	.string "仪器的接口进水了。\n先别碰，等我把它擦干。$"

Part4_ArcheTech::
	msgbox Part4_Text_092, MSGBOX_NPC
	end

Part4_Text_093:
	.string "我是走阿尔刻的物流渠道进的货。\p时间球和树果管够，石头可就少了：\n普通进化石每种两块，进化石一块。$"

Part4_Text_094:
	.string "有需要再来吧。\n这几天我都会在附近歇脚。$"

Part4_Text_095:
	.string "路上太潮湿，货还没拆开呢。\n你先往前走吧。$"

Part4_ImportMerchant::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_HM_FLY, Part4_ImportClosed
	msgbox Part4_Text_093, MSGBOX_DEFAULT
	setflag FLAG_PART4_ARCHE_KNOWN
	pokemart Part4_ImportStock
	msgbox Part4_Text_094, MSGBOX_DEFAULT
	release
	end
	Part4_ImportClosed::
	msgbox Part4_Text_095, MSGBOX_DEFAULT
	release
	end

Part4_Text_096:
	.string "河水的水位比记录高了一点。\n这里的天气变得真快啊。$"

Part4_119Observer::
	lock
	faceplayer
	msgbox Part4_Text_096, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART4_ARCHE_KNOWN, Part4_QuietEnd
	msgbox Part4_Text_155, MSGBOX_DEFAULT
	release
	end

Part4_Text_097:
	.string "我的风筝被风吹走，掉到树桥底下了！\p就是商店东边那座长树桥的桥头下面。\n你能帮我捡回来吗？$"

Part4_Text_098:
	.string "就是这个！谢谢你！\p这是我捡到的尖锐鸟嘴，送给你吧。\n我要去找青绵鸟玩啦！$"

Part4_Text_099:
	.string "谢谢你帮我捡回风筝！$"

Part4_Text_100:
	.string "找到了一只风筝。\n先带回去还给它的主人吧。$"

Part4_Kite::
	lock
	faceplayer
	goto_if_eq VAR_PART4_KITE, 2, Part4_Kite_Done
	checkitem ITEM_LOST_KITE
	goto_if_eq VAR_RESULT, TRUE, Part4_Kite_Return
	msgbox Part4_Text_097, MSGBOX_DEFAULT
	release
	end
	Part4_Kite_Return::
	msgbox Part4_Text_098, MSGBOX_DEFAULT
	giveitem ITEM_SHARP_BEAK, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	removeitem ITEM_LOST_KITE, 1
	setvar VAR_PART4_KITE, 2
	Part4_Kite_Done::
	msgbox Part4_Text_099, MSGBOX_DEFAULT
	release
	end

Part4_Kite_Find::
	lockall
	goto_if_ge VAR_PART4_KITE, 1, Part4_QuietEnd
	msgbox Part4_Text_100, MSGBOX_DEFAULT
	giveitem ITEM_LOST_KITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setvar VAR_PART4_KITE, 1
	special StoryRefreshPickupMarkers
	releaseall
	end

Part4_PostPelipper::
	lock
	faceplayer
	playmoncry SPECIES_PELIPPER, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part4_Text_101:
	.string "这里有些信件，靠飞行宝可梦送更快。\p刚才一个包裹从树桥上掉下来了，\n就落在商店东边的草地上。\p能帮我捡回来吗？别拆开呀。$"

Part4_Text_102:
	.string "完好无损！\n今天总算不用赔钱了！\p这几个高级球是谢礼，拿去吧。$"

Part4_Text_103:
	.string "谢谢你帮我找回包裹！$"

Part4_Text_104:
	.string "找到了一个包裹。\n先带回去交给失主吧。$"

Part4_Parcel::
	lock
	faceplayer
	goto_if_eq VAR_PART4_PARCEL, 2, Part4_Parcel_Done
	checkitem ITEM_POSTAL_PARCEL
	goto_if_eq VAR_RESULT, TRUE, Part4_Parcel_Return
	msgbox Part4_Text_101, MSGBOX_DEFAULT
	release
	end
	Part4_Parcel_Return::
	msgbox Part4_Text_102, MSGBOX_DEFAULT
	giveitem ITEM_ULTRA_BALL, 3
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	removeitem ITEM_POSTAL_PARCEL, 1
	setvar VAR_PART4_PARCEL, 2
	Part4_Parcel_Done::
	msgbox Part4_Text_103, MSGBOX_DEFAULT
	release
	end

Part4_Parcel_Find::
	lockall
	goto_if_ge VAR_PART4_PARCEL, 1, Part4_QuietEnd
	msgbox Part4_Text_104, MSGBOX_DEFAULT
	giveitem ITEM_POSTAL_PARCEL, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setvar VAR_PART4_PARCEL, 1
	special StoryRefreshPickupMarkers
	releaseall
	end

Part4_Text_105:
	.string "这儿的木板经常要换。\p长鼻叶挑木料的眼光比我还准，\n不过钉钉子还得靠我！$"

Part4_Carpenter::
	msgbox Part4_Text_105, MSGBOX_NPC
	end

Part4_CarpenterNuzleaf::
	lock
	faceplayer
	playmoncry SPECIES_NUZLEAF, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part4_KiteSwablu::
	lock
	faceplayer
	playmoncry SPECIES_SWABLU, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part4_Text_106:
	.string "你赢了娜琪？\p我在这儿住了这么久，\n还从来没跟上过她的飞行宝可梦。$"

Part4_FortreeBadgeComment::
	goto_if_unset FLAG_BADGE06_GET, Part4_Return
	msgbox Part4_Text_106, MSGBOX_DEFAULT
	return

Part4_Text_107:
	.string "这件小摆设是外地朋友寄来的。\n放在木头房间里正合适。$"

Part4_Text_108:
	.string "一件小巧的外地工艺品。\n边角被擦得干干净净。$"

Part4_ForeignDecor::
	msgbox Part4_Text_108, MSGBOX_NPC
	end

Part4_Text_109:
	.string "有人在树边刻了个小小的箭头，\n旁边写着：“我的秘密基地”。$"

Part4_BaseNote::
	msgbox Part4_Text_109, MSGBOX_NPC
	end

Part4_Text_110:
	.string "大吾：那个手环……你已经拿到它了？\p看来这一路上，你遇到了很多人，\n也经历了不少事。$"

Part4_StevenRing::
	checkitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, FALSE, Part4_Return
	msgbox Part4_Text_110, MSGBOX_DEFAULT
	return

Part4_Kecleon0::
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, FALSE, Part4_KecleonNoScope
	msgbox Kecleon_Text_WantToUseDevonScope, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part4_QuietEnd
	applymovement LOCALID_PART4_KECLEON_0, Movement_KecleonAppears
	waitmovement 0
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_KECLEON, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, Part4_QuietEnd
	setflag FLAG_PART4_KECLEON_0
	removeobject LOCALID_PART4_KECLEON_0
	release
	end

Part4_Kecleon1::
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, FALSE, Part4_KecleonNoScope
	msgbox Kecleon_Text_WantToUseDevonScope, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part4_QuietEnd
	applymovement LOCALID_PART4_KECLEON_1, Movement_KecleonAppears
	waitmovement 0
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_KECLEON, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, Part4_QuietEnd
	setflag FLAG_PART4_KECLEON_1
	removeobject LOCALID_PART4_KECLEON_1
	release
	end

Part4_KecleonNoScope::
	msgbox Kecleon_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

Part4_Text_111:
	.string "树根之间闪着一点光。\n是一块带着复杂纹路的石头。$"

Part4_Text_112:
	.string "树根之间只剩下潮湿的泥土。$"

Part4_Mawilite::
	lock
	faceplayer
	goto_if_unset FLAG_PART4_KECLEON_0, Part4_QuietEnd
	goto_if_set FLAG_PART4_MAWILITE, Part4_Mawilite_After
	msgbox Part4_Text_111, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_STONE, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_MAWILITE
	special StoryRefreshPickupMarkers
	Part4_Mawilite_After::
	msgbox Part4_Text_112, MSGBOX_DEFAULT
	release
	end

Part4_Text_113:
	.string "前面正在测量，设备还没收好。\n请先别进去。$"

Part4_Text_114:
	.string "你一定要过去？\p那就先和我打一场吧。\n或者等我们把设备收好也行。$"

Part4_Text_115:
	.string "让你的伙伴也留心脚下的线路！$"

Part4_Text_116:
	.string "行，你比我想的稳多了。$"

Part4_Text_117:
	.string "过去吧，小心别踩到线路。\n我把这边的设备挪开。$"

Part4_ArcheGuard::
	lock
	faceplayer
	goto_if_ge VAR_PART4_GUARD_VISITS, 1, Part4_GuardAsk
	setvar VAR_PART4_GUARD_VISITS, 1
	msgbox Part4_Text_113, MSGBOX_DEFAULT
	release
	end
	Part4_GuardAsk::
	msgbox Part4_Text_114, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part4_QuietEnd
	trainerbattle_single TRAINER_PART4_ARCHE_GUARD, Part4_Text_115, Part4_Text_116, Part4_GuardPassed
	Part4_GuardPassed::
	msgbox Part4_Text_117, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_PART4_GUARD_PASSED
	setvar VAR_0x8000, LOCALID_PART4_ARCHEGUARD
	setvar VAR_0x8001, 6
	call Story_WalkAwayAndRemove
	release
	end

Part4_Text_118:
	.string "石碑上的字已经模糊了，\n只能辨认出很浅的刻痕。$"

Part4_Text_119:
	.string "雨水顺着凹槽流下来。\p那些线条，好像描绘着风、云和山。$"

Part4_OldTablet::
	lockall
	special GetPart4RainState
	goto_if_eq VAR_RESULT, TRUE, Part4_OldTabletRain
	msgbox Part4_Text_118, MSGBOX_DEFAULT
	releaseall
	end
	Part4_OldTabletRain::
	msgbox Part4_Text_119, MSGBOX_DEFAULT
	releaseall
	end

Part4_Text_120:
	.string "急着赶路吗？\n不急的话，和我们认真比一场吧！$"

Part4_Text_121:
	.string "呼……这一场打得真过瘾！$"

Part4_Text_122:
	.string "我就在这里练习。\n你要往前走的话，从旁边绕过去就行。$"

Part4_ForestAce::
	lock
	faceplayer
	trainerbattle_single TRAINER_PART4_ACE, Part4_Text_120, Part4_Text_121
	msgbox Part4_Text_122, MSGBOX_DEFAULT
	release
	end

Part4_Text_123:
	.string "我本来想钓爱心鱼，结果上钩的全是\n这些大家伙！来，你也见识一下！$"

Part4_Text_124:
	.string "唉，钓鱼不顺，对战也不顺！$"

Part4_Text_125:
	.string "阿尔刻那些人在湖边摆满了仪器，\n好钓位全被他们占了。\p女儿快过生日了，想要一只爱心鱼，\n可我到现在一条都没钓到。\p她住在水静市。你要是有爱心鱼，\n能不能帮我送她一只？$"

Part4_Text_126:
	.string "女儿收到爱心鱼了？\n真是帮了我大忙！\p这块石头是我以前钓上来的，\n你拿着吧。$"

Part4_Text_127:
	.string "今年的生日，\n总算能让她开开心心地过了。$"

Part4_LakeFisher::
	lock
	faceplayer
	goto_if_ge VAR_PART4_LUVDISC_STATE, 2, Part4_FisherReward
	trainerbattle_single TRAINER_PART4_FISHER, Part4_Text_123, Part4_Text_124
	msgbox Part4_Text_125, MSGBOX_DEFAULT
	release
	end
	Part4_FisherReward::
	goto_if_set FLAG_PART4_GYARADOSITE, Part4_FisherThanks
	msgbox Part4_Text_126, MSGBOX_DEFAULT
	giveitem ITEM_WATER_STONE
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_GYARADOSITE
	setvar VAR_PART4_LUVDISC_STATE, 3
	Part4_FisherThanks::
	goto_if_set FLAG_SYS_GAME_CLEAR, Part7_FisherRematch
	msgbox Part4_Text_127, MSGBOX_DEFAULT
	release
	end

Part4_Text_128:
	.string "这块石头是我在附近捡到的。\n岩石上原本没有这种花纹。\p比起研究它，我更想找到遗迹的入口。\p这块石头就给你吧。$"

Part4_Text_129:
	.string "总有一天，我一定会找到入口的。$"

Part4_RuinsAggronite::
	lock
	faceplayer
	goto_if_set FLAG_PART4_RUINSAGGRONITE, Part4_RuinsAggronite_After
	msgbox Part4_Text_128, MSGBOX_DEFAULT
	giveitem ITEM_AGGRONITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_RUINSAGGRONITE
	Part4_RuinsAggronite_After::
	msgbox Part4_Text_129, MSGBOX_DEFAULT
	release
	end

Part4_Text_130:
	.string "石像身后的岩壁上刻着古老的封印。\n轻轻一碰，封印没有任何反应。\p看来要等你成为丰缘的冠军，\n再得到某个人的许可，它才会打开。$"

Part4_Seal::
	lockall
	goto_if_unset FLAG_SYS_GAME_CLEAR, Part4_SealClosed
	goto_if_unset FLAG_PART4_SEAL_AUTHORIZED, Part4_SealClosed
	warp MAP_SCORCHED_SLAB_SEALED_ROOM, 0
	waitstate
	releaseall
	end
	Part4_SealClosed::
	msgbox Part4_Text_130, MSGBOX_DEFAULT
	releaseall
	end

Part4_SealStatue::
	goto Part4_Seal

Part4_SealLoad::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Part4_SealBlock
	goto_if_unset FLAG_PART4_SEAL_AUTHORIZED, Part4_SealBlock
	setmetatile 7, 3, 0x201, FALSE
	end
	Part4_SealBlock::
	setmetatile 7, 3, 0x201, TRUE
	end

Part4_Text_131:
	.string "封印深处还留着一小块奇怪的材料。$"

Part4_Text_132:
	.string "封印里面已经空了。$"

Part4_UnknownResearchData::
	lock
	faceplayer
	goto_if_unset FLAG_PART4_SEAL_AUTHORIZED, Part4_QuietEnd
	goto_if_set FLAG_PART4_UNKNOWN_RESEARCH_DATA_RECEIVED, Part4_UnknownResearchData_After
	msgbox Part4_Text_131, MSGBOX_DEFAULT
	giveitem ITEM_UNKNOWN_RESEARCH_DATA, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_UNKNOWN_RESEARCH_DATA_RECEIVED
	Part4_UnknownResearchData_After::
	msgbox Part4_Text_132, MSGBOX_DEFAULT
	release
	end

Part4_GirlLuvdisc::
	lock
	faceplayer
	playmoncry SPECIES_LUVDISC, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part4_Text_133:
	.string "我的生日快到了。\p爸爸去120号道路钓爱心鱼，好几天\n都没钓到。\p你愿意送我一只爱心鱼吗？$"

Part4_Text_134:
	.string "你的队伍里还没有爱心鱼呢。\n没关系，我可以再等等。$"

Part4_Text_135:
	.string "等等，你旅行还得靠能战斗的伙伴，\n先别把它送给我啦。$"

Part4_Text_136:
	.string "它身上还带着道具呢。\n先把道具取下来再给我吧。$"

Part4_Text_137:
	.string "谢谢你！我会好好照顾它的！\p也去告诉爸爸一声吧，\n他还在120号道路的湖边钓鱼呢。$"

Part4_Text_138:
	.string "它好可爱！\n这是我收到过最棒的生日礼物！$"

Part4_BirthdayGirl::
	lock
	faceplayer
	goto_if_ge VAR_PART4_LUVDISC_STATE, 2, Part4_GirlThanks
	setvar VAR_PART4_LUVDISC_STATE, 1
	msgbox Part4_Text_133, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part4_QuietEnd
	special GivePart4LuvdiscToGirl
	goto_if_eq VAR_RESULT, 1, Part4_GirlSuccess
	goto_if_eq VAR_RESULT, 2, Part4_GirlLastAble
	goto_if_eq VAR_RESULT, 3, Part4_GirlHeldItem
	msgbox Part4_Text_134, MSGBOX_DEFAULT
	release
	end
	Part4_GirlLastAble::
	msgbox Part4_Text_135, MSGBOX_DEFAULT
	release
	end
	Part4_GirlHeldItem::
	msgbox Part4_Text_136, MSGBOX_DEFAULT
	release
	end
	Part4_GirlSuccess::
	addobject LOCALID_PART4_GIRL_LUVDISC
	msgbox Part4_Text_137, MSGBOX_DEFAULT
	Part4_GirlThanks::
	msgbox Part4_Text_138, MSGBOX_DEFAULT
	release
	end

Part4_Text_139:
	.string "这孩子，交给你了。$"

Part4_Text_140:
	.string "得到了古空棘鱼！$"

Part4_Text_141:
	.string "以后，你会需要它的。$"

Part4_Text_142:
	.string "队伍满了。空出一个位置再来。$"

Part4_Text_143:
	.string "……$"

Part4_QuietVisitor::
	lock
	faceplayer
	goto_if_set FLAG_PART4_RELICANTH_RECEIVED, Part4_VisitorSilent
	msgbox Part4_Text_139, MSGBOX_DEFAULT
	special GivePart4Relicanth
	goto_if_eq VAR_RESULT, FALSE, Part4_VisitorPartyFull
	playfanfare MUS_OBTAIN_ITEM
	msgbox Part4_Text_140, MSGBOX_DEFAULT
	waitfanfare
	msgbox Part4_Text_141, MSGBOX_DEFAULT
	release
	end
	Part4_VisitorPartyFull::
	msgbox Part4_Text_142, MSGBOX_DEFAULT
	release
	end
	Part4_VisitorSilent::
	msgbox Part4_Text_143, MSGBOX_DEFAULT
	release
	end

Part4_Text_144:
	.string "那个人前几天就来了，一直不太说话。\n大概是喜欢清静吧。$"

Part4_Text_145:
	.string "树屋之间的风，可没看起来那么简单！\n让我的宝可梦带你体验一下！$"

Part4_Text_146:
	.string "被你找准风向了！$"

Part4_Text_147:
	.string "娜琪能看见更高处的风。\n我还差得远呢。$"

Part4_TreeBird::
	lock
	faceplayer
	trainerbattle_single TRAINER_PART4_BIRD, Part4_Text_145, Part4_Text_146
	msgbox Part4_Text_147, MSGBOX_DEFAULT
	release
	end

Part4_Text_148:
	.string "我和伙伴们飞遍了丰缘的天空。\p现在，让我看看你们如何迎风前进！$"

Part4_Text_149:
	.string "娜琪：你已经有那种手环了啊。\p力量变了，配合方式也要跟着变。\n记住刚才战斗中的那种感觉吧。$"

Part4_WinonaRing::
	checkitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, FALSE, Part4_Return
	msgbox Part4_Text_149, MSGBOX_DEFAULT
	return

Part4_Text_155:
	.string "南边那些人提起过你。\n看来你很喜欢到处跑嘛。$"

Part4_Text_156:
	.string "雷公化作一道电光，\n消失在通道深处。\p空气中仍残留着细微的电流。\p等你登上丰缘训练家的顶点之后，\n它或许还会再次回应你。$"

Part4_Text_157:
	.string "终于追上你了！这条路也太长了，\n而且一路都在下雨！\p正好，来打一场活动活动筋骨吧！$"
