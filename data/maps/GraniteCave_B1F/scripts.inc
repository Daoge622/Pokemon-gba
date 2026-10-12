GraniteCave_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, GraniteCave_B1F_SetHoleWarp
	.byte 0

GraniteCave_B1F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_GRANITE_CAVE_B2F
	end


GraniteCave_Part1_Everstone::
 lock
 faceplayer
 goto_if_set FLAG_PART1_GRANITE_EVERSTONE, GraniteCave_Part1_Everstone_Done
 msgbox GraniteCave_Part1_Everstone_Intro, MSGBOX_DEFAULT
 giveitem ITEM_EVERSTONE, 1
 goto_if_eq VAR_RESULT, FALSE, GraniteCave_Part1_Everstone_BagFull
 setflag FLAG_PART1_GRANITE_EVERSTONE
 removeobject VAR_LAST_TALKED
GraniteCave_Part1_Everstone_Done::
 msgbox GraniteCave_Part1_Everstone_After, MSGBOX_DEFAULT
 release
 end
GraniteCave_Part1_Everstone_BagFull::
 msgbox Part1_Text_BagFull, MSGBOX_DEFAULT
 release
 end

GraniteCave_Part1_Everstone_Intro:
	.string "岩石旁有一件东西。$"

GraniteCave_Part1_Everstone_After:
	.string "这里已经没有东西了。$"
