FieryPath_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FieryPath_OnTransition
	.byte 0

FieryPath_OnTransition:
	call_if_unset FLAG_LANDMARK_FIERY_PATH, FieryPath_EventScript_MoveScottToFallarbor
	setflag FLAG_LANDMARK_FIERY_PATH
	end

FieryPath_EventScript_MoveScottToFallarbor::
	setflag FLAG_HIDE_VERDANTURF_TOWN_SCOTT
	clearflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	return


Part3_FieryHotFissure::
	msgbox Part3_FieryHotFissureText, MSGBOX_SIGN
	end

Part3_FieryHotFissureText:
	.string "从岩缝中不断冒出热气。\p站得太近的话，连精灵球都变得热乎\n乎的。$"
