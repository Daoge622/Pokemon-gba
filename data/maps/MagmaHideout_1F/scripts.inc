MagmaHideout_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition:
	setflag FLAG_PART55_HIDE_MAGMA_AFTERMATH
	call_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, Part55_ShowMagmaAftermath
	setflag FLAG_PART55_HIDE_RESCUED_MAGMA
	call_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, Part55_CheckRescuedExit
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

MagmaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_2, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro:
    .string "当熔岩队点名布置任务的时候，\n我们按照排队的顺序各自领到\l重要性不同的守卫任务。\p所以我才被安排到这个角落里——\n因为我点名的时候总是迟到！$"

MagmaHideout_1F_Text_Grunt1Defeat:
    .string "我训练时也\n总是迟到！\p虽然不想承认，\n可我真的很弱……$"

MagmaHideout_1F_Text_Grunt1PostBattle:
    .string "好吧，我以后做事会试着\n再努力一点的……$"

MagmaHideout_1F_Text_Grunt2Intro:
    .string "我们老大叫我们挖掘烟囱山，\n所以我们就一直挖啊挖。\p在挖的过程中，\n我们发现了劲爆的东西！\p究竟是什么？\p哈哈哈！\n打赢我的话就告诉你！$"

MagmaHideout_1F_Text_Grunt2Defeat:
    .string "啊！\n输了！$"

MagmaHideout_1F_Text_Grunt2PostBattle:
    .string "我才不会告诉你。\n你到了那里就知道了！\p悬念要保存到最后一刻，\n你说对吧？$"

