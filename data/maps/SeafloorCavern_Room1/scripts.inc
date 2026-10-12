SeafloorCavern_Room1_MapScripts::
	.byte 0

SeafloorCavern_Room1_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_1, SeafloorCavern_Room1_Text_Grunt1Intro, SeafloorCavern_Room1_Text_Grunt1Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_2, SeafloorCavern_Room1_Text_Grunt2Intro, SeafloorCavern_Room1_Text_Grunt2Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_Text_Grunt1Intro:
    .string "只差最后一步了！\p你别想挡路！$"

SeafloorCavern_Room1_Text_Grunt1Defeat:
    .string "我想回家了……$"

SeafloorCavern_Room1_Text_Grunt1PostBattle:
    .string "好想升职当干部，\n那样就能使唤小卒们了……$"

SeafloorCavern_Room1_Text_Grunt2Intro:
    .string "那潜水艇……里面也太窄了！\n挤得真难受！$"

SeafloorCavern_Room1_Text_Grunt2Defeat:
    .string "失败让我更难受！$"

SeafloorCavern_Room1_Text_Grunt2PostBattle:
    .string "我们抢来的那潜水艇\n坐起来简直折磨人！\l里面挤得要命！$"

