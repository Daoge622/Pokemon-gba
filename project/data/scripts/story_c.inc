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
	.string "飞天螳螂才是最强的！\n速度又快，镰刀又帅！\p"
	.string "胡说！巨钳螳螂的钢铁钳子\n一夹下去谁都受不了！\p"
	.string "我们吵了一上午也没结果。\n你来当裁判，用对战说话！$"

StoryC_Text_GearIntro:
	.string "东西买错了，也不能白买！\n陪我们试试这些用品吧。\p"
	.string "我们两个一起上！$"

StoryC_Text_GearDefeat:
	.string "……果然用不上啊。\n这钱花得真冤。$"

StoryC_Text_GearNotEnough:
	.string "我们是两个人一起上的，\n你得带两只能战斗的宝可梦才行。$"

StoryC_Text_GraveIntro:
	.string "这里的宝可梦精力旺盛得很，\n一刻也闲不住。\p"
	.string "扫墓之前，\n先陪它们活动活动筋骨吧！$"

StoryC_Text_GraveDefeat:
	.string "哈哈，它们玩得很开心。\n谢谢你陪它们。$"

StoryC_Text_StarIntro:
	.string "嘘……他刚睡着。\p"
	.string "嗯？你是训练家？\n那正好，我把他叫起来！\p"
	.string "我们两个一起上，\n你不介意吧？$"

StoryC_Text_StarDefeat:
	.string "输了……\n你看，他又睡着了。$"

StoryC_Text_StarNotEnough:
	.string "你只带了一只宝可梦？\n那就算了，让他接着睡吧。$"

StoryC_Text_BuoyIntro:
	.string "采样工作正好告一段落。\n陪我的伙伴放放电吧！\p"
	.string "说好的谢礼，打完就给你。$"

StoryC_Text_BuoyDefeat:
	.string "数据记下来了……\n是输掉的那一种。$"

StoryC_Text_BuoyGive:
	.string "这是说好的谢礼。\n潜水的时候能派上用场。$"

StoryC_Text_ForeignIntro:
	.string "我的伙伴都是从外地来的，\n在丰缘可不常见哦。\p"
	.string "想见识一下吗？$"

StoryC_Text_ForeignDefeat:
	.string "丰缘的训练家真不简单！$"

StoryC_Text_HayatoNew:
	.string "隼人：包吃包住，器材随便用。\n天底下哪有这种好事？\p"
	.string "反正我是不太信。$"

StoryC_Text_HayatoBadge7:
	.string "隼人：这里每一场对战都有记录，\n连我输掉的那几场也记。\p"
	.string "记得这么细，到底想干什么？$"

StoryC_Text_HayatoCrisis:
	.string "隼人：我问过他们，\n那些数据拿去干什么用。\p"
	.string "结果没有一个人回答我。$"

StoryC_Text_HayatoAsk:
	.string "要不要打一场？\n想记录就让他们记去吧。$"

StoryC_Text_HayatoNo:
	.string "行，想打了再来找我。$"

StoryC_Text_HayatoIntro:
	.string "别放水，\n拿出你的真本事来！$"

StoryC_Text_HayatoDefeat:
	.string "……行，我输了。\n这场也让他们记上吧。$"

StoryC_Text_HayatoWon:
	.string "隼人：输了就是输了，我认。\p"
	.string "下次换个地方打，\n不在这种被人盯着的地方。$"

StoryC_Text_HayatoClear:
	.string "隼人：……$"

StoryC_Text_MaxieArche:
	.string "赤焰松：阿尔刻？那家公司啊。\n他们的测量确实很精确。\p"
	.string "可是测完之后，\n他们什么也不做。$"

StoryC_Text_ArchieArche:
	.string "对了，老大提过阿尔刻那帮人。\p"
	.string "“他们来买过我们的潜水数据，\n我没卖。\p"
	.string "跟钱没关系。\n我只是不喜欢他们看海的眼神。”$"
