Route112_CableCarStation_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route112_CableCarStation_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route112_CableCarStation_OnFrame
	.byte 0

Route112_CableCarStation_OnTransition:
	call StoryB_CableCar_OnTransition
	setescapewarp MAP_ROUTE112, 28, 28
	call_if_eq VAR_CABLE_CAR_STATION_STATE, 2, Route112_CableCarStation_EventScript_MoveAttendantAside
	end

Route112_CableCarStation_EventScript_MoveAttendantAside::
	setobjectxyperm LOCALID_ROUTE112_CABLE_CAR_ATTENDANT, 7, 4
	setobjectmovementtype LOCALID_ROUTE112_CABLE_CAR_ATTENDANT, MOVEMENT_TYPE_FACE_LEFT
	return

Route112_CableCarStation_OnFrame:
	map_script_2 VAR_CABLE_CAR_STATION_STATE, 2, Route112_CableCarStation_EventScript_ExitCableCar
	.2byte 0

Route112_CableCarStation_EventScript_ExitCableCar::
	lockall
	applymovement LOCALID_PLAYER, Route112_CableCarStation_Movement_ExitCableCar
	applymovement LOCALID_ROUTE112_CABLE_CAR_ATTENDANT, Route112_CableCarStation_Movement_FollowPlayerOutFromCableCar
	waitmovement 0
	setvar VAR_CABLE_CAR_STATION_STATE, 0
	setobjectxyperm LOCALID_ROUTE112_CABLE_CAR_ATTENDANT, 6, 7
	setobjectmovementtype LOCALID_ROUTE112_CABLE_CAR_ATTENDANT, MOVEMENT_TYPE_FACE_DOWN
	releaseall
	end

Route112_CableCarStation_EventScript_Attendant::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_ROUTE_112_TEAM_MAGMA, Route112_CableCarStation_Part3_Blocked
	call_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, Route112_CableCarStation_Part3_Warning
	msgbox Route112_CableCarStation_Text_CableCarReadyGetOn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route112_CableCarStation_EventScript_RideCableCar
	goto_if_eq VAR_RESULT, NO, Route112_CableCarStation_EventScript_DeclineRide
	end

Route112_CableCarStation_EventScript_RideCableCar::
	msgbox Route112_CableCarStation_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE112_CABLE_CAR_ATTENDANT, Route112_CableCarStation_Movement_LeadPlayerToCableCar
	applymovement LOCALID_PLAYER, Route112_CableCarStation_Movement_BoardCableCar
	waitmovement 0
	setvar VAR_0x8004, FALSE  @ Going up
	setvar VAR_CABLE_CAR_STATION_STATE, 1
	incrementgamestat GAME_STAT_RODE_CABLE_CAR
	special CableCarWarp
	special CableCar
	release
	end

Route112_CableCarStation_EventScript_DeclineRide::
	msgbox Route112_CableCarStation_Text_RideAnotherTime, MSGBOX_DEFAULT
	release
	end

Route112_CableCarStation_Movement_LeadPlayerToCableCar:
	walk_up
	walk_up
	walk_right
	walk_in_place_faster_left
	step_end

Route112_CableCarStation_Movement_FollowPlayerOutFromCableCar:
	delay_16
	walk_left
	walk_down
	walk_down
	step_end

Route112_CableCarStation_Movement_BoardCableCar:
	walk_up
	walk_up
	walk_up
	delay_16
	step_end

Route112_CableCarStation_Movement_ExitCableCar:
	walk_down
	walk_down
	walk_down
	delay_16
	step_end

Route112_CableCarStation_Text_CableCarReadyGetOn:
    .string "登山缆车即将发车。\n您要乘坐吗？$"

Route112_CableCarStation_Text_StepThisWay:
    .string "这边请。$"

Route112_CableCarStation_Text_RideAnotherTime:
    .string "欢迎再次乘坐。$"


Route112_CableCarStation_Part3_Blocked::
 msgbox Route112_CableCarStation_Part3_BlockedText, MSGBOX_DEFAULT
 release
 end
Route112_CableCarStation_Part3_Warning::
 msgbox Route112_CableCarStation_Part3_WarningText, MSGBOX_DEFAULT
 return

Route112_CableCarStation_Part3_BlockedText:
	.string "缆车入口被人封住了，暂时无法发车\n。\p刚才明明还在正常营业……请稍等一下\n。$"

Route112_CableCarStation_Part3_WarningText:
	.string "入口已经可以通行了，不过山顶好像\n还在发生争执。\p乘车上山的话，请留意周围的情况。$"
