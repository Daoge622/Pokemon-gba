@ PART 7 generated scripts. Design: docs/story/PART7_DRAFT.md (DESIGN CONFIRMED / DRAFT)
Part7_BagFull::
	msgbox Part7_Text_001, MSGBOX_DEFAULT
	release
	end

Part7_BagFullAll::
	msgbox Part7_Text_002, MSGBOX_DEFAULT
	releaseall
	end

Part7_End::
	release
	end

Part7_EndAll::
	releaseall
	end

Part7_NewMap_OnTransition::
	special Part7_SyncMap
	end

Part7_BirchHint::
	goto_if_set FLAG_TEMP_7, Part7_Return
	goto_if_set FLAG_SYS_GAME_CLEAR, Part7_Return
	setflag FLAG_TEMP_7
	msgbox Part7_Text_003, MSGBOX_DEFAULT
	goto_if_eq VAR_STARTER_MON, 1, Part7_BirchHint_Torchic
	goto_if_eq VAR_STARTER_MON, 2, Part7_BirchHint_Mudkip
	msgbox Part7_Text_004, MSGBOX_DEFAULT
	goto Part7_BirchHint_Others
Part7_BirchHint_Torchic::
	msgbox Part7_Text_005, MSGBOX_DEFAULT
	goto Part7_BirchHint_Others
Part7_BirchHint_Mudkip::
	msgbox Part7_Text_006, MSGBOX_DEFAULT
Part7_BirchHint_Others::
	msgbox Part7_Text_007, MSGBOX_DEFAULT
	return

Part7_Return::
	return

Part7_Forest0::
	trainerbattle_single TRAINER_PART7_FOREST_RANGER, Part7_Text_008, Part7_Text_009
	msgbox Part7_Text_010, MSGBOX_AUTOCLOSE
	end

Part7_Forest1::
	trainerbattle_single TRAINER_PART7_FOREST_COOLTRAINER, Part7_Text_011, Part7_Text_012
	msgbox Part7_Text_013, MSGBOX_AUTOCLOSE
	end

Part7_Forest2::
	trainerbattle_single TRAINER_PART7_FOREST_BUG_MANIAC, Part7_Text_014, Part7_Text_015
	msgbox Part7_Text_016, MSGBOX_AUTOCLOSE
	end

Part7_SceptileMaster::
	lock
	faceplayer
	goto_if_set FLAG_PART7_SCEPTILITE_DONE, Part7_SceptileMaster_Done
	msgbox Part7_Text_017, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART7_SCEPTILE_MASTER, Part7_Text_018
	msgbox Part7_Text_019, MSGBOX_DEFAULT
	goto Part7_SceptileReward
Part7_SceptileMaster_Done::
	msgbox Part7_Text_020, MSGBOX_DEFAULT
	release
	end

Part7_SceptileReward::
	setvar VAR_0x8004, ITEM_SCEPTILITE
	special Part7_CheckItemOwned
	goto_if_eq VAR_RESULT, TRUE, Part7_SceptileReward_Alt
	checkitemspace ITEM_SCEPTILITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_SCEPTILITE, 1
	setflag FLAG_PART7_SCEPTILITE_DONE
	release
	end

Part7_SceptileReward_Alt::
	msgbox Part7_Text_021, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_UP, 1
	giveitem ITEM_RARE_CANDY, 1
	setflag FLAG_PART7_SCEPTILITE_DONE
	release
	end

Part7_JaggedTrainee::
	msgbox Part7_Text_022, MSGBOX_NPC
	end

Part7_BlazikenElder::
	lock
	faceplayer
	goto_if_set FLAG_PART7_BLAZIKENITE_DONE, Part7_BlazikenElder_Done
	msgbox Part7_Text_023, MSGBOX_DEFAULT
	msgbox Part7_Text_024, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part7_BlazikenElder_Later
	msgbox Part7_Text_025, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART7_JAGGED_FIGHTER, Part7_Text_026
	msgbox Part7_Text_027, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART7_JAGGED_KINDLER, Part7_Text_028
	msgbox Part7_Text_029, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART7_BLAZIKEN_ELDER, Part7_Text_030
	msgbox Part7_Text_031, MSGBOX_DEFAULT
	goto Part7_BlazikenReward
Part7_BlazikenElder_Later::
	msgbox Part7_Text_032, MSGBOX_DEFAULT
	release
	end
Part7_BlazikenElder_Done::
	msgbox Part7_Text_033, MSGBOX_DEFAULT
	release
	end

Part7_BlazikenReward::
	setvar VAR_0x8004, ITEM_BLAZIKENITE
	special Part7_CheckItemOwned
	goto_if_eq VAR_RESULT, TRUE, Part7_BlazikenReward_Alt
	checkitemspace ITEM_BLAZIKENITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_BLAZIKENITE, 1
	setflag FLAG_PART7_BLAZIKENITE_DONE
	release
	end

Part7_BlazikenReward_Alt::
	msgbox Part7_Text_034, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_UP, 1
	setflag FLAG_PART7_BLAZIKENITE_DONE
	release
	end

Part7_FlanneryTrainee::
	goto_if_set FLAG_PART7_BLAZIKENITE_DONE, Part7_FlanneryTrainee_0
	msgbox Part7_Text_036, MSGBOX_NPC
	end

Part7_FlanneryTrainee_0::
	msgbox Part7_Text_035, MSGBOX_NPC
	end

Part7_SwampertDiver::
	lock
	faceplayer
	goto_if_set FLAG_PART7_SWAMPERTITE_DONE, Part7_SwampertDiver_Done
	msgbox Part7_Text_037, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART7_SWAMPERT_DIVER, Part7_Text_038
	msgbox Part7_Text_039, MSGBOX_DEFAULT
	goto Part7_SwampertReward
Part7_SwampertDiver_Done::
	msgbox Part7_Text_040, MSGBOX_DEFAULT
	release
	end

Part7_SwampertReward::
	setvar VAR_0x8004, ITEM_SWAMPERTITE
	special Part7_CheckItemOwned
	goto_if_eq VAR_RESULT, TRUE, Part7_SwampertReward_Alt
	checkitemspace ITEM_SWAMPERTITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_SWAMPERTITE, 1
	setflag FLAG_PART7_SWAMPERTITE_DONE
	release
	end

Part7_SwampertReward_Alt::
	msgbox Part7_Text_041, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_UP, 1
	setflag FLAG_PART7_SWAMPERTITE_DONE
	release
	end

Part7_DeepStrataEntrance::
	lockall
	goto_if_unset FLAG_BADGE08_GET, Part7_DeepStrata_Closed
	msgbox Part7_Text_042, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part7_EndAll
	warp MAP_METEOR_FALLS_DEEP_STRATA, 10, 28
	waitstate
	releaseall
	end
Part7_DeepStrata_Closed::
	msgbox Part7_Text_043, MSGBOX_DEFAULT
	releaseall
	end

Part7_DragonNestEntrance::
	lockall
	msgbox Part7_Text_044, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part7_EndAll
	warp MAP_METEOR_FALLS_DRAGON_NEST, 10, 28
	waitstate
	releaseall
	end

Part7_MeteorResearcher::
	lock
	faceplayer
	goto_if_set FLAG_PART7_METEOR_STAGE2, Part7_MeteorResearcher_Done
	goto_if_set FLAG_PART7_METEOR_STAGE1, Part7_MeteorResearcher_Stage2
	goto_if_set FLAG_PART7_METEOR_ASKED, Part7_MeteorResearcher_Stage1
	msgbox Part7_Text_045, MSGBOX_DEFAULT
	msgbox Part7_Text_046, MSGBOX_DEFAULT
	setflag FLAG_PART7_METEOR_ASKED
	release
	end
Part7_MeteorResearcher_Stage1::
	goto_if_unset FLAG_PART7_METEOR_INV_BURN, Part7_MeteorResearcher_Wait1
	goto_if_unset FLAG_PART7_METEOR_INV_DEBRIS, Part7_MeteorResearcher_Wait1
	goto_if_unset FLAG_PART7_METEOR_INV_POOL, Part7_MeteorResearcher_Wait1
	msgbox Part7_Text_047, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_STAR_PIECE, 2
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_UP, 1
	giveitem ITEM_STAR_PIECE, 2
	setflag FLAG_PART7_METEOR_STAGE1
	msgbox Part7_Text_048, MSGBOX_DEFAULT
	release
	end
Part7_MeteorResearcher_Wait1::
	msgbox Part7_Text_049, MSGBOX_DEFAULT
	release
	end
Part7_MeteorResearcher_Stage2::
	goto_if_unset FLAG_PART7_METEOR_SHARD_1, Part7_MeteorResearcher_Wait2
	goto_if_unset FLAG_PART7_METEOR_SHARD_2, Part7_MeteorResearcher_Wait2
	goto_if_unset FLAG_PART7_METEOR_SHARD_3, Part7_MeteorResearcher_Wait2
	msgbox Part7_Text_050, MSGBOX_DEFAULT
	checkitemspace ITEM_KANGASKHANITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_NUGGET, 2
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_KANGASKHANITE, 1
	giveitem ITEM_NUGGET, 2
	setflag FLAG_PART7_METEOR_STAGE2
	release
	end
Part7_MeteorResearcher_Wait2::
	msgbox Part7_Text_051, MSGBOX_DEFAULT
	release
	end
Part7_MeteorResearcher_Done::
	msgbox Part7_Text_052, MSGBOX_DEFAULT
	release
	end

Part7_MeteorInv0::
	lockall
	msgbox Part7_Text_053, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART7_METEOR_ASKED, Part7_EndAll
	goto_if_set FLAG_PART7_METEOR_INV_BURN, Part7_EndAll
	msgbox Part7_Text_054, MSGBOX_DEFAULT
	setflag FLAG_PART7_METEOR_INV_BURN
	releaseall
	end

Part7_MeteorInv1::
	lockall
	msgbox Part7_Text_055, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART7_METEOR_ASKED, Part7_EndAll
	goto_if_set FLAG_PART7_METEOR_INV_DEBRIS, Part7_EndAll
	msgbox Part7_Text_056, MSGBOX_DEFAULT
	setflag FLAG_PART7_METEOR_INV_DEBRIS
	releaseall
	end

Part7_MeteorInv2::
	lockall
	msgbox Part7_Text_057, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART7_METEOR_ASKED, Part7_EndAll
	goto_if_set FLAG_PART7_METEOR_INV_POOL, Part7_EndAll
	msgbox Part7_Text_058, MSGBOX_DEFAULT
	setflag FLAG_PART7_METEOR_INV_POOL
	releaseall
	end

Part7_MeteorShard0::
	lockall
	goto_if_set FLAG_PART7_METEOR_SHARD_1, Part7_MeteorShard0_Empty
	goto_if_unset FLAG_PART7_METEOR_STAGE1, Part7_MeteorShard0_Empty
	msgbox Part7_Text_059, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox Part7_Text_060, MSGBOX_DEFAULT
	setflag FLAG_PART7_METEOR_SHARD_1
	releaseall
	end
Part7_MeteorShard0_Empty::
	msgbox Part7_Text_061, MSGBOX_DEFAULT
	releaseall
	end

Part7_MeteorShard1::
	lockall
	goto_if_set FLAG_PART7_METEOR_SHARD_2, Part7_MeteorShard1_Empty
	goto_if_unset FLAG_PART7_METEOR_STAGE1, Part7_MeteorShard1_Empty
	msgbox Part7_Text_062, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox Part7_Text_063, MSGBOX_DEFAULT
	setflag FLAG_PART7_METEOR_SHARD_2
	releaseall
	end
Part7_MeteorShard1_Empty::
	msgbox Part7_Text_064, MSGBOX_DEFAULT
	releaseall
	end

Part7_MeteorShard2::
	lockall
	goto_if_set FLAG_PART7_METEOR_SHARD_3, Part7_MeteorShard2_Empty
	goto_if_unset FLAG_PART7_METEOR_STAGE1, Part7_MeteorShard2_Empty
	msgbox Part7_Text_065, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox Part7_Text_066, MSGBOX_DEFAULT
	setflag FLAG_PART7_METEOR_SHARD_3
	releaseall
	end
Part7_MeteorShard2_Empty::
	msgbox Part7_Text_067, MSGBOX_DEFAULT
	releaseall
	end

Part7_ArcheMarker::
	msgbox Part7_Text_068, MSGBOX_SIGN
	end

Part7_InjuredHiker::
	lock
	faceplayer
	goto_if_set FLAG_PART7_HIKER_DONE, Part7_InjuredHiker_Done
	goto_if_set FLAG_PART7_HIKER_PACK, Part7_InjuredHiker_Return
	msgbox Part7_Text_069, MSGBOX_DEFAULT
	release
	end
Part7_InjuredHiker_Return::
	msgbox Part7_Text_070, MSGBOX_DEFAULT
	checkitemspace ITEM_FULL_RESTORE, 3
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_MAWILITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_FULL_RESTORE, 3
	giveitem ITEM_MAWILITE, 1
	setflag FLAG_PART7_HIKER_DONE
	release
	end
Part7_InjuredHiker_Done::
	msgbox Part7_Text_071, MSGBOX_DEFAULT
	release
	end

Part7_HikerPack::
	lockall
	goto_if_set FLAG_PART7_HIKER_PACK, Part7_HikerPack_Empty
	msgbox Part7_Text_072, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox Part7_Text_073, MSGBOX_DEFAULT
	setflag FLAG_PART7_HIKER_PACK
	releaseall
	end
Part7_HikerPack_Empty::
	msgbox Part7_Text_074, MSGBOX_DEFAULT
	releaseall
	end

Part7_Bagon::
	lock
	faceplayer
	playmoncry SPECIES_BAGON, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part7_Text_075, MSGBOX_DEFAULT
	setwildbattle SPECIES_BAGON, 35, ITEM_NONE
	special Part7_PrepareBagon
	hideobjectat LOCALID_PART7_BAGON, MAP_METEOR_FALLS_DRAGON_NEST
	dowildbattle
	special Part7_FinishBagon
	release
	end

Part7_NestCamp::
	lock
	faceplayer
	msgbox Part7_Text_076, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	fadescreen FADE_FROM_BLACK
	msgbox Part7_Text_077, MSGBOX_DEFAULT
	release
	end

Part7_Meteorite::
	msgbox Part7_Text_078, MSGBOX_SIGN
	end

Part7_NestLook7::
	msgbox Part7_Text_079, MSGBOX_SIGN
	end

Part7_NestLook16::
	msgbox Part7_Text_080, MSGBOX_SIGN
	end

Part7_DragonElder::
	lock
	faceplayer
	goto_if_set FLAG_PART7_SALAMENCITE_DONE, Part7_DragonElder_After
	msgbox Part7_Text_081, MSGBOX_DEFAULT
	msgbox Part7_Text_082, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART7_DRAGON_TRIAL, Part7_Text_083
	msgbox Part7_Text_084, MSGBOX_DEFAULT
	goto Part7_DragonTrialReward
Part7_DragonElder_After::
	goto_if_set FLAG_SYS_GAME_CLEAR, Part7_DragonElder_Rematch
	msgbox Part7_Text_085, MSGBOX_DEFAULT
	release
	end
Part7_DragonElder_Rematch::
	msgbox Part7_Text_086, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part7_DragonElder_No
	trainerbattle_no_intro TRAINER_PART7_DRAGON_TRIAL_REMATCH, Part7_Text_087
	goto_if_set FLAG_PART7_DRAGON_REMATCH_REWARD, Part7_DragonElder_RematchDone
	msgbox Part7_Text_088, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_MAX, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_MAX, 1
	setflag FLAG_PART7_DRAGON_REMATCH_REWARD
Part7_DragonElder_RematchDone::
	msgbox Part7_Text_089, MSGBOX_DEFAULT
	release
	end
Part7_DragonElder_No::
	msgbox Part7_Text_090, MSGBOX_DEFAULT
	release
	end

Part7_DragonTrialReward::
	setvar VAR_0x8004, ITEM_SALAMENCITE
	special Part7_CheckItemOwned
	goto_if_eq VAR_RESULT, TRUE, Part7_DragonTrialReward_Alt
	checkitemspace ITEM_SALAMENCITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_SALAMENCITE, 1
	setflag FLAG_PART7_SALAMENCITE_DONE
	release
	end

Part7_DragonTrialReward_Alt::
	msgbox Part7_Text_091, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_UP, 1
	giveitem ITEM_RARE_CANDY, 1
	setflag FLAG_PART7_SALAMENCITE_DONE
	release
	end

Part7_StevenReward::
	setvar VAR_0x8004, ITEM_METAGROSSITE
	special Part7_CheckItemOwned
	goto_if_eq VAR_RESULT, TRUE, Part7_StevenReward_Alt
	checkitemspace ITEM_METAGROSSITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_METAGROSSITE, 1
	setflag FLAG_PART7_METAGROSSITE_DONE
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

Part7_StevenReward_Alt::
	msgbox Part7_Text_092, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_MAX, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_MAX, 1
	giveitem ITEM_RARE_CANDY, 1
	setflag FLAG_PART7_METAGROSSITE_DONE
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

Part7_132Current::
	msgbox Part7_Text_093, MSGBOX_SIGN
	end

Part7_Drifter::
	trainerbattle_single TRAINER_PART7_DRIFTER, Part7_Text_094, Part7_Text_095
	msgbox Part7_Text_096, MSGBOX_AUTOCLOSE
	end

Part7_Siblings::
	trainerbattle_double TRAINER_PART7_BACKFLOW_SIBLINGS, Part7_Text_097, Part7_Text_098, Part7_Text_099
	msgbox Part7_Text_100, MSGBOX_AUTOCLOSE
	end

Part7_BackflowNuggets::
	lockall
	goto_if_set FLAG_PART7_BACKFLOW_NUGGETS, Part7_BackflowNuggets_Empty
	msgbox Part7_Text_101, MSGBOX_DEFAULT
	giveitem ITEM_NUGGET, 2
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFullAll
	setflag FLAG_PART7_BACKFLOW_NUGGETS
	releaseall
	end
Part7_BackflowNuggets_Empty::
	msgbox Part7_Text_102, MSGBOX_DEFAULT
	releaseall
	end

Part7_TideCaveEntrance::
	lockall
	msgbox Part7_Text_103, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part7_EndAll
	warp MAP_ROUTE133_TIDE_MARK_CAVE, 7, 6
	waitstate
	releaseall
	end

Part7_WaterproofBag::
	lockall
	goto_if_set FLAG_PART7_WATERPROOF_BAG, Part7_WaterproofBag_Empty
	msgbox Part7_Text_104, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox Part7_Text_105, MSGBOX_DEFAULT
	setflag FLAG_PART7_WATERPROOF_BAG
	releaseall
	end
Part7_WaterproofBag_Empty::
	msgbox Part7_Text_106, MSGBOX_DEFAULT
	releaseall
	end

Part7_TideSailor::
	lock
	faceplayer
	goto_if_set FLAG_PART7_SAILOR_DONE, Part7_TideSailor_Done
	goto_if_set FLAG_PART7_WATERPROOF_BAG, Part7_TideSailor_Return
	msgbox Part7_Text_107, MSGBOX_DEFAULT
	release
	end
Part7_TideSailor_Return::
	msgbox Part7_Text_108, MSGBOX_DEFAULT
	checkitemspace ITEM_BIG_PEARL, 2
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_FULL_RESTORE, 2
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_BIG_PEARL, 2
	giveitem ITEM_FULL_RESTORE, 2
	setflag FLAG_PART7_SAILOR_DONE
	release
	end
Part7_TideSailor_Done::
	msgbox Part7_Text_109, MSGBOX_DEFAULT
	release
	end

Part7_TideMarks::
	msgbox Part7_Text_110, MSGBOX_SIGN
	end

Part7_134Calm::
	msgbox Part7_Text_111, MSGBOX_SIGN
	end

Part7_FallsOldTrainer::
	goto_if_set FLAG_SYS_GAME_CLEAR, Part7_FallsOldTrainer_0
	msgbox Part7_Text_113, MSGBOX_NPC
	end

Part7_FallsOldTrainer_0::
	msgbox Part7_Text_112, MSGBOX_NPC
	end

Part7_BadgeStaff::
	lock
	faceplayer
	goto_if_set FLAG_TEMP_9, Part7_BadgeStaff_Again
	setflag FLAG_TEMP_9
	msgbox Part7_Text_114, MSGBOX_DEFAULT
	release
	end
Part7_BadgeStaff_Again::
	msgbox Part7_Text_115, MSGBOX_DEFAULT
	release
	end

Part7_PlatformAce::
	trainerbattle_single TRAINER_PART7_PLATFORM_ACE, Part7_Text_116, Part7_Text_117
	msgbox Part7_Text_118, MSGBOX_AUTOCLOSE
	end

Part7_Postman::
	lock
	faceplayer
	goto_if_set FLAG_PART7_POSTMAN_DONE, Part7_Postman_Done
	goto_if_set FLAG_PART7_POSTMAN_FIRST_AID, Part7_Postman_Return
	msgbox Part7_Text_119, MSGBOX_DEFAULT
	setflag FLAG_PART7_POSTMAN_ASKED
	release
	end
Part7_Postman_Return::
	msgbox Part7_Text_120, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_ULTRA_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_UP, 1
	giveitem ITEM_ULTRA_BALL, 5
	setflag FLAG_PART7_POSTMAN_DONE
	release
	end
Part7_Postman_Done::
	msgbox Part7_Text_121, MSGBOX_DEFAULT
	release
	end

Part7_PostWingull::
	lock
	faceplayer
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part7_PcAide::
	lock
	faceplayer
	goto_if_set FLAG_PART7_POSTMAN_FIRST_AID, Part7_PcAide_Plain
	goto_if_unset FLAG_PART7_POSTMAN_ASKED, Part7_PcAide_Plain
	msgbox Part7_Text_122, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox Part7_Text_123, MSGBOX_DEFAULT
	setflag FLAG_PART7_POSTMAN_FIRST_AID
	release
	end
Part7_PcAide_Plain::
	msgbox Part7_Text_124, MSGBOX_DEFAULT
	release
	end

Part7_MessageBoard::
	lockall
	msgbox Part7_Text_125, MSGBOX_DEFAULT
	msgbox Part7_Text_126, MSGBOX_DEFAULT
	msgbox Part7_Text_127, MSGBOX_DEFAULT
	msgbox Part7_Text_128, MSGBOX_DEFAULT
	goto_if_unset FLAG_SYS_GAME_CLEAR, Part7_EndAll
	msgbox Part7_Text_129, MSGBOX_DEFAULT
	releaseall
	end

Part7_WrongMap::
	lock
	faceplayer
	goto_if_set FLAG_PART7_MAP_DONE, Part7_WrongMap_Done
	goto_if_set FLAG_PART7_MAP_FOUND, Part7_WrongMap_Return
	msgbox Part7_Text_130, MSGBOX_DEFAULT
	setflag FLAG_PART7_MAP_ASKED
	release
	end
Part7_WrongMap_Return::
	msgbox Part7_Text_131, MSGBOX_DEFAULT
	checkitemspace ITEM_GYARADOSITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_FULL_RESTORE, 2
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_GYARADOSITE, 1
	giveitem ITEM_FULL_RESTORE, 2
	setflag FLAG_PART7_MAP_DONE
	release
	end
Part7_WrongMap_Done::
	msgbox Part7_Text_132, MSGBOX_DEFAULT
	release
	end

Part7_Brother::
	lock
	faceplayer
	goto_if_set FLAG_PART7_SISTER_DONE, Part7_Brother_Done
	goto_if_set FLAG_PART7_SISTER_BRACE, Part7_Brother_Return
	msgbox Part7_Text_133, MSGBOX_DEFAULT
	release
	end
Part7_Brother_Return::
	msgbox Part7_Text_134, MSGBOX_DEFAULT
	checkitemspace ITEM_FOCUS_SASH, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_FULL_RESTORE, 3
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_FOCUS_SASH, 1
	giveitem ITEM_FULL_RESTORE, 3
	setflag FLAG_PART7_SISTER_DONE
	release
	end
Part7_Brother_Done::
	msgbox Part7_Text_135, MSGBOX_DEFAULT
	release
	end

Part7_SisterPc::
	msgbox Part7_Text_136, MSGBOX_NPC
	end

Part7_PcLoser::
	goto_if_set FLAG_SYS_GAME_CLEAR, Part7_PcLoser_0
	msgbox Part7_Text_138, MSGBOX_NPC
	end

Part7_PcLoser_0::
	msgbox Part7_Text_137, MSGBOX_NPC
	end

Part7_Veteran::
	msgbox Part7_Text_139, MSGBOX_NPC
	end

Part7_Parent::
	msgbox Part7_Text_140, MSGBOX_NPC
	end

Part7_VrTrace0::
	msgbox Part7_Text_141, MSGBOX_SIGN
	end

Part7_VrTrace1::
	msgbox Part7_Text_142, MSGBOX_SIGN
	end

Part7_VrTrace2::
	msgbox Part7_Text_143, MSGBOX_SIGN
	end

Part7_VrSignpost::
	lockall
	msgbox Part7_Text_144, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART7_MAP_ASKED, Part7_EndAll
	goto_if_set FLAG_PART7_MAP_FOUND, Part7_EndAll
	msgbox Part7_Text_145, MSGBOX_DEFAULT
	setflag FLAG_PART7_MAP_FOUND
	releaseall
	end

Part7_Riolu::
	lock
	faceplayer
	playmoncry SPECIES_RIOLU, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part7_Text_146, MSGBOX_DEFAULT
	setwildbattle SPECIES_RIOLU, 38, ITEM_NONE
	setvar VAR_0x8005, FLAG_PART7_RIOLU_CAUGHT
	hideobjectat LOCALID_PART7_RIOLU, MAP_VICTORY_ROAD_B2F
	dowildbattle
	setvar VAR_0x8005, FLAG_PART7_RIOLU_CAUGHT
	special Part7_SetFlagIfCaught
	release
	end

Part7_VrCamp::
	lock
	faceplayer
	msgbox Part7_Text_147, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	fadescreen FADE_FROM_BLACK
	msgbox Part7_Text_148, MSGBOX_DEFAULT
	release
	end

Part7_VrCampShop::
	lock
	faceplayer
	message Part7_Text_149
	waitmessage
	pokemart Part7_VrCampShop_Items
	msgbox Part7_Text_150, MSGBOX_DEFAULT
	release
	end

	.align 2
Part7_VrCampShop_Items:
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	pokemartlistend

Part7_VrSister::
	lock
	faceplayer
	goto_if_set FLAG_PART7_SISTER_BRACE, Part7_EndLock
	msgbox Part7_Text_151, MSGBOX_DEFAULT
	msgbox Part7_Text_152, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox Part7_Text_153, MSGBOX_DEFAULT
	setflag FLAG_PART7_SISTER_BRACE
	release
	end
Part7_EndLock::
	release
	end

Part7_VrBug::
	trainerbattle_single TRAINER_PART7_VR_BUG_MANIAC, Part7_Text_154, Part7_Text_155
	msgbox Part7_Text_156, MSGBOX_AUTOCLOSE
	end

Part7_LucarioMaster::
	lock
	faceplayer
	goto_if_set FLAG_PART7_LUCARIONITE_DONE, Part7_LucarioMaster_Done
	msgbox Part7_Text_157, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part7_LucarioMaster_No
	trainerbattle_no_intro TRAINER_PART7_LUCARIO_MASTER, Part7_Text_158
	msgbox Part7_Text_159, MSGBOX_DEFAULT
	goto Part7_LucarioReward
Part7_LucarioMaster_No::
	msgbox Part7_Text_160, MSGBOX_DEFAULT
	release
	end
Part7_LucarioMaster_Done::
	msgbox Part7_Text_161, MSGBOX_DEFAULT
	release
	end

Part7_LucarioReward::
	setvar VAR_0x8004, ITEM_LUCARIONITE
	special Part7_CheckItemOwned
	goto_if_eq VAR_RESULT, TRUE, Part7_LucarioReward_Alt
	checkitemspace ITEM_LUCARIONITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_LUCARIONITE, 1
	setflag FLAG_PART7_LUCARIONITE_DONE
	release
	end

Part7_LucarioReward_Alt::
	msgbox Part7_Text_162, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_UP, 1
	giveitem ITEM_RARE_CANDY, 1
	setflag FLAG_PART7_LUCARIONITE_DONE
	release
	end

Part7_GarchompAce::
	lock
	faceplayer
	goto_if_set FLAG_PART7_GARCHOMPITE_DONE, Part7_GarchompAce_Done
	goto_if_set FLAG_SYS_GAME_CLEAR, Part7_GarchompAce_Battle
	msgbox Part7_Text_163, MSGBOX_DEFAULT
	release
	end
Part7_GarchompAce_Battle::
	msgbox Part7_Text_164, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PART7_GARCHOMP_ACE, Part7_Text_165
	msgbox Part7_Text_166, MSGBOX_DEFAULT
	goto Part7_GarchompReward
Part7_GarchompAce_Done::
	msgbox Part7_Text_167, MSGBOX_DEFAULT
	release
	end

Part7_GarchompReward::
	setvar VAR_0x8004, ITEM_GARCHOMPITE
	special Part7_CheckItemOwned
	goto_if_eq VAR_RESULT, TRUE, Part7_GarchompReward_Alt
	checkitemspace ITEM_GARCHOMPITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_GARCHOMPITE, 1
	setflag FLAG_PART7_GARCHOMPITE_DONE
	release
	end

Part7_GarchompReward_Alt::
	msgbox Part7_Text_168, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_MAX, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_MAX, 1
	giveitem ITEM_RARE_CANDY, 1
	setflag FLAG_PART7_GARCHOMPITE_DONE
	release
	end

Part7_LeagueStaff::
	lock
	faceplayer
	goto_if_set FLAG_PART7_STRONG_LEAGUE_CLEARED, Part7_LeagueStaff_Strong
	goto_if_set FLAG_PART7_LEAGUE_SUPPLY, Part7_LeagueStaff_Plain
	msgbox Part7_Text_170, MSGBOX_DEFAULT
	checkitemspace ITEM_FULL_RESTORE, 5
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_REVIVE, 3
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_FULL_RESTORE, 5
	giveitem ITEM_REVIVE, 3
	setflag FLAG_PART7_LEAGUE_SUPPLY
	msgbox Part7_Text_171, MSGBOX_DEFAULT
	release
	end
Part7_LeagueStaff_Strong::
	goto_if_set FLAG_PART7_STRONG_LEAGUE_PRIZE, Part7_LeagueStaff_Plain
	msgbox Part7_Text_172, MSGBOX_DEFAULT
	checkitemspace ITEM_ABILITY_PATCH, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	checkitemspace ITEM_PP_MAX, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_ABILITY_PATCH, 1
	giveitem ITEM_PP_MAX, 1
	addmoney 50000
	playse SE_SHOP
	msgbox Part7_Text_173, MSGBOX_DEFAULT
	setflag FLAG_PART7_STRONG_LEAGUE_PRIZE
	release
	end
Part7_LeagueStaff_Plain::
	goto_if_set FLAG_SYS_GAME_CLEAR, Part7_LeagueStaff_Champion
	msgbox Part7_Text_174, MSGBOX_DEFAULT
	release
	end
Part7_LeagueStaff_Champion::
	msgbox Part7_Text_175, MSGBOX_DEFAULT
	release
	end

Part7_AdjusterLeague::
	msgbox Part7_Text_176, MSGBOX_DEFAULT
	releaseall
	end

Part7_StrongSidney::
	trainerbattle_no_intro TRAINER_PART7_SIDNEY_STRONG, EverGrandeCity_SidneysRoom_Text_Defeat
	goto Part7_AfterSidney

Part7_StrongPhoebe::
	trainerbattle_no_intro TRAINER_PART7_PHOEBE_STRONG, EverGrandeCity_PhoebesRoom_Text_Defeat
	goto Part7_AfterPhoebe

Part7_StrongGlacia::
	trainerbattle_no_intro TRAINER_PART7_GLACIA_STRONG, EverGrandeCity_GlaciasRoom_Text_Defeat
	goto Part7_AfterGlacia

Part7_StrongDrake::
	trainerbattle_no_intro TRAINER_PART7_DRAKE_STRONG, EverGrandeCity_DrakesRoom_Text_Defeat
	goto Part7_AfterDrake

Part7_StrongWallace::
	trainerbattle_no_intro TRAINER_PART7_WALLACE_STRONG, EverGrandeCity_ChampionsRoom_Text_Defeat
	setflag FLAG_PART7_STRONG_LEAGUE_CLEARED
	goto Part7_AfterWallace

Part7_LatiGirl::
	lock
	faceplayer
	goto_if_set FLAG_PART7_LATI_REUNION, Part7_LatiGirl_Free
	msgbox Part7_Text_177, MSGBOX_DEFAULT
	goto_if_ne VAR_ROAMER_POKEMON, 0, Part7_LatiGirl_Blue
	msgbox Part7_Text_178, MSGBOX_DEFAULT
	goto Part7_LatiGirl_Trail
Part7_LatiGirl_Blue::
	msgbox Part7_Text_179, MSGBOX_DEFAULT
Part7_LatiGirl_Trail::
	msgbox Part7_Text_180, MSGBOX_DEFAULT
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part7_Text_181, MSGBOX_DEFAULT
	setflag FLAG_PART7_LATI_MET
	release
	end
Part7_LatiGirl_Free::
	msgbox Part7_Text_182, MSGBOX_DEFAULT
	release
	end

Part7_LatiJiggly::
	lock
	faceplayer
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part7_119Lati::
	lockall
	goto_if_ne VAR_ROAMER_POKEMON, 0, Part7_119Latios
	playmoncry SPECIES_LATIAS, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_PART7_119_LATIAS, Part7_Movement_LatiFlyAway
	waitmovement 0
	removeobject LOCALID_PART7_119_LATIAS
	goto Part7_119Girl
Part7_119Latios::
	playmoncry SPECIES_LATIOS, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_PART7_119_LATIOS, Part7_Movement_LatiFlyAway
	waitmovement 0
	removeobject LOCALID_PART7_119_LATIOS
Part7_119Girl::
	msgbox Part7_Text_183, MSGBOX_DEFAULT
	clearflag FLAG_TEMP_B
	addobject LOCALID_PART7_119_GIRL
	addobject LOCALID_PART7_119_JIGGLY
	msgbox Part7_Text_184, MSGBOX_DEFAULT
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part7_Text_185, MSGBOX_DEFAULT
	msgbox Part7_Text_186, MSGBOX_DEFAULT
	giveitem ITEM_EON_TICKET, 1
	setflag FLAG_ENABLE_SHIP_SOUTHERN_ISLAND
	setflag FLAG_PART7_LATI_119_DONE
	msgbox Part7_Text_187, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PART7_119_GIRL
	removeobject LOCALID_PART7_119_JIGGLY
	fadescreen FADE_FROM_BLACK
	releaseall
	end

Part7_Movement_LatiFlyAway:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	set_invisible
	step_end

Part7_IslandGfx::
	goto_if_ne VAR_ROAMER_POKEMON, 0, Part7_IslandGfx_Blue
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_LATIOS
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_LATIAS
	return
Part7_IslandGfx_Blue::
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_LATIAS
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_LATIOS
	return

Part7_IslandGirl::
	msgbox Part7_Text_188, MSGBOX_NPC
	end

Part7_IslandLati::
	lock
	goto_if_set FLAG_PART7_LATI_REUNION, Part7_IslandLati_Battle
	msgbox Part7_Text_189, MSGBOX_DEFAULT
	msgbox Part7_Text_190, MSGBOX_DEFAULT
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part7_Text_191, MSGBOX_DEFAULT
	call Part7_IslandCryIsland
	delay 30
	msgbox Part7_Text_192, MSGBOX_DEFAULT
	call Part7_IslandCryChased
	clearflag FLAG_TEMP_8
	addobject LOCALID_PART7_CHASED_LATI
	applymovement LOCALID_PART7_CHASED_LATI, Part7_Movement_LatiLand
	waitmovement 0
	call Part7_IslandCryIsland
	call Part7_IslandCryChased
	msgbox Part7_Text_193, MSGBOX_DEFAULT
	setflag FLAG_PART7_LATI_REUNION
	msgbox Part7_Text_194, MSGBOX_DEFAULT
	msgbox Part7_Text_195, MSGBOX_DEFAULT
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part7_Text_196, MSGBOX_DEFAULT
	msgbox Part7_Text_197, MSGBOX_DEFAULT
	release
	end

Part7_Movement_LatiLand:
	walk_down
	walk_down
	walk_down
	step_end

Part7_IslandCryIsland::
	goto_if_ne VAR_ROAMER_POKEMON, 0, Part7_IslandCryIsland_Latias
	playmoncry SPECIES_LATIOS, CRY_MODE_NORMAL
	waitmoncry
	return
Part7_IslandCryIsland_Latias::
	playmoncry SPECIES_LATIAS, CRY_MODE_NORMAL
	waitmoncry
	return
Part7_IslandCryChased::
	goto_if_ne VAR_ROAMER_POKEMON, 0, Part7_IslandCryChased_Latios
	playmoncry SPECIES_LATIAS, CRY_MODE_NORMAL
	waitmoncry
	return
Part7_IslandCryChased_Latios::
	playmoncry SPECIES_LATIOS, CRY_MODE_NORMAL
	waitmoncry
	return

Part7_IslandLati_Battle::
	goto_if_ne VAR_ROAMER_POKEMON, 0, Part7_IslandLati_Latias
	setvar VAR_0x8006, LOCALID_PART7_ISLAND_LATI
	goto Part7_LatiosBattle
Part7_IslandLati_Latias::
	setvar VAR_0x8006, LOCALID_PART7_ISLAND_LATI
	goto Part7_LatiasBattle

Part7_ChasedLati::
	lock
	goto_if_ne VAR_ROAMER_POKEMON, 0, Part7_ChasedLati_Latios
	setvar VAR_0x8006, LOCALID_PART7_CHASED_LATI
	goto Part7_LatiasBattle
Part7_ChasedLati_Latios::
	setvar VAR_0x8006, LOCALID_PART7_CHASED_LATI
	goto Part7_LatiosBattle

Part7_LatiasBattle::
	playmoncry SPECIES_LATIAS, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_LATIAS, 50
	setvar VAR_0x8005, FLAG_PART7_LATIAS_CAUGHT
	goto Part7_LatiBattle
Part7_LatiosBattle::
	playmoncry SPECIES_LATIOS, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_LATIOS, 50
	setvar VAR_0x8005, FLAG_PART7_LATIOS_CAUGHT
Part7_LatiBattle::
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLatiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	special Part7_SetFlagIfCaught
	removeobject VAR_0x8006
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Part7_EndLock
	msgbox Part7_Text_198, MSGBOX_DEFAULT
	release
	end

Part7_IslandStone::
	lockall
	goto_if_set FLAG_PART7_SOUL_DEW, Part7_IslandStone_Plain
	goto_if_unset FLAG_PART7_LATIAS_CAUGHT, Part7_IslandStone_Plain
	goto_if_unset FLAG_PART7_LATIOS_CAUGHT, Part7_IslandStone_Plain
	msgbox Part7_Text_199, MSGBOX_DEFAULT
	giveitem ITEM_SOUL_DEW, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFullAll
	setflag FLAG_PART7_SOUL_DEW
	releaseall
	end
Part7_IslandStone_Plain::
	msgbox SouthernIsland_Interior_Text_Sign, MSGBOX_DEFAULT
	releaseall
	end

Part7_LabRecords::
	lockall
	msgbox Part7_Text_200, MSGBOX_DEFAULT
	goto_if_unset FLAG_SYS_GAME_CLEAR, Part7_LabRecords_None
	call_if_unset FLAG_DEFEATED_GROUDON, Part7_LabRecords_Weather
	call_if_unset FLAG_DEFEATED_METEOR_FALLS_STEVEN, Part7_LabRecords_Meteor
	call_if_unset FLAG_PART7_LATI_REUNION, Part7_LabRecords_Slateport
	call_if_unset FLAG_LANDMARK_BATTLE_FRONTIER, Part7_LabRecords_Ship
	call_if_unset FLAG_LANDMARK_DESERT_UNDERPASS, Part7_LabRecords_Desert
	msgbox Part7_Text_201, MSGBOX_DEFAULT
	releaseall
	end
Part7_LabRecords_None::
	msgbox Part7_Text_202, MSGBOX_DEFAULT
	releaseall
	end
Part7_LabRecords_Weather::
	msgbox Part7_Text_203, MSGBOX_DEFAULT
	return
Part7_LabRecords_Meteor::
	msgbox Part7_Text_204, MSGBOX_DEFAULT
	return
Part7_LabRecords_Slateport::
	msgbox Part7_Text_205, MSGBOX_DEFAULT
	return
Part7_LabRecords_Ship::
	msgbox Part7_Text_206, MSGBOX_DEFAULT
	return
Part7_LabRecords_Desert::
	msgbox Part7_Text_207, MSGBOX_DEFAULT
	return

Part7_MomChampion::
	goto_if_set FLAG_PART7_MOM_CHAMPION_GIFT, Part7_Return
	msgbox Part7_Text_208, MSGBOX_DEFAULT
	delay 30
	msgbox Part7_Text_209, MSGBOX_DEFAULT
	msgbox Part7_Text_210, MSGBOX_DEFAULT
	checkitemspace ITEM_FULL_RESTORE, 5
	goto_if_eq VAR_RESULT, FALSE, Part7_Return
	giveitem ITEM_FULL_RESTORE, 5
	setflag FLAG_PART7_MOM_CHAMPION_GIFT
	return

Part7_NormanChampion::
	goto_if_set FLAG_TEMP_7, Part7_Return
	setflag FLAG_TEMP_7
	msgbox Part7_Text_211, MSGBOX_DEFAULT
	return

Part7_CoupleChampion::
	msgbox Part7_Text_212, MSGBOX_DEFAULT
	msgbox Part7_Text_213, MSGBOX_DEFAULT
	msgbox Part7_Text_214, MSGBOX_DEFAULT
	release
	end

Part7_HqChampion::
	goto_if_set FLAG_DEFEATED_GROUDON, Part7_HqSignal
	goto_if_set FLAG_DEFEATED_KYOGRE, Part7_HqSignal
	msgbox Part7_Text_215, MSGBOX_NPC
	end
Part7_HqSignal::
	msgbox Part7_Text_216, MSGBOX_NPC
	end

Part7_SavielChampion::
	msgbox Part7_Text_217, MSGBOX_DEFAULT
	msgbox Part7_Text_218, MSGBOX_DEFAULT
	msgbox Part7_Text_219, MSGBOX_DEFAULT
	release
	end

Part7_FisherRematch::
	msgbox Part7_Text_220, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part7_FisherRematch_No
	trainerbattle_no_intro TRAINER_PART7_FISHER_REMATCH, Part7_Text_221
	goto_if_set FLAG_PART7_FISHER_REMATCH_REWARD, Part7_FisherRematch_Done
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part7_BagFull
	giveitem ITEM_PP_UP, 1
	setflag FLAG_PART7_FISHER_REMATCH_REWARD
Part7_FisherRematch_Done::
	msgbox Part7_Text_222, MSGBOX_DEFAULT
	release
	end
Part7_FisherRematch_No::
	msgbox Part7_Text_223, MSGBOX_DEFAULT
	release
	end

Part7_BpClerk::
	lock
	faceplayer
	msgbox Part7_Text_241, MSGBOX_DEFAULT
Part7_BpClerk_Menu::
	message Part7_Text_242
	waitmessage
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, Part7_Text_224, Part7_Text_225, Part7_Text_226, Part7_Text_227, Part7_Text_228, Part7_Text_229, Part7_Text_230, Part7_Text_231, Part7_Text_232, Part7_Text_233, Part7_Text_234, Part7_Text_235, Part7_Text_236, Part7_Text_237, Part7_Text_238, Part7_Text_239, Part7_Text_240
	goto_if_ge VAR_RESULT, 16, Part7_BpClerk_Bye
	copyvar VAR_0x8004, VAR_RESULT
	special Part7_BuyBpItem
	goto_if_eq VAR_RESULT, 1, Part7_BpClerk_NoBp
	goto_if_eq VAR_RESULT, 2, Part7_BpClerk_Full
	playse SE_SHOP
	msgbox Part7_Text_243, MSGBOX_DEFAULT
	goto Part7_BpClerk_Menu
Part7_BpClerk_NoBp::
	msgbox Part7_Text_244, MSGBOX_DEFAULT
	goto Part7_BpClerk_Menu
Part7_BpClerk_Full::
	msgbox Part7_Text_245, MSGBOX_DEFAULT
	goto Part7_BpClerk_Menu
Part7_BpClerk_Bye::
	msgbox Part7_Text_246, MSGBOX_DEFAULT
	release
	end

Part7_Text_001:
	.string "背包已经满了。整理一下再来吧。$"

Part7_Text_002:
	.string "背包已经满了。整理一下再来吧。$"

Part7_Text_003:
	.string "八枚徽章了啊……\p对了，最近有几条关于丰缘御三家的消\n息。$"

Part7_Text_004:
	.string "有人在119号道路高处的林子里，\p见过一只会超级进化的蜥蜴王。\p天气研究所附近的瀑布上面，\p据说有一片很少有人去的林间平台。$"

Part7_Text_005:
	.string "釜炎镇那边的老训练家，\p在凸凹山道的高处组织连续对战。\p最后出场的，好像是一只火焰鸡。\p亚莎可应该知道得更清楚。$"

Part7_Text_006:
	.string "127、128号海域有一位潜水好手，\p在海上的小平台等挑战者。\p听说她的巨沼怪能超级进化。$"

Part7_Text_007:
	.string "另外两种御三家的石头，\p当地人应该也知道一些线索。\p多问问吧。$"

Part7_Text_008:
	.string "这片林子不在地图上。\p能找到这里，\p说明你的宝可梦也有两下子。$"

Part7_Text_009:
	.string "……林子比我想的还要深。$"

Part7_Text_010:
	.string "前面的老手在林子最里面。\p他的蜥蜴王，可不是普通的蜥蜴王。$"

Part7_Text_011:
	.string "树冠上面的风很大。\p站稳了吗？$"

Part7_Text_012:
	.string "站不稳的是我。$"

Part7_Text_013:
	.string "再往里走，就是老手的地盘了。$"

Part7_Text_014:
	.string "这里的虫系宝可梦都长得特别好。\p来比比看！$"

Part7_Text_015:
	.string "被看穿了……$"

Part7_Text_016:
	.string "林子深处很安静。\p老手一般不说话，直接对战。$"

Part7_Text_017:
	.string "……八枚徽章。\p这片林子，是我和它一起长大的地方。\p让我看看你走到这里的本事。$"

Part7_Text_018:
	.string "……好。\p林子认你了。$"

Part7_Text_019:
	.string "这块石头，本来就该交给\p能走到这里的人。$"

Part7_Text_020:
	.string "风停了。\p林子里难得这么安静。$"

Part7_Text_021:
	.string "看来这块石头你已经有了。\p那就换成别的东西吧。$"

Part7_Text_022:
	.string "要挑战的话，先去跟老师傅说。\p我们三个，是连着上的。$"

Part7_Text_023:
	.string "是亚莎可让你来的吧？\p这里是山道上面的训练场。\p规矩只有一条：三场连战，中途不休\n息。$"

Part7_Text_024:
	.string "准备好了吗？$"

Part7_Text_025:
	.string "格斗家：第一场，我来！$"

Part7_Text_026:
	.string "格斗家：拳头还不够硬……$"

Part7_Text_027:
	.string "火系训练家：第二场。\p山上的火，可比山下的烫。$"

Part7_Text_028:
	.string "火系训练家：……被扑灭了。$"

Part7_Text_029:
	.string "老训练家：不错。\p最后一场，我和我的老搭档来。$"

Part7_Text_030:
	.string "……哈哈！\p好久没打得这么痛快了！$"

Part7_Text_031:
	.string "这块石头放在我这里，\p也只是让它陪我晒太阳。\p你拿去吧。$"

Part7_Text_032:
	.string "想好了再来。\p山不会跑。$"

Part7_Text_033:
	.string "年轻真好啊。\p下次带着更强的队伍来玩。$"

Part7_Text_034:
	.string "看来这块石头你已经有了。\p那就换成别的东西吧。$"

Part7_Text_035:
	.string "听说你打赢了山道上的老师傅？\p亚莎可馆主说，\p她早就猜到会是这样。$"

Part7_Text_036:
	.string "亚莎可馆主让我转告你：\p凸凹山道高处有一位老训练家，\p他的火焰鸡会超级进化。\p往山道上面走，就能看到训练场。$"

Part7_Text_037:
	.string "从海沟那边顺着海流上来的？\p能找到这个平台的人不多。\p我的巨沼怪等你很久了。$"

Part7_Text_038:
	.string "……海流站在你那边。$"

Part7_Text_039:
	.string "这块石头是我在海底捡到的。\p比起放在我包里，\p它更适合跟着你。$"

Part7_Text_040:
	.string "今天的海很平。\p适合潜水。$"

Part7_Text_041:
	.string "看来这块石头你已经有了。\p那就换成别的东西吧。$"

Part7_Text_042:
	.string "岩壁后面有一条向下的侧路。\p冷风从深处吹上来。\p要进去看看吗？$"

Part7_Text_043:
	.string "岩壁上有一道裂缝。\p落石堵住了，现在过不去。$"

Part7_Text_044:
	.string "岩台尽头有一个更深的洞口。\p里面传来低沉的叫声。\p要进去吗？$"

Part7_Text_045:
	.string "哦，有人来了。\p我在这里研究流星瀑布的岩层，\p已经很多年了。$"

Part7_Text_046:
	.string "年纪大了，腿脚不太方便。\p能帮我看看三个地方吗？\p烧过的岩层、陨石碎屑，\p还有深处的地下水洼。$"

Part7_Text_047:
	.string "三处都看过了？\p……果然。\p这一层的岩石，确实被高温熔过。$"

Part7_Text_048:
	.string "对了。\p这一带还散落着几块完整的陨星碎片。\p不是随便掉的碎屑，是完整的。\p找到三块的话，拿来给我看看。$"

Part7_Text_049:
	.string "烧过的岩层、陨石碎屑、地下水洼。\p三个地方都在这一层。$"

Part7_Text_050:
	.string "三块都在……\p表面这么完整，真难得。\p这些就当作谢礼吧。$"

Part7_Text_051:
	.string "完整的陨星碎片，一共三块。\p它们在岩缝里会微微反光。$"

Part7_Text_052:
	.string "前阵子也有人来过。\p问了不少问题。\p很快就走了。$"

Part7_Text_053:
	.string "这一面的岩石像是被高温熔过。\p表面又黑又亮。$"

Part7_Text_054:
	.string "把看到的情况记下来了。$"

Part7_Text_055:
	.string "岩层里夹着细小的黑色碎片。\p是陨石的碎屑。$"

Part7_Text_056:
	.string "把看到的情况记下来了。$"

Part7_Text_057:
	.string "岩缝里渗出地下水，积成一小片水洼。\p水底沉着几块发黑的石头。$"

Part7_Text_058:
	.string "把看到的情况记下来了。$"

Part7_Text_059:
	.string "岩缝里有一块微微反光的碎片。$"

Part7_Text_060:
	.string "找到了一块完整的陨星碎片！$"

Part7_Text_061:
	.string "岩缝里只剩下细小的碎屑。$"

Part7_Text_062:
	.string "岩缝里有一块微微反光的碎片。$"

Part7_Text_063:
	.string "找到了一块完整的陨星碎片！$"

Part7_Text_064:
	.string "岩缝里只剩下细小的碎屑。$"

Part7_Text_065:
	.string "岩缝里有一块微微反光的碎片。$"

Part7_Text_066:
	.string "找到了一块完整的陨星碎片！$"

Part7_Text_067:
	.string "岩缝里只剩下细小的碎屑。$"

Part7_Text_068:
	.string "岩壁上贴着一个新的测量标记。\p编号的开头是阿尔刻的缩写。\p附近没有人。$"

Part7_Text_069:
	.string "……踩空了。\p腿没断。\p就是背包掉下去了。\p好像滚到更深的龙巢那边去了。$"

Part7_Text_070:
	.string "我的背包！\p里面的东西都还在。\p谢谢你，这些拿去用吧。$"

Part7_Text_071:
	.string "腿已经好多了。\p再休息一会儿就能下山了。$"

Part7_Text_072:
	.string "岩石下面卡着一个登山背包。\p是那位登山客的吧。$"

Part7_Text_073:
	.string "捡起了登山背包。$"

Part7_Text_074:
	.string "这里什么都没有了。$"

Part7_Text_075:
	.string "宝贝龙一直盯着你。\p它看起来非常有精神。$"

Part7_Text_076:
	.string "这里是研究营地。\p走到这么深的地方，一定累了吧。\p让宝可梦休息一下。$"

Part7_Text_077:
	.string "随时可以回来休息。\p这里不收钱。$"

Part7_Text_078:
	.string "一块无法带走的大陨石。\p表面非常光滑。\p触碰时，能感觉到微弱的热量。$"

Part7_Text_079:
	.string "岩台下面的水池很清。\p水边有几片脱落的鳞片。$"

Part7_Text_080:
	.string "地上散着碎掉的蛋壳。\p岩壁上有新的抓痕。$"

Part7_Text_081:
	.string "能走到这里，\p说明你没走错路。$"

Part7_Text_082:
	.string "……八枚。\p来试试吧。$"

Part7_Text_083:
	.string "……好。\p龙巢认得你了。$"

Part7_Text_084:
	.string "这块石头，我年轻时在这里找到的。\p该交给下一个走到这里的人了。$"

Part7_Text_085:
	.string "源治那家伙，现在还在联盟吧。\p替我问声好。$"

Part7_Text_086:
	.string "听说新的冠军诞生了。\p……原来是你。\p要不要用真正的队伍，再来一次？$"

Part7_Text_087:
	.string "……哈。\p冠军果然不一样。$"

Part7_Text_088:
	.string "第一次赢我的冠军，\p得拿点像样的东西回去。$"

Part7_Text_089:
	.string "龙巢随时欢迎你。$"

Part7_Text_090:
	.string "想打的时候再来。$"

Part7_Text_091:
	.string "看来这块石头你已经有了。\p那就换成别的东西吧。$"

Part7_Text_092:
	.string "大吾：看来那块石头已经到你手里了。\p那就收下这些吧。$"

Part7_Text_093:
	.string "两股海流在礁石前分开，\p一股冲向凯那，一股绕回这里。\p只有选对两次才能靠岸。$"

Part7_Text_094:
	.string "第一次来这里的时候，\p我直接被冲到凯那了。$"

Part7_Text_095:
	.string "看来你也不是随便漂过来的。$"

Part7_Text_096:
	.string "北边礁石那里的海流，要选对两次。\p选错了就从头来。$"

Part7_Text_097:
	.string "兄：这座岛是我们发现的！\p妹：要过去，先赢我们两个！$"

Part7_Text_098:
	.string "兄：……被回流冲散了。\p妹：都怪你走太快！$"

Part7_Text_099:
	.string "兄：我们是两个人。\p带两只宝可梦再来！$"

Part7_Text_100:
	.string "妹：岛后面那个洞，\p涨潮的时候会被水淹一半。$"

Part7_Text_101:
	.string "礁石缝里卡着两颗闪闪发光的东西。$"

Part7_Text_102:
	.string "海浪拍打着礁石。$"

Part7_Text_103:
	.string "岩壁下面有一个海蚀洞。\p潮水留下的痕迹一直延伸到里面。\p要进去吗？$"

Part7_Text_104:
	.string "潮痕下面压着一个旧防水袋。\p里面好像是航海记录。$"

Part7_Text_105:
	.string "捡起了旧防水袋。$"

Part7_Text_106:
	.string "潮水在岩壁上留下一圈一圈的痕迹。$"

Part7_Text_107:
	.string "糟了，航海记录袋被浪卷走了。\p多半漂进后面那个海蚀洞了。\p我的船进不去……$"

Part7_Text_108:
	.string "就是这个！\p记录一页都没湿。\p太感谢了！$"

Part7_Text_109:
	.string "下次出海，我会把袋子绑紧一点。$"

Part7_Text_110:
	.string "岩壁上有一圈一圈的潮痕。\p最高的那一圈，比你的头还高。$"

Part7_Text_111:
	.string "急流在这里突然平静下来。$"

Part7_Text_112:
	.string "新的冠军也是从这道瀑布上去的。\p……徽章只能把人送到这里。\p上面的路，都得自己走。$"

Part7_Text_113:
	.string "到这里的人，都有八枚徽章。\p……不过徽章只能把你送到这里。\p上面的路，得自己走。$"

Part7_Text_114:
	.string "八枚徽章，确认完毕。\p前面就是彩幽。$"

Part7_Text_115:
	.string "祝你好运。$"

Part7_Text_116:
	.string "这是临时的露天训练平台。\p进冠军之路之前，热热身吧！$"

Part7_Text_117:
	.string "……热身的是我才对。$"

Part7_Text_118:
	.string "冠军之路很长。\p药一定要带够。$"

Part7_Text_119:
	.string "我的大嘴鸥送信的时候撞到岩壁了。\p翅膀擦伤了，飞不起来。\p宝可梦中心那边，\p也许有能用的急救药……$"

Part7_Text_120:
	.string "这就是急救药？\p……好了，它又能扑腾翅膀了！\p这些是谢礼，请收下。$"

Part7_Text_121:
	.string "它又能送信了。\p这次我们会绕开那面岩壁。$"

Part7_Text_122:
	.string "受伤的大嘴鸥？\p这是给野外宝可梦用的急救药，\p请拿去用吧。$"

Part7_Text_123:
	.string "拿到了任务用的急救药。$"

Part7_Text_124:
	.string "每年这个季节，\p来挑战联盟的人都特别多。$"

Part7_Text_125:
	.string "联盟挑战者留言板。$"

Part7_Text_126:
	.string "“第四次挑战。\p这次一定要打到源治。”$"

Part7_Text_127:
	.string "“给明年的自己：\p记得买解异常药。”$"

Part7_Text_128:
	.string "“第一次来。\p有点紧张。”$"

Part7_Text_129:
	.string "最新的一张纸条写着：\p“新的冠军诞生了。”$"

Part7_Text_130:
	.string "朋友给我画了一张冠军之路的地图，\p可是第一个岔路就对不上。\p你要是进去了，能帮我看看\p入口附近的路标吗？$"

Part7_Text_131:
	.string "原来要往另一边走！\p他把左右画反了……\p谢谢你，这些拿去用吧。$"

Part7_Text_132:
	.string "我把地图改好了。\p下次换我给别人指路。$"

Part7_Text_133:
	.string "姐姐一个人先进冠军之路了。\p说好天黑前回来的……\p你要是在里面看到她，能帮我看看吗？$"

Part7_Text_134:
	.string "这是姐姐的护具！\p她没事就好……\p这些是姐姐让我给你的。$"

Part7_Text_135:
	.string "姐姐回宝可梦中心休息了。\p她说明年还要再来。$"

Part7_Text_136:
	.string "脚已经不疼了。\p谢谢你帮我把护具带给弟弟。\p明年，我会一口气走到底。$"

Part7_Text_137:
	.string "听说联盟最近换了新的冠军。\p……长什么样？我也没见过。$"

Part7_Text_138:
	.string "输了三场。\p……明天再进去。$"

Part7_Text_139:
	.string "我去年也来过。\p今年的队伍，已经不一样了。$"

Part7_Text_140:
	.string "孩子进联盟已经两个小时了。\p……这种时候，\p大人反而最紧张。$"

Part7_Text_141:
	.string "岩壁上留下了许多训练家做的路线标\n记。$"

Part7_Text_142:
	.string "地上散着已经空掉的药品包装。$"

Part7_Text_143:
	.string "石头上刻着几个名字。\p有的已经被磨得看不清了。$"

Part7_Text_144:
	.string "倒在地上的旧路标。\p箭头指向和入口相反的那条岔路。$"

Part7_Text_145:
	.string "……那张地图把左右画反了。\p回去告诉他吧。$"

Part7_Text_146:
	.string "利欧路摆好了架势。\p它好像一直在这里独自修行。$"

Part7_Text_147:
	.string "我在这里搭营地好些年了。\p坐下歇一会儿吧。$"

Part7_Text_148:
	.string "好了。\p前面的路，自己走。$"

Part7_Text_149:
	.string "营地里多带了一些药。\p要买吗？$"

Part7_Text_150:
	.string "路上小心。$"

Part7_Text_151:
	.string "……我弟弟让你来找我的？\p没事，只是扭到脚了。\p休息一下就能自己走回去。$"

Part7_Text_152:
	.string "这个护具帮我带给他吧。\p他看到就知道我没事了。$"

Part7_Text_153:
	.string "拿到了绑好的护具。$"

Part7_Text_154:
	.string "又是你！\p从119号道路开始，\p我就一直想再打一次！$"

Part7_Text_155:
	.string "还是差一点。$"

Part7_Text_156:
	.string "还是差一点。\p不过能走到这里，也不算白跑。$"

Part7_Text_157:
	.string "这块平台，是我修行的地方。\p你的气息很稳。\p要和我的路卡利欧比一比吗？$"

Part7_Text_158:
	.string "……波导不会说谎。\p你赢了。$"

Part7_Text_159:
	.string "这块石头，交给你。$"

Part7_Text_160:
	.string "心静下来再来。$"

Part7_Text_161:
	.string "修行没有终点。\p联盟也是。$"

Part7_Text_162:
	.string "看来这块石头你已经有了。\p那就换成别的东西吧。$"

Part7_Text_163:
	.string "……你也要去联盟？\p我的烈咬陆鲨，\p现在还不是拿出来的时候。\p等你从里面出来，再说吧。$"

Part7_Text_164:
	.string "……你真的出来了。\p而且是以冠军的身份。\p现在，是时候了。$"

Part7_Text_165:
	.string "……原来冠军是这种感觉。$"

Part7_Text_166:
	.string "这块石头，本来是给赢过我的人准备\n的。$"

Part7_Text_167:
	.string "我还会在这里练。\p下次换我去联盟。$"

Part7_Text_168:
	.string "看来这块石头你已经有了。\p那就换成别的东西吧。$"

Part7_Text_169:
	.string "满充：……这是我现在最好的队伍了。\p这个，你拿着。\p就当是我还没追上你的证明。$"

Part7_Text_170:
	.string "八枚徽章，确认完毕。\p第一次挑战联盟的训练家，\p可以领取一份补给。$"

Part7_Text_171:
	.string "里面是连续五场对战，中途不能出来。\p祝你好运。$"

Part7_Text_172:
	.string "您完整打通了强化联盟！\p这是联盟为此准备的奖励。$"

Part7_Text_173:
	.string "得到了50000元！$"

Part7_Text_174:
	.string "里面是连续五场对战。\p准备好了再进去。$"

Part7_Text_175:
	.string "冠军回来了。\p四天王和米可利先生\p已经换上了真正的队伍。$"

Part7_Text_176:
	.string "联盟设施内无法使用本原调律器。$"

Part7_Text_177:
	.string "喂。\p你也是来看新闻里那只宝可梦的？$"

Part7_Text_178:
	.string "红白色的那只。\p我追了三天。$"

Part7_Text_179:
	.string "蓝白色的那只。\p我追了三天。$"

Part7_Text_180:
	.string "一次在凯那附近。\p一次在119号道路。\p还有一次……\p我追错了一只大嘴鸥。$"

Part7_Text_181:
	.string "你当时也看错了！\p……总之，它好像常在119号道路\p天气研究所附近停下来。\p我先过去了，你也来吧。$"

Part7_Text_182:
	.string "下一站去哪？\p还没决定。\p反正现在，是我们自己选。$"

Part7_Text_183:
	.string "它停了一下……\p然后朝南边飞走了。$"

Part7_Text_184:
	.string "……又让它跑了。$"

Part7_Text_185:
	.string "不过这次我看清了。\p它一直往海那边看。\p南边……是南方孤岛。$"

Part7_Text_186:
	.string "对了，这个给你。\p以前旅行的时候，船员送我的旧船票。\p我本来以为只是纪念品。\p现在看来，还真有地方能用。$"

Part7_Text_187:
	.string "拿着它去水静港口坐船。\p我和胖丁先去岛上等你！$"

Part7_Text_188:
	.string "嘘——\p它在那边，好像很累。\p慢慢走过去，别吓到它。$"

Part7_Text_189:
	.string "它蜷在岩台边，翅膀上有擦伤。\p危机时的极端天气里，\p它好像硬撑着飞了很远。$"

Part7_Text_190:
	.string "胖丁女孩：慢一点。\p别吓到它。$"

Part7_Text_191:
	.string "胖丁慢慢靠了过去……\p它的呼吸渐渐平稳下来。$"

Part7_Text_192:
	.string "天空中传来一声长鸣！$"

Part7_Text_193:
	.string "两只宝可梦靠在一起，\p轻轻地叫了几声。$"

Part7_Text_194:
	.string "胖丁女孩：……总算找到了。$"

Part7_Text_195:
	.string "以前，每天都有人告诉我下一步去哪。\p……\p现在自己找地方去，好像也不错。$"

Part7_Text_196:
	.string "嗯。\p下一站，我们自己选。$"

Part7_Text_197:
	.string "它们看起来已经放松下来了。\p……要不要试着和它们交流？$"

Part7_Text_198:
	.string "它飞向了岛的另一边……\p离开这里再回来，也许还能见到它。$"

Part7_Text_199:
	.string "石台的凹槽里，\p静静放着一颗透明的宝珠。$"

Part7_Text_200:
	.string "桌上放着一本笔记：\p“丰缘近期记录”。$"

Part7_Text_201:
	.string "……记录就到这里。$"

Part7_Text_202:
	.string "最近还没有新的记录。$"

Part7_Text_203:
	.string "天气研究所的报告：\p丰缘某处又观测到了异常天气。$"

Part7_Text_204:
	.string "流星瀑布的消息：\p有人在深处见到了一位银发的训练家。$"

Part7_Text_205:
	.string "凯那港口的目击报告：\p天上飞过红色和蓝色的影子。$"

Part7_Text_206:
	.string "新的船舶航线：\p凯那和水静港口开通了新的航线。$"

Part7_Text_207:
	.string "沙漠里的传闻：\p那边最近又发现了一条通道。$"

Part7_Text_208:
	.string "冠军？$"

Part7_Text_209:
	.string "……让我先看看你。\p瘦了没有？$"

Part7_Text_210:
	.string "以后还会到处跑吧。\p这些带着。$"

Part7_Text_211:
	.string "千里：做得很好。\p……冠军也还是训练家。\p有空再来打一场。$"

Part7_Text_212:
	.string "男：冠军都能来参加我们的婚礼了。$"

Part7_Text_213:
	.string "女：谁说现在要办了？$"

Part7_Text_214:
	.string "男：我只是说如果！$"

Part7_Text_215:
	.string "听说你成了冠军？恭喜！\p……环境部门还在分析上次的数据。\p地下那一层？\p那里需要更高级的权限。$"

Part7_Text_216:
	.string "那个异常信号突然稳定了。\p原因还在确认。$"

Part7_Text_217:
	.string "……冠军。$"

Part7_Text_218:
	.string "……$"

Part7_Text_219:
	.string "他又转回去，继续钓鱼了。$"

Part7_Text_220:
	.string "冠军？\p哈哈，女儿天天跟我念叨你。\p要不要看看我真正的钓竿？$"

Part7_Text_221:
	.string "……这条大鱼，我钓不上来。$"

Part7_Text_222:
	.string "钓鱼和对战一样，\p都得耐心等。$"

Part7_Text_223:
	.string "鱼不会跑的。\p你也不会吧？$"

Part7_Text_224:
	.string "讲究眼镜 48BP$"

Part7_Text_225:
	.string "讲究围巾 48BP$"

Part7_Text_226:
	.string "生命宝珠 48BP$"

Part7_Text_227:
	.string "气势披带 48BP$"

Part7_Text_228:
	.string "凸凸头盔 48BP$"

Part7_Text_229:
	.string "突击背心 48BP$"

Part7_Text_230:
	.string "进化奇石 48BP$"

Part7_Text_231:
	.string "强力香草 32BP$"

Part7_Text_232:
	.string "达人带 48BP$"

Part7_Text_233:
	.string "PP提升剂 16BP$"

Part7_Text_234:
	.string "特性胶囊 32BP$"

Part7_Text_235:
	.string "固执薄荷 24BP$"

Part7_Text_236:
	.string "内敛薄荷 24BP$"

Part7_Text_237:
	.string "爽朗薄荷 24BP$"

Part7_Text_238:
	.string "胆小薄荷 24BP$"

Part7_Text_239:
	.string "特性膏药 128BP$"

Part7_Text_240:
	.string "不用了$"

Part7_Text_241:
	.string "这里是竞技道具兑换处。\p可以用对战点数换道具。\p超级石不在兑换范围内。$"

Part7_Text_242:
	.string "要换哪一样？$"

Part7_Text_243:
	.string "兑换好了。\p请收好。$"

Part7_Text_244:
	.string "对战点数不够哦。$"

Part7_Text_245:
	.string "背包已经放不下了。$"

Part7_Text_246:
	.string "欢迎再来。$"

