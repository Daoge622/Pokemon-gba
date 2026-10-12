LavaridgeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LavaridgeTown_OnFrame
	.byte 0

LavaridgeTown_OnTransition:
	call StoryB_Lavaridge_OnTransition
	special Part6_SyncMap
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, LavaridgeTown_EventScript_ClearLavaridgeWhiteOut
	call_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, LavaridgeTown_EventScript_ShowMtChimneyTrainers
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_CheckSetRivalPos
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_HideMapNamePopup
	end

LavaridgeTown_EventScript_ClearLavaridgeWhiteOut::
	clearflag FLAG_WHITEOUT_TO_LAVARIDGE
	return

LavaridgeTown_EventScript_CheckSetRivalPos::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, LavaridgeTown_EventScript_SetRivalPos
	return

LavaridgeTown_EventScript_SetRivalPos::
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL, 11, 9
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL_ON_BIKE, 9, 8
	setobjectmovementtype LOCALID_LAVARIDGE_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL
	return

LavaridgeTown_EventScript_ShowMtChimneyTrainers::
	clearflag FLAG_HIDE_MT_CHIMNEY_TRAINERS
	return

LavaridgeTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LavaridgeTown_OnFrame:
	map_script_2 VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_RivalGiveGoGoggles
	.2byte 0

LavaridgeTown_EventScript_RivalGiveGoGoggles::
	lockall
	getplayerxy VAR_0x8008, VAR_0x8009
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalNoticePlayer
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExitHerbShop
	delay 20
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_PlayBrendanMusic
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer2
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_MayGiveGoGoggles
	goto_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_MayGiveGoGoggles::
	msgbox LavaridgeTown_Text_MayNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BrendanGiveGoGoggles::
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_RivalExit::
	closemessage
	removeobject LOCALID_LAVARIDGE_RIVAL
	addobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	delay 30
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit2
	removeobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	setvar VAR_LAVARIDGE_TOWN_STATE, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LavaridgeTown_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

LavaridgeTown_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

LavaridgeTown_EventScript_RivalNoticePlayer::
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExitHerbShop::
	opendoor 12, 15
	waitdooranim
	addobject LOCALID_LAVARIDGE_RIVAL
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalExitHerbShop
	waitmovement 0
	closedoor 12, 15
	waitdooranim
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer2
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit1::
	applymovement LOCALID_PLAYER, LavaridgeTown_Movement_PlayerWatchRivalExit
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit2::
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExit2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_PlayerWatchRivalExit:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LavaridgeTown_Movement_RivalExit1:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

LavaridgeTown_Movement_RivalApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	walk_up
	step_end

LavaridgeTown_Movement_RivalExitHerbShop:
	walk_down
	step_end

LavaridgeTown_EventScript_HotSpringsTrigger::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, LavaridgeTown_EventScript_EnteredHotSprings
	end

LavaridgeTown_EventScript_EnteredHotSprings::
	incrementgamestat GAME_STAT_ENTERED_HOT_SPRINGS
	end

LavaridgeTown_EventScript_ExpertM::
	msgbox LavaridgeTown_Text_HotSpringsNeverRunDry, MSGBOX_NPC
	end

LavaridgeTown_EventScript_OldMan::
	msgbox LavaridgeTown_Text_PokemonNippedBackside, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_Twin::
	msgbox LavaridgeTown_Text_BatheInHotSpringsEveryDay, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman1::
	msgbox LavaridgeTown_Text_IfPokemonInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman2::
	msgbox LavaridgeTown_Text_HotSpringsClaims, MSGBOX_NPC
	end

LavaridgeTown_EventScript_ExpertF::
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_EggWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LAVARIDGE_EGG, LavaridgeTown_EventScript_ReceivedEgg
	msgbox LavaridgeTown_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_EventScript_DeclineEgg
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, LavaridgeTown_EventScript_NoRoomForEgg
	msgbox LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_LAVARIDGE_EGG
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_WYNAUT
	release
	end

LavaridgeTown_EventScript_ReceivedEgg::
	msgbox LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_NoRoomForEgg::
	msgbox LavaridgeTown_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_DeclineEgg::
	msgbox LavaridgeTown_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_TownSign::
	msgbox LavaridgeTown_Text_TownSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_GymSign::
	msgbox LavaridgeTown_Text_GymSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_HerbShopSign::
	msgbox LavaridgeTown_Text_HerbShopSign, MSGBOX_SIGN
	end

LavaridgeTown_Text_MayNiceBadgesTakeThis:
    .string "小遥：{PLAYER}{KUN}！好久不见！\p哦？看来我去温泉的时候\n你已经拿到釜炎镇道馆徽章了。\p你一定得到了不少\n优秀的宝可梦……\l不，我想还是因为你培育得好。\p我想我可以把这个给你。$"

LavaridgeTown_Text_MayExplainGoGogglesChallengeDad:
    .string "小遥：有这个GOGO护目镜的话，\n就能穿越111号道路上的沙漠了。\p不过，{PLAYER}{KUN}居然在\n挑战道馆……\p是不想输给我吧？\n你为此真的很努力呢！\p{PLAYER}{KUN}，我现在打算\n去橙华市道馆挑战你爸爸了！\p回头见！$"

LavaridgeTown_Text_BrendanNiceBadgesTakeThis:
    .string "小悠：{PLAYER}，好久不见了，\n还顺利吗？\p唔……\n你收集了不少徽章了啊。\p那好，\n这个也给你吧。$"

LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad:
    .string "小悠：如果要去111号道路上\n的沙漠就带上它吧。\p那里应该也有一些\n沙漠特有的宝可梦，\l你可以去找找看。\p至于我……\n我打算去挑战橙华市的\l道馆馆主千里。\p{PLAYER}，你爸爸和你不一样，\n他看上去相当厉害！\p再见啦！$"

LavaridgeTown_Text_HaveEggWillYouTakeIt:
    .string "我这儿有个蛋。\p我本来指望用温泉边温暖的沙子\n盖起它来会孵化的，\l但看来这样还不够……\p听说最好能\n让它跟宝可梦\l在一起。\p你是个训练家对吗？\n而且你的宝可梦看上去活力十足。\p怎么样？\n你愿意带上这个蛋孵化它吗？$"

LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg:
    .string "好！希望你能带上\n这个蛋一起旅行！$"

LavaridgeTown_Text_ReceivedTheEgg:
    .string "{PLAYER}得到蛋。$"

LavaridgeTown_Text_NoRoomForThisEgg:
    .string "嗯？你带了太多宝可梦，\n没法再带上这个蛋了……$"

LavaridgeTown_Text_AsYouWishThen:
    .string "那么请便吧……\p如果你改变主意了，\n再来这儿找我。$"

LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare:
    .string "有时宝可梦培育屋里\n会发现蛋，\p至少传闻中是这样。$"

LavaridgeTown_Text_HotSpringsNeverRunDry:
	.string "温泉靠近活火山，地下的水被岩浆加\n热后就冒出来了。\p带着拥有火焰之躯的宝可梦旅行，宝\n可梦的蛋会更快孵化哦。$"

LavaridgeTown_Text_PokemonNippedBackside:
    .string "埋在沙里的感觉……\n哎……\p说不出的温暖美妙……\p呃？呀！啊噢！\p有宝可梦咬了我！$"

LavaridgeTown_Text_OhYouLikeHotSprings:
    .string "你喜欢温泉吗？\p对像你这样的年轻人来说\n还真是少见。\p朋友推荐我来丰缘旅行。这儿的温泉\n比传闻还舒服。$"

LavaridgeTown_Text_BatheInHotSpringsEveryDay:
    .string "我每天都来泡温泉，因为我也想成为\n亚莎那样既漂亮又强大的道馆馆主。$"

LavaridgeTown_Text_IfPokemonInHotSprings:
    .string "如果把宝可梦放进温泉，\n它就会变得很奇怪。\p哈，有时候可能变成电气浴，\n或者泡沫浴，甚至岩浆浴……$"

LavaridgeTown_Text_HotSpringsClaims:
    .string "据说温泉可以放松\n紧张的神经，\l减轻身体的疲劳，\l解决感情问题，\l还能增加财运……$"

LavaridgeTown_Text_TownSign:
    .string "这里是釜炎镇。\n“宝可梦中心、温泉、绝妙的场所。”$"

LavaridgeTown_Text_GymSign:
    .string "釜炎镇宝可梦道馆\n馆主：亚莎\l“热情似火的女性！”$"

LavaridgeTown_Text_HerbShopSign:
    .string "宝可梦中药店\n“良药苦口。”$"


LavaridgeTown_Part3_HotSpring::
 lockall
 msgbox LavaridgeTown_Part3_HotSpringText, MSGBOX_DEFAULT
 special HealPlayerParty
 playfanfare MUS_HEAL
 waitfanfare
 specialvar VAR_RESULT, GetPart3LeadHotSpringType
 goto_if_eq VAR_RESULT, 1, LavaridgeTown_Part3_HotSpringFire
 goto_if_eq VAR_RESULT, 2, LavaridgeTown_Part3_HotSpringIce
 msgbox LavaridgeTown_Part3_HotSpringHealedText, MSGBOX_DEFAULT
 releaseall
 end
LavaridgeTown_Part3_HotSpringFire::
 msgbox LavaridgeTown_Part3_HotSpringFireText, MSGBOX_DEFAULT
 releaseall
 end
LavaridgeTown_Part3_HotSpringIce::
 msgbox LavaridgeTown_Part3_HotSpringIceText, MSGBOX_DEFAULT
 releaseall
 end

LavaridgeTown_Part3_HotSpringText:
	.string "暖暖的泉水让宝可梦放松下来。$"

LavaridgeTown_Part3_HotSpringHealedText:
	.string "队伍里的宝可梦恢复精神了！$"

LavaridgeTown_Part3_HotSpringFireText:
	.string "队伍里的宝可梦恢复精神了！\p领头的宝可梦看起来很舒服。$"

LavaridgeTown_Part3_HotSpringIceText:
	.string "队伍里的宝可梦恢复精神了！\p领头的宝可梦似乎有点受不了这里的\n温度……$"

LavaridgeTown_Part3_Snorunt::
 lock
 faceplayer
 waitse
 playmoncry SPECIES_SNORUNT, CRY_MODE_NORMAL
 waitmoncry
 release
 end

LavaridgeTown_Part3_IceTrainer::
 lock
 faceplayer
 goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Part3_IceTrainerLeave
 msgbox LavaridgeTown_Part3_IceTrainerText, MSGBOX_DEFAULT
 release
 end
LavaridgeTown_Part3_IceTrainerLeave::
 msgbox LavaridgeTown_Part3_IceTrainerLeaveText, MSGBOX_DEFAULT
 closemessage
 applymovement LOCALID_PART3_ICE_TRAINER, Common_Movement_WalkInPlaceFasterRight
 waitmovement 0
 removeobject LOCALID_PART3_ICE_TRAINER
 removeobject LOCALID_PART3_SNORUNT
 setflag FLAG_PART3_SNORUNT_TRAINER_LEFT
 release
 end

LavaridgeTown_Part3_IceTrainerText:
	.string "我和雪童子是来挑战亚莎的。\p可这里也太热了吧……我是不是选错地\n方修行了……$"

LavaridgeTown_Part3_IceTrainerLeaveText:
	.string "你已经拿到徽章了？真厉害。\p我还是先去凉快一点的地方训练吧……$"

LavaridgeTown_Part3_FireFan::
 lock
 faceplayer
 checkspecies SPECIES_VULPIX
 goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_Part3_FireFanVulpix
 checkspecies SPECIES_NINETALES
 goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_Part3_FireFanVulpix
 checkspecies SPECIES_TORKOAL
 goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_Part3_FireFanTorkoal
 msgbox LavaridgeTown_Part3_FireFanText, MSGBOX_DEFAULT
 release
 end
LavaridgeTown_Part3_FireFanVulpix::
 msgbox LavaridgeTown_Part3_FireFanVulpixText, MSGBOX_DEFAULT
 release
 end
LavaridgeTown_Part3_FireFanTorkoal::
 msgbox LavaridgeTown_Part3_FireFanTorkoalText, MSGBOX_DEFAULT
 release
 end

LavaridgeTown_Part3_FireFanText:
	.string "这里的火系宝可梦很有活力。\p去热焰小径走走，说不定能遇到合拍\n的伙伴。$"

LavaridgeTown_Part3_FireFanVulpixText:
	.string "九尾的火焰很漂亮，不过可别小看它\n的脾气哦。\p六尾也一样，要好好相处才行！$"

LavaridgeTown_Part3_FireFanTorkoalText:
	.string "煤炭龟慢悠悠的，可它烧起煤炭来很\n有精神。\p看那股热乎乎的烟，就知道它状态不\n错！$"

LavaridgeTown_Part3_FlanneryFan::
 msgbox LavaridgeTown_Part3_FlanneryFanText, MSGBOX_NPC
 end

LavaridgeTown_Part3_FlanneryFanText:
	.string "亚莎小姐很厉害的！\p不过最近好像总是在偷偷练习馆主台\n词……$"
