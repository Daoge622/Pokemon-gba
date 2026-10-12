GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "这附近的洞窟岩壁很复杂。\p有些宝可梦会受强光影响，有些地方\n也能靠光照发现异常。\p这个给你，旅行途中也许能派上用场\n。$"

GraniteCave_1F_Text_ExplainFlash:
	.string "闪光可以照亮其他漆黑的地方。\p教给宝可梦以后，有需要时再试试吧\n。\p在野外使用前，记得先取得武斗道馆\n的徽章。$"


GraniteCave_Part1_Stardust::
 lock
 faceplayer
 goto_if_set FLAG_PART1_GRANITE_STARDUST, GraniteCave_Part1_Stardust_Done
 msgbox GraniteCave_Part1_Stardust_Intro, MSGBOX_DEFAULT
 giveitem ITEM_STARDUST, 1
 goto_if_eq VAR_RESULT, FALSE, GraniteCave_Part1_Stardust_BagFull
 setflag FLAG_PART1_GRANITE_STARDUST
 removeobject VAR_LAST_TALKED
GraniteCave_Part1_Stardust_Done::
 msgbox GraniteCave_Part1_Stardust_After, MSGBOX_DEFAULT
 release
 end
GraniteCave_Part1_Stardust_BagFull::
 msgbox Part1_Text_BagFull, MSGBOX_DEFAULT
 release
 end

GraniteCave_Part1_Stardust_Intro:
	.string "岩石旁有一件东西。$"

GraniteCave_Part1_Stardust_After:
	.string "这里已经没有东西了。$"

GraniteCave_Part1_MetalWall::
 msgbox GraniteCave_Part1_MetalText, MSGBOX_SIGN
 end

GraniteCave_Part1_MetalText:
	.string "岩石中混杂着闪闪发亮的金属颗粒。$"
