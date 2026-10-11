@ mid game: quest NPCs turned into battles, Hayato at the Training Hall
@
@ IMPORTANT: the PARTNER_* story slots have NO saved "defeated" flag
@ (Part55_TrainerFlag in src/part55.c returns 0 for any slot it does not list),
@ so goto_if_defeated on TRAINER_STORY_C_xx is always false. Every battle here
@ therefore records its own result in its "Won" continue script:
@   FLAG_STORY_C_01  Mt. Pyre 1F grave worker beaten      (TRAINER_STORY_C_03)
@   FLAG_STORY_C_02  Mossdeep stargazing couple beaten    (TRAINER_STORY_C_04)
@   FLAG_STORY_C_03  Exchange Hall foreign trainer beaten (TRAINER_STORY_C_06)
@   FLAG_STORY_C_04  Hayato beaten at the Training Hall   (TRAINER_STORY_C_07)
@   trainer flag of TRAINER_PART5_SCYTHER_FAN (a real slot that is no longer
@     fought anywhere)  Lilycove Dept. Store 3F duo beaten (TRAINER_STORY_C_02)
@   VAR_PART55_BUOY == 2  Route124 buoy researcher beaten (TRAINER_STORY_C_05)
@   Route121 bug fans use the real slot TRAINER_PART5_BUG_DUO (own flag).
@ FLAG_TEMP_1F: per-visit hide flag of Hayato's object in the Training Hall,
@   set by StoryC_HayatoHall_SetVisibility while FLAG_BADGE06_GET is unset.
@ Existing milestone flags used: FLAG_BADGE06_GET, FLAG_BADGE07_GET,
@   FLAG_RECEIVED_HM_WATERFALL (weather crisis over), FLAG_SYS_GAME_CLEAR.

@ ---------------------------------------------------------------
@ Lilycove Department Store 3F: the two who bought the wrong gear
@ (entry points Part55_WrongGear / Part55_GearFriend in part55.inc)
@ ---------------------------------------------------------------
StoryC_WrongGear_Won::
	settrainerflag TRAINER_PART5_SCYTHER_FAN
StoryC_WrongGear_Talk::
	lock
	faceplayer
	msgbox Part55_Text_0052, MSGBOX_DEFAULT
	release
	end

StoryC_GearFriend_Won::
	settrainerflag TRAINER_PART5_SCYTHER_FAN
StoryC_GearFriend_Talk::
	lock
	faceplayer
	msgbox Part55_Text_0053, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------
@ Arche Training Hall: Hayato (new NPC, placed by the campus builder)
@ ---------------------------------------------------------------
StoryC_HayatoHall_SetVisibility::
	clearflag FLAG_TEMP_1F
	goto_if_set FLAG_BADGE06_GET, StoryC_HayatoHall_SetVisibility_End
	setflag FLAG_TEMP_1F
	return
StoryC_HayatoHall_SetVisibility_End::
	goto_if_unset FLAG_STORY_A_07, StoryC_HayatoHall_SetVisibility_Ret
	setflag FLAG_TEMP_1F
StoryC_HayatoHall_SetVisibility_Ret::
	return

StoryC_HayatoHall::
	lock
	faceplayer
	@ INTEGRATOR: replace the next line's target with StoryA_HayatoResign after the merge.
	goto_if_set FLAG_SYS_GAME_CLEAR, StoryA_HayatoResign
	goto_if_set FLAG_RECEIVED_HM_WATERFALL, StoryC_HayatoHall_Crisis
	goto_if_set FLAG_BADGE07_GET, StoryC_HayatoHall_Badge7
	msgbox StoryC_Text_HayatoNew, MSGBOX_DEFAULT
	release
	end

StoryC_HayatoHall_Badge7::
	msgbox StoryC_Text_HayatoBadge7, MSGBOX_DEFAULT
	goto StoryC_HayatoHall_Offer

StoryC_HayatoHall_Crisis::
	msgbox StoryC_Text_HayatoCrisis, MSGBOX_DEFAULT
	goto StoryC_HayatoHall_Offer

StoryC_HayatoHall_Offer::
	goto_if_set FLAG_STORY_C_04, StoryC_HayatoHall_End
	msgbox StoryC_Text_HayatoAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, StoryC_HayatoHall_No
	trainerbattle_single TRAINER_STORY_C_07, StoryC_Text_HayatoIntro, StoryC_Text_HayatoDefeat, StoryC_HayatoHall_Won
	release
	end

StoryC_HayatoHall_No::
	msgbox StoryC_Text_HayatoNo, MSGBOX_DEFAULT
	release
	end

StoryC_HayatoHall_Won::
	setflag FLAG_STORY_C_04
	lock
	faceplayer
	msgbox StoryC_Text_HayatoWon, MSGBOX_DEFAULT
	release
	end

StoryC_HayatoHall_Clear::
	msgbox StoryC_Text_HayatoClear, MSGBOX_DEFAULT
StoryC_HayatoHall_End::
	release
	end

@ ---------------------------------------------------------------
@ Text
@ ---------------------------------------------------------------
StoryC_Text_BugFansIntro:
	.string "飞天螳螂才是最强的！\p不对，巨钳螳螂的钳子才是！\p你来评评理！用对战来评！$"

StoryC_Text_GearIntro:
	.string "买错了也不能白买。\p陪我们试试这些用品，\n两个一起上！$"

StoryC_Text_GearDefeat:
	.string "……果然用不上。$"

StoryC_Text_GearNotEnough:
	.string "你得带两只能战斗的宝可梦才行。$"

StoryC_Text_GraveIntro:
	.string "这里的宝可梦闲不住。\p扫墓之前，\n先陪它们活动活动吧。$"

StoryC_Text_GraveDefeat:
	.string "……它们玩得很高兴。$"

StoryC_Text_StarIntro:
	.string "嘘……他刚睡着。\p……你是训练家？\n那正好，我把他叫起来。\p两个人一起上，你不介意吧？$"

StoryC_Text_StarDefeat:
	.string "……他又睡着了。$"

StoryC_Text_StarNotEnough:
	.string "你只带了一只宝可梦？\n那就算了，让他睡吧。$"

StoryC_Text_BuoyIntro:
	.string "采样正好告一段落。\p陪我的伙伴放放电吧。\n谢礼打完再给你。$"

StoryC_Text_BuoyDefeat:
	.string "……数据记下了。输的那种。$"

StoryC_Text_BuoyGive:
	.string "说好的谢礼。\n潜水的时候用得上。$"

StoryC_Text_ForeignIntro:
	.string "我的伙伴都是从外地来的。\p想见识一下吗？\n在丰缘可不常见。$"

StoryC_Text_ForeignDefeat:
	.string "……丰缘的训练家真不简单。$"

StoryC_Text_HayatoNew:
	.string "隼人：包吃住，器材随便用。\p……哪有这种好事。$"

StoryC_Text_HayatoBadge7:
	.string "隼人：他们记录每一场对战。\p连我输的都记。$"

StoryC_Text_HayatoCrisis:
	.string "隼人：我问过那些数据\n拿去干什么。\p没人回答我。$"

StoryC_Text_HayatoAsk:
	.string "……打一场？\n要记就让他们记。$"

StoryC_Text_HayatoNo:
	.string "行。想打再来。$"

StoryC_Text_HayatoIntro:
	.string "别放水。$"

StoryC_Text_HayatoDefeat:
	.string "……行。这场也记上吧。$"

StoryC_Text_HayatoWon:
	.string "隼人：输了就是输了。\p……下次不在这儿打。$"

StoryC_Text_HayatoClear:
	.string "隼人：……$"

StoryC_Text_MaxieArche:
	.string "赤焰松：阿尔刻……那家公司？\n他们量得很准。\p量完之后什么都不做。$"

StoryC_Text_ArchieArche:
	.string "对了，老大提过阿尔刻那帮人。\p“他们来买过我们的潜水数据。\n我没卖。\p跟钱没关系，\n我不喜欢他们看海的眼神。”$"
