SkyPillar_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_Entrance_OnTransition
	.byte 0

SkyPillar_Entrance_OnTransition:
	special Part6_SyncMap
	setflag FLAG_LANDMARK_SKY_PILLAR
	end

