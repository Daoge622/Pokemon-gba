@ PART 6 generated scripts. Design: docs/story/PART6_DRAFT.md (DESIGN CONFIRMED / DRAFT)
Part6_BagFull::
	msgbox Part6_Text_001, MSGBOX_DEFAULT
	release
	end

Part6_QuietEnd::
	releaseall
	end

Part6_Return::
	return

Part6_RookieSpaceCenter::
	lock
	faceplayer
	goto_if_ge VAR_MOSSDEEP_CITY_STATE, 3, Part6_RookieSpaceCenter_After
	msgbox Part6_Text_002, MSGBOX_DEFAULT
	msgbox Part6_Text_003, MSGBOX_DEFAULT
	release
	end

Part6_RookieSpaceCenter_After::
	msgbox Part6_Text_004, MSGBOX_DEFAULT
	msgbox Part6_Text_005, MSGBOX_DEFAULT
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part6_Text_006, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PART6_ROOKIE_SPACE_CENTER
	setflag FLAG_PART6_ROOKIE_LEFT_MAGMA
	setflag FLAG_TEMP_1E
	fadescreen FADE_FROM_BLACK
	release
	end

Part6_BagFullAll::
	msgbox Part6_Text_007, MSGBOX_DEFAULT
	releaseall
	end

Part6_Anomaly0::
	lockall
	msgbox Part6_Text_008, MSGBOX_DEFAULT
	goto_if_set FLAG_PART6_ANOMALY_HEAT, Part6_QuietEnd
	goto_if_lt VAR_PART55_UNDERWATER_OBSERVATION, 1, Part6_QuietEnd
	setflag FLAG_PART6_ANOMALY_HEAT
	special Part6_CountAnomaly
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox Part6_Text_009, MSGBOX_DEFAULT
	releaseall
	end

Part6_Anomaly1::
	lockall
	msgbox Part6_Text_010, MSGBOX_DEFAULT
	goto_if_set FLAG_PART6_ANOMALY_CURRENT, Part6_QuietEnd
	goto_if_lt VAR_PART55_UNDERWATER_OBSERVATION, 1, Part6_QuietEnd
	setflag FLAG_PART6_ANOMALY_CURRENT
	special Part6_CountAnomaly
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox Part6_Text_011, MSGBOX_DEFAULT
	releaseall
	end

@ Underwater observation devices (visible objects; they replaced the old
@ invisible sign events). One device can serve both the calibration job
@ (Rain, Route 127) and the anomaly survey (researcher, Route 124).
Part6_Site127::
	goto_if_unset FLAG_PART6_CALIBRATION_ASKED, Part6_Anomaly1
	goto_if_unset FLAG_PART6_CALIBRATION_1, Part6_CalPoint0
	goto Part6_Anomaly1

Part6_Site128::
	goto_if_unset FLAG_PART6_CALIBRATION_ASKED, Part6_Anomaly2
	goto_if_unset FLAG_PART6_CALIBRATION_3, Part6_CalPoint2
	goto Part6_Anomaly2

Part6_Anomaly2::
	lockall
	msgbox Part6_Text_012, MSGBOX_DEFAULT
	goto_if_set FLAG_PART6_ANOMALY_ENERGY, Part6_QuietEnd
	goto_if_lt VAR_PART55_UNDERWATER_OBSERVATION, 1, Part6_QuietEnd
	setflag FLAG_PART6_ANOMALY_ENERGY
	special Part6_CountAnomaly
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox Part6_Text_013, MSGBOX_DEFAULT
	releaseall
	end

Part6_AnomalyResearcher::
	goto_if_set FLAG_PART6_ANOMALY_REWARD, Part6_AnomalyResearcher_Done
	goto_if_lt VAR_PART55_UNDERWATER_OBSERVATION, 1, Part55_UnderwaterResearcher
	special Part6_CountAnomaly
	goto_if_lt VAR_RESULT, 3, Part55_UnderwaterResearcher
	lock
	faceplayer
	msgbox Part6_Text_014, MSGBOX_DEFAULT
	checkitemspace ITEM_EVOLUTION_STONE, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	checkitemspace ITEM_BIG_PEARL, 3
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_EVOLUTION_STONE, 1
	giveitem ITEM_BIG_PEARL, 3
	setflag FLAG_PART6_ANOMALY_REWARD
	release
	end

Part6_AnomalyResearcher_Done::
	msgbox Part6_Text_015, MSGBOX_NPC
	end

Part6_Coral::
	msgbox Part6_Text_016, MSGBOX_SIGN
	end

Part6_Crates::
	msgbox Part6_Text_017, MSGBOX_SIGN
	end

Part6_Pillar::
	msgbox Part6_Text_018, MSGBOX_SIGN
	end

Part6_SeabedSensor::
	msgbox Part6_Text_019, MSGBOX_SIGN
	end

Part6_Route126Diver::
	goto_if_unset FLAG_RECEIVED_HM_DIVE, Part6_Route126Diver_Before
	msgbox Part6_Text_020, MSGBOX_NPC
	end
Part6_Route126Diver_Before::
	msgbox Part6_Text_021, MSGBOX_NPC
	end

Part6_CoralFather::
	lock
	faceplayer
	goto_if_set FLAG_PART6_CORAL_DONE, Part6_CoralFather_Done
	goto_if_set FLAG_PART6_CORAL_SEEN, Part6_CoralFather_Seen
	goto_if_unset FLAG_RECEIVED_HM_DIVE, Part6_CoralFather_Before
	msgbox Part6_Text_022, MSGBOX_DEFAULT
	setflag FLAG_PART6_CORAL_ASKED
	release
	end
Part6_CoralFather_Before::
	msgbox Part6_Text_023, MSGBOX_DEFAULT
	release
	end
Part6_CoralFather_Seen::
	msgbox Part6_Text_024, MSGBOX_DEFAULT
	release
	end
Part6_CoralFather_Done::
	msgbox Part6_Text_025, MSGBOX_DEFAULT
	release
	end

Part6_CoralDaughter::
	lock
	faceplayer
	goto_if_set FLAG_PART6_CORAL_DONE, Part6_CoralDaughter_Done
	goto_if_set FLAG_PART6_CORAL_SEEN, Part6_CoralDaughter_Ask
	msgbox Part6_Text_026, MSGBOX_DEFAULT
	release
	end
Part6_CoralDaughter_Ask::
	msgbox Part6_Text_027, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, Part6_Choice_Pretty, Part6_Choice_Dark
	goto_if_eq VAR_RESULT, 1, Part6_CoralDaughter_Dark
	msgbox Part6_Text_028, MSGBOX_DEFAULT
	goto Part6_CoralDaughter_Reward
Part6_CoralDaughter_Dark::
	msgbox Part6_Text_029, MSGBOX_DEFAULT
	msgbox Part6_Text_030, MSGBOX_DEFAULT
Part6_CoralDaughter_Reward::
	msgbox Part6_Text_031, MSGBOX_DEFAULT
	giveitem ITEM_HEART_SCALE, 3
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	setflag FLAG_PART6_CORAL_DONE
	release
	end
Part6_CoralDaughter_Done::
	msgbox Part6_Text_032, MSGBOX_DEFAULT
	release
	end

Part6_Choice_Pretty:
	.string "很好看$"
Part6_Choice_Dark:
	.string "有点黑$"

Part6_CoralSpot::
	lockall
	msgbox Part6_Text_033, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART6_CORAL_ASKED, Part6_QuietEnd
	setflag FLAG_PART6_CORAL_SEEN
	releaseall
	end

Part6_OldDiver::
	lock
	faceplayer
	goto_if_set FLAG_PART6_DIVE_LAMP_DONE, Part6_OldDiver_Done
	checkitem ITEM_OLD_DIVE_LAMP
	goto_if_eq VAR_RESULT, TRUE, Part6_OldDiver_Return
	msgbox Part6_Text_034, MSGBOX_DEFAULT
	release
	end

Part6_OldDiver_Return::
	msgbox Part6_Text_035, MSGBOX_DEFAULT
	checkitemspace ITEM_DIVE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	checkitemspace ITEM_PEARL, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_DIVE_BALL, 5
	giveitem ITEM_PEARL, 1
	removeitem ITEM_OLD_DIVE_LAMP, 1
	setflag FLAG_PART6_DIVE_LAMP_DONE
	release
	end

Part6_OldDiver_Done::
	msgbox Part6_Text_036, MSGBOX_DEFAULT
	release
	end

Part6_DiveLampSpot::
	lockall
	goto_if_set FLAG_PART6_DIVE_LAMP_TAKEN, Part6_DiveLampSpot_Empty
	msgbox Part6_Text_037, MSGBOX_DEFAULT
	giveitem ITEM_OLD_DIVE_LAMP, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_DIVE_LAMP_TAKEN
	special StoryRefreshPickupMarkers
	releaseall
	end

Part6_DiveLampSpot_Empty::
	msgbox Part6_Text_038, MSGBOX_DEFAULT
	releaseall
	end

Part6_TideOldMan::
	lock
	faceplayer
	goto_if_set FLAG_PART6_TIDE_RECORDER_DONE, Part6_TideOldMan_Done
	checkitem ITEM_TIDE_RECORDER
	goto_if_eq VAR_RESULT, TRUE, Part6_TideOldMan_Return
	msgbox Part6_Text_039, MSGBOX_DEFAULT
	release
	end

Part6_TideOldMan_Return::
	msgbox Part6_Text_040, MSGBOX_DEFAULT
	checkitemspace ITEM_SLOWBRONITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_SLOWBRONITE, 1
	removeitem ITEM_TIDE_RECORDER, 1
	setflag FLAG_PART6_TIDE_RECORDER_DONE
	release
	end

Part6_TideOldMan_Done::
	msgbox Part6_Text_041, MSGBOX_DEFAULT
	release
	end

Part6_TideRecorderSpot::
	lockall
	goto_if_set FLAG_PART6_TIDE_RECORDER_TAKEN, Part6_TideRecorderSpot_Empty
	msgbox Part6_Text_042, MSGBOX_DEFAULT
	giveitem ITEM_TIDE_RECORDER, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_TIDE_RECORDER_TAKEN
	special StoryRefreshPickupMarkers
	releaseall
	end

Part6_TideRecorderSpot_Empty::
	msgbox Part6_Text_043, MSGBOX_DEFAULT
	releaseall
	end

Part6_TideSlowpoke::
	lock
	faceplayer
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part6_Boatman::
	lock
	faceplayer
	goto_if_set FLAG_PART6_TOOLBOX_DONE, Part6_Boatman_Done
	checkitem ITEM_WATERPROOF_TOOLBOX
	goto_if_eq VAR_RESULT, TRUE, Part6_Boatman_Return
	msgbox Part6_Text_044, MSGBOX_DEFAULT
	release
	end

Part6_Boatman_Return::
	msgbox Part6_Text_045, MSGBOX_DEFAULT
	checkitemspace ITEM_DIVE_BALL, 10
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	checkitemspace ITEM_BIG_PEARL, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_DIVE_BALL, 10
	giveitem ITEM_BIG_PEARL, 1
	removeitem ITEM_WATERPROOF_TOOLBOX, 1
	setflag FLAG_PART6_TOOLBOX_DONE
	release
	end

Part6_Boatman_Done::
	msgbox Part6_Text_046, MSGBOX_DEFAULT
	release
	end

Part6_ToolboxSpot::
	lockall
	goto_if_set FLAG_PART6_TOOLBOX_TAKEN, Part6_ToolboxSpot_Empty
	msgbox Part6_Text_047, MSGBOX_DEFAULT
	giveitem ITEM_WATERPROOF_TOOLBOX, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_TOOLBOX_TAKEN
	special StoryRefreshPickupMarkers
	releaseall
	end

Part6_ToolboxSpot_Empty::
	msgbox Part6_Text_048, MSGBOX_DEFAULT
	releaseall
	end

Part6_Wreck::
	lockall
	goto_if_unset FLAG_RECEIVED_HM_DIVE, Part6_Wreck_Surface
	goto_if_set FLAG_PART6_ROUTE130_WRECK, Part6_Wreck_Done
	msgbox Part6_Text_049, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part6_QuietEnd
	fadescreen FADE_TO_BLACK
	msgbox Part6_Text_050, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_Wreck_Full
	checkitemspace ITEM_NUGGET, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_Wreck_Full
	giveitem ITEM_PP_UP, 1
	giveitem ITEM_NUGGET, 1
	setflag FLAG_PART6_ROUTE130_WRECK
	fadescreen FADE_FROM_BLACK
	releaseall
	end
Part6_Wreck_Full::
	fadescreen FADE_FROM_BLACK
	goto Part6_BagFullAll
Part6_Wreck_Surface::
	msgbox Part6_Text_051, MSGBOX_DEFAULT
	releaseall
	end
Part6_Wreck_Done::
	msgbox Part6_Text_052, MSGBOX_DEFAULT
	releaseall
	end

Part6_Paleontologist::
	lock
	faceplayer
	goto_if_set FLAG_PART6_SAMPLE_CASE_DONE, Part6_Paleontologist_Done
	checkitem ITEM_SAMPLE_CASE
	goto_if_eq VAR_RESULT, TRUE, Part6_Paleontologist_Return
	msgbox Part6_Text_053, MSGBOX_DEFAULT
	release
	end

Part6_Paleontologist_Return::
	msgbox Part6_Text_054, MSGBOX_DEFAULT
	checkitemspace ITEM_AERODACTYLITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_AERODACTYLITE, 1
	removeitem ITEM_SAMPLE_CASE, 1
	setflag FLAG_PART6_SAMPLE_CASE_DONE
	release
	end

Part6_Paleontologist_Done::
	msgbox Part6_Text_055, MSGBOX_DEFAULT
	release
	end

Part6_SampleDive::
	lockall
	goto_if_unset FLAG_RECEIVED_HM_DIVE, Part6_Wreck_Surface
	goto_if_set FLAG_PART6_SAMPLE_CASE_TAKEN, Part6_QuietEnd
	msgbox Part6_Text_056, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part6_QuietEnd
	fadescreen FADE_TO_BLACK
	msgbox Part6_Text_057, MSGBOX_DEFAULT
	giveitem ITEM_SAMPLE_CASE, 1
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_SAMPLE_CASE_TAKEN
	special StoryRefreshPickupMarkers
	releaseall
	end

Part6_Crevice::
	lockall
	msgbox Part6_Text_058, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part6_QuietEnd
	warp MAP_ROUTE126_STILL_WATER_CAVE, 19, 4
	waitstate
	releaseall
	end

Part6_CaveExit::
	lockall
	msgbox Part6_Text_059, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part6_QuietEnd
	warp MAP_UNDERWATER_ROUTE126, 5, 78
	waitstate
	releaseall
	end

Part6_Suicune::
	lockall
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitmoncry
	seteventmon SPECIES_SUICUNE, 40
	special Part6_BeginSuicuneBattle
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	special Part6_FinishSuicuneBattle
	removeobject LOCALID_PART6_SUICUNE
	goto_if_set FLAG_PART6_SUICUNE_CAUGHT, Part6_QuietEnd
	msgbox Part6_Text_060, MSGBOX_DEFAULT
	releaseall
	end

Part6_StillWaterCave_OnTransition:
	special Part6_SyncSuicune
	end

Part6_RainObservatory::
	lock
	faceplayer
	goto_if_set FLAG_PART6_RAIN_INTRO, Part6_RainObservatory_Anomaly
	msgbox Part6_Text_061, MSGBOX_DEFAULT
	msgbox Part6_Text_062, MSGBOX_DEFAULT
	call Part6_RainTurnToAssistant
	msgbox Part6_Text_063, MSGBOX_DEFAULT
	msgbox Part6_Text_064, MSGBOX_DEFAULT
	msgbox Part6_Text_065, MSGBOX_DEFAULT
	msgbox Part6_Text_066, MSGBOX_DEFAULT
	applymovement LOCALID_PART6_RAIN_SC, Common_Movement_FacePlayer
	waitmovement 0
	setflag FLAG_PART6_RAIN_INTRO
	release
	end

Part6_RainObservatory_Anomaly::
	goto_if_set FLAG_PART6_RAIN_ANOMALY_TALK, Part6_RainObservatory_Idle
	special Part6_CountAnomaly
	goto_if_lt VAR_RESULT, 3, Part6_RainObservatory_Idle
	msgbox Part6_Text_067, MSGBOX_DEFAULT
	msgbox Part6_Text_068, MSGBOX_DEFAULT
	call Part6_RainTurnToAssistant
	msgbox Part6_Text_069, MSGBOX_DEFAULT
	msgbox Part6_Text_070, MSGBOX_DEFAULT
	msgbox Part6_Text_071, MSGBOX_DEFAULT
	msgbox Part6_Text_072, MSGBOX_DEFAULT
	msgbox Part6_Text_073, MSGBOX_DEFAULT
	msgbox Part6_Text_074, MSGBOX_DEFAULT
	applymovement LOCALID_PART6_RAIN_SC, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Part6_Text_075, MSGBOX_DEFAULT
	setflag FLAG_PART6_RAIN_ANOMALY_TALK
	release
	end

Part6_RainObservatory_Idle::
	msgbox Part6_Text_076, MSGBOX_DEFAULT
	release
	end

@ Rain and his assistant stand face to face at (5,8)/(5,7); the
@ assistant's lines are spoken to Rain, not to the player.
Part6_RainTurnToAssistant::
	applymovement LOCALID_PART6_RAIN_SC, Common_Movement_FaceUp
	applymovement LOCALID_PART6_RAIN_ASSISTANT_SC, Common_Movement_FaceDown
	waitmovement 0
	return

Part6_RainAssistant::
	lock
	faceplayer
	msgbox Part6_Text_077, MSGBOX_DEFAULT
	applymovement LOCALID_PART6_RAIN_ASSISTANT_SC, Common_Movement_FaceDown
	waitmovement 0
	release
	end

Part6_RainPlatform::
	lock
	faceplayer
	goto_if_defeated TRAINER_PART6_RAIN, Part6_RainPlatform_After
	msgbox Part6_Text_078, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part6_RainPlatform_No
	goto_if_unset FLAG_PART4_MEGA_RING_RECEIVED, Part6_RainPlatform_Battle
	msgbox Part6_Text_079, MSGBOX_DEFAULT
Part6_RainPlatform_Battle::
	trainerbattle_single TRAINER_PART6_RAIN, Part6_Text_080, Part6_Text_081, Part6_RainPlatform_After
	goto Part6_RainPlatform_After

Part6_RainPlatform_No::
	msgbox Part6_Text_082, MSGBOX_DEFAULT
	release
	end

Part6_RainPlatform_After::
	lock
	faceplayer
	goto_if_set FLAG_PART6_RAIN_TEST_REWARD, Part6_RainPlatform_Done
	msgbox Part6_Text_083, MSGBOX_DEFAULT
	checkitemspace ITEM_ABILITY_CAPSULE, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_ABILITY_CAPSULE, 1
	giveitem ITEM_PP_UP, 1
	setflag FLAG_PART6_RAIN_TEST_REWARD
	release
	end

Part6_RainPlatform_Done::
	msgbox Part6_Text_084, MSGBOX_DEFAULT
	release
	end

Part6_CalFisher::
	lock
	faceplayer
	goto_if_set FLAG_PART6_CALIBRATION_DONE, Part6_CalFisher_Done
	goto_if_set FLAG_PART6_CALIBRATION_ASKED, Part6_CalFisher_Check
	msgbox Part6_Text_085, MSGBOX_DEFAULT
	call Part6_CalFaceArgue
	msgbox Part6_Text_086, MSGBOX_DEFAULT
	msgbox Part6_Text_087, MSGBOX_DEFAULT
	msgbox Part6_Text_088, MSGBOX_DEFAULT
	msgbox Part6_Text_089, MSGBOX_DEFAULT
	msgbox Part6_Text_090, MSGBOX_DEFAULT
	msgbox Part6_Text_091, MSGBOX_DEFAULT
	msgbox Part6_Text_092, MSGBOX_DEFAULT
	call Part6_CalFacePlayer
	goto_if_unset FLAG_RECEIVED_HM_DIVE, Part6_CalFisher_End
	msgbox Part6_Text_093, MSGBOX_DEFAULT
	setflag FLAG_PART6_CALIBRATION_ASKED
Part6_CalFisher_End::
	release
	end

Part6_CalFisher_Check::
	goto_if_unset FLAG_PART6_CALIBRATION_1, Part6_CalFisher_Wait
	goto_if_unset FLAG_PART6_CALIBRATION_2, Part6_CalFisher_Wait
	goto_if_unset FLAG_PART6_CALIBRATION_3, Part6_CalFisher_Wait
	call Part6_CalFaceArgue
	call StoryA_CalHandIn
	call Part6_CalFacePlayer
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	checkitemspace ITEM_BIG_PEARL, 2
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_PP_UP, 1
	giveitem ITEM_BIG_PEARL, 2
	setflag FLAG_PART6_CALIBRATION_DONE
	release
	end

Part6_CalFisher_Wait::
	msgbox Part6_Text_098, MSGBOX_DEFAULT
	release
	end

Part6_CalFisher_Done::
	msgbox Part6_Text_099, MSGBOX_DEFAULT
	release
	end

@ Fisher (11,31) and the technician (9,31) face each other across the island; Rain (10,29) looks down at them.
Part6_CalFaceArgue::
	applymovement LOCALID_PART6_CAL_FISHER, Common_Movement_FaceLeft
	applymovement LOCALID_PART6_CAL_TECH, Common_Movement_FaceRight
	applymovement LOCALID_PART6_CAL_RAIN, Common_Movement_FaceDown
	waitmovement 0
	return

Part6_CalFacePlayer::
	applymovement LOCALID_PART6_CAL_RAIN, Common_Movement_FacePlayer
	applymovement LOCALID_PART6_CAL_FISHER, Common_Movement_FacePlayer
	waitmovement 0
	return

Part6_CalTech::
	msgbox Part6_Text_100, MSGBOX_NPC
	end

Part6_CalRain::
	msgbox Part6_Text_101, MSGBOX_NPC
	end

Part6_CalBoatman::
	msgbox Part6_Text_102, MSGBOX_NPC
	end

Part6_CalPoint0::
	lockall
	goto_if_unset FLAG_PART6_CALIBRATION_ASKED, Part6_CalPoint_Idle
	goto_if_set FLAG_PART6_CALIBRATION_1, Part6_CalPoint_Idle
	msgbox Part6_Text_103, MSGBOX_DEFAULT
	setflag FLAG_PART6_CALIBRATION_1
	releaseall
	end

Part6_CalPoint1::
	lockall
	goto_if_unset FLAG_PART6_CALIBRATION_ASKED, Part6_CalPoint_Idle
	goto_if_set FLAG_PART6_CALIBRATION_2, Part6_CalPoint_Idle
	msgbox Part6_Text_104, MSGBOX_DEFAULT
	setflag FLAG_PART6_CALIBRATION_2
	releaseall
	end

Part6_CalPoint2::
	lockall
	goto_if_unset FLAG_PART6_CALIBRATION_ASKED, Part6_CalPoint_Idle
	goto_if_set FLAG_PART6_CALIBRATION_3, Part6_CalPoint_Idle
	msgbox Part6_Text_105, MSGBOX_DEFAULT
	setflag FLAG_PART6_CALIBRATION_3
	releaseall
	end

Part6_CalPoint_Idle::
	msgbox Part6_Text_106, MSGBOX_DEFAULT
	releaseall
	end

Part6_RainHQ::
	lock
	faceplayer
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_RainHQ_Crisis
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Part6_RainHQ_After
	msgbox Part6_Text_107, MSGBOX_DEFAULT
	release
	end

Part6_RainHQ_Crisis::
	msgbox Part6_Text_108, MSGBOX_DEFAULT
	msgbox Part6_Text_109, MSGBOX_DEFAULT
	msgbox Part6_Text_110, MSGBOX_DEFAULT
	msgbox Part6_Text_111, MSGBOX_DEFAULT
	msgbox Part6_Text_112, MSGBOX_DEFAULT
	msgbox Part6_Text_113, MSGBOX_DEFAULT
	msgbox Part6_Text_114, MSGBOX_DEFAULT
	msgbox Part6_Text_115, MSGBOX_DEFAULT
	msgbox Part6_Text_116, MSGBOX_DEFAULT
	msgbox Part6_Text_117, MSGBOX_DEFAULT
	release
	end

Part6_RainHQ_After::
	goto_if_set FLAG_PART6_RAIN_AFTERMATH_TALK, Part6_RainHQ_AfterRepeat
	msgbox Part6_Text_118, MSGBOX_DEFAULT
	msgbox Part6_Text_119, MSGBOX_DEFAULT
	msgbox Part6_Text_120, MSGBOX_DEFAULT
	msgbox Part6_Text_121, MSGBOX_DEFAULT
	msgbox Part6_Text_122, MSGBOX_DEFAULT
	msgbox Part6_Text_123, MSGBOX_DEFAULT
	setflag FLAG_PART6_RAIN_AFTERMATH_TALK
	release
	end

Part6_RainHQ_AfterRepeat::
	goto_if_unset FLAG_STORY_A_10, StoryA_ReinSample
	special Part6_CountAdjusterWeathers
	goto_if_eq VAR_RESULT, 0, Part6_RainHQ_Busy
	msgbox Part6_Text_124, MSGBOX_DEFAULT
	release
	end

Part6_RainHQ_Busy::
	msgbox Part6_Text_125, MSGBOX_DEFAULT
	release
	end

Part6_HQCrisisStaff::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_HQCrisisStaff_Crisis
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Part6_HQCrisisStaff_After
	msgbox Part6_Text_126, MSGBOX_NPC
	end
Part6_HQCrisisStaff_Crisis::
	msgbox Part6_Text_127, MSGBOX_NPC
	end
Part6_HQCrisisStaff_After::
	goto_if_set FLAG_SYS_GAME_CLEAR, Part7_HqChampion
	msgbox Part6_Text_128, MSGBOX_NPC
	end

Part6_Crisis_SlateportCity_29::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_SlateportCity_29_C
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Part6_Crisis_SlateportCity_29_A
	goto Part5_SlateHarborWorker

Part6_Crisis_SlateportCity_29_C::
	msgbox Part6_Text_129, MSGBOX_NPC
	end

Part6_Crisis_SlateportCity_29_A::
	msgbox Part6_Text_130, MSGBOX_NPC
	end

Part6_Crisis_SlateportCity_30::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_SlateportCity_30_C
	goto Part5_SlateMarketMerchant

Part6_Crisis_SlateportCity_30_C::
	msgbox Part6_Text_131, MSGBOX_NPC
	end

Part6_Crisis_SlateportCity_31::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_SlateportCity_31_C
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Part6_Crisis_SlateportCity_31_A
	goto Part5_SlateArcheLogistics

Part6_Crisis_SlateportCity_31_C::
	msgbox Part6_Text_132, MSGBOX_NPC
	end

Part6_Crisis_SlateportCity_31_A::
	msgbox Part6_Text_133, MSGBOX_NPC
	end

Part6_Crisis_LilycoveCity_32::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_LilycoveCity_32_C
	goto Part5_LilyPortWorker

Part6_Crisis_LilycoveCity_32_C::
	msgbox Part6_Text_134, MSGBOX_NPC
	end

Part6_Crisis_ArcheCampus_33::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_ArcheCampus_33_C
	goto Part5_CampusEmployeeReport

Part6_Crisis_ArcheCampus_33_C::
	msgbox Part6_Text_135, MSGBOX_NPC
	end

Part6_Crisis_Route119_WeatherInstitute_1F_34::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_Route119_WeatherInstitute_1F_34_C
	goto Route119_WeatherInstitute_1F_EventScript_InstituteWorker1

Part6_Crisis_Route119_WeatherInstitute_1F_34_C::
	msgbox Part6_Text_136, MSGBOX_NPC
	end

Part6_Crisis_Route119_WeatherInstitute_1F_35::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_Route119_WeatherInstitute_1F_35_C
	goto Route119_WeatherInstitute_1F_EventScript_InstituteWorker2

Part6_Crisis_Route119_WeatherInstitute_1F_35_C::
	msgbox Part6_Text_137, MSGBOX_NPC
	end

Part6_Crisis_LavaridgeTown_36::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_LavaridgeTown_36_C
	goto LavaridgeTown_EventScript_HotSpringsOldWoman1

Part6_Crisis_LavaridgeTown_36_C::
	msgbox Part6_Text_138, MSGBOX_NPC
	end

Part6_Crisis_LavaridgeTown_37::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_LavaridgeTown_37_C
	goto LavaridgeTown_EventScript_ExpertM

Part6_Crisis_LavaridgeTown_37_C::
	msgbox Part6_Text_139, MSGBOX_NPC
	end

Part6_Crisis_MossdeepCity_SpaceCenter_1F_38::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_MossdeepCity_SpaceCenter_1F_38_C
	goto Part5_SpaceStaff

Part6_Crisis_MossdeepCity_SpaceCenter_1F_38_C::
	msgbox Part6_Text_140, MSGBOX_NPC
	end

Part6_Crisis_MossdeepCity_SpaceCenter_1F_39::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_MossdeepCity_SpaceCenter_1F_39_C
	goto Part55_LiaisonAfter

Part6_Crisis_MossdeepCity_SpaceCenter_1F_39_C::
	msgbox Part6_Text_141, MSGBOX_NPC
	end

Part6_Crisis_PacifidlogTown_40::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_PacifidlogTown_40_C
	goto PacifidlogTown_EventScript_Girl

Part6_Crisis_PacifidlogTown_40_C::
	msgbox Part6_Text_142, MSGBOX_NPC
	end

Part6_Crisis_PacifidlogTown_41::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Crisis_PacifidlogTown_41_C
	goto PacifidlogTown_EventScript_NinjaBoy

Part6_Crisis_PacifidlogTown_41_C::
	msgbox Part6_Text_143, MSGBOX_NPC
	end

Part6_SeafloorGear::
	msgbox Part6_Text_144, MSGBOX_SIGN
	end
Part6_SeafloorCharts::
	msgbox Part6_Text_145, MSGBOX_SIGN
	end
Part6_SeafloorMap::
	msgbox Part6_Text_146, MSGBOX_SIGN
	end

Part6_OriginWall1::
	msgbox Part6_Text_147, MSGBOX_SIGN
	end
Part6_OriginWall2::
	msgbox Part6_Text_148, MSGBOX_SIGN
	end
Part6_OriginWall3::
	msgbox Part6_Text_149, MSGBOX_SIGN
	end

Part6_SootFeeder::
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Part6_SootFeeder_After
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_SootFeeder_Crisis
	msgbox Part6_Text_150, MSGBOX_NPC
	end
Part6_SootFeeder_Crisis::
	msgbox Part6_Text_151, MSGBOX_NPC
	end
Part6_SootFeeder_After::
	msgbox Part6_Text_152, MSGBOX_NPC
	end

Part6_SootYoungMan::
	msgbox Part6_Text_153, MSGBOX_NPC
	end

Part6_SootDiveKid::
	msgbox Part6_Text_154, MSGBOX_NPC
	end

Part6_SootDiveMom::
	msgbox Part6_Text_155, MSGBOX_NPC
	end

Part6_SootBlockSign::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_SootBlockSign_Crisis
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Part6_SootBlockSign_After
	msgbox Part6_Text_156, MSGBOX_SIGN
	end
Part6_SootBlockSign_Crisis::
	msgbox Part6_Text_157, MSGBOX_SIGN
	end
Part6_SootBlockSign_After::
	msgbox Part6_Text_158, MSGBOX_SIGN
	end

Part6_SootBlockResident::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_SootBlockResident_Crisis
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Part6_SootBlockResident_After
	msgbox Part6_Text_159, MSGBOX_NPC
	end
Part6_SootBlockResident_Crisis::
	msgbox Part6_Text_160, MSGBOX_DEFAULT
	msgbox Part6_Text_161, MSGBOX_DEFAULT
	msgbox Part6_Text_162, MSGBOX_DEFAULT
	msgbox Part6_Text_163, MSGBOX_DEFAULT
	msgbox Part6_Text_164, MSGBOX_DEFAULT
	msgbox Part6_Text_165, MSGBOX_DEFAULT
	end
Part6_SootBlockResident_After::
	msgbox Part6_Text_166, MSGBOX_NPC
	end

Part6_SootBlockStaff::
	msgbox Part6_Text_167, MSGBOX_NPC
	end

Part6_ClinicNurse::
	lock
	faceplayer
	goto_if_set FLAG_PART6_AID_KIT_REWARD, Part6_ClinicNurse_Done
	goto_if_set FLAG_PART6_AID_KIT_DELIVERED, Part6_ClinicNurse_AfterKit
	checkitem ITEM_FIRST_AID_KIT
	goto_if_eq VAR_RESULT, TRUE, Part6_ClinicNurse_Return
	goto_if_unset FLAG_SYS_WEATHER_CTRL, Part6_ClinicNurse_Calm
	msgbox Part6_Text_168, MSGBOX_DEFAULT
	release
	end
Part6_ClinicNurse_Calm::
	msgbox Part6_Text_169, MSGBOX_DEFAULT
	release
	end
Part6_ClinicNurse_Return::
	msgbox Part6_Text_170, MSGBOX_DEFAULT
	removeitem ITEM_FIRST_AID_KIT, 1
	setflag FLAG_PART6_AID_KIT_DELIVERED
	release
	end
Part6_ClinicNurse_AfterKit::
	goto_if_lt VAR_SKY_PILLAR_STATE, 2, Part6_ClinicNurse_Busy
	msgbox Part6_Text_171, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	checkitemspace ITEM_FULL_RESTORE, 3
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_PP_UP, 1
	giveitem ITEM_FULL_RESTORE, 3
	setflag FLAG_PART6_AID_KIT_REWARD
	release
	end
Part6_ClinicNurse_Busy::
	msgbox Part6_Text_172, MSGBOX_DEFAULT
	release
	end
Part6_ClinicNurse_Done::
	msgbox Part6_Text_173, MSGBOX_DEFAULT
	release
	end

Part6_ClinicSableye::
	lock
	faceplayer
	playmoncry SPECIES_SABLEYE, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part6_AidKitSpot::
	lockall
	goto_if_set FLAG_PART6_AID_KIT_TAKEN, Part6_AidKitSpot_Empty
	msgbox Part6_Text_174, MSGBOX_DEFAULT
	giveitem ITEM_FIRST_AID_KIT, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_AID_KIT_TAKEN
	special StoryRefreshPickupMarkers
	releaseall
	end

Part6_AidKitSpot_Empty::
	msgbox Part6_Text_175, MSGBOX_DEFAULT
	releaseall
	end

Part6_SphealKid::
	lock
	faceplayer
	goto_if_set FLAG_PART6_SPHEAL_FOUND, Part6_SphealKid_Found
	msgbox Part6_Text_176, MSGBOX_DEFAULT
	release
	end
Part6_SphealKid_Found::
	goto_if_set FLAG_PART6_SPHEAL_REWARD, Part6_SphealKid_Done
	msgbox Part6_Text_177, MSGBOX_DEFAULT
	msgbox Part6_Text_178, MSGBOX_DEFAULT
	giveitem ITEM_DIVE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	setflag FLAG_PART6_SPHEAL_REWARD
	release
	end
Part6_SphealKid_Done::
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Part6_SphealKid_After
	msgbox Part6_Text_179, MSGBOX_DEFAULT
	release
	end
Part6_SphealKid_After::
	msgbox Part6_Text_180, MSGBOX_DEFAULT
	release
	end

Part6_SphealLost::
	lock
	faceplayer
	playmoncry SPECIES_SPHEAL, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part6_Text_181, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PART6_SPHEAL_LOST
	setflag FLAG_PART6_SPHEAL_FOUND
	special Part6_SyncMap
	addobject LOCALID_PART6_SPHEAL_HOME
	fadescreen FADE_FROM_BLACK
	release
	end

Part6_SphealHome::
	lock
	faceplayer
	playmoncry SPECIES_SPHEAL, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part6_Photographer::
	lock
	faceplayer
	goto_if_set FLAG_PART6_CAMERA_DONE, Part6_Photographer_Done
	checkitem ITEM_WATERPROOF_CAMERA
	goto_if_eq VAR_RESULT, TRUE, Part6_Photographer_Return
	msgbox Part6_Text_182, MSGBOX_DEFAULT
	release
	end

Part6_Photographer_Return::
	msgbox Part6_Text_183, MSGBOX_DEFAULT
	checkitemspace ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	checkitemspace ITEM_LUXURY_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_RARE_CANDY, 1
	giveitem ITEM_LUXURY_BALL, 5
	removeitem ITEM_WATERPROOF_CAMERA, 1
	setflag FLAG_PART6_CAMERA_DONE
	release
	end

Part6_Photographer_Done::
	msgbox Part6_Text_184, MSGBOX_DEFAULT
	release
	end

Part6_CameraSpot::
	lockall
	goto_if_set FLAG_PART6_CAMERA_TAKEN, Part6_CameraSpot_Empty
	msgbox Part6_Text_185, MSGBOX_DEFAULT
	giveitem ITEM_WATERPROOF_CAMERA, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_CAMERA_TAKEN
	special StoryRefreshPickupMarkers
	releaseall
	end

Part6_CameraSpot_Empty::
	msgbox Part6_Text_186, MSGBOX_DEFAULT
	releaseall
	end

Part6_GalladeMaster::
	lock
	faceplayer
	goto_if_set FLAG_PART6_GALLADITE, Part6_GalladeMaster_Done
	goto_if_defeated TRAINER_PART6_GALLADE_MASTER, Part6_GalladeMaster_Reward
	goto_if_lt VAR_SKY_PILLAR_STATE, 2, Part6_GalladeMaster_Wait
	msgbox Part6_Text_187, MSGBOX_DEFAULT
	trainerbattle_single TRAINER_PART6_GALLADE_MASTER, Part6_Text_188, Part6_Text_189, Part6_GalladeMaster_Reward
	goto Part6_GalladeMaster_Reward
Part6_GalladeMaster_Wait::
	msgbox Part6_Text_190, MSGBOX_DEFAULT
	release
	end
Part6_GalladeMaster_Reward::
	lock
	faceplayer
	msgbox Part6_Text_191, MSGBOX_DEFAULT
	giveitem ITEM_GALLADITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	setflag FLAG_PART6_GALLADITE
	release
	end
Part6_GalladeMaster_Done::
	msgbox Part6_Text_192, MSGBOX_DEFAULT
	release
	end

Part6_Anti::
	lock
	faceplayer
	goto_if_set FLAG_PART6_ADJUSTER_RECEIVED, Part6_Anti_Done
	msgbox Part6_Text_193, MSGBOX_DEFAULT
	msgbox Part6_Text_194, MSGBOX_DEFAULT
	msgbox Part6_Text_195, MSGBOX_DEFAULT
	giveitem ITEM_PRIMAL_ADJUSTER, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	setflag FLAG_PART6_ADJUSTER_RECEIVED
	msgbox Part6_Text_196, MSGBOX_DEFAULT
	msgbox Part6_Text_197, MSGBOX_DEFAULT
	msgbox Part6_Text_198, MSGBOX_DEFAULT
	msgbox Part6_Text_199, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PART6_ANTI
	fadescreen FADE_FROM_BLACK
	release
	end
Part6_Anti_Done::
	release
	end

Part6_EventScript_PrimalAdjuster::
	lockall
	special Part7_IsLeagueMap
	goto_if_eq VAR_RESULT, TRUE, Part7_AdjusterLeague
	special Part6_AdjusterCanUse
	goto_if_eq VAR_RESULT, 2, Part6_Adjuster_Extreme
	goto_if_eq VAR_RESULT, 1, Part6_Adjuster_Blocked
	msgbox Part6_Text_200, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, Part6_Adj_Sun, Part6_Adj_Rain, Part6_Adj_Sand, Part6_Adj_Snow, Part6_Adj_Reset, Part6_Adj_Cancel
	goto_if_ge VAR_RESULT, 5, Part6_QuietEnd
	copyvar VAR_0x8004, VAR_RESULT
	special Part6_AdjusterApply
	msgbox Part6_Text_201, MSGBOX_DEFAULT
	releaseall
	end
Part6_Adjuster_Blocked::
	msgbox Part6_Text_202, MSGBOX_DEFAULT
	releaseall
	end
Part6_Adjuster_Extreme::
	msgbox Part6_Text_203, MSGBOX_DEFAULT
	releaseall
	end

Part6_Adj_Sun:
	.string "晴天$"
Part6_Adj_Rain:
	.string "降雨$"
Part6_Adj_Sand:
	.string "沙暴$"
Part6_Adj_Snow:
	.string "下雪$"
Part6_Adj_Reset:
	.string "恢复正常$"
Part6_Adj_Cancel:
	.string "取消$"

Part6_AdjusterTeach::
	lock
	faceplayer
	goto_if_set FLAG_PART6_ADJUSTER_TEACH_REWARD, Part6_AdjusterTeach_Done
	goto_if_unset FLAG_PART6_ADJUSTER_RECEIVED, Part6_AdjusterTeach_Idle
	special Part6_CountAdjusterWeathers
	goto_if_ge VAR_RESULT, 3, Part6_AdjusterTeach_Reward
	msgbox Part6_Text_204, MSGBOX_DEFAULT
	release
	end
Part6_AdjusterTeach_Reward::
	msgbox Part6_Text_205, MSGBOX_DEFAULT
	giveitem ITEM_PP_MAX, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	setflag FLAG_PART6_ADJUSTER_TEACH_REWARD
	release
	end
Part6_AdjusterTeach_Idle::
	msgbox Part6_Text_206, MSGBOX_DEFAULT
	release
	end
Part6_AdjusterTeach_Done::
	msgbox Part6_Text_207, MSGBOX_DEFAULT
	release
	end

Part6_Carpenter::
	lock
	faceplayer
	goto_if_set FLAG_PART6_PLANK_DONE, Part6_Carpenter_Done
	checkitem ITEM_DRIFT_PLANK, 3
	goto_if_eq VAR_RESULT, TRUE, Part6_Carpenter_Return
	msgbox Part6_Text_208, MSGBOX_DEFAULT
	release
	end
Part6_Carpenter_Return::
	msgbox Part6_Text_209, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	removeitem ITEM_DRIFT_PLANK, 3
	setflag FLAG_PART6_PLANK_DONE
	release
	end
Part6_Carpenter_Done::
	msgbox Part6_Text_210, MSGBOX_DEFAULT
	release
	end

Part6_Plank0::
	lockall
	goto_if_set FLAG_PART6_PLANK_1, Part6_QuietEnd
	msgbox Part6_Text_211, MSGBOX_DEFAULT
	giveitem ITEM_DRIFT_PLANK, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_PLANK_1
	special StoryRefreshPickupMarkers
	releaseall
	end

Part6_Plank1::
	lockall
	goto_if_set FLAG_PART6_PLANK_2, Part6_QuietEnd
	msgbox Part6_Text_212, MSGBOX_DEFAULT
	giveitem ITEM_DRIFT_PLANK, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_PLANK_2
	special StoryRefreshPickupMarkers
	releaseall
	end

Part6_Plank2::
	lockall
	goto_if_set FLAG_PART6_PLANK_3, Part6_QuietEnd
	msgbox Part6_Text_213, MSGBOX_DEFAULT
	giveitem ITEM_DRIFT_PLANK, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_PLANK_3
	special StoryRefreshPickupMarkers
	releaseall
	end

Part6_PacResident::
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Part6_PacResident_After
	goto_if_ge VAR_SOOTOPOLIS_CITY_STATE, 4, Part6_PacResident_Tower
	msgbox Part6_Text_214, MSGBOX_NPC
	end
Part6_PacResident_Tower::
	msgbox Part6_Text_215, MSGBOX_NPC
	end
Part6_PacResident_After::
	msgbox Part6_Text_216, MSGBOX_NPC
	end

Part6_PacFisherHint::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_PacFisherHint_Crisis
	msgbox Part6_Text_217, MSGBOX_NPC
	end
Part6_PacFisherHint_Crisis::
	msgbox Part6_Text_218, MSGBOX_NPC
	end

Part6_ArcheShip::
	msgbox Part6_Text_219, MSGBOX_SIGN
	end

Part6_Saviel::
	lock
	faceplayer
	goto_if_unset FLAG_PART4_RELICANTH_RECEIVED, Part6_Saviel_Native
	goto_if_set FLAG_SYS_WEATHER_CTRL, Part6_Saviel_Crisis
	goto_if_set FLAG_PART6_SAVIEL_REGI_REWARD, Part6_Saviel_Quiet
	special Part6_CheckRegisCaught
	goto_if_eq VAR_RESULT, TRUE, Part6_Saviel_Regi
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Part6_Saviel_Tower
Part6_Saviel_Native::
	release
	goto Part4_QuietVisitor
Part6_Saviel_Crisis::
	msgbox Part6_Text_220, MSGBOX_DEFAULT
	release
	end
Part6_Saviel_Tower::
	msgbox Part6_Text_221, MSGBOX_DEFAULT
	release
	end
Part6_Saviel_Regi::
	msgbox Part6_Text_222, MSGBOX_DEFAULT
	checkitemspace ITEM_ABILITY_PATCH, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	checkitemspace ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_ABILITY_PATCH, 1
	giveitem ITEM_RARE_CANDY, 1
	setflag FLAG_PART6_SAVIEL_REGI_REWARD
	msgbox Part6_Text_223, MSGBOX_DEFAULT
	release
	end
Part6_Saviel_Quiet::
	goto StoryA_Xavier
	goto_if_set FLAG_SYS_GAME_CLEAR, Part7_SavielChampion
	msgbox Part6_Text_224, MSGBOX_DEFAULT
	release
	end

Part6_SealedChamberGlint::
	lockall
	goto_if_unset FLAG_REGI_DOORS_OPENED, Part6_SealedChamberGlint_Plain
	goto_if_set FLAG_PART6_SEALED_CHAMBER_PP_MAX, Part6_SealedChamberGlint_Plain
	msgbox Part6_Text_225, MSGBOX_DEFAULT
	giveitem ITEM_PP_MAX, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_SEALED_CHAMBER_PP_MAX
	releaseall
	end
Part6_SealedChamberGlint_Plain::
	msgbox Part6_Text_226, MSGBOX_DEFAULT
	releaseall
	end

Part6_SkyGuard131::
	trainerbattle_single TRAINER_PART6_SKY_GUARD_131, Part6_Text_227, Part6_Text_228, Part6_SkyGuard131_After
	goto Part6_SkyGuard131_After
Part6_SkyGuard131_After::
	msgbox Part6_Text_229, MSGBOX_NPC
	end

Part6_SkySecurity::
	trainerbattle_single TRAINER_PART6_SKY_SECURITY, Part6_Text_230, Part6_Text_231
	msgbox Part6_Text_232, MSGBOX_AUTOCLOSE
	end

Part6_SkyLifeResearcher::
	trainerbattle_single TRAINER_PART6_SKY_LIFE_RESEARCHER, Part6_Text_233, Part6_Text_234
	msgbox Part6_Text_235, MSGBOX_AUTOCLOSE
	end

Part6_SkyDuo::
	trainerbattle_double TRAINER_PART6_SKY_TECH_GUARD, Part6_Text_236, Part6_Text_237, Part6_Text_238
	msgbox Part6_Text_239, MSGBOX_AUTOCLOSE
	end

Part6_SkyDuoGuard::
	msgbox Part6_Text_240, MSGBOX_NPC
	end

Part6_SkySenior::
	trainerbattle_single TRAINER_PART6_SKY_SENIOR_RESEARCHER, Part6_Text_241, Part6_Text_242
	msgbox Part6_Text_243, MSGBOX_AUTOCLOSE
	end

Part6_SkyFrame::
	goto_if_set FLAG_PART6_SKY_PILLAR_ARCHE_LEFT, Part6_SkyFrame_After
	msgbox Part6_Text_244, MSGBOX_SIGN
	end
Part6_SkyFrame_After::
	msgbox Part6_Text_245, MSGBOX_SIGN
	end

Part6_SkyDrill::
	goto_if_set FLAG_PART6_SKY_PILLAR_ARCHE_LEFT, Part6_SkyDrill_After
	msgbox Part6_Text_246, MSGBOX_SIGN
	end
Part6_SkyDrill_After::
	msgbox Part6_Text_247, MSGBOX_SIGN
	end

Part6_SkyBarrier::
	goto_if_set FLAG_PART6_SKY_PILLAR_ARCHE_LEFT, Part6_SkyBarrier_After
	msgbox Part6_Text_248, MSGBOX_SIGN
	end
Part6_SkyBarrier_After::
	msgbox Part6_Text_249, MSGBOX_SIGN
	end

Part6_SkyAltaria::
	lock
	faceplayer
	playmoncry SPECIES_ALTARIA, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part6_Text_250, MSGBOX_DEFAULT
	release
	end

Part6_SkyAltariaDevice::
	lockall
	goto_if_set FLAG_PART6_SKY_ALTARIA_FREED, Part6_SkyAltariaDevice_After
	goto_if_set FLAG_TEMP_2, Part6_SkyAltariaDevice_Free
	msgbox Part6_Text_251, MSGBOX_DEFAULT
	msgbox Part6_Text_252, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	releaseall
	end
Part6_SkyAltariaDevice_Free::
	msgbox Part6_Text_253, MSGBOX_DEFAULT
	playmoncry SPECIES_ALTARIA, CRY_MODE_NORMAL
	waitmoncry
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PART6_SKY_ALTARIA
	setflag FLAG_PART6_SKY_ALTARIA_FREED
	fadescreen FADE_FROM_BLACK
	msgbox Part6_Text_254, MSGBOX_DEFAULT
	msgbox Part6_Text_255, MSGBOX_DEFAULT
	msgbox Part6_Text_256, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 1
	releaseall
	end
Part6_SkyAltariaDevice_After::
	goto_if_set FLAG_PART6_SKY_PILLAR_ARCHE_LEFT, Part6_SkyAltariaDevice_Gone
	msgbox Part6_Text_257, MSGBOX_DEFAULT
	releaseall
	end
Part6_SkyAltariaDevice_Gone::
	msgbox Part6_Text_258, MSGBOX_DEFAULT
	releaseall
	end

Part6_SkyAltariaResearcher::
	msgbox Part6_Text_259, MSGBOX_NPC
	end

Part6_Evelyn::
	trainerbattle_single TRAINER_PART6_EVELYN, Part6_Text_260, Part6_Text_261, Part6_Evelyn_After
	goto Part6_Evelyn_After

Part6_Evelyn_After::
	lockall
	msgbox StoryA_Text_EvelynAfter1, MSGBOX_DEFAULT
	msgbox StoryA_Text_EvelynAfter2, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PART6_EVELYN
	removeobject LOCALID_PART6_EVELYN_AIDE
	setflag FLAG_PART6_SKY_PILLAR_ARCHE_LEFT
	fadescreen FADE_FROM_BLACK
	releaseall
	end

Part6_EvelynAide::
	msgbox Part6_Text_266, MSGBOX_NPC
	end

Part6_SkySampleDevice::
	goto_if_set FLAG_PART6_SKY_PILLAR_ARCHE_LEFT, Part6_SkySampleDevice_After
	msgbox Part6_Text_267, MSGBOX_SIGN
	end
Part6_SkySampleDevice_After::
	msgbox Part6_Text_268, MSGBOX_SIGN
	end

Part6_SkyBrokenBox::
	lockall
	goto_if_unset FLAG_PART6_SKY_PILLAR_ARCHE_LEFT, Part6_SkyBrokenBox_Closed
	goto_if_set FLAG_PART6_SKY_BOX_PP_UP, Part6_SkyBrokenBox_Empty
	msgbox Part6_Text_269, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFullAll
	setflag FLAG_PART6_SKY_BOX_PP_UP
	releaseall
	end
Part6_SkyBrokenBox_Closed::
	msgbox Part6_Text_270, MSGBOX_DEFAULT
	releaseall
	end
Part6_SkyBrokenBox_Empty::
	msgbox Part6_Text_271, MSGBOX_DEFAULT
	releaseall
	end

Part6_RookieCivilian::
	lock
	faceplayer
	msgbox Part6_Text_272, MSGBOX_DEFAULT
	msgbox Part6_Text_273, MSGBOX_DEFAULT
	msgbox Part6_Text_274, MSGBOX_DEFAULT
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part6_Text_275, MSGBOX_DEFAULT
	release
	end

Part6_RookieJigglypuff::
	lock
	faceplayer
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part6_ReviewResearcher::
	lock
	faceplayer
	goto_if_set FLAG_PART6_REVIEW_DONE, Part6_ReviewResearcher_Done
	goto_if_unset FLAG_BADGE08_GET, Part6_ReviewResearcher_Busy
	goto_if_set FLAG_PART6_REVIEW_ASKED, Part6_ReviewResearcher_Check
	msgbox Part6_Text_276, MSGBOX_DEFAULT
	setflag FLAG_PART6_REVIEW_ASKED
	release
	end
Part6_ReviewResearcher_Check::
	special Part6_CountReview
	goto_if_lt VAR_RESULT, 4, Part6_ReviewResearcher_Wait
	msgbox Part6_Text_277, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_MAX, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	checkitemspace ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part6_BagFull
	giveitem ITEM_PP_MAX, 1
	giveitem ITEM_RARE_CANDY, 1
	addmoney 25000
	msgbox Part6_Text_278, MSGBOX_DEFAULT
	setflag FLAG_PART6_REVIEW_DONE
	release
	end
Part6_ReviewResearcher_Wait::
	msgbox Part6_Text_279, MSGBOX_DEFAULT
	release
	end
Part6_ReviewResearcher_Busy::
	msgbox Part6_Text_280, MSGBOX_DEFAULT
	release
	end
Part6_ReviewResearcher_Done::
	msgbox Part6_Text_281, MSGBOX_DEFAULT
	release
	end

Part6_ReviewNode0::
	lockall
	msgbox Part6_Text_282, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART6_REVIEW_ASKED, Part6_QuietEnd
	goto_if_set FLAG_PART6_REVIEW_119, Part6_QuietEnd
	setflag FLAG_PART6_REVIEW_119
	special Part6_CountReview
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox Part6_Text_283, MSGBOX_DEFAULT
	releaseall
	end

Part6_ReviewNode1::
	lockall
	msgbox Part6_Text_284, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART6_REVIEW_ASKED, Part6_QuietEnd
	goto_if_set FLAG_PART6_REVIEW_SLATEPORT, Part6_QuietEnd
	setflag FLAG_PART6_REVIEW_SLATEPORT
	special Part6_CountReview
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox Part6_Text_285, MSGBOX_DEFAULT
	releaseall
	end

Part6_ReviewNode2::
	lockall
	msgbox Part6_Text_286, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART6_REVIEW_ASKED, Part6_QuietEnd
	goto_if_set FLAG_PART6_REVIEW_LILYCOVE, Part6_QuietEnd
	setflag FLAG_PART6_REVIEW_LILYCOVE
	special Part6_CountReview
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox Part6_Text_287, MSGBOX_DEFAULT
	releaseall
	end

Part6_ReviewNode3::
	lockall
	msgbox Part6_Text_288, MSGBOX_DEFAULT
	goto_if_unset FLAG_PART6_REVIEW_ASKED, Part6_QuietEnd
	goto_if_set FLAG_PART6_REVIEW_MOSSDEEP, Part6_QuietEnd
	setflag FLAG_PART6_REVIEW_MOSSDEEP
	special Part6_CountReview
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox Part6_Text_289, MSGBOX_DEFAULT
	releaseall
	end

Part6_Text_001:
	.string "背包已经满了。整理一下再来吧。$"

Part6_Text_002:
	.string "啊……又见面了。\n今天上面没让我拦着你。\p你想进去就进去吧，\n我不会挡路的。$"

Part6_Text_003:
	.string "说实话，他们要在里面做什么，\n我到现在也没完全听懂。\p我只知道，这一次\n我一点都高兴不起来。$"

Part6_Text_004:
	.string "大家都撤走了……\n这一次，我知道他们去了哪里。$"

Part6_Text_005:
	.string "可是，我不想再追上去了。$"

Part6_Text_006:
	.string "走吧，胖丁，我们先离开这里。\p……下次再见面的时候，\n我大概就不会穿这身制服了。$"

Part6_Text_007:
	.string "背包已经满了。整理一下再来吧。$"

Part6_Text_008:
	.string "这一带的海水比别处暖和得多，\n岩石缝里不停地冒出气泡。$"

Part6_Text_009:
	.string "已记录水下异常点：{STR_VAR_1}/3。$"

Part6_Text_010:
	.string "这里的水流比周围急得多，\n可附近的地形并没有什么变化。$"

Part6_Text_011:
	.string "已记录水下异常点：{STR_VAR_1}/3。$"

Part6_Text_012:
	.string "装置的读数完全不正常，\n屏幕上的数字一直在乱跳。\p附近的宝可梦好像也有些躁动。$"

Part6_Text_013:
	.string "已记录水下异常点：{STR_VAR_1}/3。$"

Part6_Text_014:
	.string "三个点全都有异常？\n高温、强流，还有乱跳的读数……\p这下麻烦大了。之前的资料\n我得全部重新整理一遍。\p谢谢你帮我跑了这一趟，\n这些是调查的谢礼。$"

Part6_Text_015:
	.string "水温、海流，还有那组怪读数，\n我都整理好寄给天气研究所了。\p希望他们能看出点名堂来。$"

Part6_Text_016:
	.string "色彩鲜艳的珊瑚一片连着一片，\n小宝可梦在缝隙间钻进钻出。$"

Part6_Text_017:
	.string "海底散落着几只腐蚀的货箱，\n大部分都已经打不开了。$"

Part6_Text_018:
	.string "一根古老的石柱立在海底，\n表面的纹路已经看不清了。$"

Part6_Text_019:
	.string "一台装置牢牢固定在海床上，\n外壳上印着阿尔刻的编号。$"

Part6_Text_020:
	.string "你说海底那台机器？\n前几天才有人来装上的。\p到底是干什么用的，\n也没人跟我们这些游泳的说一声。$"

Part6_Text_021:
	.string "这一带的海底很深。\p不会潜水的话，\n就只能在海面上看看了。$"

Part6_Text_022:
	.string "哦，你已经会潜水了？\p这片海的西北边，海底有一大片\n特别漂亮的珊瑚。\p我女儿还潜不了那么深。\n你要是看到了，回来讲给她听听吧。$"

Part6_Text_023:
	.string "我女儿也想下去看珊瑚，\n可她还潜不了那么深。\p等她再长大一点吧。$"

Part6_Text_024:
	.string "看到珊瑚了？\p快去跟她讲讲吧，\n她肯定等不及了。$"

Part6_Text_025:
	.string "下次我带她去浅一点的地方，\n亲眼看看海里的样子。$"

Part6_Text_026:
	.string "爸爸说，海底下特别好看！\n我也好想去看看。$"

Part6_Text_027:
	.string "你真的去看珊瑚了吗？\n那里真的很好看吗？$"

Part6_Text_028:
	.string "哇！等我长大了，\n我也要潜下去看！$"

Part6_Text_029:
	.string "诶……很黑吗……$"

Part6_Text_030:
	.string "父亲：哈哈，这倒也没说错。\n深海里的光线本来就暗。$"

Part6_Text_031:
	.string "父亲：谢谢你陪她聊这些。\p这是我在海边捡到的，\n不嫌弃的话就收下吧。$"

Part6_Text_032:
	.string "我在练习憋气！\n已经能憋十秒了！$"

Part6_Text_033:
	.string "色彩鲜艳的珊瑚一片连着一片。\n应该就是那位父亲说的地方了。$"

Part6_Text_034:
	.string "我年轻的时候，天天往海底下跑。\p现在耳朵受不了水压，\n只能在这儿看看海了。\p我以前在那片珊瑚附近，\n弄丢过一盏旧潜水灯。\p珊瑚就在这片海西南边的海底。\n你要是潜下去，能帮我找找吗？$"

Part6_Text_035:
	.string "还真找着了！\n我还以为早被海水冲走了。\p这些你拿去吧，\n潜水的时候用得着。$"

Part6_Text_036:
	.string "年轻时总想着往更深的地方去。\n现在坐在这里看海，也挺好。$"

Part6_Text_037:
	.string "珊瑚缝里卡着一盏旧潜水灯。$"

Part6_Text_038:
	.string "这里没有别的东西了。$"

Part6_Text_039:
	.string "这只呆呆兽每天都坐在这儿。\n有时候我觉得，它比我还懂海。\p对了，我的潮流记录仪\n被浪冲到海底去了。\p就沉在这座小岛东边的深水带底下，\n珊瑚旁边。你能帮我捞回来吗？$"

Part6_Text_040:
	.string "找到了？太好了！\p……你看，它比我还高兴。\p这块石头是我们在礁石上捡的，\n送给你吧。$"

Part6_Text_041:
	.string "今天的海流很平稳。\n它又在这儿坐了一整天。$"

Part6_Text_042:
	.string "岩石缝里卡着一台小仪器，\n是潮流记录仪。$"

Part6_Text_043:
	.string "这里没有别的东西了。$"

Part6_Text_044:
	.string "刚才那阵浪，\n把我的工具箱卷到海里去了。\p里面没什么值钱东西，\n可没了它，我什么都修不了。\p就沉在小岛西北边那块深色海水\n底下。你会潜水的话，帮我捞一下吧？$"

Part6_Text_045:
	.string "居然真找回来了！\n泡成这样，工具居然还能用。\p这些你收着，\n算是我的一点心意。$"

Part6_Text_046:
	.string "浮标修好了。\n今晚航道上的灯能亮了。$"

Part6_Text_047:
	.string "沙地上半埋着一个工具箱。$"

Part6_Text_048:
	.string "这里没有别的东西了。$"

Part6_Text_049:
	.string "海面下隐约能看到断掉的船板。\p要潜下去看看吗？$"

Part6_Text_050:
	.string "断裂的船板、生锈的船锚……\n看起来已经沉在这里很久了。\p其中一只货箱还能打开。$"

Part6_Text_051:
	.string "海面下好像沉着什么东西。\n要是会潜水，就能下去看看了。$"

Part6_Text_052:
	.string "沉船的残骸静静地躺在海底。$"

Part6_Text_053:
	.string "我本来是来调查附近岩层的。\p结果昨天一阵急流，\n把我的样本箱冲走了。\p里面装着一块化石样本，\n它可比我这个人值钱多了。\p箱子漂到这个木台南边去了，\n海面上有个亮点的地方就是。\p你会潜水的话，帮我捞上来吧？$"

Part6_Text_054:
	.string "完整无损！\n我连损失报告都准备好了。\p……咦，箱子里还混着一块怪石头。\n跟我的研究没关系，你拿着吧。$"

Part6_Text_055:
	.string "这块化石的年代比我想的还要早。\n回去又有得忙了。$"

Part6_Text_056:
	.string "海底好像卡着一个箱子。\p要潜下去看看吗？$"

Part6_Text_057:
	.string "岩缝里卡着一个防水样本箱。$"

Part6_Text_058:
	.string "海草后面有一道狭窄的裂隙，\n上方似乎有光透下来。\p要顺着裂隙往上浮吗？$"

Part6_Text_059:
	.string "脚下的水道连着来时的海沟。\p要潜回海里吗？$"

Part6_Text_060:
	.string "水君轻盈地跃过水面，\n消失在了洞窟深处。\p水面又恢复了平静。$"

Part6_Text_061:
	.string "我是阿尔刻环境系统研究部的负责人，\n莱因。\p……你就是最近在丰缘到处跑的那位\n训练家吧。$"

Part6_Text_062:
	.string "莱因：119号道路的雨量、124号水路\n的水温、还有这几周的大气数据——\p全都在往同一个方向偏离正常值。\n这不是巧合。$"

Part6_Text_063:
	.string "助手：负责人，要不要先暂停观测？\n设备的读数也开始不稳定了。$"

Part6_Text_064:
	.string "莱因：设备还能用，就继续记录。\p等它真坏了再换。现在停下来，\n我们就会漏掉最关键的那一段。$"

Part6_Text_065:
	.string "助手：那……要先报告联盟吗？$"

Part6_Text_066:
	.string "莱因：早上就报了。\p他们什么时候看完报告，那是他们\n的事。我们这边不能等。$"

Part6_Text_067:
	.string "莱因：海底的记录？给我看看。\p……水温偏高，海流方向异常，\n还有一组无法解释的能量读数。$"

Part6_Text_068:
	.string "莱因：很好。$"

Part6_Text_069:
	.string "助手：这……怎么看都不算好吧？$"

Part6_Text_070:
	.string "莱因：我说的是这份记录很好。\n现象本身当然很糟。$"

Part6_Text_071:
	.string "助手：原始数据要发给天气研究所吗？$"

Part6_Text_072:
	.string "莱因：发处理过的版本。$"

Part6_Text_073:
	.string "助手：那原始记录呢？$"

Part6_Text_074:
	.string "莱因：留在内部数据库。\n没有我的签字，谁也不准调出来。$"

Part6_Text_075:
	.string "莱因：很多人觉得，只要是自然发生的\n事，就只能默默接受。\p可失控的自然，并不比失控的机器\n更高贵。$"

Part6_Text_076:
	.string "莱因：数据还在变化。\p……你要是没别的事，就别挡着屏幕。$"

Part6_Text_077:
	.string "负责人一盯上数据就忘了吃饭……\n这份便当我已经热了三次了。\p负责人在128号水路东侧还架了设备，\n就在礁石带北边那座浅滩小岛上。$"

Part6_Text_078:
	.string "莱因：最后一组传感器装好了，\n只差高强度战斗下的环境扰动数据。\p你来当这个数据源正合适。\n打一场，可以吗？$"

Part6_Text_079:
	.string "莱因：Mega进化？\n那不是今天的测试项目。$"

Part6_Text_080:
	.string "莱因：传感器启动，记录开始。$"

Part6_Text_081:
	.string "莱因：……够了，数据已经足够。$"

Part6_Text_082:
	.string "莱因：随你。\n想打的时候再来找我。$"

Part6_Text_083:
	.string "莱因：战斗数据收集完毕。\p你比仪器麻烦多了。\n……不过也有用得多。\p这是测试报酬，拿着。$"

Part6_Text_084:
	.string "莱因：岛上这边的数据正常。\n接下来要看海底的情况了。$"

Part6_Text_085:
	.string "渔夫：那台机器正好挡住了\n我平时下网的地方！\p装的时候，也没人来问过我一声。$"

Part6_Text_086:
	.string "技术员：安装手续是正规审批过的。$"

Part6_Text_087:
	.string "渔夫：谁批的手续？$"

Part6_Text_088:
	.string "技术员：海洋观测项目的手续。$"

Part6_Text_089:
	.string "渔夫：我不管什么项目，给我拆掉！$"

Part6_Text_090:
	.string "莱因：……再留一天就够了。$"

Part6_Text_091:
	.string "渔夫：我不同意！$"

Part6_Text_092:
	.string "莱因：我知道你不会同意。$"

Part6_Text_093:
	.string "莱因：你会潜水？那正好，帮我校准\n三台海床观测装置。\p两台就在这座小岛南边，\n那条深水带的正下方。\p最后一台在128号水路西边——\n有一圈浅滩围着一片深色的海水，\p从那片深水潜下去就能看到。\n装置顶上有灯，很好认。\p三台都校准完，数据没问题，\n我就把这里的设备拆掉。$"

Part6_Text_098:
	.string "渔夫：那个负责人说校准完就拆。\p我就在这儿盯着，\n看他说话算不算数。$"

Part6_Text_099:
	.string "渔夫：……下网的地方是没了。\p可那天要不是那台机器报警，\n我的船也没了。$"

Part6_Text_100:
	.string "技术员：观测项目的手续都是齐的。\p……只是从头到尾，\n都没人去跟渔民们说一声。$"

Part6_Text_101:
	.string "莱因：一共三台。小岛南边的深水带\n下面两台，128号浅滩圈中间一台。$"

Part6_Text_102:
	.string "船工：这一带的海流说变就变。\p有台机器能提前提醒一声，\n其实也不坏。$"

Part6_Text_103:
	.string "海床上立着一台阿尔刻的观测装置，\n顶上的指示灯一闪一闪。\p照着侧面的说明完成了校准。$"

Part6_Text_104:
	.string "海床上立着一台阿尔刻的观测装置，\n顶上的指示灯一闪一闪。\p照着侧面的说明完成了校准。$"

Part6_Text_105:
	.string "海床上立着一台阿尔刻的观测装置，\n顶上的指示灯一闪一闪。\p照着侧面的说明完成了校准。\p……屏幕上突然跳出红色警报！\n前方海域出现异常强海流！\p海面上传来船只紧急停航的汽笛声。$"

Part6_Text_106:
	.string "海床上立着一台阿尔刻的观测装置，\n顶上的指示灯一闪一闪。$"

Part6_Text_107:
	.string "莱因：我在看数据。\n有事的话，等会儿再说。$"

Part6_Text_108:
	.string "工作人员：缓冲设备的范围\n已经撑到极限了！$"

Part6_Text_109:
	.string "莱因：知道了。优先保住城区。$"

Part6_Text_110:
	.string "助手：琉璃市那边怎么办？$"

Part6_Text_111:
	.string "莱因：我们的设备，\n应付不了那种量级。$"

Part6_Text_112:
	.string "助手：手上还剩两套完整设备。\n凯那市和暮水镇都提出了申请。$"

Part6_Text_113:
	.string "莱因：送去凯那。$"

Part6_Text_114:
	.string "助手：那暮水镇呢？$"

Part6_Text_115:
	.string "莱因：暮水人口少，\n优先组织撤离。$"

Part6_Text_116:
	.string "助手：可很多居民不愿意离开。$"

Part6_Text_117:
	.string "莱因：那是另一个问题。\n先把能做的事做完。$"

Part6_Text_118:
	.string "莱因：气压恢复的那一瞬间，\n我们全都记录下来了。\p……原来是这样。$"

Part6_Text_119:
	.string "莱因：结束了。\n……至少外面已经结束了。\p我们这边的工作才刚开始。\p这次的数据，\n是过去从来没有记录到过的。$"

Part6_Text_120:
	.string "助手：如果以后再发生这种事……$"

Part6_Text_121:
	.string "莱因：如果下次还得等六个部门\n挨个审批，我们照样会慢一步。$"

Part6_Text_122:
	.string "助手：联盟不可能把控制权\n全部交给一家机构的。$"

Part6_Text_123:
	.string "莱因：那就让他们先看完报告\n再说。$"

Part6_Text_124:
	.string "莱因：最近有几组天气变化，\n变化得太干净了。\p……是人为的？\p……算了，数据能用就行。$"

Part6_Text_125:
	.string "莱因：报告还没写完，\n有事下次再说。$"

Part6_Text_126:
	.string "最近总部的灯一到晚上也不关，\n大家都在加班。$"

Part6_Text_127:
	.string "现在环境数据全面超标了。\p以前一直不同意安装传感器的地方，\n这下全都批了。$"

Part6_Text_128:
	.string "审批快得吓人。\n这种天气，谁还会拒绝呢？\p……这些装上去的设备，\n大概也不会再拆了吧。$"

Part6_Text_129:
	.string "这种天气，\n船根本不敢正常出港啊。$"

Part6_Text_130:
	.string "港口总算重新开放了。\p积压的货这几天都得加班送，\n我的腰都快断了。$"

Part6_Text_131:
	.string "仓库里的货越堆越多了。\n再这样下去，连放的地方都没了。$"

Part6_Text_132:
	.string "阿尔刻送来的缓冲设备\n就装在码头上。\p外面还是乱成一团，\n至少这里的设备还能正常运转。$"

Part6_Text_133:
	.string "缓冲设备撤走了一半。\n剩下的传感器，说是以后还用得上。$"

Part6_Text_134:
	.string "外面的船都进不了港，\n仓库已经快堆满了。$"

Part6_Text_135:
	.string "环境数据全部超出正常范围。\n今天谁都别想准时下班了。$"

Part6_Text_136:
	.string "这已经超出我们有记录以来的\n所有范围了。$"

Part6_Text_137:
	.string "预测模型完全失效了。\n我们只能一小时一小时地记录。$"

Part6_Text_138:
	.string "今天温泉的水温一直忽冷忽热的，\n泡得人心里不踏实。$"

Part6_Text_139:
	.string "山那边的气息很不对劲。\n我活了这么多年，从没见过这样。$"

Part6_Text_140:
	.string "卫星观测显示，\n云层的变化快得不正常。$"

Part6_Text_141:
	.string "警报一直响个不停。\n可关掉警报也没用，读数是真的。$"

Part6_Text_142:
	.string "海浪越来越大了，\n浮桥一直晃个不停。$"

Part6_Text_143:
	.string "再这样下去，\n今晚都不知道房子会漂到哪里去。$"

Part6_Text_144:
	.string "这里堆放着大量潜水装备。$"

Part6_Text_145:
	.string "防水箱里装着海图和测量仪器。$"

Part6_Text_146:
	.string "地图上标出了洞窟最深处的位置，\n好几条路线被反复修改过。$"

Part6_Text_147:
	.string "墙上的纹路，像是在描绘云层。$"

Part6_Text_148:
	.string "三个巨大的身影刻在墙上，\n已经被岁月磨得模糊不清。$"

Part6_Text_149:
	.string "墙的最高处，\n留着一道细长的刻痕。$"

Part6_Text_150:
	.string "这些鱼什么时候开饭，\n它们心里清楚得很。\p我要是晚来五分钟，\n它们都会瞪我。$"

Part6_Text_151:
	.string "……今天一条都没来。\n它们也知道外面不对劲吧。$"

Part6_Text_152:
	.string "昨天它们一条都没来，\n今天全都回来了。$"

Part6_Text_153:
	.string "住在这里最大的麻烦？\p朋友约你去对岸，\n看着就在眼前。\p真走起来，可一点都不近。$"

Part6_Text_154:
	.string "我在水里睁开眼睛了！$"

Part6_Text_155:
	.string "所以现在眼睛还红红的。$"

Part6_Text_156:
	.string "岸边立着一根空旗杆。$"

Part6_Text_157:
	.string "“环境危险区域”\n“非授权人员禁止进入”$"

Part6_Text_158:
	.string "路障已经撤掉了。\p旁边留下了一台传感器，\n仍在持续记录琉璃市的环境数据。$"

Part6_Text_159:
	.string "这条岸边谁都能走。\n我每天都从这儿绕去对面。$"

Part6_Text_160:
	.string "居民：这条路以前谁都能走！$"

Part6_Text_161:
	.string "阿尔刻员工：现在不行。$"

Part6_Text_162:
	.string "居民：是谁让你们封的？$"

Part6_Text_163:
	.string "阿尔刻员工：根据应急协议。$"

Part6_Text_164:
	.string "居民：谁定的应急协议？$"

Part6_Text_165:
	.string "阿尔刻员工：……阿尔刻定的。$"

Part6_Text_166:
	.string "那台传感器？\n他们说以后也用得上。\p市里好像已经同意留下了。$"

Part6_Text_167:
	.string "丰缘环境应急协议正在执行中。\n前面风浪太大，请绕行。$"

Part6_Text_168:
	.string "普通药品还够用。\p可是有一箱急救用品，\n卡在进出琉璃的那条海底水道里了。\p你会潜水的话，\n能帮忙找一找吗？$"

Part6_Text_169:
	.string "这里是临时诊疗点。\n今天来的宝可梦不多，还算清闲。$"

Part6_Text_170:
	.string "太好了！\n还有几个孩子一直在等着处理伤口。$"

Part6_Text_171:
	.string "最忙的时候总算过去了。\p这些是在旧医疗箱里找到的，\n放在这里也没人用，你拿着吧。$"

Part6_Text_172:
	.string "药箱真是帮了大忙。\p等外面平静下来，\n你再来一趟吧。$"

Part6_Text_173:
	.string "差不多娃娃终于能好好休息了。$"

Part6_Text_174:
	.string "水道的岩缝里卡着一个药箱。$"

Part6_Text_175:
	.string "这里没有别的东西了。$"

Part6_Text_176:
	.string "我的海豹球不见了……\p刚才还在这儿的，\n好像往东边滚过去了……$"

Part6_Text_177:
	.string "找到了！\n你跑到哪里去了嘛！$"

Part6_Text_178:
	.string "家长：真是太谢谢你了。\n这些潜水球，你拿去用吧。$"

Part6_Text_179:
	.string "这次我一定会抱紧它的。$"

Part6_Text_180:
	.string "今天终于可以出去玩了！$"

Part6_Text_181:
	.string "海豹球骨碌碌地滚了一圈，\n朝主人那边滚走了。$"

Part6_Text_182:
	.string "我昨天拍了好多照片，\n结果相机掉进水里了。\p相机坏了也就算了，\n可照片还在里面啊。\p大概是掉进了潜水进城的\n那条海底水道里……$"

Part6_Text_183:
	.string "还能开机！太好了。\p我还以为这趟旅行，\n什么都带不回去了。$"

Part6_Text_184:
	.string "回去以后我要把照片洗出来。\n有一张还拍到了你哦。$"

Part6_Text_185:
	.string "水底的沙子里埋着一台相机。$"

Part6_Text_186:
	.string "这里没有别的东西了。$"

Part6_Text_187:
	.string "听说去了天空之柱的人就是你。\p能一路走到那里的训练家，\n我很想跟你较量一下。$"

Part6_Text_188:
	.string "拔剑吧！$"

Part6_Text_189:
	.string "……够了，是我输了。$"

Part6_Text_190:
	.string "现在城里还有很多事要处理。\n等一切平静下来再说吧。$"

Part6_Text_191:
	.string "你懂得什么时候该进，\n什么时候该退。\p这块石头，就交给你了。$"

Part6_Text_192:
	.string "剑舞不是为了快，\n而是为了在对的时机出剑。$"

Part6_Text_193:
	.string "男子：哟，又见面了。\n你还真会往有意思的地方跑。$"

Part6_Text_194:
	.string "男子：极端的烈日，没完没了的暴雨，\n还有最后让一切平息下来的力量。\p这样的记录，\n平时可是想见都见不着。$"

Part6_Text_195:
	.string "男子：上次给你的东西，\n是用来改变宝可梦战斗形态的。\p这次的可不一样。$"

Part6_Text_196:
	.string "男子：它能对周围的环境\n做一点有限的调整。\p晴天、降雨，还有几种类似的天气。\n你可以自己试试看。$"

Part6_Text_197:
	.string "本原调律器只能影响普通的天气。\p特殊环境和强烈的异常天气，\n不会受到它的影响。$"

Part6_Text_198:
	.string "男子：所谓奇迹与技术，\n区别也许只是程度不同而已。$"

Part6_Text_199:
	.string "男子：你也亲眼见过了吧？\n自然本身，同样会失控。\p……怎么用这个东西，\n就由你自己决定了。$"

Part6_Text_200:
	.string "要调整成哪种天气？$"

Part6_Text_201:
	.string "本原调律器发出轻微的鸣响……\n周围的天气改变了。$"

Part6_Text_202:
	.string "这里无法调整天气。\n本原调律器只能在普通的户外使用。$"

Part6_Text_203:
	.string "强烈的异常天气压过了装置的作用，\n本原调律器没有反应。$"

Part6_Text_204:
	.string "设备总算恢复正常了。\p不过，有几组普通天气的数据\n还缺对照组。\p要是能在普通的户外，\n晴天、降雨、沙暴各记录一次就好了。$"

Part6_Text_205:
	.string "晴天、降雨、沙暴，\n三组数据都齐了！\p对照数据非常干净……\n谢谢你，这个送给你。$"

Part6_Text_206:
	.string "环境部门今天还在整理数据，\n大家都忙得团团转。$"

Part6_Text_207:
	.string "对照组已经归档完成了。$"

Part6_Text_208:
	.string "刚才那阵大浪，\n把好几块固定用的木板冲走了。\p少一两块还撑得住，\n再少就麻烦了。\p镇子西南边和东北边的海面上\n应该各漂着一块，\p还有一块被冲到了131号水路东段。\n你会冲浪的话，帮我捞回来吧。$"

Part6_Text_209:
	.string "正好三块！\n今晚不用担心整条路漂走了。\p这个你收着吧。$"

Part6_Text_210:
	.string "步道已经钉牢了。\n下次再来大浪也不怕了。$"

Part6_Text_211:
	.string "海面上漂着一块木板。$"

Part6_Text_212:
	.string "海面上漂着一块木板。$"

Part6_Text_213:
	.string "海面上漂着一块木板。$"

Part6_Text_214:
	.string "你说那个钓鱼的人？\n他来这儿好几天了。\p一天到晚也不怎么说话，\n就坐在那儿钓鱼。$"

Part6_Text_215:
	.string "昨天来了好多研究员。\p他们还给附近的船家塞钱，\n让大家暂时别靠近那座塔。$"

Part6_Text_216:
	.string "钱是给得不少。\n可那座塔又不是他们家的。$"

Part6_Text_217:
	.string "镇子西边的水流特别急。\p以前听老人们说，顺着那股水流\n往西走，能找到一个奇怪的潜水点。$"

Part6_Text_218:
	.string "这种天气，\n那个人居然还在钓鱼……$"

Part6_Text_219:
	.string "远处停着一艘研究船，\n船身上印着“ARCHE”。$"

Part6_Text_220:
	.string "……风变了。\n这几天，别出海。$"

Part6_Text_221:
	.string "东边那座塔上，最近吵得很。\n鱼都不肯咬钩了。$"

Part6_Text_222:
	.string "……那三间石室，\n你都走过了啊。\p这些，你拿着。$"

Part6_Text_223:
	.string "老头子能给的，就这些了。$"

Part6_Text_224:
	.string "……今天的海，挺安静。$"

Part6_Text_225:
	.string "一阵震动过后，\n石壁的缝隙里掉出了一件东西。$"

Part6_Text_226:
	.string "古老的石壁上刻满了点状的文字。$"

Part6_Text_227:
	.string "前方航线暂时封闭。\p……我已经说过了，\n前面不能过去。$"

Part6_Text_228:
	.string "……居然拦不住。$"

Part6_Text_229:
	.string "你还真要进去啊。\n算了，反正我也拦不住你。$"

Part6_Text_230:
	.string "这里是环境危险区域。\n上层正在进行实验，现在不能通过。$"

Part6_Text_231:
	.string "……拦不住啊。\n上头会记下这件事的。$"

Part6_Text_232:
	.string "你要上去就上去吧。\n我只是负责外围的安保。$"

Part6_Text_233:
	.string "复制、形态、生命结构……\n这座塔的数据比哪里都有意思。\p别来打扰我们。$"

Part6_Text_234:
	.string "百变怪的数据倒是采到了不少。$"

Part6_Text_235:
	.string "变身是最直接的复制。\n……可惜，它复制不了经验。$"

Part6_Text_236:
	.string "技术员：设备正在运转中。\n护卫：外人禁止靠近！$"

Part6_Text_237:
	.string "技术员：……设备没事吧？$"

Part6_Text_238:
	.string "技术员：想挑战我们两个，\n至少带两只宝可梦再来。$"

Part6_Text_239:
	.string "技术员：设备必须固定在石面上。\n之后我们会修复的。$"

Part6_Text_240:
	.string "这里外人禁止靠近。$"

Part6_Text_241:
	.string "你已经走到这里了？\n那就顺便留下一组战斗数据吧。$"

Part6_Text_242:
	.string "数据记录完成。$"

Part6_Text_243:
	.string "失败也是数据。\n只要记下来，就不算浪费。$"

Part6_Text_244:
	.string "金属固定架压在古老的刻纹上。$"

Part6_Text_245:
	.string "固定大型设备的地方，\n只剩下几道压痕。$"

Part6_Text_246:
	.string "石面上留着新鲜的钻孔痕迹。$"

Part6_Text_247:
	.string "钻孔还在，\n设备已经被拆走了。$"

Part6_Text_248:
	.string "“环境危险区域”\n“非授权人员禁止进入”$"

Part6_Text_249:
	.string "临时封锁牌倒在一旁，\n封锁已经解除了。$"

Part6_Text_250:
	.string "七夕青鸟身上贴着生命监测器\n和能量传感器，\p翅膀被临时固定带绑着，\n它正烦躁地扑腾着。$"

Part6_Text_251:
	.string "研究员：只是短时间固定而已。\n数据采完就会放了它。$"

Part6_Text_252:
	.string "研究员：……别碰那个。$"

Part6_Text_253:
	.string "{PLAYER}松开了固定带的卡扣。$"

Part6_Text_254:
	.string "七夕青鸟挣脱了束缚，\n飞出了塔外。$"

Part6_Text_255:
	.string "研究员：…………\p两个小时的数据……\n全都没了。$"

Part6_Text_256:
	.string "地上掉着一颗糖果。\n大概是研究员拿来安抚它的。$"

Part6_Text_257:
	.string "观测架上只剩下断开的固定带。$"

Part6_Text_258:
	.string "几根断掉的固定带留在地上。$"

Part6_Text_259:
	.string "别碰那台设备，\n里面的数据还在记录。$"

Part6_Text_260:
	.string "阿尔刻生命与进化研究负责人　伊芙琳\p你比我预计的早到了。\p我正在记录烈空坐苏醒的全过程。\n这样的数据，不会有第二次。\p我没有中止的打算。\n……看来，我们之间没有交涉的余地。$"

Part6_Text_261:
	.string "诱导程序，停止。$"

Part6_Text_266:
	.string "负责人正在进行最后一组记录。\n请不要靠近。$"

Part6_Text_267:
	.string "里面保存着微量的生物样本。\n标签上写着：鳞片、组织、能量谱。$"

Part6_Text_268:
	.string "只剩下几个固定支架和断线，\n设备已经被带走了。$"

Part6_Text_269:
	.string "撤离时留下的破损储存盒，\n里面还剩着一件东西。$"

Part6_Text_270:
	.string "贴着阿尔刻标签的储存盒。$"

Part6_Text_271:
	.string "空空如也的储存盒。$"

Part6_Text_272:
	.string "……嗨。\n这次见面，总算不用对战了。$"

Part6_Text_273:
	.string "好久没穿普通衣服了，\n反而有点不习惯。$"

Part6_Text_274:
	.string "我回去找过以前的朋友。\n他们问我最近都去哪儿了。\p……我没敢全说出来。$"

Part6_Text_275:
	.string "这孩子倒是一点压力都没有。\p接下来要做什么？我还没想好。\n先带它到处走走吧。$"

Part6_Text_276:
	.string "这次的异常天气留下了大量记录，\n我们正在确认各地的设备是否正常。\p能请你帮忙跑一趟吗？\n一共有四个地方。\p119号道路上，天气研究所的观测点，\n还有凯那市港口的监测设备。\p水静市海滨大道的观测点，\n还有绿岭宇宙中心里的联合观测站。\p每个地方调查一次设备就好。$"

Part6_Text_277:
	.string "四个地方全都恢复正常了。\n终于可以把这次事件正式归档了。$"

Part6_Text_278:
	.string "{PLAYER}还收到了25000元的\n调查经费。$"

Part6_Text_279:
	.string "还有几个地方没确认完。\p119号道路、凯那港口、\n水静海滨大道、绿岭观测站，\p每个地方都要调查一次。拜托了。$"

Part6_Text_280:
	.string "这阵子的数据实在太多了……\n我都快看不过来了。$"

Part6_Text_281:
	.string "归档完成。\n希望很久都不用再打开这份文件了。$"

Part6_Text_282:
	.string "天气研究所的观测点。\n研究所自己的设备已经恢复了。$"

Part6_Text_283:
	.string "设备运行正常。\p环境复查进度：{STR_VAR_1}/4。$"

Part6_Text_284:
	.string "港口的监测设备。\n港口已经重新开放了。$"

Part6_Text_285:
	.string "设备运行正常。\p环境复查进度：{STR_VAR_1}/4。$"

Part6_Text_286:
	.string "海滨大道的环境观测点。\n阿尔刻留下的设备还在运转。$"

Part6_Text_287:
	.string "设备运行正常。\p环境复查进度：{STR_VAR_1}/4。$"

Part6_Text_288:
	.string "联合观测站的终端。\n联合观测计划仍在继续。$"

Part6_Text_289:
	.string "设备运行正常。\p环境复查进度：{STR_VAR_1}/4。$"

