## 2026-10-11 (2) — Playtest fixes from the user's list (Route 118–120, Fortree, bag freeze)  [IMPLEMENTED + TESTED headless]

The user reported 7 problems. All were reproduced or checked with the user's own MyBoy save (`EmeraldStory-一周目完整版.sav`, Route 120, 6 badges) in headless mGBA.

### Crashes (#6 Arche guard battle freeze, #7 bag graphics / freeze)
- Root cause: `LOCALID_PART4_FORESTACE` on Route 120 used `OBJ_EVENT_GFX_COOLTRAINER_F`. That is an FRLG-only graphics ID, and its entry in `gObjectEventGraphicsInfoPointers` is NULL in the Emerald build. The sprite was built from garbage data (corrupt tiles in the bag) and crashed in `ContinueAnim` whenever Route 120 objects were re-created (returning from a battle or from the bag).
- A sweep found 5 such objects. They now use Emerald graphics:
  - Route120 ForestAce → `WOMAN_5`
  - Route124/126 divers (`SWIMMER_M_LAND`) → `RUNNING_TRIATHLETE_M`
  - Scorched Grotto Entei → `SPECIES(ENTEI)`
  - Still Water Cave Suicune → `SPECIES(SUICUNE)`
- Safety net: `GetObjectEventGraphicsInfo()` now falls back to `NINJA_BOY` whenever the table entry is NULL. That includes a NULL species graphic.
- Verified: the guard battle finishes and the guard walks away; opening the bag, scrolling every pocket and closing it no longer resets the game.

### #5 Fisherman battles as a Lv50 Magma grunt
- Story B's Lavaridge multi battle used vanilla slots `TRAINER_KAYLEE` and `TRAINER_TERRY` for its Magma grunts. It overwrote Part 4's aliases for those slots: `TRAINER_PART4_ACE` = KAYLEE and `TRAINER_PART4_FISHER` = TERRY.
- The two trainers.party blocks are restored from base3 (05ec7d20): 阿成 / Fisherman and 小岚 / Cooltrainer.
- The Lava grunts moved to `PARTNER_STORY_A_SPARE1/2` (battle_partners.party), and story_b now uses `TRAINER_STORY_A_SPARE1/2`.
- A block-level audit of story branches A, B and C found no other slot collisions.
- The lake fisherman moved from the middle of the path (5,20) to the pond edge at Route 120 (22,30), facing the water.

### #1 Route 118 Anti scene
- New helpers in `src/story_move.c` and `data/scripts/story_move.inc`:
  - `StoryStepTowardPlayer`: BFS path to the player, with a stop distance.
  - `StoryStepAwayFromPlayer`.
  - `StoryFindSpawnNearPlayer`.
  - `StoryPlayerFaceObject`.
  - Script wrappers `Story_WalkToPlayer`, `Story_WalkAwayAndRemove`, `Story_WalkAwayFromPlayerKeep`, `Story_SpawnNearPlayer`.
- New scene flow:
  1. Both grunts get a "!" and walk up to the player.
  2. After its loss, grunt A steps back and grunt B walks up.
  3. Three reinforcements run in from off-screen and surround the player.
  4. Anti, then Scizor, walk in. Scizor flashes.
  5. All five Aqua walk away and disappear.
  6. Anti walks up and gives the Mega Ring, then he and Scizor walk off.
- Text 057 is split into Anti's line and a new 057b for the grunts.
- The same walk-in / walk-out was applied to other abrupt appear/vanish moments:
  - Route 120 Arche guard
  - Part5 shopping list NPC
  - Part55 rescued Magma + Houndour
  - Part55 team-up Aqua pair
  - Story B Lavaridge grunts
  - Story A Mt. Pyre Anti
  - Story A Hayato farewell
  - Part7 Route 119 girl + Jigglypuff (walk in)

### #2 Clutter
- The Route 118 Volbeat/Illumise pair (pure decoration standing in the grass lane) moved to the dead-end nook at (56,4)/(58,4).

### #3 Fortree errands and invisible pickups
- Fortree:
  - Kite boy + Swablu moved off the entrance to the south-east garden (35,18)/(36,18).
  - Postman + Pelipper moved next to the Mart (6,17)/(5,17).
  - The kite now lies under the bridge head (12,15). The kite and parcel texts now say exactly where to look.
- New system `src/story_markers.c`: quest pickups that were invisible sign events now have a visible item-ball marker object. Each marker:
  - uses a temp flag;
  - has its state evaluated in `RunOnTransitionMapScript` → `Story_UpdatePickupMarkers`;
  - is removed right after pickup via `special StoryRefreshPickupMarkers`.
- 18 markers:
  - Fortree kite and parcel
  - Meteor Falls stardust
  - Pacifidlog planks ×2
  - Route 108 bottle pearl
  - Route 111 canteen and the desert evolution stone (28,37)
  - Route 118 berry basket
  - Route 120 Mawilite (only after Kecleon 0)
  - Route 131 plank
  - Route 133 nuggets
  - Shoal Cave frozen stone (only after Shell Bell)
  - Underwater 127 ×2, 129 ×1, Sootopolis ×2
- The canteen owner now says the canteen blew south, to the east side of the sand.

### #4 Scorched Slab "air wall"
- A visible statue (`TRICK_HOUSE_STATUE`, `LOCALID_PART4_SEAL_STATUE`) now stands next to the sealed wall at (8,4).
- The seal text now says it opens after becoming Champion and receiving permission. Talking to the statue runs the same seal script.

### Tests (release build)
- Norman → Surf from the user's gym-door save: OK.
- Route 120 guard battle: OK.
- Bag pocket scroll and close on Route 120: OK.
- Fisherman battle shows Fisherman 阿成: OK.
- Route 118 scene: full run to the Mega Ring, with 2 battles: OK.
- Markers: the kite marker disappears on pickup; the desert stone marker is visible.
- 8-map random walk/talk soak: OK.
