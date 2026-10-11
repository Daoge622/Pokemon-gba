#include "global.h"
#include "battle.h"
#include "battle_controllers.h"
#include "battle_util.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "part7.h"
#include "constants/battle.h"
#include "constants/flags.h"
#include "constants/hold_effects.h"
#include "constants/items.h"
#include "constants/vars.h"
#include "constants/part5.h"

// PART7 item rules.
// - Mega stones are one-of-a-kind: "owned" is derived from where the stone can be (bag, PC, party,
//   boxes, Day Care) plus the completion state of the quest that already handed it out. No new flags.
// - Enemy item removal never costs the player anything permanently (TryRestoreHeldItems).
// - NPC Mega Evolution depends on the trainer's battle data, not on the item the mon holds right now.
// - Only Thief/Covet can loot, only Mega stones and items listed below, never in Frontier/link battles.

// Special items other than Mega stones that Thief/Covet may keep. Empty until a PART marks one.
static const u16 sLootableItems[] =
{
    ITEM_NONE,
};

enum
{
    OWNED_BY_FLAG,
    OWNED_BY_VAR_AT_LEAST,
};

struct Part7StoneSource
{
    u16 item;
    u8 kind;
    u16 id;
    u16 value;
};

// Quest states that are only reached after the stone was handed over.
static const struct Part7StoneSource sStoneSources[] =
{
    {ITEM_MANECTITE,      OWNED_BY_FLAG, FLAG_PART4_MANECTITE},
    {ITEM_MAWILITE,       OWNED_BY_FLAG, FLAG_PART7_HIKER_DONE},
    {ITEM_GYARADOSITE,    OWNED_BY_FLAG, FLAG_PART7_MAP_DONE},
    {ITEM_AGGRONITE,      OWNED_BY_FLAG, FLAG_PART4_RUINSAGGRONITE},
    {ITEM_SCIZORITE,      OWNED_BY_FLAG, FLAG_PART5_SCIZORITE},
    {ITEM_HERACRONITE,    OWNED_BY_FLAG, FLAG_PART5_HERACRONITE},
    {ITEM_PINSIRITE,      OWNED_BY_FLAG, FLAG_PART5_PINSIRITE},
    {ITEM_GARDEVOIRITE,   OWNED_BY_VAR_AT_LEAST, VAR_PART5_RIBBON, PART5_RIBBON_DONE},
    {ITEM_MEDICHAMITE,    OWNED_BY_FLAG, FLAG_PART5_MEDICHAMITE},
    {ITEM_ABSOLITE,       OWNED_BY_FLAG, FLAG_PART5_ABSOLITE},
    {ITEM_ALTARIANITE,    OWNED_BY_FLAG, FLAG_PART5_ALTARIANITE},
    {ITEM_CAMERUPTITE,    OWNED_BY_FLAG, FLAG_PART5_CAMERUPTITE},
    {ITEM_SHARPEDONITE,   OWNED_BY_FLAG, FLAG_PART5_SHARPEDONITE},
    {ITEM_LOPUNNITE,      OWNED_BY_VAR_AT_LEAST, VAR_PART55_FABRIC, 3},
    {ITEM_AMPHAROSITE,    OWNED_BY_VAR_AT_LEAST, VAR_PART55_MODULE, 3},
    {ITEM_ALAKAZITE,      OWNED_BY_VAR_AT_LEAST, VAR_PART55_ALAKAZITE, 3},
    {ITEM_GLALITITE,      OWNED_BY_VAR_AT_LEAST, VAR_PART55_FROZEN_STONE, 3},
    {ITEM_ABOMASITE,      OWNED_BY_VAR_AT_LEAST, VAR_PART55_ABOMASITE, 3},
    {ITEM_BEEDRILLITE,    OWNED_BY_VAR_AT_LEAST, VAR_PART55_BEE, 15},
    {ITEM_KANGASKHANITE,  OWNED_BY_FLAG, FLAG_PART7_METEOR_STAGE2},
    {ITEM_SABLENITE,      OWNED_BY_VAR_AT_LEAST, VAR_PART55_SABLEYITE, 3},
    {ITEM_PIDGEOTITE,     OWNED_BY_VAR_AT_LEAST, VAR_PART55_AIR_MAIL, 3},
    {ITEM_STEELIXITE,     OWNED_BY_VAR_AT_LEAST, VAR_PART55_STEELIX_REPAIR, 3},
    {ITEM_HOUNDOOMINITE,  OWNED_BY_VAR_AT_LEAST, VAR_PART55_HOUNDOUR_RESCUE, 3},
    {ITEM_BANETTITE,      OWNED_BY_FLAG, FLAG_PART5_BANETTITE},
    {ITEM_SLOWBRONITE,    OWNED_BY_FLAG, FLAG_PART6_TIDE_RECORDER_DONE},
    {ITEM_AERODACTYLITE,  OWNED_BY_FLAG, FLAG_PART6_SAMPLE_CASE_DONE},
    {ITEM_GALLADITE,      OWNED_BY_FLAG, FLAG_PART6_GALLADITE},
    {ITEM_SCEPTILITE, OWNED_BY_FLAG, FLAG_PART7_SCEPTILITE_DONE},
    {ITEM_BLAZIKENITE, OWNED_BY_FLAG, FLAG_PART7_BLAZIKENITE_DONE},
    {ITEM_SWAMPERTITE, OWNED_BY_FLAG, FLAG_PART7_SWAMPERTITE_DONE},
    {ITEM_SALAMENCITE, OWNED_BY_FLAG, FLAG_PART7_SALAMENCITE_DONE},
    {ITEM_METAGROSSITE, OWNED_BY_FLAG, FLAG_PART7_METAGROSSITE_DONE},
    {ITEM_LUCARIONITE, OWNED_BY_FLAG, FLAG_PART7_LUCARIONITE_DONE},
    {ITEM_GARCHOMPITE, OWNED_BY_FLAG, FLAG_PART7_GARCHOMPITE_DONE},
};

#define PART7_MAX_LOOT 8
static EWRAM_DATA u16 sBattleLoot[PART7_MAX_LOOT] = {0};

const u8 gText_Part7_MegaStoneNoToss[] = _("超级石只有一颗，\n不能丢掉！");

bool32 Part7_IsMegaStone(enum Item item)
{
    return item != ITEM_NONE && GetItemHoldEffect(item) == HOLD_EFFECT_MEGA_STONE;
}

bool32 Part7_IsLootableItem(enum Item item)
{
    if (Part7_IsMegaStone(item))
        return TRUE;
    for (u32 i = 0; sLootableItems[i] != ITEM_NONE; i++)
    {
        if (sLootableItems[i] == item)
            return TRUE;
    }
    return FALSE;
}

static bool32 IsStoneQuestDone(enum Item item)
{
    for (u32 i = 0; i < ARRAY_COUNT(sStoneSources); i++)
    {
        const struct Part7StoneSource *src = &sStoneSources[i];
        if (src->item != item)
            continue;
        if (src->kind == OWNED_BY_FLAG && FlagGet(src->id))
            return TRUE;
        if (src->kind == OWNED_BY_VAR_AT_LEAST && VarGet(src->id) >= src->value)
            return TRUE;
    }
    return FALSE;
}

bool32 Part7_IsItemOwned(enum Item item)
{
    if (item == ITEM_NONE)
        return FALSE;
    if (CheckBagHasItem(item, 1) || CheckPCHasItem(item, 1) || IsStoneQuestDone(item))
        return TRUE;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_HELD_ITEM) == item)
            return TRUE;
    }
    for (u32 i = 0; i < DAYCARE_MON_COUNT; i++)
    {
        if (GetBoxMonData(&gSaveBlock1Ptr->daycare.mons[i].mon, MON_DATA_HELD_ITEM) == item)
            return TRUE;
    }
    for (u32 box = 0; box < TOTAL_BOXES_COUNT; box++)
    {
        for (u32 pos = 0; pos < IN_BOX_COUNT; pos++)
        {
            if (GetBoxMonDataAt(box, pos, MON_DATA_HELD_ITEM) == item)
                return TRUE;
        }
    }
    return FALSE;
}

// Script use: setvar VAR_0x8004, ITEM_X ; special Part7_CheckItemOwned -> VAR_RESULT
void Part7_CheckItemOwned(void)
{
    gSpecialVar_Result = Part7_IsItemOwned(gSpecialVar_0x8004);
}

// Ordinary in-game trainer battles. Frontier, link, recorded, e-Reader, secret base and Trainer Hill
// battles keep Expansion's native item rules and never produce loot.
bool32 Part7_IsLootBattle(void)
{
    return (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        && !(gBattleTypeFlags & (BATTLE_TYPE_FRONTIER
                               | BATTLE_TYPE_LINK
                               | BATTLE_TYPE_RECORDED
                               | BATTLE_TYPE_RECORDED_LINK
                               | BATTLE_TYPE_EREADER_TRAINER
                               | BATTLE_TYPE_SECRET_BASE
                               | BATTLE_TYPE_TRAINER_HILL));
}

static bool32 IsNpcOpponent(enum BattlerId battler)
{
    return !IsOnPlayerSide(battler) && Part7_IsLootBattle();
}

// A Mega stone held by an NPC opponent may be stolen, knocked off or swapped by the player's side,
// even when the holder could Mega Evolve with it. Player-side stones keep Expansion's protection,
// and NPCs never give their own stone away (the move user has to be on the player's side).
bool32 Part7_CanMegaStoneLeaveNpc(enum BattlerId battler1, enum BattlerId battler2, enum Item item)
{
    if (!Part7_IsMegaStone(item) || battler1 == battler2 || !IsOnPlayerSide(gBattlerAttacker))
        return FALSE;
    if (IsOnPlayerSide(battler1) == IsOnPlayerSide(battler2))
        return FALSE;
    if (gBattleMons[battler1].item == item && IsNpcOpponent(battler1))
        return TRUE;
    if (gBattleMons[battler2].item == item && IsNpcOpponent(battler2))
        return TRUE;
    return FALSE;
}

// NPC Mega authorization: the item the mon carried at battle start (trainer data), whatever it holds now.
enum Item Part7_GetMegaAuthorizationItem(enum BattlerId battler)
{
    if (IsNpcOpponent(battler))
        return gBattleStruct->itemLost[GetBattlerTrainer(battler)][gBattlerPartyIndexes[battler]].originalItem;
    return gBattleMons[battler].item;
}

void Part7_ResetBattleLoot(void)
{
    for (u32 i = 0; i < PART7_MAX_LOOT; i++)
        sBattleLoot[i] = ITEM_NONE;
}

// Called when Thief/Covet takes an item. Only the player's own mons loot, never an in-game partner.
void Part7_RecordStolenItem(enum BattlerId stealer, enum Item item)
{
    if (!Part7_IsLootBattle() || GetBattlerTrainer(stealer) != B_TRAINER_PLAYER || !Part7_IsLootableItem(item))
        return;
    for (u32 i = 0; i < PART7_MAX_LOOT; i++)
    {
        if (sBattleLoot[i] == item)
            return;
        if (sBattleLoot[i] == ITEM_NONE)
        {
            sBattleLoot[i] = item;
            return;
        }
    }
}

// Runs after held items were restored, so a stone that only sat on the thief this battle does not count as owned.
void Part7_GrantBattleLoot(void)
{
    for (u32 i = 0; i < PART7_MAX_LOOT; i++)
    {
        enum Item item = sBattleLoot[i];
        sBattleLoot[i] = ITEM_NONE;
        if (item == ITEM_NONE || Part7_IsItemOwned(item))
            continue;
        if (!AddBagItem(item, 1))
            AddPCItem(item, 1);
    }
}

// Bug Bite, Pluck and Incinerate remove the player's item without going through the steal helpers.
void Part7_MarkPlayerItemRemoved(enum BattlerId battler, enum Item item)
{
    if (GetBattlerTrainer(battler) != B_TRAINER_PLAYER)
        return;
    if (item != ITEM_NONE && item == gBattleStruct->itemLost[B_TRAINER_PLAYER][gBattlerPartyIndexes[battler]].originalItem)
        gBattleStruct->itemLost[B_TRAINER_PLAYER][gBattlerPartyIndexes[battler]].stolen = TRUE;
}
