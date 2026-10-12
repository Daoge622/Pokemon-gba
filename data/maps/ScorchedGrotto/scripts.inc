ScorchedGrotto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Part3_GrottoTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Part3_GrottoFrameTable
	.byte 0

Part3_GrottoTransition:
	special SyncPart3EnteiObject
	end

Part3_GrottoFrameTable:
	map_script_2 VAR_TEMP_1, 0, Part3_GrottoFailureNotice
	.2byte 0

Part3_GrottoFailureNotice::
	setvar VAR_TEMP_1, 1
	goto_if_ne VAR_PART3_ENTEI_STATE, PART3_ENTEI_WAITING, Part3_GrottoEnd
	lockall
	msgbox Part3_EnteiFailureText, MSGBOX_DEFAULT
	releaseall
	end

Part3_GrottoEnd:
	end

Part3_Entei::
	lockall
	playmoncry SPECIES_ENTEI, CRY_MODE_NORMAL
	waitmoncry
	seteventmon SPECIES_ENTEI, PART3_ENTEI_LEVEL
	special BeginPart3EnteiBattle
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	special FinishPart3EnteiBattle
	removeobject LOCALID_PART3_ENTEI
	setvar VAR_TEMP_1, 1
	goto_if_eq VAR_PART3_ENTEI_STATE, PART3_ENTEI_CAUGHT, Part3_EnteiCaught
	msgbox Part3_EnteiFailureText, MSGBOX_DEFAULT
Part3_EnteiCaught:
	releaseall
	end

Part3_EnteiGone::
	goto_if_eq VAR_PART3_ENTEI_STATE, PART3_ENTEI_CAUGHT, Part3_EnteiSilent
	msgbox Part3_EnteiFailureText, MSGBOX_SIGN
	end
Part3_EnteiSilent:
	msgbox Part3_GrottoHeatText, MSGBOX_SIGN
	end

Part3_GrottoHeat::
	msgbox Part3_GrottoHeatText, MSGBOX_SIGN
	end

Part3_EnteiFailureText:
	.string "炎帝的身影消失在洞窟深处……\p空气中仍残留着炽热的气息。\p也许等你站上丰缘训练家的顶点\n之后，它还会再次回应你。$"


Part3_GrottoHeatText:
	.string "越往洞窟深处走，空气就越炽热。\p火山岩缝里吹来的热风，让人不由得\n屏住呼吸。$"
