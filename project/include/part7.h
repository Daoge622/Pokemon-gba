#ifndef GUARD_PART7_H
#define GUARD_PART7_H
bool32 Part7_IsMegaStone(enum Item item);
bool32 Part7_IsLootableItem(enum Item item);
bool32 Part7_IsItemOwned(enum Item item);
void Part7_CheckItemOwned(void);
bool32 Part7_IsLootBattle(void);
bool32 Part7_CanMegaStoneLeaveNpc(enum BattlerId battler1, enum BattlerId battler2, enum Item item);
enum Item Part7_GetMegaAuthorizationItem(enum BattlerId battler);
void Part7_ResetBattleLoot(void);
void Part7_RecordStolenItem(enum BattlerId stealer, enum Item item);
void Part7_GrantBattleLoot(void);
void Part7_MarkPlayerItemRemoved(enum BattlerId battler, enum Item item);
extern const u8 gText_Part7_MegaStoneNoToss[];
void Part7_SyncMap(void);
void Part7_PrepareBagon(void);
void Part7_FinishBagon(void);
void Part7_SetFlagIfCaught(void);
void Part7_IsWallyFinalTier(void);
void Part7_IsLeagueMap(void);
void Part7_BuyBpItem(void);
#endif
