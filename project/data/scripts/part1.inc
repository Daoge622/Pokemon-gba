
Part1_Text_BagFull:
	.string "背包里没有空位了。\p留出空位后，再回来领取吧。$"

Part1_GiveExpShare::
 goto_if_set FLAG_RECEIVED_EXP_SHARE, Part1_GiveExpShare_Return
 msgbox Part1_Text_TeacherIntro, MSGBOX_DEFAULT
 giveitem ITEM_EXP_SHARE, 1
 goto_if_eq VAR_RESULT, FALSE, Part1_GiveExpShare_BagFull
 setflag FLAG_RECEIVED_EXP_SHARE
 setflag FLAG_PART1_EXP_SHARE_ENABLED
 msgbox Part1_Text_ExpShareExplain, MSGBOX_DEFAULT
Part1_GiveExpShare_Return::
 return
Part1_GiveExpShare_BagFull::
 msgbox Part1_Text_BagFull, MSGBOX_DEFAULT
 return
Part1_TeacherFollowup::
 goto_if_unset FLAG_RECEIVED_EXP_SHARE, Part1_GiveExpShare_Return
 goto_if_unset FLAG_PART1_EXP_SHARE_ENABLED, Part1_TeacherOff
 msgbox Part1_Text_TeacherOn, MSGBOX_DEFAULT
 return
Part1_TeacherOff::
 msgbox Part1_Text_TeacherOff, MSGBOX_DEFAULT
 return

Part1_Text_TeacherIntro:
	.string "老师：等等，你是第一次来挑战道馆\n的训练家吧？\p卡那兹训练家学校有一项新人训练计\n划。\p杜鹃馆主也很支持这项计划哦。\p这个学习装置就交给你了！$"

Part1_Text_ExpShareExplain:
	.string "学习装置已经开启了。\p没有参加战斗的同行宝可梦，也能获\n得一些经验值。\p蛋和濒死的宝可梦不会获得经验。\p想按自己的节奏训练时，可以在重要\n道具里随时关闭或开启。$"

Part1_Text_TeacherOn:
	.string "学习装置会帮助同行的宝可梦一起成\n长。\p如果想换一种训练方法，随时都能关\n闭它。$"

Part1_Text_TeacherOff:
	.string "把学习装置关掉了吗？\p嗯，这也是一种训练方法。\p重要的是找到适合自己的节奏。$"
