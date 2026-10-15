@ PART 5 generated scripts. Story spec: docs/story/PART5_DRAFT.md
Part5_BagFull::
	msgbox Part5_Text_001, MSGBOX_DEFAULT
	release
	end

Part5_QuietEnd::
	releaseall
	end

Part5_Traveler::
	trainerbattle_single TRAINER_PART5_TRAVELER, Part5_Text_002, Part5_Text_003
	msgbox Part5_Text_004, MSGBOX_AUTOCLOSE
	end

@ Story C: the two fans now fight together in ONE double battle, the existing
@ TRAINER_PART5_BUG_DUO (it has a real saved trainer flag). The old single
@ battles (TRAINER_PART5_SCYTHER_FAN / _SCIZOR_FAN) are no longer started and
@ no longer required.
Part5_ScytherFan::
Part5_ScizorFan::
Part5_BugFans_After::
	lock
	faceplayer
	goto_if_set FLAG_PART5_SCIZORITE, Part5_BugFans_Done
	goto_if_defeated TRAINER_PART5_BUG_DUO, Part5_BugFans_Reward
	trainerbattle_double TRAINER_PART5_BUG_DUO, StoryC_Text_BugFansIntro, Part5_Text_011, Part5_Text_012, Part5_BugFans_Reward
	release
	end

Part5_BugFans_NeedBoth::
	msgbox Part5_Text_013, MSGBOX_DEFAULT
	release
	end

Part5_BugFans_Reward::
	lock
	faceplayer
	msgbox Part5_Text_014, MSGBOX_DEFAULT
	giveitem ITEM_SCIZORITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setflag FLAG_PART5_SCIZORITE
	release
	end

Part5_BugFans_Done::
	msgbox Part5_Text_015, MSGBOX_DEFAULT
	release
	end

Part5_SafariResearcher::
	lock
	faceplayer
	msgbox Part5_Text_016, MSGBOX_DEFAULT
	goto_if_set FLAG_PART5_SAFARI_LUCKY_EGG, Part5_SafariResearcher_Bugs
	special Part5_CountSafariSpecies
	goto_if_ge VAR_RESULT, 3, Part5_SafariResearcher_Lucky
	msgbox Part5_Text_017, MSGBOX_DEFAULT
	release
	end

Part5_SafariResearcher_Lucky::
	msgbox Part5_Text_018, MSGBOX_DEFAULT
	giveitem ITEM_LUCKY_EGG, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setflag FLAG_PART5_SAFARI_LUCKY_EGG
	goto Part5_SafariResearcher_Bugs

Part5_SafariResearcher_Bugs::
	goto_if_set FLAG_PART5_PINSIRITE, Part5_SafariResearcher_BugsCheckDone
	goto Part5_SafariResearcher_BugsOpen
Part5_SafariResearcher_BugsCheckDone::
	goto_if_set FLAG_PART5_HERACRONITE, Part5_SafariResearcher_AllDone
Part5_SafariResearcher_BugsOpen::
	goto_if_defeated TRAINER_PART5_SAFARI_RESEARCHER, Part5_SafariResearcher_Stones
	special Part5_CheckHeracrossPinsirCaught
	goto_if_eq VAR_RESULT, TRUE, Part5_SafariResearcher_Challenge
	msgbox Part5_Text_019, MSGBOX_DEFAULT
	release
	end

Part5_SafariResearcher_Challenge::
	msgbox Part5_Text_020, MSGBOX_DEFAULT
	trainerbattle_single TRAINER_PART5_SAFARI_RESEARCHER, Part5_Text_021, Part5_Text_022, Part5_SafariResearcher_Stones
	release
	end

Part5_SafariResearcher_Stones::
	lock
	faceplayer
	msgbox Part5_Text_023, MSGBOX_DEFAULT
	goto_if_set FLAG_PART5_HERACRONITE, Part5_SafariResearcher_Stone2
	giveitem ITEM_HERACRONITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setflag FLAG_PART5_HERACRONITE
Part5_SafariResearcher_Stone2::
	goto_if_set FLAG_PART5_PINSIRITE, Part5_SafariResearcher_AllDone
	giveitem ITEM_PINSIRITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setflag FLAG_PART5_PINSIRITE
Part5_SafariResearcher_AllDone::
	msgbox Part5_Text_024, MSGBOX_DEFAULT
	release
	end

Part5_BallClerk::
	lock
	faceplayer
	message Part5_Text_025
	waitmessage
	pokemart Part5_Mart_Balls
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Part5_Mart_Balls:
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_LUXURY_BALL
	pokemartlistend

Part5_TrainingClerk::
	lock
	faceplayer
	message Part5_Text_026
	waitmessage
	pokemart Part5_Mart_Training
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Part5_Mart_Training:
	.2byte ITEM_POWER_WEIGHT
	.2byte ITEM_POWER_BRACER
	.2byte ITEM_POWER_BELT
	.2byte ITEM_POWER_LENS
	.2byte ITEM_POWER_BAND
	.2byte ITEM_POWER_ANKLET
	.2byte ITEM_ABILITY_CAPSULE
	pokemartlistend

Part5_MintClerk::
	lock
	faceplayer
	message Part5_Text_027
	waitmessage
	pokemart Part5_Mart_Mints
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Part5_Mart_Mints:
	.2byte ITEM_LONELY_MINT
	.2byte ITEM_ADAMANT_MINT
	.2byte ITEM_NAUGHTY_MINT
	.2byte ITEM_BRAVE_MINT
	.2byte ITEM_BOLD_MINT
	.2byte ITEM_IMPISH_MINT
	.2byte ITEM_LAX_MINT
	.2byte ITEM_RELAXED_MINT
	.2byte ITEM_MODEST_MINT
	.2byte ITEM_MILD_MINT
	.2byte ITEM_RASH_MINT
	.2byte ITEM_QUIET_MINT
	.2byte ITEM_CALM_MINT
	.2byte ITEM_GENTLE_MINT
	.2byte ITEM_CAREFUL_MINT
	.2byte ITEM_SASSY_MINT
	.2byte ITEM_TIMID_MINT
	.2byte ITEM_HASTY_MINT
	.2byte ITEM_JOLLY_MINT
	.2byte ITEM_NAIVE_MINT
	.2byte ITEM_SERIOUS_MINT
	pokemartlistend

Part5_TypeItemClerk::
	lock
	faceplayer
	message Part5_Text_028
	waitmessage
	pokemart Part5_Mart_TypeItems
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Part5_Mart_TypeItems:
	.2byte ITEM_MYSTIC_WATER
	.2byte ITEM_CHARCOAL
	.2byte ITEM_MIRACLE_SEED
	.2byte ITEM_MAGNET
	.2byte ITEM_SHARP_BEAK
	.2byte ITEM_SOFT_SAND
	.2byte ITEM_BLACK_BELT
	.2byte ITEM_POISON_BARB
	.2byte ITEM_NEVER_MELT_ICE
	.2byte ITEM_SPELL_TAG
	.2byte ITEM_TWISTED_SPOON
	.2byte ITEM_HARD_STONE
	.2byte ITEM_METAL_COAT
	.2byte ITEM_BLACK_GLASSES
	.2byte ITEM_DRAGON_FANG
	.2byte ITEM_SILK_SCARF
	.2byte ITEM_SILVER_POWDER
	pokemartlistend

Part5_TacticalClerk::
	lock
	faceplayer
	message Part5_Text_029
	waitmessage
	pokemart Part5_Mart_Tactical
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Part5_Mart_Tactical:
	.2byte ITEM_WHITE_HERB
	.2byte ITEM_MENTAL_HERB
	.2byte ITEM_POWER_HERB
	.2byte ITEM_SMOKE_BALL
	.2byte ITEM_LIGHT_CLAY
	.2byte ITEM_DAMP_ROCK
	.2byte ITEM_HEAT_ROCK
	.2byte ITEM_SMOOTH_ROCK
	.2byte ITEM_ICY_ROCK
	.2byte ITEM_RED_CARD
	.2byte ITEM_EJECT_BUTTON
	.2byte ITEM_WIDE_LENS
	.2byte ITEM_SCOPE_LENS
	.2byte ITEM_SHELL_BELL
	.2byte ITEM_WISE_GLASSES
	.2byte ITEM_MUSCLE_BAND
	.2byte ITEM_METRONOME
	.2byte ITEM_EVIOLITE
	pokemartlistend

Part5_StoreClerkTalk::
	msgbox Part5_Text_030, MSGBOX_NPC
	end

Part5_ArcheDisplay::
	msgbox Part5_Text_031, MSGBOX_SIGN
	end

Part5_ArcheDisplayCustomer::
	msgbox Part5_Text_032, MSGBOX_NPC
	end

Part5_ListOldMan::
	lock
	faceplayer
	goto_if_set FLAG_PART5_SHOPPING_LIST_DONE, Part5_ListOldMan_Done
	checkitem ITEM_SHOPPING_LIST
	goto_if_eq VAR_RESULT, TRUE, Part5_ListOldMan_Return
	msgbox Part5_Text_033, MSGBOX_DEFAULT
	release
	end

Part5_ListOldMan_Return::
	msgbox Part5_Text_034, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	removeitem ITEM_SHOPPING_LIST, 1
	setflag FLAG_PART5_SHOPPING_LIST_DONE
	release
	end

Part5_ListOldMan_Done::
	msgbox Part5_Text_035, MSGBOX_DEFAULT
	release
	end

Part5_ShoppingList::
	lock
	msgbox Part5_Text_036, MSGBOX_DEFAULT
	giveitem ITEM_SHOPPING_LIST, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setflag FLAG_PART5_SHOPPING_LIST_TAKEN
	closemessage
	copyvar VAR_0x8000, VAR_LAST_TALKED
	setvar VAR_0x8001, 6
	call Story_WalkAwayAndRemove
	release
	end

Part5_LunchWife::
	lock
	faceplayer
	goto_if_eq VAR_PART5_LUNCH, PART5_LUNCH_DONE, Part5_LunchWife_Done
	goto_if_eq VAR_PART5_LUNCH, PART5_LUNCH_DELIVERED, Part5_LunchWife_Reward
	goto_if_eq VAR_PART5_LUNCH, PART5_LUNCH_CARRYING, Part5_LunchWife_Waiting
	msgbox Part5_Text_037, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part5_LunchWife_No
	giveitem ITEM_BENTO, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setvar VAR_PART5_LUNCH, PART5_LUNCH_CARRYING
	msgbox Part5_Text_038, MSGBOX_DEFAULT
	release
	end

Part5_LunchWife_No::
	msgbox Part5_Text_039, MSGBOX_DEFAULT
	release
	end

Part5_LunchWife_Waiting::
	msgbox Part5_Text_040, MSGBOX_DEFAULT
	release
	end

Part5_LunchWife_Reward::
	msgbox Part5_Text_041, MSGBOX_DEFAULT
	giveitem ITEM_FULL_RESTORE, 2
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setvar VAR_PART5_LUNCH, PART5_LUNCH_DONE
	release
	end

Part5_LunchWife_Done::
	msgbox Part5_Text_042, MSGBOX_DEFAULT
	release
	end

Part5_LunchHusband::
	lock
	faceplayer
	goto_if_ge VAR_PART5_LUNCH, PART5_LUNCH_DELIVERED, Part5_LunchHusband_Done
	goto_if_eq VAR_PART5_LUNCH, PART5_LUNCH_CARRYING, Part5_LunchHusband_Deliver
	msgbox Part5_Text_043, MSGBOX_DEFAULT
	release
	end

Part5_LunchHusband_Deliver::
	checkitem ITEM_BENTO
	goto_if_eq VAR_RESULT, FALSE, Part5_LunchHusband_NoBento
	msgbox Part5_Text_044, MSGBOX_DEFAULT
	removeitem ITEM_BENTO, 1
	setvar VAR_PART5_LUNCH, PART5_LUNCH_DELIVERED
	msgbox Part5_Text_045, MSGBOX_DEFAULT
	release
	end

Part5_LunchHusband_NoBento::
	msgbox Part5_Text_046, MSGBOX_DEFAULT
	release
	end

Part5_LunchHusband_Done::
	msgbox Part5_Text_047, MSGBOX_DEFAULT
	release
	end

Part5_RibbonMother::
	lock
	faceplayer
	goto_if_eq VAR_PART5_RIBBON, PART5_RIBBON_DONE, Part5_RibbonMother_Done
	goto_if_eq VAR_PART5_RIBBON, PART5_RIBBON_BACK, Part5_RibbonMother_Reward
	goto_if_eq VAR_PART5_RIBBON, PART5_RIBBON_INSIDE, Part5_RibbonMother_Inside
	goto_if_eq VAR_PART5_RIBBON, PART5_RIBBON_CARRYING, Part5_RibbonMother_Waiting
	msgbox Part5_Text_048, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part5_RibbonMother_No
	giveitem ITEM_RIBBON_BOX, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setvar VAR_PART5_RIBBON, PART5_RIBBON_CARRYING
	release
	end

Part5_RibbonMother_No::
	msgbox Part5_Text_049, MSGBOX_DEFAULT
	release
	end

Part5_RibbonMother_Waiting::
	msgbox Part5_Text_050, MSGBOX_DEFAULT
	release
	end

Part5_RibbonMother_Inside::
	msgbox Part5_Text_051, MSGBOX_DEFAULT
	release
	end

Part5_RibbonMother_Reward::
	msgbox Part5_Text_052, MSGBOX_DEFAULT
	giveitem ITEM_GARDEVOIRITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setvar VAR_PART5_RIBBON, PART5_RIBBON_DONE
	special Part5_CheckPartyRaltsLine
	goto_if_eq VAR_RESULT, FALSE, Part5_RibbonMother_End
	msgbox Part5_Text_053, MSGBOX_DEFAULT
Part5_RibbonMother_End::
	release
	end

Part5_RibbonMother_Done::
	msgbox Part5_Text_054, MSGBOX_DEFAULT
	release
	end

Part5_ContestGirl::
	lock
	faceplayer
	goto_if_ge VAR_PART5_RIBBON, PART5_RIBBON_BACK, Part5_ContestGirl_Back
	goto_if_eq VAR_PART5_RIBBON, PART5_RIBBON_CARRYING, Part5_ContestGirl_Give
	msgbox Part5_Text_055, MSGBOX_DEFAULT
	release
	end

Part5_ContestGirl_Give::
	checkitem ITEM_RIBBON_BOX
	goto_if_eq VAR_RESULT, FALSE, Part5_ContestGirl_NoBox
	msgbox Part5_Text_056, MSGBOX_DEFAULT
	removeitem ITEM_RIBBON_BOX, 1
	msgbox Part5_Text_057, MSGBOX_DEFAULT
	closemessage
	setvar VAR_PART5_RIBBON, PART5_RIBBON_INSIDE
	setflag FLAG_PART5_HIDE_CONTEST_GIRL
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PART5_CONTEST_GIRL
	removeobject LOCALID_PART5_CONTEST_KIRLIA
	fadescreen FADE_FROM_BLACK
	release
	end

Part5_ContestGirl_NoBox::
	msgbox Part5_Text_058, MSGBOX_DEFAULT
	release
	end

Part5_ContestGirl_Back::
	msgbox Part5_Text_059, MSGBOX_DEFAULT
	release
	end

Part5_ContestKirlia::
	lock
	faceplayer
	playmoncry SPECIES_KIRLIA, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part5_LilyCustomer::
	msgbox Part5_Text_060, MSGBOX_NPC
	end

Part5_LilyPortWorker::
	msgbox Part5_Text_061, MSGBOX_NPC
	end

Part5_LilyYoungWorker::
	msgbox Part5_Text_062, MSGBOX_NPC
	end

Part5_LilyYoungWorkerFriend::
	msgbox Part5_Text_063, MSGBOX_NPC
	end

Part5_LilyMotelGuest::
	msgbox Part5_Text_064, MSGBOX_NPC
	end

Part5_RooftopOldMan::
	msgbox Part5_Text_065, MSGBOX_NPC
	end

Part5_RooftopOldWoman::
	msgbox Part5_Text_066, MSGBOX_NPC
	end

Part5_LilyGateSign::
	msgbox Part5_Text_067, MSGBOX_SIGN
	end

Part5_CampusPC_OnTransition:
	setrespawn HEAL_LOCATION_LILYCOVE_CITY
	end

Part5_AvenueSign::
	msgbox Part5_Text_068, MSGBOX_SIGN
	end

Part5_AvenueJogger::
	msgbox Part5_Text_069, MSGBOX_NPC
	end

Part5_AvenueTourist::
	msgbox Part5_Text_070, MSGBOX_NPC
	end

Part5_AvenueVendor::
	msgbox Part5_Text_071, MSGBOX_NPC
	end

Part5_AvenueCyclist::
	msgbox Part5_Text_072, MSGBOX_NPC
	end

Part5_AvenueEmployee::
	msgbox Part5_Text_073, MSGBOX_NPC
	end

Part5_AvenueTrucks::
	msgbox Part5_Text_074, MSGBOX_SIGN
	end

Part5_CampusGateSign::
	msgbox Part5_Text_075, MSGBOX_SIGN
	end

Part5_CampusHQSign::
	msgbox Part5_Text_076, MSGBOX_SIGN
	end

Part5_CampusTrainingSign::
	msgbox Part5_Text_077, MSGBOX_SIGN
	end

Part5_CampusExchangeSign::
	msgbox Part5_Text_078, MSGBOX_SIGN
	end

Part5_CampusLogisticsSign::
	msgbox Part5_Text_079, MSGBOX_SIGN
	end

Part5_CampusPlazaSign::
	msgbox Part5_Text_080, MSGBOX_SIGN
	end

Part5_CampusEmployeeReport::
	msgbox Part5_Text_081, MSGBOX_NPC
	end

Part5_CampusEmployeeOnTime::
	msgbox Part5_Text_082, MSGBOX_NPC
	end

Part5_CampusScholar::
	msgbox Part5_Text_083, MSGBOX_NPC
	end

Part5_CampusRent::
	msgbox Part5_Text_084, MSGBOX_NPC
	end

Part5_CampusOldMan::
	msgbox Part5_Text_085, MSGBOX_NPC
	end

Part5_CampusFoodStall::
	msgbox Part5_Text_086, MSGBOX_NPC
	end

Part5_CampusTransit::
	msgbox Part5_Text_087, MSGBOX_NPC
	end

Part5_CampusSample::
	msgbox Part5_Text_088, MSGBOX_NPC
	end

Part5_CampusMeeting1::
	msgbox Part5_Text_089, MSGBOX_NPC
	end

Part5_CampusMeeting2::
	msgbox Part5_Text_090, MSGBOX_NPC
	end

Part5_CampusLittleGirl::
	msgbox Part5_Text_091, MSGBOX_NPC
	end

Part5_CampusVisitor::
	msgbox Part5_Text_092, MSGBOX_NPC
	end

Part5_HQReceptionist::
	msgbox Part5_Text_093, MSGBOX_NPC
	end

Part5_HQLobbyEmployee::
	msgbox Part5_Text_094, MSGBOX_NPC
	end

Part5_HQLobbyGuard::
	msgbox Part5_Text_095, MSGBOX_NPC
	end

Part5_HQCafeStaff::
	msgbox Part5_Text_096, MSGBOX_NPC
	end

Part5_HQVisitorFamily::
	msgbox Part5_Text_097, MSGBOX_NPC
	end

Part5_HQCommittee::
	msgbox Part5_Text_098, MSGBOX_SIGN
	end

Part5_HQProducts::
	msgbox Part5_Text_099, MSGBOX_SIGN
	end

Part5_HQExhibitEnv::
	msgbox Part5_Text_100, MSGBOX_SIGN
	end

Part5_HQExhibitLife::
	msgbox Part5_Text_101, MSGBOX_SIGN
	end

Part5_HQExhibitAncient::
	msgbox Part5_Text_102, MSGBOX_SIGN
	end

Part5_HQStairGuard::
	msgbox Part5_Text_103, MSGBOX_NPC
	end

Part5_HQOpenLab::
	msgbox Part5_Text_104, MSGBOX_NPC
	end

Part5_HQVisitorStudent::
	msgbox Part5_Text_105, MSGBOX_NPC
	end

Part5_HQEngineer::
	msgbox Part5_Text_106, MSGBOX_NPC
	end

Part5_CampusNurse::
	setvar VAR_0x800B, LOCALID_PART5_CAMPUS_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

Part5_CampusPCDonation::
	msgbox Part5_Text_107, MSGBOX_NPC
	end

Part5_CampusPCTraveler::
	msgbox Part5_Text_108, MSGBOX_NPC
	end

Part5_CampusPCForeign::
	msgbox Part5_Text_109, MSGBOX_NPC
	end

Part5_CampusPCStairs::
	msgbox Part5_Text_110, MSGBOX_NPC
	end

Part5_CampusMartClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Part5_Mart_Campus
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Part5_Mart_Campus:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	pokemartlistend

Part5_CampusMartCustomer::
	msgbox Part5_Text_111, MSGBOX_NPC
	end

Part5_ApartmentResident::
	msgbox Part5_Text_112, MSGBOX_NPC
	end

Part5_ApartmentNewcomer::
	msgbox Part5_Text_113, MSGBOX_NPC
	end

Part5_ApartmentStairs::
	msgbox Part5_Text_114, MSGBOX_NPC
	end

Part5_SeasideResident::
	msgbox Part5_Text_115, MSGBOX_NPC
	end

Part5_SeasideWingull::
	lock
	faceplayer
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part5_HouseResident::
	msgbox Part5_Text_116, MSGBOX_NPC
	end

Part5_HouseKid::
	msgbox Part5_Text_117, MSGBOX_NPC
	end

Part5_CafeOwner::
	msgbox Part5_Text_118, MSGBOX_NPC
	end

Part5_CafeEmployee::
	msgbox Part5_Text_119, MSGBOX_NPC
	end

Part5_FamilyMother::
	msgbox Part5_Text_120, MSGBOX_NPC
	end

Part5_FamilyGrandpa::
	msgbox Part5_Text_121, MSGBOX_NPC
	end

Part5_LogisticsWorker::
	msgbox Part5_Text_122, MSGBOX_NPC
	end

Part5_ExchangeForeign1::
	msgbox Part5_Text_123, MSGBOX_NPC
	end

Part5_ExchangeForeign2::
	msgbox Part5_Text_124, MSGBOX_NPC
	end

Part5_ExchangeGuide::
	msgbox Part5_Text_125, MSGBOX_NPC
	end

Part5_ExchangeBoard::
	msgbox Part5_Text_126, MSGBOX_SIGN
	end

Part5_ExchangeNotebook::
	msgbox Part5_Text_127, MSGBOX_SIGN
	end

Part5_ExchangeStudent::
	msgbox Part5_Text_128, MSGBOX_NPC
	end

Part5_TrainingDesk::
	lock
	faceplayer
	goto_if_set FLAG_PART5_MEDICHAMITE, Part5_TrainingDesk_Done
	goto_if_defeated TRAINER_PART5_ARCHE_GUARD, Part5_TrainingDesk_Reward
	msgbox Part5_Text_129, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part5_TrainingDesk_Decline
	msgbox Part5_Text_130, MSGBOX_DEFAULT
	call Common_EventScript_OutOfCenterPartyHeal
	goto Part5_TrainingDesk_Next

Part5_TrainingDesk_Next::
	goto_if_not_defeated TRAINER_PART5_ARCHE_TECH, Part5_TrainingDesk_Battle1
	goto_if_not_defeated TRAINER_PART5_ARCHE_SURVEYOR, Part5_TrainingDesk_Battle2
	goto_if_not_defeated TRAINER_PART5_ARCHE_GUARD, Part5_TrainingDesk_Battle3
	goto Part5_TrainingDesk_Reward

Part5_TrainingDesk_Battle1::
	msgbox Part5_Text_131, MSGBOX_DEFAULT
	trainerbattle_single TRAINER_PART5_ARCHE_TECH, Part5_Text_132, Part5_Text_133, Part5_TrainingDesk_After
	goto Part5_TrainingDesk_After

Part5_TrainingDesk_Battle2::
	msgbox Part5_Text_134, MSGBOX_DEFAULT
	trainerbattle_single TRAINER_PART5_ARCHE_SURVEYOR, Part5_Text_135, Part5_Text_136, Part5_TrainingDesk_After
	goto Part5_TrainingDesk_After

Part5_TrainingDesk_Battle3::
	msgbox Part5_Text_137, MSGBOX_DEFAULT
	trainerbattle_single TRAINER_PART5_ARCHE_GUARD, Part5_Text_138, Part5_Text_139, Part5_TrainingDesk_After
	goto Part5_TrainingDesk_After

Part5_TrainingDesk_After::
	lock
	goto_if_defeated TRAINER_PART5_ARCHE_GUARD, Part5_TrainingDesk_Reward
	msgbox Part5_Text_140, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part5_TrainingDesk_Pause
	call Common_EventScript_OutOfCenterPartyHeal
	goto Part5_TrainingDesk_Next

Part5_TrainingDesk_Pause::
	msgbox Part5_Text_141, MSGBOX_DEFAULT
	release
	end

Part5_TrainingDesk_Decline::
	msgbox Part5_Text_142, MSGBOX_DEFAULT
	release
	end

Part5_TrainingDesk_Reward::
	msgbox Part5_Text_143, MSGBOX_DEFAULT
	giveitem ITEM_MEDICHAMITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setflag FLAG_PART5_MEDICHAMITE
	release
	end

Part5_TrainingDesk_Done::
	msgbox Part5_Text_144, MSGBOX_DEFAULT
	release
	end

Part5_TrainingTech::
	msgbox Part5_Text_145, MSGBOX_NPC
	end

Part5_Route122Traveler::
	msgbox Part5_Text_146, MSGBOX_NPC
	end

Part5_FlowerOldMan::
	lock
	faceplayer
	goto_if_eq VAR_PART5_FLOWER, PART5_FLOWER_DONE, Part5_FlowerOldMan_Done
	goto_if_eq VAR_PART5_FLOWER, PART5_FLOWER_PLACED, Part5_FlowerOldMan_Reward
	goto_if_eq VAR_PART5_FLOWER, PART5_FLOWER_CARRYING, Part5_FlowerOldMan_Waiting
	msgbox Part5_Text_147, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part5_FlowerOldMan_No
	giveitem ITEM_WHITE_FLOWER, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setvar VAR_PART5_FLOWER, PART5_FLOWER_CARRYING
	msgbox Part5_Text_148, MSGBOX_DEFAULT
	release
	end

Part5_FlowerOldMan_No::
	msgbox Part5_Text_149, MSGBOX_DEFAULT
	release
	end

Part5_FlowerOldMan_Waiting::
	msgbox Part5_Text_150, MSGBOX_DEFAULT
	release
	end

Part5_FlowerOldMan_Reward::
	msgbox Part5_Text_151, MSGBOX_DEFAULT
	msgbox Part5_Text_152, MSGBOX_DEFAULT
	giveitem ITEM_HIGANBANA, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setflag FLAG_PART5_HIGANBANA
	setvar VAR_PART5_FLOWER, PART5_FLOWER_DONE
	release
	end

Part5_FlowerOldMan_Done::
	msgbox Part5_Text_153, MSGBOX_DEFAULT
	release
	end

Part5_FlowerGrave::
	lockall
	goto_if_ne VAR_PART5_FLOWER, PART5_FLOWER_CARRYING, Part5_FlowerGrave_Plain
	msgbox Part5_Text_154, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part5_QuietEnd
	removeitem ITEM_WHITE_FLOWER, 1
	setvar VAR_PART5_FLOWER, PART5_FLOWER_PLACED
	msgbox Part5_Text_155, MSGBOX_DEFAULT
	releaseall
	end

Part5_FlowerGrave_Plain::
	goto_if_ge VAR_PART5_FLOWER, PART5_FLOWER_PLACED, Part5_FlowerGrave_HasFlower
	msgbox Part5_Text_156, MSGBOX_DEFAULT
	releaseall
	end

Part5_FlowerGrave_HasFlower::
	msgbox Part5_Text_157, MSGBOX_DEFAULT
	releaseall
	end

Part5_SummitSync::
	call_if_set FLAG_PART5_ABSOL_MOVED, Part5_SummitSync_Absol
	return

Part5_SummitSync_Absol::
	setobjectxyperm LOCALID_PART5_ABSOL, 34, 22
	setobjectmovementtype LOCALID_PART5_ABSOL, MOVEMENT_TYPE_FACE_RIGHT
	return

Part5_Absol::
	lock
	faceplayer
	playmoncry SPECIES_ABSOL, CRY_MODE_NORMAL
	waitmoncry
	goto_if_set FLAG_PART5_ABSOL_MOVED, Part5_Absol_End
	goto_if_unset FLAG_PART5_HIGANBANA, Part5_Absol_End
	applymovement LOCALID_PART5_ABSOL, Part5_Movement_AbsolToGrave
	waitmovement 0
	setflag FLAG_PART5_ABSOL_MOVED
	msgbox Part5_Text_158, MSGBOX_DEFAULT
Part5_Absol_End::
	release
	end

Part5_Movement_AbsolToGrave:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	face_right
	step_end

Part5_AbsolGrave::
	lockall
	goto_if_unset FLAG_PART5_ABSOL_MOVED, Part5_AbsolGrave_Plain
	goto_if_set FLAG_PART5_ABSOLITE, Part5_AbsolGrave_Plain
	msgbox Part5_Text_159, MSGBOX_DEFAULT
	giveitem ITEM_ABSOLITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setflag FLAG_PART5_ABSOLITE
	releaseall
	end

Part5_AbsolGrave_Plain::
	msgbox Part5_Text_160, MSGBOX_DEFAULT
	releaseall
	end

Part5_GraveKeeper::
	msgbox Part5_Text_161, MSGBOX_NPC
	end

Part5_SummitTourist::
	msgbox Part5_Text_162, MSGBOX_NPC
	end

Part5_SpecialTomb::
	lockall
	goto_if_unset FLAG_PART5_DISTORTION_AUTHORIZED, Part5_SpecialTomb_Plain
	checkitem ITEM_HIGANBANA
	goto_if_eq VAR_RESULT, FALSE, Part5_SpecialTomb_Plain
	msgbox Part5_Text_163, MSGBOX_DEFAULT
	releaseall
	end

Part5_SpecialTomb_Plain::
	msgbox Part5_Text_164, MSGBOX_DEFAULT
	releaseall
	end

Part5_SpaceUneasy::
	msgbox Part5_Text_165, MSGBOX_SIGN
	end

Part5_MagmaRookie::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_14, Part5_Text_166, Part5_Text_167, Part5_MagmaRookie_Defeated
	goto Part5_MagmaRookie_After

Part5_MagmaRookie_Defeated::
	lock
	faceplayer
	call_if_set FLAG_PART55_ROOKIE_TEAMUP_DONE, Part55_RookieAfterRecall
	msgbox Part5_Text_168, MSGBOX_DEFAULT
	release
	end

Part5_MagmaRookie_After::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, Part5_MagmaRookie_Leave
	msgbox Part5_Text_169, MSGBOX_DEFAULT
	release
	end

Part5_MagmaRookie_Leave::
	msgbox Part5_Text_170, MSGBOX_DEFAULT
	msgbox Part5_Text_171, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PART55_BasePuff
	removeobject LOCALID_PART5_MAGMA_ROOKIE
	setflag FLAG_PART5_MAGMA_ROOKIE_LEFT
	fadescreen FADE_FROM_BLACK
	release
	end

Part5_MagmaMonitor::
	msgbox Part5_Text_172, MSGBOX_SIGN
	end

Part5_MagmaMapDesk::
	msgbox Part5_Text_173, MSGBOX_SIGN
	end

Part5_MagmaGeoData::
	msgbox Part5_Text_174, MSGBOX_SIGN
	end

Part5_MagmaPlans::
	msgbox Part5_Text_175, MSGBOX_SIGN
	end

Part5_MagmaDigWall::
	msgbox Part5_Text_176, MSGBOX_SIGN
	end

Part5_AquaBoyfriend::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_1, Part5_Text_177, Part5_Text_178, Part5_AquaBoyfriend_After
	goto Part5_AquaBoyfriend_After

Part5_AquaBoyfriend_After::
	lock
	faceplayer
	checkitem ITEM_PEACE_CHARM
	goto_if_eq VAR_RESULT, FALSE, Part5_AquaBoyfriend_NoCharm
	msgbox Part5_Text_179, MSGBOX_DEFAULT
	msgbox Part5_Text_180, MSGBOX_DEFAULT
	removeitem ITEM_PEACE_CHARM, 1
	setvar VAR_PART2_PEACE_CHARM_STATE, PART2_CHARM_DELIVERED
	msgbox Part5_Text_181, MSGBOX_DEFAULT
	msgbox Part5_Text_182, MSGBOX_DEFAULT
	msgbox Part5_Text_183, MSGBOX_DEFAULT
	msgbox Part5_Text_184, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PART5_AQUA_BOYFRIEND
	setflag FLAG_PART5_AQUA_BOYFRIEND_LEFT
	fadescreen FADE_FROM_BLACK
	release
	end

Part5_AquaBoyfriend_NoCharm::
	msgbox Part5_Text_185, MSGBOX_DEFAULT
	release
	end

Part5_AquaGear::
	msgbox Part5_Text_186, MSGBOX_SIGN
	end

Part5_AquaLunch::
	msgbox Part5_Text_187, MSGBOX_SIGN
	end

Part5_AquaLaundry::
	msgbox Part5_Text_188, MSGBOX_SIGN
	end

Part5_AquaStorageNote::
	msgbox Part5_Text_189, MSGBOX_SIGN
	end

Part5_SlateHarborWorker::
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, Part5_SlateHarborWorker_Later
	goto_if_ge VAR_SLATEPORT_HARBOR_STATE, 2, Part5_SlateHarborWorker_After
	msgbox Part5_Text_190, MSGBOX_NPC
	end
Part5_SlateHarborWorker_After::
	msgbox Part5_Text_191, MSGBOX_NPC
	end
Part5_SlateHarborWorker_Later::
	msgbox Part5_Text_192, MSGBOX_NPC
	end

Part5_SlateMarketMerchant::
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, Part5_SlateMarketMerchant_Later
	goto_if_ge VAR_SLATEPORT_HARBOR_STATE, 2, Part5_SlateMarketMerchant_After
	msgbox Part5_Text_193, MSGBOX_NPC
	end
Part5_SlateMarketMerchant_After::
	msgbox Part5_Text_194, MSGBOX_NPC
	end
Part5_SlateMarketMerchant_Later::
	msgbox Part5_Text_195, MSGBOX_NPC
	end

Part5_SlateTourist::
	goto_if_ge VAR_SLATEPORT_HARBOR_STATE, 2, Part5_SlateTourist_After
	msgbox Part5_Text_196, MSGBOX_NPC
	end
Part5_SlateTourist_After::
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, Part5_SlateTourist_Later
	msgbox Part5_Text_197, MSGBOX_NPC
	end
Part5_SlateTourist_Later::
	msgbox Part5_Text_198, MSGBOX_NPC
	end

Part5_SlateArcheLogistics::
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, Part5_SlateArcheLogistics_Later
	goto_if_ge VAR_SLATEPORT_HARBOR_STATE, 2, Part5_SlateArcheLogistics_After
	msgbox Part5_Text_199, MSGBOX_NPC
	end
Part5_SlateArcheLogistics_After::
	msgbox Part5_Text_200, MSGBOX_NPC
	end
Part5_SlateArcheLogistics_Later::
	msgbox Part5_Text_201, MSGBOX_NPC
	end

Part5_SlateCrates::
	msgbox Part5_Text_202, MSGBOX_SIGN
	end

Part5_MuseumStaff::
	goto_if_ge VAR_SLATEPORT_HARBOR_STATE, 2, Part5_MuseumStaff_After
	msgbox Part5_Text_203, MSGBOX_NPC
	end
Part5_MuseumStaff_After::
	msgbox Part5_Text_204, MSGBOX_NPC
	end

Part5_SlateBoyfriend::
	lock
	faceplayer
	goto_if_eq VAR_PART2_PEACE_CHARM_STATE, PART2_CHARM_COMPLETED, Part5_SlateBoyfriend_Done
	call Part5_CoupleReunion
	release
	end

Part5_SlateBoyfriend_Done::
	goto_if_set FLAG_SYS_GAME_CLEAR, Part7_CoupleChampion
	msgbox Part5_Text_205, MSGBOX_DEFAULT
	release
	end

Part5_CoupleReunion::
	msgbox Part5_Text_206, MSGBOX_DEFAULT
	msgbox Part5_Text_207, MSGBOX_DEFAULT
	msgbox Part5_Text_208, MSGBOX_DEFAULT
	msgbox Part5_Text_209, MSGBOX_DEFAULT
	setvar VAR_PART2_PEACE_CHARM_STATE, PART2_CHARM_COMPLETED
	return

Part5_CharmGirlfriend::
	goto_if_eq VAR_PART2_PEACE_CHARM_STATE, PART2_CHARM_COMPLETED, Part5_CharmGirlfriend_Done
	goto_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, Part5_CharmGirlfriend_Wait
	call Part5_CoupleReunion
	release
	end

Part5_CharmGirlfriend_Wait::
	msgbox Part5_Text_210, MSGBOX_DEFAULT
	release
	end

Part5_CharmGirlfriend_Done::
	msgbox Part5_Text_211, MSGBOX_DEFAULT
	release
	end

Part5_R124Researcher::
	msgbox Part5_Text_212, MSGBOX_NPC
	end

Part5_R124DiveHint::
	msgbox Part5_Text_213, MSGBOX_NPC
	end

Part5_MossKid::
	msgbox Part5_Text_214, MSGBOX_NPC
	end

Part5_MossParent::
	msgbox Part5_Text_215, MSGBOX_NPC
	end

Part5_MossForeignResearcher::
	msgbox Part5_Text_216, MSGBOX_NPC
	end

Part5_SpaceStaff::
	msgbox Part5_Text_217, MSGBOX_NPC
	end

Part5_ArcheLiaison::
	msgbox Part5_Text_218, MSGBOX_NPC
	end

Part5_ArcheInstrument::
	lockall
	goto_if_set FLAG_PART5_MOSSDEEP_INSTRUMENT_SEEN, Part5_ArcheInstrument_Again
	msgbox Part5_Text_219, MSGBOX_DEFAULT
	setflag FLAG_PART5_MOSSDEEP_INSTRUMENT_SEEN
	releaseall
	end

Part5_ArcheInstrument_Again::
	msgbox Part5_Text_220, MSGBOX_DEFAULT
	releaseall
	end

Part5_StarKid::
	lock
	faceplayer
	goto_if_set FLAG_PART5_SOLROCK_LUNATONE_CANDY, Part5_StarKid_Done
	msgbox Part5_Text_221, MSGBOX_DEFAULT
	special Part5_CheckSolrockLunatoneCaught
	goto_if_eq VAR_RESULT, FALSE, Part5_StarKid_NotYet
	msgbox Part5_Text_222, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setflag FLAG_PART5_SOLROCK_LUNATONE_CANDY
	release
	end

Part5_StarKid_NotYet::
	msgbox Part5_Text_223, MSGBOX_DEFAULT
	release
	end

Part5_StarKid_Done::
	msgbox Part5_Text_224, MSGBOX_DEFAULT
	release
	end

Part5_SwabluKid::
	lock
	faceplayer
	goto_if_set FLAG_PART5_SWABLU_RETURNED, Part5_SwabluKid_Back
	msgbox Part5_Text_225, MSGBOX_DEFAULT
	release
	end

Part5_SwabluKid_Back::
	msgbox Part5_Text_226, MSGBOX_DEFAULT
	release
	end

Part5_SwabluParent::
	lock
	faceplayer
	goto_if_set FLAG_PART5_ALTARIANITE, Part5_SwabluParent_Done
	goto_if_unset FLAG_PART5_SWABLU_RETURNED, Part5_SwabluParent_Wait
	msgbox Part5_Text_227, MSGBOX_DEFAULT
	giveitem ITEM_ALTARIANITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part5_BagFull
	setflag FLAG_PART5_ALTARIANITE
	release
	end

Part5_SwabluParent_Wait::
	msgbox Part5_Text_228, MSGBOX_DEFAULT
	release
	end

Part5_SwabluParent_Done::
	msgbox Part5_Text_229, MSGBOX_DEFAULT
	release
	end

Part5_SwabluLost::
	lock
	faceplayer
	playmoncry SPECIES_SWABLU, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part5_Text_230, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PART5_SWABLU_LOST
	setflag FLAG_PART5_SWABLU_RETURNED
	special Part5_SyncMossdeep
	addobject LOCALID_PART5_SWABLU_HOME
	fadescreen FADE_FROM_BLACK
	release
	end

Part5_SwabluHome::
	lock
	faceplayer
	playmoncry SPECIES_SWABLU, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Part5_StevenHouse::
	lock
	faceplayer
	goto_if_set FLAG_PART5_STEVEN_MOSSDEEP_GREET, Part5_StevenHouse_Native
	msgbox Part5_Text_231, MSGBOX_DEFAULT
	setflag FLAG_PART5_STEVEN_MOSSDEEP_GREET
Part5_StevenHouse_Native::
	msgbox MossdeepCity_StevensHouse_Text_UnderwateCavernBetweenMossdeepSootopolis, MSGBOX_DEFAULT
	release
	end

Part5_GymPartnerEgg::
	goto_if_defeated TRAINER_TATE_AND_LIZA_1, Part5_GymPartnerEgg_End
	special Part5_CheckPartySolrockLunatone
	goto_if_eq VAR_RESULT, FALSE, Part5_GymPartnerEgg_End
	msgbox Part5_Text_232, MSGBOX_DEFAULT
Part5_GymPartnerEgg_End::
	return

Part5_Text_001:
	.string "背包已经满了。整理一下再来吧。$"

Part5_Text_002:
	.string "我坐了船又换车，走了好几天，\n就是为了来逛野生原野区！\p"
	.string "既然在路上碰到了训练家，\n那就先拿你热热身吧！$"

Part5_Text_003:
	.string "输是输了，不过能跟你打一场，\n这趟也算没白跑！$"

Part5_Text_004:
	.string "听说原野区里有好多\n我老家见不到的宝可梦。\p"
	.string "今天我非得多看几种不可！$"

Part5_Text_005:
	.string "飞天螳螂才是最强的！\p"
	.string "他非说巨钳螳螂更厉害，\n你来评评理！用对战来评！$"

Part5_Text_006:
	.string "唔……飞天螳螂的速度\n明明更快啊……$"

Part5_Text_007:
	.string "巨钳螳螂的钢铁钳子才是最强的！\p"
	.string "你来评评理！用对战来评！$"

Part5_Text_008:
	.string "钳子再硬，也挡不住你啊……$"

Part5_Text_009:
	.string "一个一个打，还是分不出高下……\p"
	.string "那就两个一起上！\n这回让你看清楚！$"

Part5_Text_010:
	.string "飞天螳螂！巨钳螳螂！上吧！$"

Part5_Text_011:
	.string "不会吧……\n我们俩联手居然还是输了！$"

Part5_Text_012:
	.string "我们是两个人一起上的，\n你得带两只能战斗的宝可梦才行。$"

Part5_Text_013:
	.string "还有一个人没跟你比过呢！\p"
	.string "你也去跟他打一场，\n再来说哪只更强！$"

Part5_Text_014:
	.string "好吧，我们输得心服口服。\n不过我还是最喜欢自己的搭档！\p"
	.string "这块石头是我们吵架的时候\n一起在路边捡到的。\p"
	.string "给我们谁都不公平，\n干脆送给你这个裁判吧！$"

Part5_Text_015:
	.string "飞天螳螂最强！\n不对，是巨钳螳螂最强！\p"
	.string "……照这样下去，\n我们大概要吵一辈子了。$"

Part5_Text_016:
	.string "你好，我负责野生原野区的\n保育记录。\p"
	.string "我们会和其他地区交换保育资料。\p"
	.string "有些宝可梦原本不住在丰缘，\n适应了这里的环境之后，\p"
	.string "也会慢慢建立起自己的族群。$"

Part5_Text_017:
	.string "能帮我个忙吗？\n我需要一些实地捕获记录。\p"
	.string "请在野生原野区里捕获\n3种不同的宝可梦，\p"
	.string "然后再回来找我。\n我会根据你的记录整理报告。$"

Part5_Text_018:
	.string "三种都记录到了！\n谢谢你，这下报告好写多了。\p"
	.string "这个给你当谢礼。\n带着它的宝可梦更容易成长。$"

Part5_Text_019:
	.string "我还有一个请求。\p"
	.string "原野区的北边有赫拉克罗斯，\n西北边有凯罗斯。\p"
	.string "这两种都捕获登记以后，\n请再来找我。\p"
	.string "我想和你做一次对战记录。$"

Part5_Text_020:
	.string "赫拉克罗斯和凯罗斯都登记了？\n太好了，我也带着这两种。\p"
	.string "陪我打一场吧，\n让我记录一下实战数据！$"

Part5_Text_021:
	.string "准备好了吗？\n对战记录，开始！$"

Part5_Text_022:
	.string "数据非常完整。\n谢谢你的配合！$"

Part5_Text_023:
	.string "对战数据都记好了。\p"
	.string "这两块石头是调查时找到的，\n和这两种宝可梦关系很深。\p"
	.string "就当作谢礼，送给你吧。$"

Part5_Text_024:
	.string "今天的记录就到这里。\p"
	.string "原野区里的宝可梦还多着呢，\n有空也多去看看它们吧。$"

Part5_Text_025:
	.string "欢迎光临，这里是捕获用品专柜。\p"
	.string "各地的特殊球都有进货，\n想要哪一种，尽管挑！$"

Part5_Text_026:
	.string "这里是训练用品专柜。\n锻炼努力值的道具都在这里。$"

Part5_Text_027:
	.string "这里是薄荷专柜。\p"
	.string "价格是贵了一点，\n不过效果绝对是实打实的。$"

Part5_Text_028:
	.string "这里是属性持有物专柜。\p"
	.string "以前这些只能在野外碰运气捡，\n现在直接就能买到了。$"

Part5_Text_029:
	.string "这里是对战道具专柜。\p"
	.string "进货不多，\n每样商品每位客人限购一个。$"

Part5_Text_030:
	.string "我们的商品来源很杂，\n丰缘本地的、外地运来的都有。$"

Part5_Text_031:
	.string "“ARCHE 野外环境调查系列”\n面向研究机构及专业调查人员。\p"
	.string "气象、土壤、宝可梦活动记录仪……\n展示柜里的设备看起来很精密。$"

Part5_Text_032:
	.string "这些设备可不便宜。\n天气、土壤、宝可梦活动都能测。\p"
	.string "听说119号道路那边\n也有人在用这种设备。$"

Part5_Text_033:
	.string "哎呀，我的购物清单不见了。\p"
	.string "刚才在楼上逛的时候\n还拿在手里的……\p"
	.string "我在4楼待得最久，\n说不定是掉在那儿了。\p"
	.string "你要是看见了，\n能帮我拿回来吗？$"

Part5_Text_034:
	.string "对对，就是这张！\p"
	.string "年纪大了，\n买三样东西都得写下来。\p"
	.string "谢谢你啊，这个拿去吧。$"

Part5_Text_035:
	.string "这回我可得把清单攥紧了。$"

Part5_Text_036:
	.string "地上掉着一张纸。\n上面写着“毛巾、茶叶、电池”。\p"
	.string "好像是谁的购物清单。$"

Part5_Text_037:
	.string "糟了糟了！\n我把丈夫今天的午饭拿错了！\p"
	.string "他在阿尔刻园区的物流部门上班，\n园区就在海滨大道的另一头。\p"
	.string "能帮我把这个便当送过去吗？$"

Part5_Text_038:
	.string "太好了，谢谢你！\p"
	.string "东海滩那栋小楼\n就是去海滨大道的入口。\p"
	.string "沿着大道一直往西走就是园区，\n物流部门在仓库办公室。$"

Part5_Text_039:
	.string "也是，突然拜托你这种事……\n我再想想别的办法吧。$"

Part5_Text_040:
	.string "物流部门在园区的仓库办公室。\p"
	.string "从东海滩的小楼进海滨大道，\n一直往西走就到了。拜托啦！$"

Part5_Text_041:
	.string "他吃到了吗？太好了！\p"
	.string "早上太着急，\n把我自己的点心盒装进去了。\p"
	.string "这个给你，\n谢谢你跑这一趟。$"

Part5_Text_042:
	.string "今天出门之前，\n我可是把便当检查了三遍。$"

Part5_Text_043:
	.string "今天的午饭怎么全是甜点……\n算了，先把这批出货单核完。$"

Part5_Text_044:
	.string "这是……我的便当？\p"
	.string "难怪我打开袋子一看，\n里面全是甜点心……\p"
	.string "谢谢你特地跑一趟。$"

Part5_Text_045:
	.string "回去替我跟她说声谢谢。\n那盒点心，我留着当下午茶。$"

Part5_Text_046:
	.string "嗯？你好像有事找我？$"

Part5_Text_047:
	.string "吃饱了才有力气搬货。\n下午还有三车设备要发呢。$"

Part5_Text_048:
	.string "我女儿今天第一次\n正式参加华丽大赛。\p"
	.string "可我这边柜台走不开……\n她带着奇鲁莉安，一定紧张坏了。\p"
	.string "她应该就在大赛会场门口。\n能帮我把这个缎带盒交给她吗？$"

Part5_Text_049:
	.string "……也是，\n还是等我下班再说吧。$"

Part5_Text_050:
	.string "大赛会场在宝可梦中心南边，\n她就在会场门口。拜托你了！$"

Part5_Text_051:
	.string "她收下了？\n……那就好。\p"
	.string "要是我这边下班早，\n我也想过去看看。$"

Part5_Text_052:
	.string "她真的上台了？\n谢谢你，真的谢谢你。\p"
	.string "这个以前一直和那条缎带\n放在一起。\p"
	.string "我也不知道它有什么用，\n就送给你吧。$"

Part5_Text_053:
	.string "哎呀，你也带着这一家族的宝可梦。\n看来它也很喜欢你呢。$"

Part5_Text_054:
	.string "下次比赛，\n我一定请假去现场看！$"

Part5_Text_055:
	.string "马上就要轮到我了……\n奇鲁莉安也一直在发抖。\p"
	.string "要不……还是下次再来吧。$"

Part5_Text_056:
	.string "这是妈妈让你送来的？$"

Part5_Text_057:
	.string "这是我小时候得的缎带……\p"
	.string "…………\p"
	.string "好，我进去试试！\n奇鲁莉安，我们走吧！$"

Part5_Text_058:
	.string "马上就要轮到我了……\n怎么办，腿都软了……$"

Part5_Text_059:
	.string "虽然没拿到第一名……\n但我没有临阵逃跑！\p"
	.string "奇鲁莉安也表现得特别棒！$"

Part5_Text_060:
	.string "我每次来水静，\n都会顺便逛逛外地来的货。\p"
	.string "结果今天又多买了两袋……$"

Part5_Text_061:
	.string "一忙起来，午饭都得站着吃。\n今天到港的船特别多。$"

Part5_Text_062:
	.string "我第一次领工资的时候，\n在百货大楼一口气花掉了一半。$"

Part5_Text_063:
	.string "你还好意思说！\n那个月月底你天天来蹭我的饭。$"

Part5_Text_064:
	.string "本来只打算住两天，\p"
	.string "结果逛着逛着，\n已经住了一个星期。$"

Part5_Text_065:
	.string "我们年轻的时候，\n第一次约会就是在这个屋顶上。$"

Part5_Text_066:
	.string "那时候这里还没这么热闹。\p"
	.string "现在楼越盖越高，\n只有海还是老样子。$"

Part5_Text_067:
	.string "水静海滨大道 入口站\p前方：阿尔刻园区$"

Part5_Text_068:
	.string "水静海滨大道\p西：阿尔刻园区　东：水静市$"

Part5_Text_069:
	.string "我每天早上沿着海边跑一圈，\n跑完正好赶上园区的班车。$"

Part5_Text_070:
	.string "从水静走过来，一会儿就到了。\p"
	.string "那栋大楼就是阿尔刻的丰缘总部吧？\n拍张照回去给朋友看看！$"

Part5_Text_071:
	.string "冰淇淋、汽水，还有釜炎仙贝！\n下班时间人最多，现在还算清闲。$"

Part5_Text_072:
	.string "这条路又平又宽，\n骑自行车最舒服了！$"

Part5_Text_073:
	.string "早上的货车又把路口堵住了。\n还是走路上班比较快。$"

Part5_Text_074:
	.string "路边停着几辆运货车。\n车厢上印着“ARCHE 物流”。$"

Part5_Text_075:
	.string "阿尔刻园区　东门\p往东：水静海滨大道$"

Part5_Text_076:
	.string "阿尔刻集团·丰缘总部\p访客中心与公共展示层对外开放。$"

Part5_Text_077:
	.string "阿尔刻公共训练测试场\p欢迎训练家参加公开测试。$"

Part5_Text_078:
	.string "研究交流馆\p与各地区研究机构的资料交流展示。$"

Part5_Text_079:
	.string "物流区　仓库办公室\p收发货请在窗口登记。$"

Part5_Text_080:
	.string "阿尔刻广场\p园区建设得到水静市各界的支持。$"

Part5_Text_081:
	.string "下午还有三份报告要交……\n午饭只能边吃边写了。$"

Part5_Text_082:
	.string "我今天的目标只有一个：\n准时下班。$"

Part5_Text_083:
	.string "我是拿奖学金才来到丰缘的。\p"
	.string "这里的资料室什么都有，\n每天都有学不完的东西。$"

Part5_Text_084:
	.string "这边工作机会多，\n就是房租也涨得快。$"

Part5_Text_085:
	.string "以前这边还没这么多楼。\n我小时候常在这片空地上抓宝可梦。$"

Part5_Text_086:
	.string "员工一下班，我这摊马上坐满。\n你也来一碗吗？……开玩笑的。$"

Part5_Text_087:
	.string "园区建起来以后，交通方便多了，\n去水静买东西也近。$"

Part5_Text_088:
	.string "昨天的样本又送迟了。\n今天得把记录补齐才行。$"

Part5_Text_089:
	.string "这周已经开了四次会了……$"

Part5_Text_090:
	.string "下周还有。\n……别说了，我饿了。$"

Part5_Text_091:
	.string "我妈妈就在那栋大楼上班。\n她说从楼上能看到一整片海！$"

Part5_Text_092:
	.string "听说总部一楼有展览，\n可以免费参观哦。$"

Part5_Text_093:
	.string "欢迎来到阿尔刻集团·丰缘总部。\p"
	.string "一楼是访客中心，\n二楼是公共展示层。\p"
	.string "更高的楼层不对外开放，\n敬请谅解。$"

Part5_Text_094:
	.string "最近访客越来越多了。\n周末还有学校组织学生来参观呢。$"

Part5_Text_095:
	.string "大厅里请不要奔跑。\n休息区在右手边，可以随便坐。$"

Part5_Text_096:
	.string "这里是访客休息区。\p"
	.string "咖啡本来是给开会的人准备的，\n现在已经被喝得差不多了。$"

Part5_Text_097:
	.string "孩子吵着要来看展览，\n结果大人反倒看得更入迷。$"

Part5_Text_098:
	.string "阿尔刻集团·丰缘总部\p由集团管理委员会运营。$"

Part5_Text_099:
	.string "展示架上陈列着测量仪器的样品。\p“ARCHE 野外环境调查系列”$"

Part5_Text_100:
	.string "“环境系统研究”\p研究气候、海洋、地质与生态变化。$"

Part5_Text_101:
	.string "“生命与进化研究”\p研究宝可梦成长、形态变化\p及特殊进化现象。$"

Part5_Text_102:
	.string "“古代文明研究”\p整理遗迹、古代文字\p与地区历史资料。$"

Part5_Text_103:
	.string "再往上的区域不对外开放，\n需要员工权限才能进入。\p"
	.string "展示层这边请慢慢参观。$"

Part5_Text_104:
	.string "这一角是开放研究区。\n我们在整理各地送来的岩石样本。\p"
	.string "随便看，就是别碰标签哦。$"

Part5_Text_105:
	.string "三个部门的展板我全抄下来了，\n回去还要写参观报告呢。$"

Part5_Text_106:
	.string "这台测量仪下个月就上市了。\n价格嘛……只有研究机构买得起。$"

Part5_Text_107:
	.string "这里有些设备是集团捐的，\n恢复机器比别处的还新一点。$"

Part5_Text_108:
	.string "我是从水静坐船过来的。\p"
	.string "本来只想看看总部大楼，\n没想到在这儿遇到了好对手！$"

Part5_Text_109:
	.string "我是来交换资料的外地研究者。\n丰缘的宝可梦中心都好干净啊。$"

Part5_Text_110:
	.string "二楼的通信设备还在调试。\p"
	.string "要联机的话，\n请先去水静的宝可梦中心。$"

Part5_Text_111:
	.string "高级货还是得去水静百货买。\n这里的东西胜在离得近。$"

Part5_Text_112:
	.string "这里是员工公寓，\n走路五分钟就到办公室。\p"
	.string "唯一的坏处是，\n周末也常被叫去加班。$"

Part5_Text_113:
	.string "我上个月才搬来，\n行李箱到现在还没整理完。$"

Part5_Text_114:
	.string "楼上是住户的房间，\n请不要随便进去。$"

Part5_Text_115:
	.string "窗外就是海。\n晚上听着浪声，睡得特别香。$"

Part5_Text_116:
	.string "我们家在这里住了很多年。\n园区建起来以后，附近热闹多了。$"

Part5_Text_117:
	.string "我长大也想去那栋大楼上班！\n……不过得先学会写报告。$"

Part5_Text_118:
	.string "员工一下班，我这里马上坐满。\n中午的套餐卖得最好。$"

Part5_Text_119:
	.string "开会开到一半，偷偷溜出来喝咖啡。\n嘘，别告诉别人哦。$"

Part5_Text_120:
	.string "孩子他爸在物流区上班。\n最近港口货多，天天很晚才回家。$"

Part5_Text_121:
	.string "这块地以前是一片荒滩。\n现在的年轻人大概想象不到吧。$"

Part5_Text_122:
	.string "这批设备要送去凯那港，\n下一批还得等船期。\p"
	.string "物流这活儿，\n就是一直在等，然后一直在赶。$"

Part5_Text_123:
	.string "我们那边看不到这么多水系宝可梦。\p"
	.string "这些交换来的资料，\n我要带回去好好对照。$"

Part5_Text_124:
	.string "各地的保育资料都在这里汇总，\n野生原野区的记录也有一份。$"

Part5_Text_125:
	.string "研究交流馆对外开放。\n墙上的展板介绍了各地的合作项目。$"

Part5_Text_126:
	.string "展板上是合作地区的照片：\n雪山、火山、草原和沙漠。\p"
	.string "每张照片旁边都标着观测站的位置。$"

Part5_Text_127:
	.string "桌上摊着一本笔记，\n标题是“丰缘东部海域水温记录”。\p"
	.string "字写得密密麻麻。$"

Part5_Text_128:
	.string "我在这里实习，负责整理照片。\n每天都能看到世界各地的宝可梦！$"

Part5_Text_129:
	.string "这里是阿尔刻公开训练测试，\n记录宝可梦在不同环境下的表现。\p"
	.string "一共三场，\n中途可以休息，也可以退出。\p"
	.string "要试试吗？$"

Part5_Text_130:
	.string "开始之前，\n先帮你的宝可梦恢复一下吧。$"

Part5_Text_131:
	.string "第一场由技术员负责，\n测试项目是电气与钢铁环境。$"

Part5_Text_132:
	.string "设备运转正常，\n开始记录！$"

Part5_Text_133:
	.string "数据采集完毕。\n表现非常好！$"

Part5_Text_134:
	.string "第二场由调查员负责，\n测试项目是特殊招式的应对。$"

Part5_Text_135:
	.string "第二场测试，请多指教。\n我的招式可不按常理出牌哦。$"

Part5_Text_136:
	.string "记录完成。\n你的判断真快。$"

Part5_Text_137:
	.string "最后一场由护卫员负责，\n测试项目是综合对战。$"

Part5_Text_138:
	.string "最后一场了。\n我可不会放水。$"

Part5_Text_139:
	.string "……测试结束。\n辛苦了，你很强。$"

Part5_Text_140:
	.string "这一场的记录已经保存。\n要继续下一场吗？$"

Part5_Text_141:
	.string "好的，进度会帮你保留。\n准备好了再来前台找我。$"

Part5_Text_142:
	.string "没关系，测试随时开放，\n想参加的时候再来吧。$"

Part5_Text_143:
	.string "三场测试全部完成，\n感谢你的配合！\p"
	.string "这是公开测试的纪念品，\n据说是研究部门多出来的样品石。$"

Part5_Text_144:
	.string "测试数据会用来改进训练设备。\n再次感谢你的参与！$"

Part5_Text_145:
	.string "想对战的话，\n请先到前台登记。$"

Part5_Text_146:
	.string "我第一次来的时候，\n还以为这里只是一座普通的山。\p"
	.string "后来才知道，很多人来这里，\n是为了和离开的伙伴告别。$"

Part5_Text_147:
	.string "唉，年纪大了，\n这段山路走起来有点吃力。\p"
	.string "你要是正好要往上走，\n能不能帮我把这朵白花\p"
	.string "放到最上面那层的墓碑旁边？$"

Part5_Text_148:
	.string "就是最上面那层，\n最靠里的那块墓碑。\p"
	.string "拜托你了。$"

Part5_Text_149:
	.string "没关系，\n我自己慢慢走上去也行。$"

Part5_Text_150:
	.string "在最上面那层，\n最靠里的那块墓碑。拜托了。$"

Part5_Text_151:
	.string "放好了吗……谢谢你。\p"
	.string "那孩子以前最喜欢追着我跑。\n一转眼，已经过去这么多年了。$"

Part5_Text_152:
	.string "这个给你。\p"
	.string "是我在这座山上偶然找到的花。\n我也说不清它是什么，\p"
	.string "只是觉得，\n应该交给愿意帮忙的人。$"

Part5_Text_153:
	.string "每年这个时候我都会来。\n今年有你帮忙，轻松多了。$"

Part5_Text_154:
	.string "要把白花放在这里吗？$"

Part5_Text_155:
	.string "{PLAYER}把白色小花轻轻放在墓\n碑旁。$"

Part5_Text_156:
	.string "一块打扫得很干净的墓碑。$"

Part5_Text_157:
	.string "墓碑旁放着一朵白色小花。$"

Part5_Text_158:
	.string "阿勃梭鲁在一块墓碑前停了下来。$"

Part5_Text_159:
	.string "墓碑底下的石缝里，\n有什么东西在闪闪发光。$"

Part5_Text_160:
	.string "一块安静的墓碑。$"

Part5_Text_161:
	.string "你说那只阿勃梭鲁？\n让它待着吧。\p"
	.string "它从来没伤过人，\n只是一直守在这里。$"

Part5_Text_162:
	.string "那只阿勃梭鲁一直待在那里，\n动也不动地盯着墓碑……\p"
	.string "说实话，有点吓人。$"

Part5_Text_163:
	.string "墓碑附近的空气微微扭曲……\p好像有什么在回应彼岸花。$"

Part5_Text_164:
	.string "一块古老的墓碑。\p上面的字已经看不清了。$"

Part5_Text_165:
	.string "附近的空间让人有些不舒服。$"

Part5_Text_166:
	.string "啊！怎么又是你！\p"
	.string "我终于领到新的宝可梦了！\n上次之后我可是天天在练！\p"
	.string "这次我准备充分了，来吧！$"

Part5_Text_167:
	.string "怎么还是输了……\n明明这次准备得好好的。$"

Part5_Text_168:
	.string "……看来还是胖丁最靠得住……\p"
	.string "没、没关系！\n至少比烟囱山那次撑得久！$"

Part5_Text_169:
	.string "你先过去吧。\n我得重新想想训练方法了。$"

Part5_Text_170:
	.string "刚才整座山都在震……\n老大说，计划已经成功了。$"

Part5_Text_171:
	.string "可是我总觉得，\n这里越待越吓人。\p"
	.string "我还是先出去吧。$"

Part5_Text_172:
	.string "机器正在监测岩层温度。\n屏幕上的数字一直在往上跳。$"

Part5_Text_173:
	.string "桌上摊着烟囱山的内部结构图，\n上面画满了红色的箭头。$"

Part5_Text_174:
	.string "这里记录着不同深度的地热数据。$"

Part5_Text_175:
	.string "挖掘计划已经修改过很多次。\n最早的日期，是好几年前了。$"

Part5_Text_176:
	.string "岩壁上留着新挖开的痕迹。\n碎石里好像混着什么闪亮的东西。$"

Part5_Text_177:
	.string "等我在水梧桐老大手下赚够了钱，\n就回凯那结婚！\p"
	.string "不过现在嘛，\n我得先把你打败！$"

Part5_Text_178:
	.string "咕啊……我输了！$"

Part5_Text_179:
	.string "等一下……\n你手里拿的那个是……$"

Part5_Text_180:
	.string "{PLAYER}交出了平安符。$"

Part5_Text_181:
	.string "…………\n这是她让你带来的？$"

Part5_Text_182:
	.string "我一直跟她说，\n等我赚够了钱就回去。\p"
	.string "结果拖着拖着……\n居然让她等了这么久。$"

Part5_Text_183:
	.string "我得回去一趟。\n现在就走。$"

Part5_Text_184:
	.string "对了，\n基地里一直有个传闻。\p"
	.string "除了那颗大师球，\n还藏着一块很少见的石头。\p"
	.string "据说就在传送装置后面的房间里。\n想找的话，仔细搜搜看吧。$"

Part5_Text_185:
	.string "等赚够了钱，我就回凯那……\n再干一阵子就好。$"

Part5_Text_186:
	.string "墙边堆着潜水装备，\n柜子里塞满了防水袋。$"

Part5_Text_187:
	.string "桌上放着吃了一半的盒饭，\n墙上贴着轮班表。$"

Part5_Text_188:
	.string "墙上贴着一张纸条：\n“谁又把湿衣服扔在床上了？”$"

Part5_Text_189:
	.string "小小的储物间里堆着几个旧箱子。$"

Part5_Text_190:
	.string "今天进港的船真不少，\n搬货搬得我手都酸了。$"

Part5_Text_191:
	.string "港口正在重新核对所有人员。\n出了那种事，谁都不敢大意。$"

Part5_Text_192:
	.string "人员核对总算结束了。\n现在进出港口都得登记。$"

Part5_Text_193:
	.string "下午还有一批船要发，\n得赶在那之前把货点完。$"

Part5_Text_194:
	.string "港口现在乱成一团，\n今天这批货估计是走不了了。$"

Part5_Text_195:
	.string "总算恢复正常了。\n耽误的货，这几天得加紧送。$"

Part5_Text_196:
	.string "我在等去水静的船。\n听说那边的百货大楼特别大！$"

Part5_Text_197:
	.string "我只是来坐个船而已……\n怎么就碰上这种事了。$"

Part5_Text_198:
	.string "船总算恢复了。\n下回我还是提前一天出门吧。$"

Part5_Text_199:
	.string "这批设备今晚就要装船。\n下一船是研究材料，要送去水静。$"

Part5_Text_200:
	.string "计划全被打乱了，\n只能重新排时间。$"

Part5_Text_201:
	.string "船期总算排回来了。\n物流就是这样，一处堵，处处慢。$"

Part5_Text_202:
	.string "这里堆着几个木箱，\n侧面印着“ARCHE”的标记。$"

Part5_Text_203:
	.string "馆长最近一直在船坞那边忙，\n听说潜水艇快完工了。$"

Part5_Text_204:
	.string "库斯诺吉馆长又被卷进麻烦里了。\n希望他别太勉强自己。$"

Part5_Text_205:
	.string "以后我就在凯那找份工作。\n正好港口那边缺人手。$"

Part5_Text_206:
	.string "你真的把他找回来了！$"

Part5_Text_207:
	.string "让她等了这么久……\n这次是我做得不对。$"

Part5_Text_208:
	.string "回来就好。$"

Part5_Text_209:
	.string "谢谢你。$"

Part5_Text_210:
	.string "他寄信回来了，说很快就回来。\n……这次应该是真的吧？$"

Part5_Text_211:
	.string "他现在每天都准时回家吃饭。$"

Part5_Text_212:
	.string "水静那边好像出了什么事……\n算了，我先把今天的水温记完吧。$"

Part5_Text_213:
	.string "下面比从水面上看着要深得多。\p"
	.string "等你能潜下去的时候，\n会看到完全不一样的风景。$"

Part5_Text_214:
	.string "今天又有火箭发射吗？$"

Part5_Text_215:
	.string "哪能天天发射啊。\n不过测试的声音倒是经常有。$"

Part5_Text_216:
	.string "我们那边看不到这样的海天线。\p难怪大家都想来绿岭做观测。$"

Part5_Text_217:
	.string "每天要记录的数据比你想象得多。\n风、云、海面温度……一样都不能少。$"

Part5_Text_218:
	.string "我是阿尔刻派驻在这里的研究员，\n和宇宙中心交换一些观测数据。\p"
	.string "丰缘的地理位置很好。\n海洋、大气和高空的数据\p"
	.string "放在一起看，\n能发现很多有意思的东西。$"

Part5_Text_219:
	.string "屏幕上的数字变化得很快。$"

Part5_Text_220:
	.string "屏幕上的数字变化得很快。\p"
	.string "其中一栏写着：\n“大气能量异常值”$"

Part5_Text_221:
	.string "我总觉得太阳岩和月石\n就像两颗小星球。\p"
	.string "你见过它们吗？$"

Part5_Text_222:
	.string "你的图鉴里两种都登记了！\n流星瀑布那边真的有啊？\p"
	.string "好厉害……这个送给你！$"

Part5_Text_223:
	.string "要是两种都登记进图鉴了，\n一定要给我看看！$"

Part5_Text_224:
	.string "我长大以后要去宇宙中心工作，\n亲眼看看真正的星星！$"

Part5_Text_225:
	.string "刚才宇宙中心那边\n“砰”的一声好响……\p"
	.string "我的青绵鸟吓得飞走了。\n它平时最怕吵了……$"

Part5_Text_226:
	.string "你回来啦！\p"
	.string "下次再响的时候，\n我们两个一起捂住耳朵吧。$"

Part5_Text_227:
	.string "谢谢你帮我们找回青绵鸟。\p"
	.string "这个是我以前旅行时捡到的，\n放在家里也用不上，送给你吧。$"

Part5_Text_228:
	.string "青绵鸟应该飞不远，\n大概躲在南边不远的海边了。$"

Part5_Text_229:
	.string "现在这孩子一听到火箭的声音，\n就先把青绵鸟紧紧抱住。$"

Part5_Text_230:
	.string "青绵鸟好像想回家了。$"

Part5_Text_231:
	.string "大吾：又见面了。\n你已经走到丰缘的东边了啊。\p"
	.string "旅途中找到的石头，\n有时候比想象中更有意思哦。$"

Part5_Text_232:
	.string "小枫：咦？\p小南：你也带着它来啦！$"

