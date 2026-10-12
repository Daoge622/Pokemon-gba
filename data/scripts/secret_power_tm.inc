Route111_Text_MakingRoomUseTMToMakeYourOwn:
	.string "哎？你问我在干什么？\p"
	.string "我正想用宝可梦的招式在这里\n"
	.string "造一个只属于自己的房间！\p"
	.string "对了！这个招式学习器送你！\n"
	.string "你也试试看怎么样？$"

Route111_Text_ExplainSecretPower:
	.string "找一棵挂满藤蔓的大树，\n"
	.string "对着树干使用秘密之力——\l"
	.string "藤蔓落下来，就能爬上树干了！\p"
	.string "你会发现超大的空间，\n"
	.string "可以随意布置喜欢的东西。\l"
	.string "那就是独属于你的秘密房间……\l"
	.string "我们叫它——“秘密基地”！\l"
	.string "你也应该弄一个试试！\p"
	.string "还有还有，能制造秘密基地的\n"
	.string "地方可不仅仅只有树上哦！\p"
	.string "试试对岩壁上凹陷的裂缝\n"
	.string "也使用秘密之力吧！\p"
	.string "我还要去找其他好地方呢，\n"
	.string "先走啦！拜拜！$"

Route111_Text_DontWantThis:
	.string "啊？你不想要吗？\n"
	.string "改变主意了随时找我呀！$"

Route111_Text_DontHaveAnyRoom:
	.string "啊，你的包包好像满了！\p"
	.string "我先帮你拿着，等下次包包\n"
	.string "空出来了，再过来拿吧！$"

Route111_EventScript_SecretPowerMan::
	lock
	faceplayer
	msgbox Route111_Text_MakingRoomUseTMToMakeYourOwn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_EventScript_GiveSecretPower
	msgbox Route111_Text_DontWantThis, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_GiveSecretPower::
	giveitem ITEM_TM_SECRET_POWER
	goto_if_eq VAR_RESULT, FALSE, Route111_EventScript_NoRoomForSecretPower
	msgbox Route111_Text_ExplainSecretPower, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RECEIVED_SECRET_POWER
	clearflag FLAG_HIDE_SLATEPORT_CITY_TM_SALESMAN
	call_if_eq VAR_FACING, DIR_WEST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_EAST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_NORTH, Route111_EventScript_SecretPowerManExitNorth
	removeobject VAR_LAST_TALKED
	release
	end

Route111_EventScript_SecretPowerManExit::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExit
	waitmovement 0
	return

Route111_EventScript_SecretPowerManExitNorth::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExitNorth
	waitmovement 0
	return

Route111_EventScript_NoRoomForSecretPower::
	msgbox Route111_Text_DontHaveAnyRoom, MSGBOX_DEFAULT
	release
	end

Route111_Movement_SecretPowerManExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

Route111_Movement_SecretPowerManExitNorth:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
