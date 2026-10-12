
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
	.string "好精彩的对战！\p除了汽水，这个也送给你！\p让水属性宝可梦携带，会很有用哦。$"

Part2_TryMuseumThanks::
 goto_if_unset FLAG_DELIVERED_DEVON_GOODS, Part2_RewardReturn
 goto_if_set FLAG_PART2_RECEIVED_HEART_SCALES, Part2_RewardReturn
 msgbox Part2_Text_MuseumThanks, MSGBOX_DEFAULT
 giveitem ITEM_HEART_SCALE, 3
 goto_if_eq VAR_RESULT, FALSE, Part2_RewardBagFull
 setflag FLAG_PART2_RECEIVED_HEART_SCALES
 return
Part2_Text_MuseumThanks:
	.string "多亏了你，博物馆和重要资料都平安\n无事。\p这些是在海洋调查时收集到的。\p也许以后会派上用场。\p如果背包没空位，来找一楼的工作人\n员就好。$"

Part2_TryTrickBonus::
 goto_if_lt VAR_TRICK_HOUSE_LEVEL, 1, Part2_RewardReturn
 goto_if_set FLAG_PART2_TRICK_EXTRA_CANDY, Part2_RewardReturn
 msgbox Part2_Text_TrickBonus, MSGBOX_DEFAULT
 giveitem ITEM_RARE_CANDY, 1
 goto_if_eq VAR_RESULT, FALSE, Part2_RewardBagFull
 setflag FLAG_PART2_TRICK_EXTRA_CANDY
 return
Part2_Text_TrickBonus:
	.string "第一次完整通过机关屋的额外奖品！\p如果这次拿不下，就来入口的奖品盒\n领取吧。$"
