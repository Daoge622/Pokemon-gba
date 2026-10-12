MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	goto Part7_StevenReward

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_unset FLAG_PART7_METAGROSSITE_DONE, Part7_StevenReward
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
    .string "大吾：你果然找到了这里。\p听说你赢了米可利。\p……\p那我也不用客气了。\p来吧。$"

MeteorFalls_StevensCave_Text_StevenDefeat:
    .string "……真了不起。\p冠军这个称号，你当之无愧。$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
    .string "大吾：在石之洞窟第一次见到你的时\n候，\p我就有种感觉。\p……我的预感一向很准。\p我还会在这里待一阵子。\p下次见面，我们都会更强。$"

