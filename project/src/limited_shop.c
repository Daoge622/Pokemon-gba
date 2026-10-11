#include "global.h"
#include "limited_shop.h"
#include "event_data.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/maps.h"

struct LimitedShopItem
{
    u16 map;
    enum Item item;
    u16 purchaseFlag;
    u16 secondPurchaseFlag; // zero: limit 1; otherwise two independently recorded units

};

// Add one entry per shop/item and a fresh persistent flag for future imports.
static const struct LimitedShopItem sLimitedShopItems[] =
{
    { MAP_OLDALE_TOWN_MART, ITEM_ULTRA_BALL, FLAG_BOUGHT_OLDALE_IMPORT_ULTRA_BALL },
    { MAP_DEWFORD_TOWN, ITEM_DIVE_BALL, FLAG_PART1_BOUGHT_DEWFORD_DIVE_BALL },
    { MAP_SLATEPORT_CITY, ITEM_QUICK_BALL, FLAG_PART2_BOUGHT_QUICK_BALL },
    { MAP_MAUVILLE_CITY, ITEM_MAGNET, FLAG_PART2_BOUGHT_MAGNET },
    { MAP_FALLARBOR_TOWN_MART, ITEM_DUSK_BALL, FLAG_PART3_BOUGHT_DUSK_BALL },
    { MAP_ROUTE119, ITEM_THUNDER_STONE, FLAG_PART4_SHOP_THUNDER_STONE_FIRST, FLAG_PART4_SHOP_THUNDER_STONE_SECOND },
    { MAP_ROUTE119, ITEM_FIRE_STONE, FLAG_PART4_SHOP_FIRE_STONE_FIRST, FLAG_PART4_SHOP_FIRE_STONE_SECOND },
    { MAP_ROUTE119, ITEM_WATER_STONE, FLAG_PART4_SHOP_WATER_STONE_FIRST, FLAG_PART4_SHOP_WATER_STONE_SECOND },
    { MAP_ROUTE119, ITEM_MOON_STONE, FLAG_PART4_SHOP_MOON_STONE_FIRST, FLAG_PART4_SHOP_MOON_STONE_SECOND },
    { MAP_ROUTE119, ITEM_SUN_STONE, FLAG_PART4_SHOP_SUN_STONE_FIRST, FLAG_PART4_SHOP_SUN_STONE_SECOND },
    { MAP_ROUTE119, ITEM_DAWN_STONE, FLAG_PART4_SHOP_DAWN_STONE_FIRST, FLAG_PART4_SHOP_DAWN_STONE_SECOND },
    { MAP_ROUTE119, ITEM_EVOLUTION_STONE, FLAG_PART4_SHOP_EVOLUTION_STONE },
    { MAP_FORTREE_CITY_MART, ITEM_MIRACLE_SEED, FLAG_PART4_SHOP_MIRACLE_SEED },
    { MAP_LILYCOVE_CITY_DEPARTMENT_STORE_3F, ITEM_WIDE_LENS, FLAG_PART5_SHOP_WIDE_LENS },
    { MAP_LILYCOVE_CITY_DEPARTMENT_STORE_3F, ITEM_SCOPE_LENS, FLAG_PART5_SHOP_SCOPE_LENS },
    { MAP_LILYCOVE_CITY_DEPARTMENT_STORE_3F, ITEM_SHELL_BELL, FLAG_PART5_SHOP_SHELL_BELL },
    { MAP_LILYCOVE_CITY_DEPARTMENT_STORE_3F, ITEM_WISE_GLASSES, FLAG_PART5_SHOP_WISE_GLASSES },
    { MAP_LILYCOVE_CITY_DEPARTMENT_STORE_3F, ITEM_MUSCLE_BAND, FLAG_PART5_SHOP_MUSCLE_BAND },
    { MAP_LILYCOVE_CITY_DEPARTMENT_STORE_3F, ITEM_METRONOME, FLAG_PART5_SHOP_METRONOME },
    { MAP_LILYCOVE_CITY_DEPARTMENT_STORE_3F, ITEM_EVIOLITE, FLAG_PART5_SHOP_EVIOLITE },
    { MAP_MOSSDEEP_CITY_MART, ITEM_TWISTED_SPOON, FLAG_PART5_SHOP_MOSSDEEP_TWISTED_SPOON },
};

u16 GetLimitedShopPurchaseFlag(u16 map, enum Item item)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sLimitedShopItems); i++)
    {
        if (sLimitedShopItems[i].map == map && sLimitedShopItems[i].item == item)
            return sLimitedShopItems[i].purchaseFlag;
    }
    return 0;
}

// Unlimited entries retain the normal shop quantity cap. Existing one-unit stock is unchanged.
u16 GetLimitedShopRemaining(u16 map, enum Item item)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sLimitedShopItems); i++)
    {
        const struct LimitedShopItem *entry = &sLimitedShopItems[i];
        if (entry->map == map && entry->item == item)
            return !FlagGet(entry->purchaseFlag) + (entry->secondPurchaseFlag != 0 && !FlagGet(entry->secondPurchaseFlag));
    }
    return 0xFFFF;
}

void RecordLimitedShopPurchase(u16 map, enum Item item, u16 count)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sLimitedShopItems); i++)
    {
        const struct LimitedShopItem *entry = &sLimitedShopItems[i];
        if (entry->map != map || entry->item != item)
            continue;
        if (count != 0 && !FlagGet(entry->purchaseFlag))
        {
            FlagSet(entry->purchaseFlag);
            count--;
        }
        if (count != 0 && entry->secondPurchaseFlag != 0)
            FlagSet(entry->secondPurchaseFlag);
        return;
    }
}
