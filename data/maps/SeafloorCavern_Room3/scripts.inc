SeafloorCavern_Room3_MapScripts::
	.byte 0

SeafloorCavern_Room3_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_SEAFLOOR_CAVERN, SeafloorCavern_Room3_Text_ShellyIntro, SeafloorCavern_Room3_Text_ShellyDefeat
	msgbox SeafloorCavern_Room3_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_5, SeafloorCavern_Room3_Text_Grunt5Intro, SeafloorCavern_Room3_Text_Grunt5Defeat
	msgbox SeafloorCavern_Room3_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_Text_ShellyIntro:
    .string "啊哈哈哈！\p没有潜水艇你是\n怎么追到这儿的？\l真是了不起的小家伙！\p不过……\n我可不会让你继续捣乱了，\p而且，天气研究所的账\n也该好好算算了……\p让你尝尝苦头吧！\n觉悟吧！$"

SeafloorCavern_Room3_Text_ShellyDefeat:
    .string "啊哈哈哈！\p好痛！$"

SeafloorCavern_Room3_Text_ShellyPostBattle:
    .string "啊哈哈哈！\n强得离谱啊你。\p你不是海洋队的一员\n实在太遗憾了。\p本来你也能一起见证老大向我们承诺的\n那个美妙新世界的……$"

SeafloorCavern_Room3_Text_Grunt5Intro:
    .string "为了实现我们的梦想，\n我们需要宝可梦的力量。\p但是那些像你一样爱管闲事的人\n却总是用宝可梦的力量来碍事，\l甚至都追到了这里来！\p人生总是不能\n如我们所愿！$"

SeafloorCavern_Room3_Text_Grunt5Defeat:
    .string "咕哇！$"

SeafloorCavern_Room3_Text_Grunt5PostBattle:
    .string "听着，我们从来不敢质疑\n老大想干的事。\p可你，一个小鬼头，\n竟然要对抗我们的老大。\p也许……\n你真是个人物。$"

