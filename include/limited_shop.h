#ifndef GUARD_LIMITED_SHOP_H
#define GUARD_LIMITED_SHOP_H

// Returns a persistent purchase flag, or 0 for an ordinary unlimited item.
u16 GetLimitedShopPurchaseFlag(u16 map, enum Item item);

u16 GetLimitedShopRemaining(u16 map, enum Item item);
void RecordLimitedShopPurchase(u16 map, enum Item item, u16 count);

#endif
