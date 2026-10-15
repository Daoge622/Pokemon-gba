
Part2_TryMysticWater::
 goto_if_unset FLAG_DEFEATED_SEASHORE_HOUSE, Part2_RewardReturn
 goto_if_set FLAG_PART2_RECEIVED_MYSTIC_WATER, Part2_RewardReturn
 msgbox Part2_Text_MysticWater, MSGBOX_DEFAULT
 giveitem ITEM_MYSTIC_WATER, 1
 goto_if_eq VAR_RESULT, FALSE, Part2_RewardBagFull
 setflag FLAG_PART2_RECEIVED_MYSTIC_WATER
 return
Part2_RewardReturn::
 return
Part2_RewardBagFull::
 msgbox Part1_Text_BagFull, MSGBOX_DEFAULT
 return
Part2_Text_MysticWater:
	.string "好精彩的对战！看得我都忘了招呼\n客人了！\p除了汽水，这个也送给你吧。\p让水属性宝可梦带着它，水属性招式\n的威力就会变强哦！$"

Part2_TryMuseumThanks::
 goto_if_unset FLAG_DELIVERED_DEVON_GOODS, Part2_RewardReturn
 goto_if_set FLAG_PART2_RECEIVED_HEART_SCALES, Part2_RewardReturn
 msgbox Part2_Text_MuseumThanks, MSGBOX_DEFAULT
 giveitem ITEM_HEART_SCALE, 3
 goto_if_eq VAR_RESULT, FALSE, Part2_RewardBagFull
 setflag FLAG_PART2_RECEIVED_HEART_SCALES
 return
Part2_Text_MuseumThanks:
	.string "多亏了你，博物馆和那些重要的资料\n都平安无事。\p这些心之鳞片是我们在海洋调查时\n收集到的，请收下吧。\p以后说不定会派上用场。\p要是背包没有空位，之后来找一楼的\n工作人员领取就行。$"

Part2_TryTrickBonus::
 goto_if_lt VAR_TRICK_HOUSE_LEVEL, 1, Part2_RewardReturn
 goto_if_set FLAG_PART2_TRICK_EXTRA_CANDY, Part2_RewardReturn
 msgbox Part2_Text_TrickBonus, MSGBOX_DEFAULT
 giveitem ITEM_RARE_CANDY, 1
 goto_if_eq VAR_RESULT, FALSE, Part2_RewardBagFull
 setflag FLAG_PART2_TRICK_EXTRA_CANDY
 return
Part2_Text_TrickBonus:
	.string "恭喜你第一次完整通过机关屋！\p这是额外奖品，请收下吧！\p要是这次拿不下，之后到入口的\n奖品盒那里领取就行。$"
