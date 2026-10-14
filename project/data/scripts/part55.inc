@ PART5.5 additions. See docs/story/PART5_5_DRAFT.md; remains DRAFT.
Part55_BagFull::
	msgbox Part55_Text_0001, MSGBOX_DEFAULT
	releaseall
	end


Part55_Text_0001:
	.string "背包已经满了。腾出空位以后，\n再来找我吧。$"
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
	.string "再停五分钟就发车。刚卸完的箱子\n还在晃，我得再捆紧一点。$"

Part55_Text_0003:
	.string "午饭以后还要再跑两车。\n先让我喝口水，嗓子都冒烟了。$"

Part55_Text_0004:
	.string "运往水静市的货一天比一天多。\n卸货口那么多，我都快记混了！$"

Part55_Text_0005:
	.string "航运公告：客船和货船均按时刻表\n运行。检票前请确认目的地。$"

Part55_Text_0006:
	.string "航运公告：部分航线暂时停运。\n恢复时间请留意港口后续通知。$"

Part55_Text_0007:
	.string "航运公告：各航线正在逐步恢复。\n新的时刻表将在此处公布。$"

Part55_Text_0008:
	.string "我答应孩子今天带他坐船，时刻表\n已经核对了三遍。这回总不会错吧。$"

Part55_Text_0009:
	.string "孩子每隔五分钟就问一次船什么时候\n开。只好等港口发新通知了。$"

Part55_Text_0010:
	.string "航线恢复了，总算能重新安排出游！\n这回我得先把船票收好。$"

Part55_Text_0011:
	.string "上了船我要坐靠窗的位置！\n还要数一数路上有几只长翅鸥！$"

Part55_Text_0012:
	.string "爸爸说今天船不开了。我带的零食\n都快被我吃光啦。$"

Part55_Text_0013:
	.string "终于能坐船啦！这次我把零食也\n补满了，一口都不会提前偷吃！$"

Part55_Text_0014:
	.string "长椅下面落着一张运输清单。\n上面印着“水静港口”的字样。$"

Part55_Text_0015:
	.string "长椅下没有别的东西了。那张清单\n该交给水静港口的工作人员。$"

Part55_Text_0016:
	.string "这是我的运输清单！刚才一阵海风\n吹过来，转眼就不见了。\p真是帮大忙了，这个请你收下。$"

Part55_Text_0017:
	.string "糟糕，我的运输清单被风吹跑了！\n好像是往海滨大道那边飞的。\p要是你看到了，能帮我捡回来吗？$"

Part55_Text_0018:
	.string "今天这批货里有合众来的训练用品，\n也有城都的日用品。\p清单找回来了，我可得一箱一箱\n仔细点清楚。$"

Part55_Text_0019:
	.string "糟了，我拿错行李了！这只箱子\n是码头那位戴帽子的旅客的。\p能请你帮我拿去港口换回来吗？\n我的那只是蓝色的。$"

Part55_Text_0020:
	.string "那位戴帽子的旅客应该还在港口。\n我的箱子是蓝色的，拜托了！$"

Part55_Text_0021:
	.string "没错，就是这只蓝箱子！\n实在太感谢了，这个请你收下。$"

Part55_Text_0022:
	.string "以后出门，我一定先看清楚\n行李上的名牌再拿。$"

Part55_Text_0023:
	.string "原来我的箱子被拿到旅馆去了！\n我也正为找不到它发愁呢。\p来，这只蓝色的给你，请帮我\n转交给旅馆里的那位旅客。$"

Part55_Text_0024:
	.string "我们俩的箱子长得一模一样。\n回去以后我得绑条缎带做记号。$"

Part55_Text_0025:
	.string "房间里放着一份包好的纪念品。\n包装纸上写着“海边买的”。$"

Part55_Text_0026:
	.string "这份纪念品的主人，也许还在\n海滨大道一带。$"

Part55_Text_0027:
	.string "这是我给家人买的礼物！我竟然把它\n忘在旅馆房间里了。\p幸好还没坐船离开。这些请收下，\n就当是谢礼吧！$"

Part55_Text_0028:
	.string "坏了，我给家人买的纪念品好像\n落在旅馆的房间里了。\p要是你去旅馆二楼，能帮我\n看一眼吗？$"

Part55_Text_0029:
	.string "回家以后，我要把水静海边的\n见闻一件一件讲给家人听。$"

Part55_Text_0030:
	.string "这是我第一次一个人旅行。伊布睡得\n可香了，我倒有点想家。\p等会儿还是给家里打个电话吧。$"

Part55_Text_0031:
	.string "刚给家里打过电话，妈妈叮嘱我\n多拍几张照片。\p明天我想带伊布去原野区看看！$"

Part55_Text_0032:
	.string "去原野区的行李都收拾好了。\n伊布的点心当然也带上啦！$"

Part55_Text_0033:
	.string "妈妈说要去看装饰品，可我忘了\n是在哪一层了。\p装饰品好像在很上面的楼层。\n你能帮我去找找妈妈吗？$"

Part55_Text_0034:
	.string "妈妈回来啦！谢谢你帮我找到她。\n妈妈说，这个可以送给你。$"

Part55_Text_0035:
	.string "这次我要一直牵着妈妈的手，\n再也不乱跑了。$"

Part55_Text_0036:
	.string "孩子在二楼等我？谢谢你特地\n跑上来告诉我，我这就下去！$"

Part55_Text_0037:
	.string "孩子一个人走丢，可把我吓坏了。\n以后逛商店，我一定得看紧点。$"

Part55_Text_0038:
	.string "我想给家里挑件装饰品。\n咦，孩子刚才还跟在我身后呢？$"

Part55_Text_0039:
	.string "这块布是海滨大道的设计师订的。\n你要是顺路，能帮我送过去吗？$"

Part55_Text_0040:
	.string "这块布料要交给海滨大道上的\n设计师。$"

Part55_Text_0041:
	.string "我订的布料到了！卷卷耳从刚才起\n就一直盯着上面的缎带。\p这块石头是我们旅行时找到的，\n就当作谢礼送给你吧。$"

Part55_Text_0042:
	.string "我在百货商店五楼订了一块布料，\n可一直没空过去拿。\p你要是路过，能帮我带过来吗？$"

Part55_Text_0043:
	.string "卷卷耳又把布料叠得整整齐齐。\n它做事比我这个设计师还细心。$"

Part55_Text_0044:
	.string "想让宝可梦学会三重攻击吗？\n我先帮你看看它能不能学。$"

Part55_Text_0045:
	.string "请选择要学习的宝可梦。$"

Part55_Text_0046:
	.string "想再学的时候，随时来找我。\n三重攻击用好了可是很华丽的！$"

Part55_Text_0047:
	.string "双打的时候，帮伙伴一把可是很\n关键的。要学习帮助吗？$"

Part55_Text_0048:
	.string "请选择要学习的宝可梦。$"

Part55_Text_0049:
	.string "需要的时候，随时来找我。\n双打里互相帮忙最重要了。$"

Part55_Text_0050:
	.string "第一份薪水到账啦！想给家里买点\n东西，还想添些训练用品。\p先列张清单，免得一冲动全花光。$"

Part55_Text_0051:
	.string "先看看价格再说吧。你上个月不是\n还说要攒路费吗？$"

Part55_Text_0052:
	.string "买回来才发现我的宝可梦根本用不上。\n下次我一定先看清说明再付钱。$"

Part55_Text_0053:
	.string "挑道具得看伙伴擅长什么。\n名字听起来厉害，可不一定合适。$"

Part55_Text_0054:
	.string "我在这儿坐了一下午了。外面太热，\n这里凉快，还能慢慢看画。$"

Part55_Text_0055:
	.string "这次拿了第三名！比上次进步了\n一名呢。\p回去得给伙伴多加一份点心。$"

Part55_Text_0056:
	.string "先吃饭，再拍照。刚下台的时候，\n它比我还饿呢。$"

Part55_Text_0057:
	.string "舞台上的灯光很漂亮，可后台的\n电线也得一根根检查才行。$"

Part55_Text_0058:
	.string "今天的饭团还热乎着呢！散步之前\n先来一个垫垫肚子吧。$"

Part55_Text_0059:
	.string "这排明信片拍的全是丰缘的海岸。\n寄回家也很方便哦。$"

Part55_Text_0060:
	.string "出远门之前，补给一定要带够。\n训练家常用的东西这里都有。$"
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
	.string "门口的长椅下掉着一张员工证。\n照片上的人穿着工作服。$"

Part55_Text_0062:
	.string "这张员工证应该交给总部一楼的\n失主。$"

Part55_Text_0063:
	.string "这是我的员工证！早上找了半天，\n差点就赶不上打卡了。\p真是谢谢你，这个请收下。$"

Part55_Text_0064:
	.string "我的员工证不见了，保安让我先在\n这里登记。\p早上我只在园区门口的长椅上\n坐过一会儿，会不会掉在那里了？$"

Part55_Text_0065:
	.string "证件总算找回来了。下次我就把它\n收进包里，不再挂在外面了。$"

Part55_Text_0066:
	.string "室友发烧了，可我得守着这组数据，\n走不开。\p能帮我把这包药送到公寓一楼吗？$"

Part55_Text_0067:
	.string "我室友就在公寓一楼等药。\n谢谢你帮忙跑这一趟。$"

Part55_Text_0068:
	.string "他还记得给我买药啊。谢谢你特地\n跑一趟，我感觉好多了。\p这些伤药就留给你的伙伴吧。$"

Part55_Text_0069:
	.string "今天有点发烧，只好请假在家休息。\n室友说会帮我买药回来。$"

Part55_Text_0070:
	.string "烧已经退了，室友也来看过我了。\n等再好一点，就去食堂吃饭。$"

Part55_Text_0071:
	.string "卸货处放着一个备用电源模块。\n标签上写着“园区电力技师收”。$"

Part55_Text_0072:
	.string "这个模块要交给阿尔刻总部二楼的\n电力技师。$"

Part55_Text_0073:
	.string "备用模块送来了！电龙，帮我接一下\n线路。好，仪器恢复正常了！\p这颗石头是谢礼，请收下吧。$"

Part55_Text_0074:
	.string "备用模块迟迟没送到，现在只能靠\n电龙给仪器供电。\p模块应该还留在121号道路的\n卸货处，能帮我拿过来吗？$"

Part55_Text_0075:
	.string "电龙总算能歇一会儿了。下班后\n我得给它多准备点好吃的。$"

Part55_Text_0076:
	.string "第一天上班，光密码就要记四个。\n午休的时候得再抄一遍。$"

Part55_Text_0077:
	.string "今天总算没走错门！就是会议室和\n档案室，我又记反了。$"

Part55_Text_0078:
	.string "忙了一整周，连今天星期几都忘了。\n只希望晚饭还能吃到咖喱。$"

Part55_Text_0079:
	.string "今天供应咖喱！过了饭点也会\n给值班的同事留一份。$"

Part55_Text_0080:
	.string "等这组数据跑完我就去吃饭。\n哎，怎么又自动开始下一组了！$"

Part55_Text_0081:
	.string "想吃点辣的，可室友提醒我今晚\n还要值班。只好点普通咖喱了。$"

Part55_Text_0082:
	.string "外卖只送到一楼。楼上员工区的\n住客，得自己下来取。$"

Part55_Text_0083:
	.string "这里房租可不便宜，好在离宝可梦\n中心很近。我的伙伴常去做检查。$"

Part55_Text_0084:
	.string "这一带住着挺安静的。偶尔有人加班\n到半夜，门口的灯会一直亮着。$"

Part55_Text_0085:
	.string "我是来这里交流的研究员。等项目\n结束，还要回自己的实验室。$"

Part55_Text_0086:
	.string "我的伙伴是在别的地区认识的。\n它对丰缘的树果特别感兴趣。$"

Part55_Text_0087:
	.string "生活区公告：训练场每周三维护。\n外卖请到一楼领取。\p另外，请勿把实验用宝可梦带进厨房。$"

Part55_Text_0088:
	.string "自动售货机旁贴着一张字条：\n零钱不够时，请到餐饮柜台兑换。$"

Part55_Text_0089:
	.string "墙上挂着研究地点分布图。许多地区\n都有标记，丰缘沿海尤其密集。$"

Part55_Text_0090:
	.string "电梯面板：下层设施仅限授权员工\n使用。目前没有可选的访客楼层。$"

Part55_Text_0091:
	.string "环境系统展示：密闭实验箱里的温度\n和湿度正在缓慢调整。\p旁边的说明写着：仅限室内测试。$"

Part55_Text_0092:
	.string "生命体征记录仪：屏幕上显示着呼吸、\n脉搏和体表温度。\p记录上没有写任何受试者的姓名。$"

Part55_Text_0093:
	.string "古代资料数字化装置：拓片上的纹路\n正被一行一行地录入。$"

Part55_Text_0094:
	.string "箱子上的标签湿透了，字迹看不清。\n里面放着几只装着水样的小瓶。$"

Part55_Text_0095:
	.string "拿起了箱子。请根据里面的东西，\n送到总部二楼对应部门的收件窗。$"

Part55_Text_0096:
	.string "箱子里是低温保存的培养皿。封条\n提醒：不要在室外停留太久。$"

Part55_Text_0097:
	.string "拿起了箱子。请根据里面的东西，\n送到总部二楼对应部门的收件窗。$"

Part55_Text_0098:
	.string "箱子里装着几卷拓片，纸上能看到\n古老的纹路。$"

Part55_Text_0099:
	.string "拿起了箱子。请根据里面的东西，\n送到总部二楼对应部门的收件窗。$"

Part55_Text_0100:
	.string "手上已经抱着一个箱子了。先把它\n送到，再来拿下一箱吧。$"

Part55_Text_0101:
	.string "这一箱已经送过了。$"

Part55_Text_0102:
	.string "环境研究收件窗$"

Part55_Text_0103:
	.string "内容核对无误。这箱资料已签收。$"

Part55_Text_0104:
	.string "生命研究收件窗$"

Part55_Text_0105:
	.string "内容核对无误。这箱资料已签收。$"

Part55_Text_0106:
	.string "古代资料收件窗$"

Part55_Text_0107:
	.string "内容核对无误。这箱资料已签收。$"

Part55_Text_0108:
	.string "这箱东西不归这个部门管。先看看\n里面装的是什么，再送对地方吧。$"

Part55_Text_0109:
	.string "目前没有需要签收的箱子。$"

Part55_Text_0110:
	.string "三箱都签收了！湿标签的麻烦总算\n解决了。辛苦你来回跑了这么多趟。\p这个请收下吧。$"

Part55_Text_0111:
	.string "这三箱货的标签全都受潮了。请你\n打开看看里面装的是什么，\p再送到总部二楼对应部门的收件窗。\n千万别照着外面的旧标签送！\p水样归环境研究，培养皿归生命研究，\n拓片归古代资料。$"

Part55_Text_0112:
	.string "新标签都换好了。这次我还特意\n套上了防水袋。$"

Part55_Text_0113:
	.string "能帮我排查一下公共网络吗？\n请按顺序检查三处终端：\p先是总部一楼，然后是交流厅，\n最后是总部二楼。$"

Part55_Text_0114:
	.string "检查顺序是总部一楼、交流厅、\n总部二楼。线路不能跳着测哦。$"

Part55_Text_0115:
	.string "线路恢复了！多边兽也从终端里\n钻出来了。\p它好像很喜欢你。愿意带它\n一起去旅行吗？$"

Part55_Text_0116:
	.string "多边兽加入了队伍！\n请好好照顾它。$"

Part55_Text_0117:
	.string "多边兽习惯旅行了吗？\n公共网络现在运行得很顺畅。$"

Part55_Text_0118:
	.string "你的队伍已经满六只了。空出一个\n位置再来接它吧，我在这里等你。$"

Part55_Text_0119:
	.string "终端检测完成。请继续检查下一处：\n交流厅的终端。$"

Part55_Text_0120:
	.string "现在还不需要操作这台终端。\n请按程序员说的顺序检查。$"

Part55_Text_0121:
	.string "终端检测完成。最后请检查总部\n二楼的终端。$"

Part55_Text_0122:
	.string "现在还不需要操作这台终端。\n请按程序员说的顺序检查。$"

Part55_Text_0123:
	.string "最后一处线路恢复正常了。多边兽\n从终端旁边探出了头！$"

Part55_Text_0124:
	.string "现在还不需要操作这台终端。\n请按程序员说的顺序检查。$"

Part55_Text_0125:
	.string "你拿到第七枚徽章了？这里正好有\n一场进阶训练。\p对手会使用Mega进化。要挑战看看吗？$"

Part55_Text_0126:
	.string "好，准备好了就开始吧！$"

Part55_Text_0127:
	.string "恰雷姆配合得很好，但你的判断\n更快一步。$"

Part55_Text_0128:
	.string "训练完成！这是特性膏药，能让伙伴\n尝试发挥隐藏特性。请慎重使用。$"

Part55_Text_0129:
	.string "进阶训练要拿到第七枚徽章以后\n才能参加。普通公开训练照常开放。$"

Part55_Text_0130:
	.string "这次的训练记录已经存档了。\n谢谢你认真参加！$"
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
	special Part6_CountAnomaly
	buffernumberstring STR_VAR_1, VAR_RESULT
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
	special StoryRefreshPickupMarkers
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
	.string "牙牙紧紧盯着你，牙尖在阳光下\n闪了一下！$"

Part55_Text_0132:
	.string "洞口附近那只牙牙特别爱咬石头。\n它的牙亮闪闪的，远远就能看见。$"

Part55_Text_0133:
	.string "是它呀！下次它想磨牙的时候，\n记得给它找块结实点的石头。$"

Part55_Text_0134:
	.string "最近没再见到那只牙牙了。\n石头上的牙印倒是还留着。$"

Part55_Text_0135:
	.string "石头上留着一排深深的牙印。$"

Part55_Text_0136:
	.string "牙牙认出了这块石头，得意地\n摆了摆尾巴。$"

Part55_Text_0137:
	.string "一块洁白的岩石，被海风磨得很光滑。$"

Part55_Text_0138:
	.string "洁白的岩石静静地映着海边的\n阳光。$"

Part55_Text_0139:
	.string "刚才那块石头好像闪了一下！\n爸爸说那只是浪花的反光。$"

Part55_Text_0140:
	.string "白石头被太阳一照就亮。她一看见\n反光，就非要拉我过来看。$"

Part55_Text_0141:
	.string "咦，你包里刚才是不是闪了一下？\n大概是我看错了吧。$"

Part55_Text_0142:
	.string "外面阳光太强了，刚进门的时候\n眼睛都花了。$"

Part55_Text_0143:
	.string "我在研究超能力宝可梦，也喜欢\n和训练家交流。来一场对战吗？$"

Part55_Text_0144:
	.string "请多指教！$"

Part55_Text_0145:
	.string "这场对战的数据很有参考价值。$"

Part55_Text_0146:
	.string "谢谢你。这颗石头交给你保管，\n说不定能和你的伙伴派上用场。$"

Part55_Text_0147:
	.string "我得先整理刚才的记录。下次\n再听你聊聊旅途上的事吧。$"

Part55_Text_0148:
	.string "小枫和小南的配合非常默契。\n先去绿岭道馆挑战他们吧，\p拿到徽章以后，我们再来一场。$"

Part55_Text_0149:
	.string "在海上跑一趟挺累的吧？\n让你的伙伴休息一下。$"

Part55_Text_0150:
	.string "伙伴们都恢复精神了！\n接下来也要留意海流哦。$"

Part55_Text_0151:
	.string "最近有几片海域的水下读数很奇怪。\p等你学会了潜水，能帮我去看看吗？\n一共三个地方。$"

Part55_Text_0152:
	.string "太好了！地点我跟你说清楚。\p第一处在126号水路，琉璃市火山口\n东北边的深水区。\p第二处在127号水路西南的深水带。\p第三处在128号水路西边，被一圈浅滩\n围起来的那片深色海水。\p三处的海底都有我们放下的观测装置，\n顶上亮着灯，靠近查看就能读到数据。$"

Part55_Text_0153:
	.string "水下观测记录：{STR_VAR_1}/3。\p126号火山口东北、127号西南深水带、\n128号浅滩圈的中央，都要潜下去看。$"

Part55_Text_0154:
	.string "小球飞鱼绕着歪掉的浮标转了一圈，\n然后游开了。你把浮标扶正了。$"

Part55_Text_0155:
	.string "浮标已经扶正，水面上的标记\n也清楚多了。$"

Part55_Text_0156:
	.string "浮标是你扶正的？太感谢了，\n那是我们标记采样位置用的。$"

Part55_Text_0157:
	.string "附近有个浮标歪掉了，小球飞鱼\n老围着它转。能帮我去扶正吗？$"

Part55_Text_0158:
	.string "今天的采样位置都确认好了。\n终于可以收工啦！$"

Part55_Text_0159:
	.string "深处的冰层里露出一块颜色奇怪的\n石头。你小心地把它取了出来。\p先拿给洞穴入口的老人看看吧。$"

Part55_Text_0160:
	.string "冰层里封着一块奇怪的石头。冰太\n厚了，暂时取不出来。\p入口那位会做贝壳之铃的老人，\n也许知道该怎么取。$"

Part55_Text_0161:
	.string "冰层上留着取出石头的痕迹。$"

Part55_Text_0162:
	.string "这层冰可真结实。我慢慢敲开看看。\p好了！里面的石头完好无损，是冰鬼\n护进化石。你留着吧！$"

Part55_Text_0163:
	.string "记录下冰晶的形状和温度。\n旁边能看到细小的裂纹。$"

Part55_Text_0164:
	.string "记录下冰晶的形状和温度。\n这块冰晶比别处的更透明。$"

Part55_Text_0165:
	.string "记录下冰晶的形状和温度。\n表面结着一层薄薄的霜。$"

Part55_Text_0166:
	.string "三处冰晶都记录好了！雪笠怪\n也很喜欢这里的温度呢。\p这颗石头是谢礼，请收下。$"

Part55_Text_0167:
	.string "我正在观察这间冰室。能帮我记录\n三处冰晶的情况吗？\p冰晶就在这个房间里。我的雪笠怪\n不怕冷，我可得多穿两件外套。$"

Part55_Text_0168:
	.string "冰晶的记录都收好了。等下次\n低潮时，再来对照看看。$"
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
	.string "草丛边掉着一本巡查记录。封面上\n写着原野区护林员的名字。$"

Part55_Text_0170:
	.string "这本巡查记录要交给原野区入口的\n护林员。$"

Part55_Text_0171:
	.string "我的巡查记录找回来了！我还以为\n得把整条路线重走一遍。\p这个送给你，谢谢啦！$"

Part55_Text_0172:
	.string "我巡查的时候把记录本弄丢了。\n大概是掉在原野区西北边的草丛里。\p要是看到了，能帮我带回来吗？$"

Part55_Text_0173:
	.string "巡查路线都记好了。下回我得换个\n结实点的夹子。$"

Part55_Text_0174:
	.string "树枝上有采食的痕迹，但没看到\n蜂巢。把这里记为调查点。$"

Part55_Text_0175:
	.string "树皮上有被啃过的痕迹，附近没有\n蜂巢。把这里记为调查点。$"

Part55_Text_0176:
	.string "这棵树上有一个蜂巢！大针蜂从\n树叶间探出了头。\p要靠近观察吗？这里仍然适用\n原野区的捕获规则。$"

Part55_Text_0177:
	.string "蜂巢的位置已经记下了。这里离\n游客常走的路很远。$"

Part55_Text_0178:
	.string "树叶深处传来沙沙声。先去看看\n另外两个调查点，再回来确认吧。$"

Part55_Text_0179:
	.string "你找到蜂巢了，而且离游客路线很远。\n那就不必去打扰它们了。\p谢谢你帮忙记录，这个送给你。$"

Part55_Text_0180:
	.string "原野区南部的树林里有三个调查点。\n能帮我去看看吗？\p我想确认大针蜂的巢，离游客走的\n路线够不够远。$"

Part55_Text_0181:
	.string "那片树林就先保持原样吧。\n游客也不必往蜂巢那边走。$"

Part55_Text_0182:
	.string "袋兽、吉利蛋和肯泰罗你都登记了？\n观察得挺仔细嘛。\p要不要和我来一场进阶对战？$"

Part55_Text_0183:
	.string "伙伴们，上场吧！$"

Part55_Text_0184:
	.string "你不光会观察，配合也很默契。$"

Part55_Text_0185:
	.string "原野区里有袋兽、吉利蛋和肯泰罗。\n等图鉴里登记了这三种，\p再来找我进行进阶对战吧。$"

Part55_Text_0186:
	.string "比赛结束！这些奖品归你了。$"

Part55_Text_0187:
	.string "观察宝可梦的时候，也别忘了看看\n它们生活的地方。$"
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
	.string "老师让我观察画里的宝可梦。画家\n连尾巴上的花纹都画得好仔细。$"

Part55_Text_0189:
	.string "画里的宝可梦是你的吧？我刚才\n还在临摹它的姿势呢！$"

Part55_Text_0190:
	.string "伴奏就交给爆音怪啦！放心，它练过\n控制音量，不会把港口的船吓跑。$"

Part55_Text_0191:
	.string "你拿到第七枚徽章了？真厉害！\n下一首就献给走过这么多路的你！$"

Part55_Text_0192:
	.string "我和家人说好在港口碰头，结果\n不知怎么走进了百货商店。\p谢谢你给我指路，这回我记住啦。$"

Part55_Text_0193:
	.string "沿着街道一直往港口走，\n这回不会再走错了。$"

Part55_Text_0194:
	.string "总算到港口了！家里人一会儿就到。\n刚才真是麻烦你指路了。$"

Part55_Text_0195:
	.string "石头上有细细的划痕，旁边散落着\n饰品上掉下来的金属屑。$"

Part55_Text_0196:
	.string "这里残留着少许宝石粉末。看样子，\n有什么东西把石头咬碎过。$"

Part55_Text_0197:
	.string "勾魂眼抱着一块被咬过的饰石，\n从岩缝里钻了出来！\p要靠近它吗？$"

Part55_Text_0198:
	.string "勾魂眼退回了岩缝，留下了那块\n被咬过的饰石。$"

Part55_Text_0199:
	.string "岩缝深处好像有什么东西。\n先看看附近的划痕和粉末吧。$"

Part55_Text_0200:
	.string "岩缝里已经没有那块饰石了。$"

Part55_Text_0201:
	.string "我的饰石怎么变成这样了！原来是\n被勾魂眼拿走了。\p算了，能找回来就好。这颗石头\n送给你，当作谢礼。$"

Part55_Text_0202:
	.string "我刚把饰石摆出来，就少了一块！\p水静市的海边好像有划痕和宝石粉末，\n能帮我去看看吗？$"

Part55_Text_0203:
	.string "宝石果然不能随便摆在海边。\n以后我得把盒子盖好。$"

Part55_Text_0204:
	.string "阿尔刻与宇宙中心联合观测联络处：\n双方在此交换大气观测资料。\p各项目由各自的研究团队负责。$"

Part55_Text_0205:
	.string "观星仪刚装好，需要校准。能帮我\n去对照三个记录点吗？\p分别在海边、白色岩石旁，\n还有宇宙中心的大门外。$"

Part55_Text_0206:
	.string "三处记录都对上了，仪器校准完毕！\n谢谢你来回跑，这个请收下。$"

Part55_Text_0207:
	.string "三个记录点在海边、白色岩石旁和\n宇宙中心门外，各有一个小标记。$"

Part55_Text_0208:
	.string "观星仪已经校准好了。今晚我再\n试着多记录几颗星星。$"

Part55_Text_0209:
	.string "对照记录点的方位，写下了当前的\n观测值。$"

Part55_Text_0210:
	.string "一个用来对照方位的小标记。\n现在不需要记录。$"

Part55_Text_0211:
	.string "对照记录点的方位，写下了当前的\n观测值。$"

Part55_Text_0212:
	.string "一个用来对照方位的小标记。\n现在不需要记录。$"

Part55_Text_0213:
	.string "对照记录点的方位，写下了当前的\n观测值。$"

Part55_Text_0214:
	.string "一个用来对照方位的小标记。\n现在不需要记录。$"

Part55_Text_0215:
	.string "大比鸟飞了一整天，得让它歇歇了。\n可这封加急信今天就得送到。\p收件地点是绿岭市宇宙中心的接待处，\n能帮我跑一趟吗？$"

Part55_Text_0216:
	.string "把信交给绿岭市宇宙中心的接待处\n以后，请把签收回执带回来给我。$"

Part55_Text_0217:
	.string "回执收到了！大比鸟也休息好了。\n这颗石头请你收下，\p就当是替它跑这一趟的谢礼。$"

Part55_Text_0218:
	.string "今天的急件全都送到了。谢谢你，\n大比鸟也精神多了。$"

Part55_Text_0219:
	.string "是今天的加急信！我签收一下。\n请把这张回执交给邮递员。$"

Part55_Text_0220:
	.string "接待处也负责登记邮件。\n有加急信的话，直接交给我就行。$"

Part55_Text_0221:
	.string "我在这儿住了十二天，就为了看一次\n火箭发射。每天都来问倒计时。$"

Part55_Text_0222:
	.string "上次那件事可把我吓坏了。还好\n宇宙中心能继续工作。$"

Part55_Text_0223:
	.string "今天终于能准时下班了。希望到家\n的时候孩子还没睡。$"

Part55_Text_0224:
	.string "出了那件事以后，要重新核对的\n记录更多了。今晚还是早点睡吧。$"

Part55_Text_0225:
	.string "说好一起看星星，结果他先睡着了。\n我得给他把外套盖好。$"

Part55_Text_0226:
	.string "今晚真安静。终于能好好看一会儿\n星星了。$"

Part55_Text_0227:
	.string "我年轻时跑船，全靠星星认方向。\n现在年轻人的仪器可方便多了。$"

Part55_Text_0228:
	.string "海边总算恢复平静了。\n看星星的时候也安心些。$"

Part55_Text_0229:
	.string "我是来看海边地层的。这里岩石的\n颜色，和我家乡的很不一样。$"

Part55_Text_0230:
	.string "观测记录还在，旅行也能继续了。\n等天气稳定，我再去海边看看。$"
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
	closemessage
	setvar VAR_0x8000, LOCALID_PART55_RescuedMagmaExit
	setvar VAR_0x8001, 6
	call Story_WalkAwayAndRemove
	setvar VAR_0x8000, LOCALID_PART55_RescuedHoundourExit
	setvar VAR_0x8001, 6
	call Story_WalkAwayAndRemove
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
	.string "排水通道入口。工地师傅正在里面\n检查。要进去吗？$"

Part55_Text_0232:
	.string "龙头地鼠挡在堵住的排水口前，\n用爪子拍了拍地面！$"

Part55_Text_0233:
	.string "龙头地鼠离开了。清开堵塞的碎石\n以后，排水恢复了。$"

Part55_Text_0234:
	.string "水总算流下去了！大钢蛇今天也能\n收工了。\p这颗石头是谢礼，你收下吧。$"

Part55_Text_0235:
	.string "小排水沟堵住了，还有只龙头地鼠\n守在排水口前不肯走。\p通道入口在物流站侧门，大钢蛇也在\n里面帮忙。能帮我去看看吗？$"

Part55_Text_0236:
	.string "排水口都检查过了。下次施工前，\n得先把挡板围好。$"

Part55_Text_0237:
	.string "侧面的小通道里传来戴鲁比的叫声。\n要进去看看吗？$"

Part55_Text_0238:
	.string "扳动了通风装置旁的开关。挡住通道\n的岩板退开了，热气也散了一些。$"

Part55_Text_0239:
	.string "开关已经打开，通道可以通过了。$"

Part55_Text_0240:
	.string "终于能出去了！我们在里面困了太久，\n戴鲁比都热坏了。\p今天就不跟你打了。这颗石头给你，\n这次算我欠你的，我会记着。$"

Part55_Text_0241:
	.string "通道被挡住了，我们出不去！\n能不能先把旁边的通风开关打开？$"

Part55_Text_0242:
	.string "戴鲁比好多了。出口已经打开，\n我们歇一会儿就走。$"

Part55_Text_0243:
	.string "刚才的事，算我欠你一次。里面太\n危险了，你也快离开吧！\p戴鲁比，我们走。$"
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
	closemessage
	setvar VAR_0x8000, LOCALID_PART55_TeamupAquaA
	setvar VAR_0x8001, 7
	call Story_WalkAwayAndRemove
	setvar VAR_0x8000, LOCALID_PART55_TeamupAquaB
	setvar VAR_0x8001, 7
	call Story_WalkAwayAndRemove
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
	cant_see_if_trainerflag_set TRAINER_GRUNT_MAGMA_HIDEOUT_14
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
	cant_see_if_trainerflag_set TRAINER_GRUNT_MAGMA_HIDEOUT_4
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


@ 战斗胜利后的入口（由 MagmaHideout_2F_1R_EventScript_Grunt4 的 trainerbattle_single
@ 第 4 参跳入）。战斗结束时玩家未处于脚本锁内，所以这里必须自带 lock/release 配对。
Part55_MagmaBento_Defeated::
	lock
	msgbox Part55_Text_0256, MSGBOX_DEFAULT
	release
	end


Part55_MagmaGloves::
	cant_see_if_trainerflag_set TRAINER_GRUNT_MAGMA_HIDEOUT_5
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


@ 同上，手套小兵战斗胜利后的入口（MagmaHideout_2F_1R_EventScript_Grunt5 的第 4 参）。
Part55_MagmaGloves_Defeated::
	lock
	msgbox Part55_Text_0258, MSGBOX_DEFAULT
	release
	end


Part55_Seasick::
	cant_see_if_trainerflag_set TRAINER_GRUNT_AQUA_HIDEOUT_2
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
	.string "又是你！嘘，小声点，我正在执行\n正式的观察任务呢。\p糟了，被发现了！我们被他们包围了！\p什么，为什么把你也算进来？\n别问了，先一起应付过去再说！$"

Part55_Text_0245:
	.string "可恶，这两个人居然配合得这么好！$"

Part55_Text_0246:
	.string "先撤！换个地方再调查！$"

Part55_Text_0247:
	.string "那边是谁？别躲了，我们都看见了！$"

Part55_Text_0248:
	.string "你们两个，别在那边嘀嘀咕咕的！$"

Part55_Text_0249:
	.string "刚才只是临时合作！下次执行任务，\n我还是会拦住你的。\p我可没说下次一定会输哦！\n好了，我要继续去调查了。$"

Part55_Text_0250:
	.string "我还在调查呢。刚才合作的事，\n你可别到处乱说！$"

Part55_Text_0251:
	.string "送神山那次只是临时合作。今天\n我们是对手，胖丁也准备好了！$"

Part55_Text_0252:
	.string "新人：还没开始打呢，不准先和\n胖丁交朋友！$"

Part55_Text_0253:
	.string "新人：胖丁好像挺喜欢你的。\n我、我才没说过这种话！$"

Part55_Text_0254:
	.string "一开始我还笑她只带一只胖丁。\n后来跟她切磋了一场，结果嘛，\p还是不提了。$"

Part55_Text_0255:
	.string "刚把便当放下就有人来了。等一下，\n你不是我们的人！$"

Part55_Text_0256:
	.string "便当都凉了。今天怎么什么倒霉\n事都凑到一块儿了。$"

Part55_Text_0257:
	.string "手套又磨破了一双！喂，你是谁？\n谁让你进来的！$"

Part55_Text_0258:
	.string "我还得去领新手套。挖石头这活儿，\n可比说起来累多了。$"

Part55_Text_0259:
	.string "坐船真是太难受了，头还在晕。\n等等，你怎么跑到这里来了！$"

Part55_Text_0260:
	.string "让我先喘口气。就不能等浪小一点\n再出发吗？$"

Part55_Text_0261:
	.string "陪伴了家人二十年的大狼犬。\n你总能听见我们回家的脚步声。$"

Part55_Text_0262:
	.string "旧精灵球旁放着一封信：\n“谢谢你，每次都等我一起回家。”$"

Part55_Text_0263:
	.string "墓碑前放着一小包点心，纸条上写着：\n“你最喜欢的，我又带来了。”$"

Part55_Text_0264:
	.string "留言簿上写满了简短的祝福。\n要写下“谢谢你”吗？$"

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
	.string "怨影娃娃往旁边让了让。它身后\n放着一只旧布偶。$"

Part55_Text_0274:
	.string "我把旧布偶落在山顶的墓碑旁边了。\n奶奶说别着急，可我还是好担心。$"

Part55_Text_0275:
	.string "布偶找到了！原来是怨影娃娃一直\n帮忙守着。\p孩子总算放心了。这颗石头\n就送给你吧。$"

Part55_Text_0276:
	.string "孩子一直惦记着她的旧布偶。\n听说是落在送神山山顶的墓碑旁了，\p你要是上去，能帮我们找找吗？$"

Part55_Text_0277:
	.string "布偶好好的，一点没坏。谢谢你，\n孩子已经把它紧紧抱在怀里了。$"

Part55_Text_0278:
	.string "墓碑旁常能看到小小的脚印。\p山上的花也很特别，有的品种\n要等很久才能见上一回。$"

Part55_Text_0279:
	.string "我在这里工作很多年了。每天扫扫\n地，再看看谁家的花该换了。$"

Part55_Text_0280:
	.string "最近山上的风刮得乱七八糟的。\n得先把花盆收好，免得被吹倒。$"

Part55_Text_0281:
	.string "风总算小了。今天可以把墓碑\n一块块好好擦一遍。$"

Part55_Text_0282:
	.string "又有老熟人来探望了。日子慢慢\n恢复，这里也和以前一样了。$"
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
	.string "桌上放着几只便当盒，压着一张字条：\n“别把饭盒放在热石头上。”$"

Part55_Text_0284:
	.string "架子上叠着磨破的工作手套。\n新的还没领回来。$"

Part55_Text_0285:
	.string "墙上贴着轮班表。今天的挖掘班\n还有两个人没签到。$"

Part55_Text_0286:
	.string "工具箱上贴着字条：“这里的石头\n太硬了，凿子又坏了一把。”$"

Part55_Text_0287:
	.string "椅背上挂着一双湿袜子，下面垫的\n纸也湿透了。$"

Part55_Text_0288:
	.string "柜子里塞着几只防水袋，\n其中一个袋口还粘着米粒。$"

Part55_Text_0289:
	.string "吃了一半的便当旁边放着船班表，\n下一班的时间被圈了出来。$"

Part55_Text_0290:
	.string "轮班表上有人写着：\n“下次别再把我排到夜班了！”$"

Part55_Text_0291:
	.string "一张没有署名的明信片，上面写着：\n“有空记得回家吃顿饭。”\p你把它放回了原处。$"

Part55_Text_0292:
	.string "床边堆着几个空瓶子，\n还没来得及收走。$"

Part55_Text_0293:
	.string "仔细一看，其中一个瓶子插着一朵\n小花。其余的还空着。$"

Part55_Text_0294:
	.string "今天我自己忘了吃午饭，伙伴们的\n饭倒是准时分好了。\p它们一饿就闹，这个我可忘不了。$"

Part55_Text_0295:
	.string "那家伙又晕船了。每次上船前都说\n“这次肯定没问题”。$"

Part55_Text_0296:
	.string "仪器读数一直往上跳，根本停不下来！\n里面太热了，我得出去透口气！$"

Part55_Text_0297:
	.string "应、应该没事吧？首领说过能控制住\n的。可这里怎么越来越热了……$"

Part55_Text_0298:
	.string "都到这儿了，我还在门口磨蹭。\n这次可不能再让她等了。$"

Part55_Text_0299:
	.string "刚才的事，算我欠你一次。里面太\n危险了，你也快离开吧！\p戴鲁比，我们走。$"
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
	goto_if_unset FLAG_STORY_C_02, Part55_StargazeCouple
	msgbox Part55_Text_0313, MSGBOX_NPC
	end


Part55_Text_0300:
	.string "刚才可把我吓坏了！总算接到孩子，\n接下来我们一起慢慢逛。$"

Part55_Text_0301:
	.string "总算抽出空来看看他。烧已经退了，\n今晚给他煮点清淡的。$"

Part55_Text_0302:
	.string "给家里打过电话以后，心里踏实多了。\n今天要和伊布一起逛原野区！$"

Part55_Text_0303:
	.string "欢迎参观阿尔刻园区。公共区域可以\n自由走动，工作区需要职员授权。$"

Part55_Text_0304:
	.string "又来啦？今天交流厅还有公开活动。\n不过里面的工作区仍需要授权哦。$"

Part55_Text_0305:
	.string "你也好奇电梯下层在忙什么？说实话，\n我也想看看。\p不过我的工作是守好门口。没有授权，\n谁都不能自己进去。$"

Part55_Text_0306:
	.string "听说你拿到第七枚徽章了，恭喜！\n园区的公开服务照常开放。$"

Part55_Text_0307:
	.string "第七枚徽章到手了？不错嘛！\n旁边的进阶训练也已经开放了。$"

Part55_Text_0308:
	.string "又见面了！听说你在绿岭道馆赢了。\n今天想吃点什么？$"

Part55_Text_0309:
	.string "上次还并肩作战，今天又成了对手。\n感觉真奇怪……不过工作就是工作。$"

Part55_Text_0310:
	.string "刚才宇宙中心那边好吵。现在还能\n等着看火箭吗？$"

Part55_Text_0311:
	.string "已经没事了。今天先回家吧，\n等工作人员确认好了再来看。$"

Part55_Text_0312:
	.string "合作观测的数据还得重新核对一遍。\n宇宙中心的工作人员也辛苦了。$"

Part55_Text_0313:
	.string "呼……呼……$"

Part55_ShuffleAside:
	walk_in_place_faster_left
	step_end

@ The Shuppet stays in its dead-end nook (11,26); moving it to (10,25)
@ blocked the only way back from the summit's west path.
Part55_DollPosition::
	setobjectxyperm LOCALID_PART5_BANETTITE, 11, 26
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
