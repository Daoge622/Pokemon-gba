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
	removeobject VAR_LAST_TALKED
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
	.string "我就是为了野生原野区来的。\p坐船、换车，又走了好几天。\p既然都到这里了，来一场吧！$"

Part5_Text_003:
	.string "输了也值了，这趟没白来。$"

Part5_Text_004:
	.string "听说原野区里有好多我们那边见不到的\n宝可梦。今天一定要多看几种。$"

Part5_Text_005:
	.string "飞天螳螂才是最强的！\p他非说巨钳螳螂更厉害。\p你来评评理！用对战来评！$"

Part5_Text_006:
	.string "唔……飞天螳螂的速度明明更快……$"

Part5_Text_007:
	.string "巨钳螳螂的钢铁钳子才是最强的！\p你来评评理！用对战来评！$"

Part5_Text_008:
	.string "钳子再硬也挡不住你……$"

Part5_Text_009:
	.string "一个一个打还是分不出来……\p那就两个一起上！飞天螳螂和巨钳螳\n螂，\p这回看清楚了！$"

Part5_Text_010:
	.string "飞天螳螂！巨钳螳螂！上吧！$"

Part5_Text_011:
	.string "……两只一起都赢不了。$"

Part5_Text_012:
	.string "你得有两只能战斗的宝可梦才行。$"

Part5_Text_013:
	.string "还有一个人没比过呢。\p你也去跟他打一场，再来说哪只更强！$"

Part5_Text_014:
	.string "……算了。\p我还是喜欢我自己的。\p这块石头是我们争论时一起捡到的。\p谁拿都不合适，就送给你吧。$"

Part5_Text_015:
	.string "飞天螳螂最强。\p不对，巨钳螳螂最强！\p……我们大概会一直这么吵下去。$"

Part5_Text_016:
	.string "我负责这里的保育记录。\p园区会和其他地区交换保育资料。\p有些宝可梦原本并不生活在丰缘。\p环境适应以后，也会慢慢建立自己的族\n群。$"

Part5_Text_017:
	.string "想帮个忙吗？\p在野生原野区里成功捕获3种不同的宝\n可梦，\p再回来告诉我。\p我会照着你的捕获记录整理报告。$"

Part5_Text_018:
	.string "三种都记录到了。\p谢谢，这下报告好写多了。\p这个给你，带着它的宝可梦更容易成\n长。$"

Part5_Text_019:
	.string "原野区北边有赫拉克罗斯，西北边有凯\n罗斯。\p两种都捕获登记过的话，\p我想请你帮忙做一次对战记录。$"

Part5_Text_020:
	.string "赫拉克罗斯和凯罗斯都登记了？\p那正好，我也带着这两种。\p让我记录一下实战数据吧。$"

Part5_Text_021:
	.string "准备好了吗？开始记录！$"

Part5_Text_022:
	.string "数据很完整。谢谢你。$"

Part5_Text_023:
	.string "对战数据记好了。\p这两块石头是调查时找到的，\p和这两种宝可梦关系很深。\p给你吧。$"

Part5_Text_024:
	.string "今天的记录就到这里。\p原野区的宝可梦，你也多去看看吧。$"

Part5_Text_025:
	.string "这里是捕获用品专柜。\p各地的特殊球都有进货，\p想要什么尽管挑。$"

Part5_Text_026:
	.string "这里是训练用品专柜。\p锻炼努力值用的道具都在这里。$"

Part5_Text_027:
	.string "这里是薄荷专柜。\p价格有点贵，\p不过效果是实打实的。$"

Part5_Text_028:
	.string "这里是属性持有物专柜。\p以前只能在野外偶然捡到，\p现在都能直接买了。$"

Part5_Text_029:
	.string "这里是对战道具专柜。\p进货不多，每样每位客人限购一个。$"

Part5_Text_030:
	.string "这里的商品来源很杂。\p丰缘自产的，外地运来的都有。$"

Part5_Text_031:
	.string "“ARCHE 野外环境调查系列”\p面向研究机构及专业调查人员。\p气象、土壤与宝可梦活动记录仪……\p展示柜里的设备看起来很精密。$"

Part5_Text_032:
	.string "这些设备挺贵的。\p听说测天气、土壤和宝可梦活动都能\n用。\p119号道路那边好像也有人在用。$"

Part5_Text_033:
	.string "哎呀，我的购物清单不见了。\p刚才在楼上逛的时候还在手里……\p你要是看到了，帮我拿回来好吗？$"

Part5_Text_034:
	.string "有了有了。\p年纪大了，买三样东西都得写下来。\p谢谢你啊，这个拿去吧。$"

Part5_Text_035:
	.string "这回清单我可要拿好了。$"

Part5_Text_036:
	.string "地上掉着一张纸。\p上面写着“毛巾、茶叶、电池”。\p好像是谁的购物清单。$"

Part5_Text_037:
	.string "糟了。\p我把丈夫今天的午饭拿错了。\p他在阿尔刻园区的物流部门上班。\p园区就在海滨大道那头……\p能帮我把这个便当送过去吗？$"

Part5_Text_038:
	.string "太好了！东海滩那栋小楼就是去海滨大\n道的入口。$"

Part5_Text_039:
	.string "也是，突然拜托你这种事……\p我再想想办法。$"

Part5_Text_040:
	.string "物流部门在园区的仓库办公室。\p拜托你了。$"

Part5_Text_041:
	.string "他吃到了吗？太好了。\p早上太急，把我自己的点心盒装进去\n了。\p这个给你，谢谢你跑这一趟。$"

Part5_Text_042:
	.string "今天我可是检查了三遍才出门的。$"

Part5_Text_043:
	.string "今天的午饭有点奇怪……\p算了，先把这批出货单核完。$"

Part5_Text_044:
	.string "这是……我的便当？\p难怪今天打开袋子，里面全是甜的……\p谢谢你跑这一趟。$"

Part5_Text_045:
	.string "回去也替我跟她说一声谢谢。$"

Part5_Text_046:
	.string "嗯？你好像要找我？$"

Part5_Text_047:
	.string "吃饱了才有力气搬货。\p下午还有三车设备要发。$"

Part5_Text_048:
	.string "我女儿今天第一次正式参加华丽大赛。\p可我这边柜台走不开……\p她带着奇鲁莉安，现在一定很紧张。\p能帮我把这个缎带盒交给她吗？\p她应该在大赛会场门口。$"

Part5_Text_049:
	.string "……也对，等我下班再说吧。$"

Part5_Text_050:
	.string "大赛会场就在宝可梦中心南边。\p拜托你了。$"

Part5_Text_051:
	.string "她收下了？\p……那就好。\p我这边结束得早的话，也去看看。$"

Part5_Text_052:
	.string "她真的参加了？\p谢谢你。\p这个以前一直和那条缎带放在一起。\p我也不知道有什么用。$"

Part5_Text_053:
	.string "哎呀，你也带着这个家族的宝可梦。\p看来它也很喜欢你呢。$"

Part5_Text_054:
	.string "下次比赛，我一定请假去看。$"

Part5_Text_055:
	.string "马上就要轮到我了……\p奇鲁莉安也在发抖。\p……要不还是下次再来吧。$"

Part5_Text_056:
	.string "妈妈让你送来的？$"

Part5_Text_057:
	.string "这是我小时候的缎带……\p…………\p好。\p那我进去试试。$"

Part5_Text_058:
	.string "马上就要轮到我了……$"

Part5_Text_059:
	.string "虽然没拿第一……\p但是我没有逃跑！\p奇鲁莉安也表现得很好。$"

Part5_Text_060:
	.string "我每次来水静，都会顺便看看外地货。\p今天又多买了两袋。$"

Part5_Text_061:
	.string "忙的时候，午饭都得站着吃。\p今天到港的船特别多。$"

Part5_Text_062:
	.string "第一次领工资的时候，\p我在百货花掉了一半。$"

Part5_Text_063:
	.string "你还好意思说。\p那个月最后几天，天天来蹭我的饭。$"

Part5_Text_064:
	.string "本来只想住两天。\p结果逛着逛着，已经住一个星期了。$"

Part5_Text_065:
	.string "我们年轻的时候，第一次约会就在这\n里。$"

Part5_Text_066:
	.string "那时候还没这么热闹。\p现在楼越盖越高，海倒是没变。$"

Part5_Text_067:
	.string "水静海滨大道 入口站\p前方：阿尔刻园区$"

Part5_Text_068:
	.string "水静海滨大道\p西：阿尔刻园区　东：水静市$"

Part5_Text_069:
	.string "每天早上沿着海边跑一圈，\p跑完正好赶上园区的班车。$"

Part5_Text_070:
	.string "从水静走过来只要一会儿。\p那边的大楼就是阿尔刻的丰缘总部吧？\p拍张照回去给朋友看看。$"

Part5_Text_071:
	.string "冰淇淋、汽水，还有釜炎仙贝！\p下班时间人最多，现在还算清闲。$"

Part5_Text_072:
	.string "这条路平坦又宽，\p骑自行车最舒服了。$"

Part5_Text_073:
	.string "早上的货车又把路口堵住了。\p我还是走路上班比较快。$"

Part5_Text_074:
	.string "路边停着几辆运货车。\p车厢上印着“ARCHE 物流”。$"

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
	.string "下午还有三个报告要交……$"

Part5_Text_082:
	.string "我今天只想准时下班。$"

Part5_Text_083:
	.string "我是拿奖学金才有机会来丰缘的。\p这里的资料室什么都有，\p每天都学不完。$"

Part5_Text_084:
	.string "这边工作机会多，\p房租也涨得快。$"

Part5_Text_085:
	.string "以前这边还没这么多楼。\p我小时候常在这片空地上抓宝可梦。$"

Part5_Text_086:
	.string "员工一下班，我这里马上就坐满。\p你也来一碗吗？……开玩笑的。$"

Part5_Text_087:
	.string "园区建起来以后，交通方便多了。\p去水静买东西也近。$"

Part5_Text_088:
	.string "昨天的样本又送迟了。\p今天得把记录补齐。$"

Part5_Text_089:
	.string "这周已经开了四次会。$"

Part5_Text_090:
	.string "下周还有。\p……别说了，我饿了。$"

Part5_Text_091:
	.string "我妈妈就在那栋大楼工作。\p她说楼上能看到整片海！$"

Part5_Text_092:
	.string "听说总部一楼有展览，\p可以免费参观。$"

Part5_Text_093:
	.string "欢迎来到阿尔刻集团·丰缘总部。\p一楼是访客中心，\p二楼是公共展示层。\p上面的楼层不对外开放，敬请谅解。$"

Part5_Text_094:
	.string "访客最近越来越多了。\p周末还有学校组织来参观呢。$"

Part5_Text_095:
	.string "大厅里请不要奔跑。\p休息区在右手边，可以随便坐。$"

Part5_Text_096:
	.string "这里是访客休息区。\p咖啡是给开会的人准备的，\p已经被喝得差不多了。$"

Part5_Text_097:
	.string "孩子吵着要来看展览。\p没想到大人也看得挺入迷的。$"

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
	.string "上面的区域不对外开放。\p需要员工权限。\p展示层这边可以慢慢看。$"

Part5_Text_104:
	.string "这一角是开放研究区。\p我们在整理各地送来的岩石样本，\p看看就好，别碰标签哦。$"

Part5_Text_105:
	.string "三个部门的展板我都抄下来了。\p回去要写参观报告。$"

Part5_Text_106:
	.string "这台测量仪下个月就要上市了。\p价格嘛……研究机构才买得起。$"

Part5_Text_107:
	.string "这里有些设备是集团捐的。\p恢复机器比别处的新一点。$"

Part5_Text_108:
	.string "我从水静坐船来的。\p本来只想看看总部大楼，\p结果在这儿找到了好对手。$"

Part5_Text_109:
	.string "我是来交换资料的外地研究者。\p丰缘的宝可梦中心都很干净。$"

Part5_Text_110:
	.string "二楼的通信设备还在调试。\p联机的话请先去水静的宝可梦中心。$"

Part5_Text_111:
	.string "高级货还是得去水静百货买。\p这里的东西胜在近。$"

Part5_Text_112:
	.string "这里是员工公寓。\p离办公室走路五分钟，\p可惜周末也会被叫去加班。$"

Part5_Text_113:
	.string "我上个月才搬来。\p行李箱还没打开完。$"

Part5_Text_114:
	.string "楼上是住户的房间，请不要随便进去。$"

Part5_Text_115:
	.string "窗外就是海。\p晚上能听见浪的声音，睡得特别好。$"

Part5_Text_116:
	.string "我们家在这里住了很多年。\p园区建起来以后，附近热闹多了。$"

Part5_Text_117:
	.string "我长大也想去那栋大楼上班！\p……不过要先学会写报告。$"

Part5_Text_118:
	.string "员工一下班，我这里马上就坐满。\p中午的套餐卖得最好。$"

Part5_Text_119:
	.string "开会开到一半偷偷溜出来喝咖啡。\p嘘，别告诉别人。$"

Part5_Text_120:
	.string "孩子他爸在物流区上班。\p最近港口的货多，回家都很晚。$"

Part5_Text_121:
	.string "这块地以前是片荒滩。\p现在的年轻人大概想象不到吧。$"

Part5_Text_122:
	.string "这批设备要送去凯那港，\p下一批要等船期。\p物流的工作就是一直在等和赶。$"

Part5_Text_123:
	.string "我们那边看不到这么多水系宝可梦。\p交换来的资料，我要带回去好好对照。$"

Part5_Text_124:
	.string "各地的保育资料都在这里汇总。\p野生原野区的记录也有一份。$"

Part5_Text_125:
	.string "研究交流馆对外开放。\p墙上的展板介绍了各地合作的项目。$"

Part5_Text_126:
	.string "展板上是合作地区的照片：\p雪山、火山、草原和沙漠。\p每张照片旁都标着观测站的位置。$"

Part5_Text_127:
	.string "桌上摊着一本笔记。\p“丰缘东部海域水温记录”……\p字写得密密麻麻。$"

Part5_Text_128:
	.string "我在这里实习，负责整理照片。\p每天能看到世界各地的宝可梦。$"

Part5_Text_129:
	.string "这里是公开训练测试。\p主要记录宝可梦在不同战斗环境里的表\n现。\p一共三场，中途可以休息或退出。\p想试试吗？$"

Part5_Text_130:
	.string "开始前先帮你的宝可梦恢复一下。$"

Part5_Text_131:
	.string "第一场，技术员负责。\p测试项目是电气与钢铁环境。$"

Part5_Text_132:
	.string "设备运转正常，开始记录！$"

Part5_Text_133:
	.string "数据采集完毕。表现很好。$"

Part5_Text_134:
	.string "第二场，调查员负责。\p测试项目是特殊招式的应对。$"

Part5_Text_135:
	.string "第二场测试，请多指教。$"

Part5_Text_136:
	.string "记录完成。你的判断很快。$"

Part5_Text_137:
	.string "最后一场，护卫员负责。\p测试项目是综合对战。$"

Part5_Text_138:
	.string "最后一场，我不会放水。$"

Part5_Text_139:
	.string "……测试结束。辛苦了。$"

Part5_Text_140:
	.string "这一场的记录已经保存。\p要继续下一场吗？$"

Part5_Text_141:
	.string "好的，进度会保留。\p准备好了再来前台找我。$"

Part5_Text_142:
	.string "没关系，测试随时开放。$"

Part5_Text_143:
	.string "三场记录完成。\p谢谢配合。\p这是公开测试活动的纪念品，\p据说是研究部门多出来的样品石。$"

Part5_Text_144:
	.string "测试数据会用来改进训练设备。\p再次感谢你的参与。$"

Part5_Text_145:
	.string "对战请先到前台登记。$"

Part5_Text_146:
	.string "第一次来的时候，\p我以为这里只是一座山。\p后来才知道，很多人会来这里\p和离开的伙伴告别。$"

Part5_Text_147:
	.string "年纪大了。\p这段山路现在走起来有点吃力。\p如果你正好要往上走……\p帮我把它放到最上面的墓碑旁吧。$"

Part5_Text_148:
	.string "最上面那层，靠里的那块墓碑。\p拜托你了。$"

Part5_Text_149:
	.string "没关系，我慢慢走也行。$"

Part5_Text_150:
	.string "最上面那层，靠里的那块墓碑。$"

Part5_Text_151:
	.string "放好了吗……谢谢。\p它以前特别喜欢追着我跑。\p一转眼，已经过去这么多年了。$"

Part5_Text_152:
	.string "这个给你。\p是在这座山上偶然找到的花。\p我也说不清它是什么，\p只是觉得该交给愿意帮忙的人。$"

Part5_Text_153:
	.string "每年这个时候我都会来。\p今年有你帮忙，轻松多了。$"

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
	.string "墓碑底下的石缝里\p有什么东西在发光。$"

Part5_Text_160:
	.string "一块安静的墓碑。$"

Part5_Text_161:
	.string "那只阿勃梭鲁？\p让它待着吧。\p它从来没伤过人，\p只是一直守在这里。$"

Part5_Text_162:
	.string "那只阿勃梭鲁一直在那里，\p动也不动地看着墓碑……\p有点吓人。$"

Part5_Text_163:
	.string "墓碑附近的空气微微扭曲……\p好像有什么在回应彼岸花。$"

Part5_Text_164:
	.string "一块古老的墓碑。\p上面的字已经看不清了。$"

Part5_Text_165:
	.string "附近的空间让人有些不舒服。$"

Part5_Text_166:
	.string "啊！\p怎么又是你！\p这次我准备好了！\p我终于领到新的宝可梦了！\p上次之后，我一直都有训练！\p来吧！$"

Part5_Text_167:
	.string "怎么还是输了……\p明明这次都准备好了。$"

Part5_Text_168:
	.string "……\p胖丁果然最靠谱……\p没、没关系！\p至少比烟囱山那次撑得久！$"

Part5_Text_169:
	.string "你先过去吧。\p我要重新想想训练方法。$"

Part5_Text_170:
	.string "刚才整座山都在震……\p老大说，计划已经成功了。$"

Part5_Text_171:
	.string "可是我总觉得……\p这里待着有点吓人。\p我还是先出去吧。$"

Part5_Text_172:
	.string "机器正在监测岩层温度。\p屏幕上的数字一直在往上跳。$"

Part5_Text_173:
	.string "桌上摊着烟囱山内部结构图。\p上面画满了红色的箭头。$"

Part5_Text_174:
	.string "这里记录着不同深度的地热数据。$"

Part5_Text_175:
	.string "挖掘计划已经修改过很多次。\p最早的日期，已经是好几年前了。$"

Part5_Text_176:
	.string "岩壁上留着新挖开的痕迹。\p碎石里好像混着什么闪亮的东西。$"

Part5_Text_177:
	.string "等我在水梧桐老大手下赚够了钱，\p我就打算回凯那结婚！\p不过现在，\p我得先打败你！$"

Part5_Text_178:
	.string "咕啊……我输了！$"

Part5_Text_179:
	.string "等一下……\p你手里那个是……$"

Part5_Text_180:
	.string "{PLAYER}交出了平安符。$"

Part5_Text_181:
	.string "…………\p这是她让你带来的？$"

Part5_Text_182:
	.string "我一直跟她说，\p等我赚够钱就回去。\p结果拖着拖着……\p居然让她等了这么久。$"

Part5_Text_183:
	.string "我得回去一趟。$"

Part5_Text_184:
	.string "对了。\p基地里一直有个传闻。\p除了那颗大师球，\p还有一块很少见的石头。\p好像藏在传送装置后面的房间。\p你想找的话，就仔细看看。$"

Part5_Text_185:
	.string "赚够了钱，我就回凯那……\p再干一阵子就好。$"

Part5_Text_186:
	.string "墙边堆着潜水装备。\p柜子里塞满防水袋。$"

Part5_Text_187:
	.string "桌上放着吃了一半的盒饭。\p墙上贴着轮班表。$"

Part5_Text_188:
	.string "一张纸条贴在墙上：\p“谁又把湿衣服扔在床上了？”$"

Part5_Text_189:
	.string "小小的储物间里堆着几个旧箱子。$"

Part5_Text_190:
	.string "今天进港的船不少，\p搬货搬到手都酸了。$"

Part5_Text_191:
	.string "港口正在重新核对所有人员。\p出了那种事，谁都不敢大意。$"

Part5_Text_192:
	.string "核对总算结束了。\p现在进出港口都要登记。$"

Part5_Text_193:
	.string "下午还有一批船要发。\p得赶在那之前把货点完。$"

Part5_Text_194:
	.string "港口现在乱成一团。\p今天这批货估计走不了了。$"

Part5_Text_195:
	.string "总算又正常了。\p耽误的货，这几天要加紧送。$"

Part5_Text_196:
	.string "我在等去水静的船。\p听说那边的百货很大。$"

Part5_Text_197:
	.string "我只是来坐船的……\p怎么就碰上这种事。$"

Part5_Text_198:
	.string "船终于恢复了。\p下回我还是早一天出门吧。$"

Part5_Text_199:
	.string "这批设备今晚就要装船。\p下一船是研究材料，要送去水静。$"

Part5_Text_200:
	.string "计划全打乱了。\p只能重新排时间。$"

Part5_Text_201:
	.string "船期总算排回来了。\p物流就是这样，一处堵住，处处都慢。$"

Part5_Text_202:
	.string "堆着几个木箱。\p箱子侧面印着“ARCHE”的标记。$"

Part5_Text_203:
	.string "馆长最近一直在船坞那边忙。\p听说潜水艇快完工了。$"

Part5_Text_204:
	.string "库斯诺吉馆长又被卷进麻烦里了。\p希望他别太勉强自己。$"

Part5_Text_205:
	.string "以后我就在凯那找份工作。\p港口那边正好缺人手。$"

Part5_Text_206:
	.string "你真的找到他了！$"

Part5_Text_207:
	.string "让她等这么久……\p这次是我做得不对。$"

Part5_Text_208:
	.string "回来就好。$"

Part5_Text_209:
	.string "谢谢。$"

Part5_Text_210:
	.string "他寄信回来了，说很快就回来。\p……这次应该是真的吧？$"

Part5_Text_211:
	.string "他现在每天都准时回家吃饭。$"

Part5_Text_212:
	.string "水静那边好像出了什么事。\p……\p我还是先把今天的水温记录完吧。$"

Part5_Text_213:
	.string "下面比从水面看起来深得多。\p以后能潜下去的话，\p会看到完全不同的景色。$"

Part5_Text_214:
	.string "今天又有火箭发射吗？$"

Part5_Text_215:
	.string "哪有天天发的。\p不过测试的声音倒是经常有。$"

Part5_Text_216:
	.string "我们那边看不到这样的海天线。\p难怪大家都想来绿岭做观测。$"

Part5_Text_217:
	.string "每天要记录的数据比你想象得多。\p风、云、海面温度……\p一样都不能少。$"

Part5_Text_218:
	.string "我是阿尔刻派驻在这里的研究员。\p我们和这里交换一些观测数据。\p丰缘的位置很好。\p海洋、大气和高空数据，\p放在一起看会更有意思。$"

Part5_Text_219:
	.string "屏幕上的数字变化得很快。$"

Part5_Text_220:
	.string "屏幕上的数字变化得很快。\p其中一栏写着：\p“大气能量异常值”$"

Part5_Text_221:
	.string "我总觉得太阳岩和月石\p像两个小星球。\p你见过它们吗？$"

Part5_Text_222:
	.string "你的图鉴里两种都登记了！\p流星瀑布那边真的有吗？\p好厉害……这个给你！$"

Part5_Text_223:
	.string "要是两种都登记在图鉴上，\p一定要给我看看！$"

Part5_Text_224:
	.string "长大以后我要去宇宙中心工作，\p亲眼看看真正的星星。$"

Part5_Text_225:
	.string "刚才宇宙中心那边响了一声好大的……\p我的青绵鸟吓得飞走了。\p它平时最怕吵了……$"

Part5_Text_226:
	.string "你回来啦！\p下次再响的时候，\p我们两个一起捂耳朵。$"

Part5_Text_227:
	.string "谢谢你。\p这个是以前旅行时捡到的。\p放在家里也用不上，送给你吧。$"

Part5_Text_228:
	.string "青绵鸟应该飞不远，\p大概躲在海边哪里了。$"

Part5_Text_229:
	.string "这孩子现在一听到火箭的声音，\p就先把青绵鸟抱紧。$"

Part5_Text_230:
	.string "青绵鸟好像想回家了。$"

Part5_Text_231:
	.string "大吾：又见面了。\p看来你已经走到丰缘东边了。\p旅途中找到的石头，\p有时候比想象中更有意思。$"

Part5_Text_232:
	.string "小枫：咦？\p小南：你也带着它来啦！$"

