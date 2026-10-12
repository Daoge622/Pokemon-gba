MagmaHideout_2F_2R_MapScripts::
	.byte 0

MagmaHideout_2F_2R_EventScript_Grunt15::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_15, MagmaHideout_2F_2R_Text_Grunt15Intro, MagmaHideout_2F_2R_Text_Grunt15Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt15PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_6, MagmaHideout_2F_2R_Text_Grunt6Intro, MagmaHideout_2F_2R_Text_Grunt6Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_7, MagmaHideout_2F_2R_Text_Grunt7Intro, MagmaHideout_2F_2R_Text_Grunt7Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt7PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_8, MagmaHideout_2F_2R_Text_Grunt8Intro, MagmaHideout_2F_2R_Text_Grunt8Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_Text_Grunt15Intro:
    .string "我和你无冤无仇，\n我只是奉命行事！$"

MagmaHideout_2F_2R_Text_Grunt15Defeat:
    .string "虽然我输了，可是……$"

MagmaHideout_2F_2R_Text_Grunt15PostBattle:
    .string "我们挖掘到了难以置信的东西！\n还拿到了靛蓝色宝珠！\p现在只等老大……\n哼哼哼……哈哈哈哈！$"

MagmaHideout_2F_2R_Text_Grunt6Intro:
    .string "实在受不了这热气。\n或许我当初该加入海洋队……$"

MagmaHideout_2F_2R_Text_Grunt6Defeat:
    .string "看来我真的不适合\n待在熔岩队……$"

MagmaHideout_2F_2R_Text_Grunt6PostBattle:
    .string "待在这种地方\n你不会想念大海吗？$"

MagmaHideout_2F_2R_Text_Grunt7Intro:
    .string "在这里有时能感觉到晃动。\p难道是火山在震动？\n还是固拉……\p哎呀！\n不，不，没什么！$"

MagmaHideout_2F_2R_Text_Grunt7Defeat:
    .string "你的进攻真猛烈，\n就像火山一样！$"

MagmaHideout_2F_2R_Text_Grunt7PostBattle:
    .string "就算这次你赢了也\n改变不了什么。\p熔岩队的伟大目标\n马上就要实现了！$"

MagmaHideout_2F_2R_Text_Grunt8Intro:
    .string "我们一个队员正因弄丢了\n熔岩标志而抓狂呢……\p等一下！\n该不会被你捡到了？$"

MagmaHideout_2F_2R_Text_Grunt8Defeat:
    .string "真是难以置信……$"

MagmaHideout_2F_2R_Text_Grunt8PostBattle:
    .string "我总感觉我们的计划\n会以失败告终……$"

