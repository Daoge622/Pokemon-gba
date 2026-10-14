FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
    .string "发生了些\n很讨厌的事！\p我总是看到鬼鬼祟祟的家伙\n在索蓝斯博士家进进出出……$"

FallarborTown_Text_RegionKnownForMeteors:
    .string "自古这片地区\n就以陨石而闻名，\p据说流星瀑布就是很久以前\n一颗陨石掉下来砸成的。$"

FallarborTown_Text_MyPreciousAzurill:
    .string "来啊！来看看！\n这是我珍贵的露力丽！\p滑滑软软的，多漂亮！\p流星瀑布的样本很特别。我们也会寄\n给外地同行一起分析。$"

FallarborTown_Text_Azurill:
    .string "露力丽：露力露。$"

FallarborTown_Text_HaveYouChallengedFlannery:
    .string "你挑战过釜炎镇道馆的馆主\n亚莎了吗？\p那女孩的爷爷非常出名，\n他曾是宝可梦联盟的\l四天王之一，\p如今亚莎也成长为一个\n出色的训练家\l并不让我感到奇怪。$"

FallarborTown_Text_BattleTentSign:
    .string "对战帐篷秋叶镇分址\n“最强战队，在此集结！”$"

FallarborTown_Text_TownSign:
    .string "这里是秋叶镇。\n“有着小型田野的农村。”$"

FallarborTown_Text_MoveTutorSign:
    .string "招式爱好者的家\n“教会宝可梦新的招式。”$"


FallarborTown_Part3_Researcher::
 msgbox FallarborTown_Part3_ResearcherText, MSGBOX_NPC
 end

FallarborTown_Part3_ResearcherText:
	.string "这里离流星瀑布很近。\p运气好的话，还真能捡到陨石呢！$"

FallarborTown_Part3_MeteorFan::
 lock
 faceplayer
 goto_if_set FLAG_MET_ARCHIE_METEOR_FALLS, FallarborTown_Part3_MeteorFanAfter
 msgbox FallarborTown_Part3_MeteorFanText, MSGBOX_DEFAULT
 release
 end
FallarborTown_Part3_MeteorFanAfter::
 msgbox FallarborTown_Part3_MeteorFanAfterText, MSGBOX_DEFAULT
 release
 end

FallarborTown_Part3_MeteorFanText:
	.string "你说，从天上掉下来的石头，\n和我们脚下的石头真有什么不同吗？$"

FallarborTown_Part3_MeteorFanAfterText:
	.string "什么？真有人为了陨石，\n把索蓝斯博士带走了？\p我只是喜欢捡石头而已啊……$"

FallarborTown_Part3_Collector::
 lock
 faceplayer
 goto_if_set FLAG_PART3_RECEIVED_STAR_PIECE, FallarborTown_Part3_CollectorDone
 msgbox FallarborTown_Part3_CollectorIntro, MSGBOX_DEFAULT
 giveitem ITEM_STAR_PIECE
 goto_if_eq VAR_RESULT, FALSE, FallarborTown_Part3_CollectorFull
 setflag FLAG_PART3_RECEIVED_STAR_PIECE
FallarborTown_Part3_CollectorDone::
 msgbox FallarborTown_Part3_CollectorAfter, MSGBOX_DEFAULT
 release
 end
FallarborTown_Part3_CollectorFull::
 msgbox Part1_Text_BagFull, MSGBOX_DEFAULT
 release
 end

FallarborTown_Part3_CollectorIntro:
	.string "这块石头没什么研究价值。\p不过挺漂亮的，就送给你吧。$"

FallarborTown_Part3_CollectorAfter:
	.string "不懂研究也没关系。\n光是喜欢这些石头，就很开心了。$"
