@ PART5.5 additions. See docs/story/PART5_5_DRAFT.md; remains DRAFT.
Part55_BagFull::
	msgbox Part55_Text_0001, MSGBOX_DEFAULT
	releaseall
	end


Part55_Text_0001:
	.string "背包已经放不下了。腾出位置以后，再\n来找我吧。$"
Part55_CargoDriver::
	msgbox Part55_Text_0002, MSGBOX_NPC
	end


Part55_CargoHelper::
	msgbox Part55_Text_0003, MSGBOX_NPC
	end


Part55_CargoMate::
	msgbox Part55_Text_0004, MSGBOX_NPC
	end


Part55_HarborNotice::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, Part55_HarborNotice_Restored
	goto_if_ge VAR_SLATEPORT_HARBOR_STATE, 2, Part55_HarborNotice_Stopped
	msgbox Part55_Text_0005, MSGBOX_DEFAULT
	release
	end


Part55_HarborNotice_Stopped::
	msgbox Part55_Text_0006, MSGBOX_DEFAULT
	release
	end


Part55_HarborNotice_Restored::
	msgbox Part55_Text_0007, MSGBOX_DEFAULT
	release
	end


Part55_BoatFather::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, Part55_BoatFather_Restored
	goto_if_ge VAR_SLATEPORT_HARBOR_STATE, 2, Part55_BoatFather_Stopped
	msgbox Part55_Text_0008, MSGBOX_DEFAULT
	release
	end


Part55_BoatFather_Stopped::
	msgbox Part55_Text_0009, MSGBOX_DEFAULT
	release
	end


Part55_BoatFather_Restored::
	msgbox Part55_Text_0010, MSGBOX_DEFAULT
	release
	end


Part55_BoatChild::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, Part55_BoatChild_Restored
	goto_if_ge VAR_SLATEPORT_HARBOR_STATE, 2, Part55_BoatChild_Stopped
	msgbox Part55_Text_0011, MSGBOX_DEFAULT
	release
	end


Part55_BoatChild_Stopped::
	msgbox Part55_Text_0012, MSGBOX_DEFAULT
	release
	end


Part55_BoatChild_Restored::
	msgbox Part55_Text_0013, MSGBOX_DEFAULT
	release
	end


Part55_Manifest::
	lock
	faceplayer
	goto_if_ge VAR_PART55_MANIFEST, 1, Part55_Manifest_After
	msgbox Part55_Text_0014, MSGBOX_DEFAULT
	giveitem ITEM_SHIPPING_MANIFEST, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_MANIFEST, 1
	release
	end


Part55_Manifest_After::
	msgbox Part55_Text_0015, MSGBOX_DEFAULT
	release
	end


Part55_ManifestWorker::
	lock
	faceplayer
	goto_if_eq VAR_PART55_MANIFEST, 3, Part55_ManifestWorker_Done
	goto_if_ne VAR_PART55_MANIFEST, 1, Part55_ManifestWorker_Wait
	checkitem ITEM_SHIPPING_MANIFEST, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_ManifestWorker_Wait
	msgbox Part55_Text_0016, MSGBOX_DEFAULT
	giveitem ITEM_NUGGET, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_SHIPPING_MANIFEST, 1
	setvar VAR_PART55_MANIFEST, 3
	release
	end


Part55_ManifestWorker_Wait::
	msgbox Part55_Text_0017, MSGBOX_DEFAULT
	release
	end


Part55_ManifestWorker_Done::
	msgbox Part55_Text_0018, MSGBOX_DEFAULT
	release
	end


Part55_LuggageOwner::
	lock
	faceplayer
	goto_if_eq VAR_PART55_LUGGAGE, 3, Part55_LuggageOwner_Done
	goto_if_eq VAR_PART55_LUGGAGE, 2, Part55_LuggageOwner_Reward
	goto_if_eq VAR_PART55_LUGGAGE, 1, Part55_LuggageOwner_Wait
	msgbox Part55_Text_0019, MSGBOX_DEFAULT
	giveitem ITEM_WRONG_LUGGAGE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_LUGGAGE, 1
	release
	end


Part55_LuggageOwner_Wait::
	msgbox Part55_Text_0020, MSGBOX_DEFAULT
	release
	end


Part55_LuggageOwner_Reward::
	checkitem ITEM_CORRECT_LUGGAGE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_LuggageOwner_Wait
	msgbox Part55_Text_0021, MSGBOX_DEFAULT
	giveitem ITEM_FULL_RESTORE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_CORRECT_LUGGAGE, 1
	setvar VAR_PART55_LUGGAGE, 3
	release
	end


Part55_LuggageOwner_Done::
	msgbox Part55_Text_0022, MSGBOX_DEFAULT
	release
	end


Part55_LuggageTraveler::
	lock
	faceplayer
	goto_if_ne VAR_PART55_LUGGAGE, 1, Part55_LuggageTraveler_After
	checkitem ITEM_WRONG_LUGGAGE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_LuggageTraveler_After
	msgbox Part55_Text_0023, MSGBOX_DEFAULT
	giveitem ITEM_CORRECT_LUGGAGE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_WRONG_LUGGAGE, 1
	setvar VAR_PART55_LUGGAGE, 2
	release
	end


Part55_LuggageTraveler_After::
	msgbox Part55_Text_0024, MSGBOX_DEFAULT
	release
	end


Part55_Souvenir::
	lock
	faceplayer
	goto_if_ge VAR_PART55_SOUVENIR, 1, Part55_Souvenir_After
	msgbox Part55_Text_0025, MSGBOX_DEFAULT
	giveitem ITEM_WRAPPED_SOUVENIR, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_SOUVENIR, 1
	release
	end


Part55_Souvenir_After::
	msgbox Part55_Text_0026, MSGBOX_DEFAULT
	release
	end


Part55_SouvenirTraveler::
	lock
	faceplayer
	goto_if_eq VAR_PART55_SOUVENIR, 3, Part55_SouvenirTraveler_Done
	goto_if_ne VAR_PART55_SOUVENIR, 1, Part55_SouvenirTraveler_Wait
	checkitem ITEM_WRAPPED_SOUVENIR, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_SouvenirTraveler_Wait
	msgbox Part55_Text_0027, MSGBOX_DEFAULT
	giveitem ITEM_ULTRA_BALL, 3
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_WRAPPED_SOUVENIR, 1
	setvar VAR_PART55_SOUVENIR, 3
	release
	end


Part55_SouvenirTraveler_Wait::
	msgbox Part55_Text_0028, MSGBOX_DEFAULT
	release
	end


Part55_SouvenirTraveler_Done::
	msgbox Part55_Text_0029, MSGBOX_DEFAULT
	release
	end


Part55_SoloTraveler::
	lock
	faceplayer
	goto_if_ge VAR_PART55_SOLO_TRAVEL, 3, Part55_SoloTraveler_Later
	goto_if_eq VAR_PART55_SOLO_TRAVEL, 2, Part55_SoloTraveler_Called
	msgbox Part55_Text_0030, MSGBOX_DEFAULT
	release
	end


Part55_SoloTraveler_Called::
	msgbox Part55_Text_0031, MSGBOX_DEFAULT
	release
	end


Part55_SoloTraveler_Later::
	msgbox Part55_Text_0032, MSGBOX_DEFAULT
	release
	end


Part55_TravelerEevee::
	lock
	faceplayer
	playmoncry SPECIES_EEVEE, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_DeptChild::
	lock
	faceplayer
	goto_if_eq VAR_PART55_DEPT_CHILD, 3, Part55_DeptChild_Done
	goto_if_eq VAR_PART55_DEPT_CHILD, 2, Part55_DeptChild_Reward
	setvar VAR_PART55_DEPT_CHILD, 1
	msgbox Part55_Text_0033, MSGBOX_DEFAULT
	release
	end


Part55_DeptChild_Reward::
	msgbox Part55_Text_0034, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_DEPT_CHILD, 3
	release
	end


Part55_DeptChild_Done::
	msgbox Part55_Text_0035, MSGBOX_DEFAULT
	release
	end


Part55_DeptMother::
	lock
	faceplayer
	goto_if_ge VAR_PART55_DEPT_CHILD, 2, Part55_DeptMother_After
	goto_if_ne VAR_PART55_DEPT_CHILD, 1, Part55_DeptMother_Wait
	setvar VAR_PART55_DEPT_CHILD, 2
	msgbox Part55_Text_0036, MSGBOX_DEFAULT
	release
	end


Part55_DeptMother_After::
	msgbox Part55_Text_0037, MSGBOX_DEFAULT
	release
	end


Part55_DeptMother_Wait::
	msgbox Part55_Text_0038, MSGBOX_DEFAULT
	release
	end


Part55_FabricClerk::
	lock
	faceplayer
	goto_if_ge VAR_PART55_FABRIC, 1, Part55_FabricClerk_After
	msgbox Part55_Text_0039, MSGBOX_DEFAULT
	giveitem ITEM_SOFT_FABRIC, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_FABRIC, 1
	release
	end


Part55_FabricClerk_After::
	msgbox Part55_Text_0040, MSGBOX_DEFAULT
	release
	end


Part55_Designer::
	lock
	faceplayer
	goto_if_eq VAR_PART55_FABRIC, 3, Part55_Designer_Done
	goto_if_ne VAR_PART55_FABRIC, 1, Part55_Designer_Wait
	checkitem ITEM_SOFT_FABRIC, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_Designer_Wait
	msgbox Part55_Text_0041, MSGBOX_DEFAULT
	giveitem ITEM_LOPUNNITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_SOFT_FABRIC, 1
	setvar VAR_PART55_FABRIC, 3
	release
	end


Part55_Designer_Wait::
	msgbox Part55_Text_0042, MSGBOX_DEFAULT
	release
	end


Part55_Designer_Done::
	msgbox Part55_Text_0043, MSGBOX_DEFAULT
	release
	end


Part55_Buneary::
	lock
	faceplayer
	playmoncry SPECIES_BUNEARY, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_TriAttackTutor::
	lock
	faceplayer
	move_tutor MOVE_TRI_ATTACK, Part55_Text_0044, Part55_Text_0045, Part55_TriAttackTutor_End, Part55_TriAttackTutor_Done


Part55_TriAttackTutor_Done::
	msgbox Part55_Text_0046, MSGBOX_DEFAULT
	release
	end


Part55_TriAttackTutor_End::
	release
	end


Part55_HelpingHandTutor::
	lock
	faceplayer
	move_tutor MOVE_HELPING_HAND, Part55_Text_0047, Part55_Text_0048, Part55_HelpingHandTutor_End, Part55_HelpingHandTutor_Done


Part55_HelpingHandTutor_Done::
	msgbox Part55_Text_0049, MSGBOX_DEFAULT
	release
	end


Part55_HelpingHandTutor_End::
	release
	end


Part55_FirstSalary::
	msgbox Part55_Text_0050, MSGBOX_NPC
	end


Part55_SalaryFriend::
	msgbox Part55_Text_0051, MSGBOX_NPC
	end


Part55_WrongGear::
	goto_if_defeated TRAINER_PART5_SCYTHER_FAN, StoryC_WrongGear_Talk
	trainerbattle_double TRAINER_STORY_C_02, StoryC_Text_GearIntro, StoryC_Text_GearDefeat, StoryC_Text_GearNotEnough, StoryC_WrongGear_Won
	release
	end


Part55_GearFriend::
	goto_if_defeated TRAINER_PART5_SCYTHER_FAN, StoryC_GearFriend_Talk
	trainerbattle_double TRAINER_STORY_C_02, StoryC_Text_GearIntro, StoryC_Text_GearDefeat, StoryC_Text_GearNotEnough, StoryC_GearFriend_Won
	release
	end


Part55_MuseumVisitor::
	msgbox Part55_Text_0054, MSGBOX_NPC
	end


Part55_ContestLoser::
	msgbox Part55_Text_0055, MSGBOX_NPC
	end


Part55_ContestPhotographer::
	msgbox Part55_Text_0056, MSGBOX_NPC
	end


Part55_BackstageStaff::
	msgbox Part55_Text_0057, MSGBOX_NPC
	end


Part55_FoodStall::
	msgbox Part55_Text_0058, MSGBOX_NPC
	end


Part55_SouvenirStall::
	msgbox Part55_Text_0059, MSGBOX_NPC
	end


Part55_TravelStall::
	msgbox Part55_Text_0060, MSGBOX_NPC
	end


Part55_Text_0002:
	.string "车再停五分钟。刚搬完的箱子还有点晃\n。$"

Part55_Text_0003:
	.string "午饭以后还有两车。先喝口水再说。$"

Part55_Text_0004:
	.string "水静的货一天比一天多。我都快记不清\n卸货口了。$"

Part55_Text_0005:
	.string "航运公告：客船和货船按表运行。请在\n检票前确认目的地。$"

Part55_Text_0006:
	.string "航运公告：部分航线暂时停运。请留意\n港口的后续通知。$"

Part55_Text_0007:
	.string "航运公告：航线正在逐步恢复。新时刻\n表将在这里公布。$"

Part55_Text_0008:
	.string "我答应带孩子坐船，已经查了三遍时刻\n表。$"

Part55_Text_0009:
	.string "孩子一直问船什么时候开。等新通知出\n来再说吧。$"

Part55_Text_0010:
	.string "总算能重新安排出游了！这回可要先收\n好船票。$"

Part55_Text_0011:
	.string "到了船上，我要坐靠窗的位置！$"

Part55_Text_0012:
	.string "爸爸说船今天不能开。我带的零食都快\n吃完了。$"

Part55_Text_0013:
	.string "终于能坐船啦！我把零食也补满了。$"

Part55_Text_0014:
	.string "长椅下面落了一张运输清单。上面写着\n“水静港口”。$"

Part55_Text_0015:
	.string "这件东西请交给它的主人。$"

Part55_Text_0016:
	.string "我的运输清单！刚才风一吹，就不见了\n。谢谢你帮我带回来。$"

Part55_Text_0017:
	.string "要是见到我遗落的东西，能帮我带回来\n吗？$"

Part55_Text_0018:
	.string "今天这批有合众来的训练用品，也有城\n都的日用品。清点起来可得仔细。$"

Part55_Text_0019:
	.string "我拿错行李了！码头有位戴帽子的旅客\n，能请你帮我换回来吗？$"

Part55_Text_0020:
	.string "那位旅客应该还在港口。我的行李是蓝\n色的。$"

Part55_Text_0021:
	.string "对，就是这只！实在太感谢了。$"

Part55_Text_0022:
	.string "这回出门，我会先看看行李上的名字。$"

Part55_Text_0023:
	.string "原来拿到旅馆去了！我也正找这只箱子\n呢。来，换回来。$"

Part55_Text_0024:
	.string "箱子的样子太像了。我得绑条缎带做记\n号。$"

Part55_Text_0025:
	.string "房间里有一份包好的纪念品。包装上写\n着“海边买的”。$"

Part55_Text_0026:
	.string "这件东西请交给它的主人。$"

Part55_Text_0027:
	.string "我把送给家人的礼物忘在旅馆了！幸好\n还没坐船走。这个请收下。$"

Part55_Text_0028:
	.string "要是见到我遗落的东西，能帮我带回来\n吗？$"

Part55_Text_0029:
	.string "下次见到家人，就把水静海边的事讲给\n他们听。$"

Part55_Text_0030:
	.string "第一次一个人旅行。伊布睡得倒很香，\n我却有点想家。等会儿给家里打个电话\p吧。$"

Part55_Text_0031:
	.string "刚给家里打过电话，妈妈叮嘱我多拍几\n张照片。明天想带伊布去原野区看看。$"

Part55_Text_0032:
	.string "原野区之旅已经准备好了。伊布的点心\n也带上了！$"

Part55_Text_0033:
	.string "妈妈刚才说要去看装饰品，可我记不住\n是哪一层了……能帮我找找吗？$"

Part55_Text_0034:
	.string "妈妈回来啦！谢谢你。妈妈说这个可以\n给你。$"

Part55_Text_0035:
	.string "这次我要牵好妈妈的手。$"

Part55_Text_0036:
	.string "她在二楼？我这就下去接她。谢谢你！$"

Part55_Text_0037:
	.string "孩子一个人走丢可吓坏我了。以后逛商\n店得看紧一点。$"

Part55_Text_0038:
	.string "想给家里挑件装饰品。孩子刚才还在我\n身后呢。$"

Part55_Text_0039:
	.string "海滨大道的设计师订了这块布。你路过\n的话，能替我带过去吗？$"

Part55_Text_0040:
	.string "这件东西请交给它的主人。$"

Part55_Text_0041:
	.string "布料送到了！卷卷耳刚才一直盯着那条\n缎带。这个石头是我们旅行时找到的，\p送给你。$"

Part55_Text_0042:
	.string "要是见到我遗落的东西，能帮我带回来\n吗？$"

Part55_Text_0043:
	.string "卷卷耳又把布叠整齐了。它做事比我还\n细心。$"

Part55_Text_0044:
	.string "想让宝可梦学习三重攻击吗？我们会先\n看看它能不能学会。$"

Part55_Text_0045:
	.string "请选择要学习的宝可梦。$"

Part55_Text_0046:
	.string "想再学的时候，随时来找我。$"

Part55_Text_0047:
	.string "双打时帮伙伴一把很有用。要学习帮助\n吗？$"

Part55_Text_0048:
	.string "请选择要学习的宝可梦。$"

Part55_Text_0049:
	.string "想再学的时候，随时来找我。$"

Part55_Text_0050:
	.string "第一份薪水到账啦！想送家里一点东西\n，还想买训练用品……得先列张清单。$"

Part55_Text_0051:
	.string "先看看价格吧。你上个月还说要攒路费\n呢。$"

Part55_Text_0052:
	.string "买回来才发现宝可梦用不上……下次我一\n定先看说明。$"

Part55_Text_0053:
	.string "选用品也得看伙伴擅长什么。名字好听\n可不一定合适。$"

Part55_Text_0054:
	.string "我在这里坐了一下午。外面太热，这里\n还能慢慢看画。$"

Part55_Text_0055:
	.string "这次第三名！比上次进步了一名。回去\n给伙伴加一份点心。$"

Part55_Text_0056:
	.string "先吃饭，再拍照。刚下台的时候，它比\n我还饿。$"

Part55_Text_0057:
	.string "台上的亮光很好看，后台可不能忘了检\n查电线。$"

Part55_Text_0058:
	.string "今天的饭团还热着。散步前先吃点东西\n吧。$"

Part55_Text_0059:
	.string "这排明信片拍的都是丰缘海岸。寄回家\n也很方便。$"

Part55_Text_0060:
	.string "长途旅行前，补给一定要带够。这里有\n训练家常用的东西。$"
Part55_Badge::
	lock
	faceplayer
	goto_if_ge VAR_PART55_EMPLOYEE_BADGE, 1, Part55_Badge_After
	msgbox Part55_Text_0061, MSGBOX_DEFAULT
	giveitem ITEM_EMPLOYEE_BADGE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_EMPLOYEE_BADGE, 1
	release
	end


Part55_Badge_After::
	msgbox Part55_Text_0062, MSGBOX_DEFAULT
	release
	end


Part55_BadgeOwner::
	lock
	faceplayer
	goto_if_eq VAR_PART55_EMPLOYEE_BADGE, 3, Part55_BadgeOwner_Done
	goto_if_ne VAR_PART55_EMPLOYEE_BADGE, 1, Part55_BadgeOwner_Wait
	checkitem ITEM_EMPLOYEE_BADGE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BadgeOwner_Wait
	msgbox Part55_Text_0063, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_EMPLOYEE_BADGE, 1
	setvar VAR_PART55_EMPLOYEE_BADGE, 3
	release
	end


Part55_BadgeOwner_Wait::
	msgbox Part55_Text_0064, MSGBOX_DEFAULT
	release
	end


Part55_BadgeOwner_Done::
	msgbox Part55_Text_0065, MSGBOX_DEFAULT
	release
	end


Part55_MedicineSender::
	lock
	faceplayer
	goto_if_ge VAR_PART55_MEDICINE, 1, Part55_MedicineSender_After
	msgbox Part55_Text_0066, MSGBOX_DEFAULT
	giveitem ITEM_MEDICINE_PARCEL, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_MEDICINE, 1
	release
	end


Part55_MedicineSender_After::
	msgbox Part55_Text_0067, MSGBOX_DEFAULT
	release
	end


Part55_Patient::
	lock
	faceplayer
	goto_if_eq VAR_PART55_MEDICINE, 3, Part55_Patient_Done
	goto_if_ne VAR_PART55_MEDICINE, 1, Part55_Patient_Wait
	checkitem ITEM_MEDICINE_PARCEL, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_Patient_Wait
	msgbox Part55_Text_0068, MSGBOX_DEFAULT
	giveitem ITEM_HYPER_POTION, 3
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_MEDICINE_PARCEL, 1
	setvar VAR_PART55_MEDICINE, 3
	release
	end


Part55_Patient_Wait::
	msgbox Part55_Text_0069, MSGBOX_DEFAULT
	release
	end


Part55_Patient_Done::
	msgbox Part55_Text_0070, MSGBOX_DEFAULT
	release
	end


Part55_PowerModule::
	lock
	faceplayer
	goto_if_ge VAR_PART55_MODULE, 1, Part55_PowerModule_After
	msgbox Part55_Text_0071, MSGBOX_DEFAULT
	giveitem ITEM_POWER_MODULE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_MODULE, 1
	release
	end


Part55_PowerModule_After::
	msgbox Part55_Text_0072, MSGBOX_DEFAULT
	release
	end


Part55_ElectricTech::
	lock
	faceplayer
	goto_if_eq VAR_PART55_MODULE, 3, Part55_ElectricTech_Done
	goto_if_ne VAR_PART55_MODULE, 1, Part55_ElectricTech_Wait
	checkitem ITEM_POWER_MODULE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_ElectricTech_Wait
	msgbox Part55_Text_0073, MSGBOX_DEFAULT
	giveitem ITEM_AMPHAROSITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_POWER_MODULE, 1
	setvar VAR_PART55_MODULE, 3
	release
	end


Part55_ElectricTech_Wait::
	msgbox Part55_Text_0074, MSGBOX_DEFAULT
	release
	end


Part55_ElectricTech_Done::
	msgbox Part55_Text_0075, MSGBOX_DEFAULT
	release
	end


Part55_WorkAmpharos::
	lock
	faceplayer
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_WorkMachamp::
	lock
	faceplayer
	playmoncry SPECIES_MACHAMP, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_NewEmployee::
	lock
	faceplayer
	goto_if_ge VAR_PART55_NEW_EMPLOYEE, 3, Part55_NewEmployee_Week
	goto_if_eq VAR_PART55_NEW_EMPLOYEE, 2, Part55_NewEmployee_Day3
	msgbox Part55_Text_0076, MSGBOX_DEFAULT
	release
	end


Part55_NewEmployee_Day3::
	msgbox Part55_Text_0077, MSGBOX_DEFAULT
	release
	end


Part55_NewEmployee_Week::
	msgbox Part55_Text_0078, MSGBOX_DEFAULT
	release
	end


Part55_CanteenServer::
	msgbox Part55_Text_0079, MSGBOX_NPC
	end


Part55_CanteenWorker::
	msgbox Part55_Text_0080, MSGBOX_NPC
	end


Part55_CanteenCurry::
	msgbox Part55_Text_0081, MSGBOX_NPC
	end


Part55_DeliveryWorker::
	msgbox Part55_Text_0082, MSGBOX_NPC
	end


Part55_RentResident::
	msgbox Part55_Text_0083, MSGBOX_NPC
	end


Part55_QuietResident::
	msgbox Part55_Text_0084, MSGBOX_NPC
	end


Part55_ForeignVisitor::
	msgbox Part55_Text_0085, MSGBOX_NPC
	end


Part55_ForeignTrainer::
	goto_if_set FLAG_STORY_C_03, Part55_ForeignTrainer_Talk
	trainerbattle_single TRAINER_STORY_C_06, StoryC_Text_ForeignIntro, StoryC_Text_ForeignDefeat, Part55_ForeignTrainer_Won
	release
	end

Part55_ForeignTrainer_Won::
	setflag FLAG_STORY_C_03
Part55_ForeignTrainer_Talk::
	lock
	faceplayer
	msgbox Part55_Text_0086, MSGBOX_DEFAULT
	release
	end


Part55_ForeignMareep::
	lock
	faceplayer
	playmoncry SPECIES_MAREEP, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_ApartmentBoard::
	msgbox Part55_Text_0087, MSGBOX_NPC
	end


Part55_VendingMachine::
	msgbox Part55_Text_0088, MSGBOX_NPC
	end


Part55_GlobalResearchMap::
	msgbox Part55_Text_0089, MSGBOX_NPC
	end


Part55_BasementLift::
	msgbox Part55_Text_0090, MSGBOX_NPC
	end


Part55_EnvDisplay::
	msgbox Part55_Text_0091, MSGBOX_NPC
	end


Part55_LifeDisplay::
	msgbox Part55_Text_0092, MSGBOX_NPC
	end


Part55_AncientDisplay::
	msgbox Part55_Text_0093, MSGBOX_NPC
	end


Part55_LiquidBox::
	lockall
	msgbox Part55_Text_0094, MSGBOX_DEFAULT
	setvar VAR_0x8004, 1
	special Part55_TakeSample
	goto_if_eq VAR_RESULT, 1, Part55_SampleBusy
	goto_if_eq VAR_RESULT, 0, Part55_SampleAlready
	msgbox Part55_Text_0095, MSGBOX_DEFAULT
	releaseall
	end


Part55_CellBox::
	lockall
	msgbox Part55_Text_0096, MSGBOX_DEFAULT
	setvar VAR_0x8004, 2
	special Part55_TakeSample
	goto_if_eq VAR_RESULT, 1, Part55_SampleBusy
	goto_if_eq VAR_RESULT, 0, Part55_SampleAlready
	msgbox Part55_Text_0097, MSGBOX_DEFAULT
	releaseall
	end


Part55_RubbingBox::
	lockall
	msgbox Part55_Text_0098, MSGBOX_DEFAULT
	setvar VAR_0x8004, 3
	special Part55_TakeSample
	goto_if_eq VAR_RESULT, 1, Part55_SampleBusy
	goto_if_eq VAR_RESULT, 0, Part55_SampleAlready
	msgbox Part55_Text_0099, MSGBOX_DEFAULT
	releaseall
	end


Part55_SampleBusy::
	msgbox Part55_Text_0100, MSGBOX_DEFAULT
	releaseall
	end


Part55_SampleAlready::
	msgbox Part55_Text_0101, MSGBOX_DEFAULT
	releaseall
	end


Part55_EnvWindow::
	lockall
	msgbox Part55_Text_0102, MSGBOX_DEFAULT
	setvar VAR_0x8004, 1
	special Part55_DeliverSample
	goto_if_eq VAR_RESULT, 1, Part55_SampleWrong
	goto_if_eq VAR_RESULT, 0, Part55_SampleNone
	msgbox Part55_Text_0103, MSGBOX_DEFAULT
	releaseall
	end


Part55_LifeWindow::
	lockall
	msgbox Part55_Text_0104, MSGBOX_DEFAULT
	setvar VAR_0x8004, 2
	special Part55_DeliverSample
	goto_if_eq VAR_RESULT, 1, Part55_SampleWrong
	goto_if_eq VAR_RESULT, 0, Part55_SampleNone
	msgbox Part55_Text_0105, MSGBOX_DEFAULT
	releaseall
	end


Part55_AncientWindow::
	lockall
	msgbox Part55_Text_0106, MSGBOX_DEFAULT
	setvar VAR_0x8004, 3
	special Part55_DeliverSample
	goto_if_eq VAR_RESULT, 1, Part55_SampleWrong
	goto_if_eq VAR_RESULT, 0, Part55_SampleNone
	msgbox Part55_Text_0107, MSGBOX_DEFAULT
	releaseall
	end


Part55_SampleWrong::
	msgbox Part55_Text_0108, MSGBOX_DEFAULT
	releaseall
	end


Part55_SampleNone::
	msgbox Part55_Text_0109, MSGBOX_DEFAULT
	releaseall
	end


Part55_SampleStaff::
	lock
	faceplayer
	goto_if_eq VAR_PART55_SAMPLE_REWARD, 3, Part55_SampleStaff_Done
	goto_if_ne VAR_PART55_SAMPLE_BITS, 7, Part55_SampleStaff_Wait
	msgbox Part55_Text_0110, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_SAMPLE_REWARD, 3
	release
	end


Part55_SampleStaff_Wait::
	msgbox Part55_Text_0111, MSGBOX_DEFAULT
	release
	end


Part55_SampleStaff_Done::
	msgbox Part55_Text_0112, MSGBOX_DEFAULT
	release
	end


Part55_Programmer::
	lock
	faceplayer
	goto_if_eq VAR_PART55_PORYGON, 5, Part55_Programmer_Done
	goto_if_eq VAR_PART55_PORYGON, 4, Part55_Programmer_Gift
	goto_if_ge VAR_PART55_PORYGON, 1, Part55_Programmer_Wait
	setvar VAR_PART55_PORYGON, 1
	msgbox Part55_Text_0113, MSGBOX_DEFAULT
	release
	end


Part55_Programmer_Wait::
	msgbox Part55_Text_0114, MSGBOX_DEFAULT
	release
	end


Part55_Programmer_Gift::
	msgbox Part55_Text_0115, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part55_Programmer_Bye
	special Part55_GivePorygon
	goto_if_eq VAR_RESULT, FALSE, Part55_PartyFull
	setflag FLAG_PART55_HIDE_PORYGON
	removeobject LOCALID_PART55_NETWORK_PORYGON
	msgbox Part55_Text_0116, MSGBOX_DEFAULT
	release
	end


Part55_Programmer_Done::
	msgbox Part55_Text_0117, MSGBOX_DEFAULT
	release
	end


Part55_Programmer_Bye::
	release
	end


Part55_PartyFull::
	msgbox Part55_Text_0118, MSGBOX_DEFAULT
	releaseall
	end


Part55_Network1::
	lockall
	goto_if_ne VAR_PART55_PORYGON, 1, Part55_Network1_Wait
	setvar VAR_PART55_PORYGON, 2
	msgbox Part55_Text_0119, MSGBOX_DEFAULT
	releaseall
	end


Part55_Network1_Wait::
	msgbox Part55_Text_0120, MSGBOX_DEFAULT
	releaseall
	end


Part55_Network2::
	lockall
	goto_if_ne VAR_PART55_PORYGON, 2, Part55_Network2_Wait
	setvar VAR_PART55_PORYGON, 3
	msgbox Part55_Text_0121, MSGBOX_DEFAULT
	releaseall
	end


Part55_Network2_Wait::
	msgbox Part55_Text_0122, MSGBOX_DEFAULT
	releaseall
	end


Part55_Network3::
	lockall
	goto_if_ne VAR_PART55_PORYGON, 3, Part55_Network3_Wait
	setvar VAR_PART55_PORYGON, 4
	clearflag FLAG_PART55_HIDE_PORYGON
	addobject LOCALID_PART55_NETWORK_PORYGON
	msgbox Part55_Text_0123, MSGBOX_DEFAULT
	releaseall
	end


Part55_Network3_Wait::
	msgbox Part55_Text_0124, MSGBOX_DEFAULT
	releaseall
	end


Part55_NetworkPorygon::
	lock
	faceplayer
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_ShowPorygon::
	clearflag FLAG_PART55_HIDE_PORYGON
	return


Part55_Advanced::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE07_GET, Part55_Advanced_Wait
	goto_if_eq VAR_PART55_ADVANCED_PATCH, 3, Part55_Advanced_Done
	goto_if_defeated TRAINER_PART55_ADVANCED_TRAINER, Part55_Advanced_Reward
	msgbox Part55_Text_0125, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part55_Advanced_Bye
	trainerbattle_single TRAINER_PART55_ADVANCED_TRAINER, Part55_Text_0126, Part55_Text_0127, Part55_Advanced_Reward
	release
	end


Part55_Advanced_Reward::
	lock
	faceplayer
	msgbox Part55_Text_0128, MSGBOX_DEFAULT
	giveitem ITEM_ABILITY_PATCH, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_ADVANCED_PATCH, 3
	release
	end


Part55_Advanced_Wait::
	msgbox Part55_Text_0129, MSGBOX_DEFAULT
	release
	end


Part55_Advanced_Done::
	msgbox Part55_Text_0130, MSGBOX_DEFAULT
	release
	end


Part55_Advanced_Bye::
	release
	end


Part55_Text_0061:
	.string "门口的长椅下有一张员工证。照片上的\n人穿着工作服。$"

Part55_Text_0062:
	.string "请把它带给收件人。$"

Part55_Text_0063:
	.string "我的员工证！早上找了半天，都快赶不\n上打卡了。谢谢你。$"

Part55_Text_0064:
	.string "员工证丢了，保安让我先在这里登记。$"

Part55_Text_0065:
	.string "证件终于找回来了。下次我把它放在包\n里。$"

Part55_Text_0066:
	.string "室友发烧了，我还要等这组数据。能把\n这包药送到公寓一楼吗？$"

Part55_Text_0067:
	.string "公寓一楼的室友在等药。谢谢你帮忙。$"

Part55_Text_0068:
	.string "他还记得买药……谢谢你跑这一趟。我好\n多了，这些伤药留给你的伙伴吧。$"

Part55_Text_0069:
	.string "今天有点发烧，只好请假休息。室友说\n要帮我买药。$"

Part55_Text_0070:
	.string "烧退了，室友也来看过我了。等好些了\n再去吃饭。$"

Part55_Text_0071:
	.string "卸货处放着一个备用模块。标签写着“\n园区电力技师”。$"

Part55_Text_0072:
	.string "请把它带给收件人。$"

Part55_Text_0073:
	.string "模块送来了！电龙，帮忙接一下。仪器\n恢复了，这颗石头作为谢礼请收下。$"

Part55_Text_0074:
	.string "电龙暂时在给仪器供电。备用模块应该\n留在121号道路的卸货处了。$"

Part55_Text_0075:
	.string "电龙总算能休息一会儿。下班给它多准\n备点吃的。$"

Part55_Text_0076:
	.string "第一天上班，光是密码就记了四个。午\n休时得重新抄一遍。$"

Part55_Text_0077:
	.string "今天终于没走错门。就是把会议室和档\n案室又记反了。$"

Part55_Text_0078:
	.string "忙了一周，连今天星期几都忘了。希望\n晚饭还能吃到咖喱。$"

Part55_Text_0079:
	.string "今天供应咖喱。过了饭点也给值班的人\n留一份。$"

Part55_Text_0080:
	.string "等这组数据结束就去吃饭……哎，怎么又\n开始下一组了。$"

Part55_Text_0081:
	.string "想吃点辣的，可室友说今晚还要值班。\n只好点普通咖喱了。$"

Part55_Text_0082:
	.string "送餐只到一楼。楼上的员工区要由住客\n自己下来取。$"

Part55_Text_0083:
	.string "这里房租不便宜，好在离宝可梦中心近\n。我的伙伴经常去那里检查。$"

Part55_Text_0084:
	.string "住在这里挺安静。偶尔半夜有人加班回\n来，门口会亮着灯。$"

Part55_Text_0085:
	.string "我是来交流的研究员。等项目结束，还\n要回自己的实验室。$"

Part55_Text_0086:
	.string "我的伙伴是在别的地区认识的。它对丰\n缘的树果很感兴趣。$"

Part55_Text_0087:
	.string "生活区公告：训练场每周三维护。外卖\n请在一楼领取。请勿把实验用宝可梦带\p进厨房。$"

Part55_Text_0088:
	.string "自动售货机旁贴着一张字条：零钱不足\n时，请找餐饮柜台换钱。$"

Part55_Text_0089:
	.string "墙上挂着研究地点分布图。许多地区都\n有标记，丰缘沿海的点尤其密集。$"

Part55_Text_0090:
	.string "电梯面板：下层设施仅供持有授权的员\n工使用。当前没有可选的访客楼层。$"

Part55_Text_0091:
	.string "环境系统展示：密闭实验箱里的温度和\n湿度正在缓慢调整。旁边注明仅限室内\p测试。$"

Part55_Text_0092:
	.string "生命体征记录仪：屏幕上显示呼吸、脉\n搏和体表温度。没有写任何受试者姓名\p。$"

Part55_Text_0093:
	.string "古代资料数字化装置：拓片上的纹理正\n在一行行录入。$"

Part55_Text_0094:
	.string "湿掉的标签已经看不清了。箱里有装着\n水样的小瓶。$"

Part55_Text_0095:
	.string "拿起了箱子。请送到总部二楼相应的部\n门收件窗。$"

Part55_Text_0096:
	.string "箱里是低温保存的培养皿。封条提醒不\n要在室外停留太久。$"

Part55_Text_0097:
	.string "拿起了箱子。请送到总部二楼相应的部\n门收件窗。$"

Part55_Text_0098:
	.string "箱里有几卷拓片。纸上能看到古老的纹\n路。$"

Part55_Text_0099:
	.string "拿起了箱子。请送到总部二楼相应的部\n门收件窗。$"

Part55_Text_0100:
	.string "手上还有一个箱子。先送好它，再来拿\n下一箱。$"

Part55_Text_0101:
	.string "这一箱已经送到了。$"

Part55_Text_0102:
	.string "环境研究收件窗$"

Part55_Text_0103:
	.string "内容核对正确。已经签收这箱资料。$"

Part55_Text_0104:
	.string "生命研究收件窗$"

Part55_Text_0105:
	.string "内容核对正确。已经签收这箱资料。$"

Part55_Text_0106:
	.string "古代资料收件窗$"

Part55_Text_0107:
	.string "内容核对正确。已经签收这箱资料。$"

Part55_Text_0108:
	.string "这箱内容应当交给另一个部门。先带回\n去核对吧。$"

Part55_Text_0109:
	.string "目前没有需要签收的箱子。$"

Part55_Text_0110:
	.string "三箱都签收了！湿标签的事总算解决了\n。辛苦你来回跑。$"

Part55_Text_0111:
	.string "三箱货的标签都受潮了。看一眼内容，\n再送到总部二楼的对应部门，千万别只\p看外面的旧标签。$"

Part55_Text_0112:
	.string "新标签换好了。这次得套上防水袋。$"

Part55_Text_0113:
	.string "能帮我排查公共网络吗？先看总部一楼\n终端，再看交流厅，最后看总部二楼。$"

Part55_Text_0114:
	.string "请按一楼、交流厅、二楼的顺序检查。\n线路不能跳着测。$"

Part55_Text_0115:
	.string "线路恢复了！多边兽也从终端出来了。\n愿意让它和你一起旅行吗？$"

Part55_Text_0116:
	.string "多边兽加入了队伍！请好好照顾它。$"

Part55_Text_0117:
	.string "多边兽适应旅行了吗？公共网络现在运\n行得很顺畅。$"

Part55_Text_0118:
	.string "队伍里已经有六只了。留出一个位置，\n再来接它吧。我会在这里等你。$"

Part55_Text_0119:
	.string "终端完成了检测。请继续检查下一处线\n路。$"

Part55_Text_0120:
	.string "终端目前不需要这一步操作。请先按程\n序员说的顺序检查。$"

Part55_Text_0121:
	.string "终端完成了检测。请继续检查下一处线\n路。$"

Part55_Text_0122:
	.string "终端目前不需要这一步操作。请先按程\n序员说的顺序检查。$"

Part55_Text_0123:
	.string "最后一处线路恢复正常。多边兽从终端\n旁探出头来！$"

Part55_Text_0124:
	.string "终端目前不需要这一步操作。请先按程\n序员说的顺序检查。$"

Part55_Text_0125:
	.string "取得第七枚徽章了？这里有一场进阶训\n练。对手会使用Mega进化，要试试吗？$"

Part55_Text_0126:
	.string "准备好了就开始吧！$"

Part55_Text_0127:
	.string "恰雷姆配合得很好。你的判断也很准确\n。$"

Part55_Text_0128:
	.string "训练完成。这个能帮助伙伴尝试隐藏特\n性，请慎重使用。$"

Part55_Text_0129:
	.string "拿到第七枚徽章以后，再来参加进阶训\n练吧。普通公开训练照常开放。$"

Part55_Text_0130:
	.string "这次的训练记录已经保存。谢谢你认真\n参加。$"
Part55_Axew::
	lock
	faceplayer
	goto_if_set FLAG_PART55_AXEW_CAUGHT, Part55_Axew_Done
	playmoncry SPECIES_AXEW, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part55_Text_0131, MSGBOX_DEFAULT
	setwildbattle SPECIES_AXEW, PART55_AXEW_LEVEL, ITEM_NONE
	special Part55_PrepareAxew
	hideobjectat LOCALID_PART55_AXEW, MAP_ROUTE125
	dowildbattle
	special Part55_FinishAxew
	release
	end


Part55_Axew_Done::
	release
	end


Part55_AxewObserver::
	lock
	faceplayer
	special Part55_CheckCapturedAxewParty
	goto_if_eq VAR_RESULT, TRUE, Part55_AxewObserver_Party
	goto_if_set FLAG_PART55_AXEW_CAUGHT, Part55_AxewObserver_Caught
	msgbox Part55_Text_0132, MSGBOX_DEFAULT
	release
	end


Part55_AxewObserver_Party::
	msgbox Part55_Text_0133, MSGBOX_DEFAULT
	release
	end


Part55_AxewObserver_Caught::
	msgbox Part55_Text_0134, MSGBOX_DEFAULT
	release
	end


Part55_AxewRock::
	lockall
	special Part55_CheckCapturedAxewParty
	goto_if_eq VAR_RESULT, TRUE, Part55_AxewRock_Party
	msgbox Part55_Text_0135, MSGBOX_DEFAULT
	releaseall
	end


Part55_AxewRock_Party::
	msgbox Part55_Text_0136, MSGBOX_DEFAULT
	releaseall
	end


Part55_WhiteRock::
	lockall
	call_if_ge VAR_PART55_STAR_CALIBRATION, 8, Part55_WhiteRockRecord
	goto_if_set FLAG_PART55_STAR_KEY, Part55_WhiteRock_After
	msgbox Part55_Text_0137, MSGBOX_DEFAULT
	closemessage
	playse SE_SHINY
	dofieldeffectsparkle 57, 21, 0
	waitfieldeffect FLDEFF_SPARKLE
	msgbox Part55_Text_0314, MSGBOX_DEFAULT
	giveitem ITEM_STAR_KEY, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setflag FLAG_PART55_STAR_KEY
	releaseall
	end


Part55_WhiteRock_After::
	msgbox Part55_Text_0138, MSGBOX_DEFAULT
	releaseall
	end


Part55_RockGirl::
	msgbox Part55_Text_0139, MSGBOX_NPC
	end


Part55_RockFather::
	msgbox Part55_Text_0140, MSGBOX_NPC
	end


Part55_KeyGlance::
	lock
	faceplayer
	goto_if_set FLAG_PART55_KEY_GLIMMER_SEEN, Part55_KeyGlance_Normal
	goto_if_unset FLAG_PART55_STAR_KEY, Part55_KeyGlance_Normal
	setflag FLAG_PART55_KEY_GLIMMER_SEEN
	msgbox Part55_Text_0141, MSGBOX_DEFAULT
	release
	end


Part55_KeyGlance_Normal::
	msgbox Part55_Text_0142, MSGBOX_DEFAULT
	release
	end


Part55_Psychic::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE07_GET, Part55_Psychic_Wait
	goto_if_eq VAR_PART55_ALAKAZITE, 3, Part55_Psychic_Done
	goto_if_defeated TRAINER_PART55_PSYCHIC_RESEARCHER, Part55_Psychic_Reward
	msgbox Part55_Text_0143, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part55_Psychic_Bye
	trainerbattle_single TRAINER_PART55_PSYCHIC_RESEARCHER, Part55_Text_0144, Part55_Text_0145, Part55_Psychic_Reward
	release
	end


Part55_Psychic_Reward::
	lock
	faceplayer
	msgbox Part55_Text_0146, MSGBOX_DEFAULT
	giveitem ITEM_ALAKAZITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_ALAKAZITE, 3
	release
	end


Part55_Psychic_Done::
	msgbox Part55_Text_0147, MSGBOX_DEFAULT
	release
	end


Part55_Psychic_Wait::
	msgbox Part55_Text_0148, MSGBOX_DEFAULT
	release
	end


Part55_Psychic_Bye::
	release
	end


Part55_SeaHealer::
	lock
	faceplayer
	msgbox Part55_Text_0149, MSGBOX_DEFAULT
	special HealPlayerParty
	msgbox Part55_Text_0150, MSGBOX_DEFAULT
	release
	end


Part55_UnderwaterResearcher::
	lock
	faceplayer
	goto_if_ge VAR_PART55_UNDERWATER_OBSERVATION, 1, Part55_UnderwaterResearcher_Wait
	msgbox Part55_Text_0151, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part55_UnderwaterResearcher_End
	setvar VAR_PART55_UNDERWATER_OBSERVATION, 1
	msgbox Part55_Text_0152, MSGBOX_DEFAULT
	release
	end


Part55_UnderwaterResearcher_Wait::
	msgbox Part55_Text_0153, MSGBOX_DEFAULT
	release
	end


Part55_UnderwaterResearcher_End::
	release
	end


Part55_Buoy::
	lockall
	goto_if_ge VAR_PART55_BUOY, 1, Part55_Buoy_After
	playmoncry SPECIES_MANTYKE, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part55_Text_0154, MSGBOX_DEFAULT
	setvar VAR_PART55_BUOY, 1
	setflag FLAG_PART55_HIDE_BUOY_MANTYKE
	removeobject LOCALID_PART55_BUOY_MANTYKE
	releaseall
	end


Part55_Buoy_After::
	msgbox Part55_Text_0155, MSGBOX_DEFAULT
	releaseall
	end


@ VAR_PART55_BUOY: 0 untouched, 1 buoy fixed, 2 buoy fixed + researcher beaten
@ (Story C), 3 reward handed over.
Part55_BuoyResearcher::
	lock
	faceplayer
	goto_if_eq VAR_PART55_BUOY, 3, Part55_BuoyResearcher_Done
	goto_if_eq VAR_PART55_BUOY, 2, Part55_BuoyResearcher_Give
	goto_if_ne VAR_PART55_BUOY, 1, Part55_BuoyResearcher_Wait
	msgbox Part55_Text_0156, MSGBOX_DEFAULT
	trainerbattle_single TRAINER_STORY_C_05, StoryC_Text_BuoyIntro, StoryC_Text_BuoyDefeat, Part55_BuoyResearcher_Won
	release
	end

Part55_BuoyResearcher_Won::
	setvar VAR_PART55_BUOY, 2
Part55_BuoyResearcher_Give::
	lock
	faceplayer
	msgbox StoryC_Text_BuoyGive, MSGBOX_DEFAULT
	giveitem ITEM_DIVE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_BUOY, 3
	release
	end


Part55_BuoyResearcher_Wait::
	msgbox Part55_Text_0157, MSGBOX_DEFAULT
	release
	end


Part55_BuoyResearcher_Done::
	msgbox Part55_Text_0158, MSGBOX_DEFAULT
	release
	end


Part55_RecordSuccessfulShard::
	special Part55_RecordShardTrade
	return


Part55_FrozenStone::
	lockall
	goto_if_unset FLAG_PART55_SHELL_BELL_CRAFTED, Part55_FrozenStone_Wait
	goto_if_ge VAR_PART55_FROZEN_STONE, 1, Part55_FrozenStone_After
	msgbox Part55_Text_0159, MSGBOX_DEFAULT
	giveitem ITEM_FROZEN_STONE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_FROZEN_STONE, 1
	releaseall
	end


Part55_FrozenStone_Wait::
	msgbox Part55_Text_0160, MSGBOX_DEFAULT
	releaseall
	end


Part55_FrozenStone_After::
	msgbox Part55_Text_0161, MSGBOX_DEFAULT
	releaseall
	end


Part55_ShoalExpert::
	lock
	faceplayer
	goto_if_eq VAR_PART55_FROZEN_STONE, 1, Part55_ShoalExpert_Reward
	goto ShoalCave_LowTideEntranceRoom_EventScript_ShellBellExpert


Part55_ShoalExpert_Reward::
	checkitem ITEM_FROZEN_STONE, 1
	goto_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_ShellBellExpert
	msgbox Part55_Text_0162, MSGBOX_DEFAULT
	giveitem ITEM_GLALITITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_FROZEN_STONE, 1
	setvar VAR_PART55_FROZEN_STONE, 3
	release
	end


Part55_IceCrystal1::
	lockall
	msgbox Part55_Text_0163, MSGBOX_DEFAULT
	setvar VAR_0x8004, VAR_PART55_ICE_CRYSTALS, FALSE
	setvar VAR_0x8005, 1
	special Part55_RecordPoint
	releaseall
	end


Part55_IceCrystal2::
	lockall
	msgbox Part55_Text_0164, MSGBOX_DEFAULT
	setvar VAR_0x8004, VAR_PART55_ICE_CRYSTALS, FALSE
	setvar VAR_0x8005, 2
	special Part55_RecordPoint
	releaseall
	end


Part55_IceCrystal3::
	lockall
	msgbox Part55_Text_0165, MSGBOX_DEFAULT
	setvar VAR_0x8004, VAR_PART55_ICE_CRYSTALS, FALSE
	setvar VAR_0x8005, 4
	special Part55_RecordPoint
	releaseall
	end


Part55_IceResearcher::
	lock
	faceplayer
	goto_if_eq VAR_PART55_ABOMASITE, 3, Part55_IceResearcher_Done
	goto_if_ne VAR_PART55_ICE_CRYSTALS, 7, Part55_IceResearcher_Wait
	msgbox Part55_Text_0166, MSGBOX_DEFAULT
	giveitem ITEM_ABOMASITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_ABOMASITE, 3
	release
	end


Part55_IceResearcher_Wait::
	msgbox Part55_Text_0167, MSGBOX_DEFAULT
	release
	end


Part55_IceResearcher_Done::
	msgbox Part55_Text_0168, MSGBOX_DEFAULT
	release
	end


Part55_Snover::
	lock
	faceplayer
	playmoncry SPECIES_SNOVER, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_Text_0131:
	.string "牙牙紧紧盯着你，牙尖在阳光下闪了一\n下。$"

Part55_Text_0132:
	.string "洞口附近那只牙牙很会咬石头。亮亮的\n，远远就能看见它。$"

Part55_Text_0133:
	.string "是它呀！这回咬石头前，记得给它找块\n结实一点的。$"

Part55_Text_0134:
	.string "最近没再见到那只牙牙。石头上的牙印\n倒还留着。$"

Part55_Text_0135:
	.string "石头上留下了一排深深的牙印。$"

Part55_Text_0136:
	.string "牙牙认出了这块石头，得意地摆了摆尾\n巴。$"

Part55_Text_0137:
	.string "一块洁白的岩石。$"

Part55_Text_0138:
	.string "这块洁白的岩石，静静地照着海边的阳\n光。$"

Part55_Text_0139:
	.string "刚才好像闪了一下！爸爸说可能是浪花\n反光。$"

Part55_Text_0140:
	.string "白色的石头在太阳下挺亮。她一看见反\n光就要拉我过来。$"

Part55_Text_0141:
	.string "你包里刚才有点微光？也许是我看错了\n。总觉得亮了一下。$"

Part55_Text_0142:
	.string "海边阳光太强了，刚进来还看不清东西\n。$"

Part55_Text_0143:
	.string "我研究超能力宝可梦，也会和训练家交\n流。要来一场普通对战吗？$"

Part55_Text_0144:
	.string "请多指教！$"

Part55_Text_0145:
	.string "这次记录很有参考价值。$"

Part55_Text_0146:
	.string "谢谢。这颗石头交给你，也许能和你的\n伙伴一起派上用场。$"

Part55_Text_0147:
	.string "我还要整理刚才的记录。下次再聊聊你\n的旅途吧。$"

Part55_Text_0148:
	.string "小枫和小南很擅长配合。先去挑战他们\n吧，拿到徽章以后我们也来一场。$"

Part55_Text_0149:
	.string "海上跑一趟挺累的。让你的伙伴休息一\n下吧。$"

Part55_Text_0150:
	.string "精神恢复了！接下来也要留意潮流。$"

Part55_Text_0151:
	.string "最近有几处水下观测值不太对。以后能\n潜水时，能帮忙记录高温、异常流向和\p能量读数吗？$"

Part55_Text_0152:
	.string "目前记录是0/3。不用急着完成，先准\n备好潜水能力。原因还不能确定。$"

Part55_Text_0153:
	.string "水下观测记录：0/3。等可以潜水以后\n，再来一起调查吧。$"

Part55_Text_0154:
	.string "小球飞鱼围着歪掉的浮标转了一圈。它\n游开以后，你扶正了浮标。$"

Part55_Text_0155:
	.string "浮标已经扶正。水面上的标记也清楚多\n了。$"

Part55_Text_0156:
	.string "你把浮标扶正了？谢谢，那可是我们标\n记采样位置用的。$"

Part55_Text_0157:
	.string "附近有个浮标歪了。小球飞鱼老是围着\n它转。$"

Part55_Text_0158:
	.string "今天的采样位置确认好了。终于可以收\n工了。$"

Part55_Text_0159:
	.string "深处的冰里露出一块颜色奇怪的石头。\n先带给入口的老人看看吧。$"

Part55_Text_0160:
	.string "冰层里封着一块奇怪的石头。附近的冰\n很厚，暂时取不下来。$"

Part55_Text_0161:
	.string "冰层里留下了取出石头的痕迹。$"

Part55_Text_0162:
	.string "这块冰可结实。慢慢敲开……里面的石头\n完好无损！是冰鬼护进化石，你留着吧\p。$"

Part55_Text_0163:
	.string "记录了冰晶的形状与温度。旁边能看到\n细小的裂纹。$"

Part55_Text_0164:
	.string "记录了冰晶的形状与温度。旁边能看到\n细小的裂纹。$"

Part55_Text_0165:
	.string "记录了冰晶的形状与温度。旁边能看到\n细小的裂纹。$"

Part55_Text_0166:
	.string "三处冰晶都记录好了！雪笠怪也喜欢这\n里的温度。这颗石头请收下。$"

Part55_Text_0167:
	.string "我正在观察冰室。能帮我记录三处冰晶\n吗？带着雪笠怪来这里，连外套都得穿\p厚一点。$"

Part55_Text_0168:
	.string "冰晶记录都收好了。等下一次低潮，再\n来对照看看。$"
Part55_RangerNotebook::
	lock
	faceplayer
	goto_if_ge VAR_PART55_NOTEBOOK, 1, Part55_RangerNotebook_After
	msgbox Part55_Text_0169, MSGBOX_DEFAULT
	giveitem ITEM_RANGER_NOTEBOOK, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_NOTEBOOK, 1
	release
	end


Part55_RangerNotebook_After::
	msgbox Part55_Text_0170, MSGBOX_DEFAULT
	release
	end


Part55_Ranger::
	lock
	faceplayer
	goto_if_eq VAR_PART55_NOTEBOOK, 3, Part55_Ranger_Done
	goto_if_ne VAR_PART55_NOTEBOOK, 1, Part55_Ranger_Wait
	checkitem ITEM_RANGER_NOTEBOOK, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_Ranger_Wait
	msgbox Part55_Text_0171, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_RANGER_NOTEBOOK, 1
	setvar VAR_PART55_NOTEBOOK, 3
	release
	end


Part55_Ranger_Wait::
	msgbox Part55_Text_0172, MSGBOX_DEFAULT
	release
	end


Part55_Ranger_Done::
	msgbox Part55_Text_0173, MSGBOX_DEFAULT
	release
	end


Part55_BeeTree1::
	lockall
	msgbox Part55_Text_0174, MSGBOX_DEFAULT
	setvar VAR_0x8004, VAR_PART55_BEE, FALSE
	setvar VAR_0x8005, 1
	special Part55_RecordPoint
	releaseall
	end


Part55_BeeTree2::
	lockall
	msgbox Part55_Text_0175, MSGBOX_DEFAULT
	setvar VAR_0x8004, VAR_PART55_BEE, FALSE
	setvar VAR_0x8005, 2
	special Part55_RecordPoint
	releaseall
	end


Part55_BeeTree3::
	lockall
	goto_if_ge VAR_PART55_BEE, 7, Part55_BeeTree3_After
	goto_if_ne VAR_PART55_BEE, 3, Part55_BeeTree3_Other
	setvar VAR_PART55_BEE, 7
	msgbox Part55_Text_0176, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part55_BeeTree3_End
	special Part55_StartSafariBeedrill
	releaseall
	end


Part55_BeeTree3_After::
	msgbox Part55_Text_0177, MSGBOX_DEFAULT
	releaseall
	end


Part55_BeeTree3_Other::
	msgbox Part55_Text_0178, MSGBOX_DEFAULT
	releaseall
	end


Part55_BeeTree3_End::
	releaseall
	end


Part55_BeeRanger::
	lock
	faceplayer
	goto_if_eq VAR_PART55_BEE, 15, Part55_BeeRanger_Done
	goto_if_lt VAR_PART55_BEE, 7, Part55_BeeRanger_Wait
	msgbox Part55_Text_0179, MSGBOX_DEFAULT
	giveitem ITEM_BEEDRILLITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_BEE, 15
	release
	end


Part55_BeeRanger_Wait::
	msgbox Part55_Text_0180, MSGBOX_DEFAULT
	release
	end


Part55_BeeRanger_Done::
	msgbox Part55_Text_0181, MSGBOX_DEFAULT
	release
	end


Part55_SafariExpert::
	lock
	faceplayer
	goto_if_eq VAR_PART55_SAFARI_EXPERT, 3, Part55_SafariExpert_Done
	goto_if_defeated TRAINER_PART55_SAFARI_EXPERT, Part55_SafariExpert_Reward
	special Part55_CheckSafariLargeSeen
	goto_if_eq VAR_RESULT, FALSE, Part55_SafariExpert_Wait
	msgbox Part55_Text_0182, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part55_SafariExpert_Bye
	trainerbattle_single TRAINER_PART55_SAFARI_EXPERT, Part55_Text_0183, Part55_Text_0184, Part55_SafariExpert_Reward
	release
	end


Part55_SafariExpert_Wait::
	msgbox Part55_Text_0185, MSGBOX_DEFAULT
	release
	end


Part55_SafariExpert_Reward::
	lock
	faceplayer
	msgbox Part55_Text_0186, MSGBOX_DEFAULT
	checkitemspace ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	checkitemspace ITEM_NUGGET, 2
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	giveitem ITEM_PP_UP, 1
	giveitem ITEM_NUGGET, 2
	setvar VAR_PART55_SAFARI_EXPERT, 3
	release
	end


Part55_SafariExpert_Done::
	msgbox Part55_Text_0187, MSGBOX_DEFAULT
	release
	end


Part55_SafariExpert_Bye::
	release
	end


Part55_Text_0169:
	.string "草丛边有一本巡查记录。封面写着原野\n区护林员的名字。$"

Part55_Text_0170:
	.string "请把它带给收件人。$"

Part55_Text_0171:
	.string "巡查记录找回来了！我还担心要重新走\n一遍。这个送给你。$"

Part55_Text_0172:
	.string "巡查时把记录本弄丢了。要是在偏远草\n丛看见，能带回来吗？$"

Part55_Text_0173:
	.string "巡查路线都记好了。下回得用结实点的\n夹子。$"

Part55_Text_0174:
	.string "树枝上有采食的痕迹，但没有看到巢。\n记下这个调查点。$"

Part55_Text_0175:
	.string "树枝上有采食的痕迹，但没有看到巢。\n记下这个调查点。$"

Part55_Text_0176:
	.string "这棵树上有一个巢。大针蜂从树叶间探\n出了头。\p要靠近观察吗？这里仍然使用原野区的\n捕获规则。$"

Part55_Text_0177:
	.string "巢的位置已经记下了。这里离游客常走\n的路很远。$"

Part55_Text_0178:
	.string "树叶深处有沙沙声。先看看另外两个调\n查点，再确认这里的情况吧。$"

Part55_Text_0179:
	.string "找到了巢，也确认离游客路线很远。这\n样就不必打扰它们。多谢你帮忙记录。$"

Part55_Text_0180:
	.string "南部树林里有三个巡查点。想确认大针\n蜂的巢是否远离游客路线，能帮忙看看\p吗？$"

Part55_Text_0181:
	.string "那片树林先保持原样。参观的人也不必\n往巢边走。$"

Part55_Text_0182:
	.string "袋兽、吉利蛋和肯泰罗都登记过了？观\n察得挺仔细。要来一场进阶对战吗？$"

Part55_Text_0183:
	.string "伙伴们，上场吧！$"

Part55_Text_0184:
	.string "你既会观察，也懂得配合。$"

Part55_Text_0185:
	.string "这里有袋兽、吉利蛋和肯泰罗。图鉴里\n登记这三种以后，可以找我试试进阶对\p战。$"

Part55_Text_0186:
	.string "完成了！这些奖品就交给你了。$"

Part55_Text_0187:
	.string "观察宝可梦，也记得看看它们生活的地\n方。$"
Part55_ArtStudent::
	lock
	faceplayer
	specialvar VAR_0x8004, CountPlayerMuseumPaintings
	goto_if_ge VAR_0x8004, 1, Part55_ArtStudent_Recognized
	msgbox Part55_Text_0188, MSGBOX_DEFAULT
	release
	end


Part55_ArtStudent_Recognized::
	msgbox Part55_Text_0189, MSGBOX_DEFAULT
	release
	end


Part55_Musician::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, Part55_Musician_Badge
	msgbox Part55_Text_0190, MSGBOX_DEFAULT
	release
	end


Part55_Musician_Badge::
	msgbox Part55_Text_0191, MSGBOX_DEFAULT
	release
	end


Part55_Exploud::
	lock
	faceplayer
	playmoncry SPECIES_EXPLOUD, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_LostElder::
	lock
	faceplayer
	goto_if_ge VAR_PART55_LOST_ELDER, 1, Part55_LostElder_After
	setvar VAR_PART55_LOST_ELDER, 1
	msgbox Part55_Text_0192, MSGBOX_DEFAULT
	release
	end


Part55_LostElder_After::
	msgbox Part55_Text_0193, MSGBOX_DEFAULT
	release
	end


Part55_LostElderPort::
	msgbox Part55_Text_0194, MSGBOX_NPC
	end


Part55_HideElderStore::
	setflag FLAG_TEMP_1E
	return


Part55_ShowElderPort::
	clearflag FLAG_PART55_HIDE_ELDER_PORT
	return


Part55_GemScratch::
	lockall
	msgbox Part55_Text_0195, MSGBOX_DEFAULT
	setvar VAR_0x8004, VAR_PART55_SABLE_CLUES, FALSE
	setvar VAR_0x8005, 1
	special Part55_RecordPoint
	releaseall
	end


Part55_GemPowder::
	lockall
	msgbox Part55_Text_0196, MSGBOX_DEFAULT
	setvar VAR_0x8004, VAR_PART55_SABLE_CLUES, FALSE
	setvar VAR_0x8005, 2
	special Part55_RecordPoint
	releaseall
	end


Part55_GemFinder::
	lockall
	goto_if_lt VAR_PART55_SABLE_CLUES, 3, Part55_GemFinder_Wait
	goto_if_ge VAR_PART55_SABLEYITE, 1, Part55_GemFinder_Done
	playmoncry SPECIES_SABLEYE, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part55_Text_0197, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part55_GemFinder_Stone
	setwildbattle SPECIES_SABLEYE, 32, ITEM_NONE
	dowildbattle
Part55_GemFinder_Stone::
	msgbox Part55_Text_0198, MSGBOX_DEFAULT
	giveitem ITEM_BITTEN_STONE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_SABLEYITE, 1
	releaseall
	end


Part55_GemFinder_Wait::
	msgbox Part55_Text_0199, MSGBOX_DEFAULT
	releaseall
	end


Part55_GemFinder_Done::
	msgbox Part55_Text_0200, MSGBOX_DEFAULT
	releaseall
	end


Part55_GemMerchant::
	lock
	faceplayer
	goto_if_eq VAR_PART55_SABLEYITE, 3, Part55_GemMerchant_Done
	goto_if_ne VAR_PART55_SABLEYITE, 1, Part55_GemMerchant_Wait
	checkitem ITEM_BITTEN_STONE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_GemMerchant_Wait
	msgbox Part55_Text_0201, MSGBOX_DEFAULT
	giveitem ITEM_SABLENITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_BITTEN_STONE, 1
	setvar VAR_PART55_SABLEYITE, 3
	release
	end


Part55_GemMerchant_Wait::
	msgbox Part55_Text_0202, MSGBOX_DEFAULT
	release
	end


Part55_GemMerchant_Done::
	msgbox Part55_Text_0203, MSGBOX_DEFAULT
	release
	end


Part55_JointOfficeBoard::
	msgbox Part55_Text_0204, MSGBOX_NPC
	end


Part55_StarCalibration::
	lock
	faceplayer
	goto_if_eq VAR_PART55_STAR_CALIBRATION, 31, Part55_StarCalibration_Done
	goto_if_eq VAR_PART55_STAR_CALIBRATION, 15, Part55_StarCalibration_Reward
	goto_if_ge VAR_PART55_STAR_CALIBRATION, 8, Part55_StarCalibration_Wait
	setvar VAR_PART55_STAR_CALIBRATION, 8
	msgbox Part55_Text_0205, MSGBOX_DEFAULT
	release
	end


Part55_StarCalibration_Reward::
	msgbox Part55_Text_0206, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_STAR_CALIBRATION, 31
	release
	end


Part55_StarCalibration_Wait::
	msgbox Part55_Text_0207, MSGBOX_DEFAULT
	release
	end


Part55_StarCalibration_Done::
	msgbox Part55_Text_0208, MSGBOX_DEFAULT
	release
	end


Part55_StarSea::
	lockall
	goto_if_lt VAR_PART55_STAR_CALIBRATION, 8, Part55_StarSea_Wait
	goto_if_eq VAR_PART55_STAR_CALIBRATION, 31, Part55_StarSea_Wait
	msgbox Part55_Text_0209, MSGBOX_DEFAULT
	setvar VAR_0x8004, VAR_PART55_STAR_CALIBRATION, FALSE
	setvar VAR_0x8005, 1
	special Part55_RecordPoint
	releaseall
	end


Part55_StarSea_Wait::
	msgbox Part55_Text_0210, MSGBOX_DEFAULT
	releaseall
	end


Part55_StarWhiteRock::
	goto Part55_WhiteRock


Part55_StarWhiteRock_Wait::
	msgbox Part55_Text_0212, MSGBOX_DEFAULT
	releaseall
	end


Part55_StarSpace::
	lockall
	goto_if_lt VAR_PART55_STAR_CALIBRATION, 8, Part55_StarSpace_Wait
	goto_if_eq VAR_PART55_STAR_CALIBRATION, 31, Part55_StarSpace_Wait
	msgbox Part55_Text_0213, MSGBOX_DEFAULT
	setvar VAR_0x8004, VAR_PART55_STAR_CALIBRATION, FALSE
	setvar VAR_0x8005, 4
	special Part55_RecordPoint
	releaseall
	end


Part55_StarSpace_Wait::
	msgbox Part55_Text_0214, MSGBOX_DEFAULT
	releaseall
	end


Part55_Postman::
	lock
	faceplayer
	goto_if_eq VAR_PART55_AIR_MAIL, 3, Part55_Postman_Done
	goto_if_eq VAR_PART55_AIR_MAIL, 2, Part55_Postman_Reward
	goto_if_eq VAR_PART55_AIR_MAIL, 1, Part55_Postman_Wait
	msgbox Part55_Text_0215, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part55_Postman_Bye
	giveitem ITEM_URGENT_AIR_MAIL, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_AIR_MAIL, 1
	release
	end


Part55_PostPidgeot::
	lock
	faceplayer
	playmoncry SPECIES_PIDGEOT, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_Postman_Wait::
	msgbox Part55_Text_0216, MSGBOX_DEFAULT
	release
	end


Part55_Postman_Reward::
	checkitem ITEM_DELIVERY_RECEIPT, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_Postman_Wait
	msgbox Part55_Text_0217, MSGBOX_DEFAULT
	giveitem ITEM_PIDGEOTITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_DELIVERY_RECEIPT, 1
	setvar VAR_PART55_AIR_MAIL, 3
	release
	end


Part55_Postman_Done::
	msgbox Part55_Text_0218, MSGBOX_DEFAULT
	release
	end


Part55_Postman_Bye::
	release
	end


Part55_AirReception::
	lock
	faceplayer
	goto_if_ne VAR_PART55_AIR_MAIL, 1, Part55_AirReception_After
	checkitem ITEM_URGENT_AIR_MAIL, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_AirReception_After
	msgbox Part55_Text_0219, MSGBOX_DEFAULT
	giveitem ITEM_DELIVERY_RECEIPT, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_URGENT_AIR_MAIL, 1
	setvar VAR_PART55_AIR_MAIL, 2
	release
	end


Part55_AirReception_After::
	msgbox Part55_Text_0220, MSGBOX_DEFAULT
	release
	end


Part55_RocketEnthusiast::
	lock
	faceplayer
	goto_if_ge VAR_MOSSDEEP_SPACE_CENTER_STATE, 3, Part55_RocketEnthusiast_Post
	msgbox Part55_Text_0221, MSGBOX_DEFAULT
	release
	end


Part55_RocketEnthusiast_Post::
	msgbox Part55_Text_0222, MSGBOX_DEFAULT
	release
	end


Part55_OffDutyResearcher::
	lock
	faceplayer
	goto_if_ge VAR_MOSSDEEP_SPACE_CENTER_STATE, 3, Part55_OffDutyResearcher_Post
	msgbox Part55_Text_0223, MSGBOX_DEFAULT
	release
	end


Part55_OffDutyResearcher_Post::
	msgbox Part55_Text_0224, MSGBOX_DEFAULT
	release
	end


Part55_StargazeCouple::
	goto_if_set FLAG_STORY_C_02, Part55_StargazeCouple_Talk
	trainerbattle_double TRAINER_STORY_C_04, StoryC_Text_StarIntro, StoryC_Text_StarDefeat, StoryC_Text_StarNotEnough, Part55_StargazeCouple_Won
	release
	end

Part55_StargazeCouple_Won::
	setflag FLAG_STORY_C_02
Part55_StargazeCouple_Talk::
	lock
	faceplayer
	goto_if_ge VAR_MOSSDEEP_SPACE_CENTER_STATE, 3, Part55_StargazeCouple_Post
	msgbox Part55_Text_0225, MSGBOX_DEFAULT
	release
	end


Part55_StargazeCouple_Post::
	msgbox Part55_Text_0226, MSGBOX_DEFAULT
	release
	end


Part55_OldNavigator::
	lock
	faceplayer
	goto_if_ge VAR_MOSSDEEP_SPACE_CENTER_STATE, 3, Part55_OldNavigator_Post
	msgbox Part55_Text_0227, MSGBOX_DEFAULT
	release
	end


Part55_OldNavigator_Post::
	msgbox Part55_Text_0228, MSGBOX_DEFAULT
	release
	end


Part55_GeologyVisitor::
	lock
	faceplayer
	goto_if_ge VAR_MOSSDEEP_SPACE_CENTER_STATE, 3, Part55_GeologyVisitor_Post
	msgbox Part55_Text_0229, MSGBOX_DEFAULT
	release
	end


Part55_GeologyVisitor_Post::
	msgbox Part55_Text_0230, MSGBOX_DEFAULT
	release
	end


Part55_Text_0188:
	.string "老师让我观察画里的宝可梦。画家连尾\n巴上的花纹都画得很仔细。$"

Part55_Text_0189:
	.string "画里的宝可梦是你的吧？我刚才还在临\n摹它的姿势呢！$"

Part55_Text_0190:
	.string "伴奏就交给吼爆弹了。别担心，它练过\n音量，不会把港口的船都吓走。$"

Part55_Text_0191:
	.string "第七枚徽章？厉害呀。下一首送给走过\n这么多地方的你！$"

Part55_Text_0192:
	.string "说好在港口等人，我却走到百货商店来\n了。谢谢你指路，我记住啦。$"

Part55_Text_0193:
	.string "沿着街道往港口走，这回不会记错了。$"

Part55_Text_0194:
	.string "已经到港口了。我家里人一会儿就来，\n刚才麻烦你指路了。$"

Part55_Text_0195:
	.string "石头上有细细的划痕。旁边散落着装饰\n品上的金属屑。$"

Part55_Text_0196:
	.string "这里留着少量宝石粉末。看起来有什么\n东西把石头咬碎过。$"

Part55_Text_0197:
	.string "勾魂眼抱着咬过的饰石，从岩缝里钻了\n出来！要靠近它吗？$"

Part55_Text_0198:
	.string "勾魂眼退回岩缝，留下了一块咬过的饰\n石。$"

Part55_Text_0199:
	.string "岩缝里面像有什么东西。附近的划痕和\n粉末还没看清楚。$"

Part55_Text_0200:
	.string "岩缝里已经没有那块装饰石了。$"

Part55_Text_0201:
	.string "我的饰石怎么变成这样了！原来是勾魂\n眼拿走了……算了，找回来就好。这颗石\p头送给你。$"

Part55_Text_0202:
	.string "我刚摆好饰石就少了一块。海边有划痕\n和宝石粉末，能帮我看看吗？$"

Part55_Text_0203:
	.string "看来宝石不能随便放在海边。以后得盖\n好盒子。$"

Part55_Text_0204:
	.string "阿尔刻与宇宙中心联合观测联络处：双\n方交换大气观测资料。项目由各自研究\p团队负责。$"

Part55_Text_0205:
	.string "观星仪刚装好。能帮我对照海边、白色\n岩石旁、宇宙中心门外三个记录点吗？$"

Part55_Text_0206:
	.string "三处记录对上了，仪器校准完毕。多谢\n你来回跑。$"

Part55_Text_0207:
	.string "三个记录点在海边、白色岩石旁和宇宙\n中心门外。每一处都有一个小标记。$"

Part55_Text_0208:
	.string "观星仪已经校准了。今晚再试着记录几\n颗星。$"

Part55_Text_0209:
	.string "对照了记录点的方位，写下当前的观测\n值。$"

Part55_Text_0210:
	.string "一个用于对照方位的小标记。现在不需\n要记录。$"

Part55_Text_0211:
	.string "对照了记录点的方位，写下当前的观测\n值。$"

Part55_Text_0212:
	.string "一个用于对照方位的小标记。现在不需\n要记录。$"

Part55_Text_0213:
	.string "对照了记录点的方位，写下当前的观测\n值。$"

Part55_Text_0214:
	.string "一个用于对照方位的小标记。现在不需\n要记录。$"

Part55_Text_0215:
	.string "大比鸟飞了一整天，得让它休息。这封\n加急信要送到绿岭宇宙中心的接待处，\p能帮我带去吗？$"

Part55_Text_0216:
	.string "交给宇宙中心接待处后，请把签收回执\n带回来。$"

Part55_Text_0217:
	.string "回执收到了！大比鸟也休息好了。这颗\n石头请你带着，也算帮它分担一趟路的\p谢礼。$"

Part55_Text_0218:
	.string "今天的急件都送到了。谢谢你帮忙，大\n比鸟也精神多了。$"

Part55_Text_0219:
	.string "是今天的急件！我签一下，请把回执交\n给邮递员。$"

Part55_Text_0220:
	.string "接待处也负责登记邮递件。加急信请直\n接交给我。$"

Part55_Text_0221:
	.string "我在这里住了十二天，就为了看一次发\n射。每天都来问倒计时。$"

Part55_Text_0222:
	.string "上次的事把我吓了一跳。还好宇宙中心\n能继续工作。$"

Part55_Text_0223:
	.string "今天终于准时下班。希望回家时孩子还\n没睡。$"

Part55_Text_0224:
	.string "事情过后，要重新核对的记录更多了。\n今晚还是早点休息吧。$"

Part55_Text_0225:
	.string "约好一起看星星，他却先睡着了。我得\n给他把外套盖好。$"

Part55_Text_0226:
	.string "今晚很安静。终于能好好看一会儿星星\n了。$"

Part55_Text_0227:
	.string "以前在海上，我常靠星星认方向。年轻\n人现在的仪器可方便多了。$"

Part55_Text_0228:
	.string "好在海边恢复平静了。看星星时也放心\n些。$"

Part55_Text_0229:
	.string "我来看看海边的地层。这里岩石的颜色\n和家乡很不一样。$"

Part55_Text_0230:
	.string "观测记录还在，旅行也能继续了。等天\n气稳定再到海边看看。$"
Part55_MaintenanceEntry::
	lockall
	msgbox Part55_Text_0231, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part55_MaintenanceEntry_End
	warp MAP_ARCHE_CAMPUS_MAINTENANCE, 0
	waitstate
	releaseall
	end


Part55_MaintenanceEntry_End::
	releaseall
	end


Part55_Excadrill::
	lock
	faceplayer
	goto_if_ge VAR_PART55_STEELIX_REPAIR, 1, Part55_Excadrill_After
	playmoncry SPECIES_EXCADRILL, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part55_Text_0232, MSGBOX_DEFAULT
	setwildbattle SPECIES_EXCADRILL, 35, ITEM_NONE
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Part55_Excadrill_Clear
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Part55_Excadrill_Clear
	release
	end


Part55_Excadrill_Clear::
	setvar VAR_PART55_STEELIX_REPAIR, 1
	setflag FLAG_PART55_HIDE_EXCADRILL
	removeobject LOCALID_PART55_EXCADRILL
	setmetatile 4, 6, 776, FALSE
	special DrawWholeMapView
	msgbox Part55_Text_0233, MSGBOX_DEFAULT
	release
	end


Part55_Excadrill_After::
	release
	end


Part55_WorkSteelix::
	lock
	faceplayer
	playmoncry SPECIES_STEELIX, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_SteelixForeman::
	lock
	faceplayer
	goto_if_eq VAR_PART55_STEELIX_REPAIR, 3, Part55_SteelixForeman_Done
	goto_if_lt VAR_PART55_STEELIX_REPAIR, 1, Part55_SteelixForeman_Wait
	msgbox Part55_Text_0234, MSGBOX_DEFAULT
	giveitem ITEM_STEELIXITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_STEELIX_REPAIR, 3
	release
	end


Part55_SteelixForeman_Wait::
	msgbox Part55_Text_0235, MSGBOX_DEFAULT
	release
	end


Part55_SteelixForeman_Done::
	msgbox Part55_Text_0236, MSGBOX_DEFAULT
	release
	end


Part55_HideExcadrill::
	setflag FLAG_PART55_HIDE_EXCADRILL
	return


Part55_MaintenanceLoad::
	call_if_ge VAR_PART55_STEELIX_REPAIR, 1, Part55_OpenMaintenance
	end


Part55_OpenMaintenance::
	setmetatile 4, 6, 776, FALSE
	return


Part55_RescueEntry::
	lockall
	msgbox Part55_Text_0237, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Part55_RescueEntry_End
	warp MAP_MAGMA_HIDEOUT_RESCUE_PASSAGE, 0
	waitstate
	releaseall
	end


Part55_RescueEntry_End::
	releaseall
	end


Part55_RescueSwitch::
	lockall
	goto_if_ge VAR_PART55_HOUNDOUR_RESCUE, 1, Part55_RescueSwitch_After
	setvar VAR_PART55_HOUNDOUR_RESCUE, 1
	setmetatile 4, 6, 776, FALSE
	special DrawWholeMapView
	msgbox Part55_Text_0238, MSGBOX_DEFAULT
	releaseall
	end


Part55_RescueSwitch_After::
	msgbox Part55_Text_0239, MSGBOX_DEFAULT
	releaseall
	end


Part55_HoundourRescue::
	lock
	faceplayer
	goto_if_eq VAR_PART55_HOUNDOUR_RESCUE, 3, Part55_HoundourRescue_Done
	goto_if_lt VAR_PART55_HOUNDOUR_RESCUE, 1, Part55_HoundourRescue_Wait
	setvar VAR_PART55_HOUNDOUR_RESCUE, 2
	msgbox Part55_Text_0240, MSGBOX_DEFAULT
	giveitem ITEM_HOUNDOOMINITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_HOUNDOUR_RESCUE, 3
	release
	end


Part55_HoundourRescue_Wait::
	msgbox Part55_Text_0241, MSGBOX_DEFAULT
	release
	end


Part55_HoundourRescue_Done::
	msgbox Part55_Text_0242, MSGBOX_DEFAULT
	release
	end


Part55_Houndour::
	lock
	faceplayer
	playmoncry SPECIES_HOUNDOUR, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_RescueLoad::
	call_if_ge VAR_PART55_HOUNDOUR_RESCUE, 1, Part55_OpenRescue
	end


Part55_OpenRescue::
	setmetatile 4, 6, 776, FALSE
	return


Part55_RescuedMagmaExit::
	lock
	faceplayer
	goto_if_eq VAR_PART55_HOUNDOUR_RESCUE, 2, Part55_ExitRescueReward
Part55_ExitRescueDepart::
	msgbox Part55_Text_0299, MSGBOX_DEFAULT
	setflag FLAG_PART55_RESCUED_MAGMA_LEFT
	setflag FLAG_PART55_HIDE_RESCUED_MAGMA
	removeobject LOCALID_PART55_RescuedMagmaExit
	removeobject LOCALID_PART55_RescuedHoundourExit
	release
	end

Part55_RescuedHoundourExit::
	lock
	faceplayer
	playmoncry SPECIES_HOUNDOUR, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_CheckRescuedExit::
	call_if_ge VAR_PART55_HOUNDOUR_RESCUE, 2, Part55_ShowRescuedExit
	return


Part55_ShowRescuedExit::
	goto_if_set FLAG_PART55_RESCUED_MAGMA_LEFT, Part55_ShowRescuedExit_Already
	clearflag FLAG_PART55_HIDE_RESCUED_MAGMA
	return


Part55_Text_0231:
	.string "排水通道入口。工地师傅正在里面检查\n。要进去吗？$"

Part55_Text_0232:
	.string "龙头地鼠挡在堵住的排水口前，拍了拍\n地面。$"

Part55_Text_0233:
	.string "龙头地鼠离开了堵塞处。清开碎石以后\n，排水恢复了。$"

Part55_Text_0234:
	.string "水终于流下去了！大钢蛇今天也能收工\n了。这颗石头作为谢礼给你。$"

Part55_Text_0235:
	.string "小排水沟堵住了，龙头地鼠守在排水口\n前。通道在物流站侧门，大钢蛇也在那\p里帮忙。$"

Part55_Text_0236:
	.string "排水口检查过了。下次施工前得先围好\n挡板。$"

Part55_Text_0237:
	.string "侧面的小通道传来戴鲁比的叫声。要进\n去看看吗？$"

Part55_Text_0238:
	.string "扳动了通风装置旁的开关。挡在通道上\n的岩板退开了，热气也散了一些。$"

Part55_Text_0239:
	.string "开关已经打开，通道可以通过了。$"

Part55_Text_0240:
	.string "终于能出来了……我们在里面待得太久，\n戴鲁比都热坏了。今天先不跟你打了。\p这颗石头给你。刚才欠你的，我可记着\n。$"

Part55_Text_0241:
	.string "通道被挡住了！能不能先把旁边的通风\n开关打开？$"

Part55_Text_0242:
	.string "戴鲁比好多了。出口已经打开，我们歇\n一会儿就走。$"

Part55_Text_0243:
	.string "刚才的事，我欠你一次。里面太危险了\n，快离开吧！戴鲁比，我们也走。$"
Part55_RookieTeamup::
	lockall
	goto_if_set FLAG_PART55_ROOKIE_TEAMUP_DONE, Part55_RookieTeamup_After
	msgbox Part55_Text_0244, MSGBOX_DEFAULT
	multi_2_vs_2 TRAINER_PART55_AQUA_OBSERVER_A, Part55_Text_0245, TRAINER_PART55_AQUA_OBSERVER_B, Part55_Text_0246, PARTNER_PART55_ROOKIE, cancelScript=Part55_RookieTeamup_Cancel
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Part55_RookieTeamup_Win
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	end


Part55_RookieTeamup_Cancel::
	releaseall
	end

Part55_TeamupPuff::
	lock
	faceplayer
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_TeamupAquaA::
	msgbox Part55_Text_0247, MSGBOX_NPC
	end


Part55_TeamupAquaB::
	msgbox Part55_Text_0248, MSGBOX_NPC
	end


Part55_RookieTeamup_Win::
	setflag FLAG_PART55_ROOKIE_TEAMUP_DONE
	msgbox Part55_Text_0249, MSGBOX_DEFAULT
	removeobject LOCALID_PART55_TeamupAquaA
	removeobject LOCALID_PART55_TeamupAquaB
	releaseall
	end


Part55_RookieTeamup_After::
	msgbox Part55_Text_0250, MSGBOX_DEFAULT
	releaseall
	end


Part55_HideTeamup::
	setflag FLAG_PART55_HIDE_ROOKIE_TEAMUP
	return


Part55_RookieFormal::
	lock
	faceplayer
	goto_if_defeated TRAINER_GRUNT_MAGMA_HIDEOUT_14, Part5_MagmaRookie_After
	call_if_set FLAG_PART55_ROOKIE_TEAMUP_DONE, Part55_RookieFormalRecall
	release
	goto Part5_MagmaRookie


Part55_RookieFormalRecall::
	msgbox Part55_Text_0251, MSGBOX_DEFAULT
	return


Part55_BasePuff::
	lock
	faceplayer
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	goto_if_defeated TRAINER_GRUNT_MAGMA_HIDEOUT_14, Part55_BasePuff_After
	msgbox Part55_Text_0252, MSGBOX_DEFAULT
	release
	end


Part55_BasePuff_After::
	msgbox Part55_Text_0253, MSGBOX_DEFAULT
	release
	end


Part55_RookieColleague::
	msgbox Part55_Text_0254, MSGBOX_NPC
	end


Part55_MagmaBento::
	lock
	faceplayer
	goto_if_defeated TRAINER_GRUNT_MAGMA_HIDEOUT_4, Part55_MagmaBento_After
	msgbox Part55_Text_0255, MSGBOX_DEFAULT
	release
	goto MagmaHideout_2F_1R_EventScript_Grunt4


Part55_MagmaBento_After::
	msgbox Part55_Text_0256, MSGBOX_DEFAULT
	release
	end


Part55_MagmaGloves::
	lock
	faceplayer
	goto_if_defeated TRAINER_GRUNT_MAGMA_HIDEOUT_5, Part55_MagmaGloves_After
	msgbox Part55_Text_0257, MSGBOX_DEFAULT
	release
	goto MagmaHideout_2F_1R_EventScript_Grunt5


Part55_MagmaGloves_After::
	msgbox Part55_Text_0258, MSGBOX_DEFAULT
	release
	end


Part55_Seasick::
	lock
	faceplayer
	goto_if_defeated TRAINER_GRUNT_AQUA_HIDEOUT_2, Part55_Seasick_After
	msgbox Part55_Text_0259, MSGBOX_DEFAULT
	release
	goto AquaHideout_B1F_EventScript_Grunt2


Part55_Seasick_After::
	msgbox Part55_Text_0260, MSGBOX_DEFAULT
	release
	end


Part55_MightyenaGrave::
	msgbox Part55_Text_0261, MSGBOX_NPC
	end


Part55_BallGrave::
	msgbox Part55_Text_0262, MSGBOX_NPC
	end


Part55_SnackGrave::
	msgbox Part55_Text_0263, MSGBOX_NPC
	end


Part55_MemorialWall::
	lockall
	goto_if_ge VAR_PART55_MEMORIAL_MESSAGE, 1, Part55_MemorialWall_After
	msgbox Part55_Text_0264, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Part55_Memorial_Thanks
	msgbox Part55_Text_0265, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Part55_Memorial_Travel
	msgbox Part55_Text_0266, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Part55_Memorial_Return
	releaseall
	end


Part55_Memorial_Thanks::
	setvar VAR_PART55_MEMORIAL_MESSAGE, 1
	msgbox Part55_Text_0267, MSGBOX_DEFAULT
	releaseall
	end


Part55_Memorial_Travel::
	setvar VAR_PART55_MEMORIAL_MESSAGE, 2
	msgbox Part55_Text_0268, MSGBOX_DEFAULT
	releaseall
	end


Part55_Memorial_Return::
	setvar VAR_PART55_MEMORIAL_MESSAGE, 3
	msgbox Part55_Text_0269, MSGBOX_DEFAULT
	releaseall
	end


Part55_MemorialWall_After::
	goto_if_eq VAR_PART55_MEMORIAL_MESSAGE, 1, Part55_Memorial_ShowThanks
	goto_if_eq VAR_PART55_MEMORIAL_MESSAGE, 2, Part55_Memorial_ShowTravel
	goto Part55_Memorial_ShowReturn


Part55_Memorial_ShowThanks::
	msgbox Part55_Text_0270, MSGBOX_DEFAULT
	releaseall
	end


Part55_Memorial_ShowTravel::
	msgbox Part55_Text_0271, MSGBOX_DEFAULT
	releaseall
	end


Part55_Memorial_ShowReturn::
	msgbox Part55_Text_0272, MSGBOX_DEFAULT
	releaseall
	end


Part55_DollShuppet::
	lock
	faceplayer
	goto_if_set FLAG_PART5_BANETTITE, Part55_DollShuppet_After
	goto_if_ge VAR_PART55_DOLL, 1, Part55_DollShuppet_After
	playmoncry SPECIES_SHUPPET, CRY_MODE_NORMAL
	waitmoncry
	msgbox Part55_Text_0273, MSGBOX_DEFAULT
	giveitem ITEM_OLD_DOLL, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_DOLL, 1
	applymovement LOCALID_PART5_BANETTITE, Part55_ShuffleAside
	waitmovement 0
	setobjectxy LOCALID_PART5_BANETTITE, 10, 25
	setobjectxyperm LOCALID_PART5_BANETTITE, 10, 25
	release
	end


Part55_DollShuppet_After::
	playmoncry SPECIES_SHUPPET, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_DollChild::
	msgbox Part55_Text_0274, MSGBOX_NPC
	end


Part55_DollGrandma::
	lock
	faceplayer
	goto_if_set FLAG_PART5_BANETTITE, Part55_DollGrandma_Done
	goto_if_ne VAR_PART55_DOLL, 1, Part55_DollGrandma_Wait
	checkitem ITEM_OLD_DOLL, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_DollGrandma_Wait
	msgbox Part55_Text_0275, MSGBOX_DEFAULT
	giveitem ITEM_BANETTITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	removeitem ITEM_OLD_DOLL, 1
	setflag FLAG_PART5_BANETTITE
	setvar VAR_PART55_DOLL, 3
	release
	end


Part55_DollGrandma_Wait::
	msgbox Part55_Text_0276, MSGBOX_DEFAULT
	release
	end


Part55_DollGrandma_Done::
	msgbox Part55_Text_0277, MSGBOX_DEFAULT
	release
	end


Part55_FlowerOldManExtra::
	lock
	faceplayer
	msgbox Part55_Text_0278, MSGBOX_DEFAULT
	release
	goto Part5_FlowerOldMan


Part55_GraveWorker::
	goto_if_set FLAG_STORY_C_01, Part55_GraveWorker_Talk
	trainerbattle_single TRAINER_STORY_C_03, StoryC_Text_GraveIntro, StoryC_Text_GraveDefeat, Part55_GraveWorker_Won
	release
	end

Part55_GraveWorker_Won::
	setflag FLAG_STORY_C_01
Part55_GraveWorker_Talk::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, Part55_GraveWorker_Clear
	goto_if_set FLAG_RECEIVED_HM_WATERFALL, Part55_GraveWorker_Quiet
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, Part55_GraveWorker_Crisis
	msgbox Part55_Text_0279, MSGBOX_DEFAULT
	release
	end


Part55_GraveWorker_Crisis::
	msgbox Part55_Text_0280, MSGBOX_DEFAULT
	release
	end


Part55_GraveWorker_Quiet::
	msgbox Part55_Text_0281, MSGBOX_DEFAULT
	release
	end


Part55_GraveWorker_Clear::
	msgbox Part55_Text_0282, MSGBOX_DEFAULT
	release
	end


Part55_Text_0244:
	.string "又是你！嘘，小声点，我在执行正式的\n观察任务。\p……糟了，被发现了！他们把我们包围了\n。\p你问为什么把你也算进来？现在先一起\n应付一下啦！$"

Part55_Text_0245:
	.string "居然让他们配合起来了！$"

Part55_Text_0246:
	.string "先撤，换个地方调查！$"

Part55_Text_0247:
	.string "那边是谁？别躲着了，我们都看见了！$"

Part55_Text_0248:
	.string "你们两个，先别在那边嘀咕了！$"

Part55_Text_0249:
	.string "刚才只是临时合作！下次执行任务，我\n还是会拦住你的。\p大概……我可没说一定会输！好了，我要\n继续调查了。$"

Part55_Text_0250:
	.string "我还在调查啦。刚才的合作，你可别到\n处说。$"

Part55_Text_0251:
	.string "送神火山那次只是临时合作。今天我们\n是对手，胖丁也准备好了！$"

Part55_Text_0252:
	.string "新人：还没开始打呢，不准先和胖丁交\n朋友！$"

Part55_Text_0253:
	.string "新人：它好像挺喜欢你……我才没有说！$"

Part55_Text_0254:
	.string "刚开始还笑她只带胖丁。后来跟她练过\n一场……算了，不提那个结果了。$"

Part55_Text_0255:
	.string "刚把便当放下就有人来了……等一下，你\n不是我们的人！$"

Part55_Text_0256:
	.string "便当都凉了。今天怎么什么事都凑在一\n起。$"

Part55_Text_0257:
	.string "手套又磨破了……喂，谁让你进来的！$"

Part55_Text_0258:
	.string "我还得去领新手套。挖石头可比说起来\n费劲。$"

Part55_Text_0259:
	.string "坐船真是难受……等等，你怎么到这里来\n了！$"

Part55_Text_0260:
	.string "我先喘口气。能不能等浪小一点再出发\n啊。$"

Part55_Text_0261:
	.string "陪伴了家人二十年的大狼犬。你总能听\n见我们回家的脚步。$"

Part55_Text_0262:
	.string "旧精灵球旁放着一封信：谢谢你，每次\n都等我一起回家。$"

Part55_Text_0263:
	.string "墓碑前放着一小包点心。纸条写着：你\n最喜欢的，我又带来了。$"

Part55_Text_0264:
	.string "留言簿上写满了短短的祝福。要写下“\n谢谢你”吗？$"

Part55_Text_0265:
	.string "要写下“旅途愉快”吗？$"

Part55_Text_0266:
	.string "要写下“我还会回来”吗？$"

Part55_Text_0267:
	.string "写下了：谢谢你。$"

Part55_Text_0268:
	.string "写下了：旅途愉快。$"

Part55_Text_0269:
	.string "写下了：我还会回来。$"

Part55_Text_0270:
	.string "你留下的字迹：谢谢你。$"

Part55_Text_0271:
	.string "你留下的字迹：旅途愉快。$"

Part55_Text_0272:
	.string "你留下的字迹：我还会回来。$"

Part55_Text_0273:
	.string "怨影娃娃让开了一点。它身后放着一只\n旧布偶。$"

Part55_Text_0274:
	.string "我把旧布偶落在上面的墓碑旁了……奶奶\n说别着急，可我还是很担心。$"

Part55_Text_0275:
	.string "布偶找到了！原来是怨影娃娃帮忙收着\n。孩子终于放心了，这颗石头给你吧。$"

Part55_Text_0276:
	.string "孩子惦记着她的旧布偶。要是路过上面\n的墓碑，能帮我们看看吗？$"

Part55_Text_0277:
	.string "布偶还好好的。谢谢你，孩子已经把它\n抱紧了。$"

Part55_Text_0278:
	.string "墓碑旁常有小小的脚印。山上的花也很\n特别，有些很久才见得到。$"

Part55_Text_0279:
	.string "我在这里工作很多年了。每天清扫，再\n看看谁家的花该换了。$"

Part55_Text_0280:
	.string "最近山上的风都乱了。先把花盆收好，\n免得被吹倒。$"

Part55_Text_0281:
	.string "风总算安静些了。今天可以把墓碑都好\n好擦一遍。$"

Part55_Text_0282:
	.string "又有熟人来探望了。日子慢慢恢复了，\n这里也和以前一样。$"
Part55_MagmaBentoDesk::
	msgbox Part55_Text_0283, MSGBOX_NPC
	end


Part55_MagmaGloveShelf::
	msgbox Part55_Text_0284, MSGBOX_NPC
	end


Part55_MagmaRoster::
	msgbox Part55_Text_0285, MSGBOX_NPC
	end


Part55_MagmaStoneComplaint::
	msgbox Part55_Text_0286, MSGBOX_NPC
	end


Part55_AquaWetSocks::
	msgbox Part55_Text_0287, MSGBOX_NPC
	end


Part55_AquaWaterproof::
	msgbox Part55_Text_0288, MSGBOX_NPC
	end


Part55_AquaBento::
	msgbox Part55_Text_0289, MSGBOX_NPC
	end


Part55_AquaRota::
	msgbox Part55_Text_0290, MSGBOX_NPC
	end


Part55_UnsignedPostcard::
	msgbox Part55_Text_0291, MSGBOX_NPC
	end


Part55_AquaBottles::
	lockall
	goto_if_set FLAG_TEMP_1F, Part55_AquaBottles_Again
	setflag FLAG_TEMP_1F
	msgbox Part55_Text_0292, MSGBOX_DEFAULT
	releaseall
	end


Part55_AquaBottles_Again::
	msgbox Part55_Text_0293, MSGBOX_DEFAULT
	releaseall
	end


Part55_AquaFoodWorker::
	msgbox Part55_Text_0294, MSGBOX_NPC
	end


Part55_SeasickColleague::
	msgbox Part55_Text_0295, MSGBOX_NPC
	end


Part55_MagmaReadings::
	msgbox Part55_Text_0296, MSGBOX_NPC
	end


Part55_MagmaStubborn::
	msgbox Part55_Text_0297, MSGBOX_NPC
	end


Part55_ShowMagmaAftermath::
	clearflag FLAG_PART55_HIDE_MAGMA_AFTERMATH
	return


Part55_BoyfriendExtra::
	lock
	faceplayer
	call_if_ne VAR_PART2_PEACE_CHARM_STATE, PART2_CHARM_COMPLETED, Part55_BoyfriendHesitation
	release
	goto Part5_SlateBoyfriend


Part55_BoyfriendHesitation::
	msgbox Part55_Text_0298, MSGBOX_DEFAULT
	turnobject LOCALID_PART5_SLATE_BOYFRIEND, DIR_NORTH
	delay 16
	faceplayer
	return


Part55_ShowRescuedExit_Already::
	return


Part55_Text_0283:
	.string "桌上放着几只便当盒。一张纸条写着：\n别把饭盒放在热石头上。$"

Part55_Text_0284:
	.string "架子上叠着磨破的工作手套。新的还没\n领回来。$"

Part55_Text_0285:
	.string "墙上贴着轮班表。今天的挖掘班还有两\n个人没签到。$"

Part55_Text_0286:
	.string "工具箱上留着字条：这里的石头太硬了\n，凿子又坏了一把。$"

Part55_Text_0287:
	.string "椅背上挂着湿袜子。下面垫的纸也湿透\n了。$"

Part55_Text_0288:
	.string "柜子里塞着几只防水袋。一个袋口还粘\n着米粒。$"

Part55_Text_0289:
	.string "吃了一半的便当旁放着船班表。下一班\n的时间被圈了起来。$"

Part55_Text_0290:
	.string "轮班表上有人写着：下次别把我的名字\n又排到夜班。$"

Part55_Text_0291:
	.string "一张没有署名的明信片。上面写着：有\n空记得回家吃顿饭。你把它放回原处。$"

Part55_Text_0292:
	.string "床边堆着几个空瓶子，还没来得及收走\n。$"

Part55_Text_0293:
	.string "仔细看了一眼，有个瓶子已经用来插小\n花了。其余的还是空着。$"

Part55_Text_0294:
	.string "今天忘了吃午饭，伙伴的食物倒是按时\n分好了。它们一饿就闹腾，我可记得清\p楚。$"

Part55_Text_0295:
	.string "那家伙又晕船了。每次上船前都说这次\n肯定没问题。$"

Part55_Text_0296:
	.string "仪器读数根本停不下来……里面太热了，\n我得先出去透口气！$"

Part55_Text_0297:
	.string "应该……应该没事吧？首领说过能控制的\n。可是这里怎么越来越热了。$"

Part55_Text_0298:
	.string "都到这里了，我还在门口磨蹭……这次不\n能再让她等了。$"

Part55_Text_0299:
	.string "刚才的事，我欠你一次。里面太危险了\n，快离开吧！戴鲁比，我们也走。$"
Part55_FoundMother::
	msgbox Part55_Text_0300, MSGBOX_NPC
	end


Part55_ShowFoundMother::
	clearflag FLAG_PART55_HIDE_DEPT_MOTHER
	return


Part55_HideDepartedMother::
	setflag FLAG_TEMP_1C
	return


Part55_PatientFriend::
	msgbox Part55_Text_0301, MSGBOX_NPC
	end


Part55_ShowPatientFriend::
	clearflag FLAG_PART55_HIDE_PATIENT_FRIEND
	return


Part55_HideMedicineSender::
	setflag FLAG_TEMP_1D
	return


Part55_AdvanceSoloVisit::
	addvar VAR_PART55_SOLO_TRAVEL, 1
	return


Part55_HideSoloHotel::
	setflag FLAG_TEMP_1B
	return


Part55_SoloSafari::
	msgbox Part55_Text_0302, MSGBOX_NPC
	end


Part55_SoloSafariEevee::
	lock
	faceplayer
	playmoncry SPECIES_EEVEE, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_ShowSafariTraveler::
	clearflag FLAG_PART55_HIDE_SAFARI_TRAVELER
	return


Part55_AdvanceEmployeeVisit::
	addvar VAR_PART55_NEW_EMPLOYEE, 1
	return


Part55_AdvanceGuardVisit::
	addvar VAR_PART55_HQ_GUARD_VISITS, 1
	return


Part55_GateGuard::
	lock
	faceplayer
	goto_if_ge VAR_PART55_HQ_GUARD_VISITS, 3, Part55_GateGuard_Third
	goto_if_eq VAR_PART55_HQ_GUARD_VISITS, 2, Part55_GateGuard_Second
	msgbox Part55_Text_0303, MSGBOX_DEFAULT
	release
	end


Part55_GateGuard_Second::
	msgbox Part55_Text_0304, MSGBOX_DEFAULT
	release
	end


Part55_GateGuard_Third::
	msgbox Part55_Text_0305, MSGBOX_DEFAULT
	release
	end


Part55_BadgeReception::
	lock
	faceplayer
	call_if_set FLAG_BADGE07_GET, Part55_BadgeReception_Recall
	release
	goto Part5_HQReceptionist


Part55_BadgeReception_Recall::
	msgbox Part55_Text_0306, MSGBOX_DEFAULT
	return


Part55_BadgeTrainingDesk::
	lock
	faceplayer
	call_if_set FLAG_BADGE07_GET, Part55_BadgeTrainingDesk_Recall
	release
	goto Part5_TrainingDesk


Part55_BadgeTrainingDesk_Recall::
	msgbox Part55_Text_0307, MSGBOX_DEFAULT
	return


Part55_BadgeCafe::
	lock
	faceplayer
	call_if_set FLAG_BADGE07_GET, Part55_BadgeCafe_Recall
	release
	goto Part5_CafeEmployee


Part55_BadgeCafe_Recall::
	msgbox Part55_Text_0308, MSGBOX_DEFAULT
	return


Part55_RookieAfterRecall::
	msgbox Part55_Text_0309, MSGBOX_DEFAULT
	return


Part55_BuoyMantyke::
	lock
	faceplayer
	playmoncry SPECIES_MANTYKE, CRY_MODE_NORMAL
	waitmoncry
	release
	end


Part55_HideBuoyFish::
	setflag FLAG_PART55_HIDE_BUOY_MANTYKE
	return


Part55_MossKidAfter::
	lock
	faceplayer
	goto_if_ge VAR_MOSSDEEP_SPACE_CENTER_STATE, 3, Part55_MossKidAfter_Post
	release
	goto Part5_MossKid


Part55_MossKidAfter_Post::
	msgbox Part55_Text_0310, MSGBOX_DEFAULT
	release
	end


Part55_MossParentAfter::
	lock
	faceplayer
	goto_if_ge VAR_MOSSDEEP_SPACE_CENTER_STATE, 3, Part55_MossParentAfter_Post
	release
	goto Part5_MossParent


Part55_MossParentAfter_Post::
	msgbox Part55_Text_0311, MSGBOX_DEFAULT
	release
	end


Part55_LiaisonAfter::
	lock
	faceplayer
	goto_if_ge VAR_MOSSDEEP_SPACE_CENTER_STATE, 3, Part55_LiaisonAfter_Post
	release
	goto Part5_ArcheLiaison


Part55_LiaisonAfter_Post::
	msgbox Part55_Text_0312, MSGBOX_DEFAULT
	release
	end


Part55_SleepingPartner::
	msgbox Part55_Text_0313, MSGBOX_NPC
	end


Part55_Text_0300:
	.string "刚才吓了一跳！已经接到孩子了，接下\n来我们一起逛。$"

Part55_Text_0301:
	.string "总算抽出时间来看看他。烧已经退了，\n今晚就给他煮点清淡的。$"

Part55_Text_0302:
	.string "给家里打过电话以后，终于踏实多了。\n今天和伊布一起逛原野区！$"

Part55_Text_0303:
	.string "欢迎参观。公开区域可以自由走动，工\n作区需要职员授权。$"

Part55_Text_0304:
	.string "又来了？今天交流厅还有公开活动。里\n面的工作区仍然需要授权。$"

Part55_Text_0305:
	.string "你也好奇电梯下层忙什么？我也想看看\n，不过先把门口看好。没有授权可不能\p自己进去。$"

Part55_Text_0306:
	.string "听说你取得第七枚徽章了。恭喜！园区\n的公开服务照常开放。$"

Part55_Text_0307:
	.string "第七枚徽章到手了？不错！旁边的进阶\n训练也已经开放。$"

Part55_Text_0308:
	.string "又见面了！听说你在绿岭赢了。今天想\n吃点什么？$"

Part55_Text_0309:
	.string "上次并肩站着，今天又成了对手……感觉\n还真不一样。可我也得认真完成工作。$"

Part55_Text_0310:
	.string "刚才宇宙中心好吵……现在还能等火箭吗\n？$"

Part55_Text_0311:
	.string "已经没事了。今天先回家，等工作人员\n确认好了，再来看。$"

Part55_Text_0312:
	.string "合作观测的数据还要重新核对。宇宙中\n心的工作人员也辛苦了。$"

Part55_Text_0313:
	.string "呼……呼……$"

Part55_ShuffleAside:
	walk_in_place_faster_left
	step_end

Part55_DollPosition::
	setobjectxyperm LOCALID_PART5_BANETTITE, 10, 25
	return

Part55_ExitRescueReward::
	msgbox Part55_Text_0240, MSGBOX_DEFAULT
	giveitem ITEM_HOUNDOOMINITE, 1
	goto_if_eq VAR_RESULT, FALSE, Part55_BagFull
	setvar VAR_PART55_HOUNDOUR_RESCUE, 3
	goto Part55_ExitRescueDepart

Part55_RescueRoomActors::
	clearflag FLAG_TEMP_1A
	call_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, Part55_RescueRoomAfterGroudon
	call_if_set FLAG_PART55_RESCUED_MAGMA_LEFT, Part55_HideRescueRoomActors
	end

Part55_RescueRoomAfterGroudon::
	call_if_ge VAR_PART55_HOUNDOUR_RESCUE, 2, Part55_HideRescueRoomActors
	return

Part55_HideRescueRoomActors::
	setflag FLAG_TEMP_1A
	return
Part55_WhiteRockRecord::
	goto_if_eq VAR_PART55_STAR_CALIBRATION, 31, Part55_WhiteRockRecord_End
	setvar VAR_0x8004, VAR_PART55_STAR_CALIBRATION, FALSE
	setvar VAR_0x8005, 2
	special Part55_RecordPoint
	return


Part55_WhiteRockRecord_End::
	return


Part55_Text_0314:
	.string "{PLAYER}感受到了一股温暖而神秘的力\n量。\p白色岩石的表面，出现了一点微弱的星\n光。$"
