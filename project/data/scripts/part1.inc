
Part1_Text_BagFull:
	.string "背包已经满了，装不下这件东西。\p整理出空位以后再来吧。$"

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
	.string "老师：啊，等一下！你是第一次来挑战\n道馆的训练家吧？\p我是卡那兹训练家学校的老师，\n我们正在推行一项新人训练计划。\p杜鹃馆主也很支持这个计划哦。\p这台学习装置就送给你了，\n路上一定用得着！$"

Part1_Text_ExpShareExplain:
	.string "学习装置已经开启了。\p有了它，没上场战斗的同行宝可梦\n也能分到一些经验值。\p不过，蛋和濒死的宝可梦是拿不到的。\p想按自己的节奏训练的话，可以在\n背包的重要道具栏里随时开关它。$"

Part1_Text_TeacherOn:
	.string "学习装置会帮队伍里的宝可梦\n一起成长。\p想换个方式训练的话，\n随时都可以把它关掉哦。$"

Part1_Text_TeacherOff:
	.string "你把学习装置关掉了啊？\p嗯，专心培养主力也是一种练法。\p找到适合自己的节奏，才是最重要的。$"
