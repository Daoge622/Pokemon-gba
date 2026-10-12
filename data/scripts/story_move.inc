@ ---------------------------------------------------------------
@ Cutscene movement helpers (see src/story_move.c)
@ ---------------------------------------------------------------

@ In: VAR_0x8000 = local id, VAR_0x8001 = how close to stop (1 = adjacent)
@ The NPC walks around obstacles to the player, then faces the player.
Story_WalkToPlayer::
	setvar VAR_0x8007, 0
Story_WalkToPlayer_Loop:
	special StoryStepTowardPlayer
	goto_if_eq VAR_RESULT, 0, Story_WalkToPlayer_Done
	call Story_StepInResultDir
	addvar VAR_0x8007, 1
	goto_if_lt VAR_0x8007, 24, Story_WalkToPlayer_Loop
Story_WalkToPlayer_Done:
	applymovement VAR_0x8000, Common_Movement_FacePlayer
	waitmovement 0
	special StoryPlayerFaceObject
	return

@ In: VAR_0x8000 = local id, VAR_0x8001 = number of steps.
@ The NPC walks away from the player, then is removed.
Story_WalkAwayAndRemove::
	call Story_WalkAwayFromPlayerKeep
	removeobject VAR_0x8000
	return

@ Same, but the NPC stays (steps back).
Story_WalkAwayFromPlayerKeep::
	setvar VAR_0x8007, 0
Story_WalkAway_Loop:
	goto_if_ge VAR_0x8007, VAR_0x8001, Story_WalkAway_Done
	special StoryStepAwayFromPlayer
	goto_if_eq VAR_RESULT, 0, Story_WalkAway_Done
	call Story_StepInResultDir
	addvar VAR_0x8007, 1
	goto Story_WalkAway_Loop
Story_WalkAway_Done:
	return

@ In: VAR_0x8000 = local id, VAR_0x8001/VAR_0x8002 = offset from the player (signed).
@ Places the (hidden) object on the nearest free tile and shows it.
Story_SpawnNearPlayer::
	special StoryFindSpawnNearPlayer
	setobjectxyperm VAR_0x8000, VAR_0x8004, VAR_0x8005
	addobject VAR_0x8000
	return

Story_StepInResultDir:
	call_if_eq VAR_RESULT, DIR_SOUTH, Story_StepDown
	call_if_eq VAR_RESULT, DIR_NORTH, Story_StepUp
	call_if_eq VAR_RESULT, DIR_WEST, Story_StepLeft
	call_if_eq VAR_RESULT, DIR_EAST, Story_StepRight
	return

Story_StepDown:
	applymovement VAR_0x8000, Common_Movement_WalkDown
	waitmovement 0
	return

Story_StepUp:
	applymovement VAR_0x8000, Common_Movement_WalkUp
	waitmovement 0
	return

Story_StepLeft:
	applymovement VAR_0x8000, Common_Movement_WalkLeft
	waitmovement 0
	return

Story_StepRight:
	applymovement VAR_0x8000, Common_Movement_WalkRight
	waitmovement 0
	return
