@ PART 4 shared events. Terminal builds only.

Part4_Text_001:
	.string "背包已经装满了。整理一下再来吧。$"

Part4_BagFull::
	msgbox Part4_Text_001, MSGBOX_DEFAULT
	releaseall
	end

Part4_QuietEnd::
	releaseall
	end

Part4_Text_002:
	.string "这里地方不大，来往的船倒是不少。\p有时外地的新鲜玩意儿，比本岛还先\n送到这里。$"

Part4_Text_003:
	.string "釜炎仙贝在外地也卖得不错。就是海\n运久了容易碎。$"

Part4_Text_004:
	.string "有些设备是丰缘造的，零件则要从外\n地订。装起来能正常运转就行。$"

Part4_Text_005:
	.string "流星瀑布的样本很特别。我们也会寄\n给外地同行一起分析。$"

Part4_Text_006:
	.string "朋友推荐我来丰缘旅行。这儿的温泉\n比传闻还舒服。$"

Part4_Text_007:
	.string "海洋观测资料会定期与其他地区的研\n究机构交换。$"

Part4_Text_008:
	.string "偶尔还有外地客人，专程来订我们的\n自行车。$"

Part4_Text_009:
	.string "系统常收到其他地区开发者的反馈。\n大家使用盒子的习惯还真不一样。$"

Part4_Text_010:
	.string "别看这里全是沙。找到水以后，总会\n有东西活下来。$"

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
	.string "我刚才差点一脚踩进它挖的坑里。$"

Part4_PitCamper::
	msgbox Part4_Text_011, MSGBOX_NPC
	end

Part4_Text_012:
	.string "水壶在沙暴里弄丢了。你要是找到了\n，帮我带回来吧。$"

Part4_Text_013:
	.string "太好了！我刚才已经开始考虑，靠仙\n人掌撑到晚上了。$"

Part4_Text_014:
	.string "谢谢你的帮忙。$"

Part4_Text_015:
	.string "找到了。先带回去吧。$"

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
	releaseall
	end

Part4_Text_016:
	.string "沙子下面露出一块形状奇特的石头。\n摸起来还有一点温度。$"

Part4_Text_017:
	.string "只剩下一点碎石。$"

Part4_FirstEvolutionStone::
	lock
	faceplayer
	goto_if_set FLAG_PART4_FIRSTEVOLUTIONSTONE, Part4_FirstEvolutionStone_After
	msgbox Part4_Text_016, MSGBOX_DEFAULT
	giveitem ITEM_EVOLUTION_STONE, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_FIRSTEVOLUTIONSTONE
	Part4_FirstEvolutionStone_After::
	msgbox Part4_Text_017, MSGBOX_DEFAULT
	release
	end

Part4_Text_018:
	.string "墙壁被风沙侵蚀得很严重。细沙不断\n从石缝里落下来。$"

Part4_MirageWall::
	msgbox Part4_Text_018, MSGBOX_NPC
	end

Part4_Text_019:
	.string "终于要挑战爸爸了吗？他嘴上不怎么\n说，心里一直等着这一天吧。别紧张\p。$"

Part4_Text_020:
	.string "你们两个真是的，对战时谁都不肯让\n一步。$"

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
	.string "咦，你回来了！已经有四枚徽章了？\n这才过了多久啊！$"

PetalburgCity_EventScript_GymBoy_Part4::
	msgbox Part4_Text_021, MSGBOX_DEFAULT
	return

Part4_Text_022:
	.string "千里馆主一直在等你回来。$"

PetalburgCity_EventScript_Gentleman_Part4::
	msgbox Part4_Text_022, MSGBOX_DEFAULT
	return

Part4_Text_023:
	.string "我刚从道馆出来。千里馆主那只请假\n王……我现在听见脚步声都有点紧张\p。$"

Part4_Text_024:
	.string "你赢了？那我也不能一直坐在这里。$"

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
	.string "岸边有一包保存完好的食物。$"

Part4_Text_026:
	.string "这里已经没有东西了。$"

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
	.string "有了冲浪，以前只能在岸边看着的地\n方，现在也能去了。$"

Part4_Text_028:
	.string "石缝里卡着一个小小的冠状物。$"

Part4_Text_029:
	.string "石缝已经空了。$"

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
	.string "沙滩上卡着一个旧玻璃瓶。里面的纸\n被海水泡得模糊。\p只剩一句话：希望下一片海也有好天\n气。$"

Part4_Text_031:
	.string "瓶子已经空了。$"

Part4_BottlePearl::
	lock
	faceplayer
	goto_if_set FLAG_PART4_BOTTLEPEARL, Part4_BottlePearl_After
	msgbox Part4_Text_030, MSGBOX_DEFAULT
	giveitem ITEM_PEARL, 1
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_BOTTLEPEARL
	Part4_BottlePearl_After::
	msgbox Part4_Text_031, MSGBOX_DEFAULT
	release
	end

Part4_Text_032:
	.string "箱子上的字已经褪色。还能看出几个\n不同地区的港口名称。$"

Part4_ShipCargo::
	msgbox Part4_Text_032, MSGBOX_NPC
	end

Part4_Text_033:
	.string "旧机器零件散落在里面。包装来自丰\n缘之外。$"

Part4_ShipParts::
	msgbox Part4_Text_033, MSGBOX_NPC
	end

Part4_Text_034:
	.string "这艘船以前似乎跑过很远的航线。$"

Part4_ShipList::
	msgbox Part4_Text_034, MSGBOX_NPC
	end

Part4_Text_035:
	.string "货舱里还有一块没有生锈的金属膜。$"

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
	.string "角落里有一瓶未开封的营养剂。$"

Part4_Text_038:
	.string "这里已经没有东西了。$"

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
	.string "把你最信任的伙伴派出来吧。让我看\n看这一路的成果。$"

Part4_Text_040:
	.string "你真的变强了。看来我多虑了。$"

Part4_Text_041:
	.string "机器停下后，这块松动的检修板可以\n打开了。$"

Part4_Text_042:
	.string "面板在剧烈振动。现在打不开。$"

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
	.string "这里的旧设备经常需要检查。停机后\n才能进去，安全第一。$"

Part4_Text_044:
	.string "你碰到阿尔刻的外勤人员了？我也在\n帮他们检查旧设备。$"

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
	.string "空气里有一股刺鼻的气味。头发似乎\n都竖起来了。$"

Part4_StaticAir::
	msgbox Part4_Text_045, MSGBOX_NPC
	end

Part4_Text_046:
	.string "电缆上留着焦黑的痕迹。附近不时传\n来低沉的响声。$"

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
	.string "你说地下那阵电是宝可梦造成的？哇\n哈哈！难怪那些仪器怎么修都不对劲\p！$"

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
	.string "我装树果的篮子被河水冲走了。好像\n漂到那边的岸上了。$"

Part4_Text_050:
	.string "是我的篮子！给你几颗树果吧，装在\n口袋里就不会漂走了。$"

Part4_Text_051:
	.string "谢谢你的帮忙。$"

Part4_Text_052:
	.string "找到了。先带回去吧。$"

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
	.string "水舰队队员：站住！我们在找一批从\n河上运来的货。先让你的宝可梦退开\p！$"

Part4_Text_054:
	.string "水舰队队员：一个人还挺能打！我来\n对付你！$"

Part4_Text_055:
	.string "啧……还没完呢！$"

Part4_Text_056:
	.string "水舰队队员：就是这个训练家！大家\n一起上！$"

Part4_Text_057:
	.string "男子：到此为止吧。巨钳螳螂。\p水舰队队员：等等！先撤退！$"

Part4_Text_058:
	.string "男子：刚才的战斗我看到了。你和宝\n可梦的配合很特别。\p正好，我这里有一样东西。放在我这\n里也没什么用，也许你更适合。$"

Part4_Text_059:
	.string "有些宝可梦能在战斗中，完成超越普\n通进化的变化。\p这叫超级进化。需要手环，以及宝可\n梦携带对应的超级石。\p训练家和宝可梦的配合也很重要。试\n着亲手感受吧。\p我还要赶路。有机会再见。$"

Part4_MegaScene::
	goto_if_unset FLAG_BADGE05_GET, Part4_SceneEnd
	goto_if_unset FLAG_RECEIVED_HM_SURF, Part4_SceneEnd
	goto_if_ge VAR_PART4_MEGA_STAGE, 4, Part4_SceneEnd
	lockall
	goto_if_ge VAR_PART4_MEGA_STAGE, 3, Part4_MegaGift
	goto_if_ge VAR_PART4_MEGA_STAGE, 2, Part4_MegaRescue
	goto_if_defeated TRAINER_PART4_AQUA_A, Part4_MegaBattleB
	msgbox Part4_Text_053, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART4_AQUA_A, Part4_Text_055
	Part4_MegaBattleB::
	setvar VAR_PART4_MEGA_STAGE, 1
	special SyncPart4MegaObjects
	removeobject LOCALID_PART4_AQUAA
	goto_if_defeated TRAINER_PART4_AQUA_B, Part4_MegaMore
	msgbox Part4_Text_054, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART4_AQUA_B, Part4_Text_055
	Part4_MegaMore::
	setvar VAR_PART4_MEGA_STAGE, 2
	Part4_MegaRescue::
	special SyncPart4MegaObjects
	removeobject LOCALID_PART4_AQUAB
	addobject LOCALID_PART4_ANTI
	addobject LOCALID_PART4_ANTISCIZOR
	addobject LOCALID_PART4_AQUAEXTRA0
	addobject LOCALID_PART4_AQUAEXTRA1
	addobject LOCALID_PART4_AQUAEXTRA2
	msgbox Part4_Text_056, MSGBOX_DEFAULT
	msgbox Part4_Text_057, MSGBOX_DEFAULT
	playmoncry SPECIES_SCIZOR, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_PART4_ANTISCIZOR, Part4_ScizorFlash
	waitmovement 0
	applymovement LOCALID_PART4_AQUAEXTRA0, Part4_GruntRetreat
	waitmovement 0
	removeobject LOCALID_PART4_AQUAEXTRA0
	applymovement LOCALID_PART4_AQUAEXTRA1, Part4_GruntRetreat
	waitmovement 0
	removeobject LOCALID_PART4_AQUAEXTRA1
	applymovement LOCALID_PART4_AQUAEXTRA2, Part4_GruntRetreat
	waitmovement 0
	removeobject LOCALID_PART4_AQUAEXTRA2
	setvar VAR_PART4_MEGA_STAGE, 3
	special SyncPart4MegaObjects
	Part4_MegaGift::
	msgbox Part4_Text_058, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, FALSE, Part4_BagFull
	setflag FLAG_PART4_MEGA_RING_RECEIVED
	setvar VAR_PART4_MEGA_STAGE, 4
	msgbox Part4_Text_059, MSGBOX_DEFAULT
	special SyncPart4MegaObjects
	removeobject LOCALID_PART4_ANTI
	removeobject LOCALID_PART4_ANTISCIZOR
	releaseall
	end
	Part4_SceneEnd::
	end

Part4_Text_060:
	.string "这里有一块带着电光纹路的石头。$"

Part4_Text_061:
	.string "岩石上仍有细小的电击痕迹。$"

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
	.string "淋成这样了？过来歇一会儿吧。等伙\n伴缓过来再走。$"

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
	.string "泥里已经没有东西了。$"

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
	.string "下雨也不能把它们都叫回来。你看，\n虫宝可梦自己也想对战！$"

Part4_Text_066:
	.string "唔，被雨声盖住指令了吗？$"

Part4_Text_067:
	.string "雨天的宝可梦总会换一种精神。下次\n我也会留心。$"

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
	.string "我和莲叶童子一起去看河水，回头就\n找不到妈妈了……她在南边的营地。$"

Part4_Text_069:
	.string "小孩和莲叶童子回到了营地。$"

Part4_Text_070:
	.string "下次我会先告诉妈妈，再出门的。$"

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
	.string "你帮他找到了路？太感谢了。孩子自\n己不害怕，我都快急坏了。给你几瓶\p牛奶。$"

Part4_Text_072:
	.string "你也注意脚下，别光顾着看宝可梦呀\n。$"

Part4_Text_073:
	.string "孩子刚才带着莲叶童子往北走了，到\n现在还没回来。$"

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
	.string "屏幕上正在记录降雨量。图表边缘留\n着手写的校正记号。$"

Part4_Instrument1F0::
	msgbox Part4_Text_074, MSGBOX_NPC
	end

Part4_Text_075:
	.string "屏幕上正在记录降雨量。图表边缘留\n着手写的校正记号。$"

Part4_Instrument2F0::
	msgbox Part4_Text_075, MSGBOX_NPC
	end

Part4_Text_076:
	.string "一份海洋温度记录。不同日期的数据\n被仔细整理在一起。$"

Part4_Instrument2F1::
	msgbox Part4_Text_076, MSGBOX_NPC
	end

Part4_Text_077:
	.string "观测日志上写着：连续降雨，河流水\n位需复核。$"

Part4_Instrument2F2::
	msgbox Part4_Text_077, MSGBOX_NPC
	end

Part4_Text_078:
	.string "设备运行正常，读数很稳定。$"

Part4_Observation0::
	lockall
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Part4_QuietEnd
	msgbox Part4_Text_078, MSGBOX_DEFAULT
	setflag FLAG_PART4_OBSERVATION_0
	releaseall
	end

Part4_Text_079:
	.string "雨水把设备外壳冲得很干净。$"

Part4_Observation1::
	lockall
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Part4_QuietEnd
	msgbox Part4_Text_079, MSGBOX_DEFAULT
	setflag FLAG_PART4_OBSERVATION_1
	releaseall
	end

Part4_Text_080:
	.string "这条线路松了一点。\n你把它重新接好了。$"

Part4_Observation2::
	lockall
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Part4_QuietEnd
	msgbox Part4_Text_080, MSGBOX_DEFAULT
	setflag FLAG_PART4_OBSERVATION_2
	releaseall
	end

Part4_Text_081:
	.string "三个观测桩都确认过了？帮大忙了。\n这瓶营养剂给你。$"

Part4_Text_082:
	.string "雨还会下上一阵。过河时要留心。$"

Part4_Text_083:
	.string "观测桩在南边河岸。能帮我查看三处\n的刻度吗？不赶时间的话再去就好。$"

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
	.string "它在外面有换过样子吗？如果有，记\n得告诉我们当天的天气。$"

Part4_CastformComment::
	special CheckPart4LeadCastform
	goto_if_eq VAR_RESULT, FALSE, Part4_Return
	msgbox Part4_Text_084, MSGBOX_DEFAULT
	return

Part4_Text_085:
	.string "雨声很大，对战的指令也得说清楚。\n一起试试？$"

Part4_Text_086:
	.string "记录好了。配合比我们想得还重要。$"

Part4_Text_087:
	.string "我们在这儿做野外观测。要不要来一\n场双打？不方便也没关系。$"

Part4_Text_088:
	.string "我们是阿尔刻的外勤人员，常在这条\n路观测连续降雨。\p那位技术员负责仪器，我们两个负责\n调查和安全。你有兴趣的话，下次再\p聊。$"

Part4_Text_089:
	.string "带上两只还能战斗的宝可梦，双打才\n方便。$"

Part4_Text_090:
	.string "好，赶路要紧。祝你一路顺利。$"

Part4_Text_091:
	.string "那边好像出了点事。我们先看着这几\n台仪器。$"

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
	.string "仪器的接口进水了。别碰，等我擦干\n。$"

Part4_ArcheTech::
	msgbox Part4_Text_092, MSGBOX_NPC
	end

Part4_Text_093:
	.string "我走阿尔刻的物流渠道进货。时间球\n和树果管够，石头可没那么多。每种\p普通进化石两块，进化石一块。$"

Part4_Text_094:
	.string "有需要再来。我也会在这附近多歇几\n天。$"

Part4_Text_095:
	.string "路上太湿，货还没拆开。你先往前走\n吧。$"

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
	.string "水位比记录高了一点。\n这里的天气变化得真快。$"

Part4_119Observer::
	lock
	faceplayer
	msgbox Part4_Text_096, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART4_ARCHE_KNOWN, Part4_QuietEnd
	msgbox Part4_Text_155, MSGBOX_DEFAULT
	release
	end

Part4_Text_097:
	.string "我的风筝落到树桥下面了。你能帮我\n找找吗？$"

Part4_Text_098:
	.string "找到了！这是我捡到的尖锐鸟嘴。送\n给你，我要去找青绵鸟玩。$"

Part4_Text_099:
	.string "谢谢你的帮忙。$"

Part4_Text_100:
	.string "找到了。先带回去吧。$"

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
	.string "这里有些信件，靠飞行宝可梦送更快\n。\p刚才一个包裹从树桥旁掉到草地了。\n能帮我捡回来吗？别拆开呀。$"

Part4_Text_102:
	.string "完好无损！今天总算不用赔钱了。这\n几个球拿去吧。$"

Part4_Text_103:
	.string "谢谢你的帮忙。$"

Part4_Text_104:
	.string "找到了。先带回去吧。$"

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
	releaseall
	end

Part4_Text_105:
	.string "这儿的木板常要换。长鼻叶比我还会\n挑木料，不过钉钉子还得靠我。$"

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
	.string "你赢了娜琪？在这儿住这么久，我都\n没能跟上她的飞行宝可梦。$"

Part4_FortreeBadgeComment::
	goto_if_unset FLAG_BADGE06_GET, Part4_Return
	msgbox Part4_Text_106, MSGBOX_DEFAULT
	return

Part4_Text_107:
	.string "这件小摆设是外地朋友寄来的。放在\n木头房间里还挺合适。$"

Part4_Text_108:
	.string "一个小巧的外地工艺品。边角被擦得\n很干净。$"

Part4_ForeignDecor::
	msgbox Part4_Text_108, MSGBOX_NPC
	end

Part4_Text_109:
	.string "有人在树边刻了个小小的箭头。旁边\n写着：我的秘密基地。$"

Part4_BaseNote::
	msgbox Part4_Text_109, MSGBOX_NPC
	end

Part4_Text_110:
	.string "大吾：那个手环……你已经得到它了\n？看来这一路，你确实遇到了不少人\p。$"

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
	.string "树根间闪着一点光。是一块带有复杂\n纹路的石头。$"

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
	Part4_Mawilite_After::
	msgbox Part4_Text_112, MSGBOX_DEFAULT
	release
	end

Part4_Text_113:
	.string "前面正在测量，设备还没收好。先别\n踩进去。$"

Part4_Text_114:
	.string "你一定要过去？那先和我打一场。也\n可以等我们收好设备。$"

Part4_Text_115:
	.string "让你的伙伴也留心脚下。$"

Part4_Text_116:
	.string "行。你比我想的稳多了。$"

Part4_Text_117:
	.string "过去吧，别踩到线路。我把这边的设\n备挪开。$"

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
	setflag FLAG_PART4_GUARD_PASSED
	removeobject LOCALID_PART4_ARCHEGUARD
	release
	end

Part4_Text_118:
	.string "石碑上的字已经模糊了。只能辨出很\n浅的刻痕。$"

Part4_Text_119:
	.string "雨水沿着凹槽流下。那些线条，好像\n在描绘风、云和山。$"

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
	.string "急着赶路吗？不着急的话，和我们认\n真比一场吧。$"

Part4_Text_121:
	.string "呼……这一场值得！$"

Part4_Text_122:
	.string "我就待在这里练习。你想往前走，绕\n过我就行。$"

Part4_ForestAce::
	lock
	faceplayer
	trainerbattle_single TRAINER_PART4_ACE, Part4_Text_120, Part4_Text_121
	msgbox Part4_Text_122, MSGBOX_DEFAULT
	release
	end

Part4_Text_123:
	.string "我本来在钓爱心鱼，结果……全是这\n些大家伙！你来看看！$"

Part4_Text_124:
	.string "唉，钓鱼和对战都没顺过！$"

Part4_Text_125:
	.string "阿尔刻那些人在边上摆仪器，把钓位\n都占了。我女儿快过生日了，还没钓\p到她想要的爱心鱼。她在水静市。$"

Part4_Text_126:
	.string "女儿收到爱心鱼了？真是帮大忙了。\n我钓到过这块石头，你拿着吧。$"

Part4_Text_127:
	.string "今年的生日，总算有件能让她开心的\n事了。$"

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
	.string "这块石头是我在附近捡到的。岩石上\n本来没有这种花纹。\p比起研究它，我更想找到遗迹的入口\n。你拿去看看吧。$"

Part4_Text_129:
	.string "也许哪天，我就能找到入口了。$"

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
	.string "岩壁上的封印没有任何反应。现在似\n乎无法打开。$"

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

Part4_SealLoad::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Part4_SealBlock
	goto_if_unset FLAG_PART4_SEAL_AUTHORIZED, Part4_SealBlock
	setmetatile 7, 3, 0x201, FALSE
	end
	Part4_SealBlock::
	setmetatile 7, 3, 0x201, TRUE
	end

Part4_Text_131:
	.string "封印深处留着一小块材料。$"

Part4_Text_132:
	.string "封印内部已经空了。$"

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
	.string "我的生日快到了。爸爸去120号道路\n钓爱心鱼，好几天都没钓到。你愿意\p送我一只吗？$"

Part4_Text_134:
	.string "你的队伍里还没有爱心鱼。没关系，\n我可以再等等。$"

Part4_Text_135:
	.string "等等，你还要带着能战斗的伙伴旅行\n。先别把它送给我。$"

Part4_Text_136:
	.string "它还带着东西呢。先把道具取下来吧\n。$"

Part4_Text_137:
	.string "谢谢你！我会好好照顾它的。也告诉\n爸爸一声吧，他还在120号道路的湖\p边。$"

Part4_Text_138:
	.string "它好可爱！这是我收到的最好的生日\n礼物。$"

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
	.string "……这个给你。$"

Part4_Text_140:
	.string "得到了古空棘鱼！$"

Part4_Text_141:
	.string "你会需要它的。$"

Part4_Text_142:
	.string "……先留一个空位。$"

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
	.string "那个人前几天就来了，一直不怎么说\n话。大概喜欢安静吧。$"

Part4_Text_145:
	.string "树屋之间的风，可没看起来那么简单\n。让它们带你体验一下！$"

Part4_Text_146:
	.string "被你找准风向了！$"

Part4_Text_147:
	.string "娜琪能看到更高处的风。我还差得远\n呢。$"

Part4_TreeBird::
	lock
	faceplayer
	trainerbattle_single TRAINER_PART4_BIRD, Part4_Text_145, Part4_Text_146
	msgbox Part4_Text_147, MSGBOX_DEFAULT
	release
	end

Part4_Text_148:
	.string "我和伙伴飞过丰缘的天空。现在，让\n我看看你们会怎样迎着风向前。$"

Part4_Text_149:
	.string "娜琪：你有那样的手环了。力量发生\n变化时，配合也要跟着改变。记住刚\p才战斗中的感觉。$"

Part4_WinonaRing::
	checkitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, FALSE, Part4_Return
	msgbox Part4_Text_149, MSGBOX_DEFAULT
	return

Part4_Text_155:
	.string "南边的人提到过你。\n看来你很喜欢到处跑。$"

Part4_Text_156:
	.string "雷公的身影随着一道电光，\n消失在通道深处……\p空气中仍残留着细微的电流。\p也许等你站上丰缘训练家的\n顶点之后，它还会再次回应你。$"

Part4_Text_157:
	.string "终于追上你了！这条路也太长了，\n而且一路都在下雨！\p正好，来打一场，活动一下！$"
