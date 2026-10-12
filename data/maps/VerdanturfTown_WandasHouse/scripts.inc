VerdanturfTown_WandasHouse_MapScripts::
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
	.string "满充：我还会继续练习。\p和宝可梦一起旅行以后，我每天都觉\n得更有精神了！\p下次见面，我一定会让你吓一跳的！$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
	.string "满充：我还会继续练习。\p下次见面，我一定会让你吓一跳的！$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
	.string "叔叔：满充就在隔壁。\p自从开始和宝可梦一起生活，他的精\n神好多了。\p以前总担心他的身体撑不住。现在他\n每天都想着什么时候能再出去训练。$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
    .string "满充不在……\n他一个人溜了出去……$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
    .string "叔叔：真的吗？\n满充自己一个人\l去了那么远的地方……\p我想我该称赞他一下——\n不愧是我弟弟的儿子。$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
	.string "满盈：你就是满充常说的{PLAYER}吧\n？\p我是他的堂姐。自从满充来这儿，他\n变得活泼开朗多了。\p每天一醒来，就惦记着和宝可梦一起\n练习呢。$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
    .string "满盈：别担心满充，\n他没事。\p我了解我的堂弟，\n而且还有宝可梦在他的身边。$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
    .string "多亏了你，我可以天天\n跟我的女朋友相聚了。\l开心吗？当然！那还用说！$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
    .string "我女儿的男友是个\n充满热情和决心的人，\p他为了见我女儿\n每天都不停地挖隧道。\p女儿有些担心，\n所以经常跑到隧道去。$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
    .string "太令人吃惊了，女儿的男友\n徒手挖开了隧道！\p难以置信！$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
    .string "要是满充出了什么事，\n我怎么该和他住在\l橙华市的父母交代……$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
    .string "满充去过彩悠市？\p他那住在橙华市的父母\n一定会大吃一惊的！$"

