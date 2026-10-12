Route113_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route113_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route113_OnTransition
	.byte 0

Route113_OnResume:
	callnative StopDefeatedRoute113Trainers
	setstepcallback STEP_CB_ASH
	end

Route113_OnTransition:
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	call Route113_EventScript_CheckSetAshWeather
	end

Route113_EventScript_CheckSetAshWeather::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_lt VAR_TEMP_0, 19, Route113_EventScript_DontSetAshWeather
	goto_if_gt VAR_TEMP_0, 84, Route113_EventScript_DontSetAshWeather
	setweather WEATHER_VOLCANIC_ASH
	return

Route113_EventScript_DontSetAshWeather::
	return

Route113_EventScript_Gentleman::
	msgbox Route113_Text_AshCanBeFashionedIntoGlass, MSGBOX_NPC
	end

Route113_EventScript_NinjaBoy::
	msgbox Route113_Text_FunWalkingThroughAsh, MSGBOX_NPC
	end

Route113_EventScript_RouteSign111::
	msgbox Route113_Text_RouteSign111, MSGBOX_SIGN
	end

Route113_EventScript_RouteSignFallarbor::
	msgbox Route113_Text_RouteSignFallarbor, MSGBOX_SIGN
	end

Route113_EventScript_GlassWorkshopSign::
	msgbox Route113_Text_GlassWorkshopSign, MSGBOX_SIGN
	end

Route113_EventScript_TrainerTipsRegisterKeyItems::
	msgbox Route113_Text_TrainerTipsRegisterKeyItems, MSGBOX_SIGN
	end

Route113_EventScript_Jaylen::
	trainerbattle_single TRAINER_JAYLEN, Route113_Text_JaylenIntro, Route113_Text_JaylenDefeat
	msgbox Route113_Text_JaylenPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Dillon::
	trainerbattle_single TRAINER_DILLON, Route113_Text_DillonIntro, Route113_Text_DillonDefeat
	msgbox Route113_Text_DillonPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Madeline::
	trainerbattle_single TRAINER_MADELINE_1, Route113_Text_MadelineIntro, Route113_Text_MadelineDefeat, Route113_EventScript_RegisterMadeline
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route113_EventScript_RematchMadeline
	msgbox Route113_Text_MadelinePostBattle, MSGBOX_DEFAULT
	release
	end

Route113_EventScript_RegisterMadeline::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route113_Text_MadelineRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_MADELINE_1
	release
	end

Route113_EventScript_RematchMadeline::
	trainerbattle_rematch TRAINER_MADELINE_1, Route113_Text_MadelineRematchIntro, Route113_Text_MadelineRematchDefeat
	msgbox Route113_Text_MadelinePostRematch, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Lao::
	trainerbattle_single TRAINER_LAO_1, Route113_Text_LaoIntro, Route113_Text_LaoDefeat, Route113_EventScript_RegisterLao
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route113_EventScript_RematchLao
	msgbox Route113_Text_LaoPostBattle, MSGBOX_DEFAULT
	release
	end

Route113_EventScript_RegisterLao::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route113_Text_LaoRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_LAO_1
	release
	end

Route113_EventScript_RematchLao::
	trainerbattle_rematch TRAINER_LAO_1, Route113_Text_LaoRematchIntro, Route113_Text_LaoRematchDefeat
	msgbox Route113_Text_LaoPostRematch, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Lung::
	trainerbattle_single TRAINER_LUNG, Route113_Text_LungIntro, Route113_Text_LungDefeat
	msgbox Route113_Text_LungPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Tori::
	trainerbattle_double TRAINER_TORI_AND_TIA, Route113_Text_ToriIntro, Route113_Text_ToriDefeat, Route113_Text_ToriNotEnoughMons
	msgbox Route113_Text_ToriPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Tia::
	trainerbattle_double TRAINER_TORI_AND_TIA, Route113_Text_TiaIntro, Route113_Text_TiaDefeat, Route113_Text_TiaNotEnoughMons
	msgbox Route113_Text_TiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Sophie::
	trainerbattle_single TRAINER_SOPHIE, Route113_Text_SophieIntro, Route113_Text_SophieDefeat
	msgbox Route113_Text_SophiePostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Coby::
	trainerbattle_single TRAINER_COBY, Route113_Text_CobyIntro, Route113_Text_CobyDefeat
	msgbox Route113_Text_CobyPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Lawrence::
	trainerbattle_single TRAINER_LAWRENCE, Route113_Text_LawrenceIntro, Route113_Text_LawrenceDefeat
	msgbox Route113_Text_LawrencePostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Wyatt::
	trainerbattle_single TRAINER_WYATT, Route113_Text_WyattIntro, Route113_Text_WyattDefeat
	msgbox Route113_Text_WyattPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_Text_AshCanBeFashionedIntoGlass:
    .string "哇哈哈哈！现今的技术\n真是神奇！\p收集这里的火山灰，\n可以做成玻璃。$"

Route113_Text_FunWalkingThroughAsh:
    .string "在布满火山灰的\n草丛里走真好玩，\p回头看看走过的地方——\n哇，都干干净净了！$"

Route113_Text_RouteSign111:
    .string "113号道路\n{RIGHT_ARROW}111号道路$"

Route113_Text_RouteSignFallarbor:
    .string "113号道路\n{LEFT_ARROW}秋叶镇$"

Route113_Text_TrainerTipsRegisterKeyItems:
    .string "有用的公告牌！\p可以将包包中的某个重要物品\n登录到SELECT键上，\p按下SELECT键就可以\n方便地使用登录的物品了。$"

Route113_Text_GlassWorkshopSign:
    .string "琉璃工坊\n“将火山灰变成玻璃”$"


Route113_Part3_Painter::
 lock
 faceplayer
 goto_if_set FLAG_PART3_RECEIVED_PRETTY_FEATHER, Route113_Part3_PainterDone
 msgbox Route113_Part3_PainterIntro, MSGBOX_DEFAULT
 goto_if_unset FLAG_PART3_ROUTE113_VIEW_EXAMINED, Route113_Part3_PainterEnd
 msgbox Route113_Part3_PainterGift, MSGBOX_DEFAULT
 giveitem ITEM_PRETTY_FEATHER
 goto_if_eq VAR_RESULT, FALSE, Route113_Part3_PainterFull
 setflag FLAG_PART3_RECEIVED_PRETTY_FEATHER
Route113_Part3_PainterDone::
 msgbox Route113_Part3_PainterAfter, MSGBOX_DEFAULT
Route113_Part3_PainterEnd::
 release
 end
Route113_Part3_PainterFull::
 msgbox Part1_Text_BagFull, MSGBOX_DEFAULT
 release
 end
Route113_Part3_View::
 lockall
 msgbox Route113_Part3_ViewText, MSGBOX_DEFAULT
 setflag FLAG_PART3_ROUTE113_VIEW_EXAMINED
 releaseall
 end

Route113_Part3_PainterIntro:
	.string "大家都觉得这里灰扑扑的。\p可我倒觉得，灰色也有灰色的漂亮。$"

Route113_Part3_PainterGift:
	.string "你也仔细看过这片风景了吧？\p这根羽毛给你。连落灰的时候，看起\n来也很漂亮呢！$"

Route113_Part3_PainterAfter:
	.string "同一片风景，每次看都会发现一点新\n东西。$"

Route113_Part3_ViewText:
	.string "灰白的道路延伸到远处。\p风吹过时，薄薄的火山灰像波纹一样\n散开。$"

Route113_Part3_SpindaCry::
 lock
 faceplayer
 waitse
 playmoncry SPECIES_SPINDA, CRY_MODE_NORMAL
 waitmoncry
 release
 end

Route113_Part3_SpindaKid::
 lock
 faceplayer
 checkspecies SPECIES_SPINDA
 goto_if_eq VAR_RESULT, TRUE, Route113_Part3_SpindaKidParty
 msgbox Route113_Part3_SpindaKidText, MSGBOX_DEFAULT
 release
 end
Route113_Part3_SpindaKidParty::
 msgbox Route113_Part3_SpindaKidPartyText, MSGBOX_DEFAULT
 release
 end

Route113_Part3_SpindaKidText:
	.string "晃晃斑最喜欢在火山灰里跑了。\p每次回来，都把自己弄得全身是灰！$"

Route113_Part3_SpindaKidPartyText:
	.string "你的晃晃斑花纹也完全不一样！\p真的没有两只是一模一样的吗？$"

Route113_Part3_AshHint::
 msgbox Route113_Part3_AshHintText, MSGBOX_NPC
 end

Route113_Part3_AshHintText:
	.string "火山灰下面，偶尔会盖住一些东西。\p走慢一点，多看看脚下。$"

Route113_Part3_OddishCry::
 lock
 faceplayer
 waitse
 playmoncry SPECIES_ODDISH, CRY_MODE_NORMAL
 waitmoncry
 release
 end

Route113_Part3_AshGrandma::
 msgbox Route113_Part3_AshGrandmaText, MSGBOX_NPC
 end

Route113_Part3_AshGrandmaText:
	.string "我刚扫干净，风一吹就又白干了。\p走路草倒是高兴，转眼又钻进灰里去\n了！$"
