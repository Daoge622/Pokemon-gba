Route102_MapScripts::
	.byte 0

Route102_EventScript_LittleBoy::
	msgbox Route102_Text_ImNotVeryTall, MSGBOX_NPC
	end

Route102_EventScript_RouteSignOldale::
	msgbox Route102_Text_RouteSignOldale, MSGBOX_SIGN
	end

Route102_EventScript_RouteSignPetalburg::
	msgbox Route102_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route102_EventScript_Boy::
	msgbox Route102_Text_CatchWholeBunchOfPokemon, MSGBOX_NPC
	end

Route102_EventScript_Calvin::
	trainerbattle_single TRAINER_CALVIN_1, Route102_Text_CalvinIntro, Route102_Text_CalvinDefeated, Route102_EventScript_CalvinRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_CalvinRematch
	setvar VAR_0x8004, TRAINER_CALVIN_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route102_EventScript_CalvinTryRegister
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route102_EventScript_CalvinRegisterMatchCall
	release
	end

Route102_EventScript_CalvinRegisterMatchCall::
	msgbox Route102_Text_CalvinRegisterShort, MSGBOX_DEFAULT
	register_matchcall TRAINER_CALVIN_1
	release
	end

Route102_EventScript_CalvinTryRegister::
	goto_if_set FLAG_HAS_MATCH_CALL, Route102_EventScript_CalvinRegister
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRegister::
	msgbox Route102_Text_CalvinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CALVIN_1
	release
	end

Route102_EventScript_CalvinRematch::
	trainerbattle_rematch TRAINER_CALVIN_1, Route102_Text_CalvinRematchIntro, Route102_Text_CalvinRematchDefeated
	msgbox Route102_Text_CalvinRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Rick::
	trainerbattle_single TRAINER_RICK, Route102_Text_RickIntro, Route102_Text_RickDefeated
	msgbox Route102_Text_RickPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Tiana::
	trainerbattle_single TRAINER_TIANA, Route102_Text_TianaIntro, Route102_Text_TianaDefeated
	msgbox Route102_Text_TianaPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Allen::
	trainerbattle_single TRAINER_ALLEN, Route102_Text_AllenIntro, Route102_Text_AllenDefeated
	msgbox Route102_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_Text_WatchMeCatchPokemon:
    .string "满充：{PLAYER}……\n草丛里会藏着宝可梦，对吧？\p请你看看我捕捉宝可梦的\n方法对不对。\p……哇！$"

Route102_Text_WallyIDidIt:
    .string "满充：成功了……这是我的……\n我的宝可梦！$"

Route102_Text_LetsGoBack:
    .string "{PLAYER}，谢谢你！\n我们回道馆吧！$"

Route102_Text_ImNotVeryTall:
    .string "我……不是很高，所以在草丛里\n走的时候我就被草遮起来了。\p草总是戳到我的鼻子里，然后就……\n阿——阿—阿——阿……\p阿嚏！$"

Route102_Text_CatchWholeBunchOfPokemon:
    .string "我要捉一大堆\n宝可梦！$"

Route102_Text_RouteSignOldale:
    .string "102号道路\n{RIGHT_ARROW}古玫镇$"

Route102_Text_RouteSignPetalburg:
    .string "102号道路\n{LEFT_ARROW}橙华市$"

@ Ordinary early-route trainer; future identity is deliberately unspecified.
Route102_EventScript_NewWorker::
	trainerbattle_single TRAINER_ROUTE102_NEW_WORKER, Route102_Text_NewWorkerIntro, Route102_Text_NewWorkerDefeated, Route102_EventScript_NewWorkerAfterBattle
	goto Route102_EventScript_NewWorkerReward

Route102_EventScript_NewWorkerAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto Route102_EventScript_NewWorkerReward

Route102_EventScript_NewWorkerReward::
	goto_if_set FLAG_RECEIVED_ROUTE102_FULL_HEAL, Route102_EventScript_NewWorkerFollowup
	msgbox Route102_Text_NewWorkerThanks, MSGBOX_DEFAULT
	giveitem ITEM_FULL_HEAL, 1
	goto_if_eq VAR_RESULT, FALSE, Route102_EventScript_NewWorkerBagFull
	setflag FLAG_RECEIVED_ROUTE102_FULL_HEAL
	msgbox Route102_Text_NewWorkerFarewell, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_NewWorkerBagFull::
	msgbox Route102_Text_NewWorkerBagFull, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_NewWorkerFollowup::
	msgbox Route102_Text_NewWorkerFollowup, MSGBOX_DEFAULT
	release
	end

Route102_Text_NewWorkerIntro:
	.string "你也是刚开始旅行的训练家吗？\p"
	.string "真巧，我最近也刚开始\n"
	.string "一份新工作。\p"
	.string "说实话……我一直有些担心，\n"
	.string "不知道自己能不能做好。\p"
	.string "要不要陪我切磋一下？\n"
	.string "我想看看自己现在的实力。$"

Route102_Text_NewWorkerDefeated:
	.string "……原来如此。$"

Route102_Text_NewWorkerThanks:
	.string "看来，不是非得准备好一切，\n"
	.string "才能迈出第一步啊。\p"
	.string "谢谢你。和你对战之后，\n"
	.string "我好像没那么没信心了。\p"
	.string "这个给你吧。\p"
	.string "这是工作时发的常备用品，\n"
	.string "我还有呢。$"

Route102_Text_NewWorkerFarewell:
	.string "那我也该继续工作了。\p"
	.string "祝你旅途顺利！$"

Route102_Text_NewWorkerBagFull:
	.string "你的背包已经满了。\p"
	.string "等有空位了再来找我吧，\n"
	.string "我会替你留着的。$"

Route102_Text_NewWorkerFollowup:
	.string "下次见面时，希望我已经\n"
	.string "能够独当一面了。$"
