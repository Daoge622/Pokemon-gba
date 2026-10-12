ArcheCampus_HQ_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArcheCampus_HQ_2F_Part55OnTransition
	.byte 0

ArcheCampus_HQ_2F_Part55OnTransition:
	clearflag FLAG_TEMP_1D
	call_if_eq VAR_PART55_MEDICINE, 3, Part55_HideMedicineSender
	setflag FLAG_PART55_HIDE_PORYGON
	call_if_eq VAR_PART55_PORYGON, 4, Part55_ShowPorygon
	end
