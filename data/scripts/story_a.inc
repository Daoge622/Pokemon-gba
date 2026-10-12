@ ending, Anti sightings, Xavier battle, Evelyn/Rein/sample echoes
@
@ Flags owned by this file:
@   FLAG_STORY_A_01  Oceanic Museum 2F: the man (Anti) has left (set by the Devon Goods scene)
@   FLAG_STORY_A_02  Mt. Pyre summit: the man walked away from the graves
@   FLAG_STORY_A_03  Pacifidlog: Xavier beaten
@   FLAG_STORY_A_04  Lilycove: Saori handed over the film negative
@   FLAG_STORY_A_05  Player's house: Mom handed over the two letters (Visitor Card received)
@   FLAG_STORY_A_06  Campus HQ: Visitor Card used on the elevator panel
@   FLAG_STORY_A_07  Campus training hall: Hayato's final battle won, he has left
@   FLAG_STORY_A_08  Littleroot: closing scene ("第一部 完") played
@   FLAG_STORY_A_09  Campus HQ: Rein's first line about the sample heard
@   FLAG_STORY_A_10  Campus HQ: Rein's second line about the sample heard
@   FLAG_STORY_A_11  Pacifidlog: Ancient Slab received
@   FLAG_STORY_A_12  Campus cafe: the man is gone (set once the weather crisis reaches Sootopolis)
@
@ Per-visit state (reset on every map load):
@   FLAG_TEMP_1D     hides this file's conditional actors (Sootopolis, Mt. Pyre, Lilycove, Littleroot)
@   VAR_TEMP_9       Mt. Pyre summit: 0 = proximity trigger armed; Littleroot: 1 = play closing scene

StoryA_Return::
	return

@ ---------------------------------------------------------------- Route 127 calibration hand-in
StoryA_CalHandIn::
	msgbox StoryA_Text_CalRein1, MSGBOX_DEFAULT
	msgbox StoryA_Text_CalFisher1, MSGBOX_DEFAULT
	msgbox StoryA_Text_CalRein2, MSGBOX_DEFAULT
	msgbox StoryA_Text_CalBoatman, MSGBOX_DEFAULT
	msgbox StoryA_Text_CalFisher2, MSGBOX_DEFAULT
	msgbox StoryA_Text_CalRein3, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------- Sample echoes
StoryA_StevenSample::
	msgbox StoryA_Text_StevenSample, MSGBOX_DEFAULT
	return

@ Hooked from Part6_RainHQ_AfterRepeat (lock/faceplayer already done there).
StoryA_ReinSample::
	goto_if_set FLAG_STORY_A_09, StoryA_ReinSample_Second
	msgbox StoryA_Text_ReinSample1, MSGBOX_DEFAULT
	setflag FLAG_STORY_A_09
	release
	end
StoryA_ReinSample_Second::
	msgbox StoryA_Text_ReinSample2, MSGBOX_DEFAULT
	setflag FLAG_STORY_A_10
	release
	end

StoryA_LilycoveSync::
	setflag FLAG_TEMP_1D
	goto_if_lt VAR_SKY_PILLAR_STATE, 2, StoryA_Return
	clearflag FLAG_TEMP_1D
	return

StoryA_Saori::
	lock
	faceplayer
	goto_if_set FLAG_STORY_A_04, StoryA_Saori_Done
	msgbox StoryA_Text_Saori1, MSGBOX_DEFAULT
	msgbox StoryA_Text_Saori2, MSGBOX_DEFAULT
	giveitem ITEM_FILM_NEGATIVE, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	setflag FLAG_STORY_A_04
	release
	end
StoryA_Saori_Done::
	msgbox StoryA_Text_SaoriDone, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- Anti sightings
@ 1: Oceanic Museum 2F. He keeps looking at the model.
StoryA_MuseumAnti::
	lock
	msgbox StoryA_Text_MuseumAnti, MSGBOX_DEFAULT
	release
	end

@ Called from the Devon Goods scene while the screen is black.
StoryA_MuseumAntiLeave::
	removeobject LOCALID_STORY_A_MUSEUM_ANTI
	setflag FLAG_STORY_A_01
	return

@ 3: campus cafe (placed by the campus builder). He stays seated.
StoryA_AntiCafe::
	lock
	msgbox StoryA_Text_AntiCafe, MSGBOX_DEFAULT
	release
	end

@ 4: Mt. Pyre summit, after the orbs were taken.
StoryA_PyreSync::
	setflag FLAG_TEMP_1D
	setvar VAR_TEMP_9, 1
	goto_if_set FLAG_STORY_A_02, StoryA_Return
	goto_if_lt VAR_MT_PYRE_STATE, 1, StoryA_Return
	clearflag FLAG_TEMP_1D
	setvar VAR_TEMP_9, 0
	return

StoryA_PyreAntiTrigger::
	lockall
	setvar VAR_TEMP_9, 1
	setflag FLAG_STORY_A_02
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 40
	applymovement LOCALID_STORY_A_PYRE_ANTI, StoryA_Movement_PyreAntiLeave
	waitmovement 0
	setvar VAR_0x8000, LOCALID_STORY_A_PYRE_ANTI
	setvar VAR_0x8001, 8
	call Story_WalkAwayAndRemove
	releaseall
	end

StoryA_Movement_PyreAntiLeave:
	delay_16
	walk_slow_left
	step_end

StoryA_PyreGrave::
	msgbox StoryA_Text_PyreGrave, MSGBOX_SIGN
	end

@ 5: Sootopolis crater rim during the weather crisis (objects have no script).
StoryA_SootopolisSync::
	setflag FLAG_TEMP_1D
	goto_if_unset FLAG_SYS_WEATHER_CTRL, StoryA_Return
	clearflag FLAG_TEMP_1D
	setflag FLAG_STORY_A_12
	return

@ ---------------------------------------------------------------- Xavier (Pacifidlog)
@ Entered from Part6_Saviel_Quiet: the regi reward was already handed over.
StoryA_Xavier::
	goto_if_set FLAG_STORY_A_11, StoryA_Xavier_Silent
	goto_if_set FLAG_STORY_A_03, StoryA_Xavier_Give
	goto_if_lt VAR_SKY_PILLAR_STATE, 2, StoryA_Xavier_Silent
	msgbox StoryA_Text_XavierIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STORY_XAVIER, StoryA_Text_XavierDefeat
	setflag FLAG_STORY_A_03
StoryA_Xavier_Give::
	msgbox StoryA_Text_XavierAfter, MSGBOX_DEFAULT
	giveitem ITEM_ANCIENT_SLAB, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	setflag FLAG_STORY_A_11
	release
	end
StoryA_Xavier_Silent::
	msgbox StoryA_Text_Silence, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- After the Hall of Fame
@ Called from PlayersHouse_1F_EventScript_Mom (lock/faceplayer already done there).
StoryA_MomLetters::
	goto_if_set FLAG_STORY_A_05, StoryA_Return
	msgbox StoryA_Text_MomLetters, MSGBOX_DEFAULT
	msgbox StoryA_Text_StevenLetter, MSGBOX_DEFAULT
	msgbox StoryA_Text_UnsignedLetter, MSGBOX_DEFAULT
	giveitem ITEM_VISITOR_CARD, 1
	goto_if_eq VAR_RESULT, FALSE, StoryA_Return
	setflag FLAG_STORY_A_05
	return

@ Campus HQ 1F elevator panel (bg sign placed by the campus builder).
StoryA_ElevatorB::
	lockall
	checkitem ITEM_VISITOR_CARD
	goto_if_eq VAR_RESULT, FALSE, StoryA_ElevatorB_Plain
	msgbox StoryA_Text_ElevatorSwipe, MSGBOX_DEFAULT
	playse SE_FAILURE
	msgbox StoryA_Text_ElevatorDenied, MSGBOX_DEFAULT
	setflag FLAG_STORY_A_06
	releaseall
	end
StoryA_ElevatorB_Plain::
	msgbox StoryA_Text_ElevatorPlain, MSGBOX_DEFAULT
	releaseall
	end

@ Campus HQ 1F guard next to the elevator (placed by the campus builder).
StoryA_GuardCard::
	lock
	faceplayer
	goto_if_set FLAG_STORY_A_06, StoryA_GuardCard_Used
	msgbox StoryA_Text_GuardPlain, MSGBOX_DEFAULT
	release
	end
StoryA_GuardCard_Used::
	msgbox StoryA_Text_GuardCard, MSGBOX_DEFAULT
	release
	end

@ VAR_RESULT = TRUE while the packing Hayato should stand in the training hall.
StoryA_HayatoVisible::
	setvar VAR_RESULT, FALSE
	goto_if_unset FLAG_SYS_GAME_CLEAR, StoryA_Return
	goto_if_set FLAG_STORY_A_07, StoryA_Return
	setvar VAR_RESULT, TRUE
	return

@ Campus training hall: Hayato packing up (placed by the campus builder).
StoryA_HayatoResign::
	lock
	faceplayer
	goto_if_set FLAG_STORY_A_07, StoryA_HayatoResign_Leave
	msgbox StoryA_Text_HayatoResign, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STORY_HAYATO_FINAL, StoryA_Text_HayatoDefeat
	setflag FLAG_STORY_A_07
StoryA_HayatoResign_Leave::
	msgbox StoryA_Text_HayatoFarewell, MSGBOX_DEFAULT
	closemessage
	copyvar VAR_0x8000, VAR_LAST_TALKED
	setvar VAR_0x8001, 8
	call Story_WalkAwayAndRemove
	release
	end

@ Littleroot: arm the closing scene only when the player steps out of their own front door.
StoryA_LittlerootSync::
	setflag FLAG_TEMP_1D
	goto_if_set FLAG_STORY_A_08, StoryA_Return
	goto_if_unset FLAG_STORY_A_06, StoryA_Return
	goto_if_unset FLAG_STORY_A_07, StoryA_Return
	special StorePlayerCoordsInVars
	goto_if_ne VAR_0x8005, 8, StoryA_Return
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, StoryA_LittlerootSync_Female
	goto_if_ne VAR_0x8004, 5, StoryA_Return
	setobjectxyperm LOCALID_STORY_A_SCIZOR, 4, 5
	goto StoryA_LittlerootSync_Arm
StoryA_LittlerootSync_Female::
	goto_if_ne VAR_0x8004, 14, StoryA_Return
	setobjectxyperm LOCALID_STORY_A_SCIZOR, 15, 5
StoryA_LittlerootSync_Arm::
	clearflag FLAG_TEMP_1D
	setvar VAR_TEMP_9, 1
	return

StoryA_Ending::
	lockall
	setvar VAR_TEMP_9, 0
	setflag FLAG_STORY_A_08
	setobjectsubpriority LOCALID_STORY_A_SCIZOR, MAP_LITTLEROOT_TOWN, 0
	delay 20
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, StoryA_Movement_CameraUp
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 40
	applymovement LOCALID_STORY_A_SCIZOR, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	playmoncry SPECIES_SCIZOR, CRY_MODE_NORMAL
	waitmoncry
	delay 60
	applymovement LOCALID_STORY_A_SCIZOR, StoryA_Movement_ScizorFlyOff
	waitmovement 0
	removeobject LOCALID_STORY_A_SCIZOR
	delay 60
	fadescreen FADE_TO_BLACK
	special RemoveCameraObject
	delay 40
	msgbox StoryA_Text_PartOneEnd, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreen FADE_FROM_BLACK
	releaseall
	end

StoryA_Movement_CameraUp:
	walk_slow_up
	walk_slow_up
	step_end

StoryA_Movement_ScizorFlyOff:
	walk_fast_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	step_end

@ ---------------------------------------------------------------- Text
StoryA_Text_Silence:
	.string "……$"

StoryA_Text_CalRein1:
	.string "莱因：留下。$"

StoryA_Text_CalFisher1:
	.string "渔夫：你说过校准完就拆。$"

StoryA_Text_CalRein2:
	.string "莱因：我说的是如果数据允许。\p数据不允许。$"

StoryA_Text_CalBoatman:
	.string "船工：上周就是这台机器\n提前报了警。\p不然我们已经撞进那股急流了。$"

StoryA_Text_CalFisher2:
	.string "渔夫没再说话。$"

StoryA_Text_CalRein3:
	.string "莱因：你校准得很准。\p所以它得留下。\p……这不是夸你。$"

StoryA_Text_EvelynAfter1:
	.string "伊芙琳：你赢了。\n后续实验到此为止。\p样本在你上来之前就采完了。\n你阻止的是我还没做的那一半。$"

StoryA_Text_EvelynAfter2:
	.string "莱因只相信读数。\p读数不会告诉他接下来该做什么。\p……我会。$"

StoryA_Text_StevenSample:
	.string "大吾：塔顶有人先到过。\p设备的痕迹还很新。\p……我会去查。$"

StoryA_Text_ReinSample1:
	.string "莱因：她带回来的东西，\n我没签过字。$"

StoryA_Text_ReinSample2:
	.string "莱因：环境部门和生命部门\n不是一回事。\p别问我。$"

StoryA_Text_Saori1:
	.string "是你啊。\p天空之柱下面撤出来\n一支运输队。我拍到了。\p稿子交上去，你猜怎么着？$"

StoryA_Text_Saori2:
	.string "他们说版面调整。\p我干这行八年，头一回听说\n版面能调整三次。\p……这张底片放你那儿。$"

StoryA_Text_SaoriDone:
	.string "底片还在你那儿吧？\p那就行。$"

StoryA_Text_MuseumAnti:
	.string "……做得很像。$"

StoryA_Text_AntiCafe:
	.string "这里的咖啡一般。\p坐一会儿还可以。$"

StoryA_Text_PyreGrave:
	.string "字迹磨平了。\p看不出是哪一年立的。$"

StoryA_Text_XavierIntro:
	.string "……让我看看，\n它们选了什么样的人。$"

StoryA_Text_XavierDefeat:
	.string "……$"

StoryA_Text_XavierAfter:
	.string "一个量天，一个量命。\p……都太急了。\p这个，你拿着。\p读不懂没关系。$"

StoryA_Text_MomLetters:
	.string "对了，有你的信。\p两封。$"

StoryA_Text_StevenLetter:
	.string "是大吾寄来的信。\p“烈空坐醒来之前，\n有人从塔顶取走了某样东西。”\p“运输记录到水静港就断了。”\p“我会继续查。\n你先休息。”$"

StoryA_Text_UnsignedLetter:
	.string "另一封信没有署名。\p里面只有一张卡片和一行字。\p“想知道的话，来地下看看。”\p“不想知道也没有关系。”$"

StoryA_Text_ElevatorSwipe:
	.string "电梯面板上有一个“B”键。\p把访客卡贴了上去。$"

StoryA_Text_ElevatorDenied:
	.string "“权限不足。\n已记录本次访问。”$"

StoryA_Text_ElevatorPlain:
	.string "员工电梯。\p需要刷卡才能使用。$"

StoryA_Text_GuardPlain:
	.string "保安：这部电梯访客不能用。$"

StoryA_Text_GuardCard:
	.string "保安：……这张卡是谁给你的？$"

StoryA_Text_HayatoResign:
	.string "我辞了。\p他们对我不差。\p就是因为不差，我才想不通\n他们要那些记录干什么。\p……走之前，再打一场。$"

StoryA_Text_HayatoDefeat:
	.string "行。\n还是你走前面。$"

StoryA_Text_HayatoFarewell:
	.string "下次见面，\n我要比你先知道答案。$"

StoryA_Text_PartOneEnd:
	.string "第一部　完$"
