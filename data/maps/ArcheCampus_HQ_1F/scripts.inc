ArcheCampus_HQ_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArcheCampus_HQ_1F_Part55OnTransition
	.byte 0

ArcheCampus_HQ_1F_Part55OnTransition:
	special Part6_SyncMap
	call_if_lt VAR_PART55_HQ_GUARD_VISITS, 3, Part55_AdvanceGuardVisit
	call_if_lt VAR_PART55_NEW_EMPLOYEE, 3, Part55_AdvanceEmployeeVisit
	end
