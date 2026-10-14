@ early game: Hayato, Saori, survey posts, Arche foreshadowing
@
@ Flags (agent B)
@ FLAG_STORY_B_01  Hayato battle 1 (Route104) finished; also the hide flag of the Route104 Hayato
@ FLAG_STORY_B_02  Choice Band received from Hayato after battle 2; hide flag of the Route110 Hayato
@ FLAG_STORY_B_03  Hayato battle 3 (Lavaridge) finished; he leaves on the next map load
@ FLAG_STORY_B_04  Petalburg Woods photo scene finished; hide flag of Saori + Venipede there
@ FLAG_STORY_B_05  Saori's Slateport request accepted (survey posts on Routes 103/110/117)
@ FLAG_STORY_B_06  Route103 post inspected while the request is active
@ FLAG_STORY_B_07  Route110 post inspected while the request is active
@ FLAG_STORY_B_08  Route117 post inspected while the request is active
@ FLAG_STORY_B_09  Saori's request reported and rewarded; hide flag of the Slateport Saori
@ FLAG_STORY_B_10  Fallarbor darkroom conversation seen once
@ FLAG_STORY_B_11  Route119 payoff conversation with Saori seen (she is gone afterwards)
@ FLAG_STORY_B_12  Route119 tag battle with the Magma rookie won (started by talking to a bridge Aqua grunt)
@ FLAG_STORY_B_13  Lavaridge tag battle with the rookie (casual clothes) finished
@ FLAG_STORY_B_14  Cable Car station worker spoken to; he is gone on the next map load
@ FLAG_STORY_B_15  Hayato battle 2 (Route110) won (the Choice Band may still be pending if the bag was full)
@ FLAG_STORY_B_16..17  unused
@
@ Trainer-defeated flags do not exist for the PARTNER_STORY_* slots (Part55_TrainerFlag returns 0),
@ so every battle here is tracked with the FLAG_STORY_B_xx flags above.
@
@ Route119 has all 64 object slots in use, so Saori and the rookie share ONE object
@ (LOCALID_STORYB_119_SHARED, gfx VAR_OBJ_GFX_ID_1, flag FLAG_TEMP_1F): it is Saori on the ledge by default,
@ and is re-used as the rookie for the duration of the bridge scene.
@
@ Per-map temporary flags (reset on every map load, set again by the hooks below)
@ FLAG_TEMP_1F  LavaridgeTown: Hayato / Route112_CableCarStation: worker / FallarborTown_PokemonCenter_1F: Saori / Route119: shared object
@ FLAG_TEMP_1E  LavaridgeTown: the two Magma grunts of the rookie event (spawned by script only)

@ ---------------------------------------------------------------
@ Map transition hooks
@ ---------------------------------------------------------------

StoryB_Route104_OnTransition::
	call_if_set FLAG_STORY_B_02, StoryB_HideHayato1
	return

StoryB_HideHayato1::
	setflag FLAG_STORY_B_01
	return

StoryB_Route119_OnTransition::
	setflag FLAG_TEMP_1F
	goto_if_set FLAG_STORY_B_11, StoryB_Return
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_PICNICKER
	clearflag FLAG_TEMP_1F
	return

StoryB_Lavaridge_OnTransition::
	setflag FLAG_TEMP_1E
	setflag FLAG_TEMP_1F
	goto_if_unset FLAG_STORY_B_02, StoryB_Return
	goto_if_set FLAG_STORY_B_03, StoryB_Return
	goto_if_set FLAG_VISITED_MOSSDEEP_CITY, StoryB_Return
	clearflag FLAG_TEMP_1F
	return

StoryB_CableCar_OnTransition::
	setflag FLAG_TEMP_1F
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, StoryB_Return
	goto_if_set FLAG_STORY_B_14, StoryB_Return
	clearflag FLAG_TEMP_1F
	return

StoryB_FallarborPC_OnTransition::
	setflag FLAG_TEMP_1F
	goto_if_unset FLAG_STORY_B_09, StoryB_Return
	goto_if_set FLAG_STORY_B_11, StoryB_Return
	clearflag FLAG_TEMP_1F
	return

StoryB_Return::
	return

@ ---------------------------------------------------------------
@ Survey posts
@ ---------------------------------------------------------------

StoryB_Post116::
	msgbox StoryB_Text_Post, MSGBOX_SIGN
	end

StoryB_Post103::
	lock
	msgbox StoryB_Text_Post, MSGBOX_DEFAULT
	goto_if_unset FLAG_STORY_B_05, StoryB_Release
	goto_if_set FLAG_STORY_B_09, StoryB_Release
	setflag FLAG_STORY_B_06
	msgbox StoryB_Text_PostMarkedBySaori, MSGBOX_DEFAULT
	release
	end

StoryB_Post110::
	lock
	msgbox StoryB_Text_Post, MSGBOX_DEFAULT
	goto_if_unset FLAG_STORY_B_05, StoryB_Release
	goto_if_set FLAG_STORY_B_09, StoryB_Release
	setflag FLAG_STORY_B_07
	msgbox StoryB_Text_PostMarkedBySaori, MSGBOX_DEFAULT
	release
	end

StoryB_Post117::
	lock
	msgbox StoryB_Text_Post, MSGBOX_DEFAULT
	goto_if_unset FLAG_STORY_B_05, StoryB_Release
	goto_if_set FLAG_STORY_B_09, StoryB_Release
	setflag FLAG_STORY_B_08
	msgbox StoryB_Text_PostMarkedBySaori, MSGBOX_DEFAULT
	release
	end

StoryB_PostMarked::
	msgbox StoryB_Text_PostMarked, MSGBOX_SIGN
	end

StoryB_Release::
	release
	end

StoryB_Text_Post:
	.string "某种测量设备。\n上面没有厂牌，也没有编号。$"

StoryB_Text_PostMarkedBySaori:
	.string "纱织在地图上标记的，\n就是这一根。$"

StoryB_Text_PostMarked:
	.string "和路上见过的桩子是同一种。\p不过这一根钉着蓝色的标牌，\n上面只有一个字母：“A”。$"

@ ---------------------------------------------------------------
@ Hayato
@ ---------------------------------------------------------------

StoryB_Hayato1::
	lock
	faceplayer
	goto_if_set FLAG_STORY_B_01, StoryB_Hayato1_After
	msgbox StoryB_Text_Hayato1_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STORY_HAYATO_1, StoryB_Text_Hayato1_Defeat
	setflag FLAG_STORY_B_01
	msgbox StoryB_Text_Hayato1_After, MSGBOX_DEFAULT
	release
	end

StoryB_Hayato1_After::
	msgbox StoryB_Text_Hayato1_After, MSGBOX_DEFAULT
	release
	end

StoryB_Text_Hayato1_Intro:
	.string "你也是今年出发的？\n我比你早半个月。\p……不过早半个月又怎样，\n打一场就知道了。$"

StoryB_Text_Hayato1_Defeat:
	.string "行，你走前面。$"

StoryB_Text_Hayato1_After:
	.string "我叫隼人。\p别回头看我，\n我很快就会追上来的。$"

StoryB_Hayato2::
	lock
	faceplayer
	goto_if_set FLAG_STORY_B_02, StoryB_Hayato2_After
	goto_if_set FLAG_STORY_B_15, StoryB_Hayato2_Give
	call_if_set FLAG_STORY_B_01, StoryB_Hayato2_IntroMet
	call_if_unset FLAG_STORY_B_01, StoryB_Hayato2_IntroNew
	trainerbattle_no_intro TRAINER_STORY_HAYATO_2, StoryB_Text_Hayato2_Defeat
	setflag FLAG_STORY_B_15
StoryB_Hayato2_Give::
	msgbox StoryB_Text_Hayato2_Take, MSGBOX_DEFAULT
	giveitem ITEM_CHOICE_BAND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_STORY_B_02
	msgbox StoryB_Text_Hayato2_Lend, MSGBOX_DEFAULT
	release
	end

StoryB_Hayato2_IntroMet::
	msgbox StoryB_Text_Hayato2_IntroMet, MSGBOX_DEFAULT
	return

StoryB_Hayato2_IntroNew::
	msgbox StoryB_Text_Hayato2_IntroNew, MSGBOX_DEFAULT
	return

StoryB_Hayato2_After::
	msgbox StoryB_Text_Hayato2_After, MSGBOX_DEFAULT
	release
	end

StoryB_Text_Hayato2_IntroMet:
	.string "……是你啊。\p我在这儿卡了三天了，\n紫堇道馆就是过不去。\p别用那种眼神看我。\n来，打一场。$"

StoryB_Text_Hayato2_IntroNew:
	.string "你也是今年出发的？\n我叫隼人，比你早半个月。\p早半个月，还不是照样\n在紫堇道馆卡了三天。\p来，打一场。$"

StoryB_Text_Hayato2_Defeat:
	.string "……连飞膝踢都没踢中。$"

StoryB_Text_Hayato2_Take:
	.string "输了就是输了。\n这个你拿着。$"

StoryB_Text_Hayato2_Lend:
	.string "先借你用。\n等你赢了铁旋再还我。$"

StoryB_Text_Hayato2_After:
	.string "我再练两天。\n你先走吧。$"

StoryB_Hayato3::
	lock
	faceplayer
	goto_if_set FLAG_STORY_B_03, StoryB_Hayato3_After
	msgbox StoryB_Text_Hayato3_Intro, MSGBOX_DEFAULT
	msgbox StoryB_Text_Hayato3_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, StoryB_Hayato3_No
	trainerbattle_no_intro TRAINER_STORY_HAYATO_3, StoryB_Text_Hayato3_Defeat
	setflag FLAG_STORY_B_03
	msgbox StoryB_Text_Hayato3_Win, MSGBOX_DEFAULT
	release
	end

StoryB_Hayato3_No::
	msgbox StoryB_Text_Hayato3_No, MSGBOX_DEFAULT
	release
	end

StoryB_Hayato3_After::
	msgbox StoryB_Text_Hayato3_After, MSGBOX_DEFAULT
	release
	end

StoryB_Text_Hayato3_Intro:
	.string "我算过了，照这个速度\n走到联盟，钱会先花光。\p……听说水静那边\n有地方招陪练，包吃包住。$"

StoryB_Text_Hayato3_Ask:
	.string "走之前，再打一场？$"

StoryB_Text_Hayato3_No:
	.string "行，不勉强。\n我泡完这一回温泉再走。$"

StoryB_Text_Hayato3_Defeat:
	.string "……还是差了一截。$"

StoryB_Text_Hayato3_Win:
	.string "头带你留着吧。\p我去水静看看。\n混不下去再说。$"

StoryB_Text_Hayato3_After:
	.string "还没走呢。\n泡完这一回就动身。$"

@ ---------------------------------------------------------------
@ Saori
@ ---------------------------------------------------------------

StoryB_SaoriWoods::
	lock
	goto_if_set FLAG_STORY_B_04, StoryB_SaoriWoods_After
	msgbox StoryB_Text_SaoriWoods_Hush, MSGBOX_DEFAULT
	closemessage
	delay 30
	playse SE_CLICK
	waitse
	delay 20
	playmoncry SPECIES_VENIPEDE, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_STORYB_WOODS_VENIPEDE, StoryB_Movement_VenipedeFlee
	waitmovement 0
	removeobject LOCALID_STORYB_WOODS_VENIPEDE
	faceplayer
	msgbox StoryB_Text_SaoriWoods_Got, MSGBOX_DEFAULT
	msgbox StoryB_Text_SaoriWoods_Ask, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, StoryB_SaoriWoods_Yes
	call_if_eq VAR_RESULT, NO, StoryB_SaoriWoods_No
	setflag FLAG_STORY_B_04
	release
	end

StoryB_SaoriWoods_Yes::
	msgbox StoryB_Text_SaoriWoods_Yes, MSGBOX_DEFAULT
	return

StoryB_SaoriWoods_No::
	msgbox StoryB_Text_SaoriWoods_No, MSGBOX_DEFAULT
	return

StoryB_SaoriWoods_After::
	faceplayer
	msgbox StoryB_Text_SaoriWoods_After, MSGBOX_DEFAULT
	release
	end

StoryB_WoodsVenipede::
	lock
	playmoncry SPECIES_VENIPEDE, CRY_MODE_NORMAL
	waitmoncry
	msgbox StoryB_Text_WoodsVenipede, MSGBOX_DEFAULT
	release
	end

StoryB_Movement_VenipedeFlee:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

StoryB_Text_SaoriWoods_Hush:
	.string "嘘——别动。$"

StoryB_Text_SaoriWoods_Got:
	.string "……好，拍到了。\p你知道这家伙的老家\n离这儿有多远吗？\p我也不知道它是怎么跑来的。$"

StoryB_Text_SaoriWoods_Ask:
	.string "你一路走过来，\n有没有见过别的“外来户”？$"

StoryB_Text_SaoriWoods_Yes:
	.string "见过？那就不是我眼花了。\n下次再碰到，记得多看两眼。$"

StoryB_Text_SaoriWoods_No:
	.string "没见过？还是没留意？\n以后多留意一下吧。$"

StoryB_Text_SaoriWoods_After:
	.string "我叫纱织，拍照的，也写稿子。\n我在这儿再蹲一会儿。$"

StoryB_Text_WoodsVenipede:
	.string "这不是这片森林里的宝可梦。\n有人正举着相机对准它。$"

StoryB_SaoriSlateport::
	lock
	faceplayer
	goto_if_set FLAG_STORY_B_09, StoryB_SaoriSlateport_Done
	goto_if_set FLAG_STORY_B_05, StoryB_SaoriSlateport_Check
	msgbox StoryB_Text_SaoriSlateport_Offer, MSGBOX_DEFAULT
	setflag FLAG_STORY_B_05
	release
	end

StoryB_SaoriSlateport_Check::
	goto_if_unset FLAG_STORY_B_06, StoryB_SaoriSlateport_Wait
	goto_if_unset FLAG_STORY_B_07, StoryB_SaoriSlateport_Wait
	goto_if_unset FLAG_STORY_B_08, StoryB_SaoriSlateport_Wait
	msgbox StoryB_Text_SaoriSlateport_Report, MSGBOX_DEFAULT
	giveitem ITEM_SCOPE_LENS
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_STORY_B_09
	msgbox StoryB_Text_SaoriSlateport_Thanks, MSGBOX_DEFAULT
	release
	end

StoryB_SaoriSlateport_Wait::
	msgbox StoryB_Text_SaoriSlateport_Wait, MSGBOX_DEFAULT
	release
	end

StoryB_SaoriSlateport_Done::
	msgbox StoryB_Text_SaoriSlateport_Done, MSGBOX_DEFAULT
	release
	end

StoryB_Text_SaoriSlateport_Offer:
	.string "你是训练家？正好。\n训练家不都爱到处跑吗？\p我叫纱织，拍照的，也写稿子。\p我在地图上标了三个地方：\n103、110、117号道路。\p每条路边都有一根灰色的桩子。\n替我各看一眼，再回来告诉我。$"

StoryB_Text_SaoriSlateport_Wait:
	.string "103、110、117号道路，\n路边的灰色桩子，看一眼就行。\p看完了就回凯那来找我。$"

StoryB_Text_SaoriSlateport_Report:
	.string "三个地方都有？还是同一种桩子？\p……有意思。\p没有厂牌的东西，\n往往是最不缺钱的人做的。$"

StoryB_Text_SaoriSlateport_Thanks:
	.string "这个多出来的镜头归你了。\n我要往北边去了。$"

StoryB_Text_SaoriSlateport_Done:
	.string "秋叶镇有间能冲洗胶卷的屋子。\n我去那边把线索串起来。$"

StoryB_SaoriFallarbor::
	lock
	faceplayer
	goto_if_set FLAG_STORY_B_10, StoryB_SaoriFallarbor_After
	msgbox StoryB_Text_SaoriFallarbor, MSGBOX_DEFAULT
	setflag FLAG_STORY_B_10
	release
	end

StoryB_SaoriFallarbor_After::
	msgbox StoryB_Text_SaoriFallarbor_After, MSGBOX_DEFAULT
	release
	end

StoryB_Text_SaoriFallarbor:
	.string "别碰那个盆，胶卷还泡着呢。\p看墙上的地图。红线是我画的，\n从卡那兹一路连到119号道路。\p沿线都是同一种桩子，\n一根接着一根。\p是谁的设备？不知道。\n不过，不知道才有意思，对吧？$"

StoryB_Text_SaoriFallarbor_After:
	.string "红线的尽头在119号道路。\n等胶卷晾干了，我就过去。$"

StoryB_119Shared::
	lock
	faceplayer
	msgbox StoryB_Text_Saori119, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_STORYB_119_SHARED
	setflag FLAG_STORY_B_11
	fadescreen FADE_FROM_BLACK
	release
	end

StoryB_Text_Saori119:
	.string "原来是他们。\p你看那身制服，崭新崭新的。\p这么大规模的调查，\n我却连一篇报道都没见过。\p……我换个角度再拍几张，回头见。$"

@ ---------------------------------------------------------------
@ Foreshadowing NPCs
@ ---------------------------------------------------------------

StoryB_RustboroBuyerA::
	msgbox StoryB_Text_RustboroBuyerA, MSGBOX_NPC
	end

StoryB_RustboroBuyerB::
	msgbox StoryB_Text_RustboroBuyerB, MSGBOX_NPC
	end

StoryB_Text_RustboroBuyerA:
	.string "前台说，那种规格的零件\n不对外供货。\p……话倒是说得挺客气。$"

StoryB_Text_RustboroBuyerB:
	.string "算了，\n我们自己做也一样。$"

StoryB_ShipyardWorker::
	msgbox StoryB_Text_ShipyardWorker, MSGBOX_NPC
	end

StoryB_Text_ShipyardWorker:
	.string "前阵子来了一批精密仪器的订单，\n订货方是谁，没人知道。\p钱付得很爽快，\n就是不让问用途。\p货已经拉去港口了。\n听说有人盯着，今晚就装船。$"

StoryB_MauvilleMeter::
	msgbox StoryB_Text_MauvilleMeter, MSGBOX_NPC
	end

StoryB_Text_MauvilleMeter:
	.string "我？抄电表的。\p新紫堇的事故报告，\n上个月被人调去看过。\p调阅的人不是市政府的。$"

StoryB_CableWorker::
	lock
	faceplayer
	msgbox StoryB_Text_CableWorker, MSGBOX_DEFAULT
	setflag FLAG_STORY_B_14
	release
	end

StoryB_Text_CableWorker:
	.string "箱子里装着一台测温仪。\n他正扣上最后一道锁。\p“数据够了。\p这座山不会再升温了，\n至少今年不会。”$"

StoryB_Xavier114::
	msgbox StoryB_Text_Xavier114, MSGBOX_SIGN
	end

StoryB_Text_Xavier114:
	.string "他专心盯着水面，\n一句话也没说。\p浮标轻轻动了一下。$"

@ ---------------------------------------------------------------
@ Magma rookie: Route119 tag battle (uniform)
@ ---------------------------------------------------------------

@ Entered from Route119_EventScript_BridgeAquaGrunt1/2 (already locked, grunt facing the player)
@ while FLAG_STORY_B_12 is unset. The shared object is far off-screen (Saori's ledge) or hidden.
StoryB_Rookie119::
	msgbox StoryB_Text_Rookie119_Aqua, MSGBOX_DEFAULT
	closemessage
	removeobject LOCALID_STORYB_119_SHARED
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_MAGMA_MEMBER_F
	setobjectxyperm LOCALID_STORYB_119_SHARED, 11, 37
	setobjectmovementtype LOCALID_STORYB_119_SHARED, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_TEMP_1F
	addobject LOCALID_STORYB_119_SHARED
	applymovement LOCALID_STORYB_119_SHARED, StoryB_Movement_Rookie119Arrive
	waitmovement 0
	msgbox StoryB_Text_Rookie119_Intro, MSGBOX_DEFAULT
	multi_2_vs_2 TRAINER_STORY_B_SPARE1, StoryB_Text_Rookie119_AquaALose, TRAINER_STORY_B_SPARE2, StoryB_Text_Rookie119_AquaBLose, PARTNER_PART55_ROOKIE, cancelScript=StoryB_Rookie119_Cancel
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, StoryB_Rookie119_Win
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	end

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

StoryB_Rookie119_Win::
	setflag FLAG_STORY_B_12
	msgbox StoryB_Text_Rookie119_After, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_STORYB_119_SHARED
	call_if_unset FLAG_STORY_B_11, StoryB_Rookie119_RestoreSaori
	fadescreen FADE_FROM_BLACK
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

@ put the shared object back on Saori's ledge; it respawns when the player walks back there
StoryB_Rookie119_RestoreSaori::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_PICNICKER
	setobjectxyperm LOCALID_STORYB_119_SHARED, 26, 49
	setobjectmovementtype LOCALID_STORYB_119_SHARED, MOVEMENT_TYPE_FACE_LEFT
	clearflag FLAG_TEMP_1F
	return

StoryB_Movement_Rookie119Arrive:
	walk_fast_up
	walk_fast_up
	walk_in_place_faster_right
	step_end

StoryB_Text_Rookie119_Aqua:
	.string "又来一个？\p刚才那个熔岩队的小鬼\n还赖在附近不走呢。$"

StoryB_Text_Rookie119_Intro:
	.string "谁是小鬼啊！\p……咦，你、你怎么在这儿！\p算了，来得正好。\n这两个人缠了我半天了。\p我可不是在求你帮忙！\n二对二才公平，仅此而已！$"

StoryB_Text_Rookie119_AquaALose:
	.string "熔岩队居然还带帮手？$"

StoryB_Text_Rookie119_AquaBLose:
	.string "啧……反正桥照样不让过。$"

StoryB_Text_Rookie119_After:
	.string "……谢了。\p别误会，我还是熔岩队的人。\n下次碰上，照样是对手。\p胖丁，走了！任务还没完成呢。$"

@ ---------------------------------------------------------------
@ Magma rookie: Lavaridge tag battle (casual clothes)
@ ---------------------------------------------------------------

StoryB_RookieCivilian::
	goto_if_set FLAG_STORY_B_13, Part6_RookieCivilian
	lock
	faceplayer
	msgbox StoryB_Text_RookieLava_Intro, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	clearflag FLAG_TEMP_1E
	addobject LOCALID_STORYB_LAVA_GRUNT_A
	addobject LOCALID_STORYB_LAVA_GRUNT_B
	waitse
	applymovement LOCALID_PART6_ROOKIE_CIVILIAN, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox StoryB_Text_RookieLava_Grunt, MSGBOX_DEFAULT
	msgbox StoryB_Text_RookieLava_Refuse, MSGBOX_DEFAULT
	multi_2_vs_2 TRAINER_STORY_A_SPARE1, StoryB_Text_RookieLava_GruntALose, TRAINER_STORY_A_SPARE2, StoryB_Text_RookieLava_GruntBLose, PARTNER_STORY_B_SPARE3, cancelScript=StoryB_RookieLava_Cancel
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, StoryB_RookieLava_Win
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	end

StoryB_RookieLava_Cancel::
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_STORYB_LAVA_GRUNT_A
	removeobject LOCALID_STORYB_LAVA_GRUNT_B
	setflag FLAG_TEMP_1E
	fadescreen FADE_FROM_BLACK
	releaseall
	end

StoryB_RookieLava_Win::
	msgbox StoryB_Text_RookieLava_GruntLeave, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8000, LOCALID_STORYB_LAVA_GRUNT_A
	setvar VAR_0x8001, 7
	call Story_WalkAwayAndRemove
	setvar VAR_0x8000, LOCALID_STORYB_LAVA_GRUNT_B
	setvar VAR_0x8001, 7
	call Story_WalkAwayAndRemove
	setflag FLAG_STORY_B_13
	applymovement LOCALID_PART6_ROOKIE_CIVILIAN, Common_Movement_FacePlayer
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox StoryB_Text_RookieLava_Thanks, MSGBOX_DEFAULT
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	release
	end

StoryB_LavaGrunt::
	msgbox StoryB_Text_LavaGrunt, MSGBOX_NPC
	end

StoryB_Text_RookieLava_Intro:
	.string "……嗨。\p等等，你后面那两个人是——$"

StoryB_Text_RookieLava_Grunt:
	.string "总算找到你了。\p队里说了，你的辞呈不算数。\n跟我们回去。$"

StoryB_Text_RookieLava_Refuse:
	.string "我不回去。\p……这一次，你能站在我这边吗？$"

StoryB_Text_RookieLava_GruntALose:
	.string "她什么时候变得这么能打了？$"

StoryB_Text_RookieLava_GruntBLose:
	.string "……打不过啊。$"

StoryB_Text_RookieLava_GruntLeave:
	.string "……算了。\n回去就报告说没找到人吧。$"

StoryB_Text_RookieLava_Thanks:
	.string "谢谢你。\p这还是我头一回\n没有站在你的对面。$"

StoryB_Text_LavaGrunt:
	.string "别挡路。\n我们在找人。$"
