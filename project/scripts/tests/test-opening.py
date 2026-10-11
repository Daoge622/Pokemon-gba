#!/usr/bin/env python3
"""Native host checks of actual gift/table C modules; no emulator or GUI."""
import json, re, subprocess, tempfile
from pathlib import Path
root = Path(__file__).resolve().parents[2]
flags = (root/'include/constants/flags.h').read_text()
for name, value in [('FLAG_RECEIVED_LITTLEROOT_RALTS_EGG', 0x20), ('FLAG_BOUGHT_OLDALE_IMPORT_ULTRA_BALL', 0x21)]:
    defs = re.findall(r'^#define\s+(FLAG_\w+)\s+(0x[0-9A-Fa-f]+)\b', flags, re.M)
    assert [(n,v) for n,v in defs if int(v,16)==value] == [(name, f'0x{value:02X}')], name
# Integration guards: validate transaction ordering in production shop source.
shop = (root/'src/shop.c').read_text()
assert shop.count('if (IsCurrentLimitedShopItemSoldOut(itemId)') == 2
assert 'if (sShopData->maxQuantity > remaining)' in shop
assert 'tItemCount > GetLimitedShopRemaining(' in shop
purchase = shop[shop.index('static void BuyMenuTryMakePurchase(u8 taskId)\n{'):shop.index('static void BuyMenuSubtractMoney(u8 taskId)\n{')]
assert 'FlagSet(' not in purchase
assert purchase.index('GetLimitedShopRemaining(') < purchase.index('AddBagItem(')
subtract = shop[shop.index('static void BuyMenuSubtractMoney(u8 taskId)\n{'):shop.index('static void Task_ReturnToItemListAfterItemPurchase(u8 taskId)\n{')]
assert subtract.index('RemoveMoney(') < subtract.index('RecordLimitedShopPurchase(')
assert 'BuyMenuSubtractMoney' in purchase
print('Shop transaction ordering and single-item guards (static): PASS')
config = json.loads((root/'tools/poryscript/font_config.json').read_text())
font = config['fonts'][config['defaultFontId']]
checked = 0
for file, labels in [('LittlerootTown', ['PrivateEggIntroduction','ReceivedPrivateEgg','PrivateEggFarewell','NoRoomForPrivateEgg']), ('OldaleTown',['OverseasGoods'])]:
    source=(root/f'data/maps/{file}/scripts.inc').read_text()
    for label in labels:
        block=re.search(rf'{file}_Text_{label}:\n((?:\s*\.string[^\n]*\n?)+)',source).group(1)
        text=''.join(re.findall(r'\.string "(.*)"',block)).replace('{PLAYER}', 'WWWWWWW')
        for page in text.split(r'\p'):
            lines=page.rstrip('$').replace(r'\l', r'\n').split(r'\n')
            assert len(lines)<=2, (label,lines)
            for line in lines:
                width=sum(font['widths'][c] for c in line)
                assert width<=font['maxLineLength'], (label,line,width)
                checked+=1
with tempfile.TemporaryDirectory() as d:
    p=Path(d); (p/'constants').mkdir()
    (p/'global.h').write_text('''#ifndef STUB_GLOBAL
#define STUB_GLOBAL
#include <stdint.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32;
#define TRUE 1
#define FALSE 0
#define PARTY_SIZE 6
#define MAX_PER_STAT_IVS 31
#define ARRAY_COUNT(a) (sizeof(a)/sizeof((a)[0]))
enum Item { ITEM_NONE, ITEM_ULTRA_BALL, ITEM_POTION, ITEM_DIVE_BALL, ITEM_QUICK_BALL, ITEM_MAGNET, ITEM_DUSK_BALL, ITEM_GREAT_BALL, ITEM_THUNDER_STONE, ITEM_FIRE_STONE, ITEM_WATER_STONE, ITEM_MOON_STONE, ITEM_SUN_STONE, ITEM_DAWN_STONE, ITEM_EVOLUTION_STONE, ITEM_MIRACLE_SEED, ITEM_WIDE_LENS, ITEM_SCOPE_LENS, ITEM_SHELL_BELL, ITEM_WISE_GLASSES, ITEM_MUSCLE_BAND, ITEM_METRONOME, ITEM_EVIOLITE, ITEM_TWISTED_SPOON };
struct Pokemon { int spatk; };
extern u16 gSpecialVar_Result;
#endif
''')
    (p/'daycare.h').write_text('void CreateEgg(struct Pokemon *, u16, u8);\n')
    (p/'event_data.h').write_text('u8 FlagGet(u16); void FlagSet(u16);\n')
    (p/'pokemon.h').write_text('''#define SPECIES_RALTS 280
#define MON_DATA_SPATK_IV 1
#define MON_GIVEN_TO_PARTY 0
u8 CalculatePlayerPartyCount(void);
void SetMonData(struct Pokemon *, int, const void *);
u8 GiveCapturedMonToPlayer(struct Pokemon *);
''')
    (p/'constants/flags.h').write_text('''#define FLAG_SYS_POKEMON_GET 3
#define FLAG_RECEIVED_LITTLEROOT_RALTS_EGG 0x20
#define FLAG_BOUGHT_OLDALE_IMPORT_ULTRA_BALL 0x21
#define FLAG_PART1_BOUGHT_DEWFORD_DIVE_BALL 0x28
#define FLAG_PART2_BOUGHT_QUICK_BALL 0x31
#define FLAG_PART2_BOUGHT_MAGNET 0x39
#define FLAG_PART3_BOUGHT_DUSK_BALL 0x46
''')
    (p/'constants/flags.h').write_text((p/'constants/flags.h').read_text()+''.join('#define '+n+' '+str(v)+'\n' for n,v in json.loads((root/'docs/project/part4-manifest.json').read_text())['flags'].items()))
    # PART5 limited-stock flags (values from the generated manifest)
    (p/'constants/flags.h').write_text((p/'constants/flags.h').read_text()+''.join('#define '+n+' '+str(int(v,16))+'\n' for n,v in json.loads((root/'docs/project/part5-manifest.json').read_text())['flags'].items()))
    (p/'constants/items.h').write_text('')
    (p/'constants/maps.h').write_text('#define MAP_OLDALE_TOWN_MART 0x204\n#define MAP_DEWFORD_TOWN 0x300\n#define MAP_SLATEPORT_CITY 0x400\n#define MAP_MAUVILLE_CITY 0x500\n#define MAP_FALLARBOR_TOWN_MART 0x600\n#define MAP_ROUTE119 0x700\n#define MAP_FORTREE_CITY_MART 0x701\n#define MAP_LILYCOVE_CITY_DEPARTMENT_STORE_3F 0x800\n#define MAP_MOSSDEEP_CITY_MART 0x801\n')
    (p/'test.c').write_text('''#include "global.h"
#include "project_gifts.h"
#include "limited_shop.h"
#include <assert.h>
#include <stdio.h>
u16 gSpecialVar_Result;
static u8 flags[4096], party, delivery; static int created, sets, delivered;
u8 FlagGet(u16 f) { return flags[f]; }
void FlagSet(u16 f) { flags[f]=1; }
u8 CalculatePlayerPartyCount(void) { return party; }
void CreateEgg(struct Pokemon *p,u16 species,u8 special) { assert(species==280); assert(!special); p->spatk=7; created++; }
void SetMonData(struct Pokemon *p,int field,const void *value) { assert(field==1); p->spatk=*(const u32 *)value; sets++; }
u8 GiveCapturedMonToPlayer(struct Pokemon *p) { assert(p->spatk==31); delivered++; return delivery; }
int main(void) {
 GiveLittlerootRaltsEgg(); assert(!created && !gSpecialVar_Result);
 flags[3]=1; party=6; GiveLittlerootRaltsEgg(); assert(!created && !flags[32]);
 party=1; delivery=2; GiveLittlerootRaltsEgg(); assert(created==1 && !flags[32] && !gSpecialVar_Result);
 delivery=0; GiveLittlerootRaltsEgg(); assert(created==2 && sets==2 && delivered==2 && flags[32] && gSpecialVar_Result);
 GiveLittlerootRaltsEgg(); assert(created==2 && !gSpecialVar_Result);
 assert(GetLimitedShopPurchaseFlag(0x204,ITEM_ULTRA_BALL)==33);
 assert(GetLimitedShopPurchaseFlag(0x205,ITEM_ULTRA_BALL)==0);
 assert(GetLimitedShopPurchaseFlag(0x300,ITEM_DIVE_BALL)==40);
 assert(GetLimitedShopPurchaseFlag(0x300,ITEM_ULTRA_BALL)==0);
 assert(GetLimitedShopPurchaseFlag(0x204,ITEM_POTION)==0);
 assert(GetLimitedShopPurchaseFlag(0x204,ITEM_NONE)==0);
 assert(GetLimitedShopPurchaseFlag(0x400,ITEM_QUICK_BALL)==0x31);
 assert(GetLimitedShopPurchaseFlag(0x500,ITEM_MAGNET)==0x39);
 assert(GetLimitedShopPurchaseFlag(0x400,ITEM_MAGNET)==0);
 assert(GetLimitedShopPurchaseFlag(0x500,ITEM_QUICK_BALL)==0);
 assert(GetLimitedShopPurchaseFlag(0x600,ITEM_DUSK_BALL)==0x46);
 assert(GetLimitedShopPurchaseFlag(0x600,ITEM_GREAT_BALL)==0);
 assert(GetLimitedShopPurchaseFlag(0x500,ITEM_DUSK_BALL)==0);
 assert(GetLimitedShopRemaining(0x700,ITEM_THUNDER_STONE)==2);
 RecordLimitedShopPurchase(0x700,ITEM_THUNDER_STONE,0); assert(GetLimitedShopRemaining(0x700,ITEM_THUNDER_STONE)==2);
 RecordLimitedShopPurchase(0x700,ITEM_THUNDER_STONE,1); assert(GetLimitedShopRemaining(0x700,ITEM_THUNDER_STONE)==1);
 RecordLimitedShopPurchase(0x700,ITEM_THUNDER_STONE,1); assert(GetLimitedShopRemaining(0x700,ITEM_THUNDER_STONE)==0);
 RecordLimitedShopPurchase(0x700,ITEM_FIRE_STONE,2); assert(GetLimitedShopRemaining(0x700,ITEM_FIRE_STONE)==0);
 assert(GetLimitedShopRemaining(0x700,ITEM_WATER_STONE)==2);
 RecordLimitedShopPurchase(0x700,ITEM_EVOLUTION_STONE,1); assert(GetLimitedShopRemaining(0x700,ITEM_EVOLUTION_STONE)==0);
 assert(GetLimitedShopRemaining(0x204,ITEM_POTION)==0xffff);
 assert(GetLimitedShopRemaining(0x700,ITEM_ULTRA_BALL)==0xffff);
 RecordLimitedShopPurchase(0x701,ITEM_MIRACLE_SEED,1); assert(GetLimitedShopRemaining(0x701,ITEM_MIRACLE_SEED)==0);
 /* PART5: Lilycove 3F tactical counter and Mossdeep spoon, one unit each, map-scoped */
 assert(GetLimitedShopRemaining(0x800,ITEM_WIDE_LENS)==1); assert(GetLimitedShopRemaining(0x800,ITEM_EVIOLITE)==1);
 RecordLimitedShopPurchase(0x800,ITEM_EVIOLITE,1); assert(GetLimitedShopRemaining(0x800,ITEM_EVIOLITE)==0); assert(GetLimitedShopRemaining(0x800,ITEM_SCOPE_LENS)==1);
 assert(GetLimitedShopRemaining(0x801,ITEM_TWISTED_SPOON)==1); assert(GetLimitedShopRemaining(0x800,ITEM_TWISTED_SPOON)==0xffff);
 RecordLimitedShopPurchase(0x801,ITEM_TWISTED_SPOON,1); assert(GetLimitedShopRemaining(0x801,ITEM_TWISTED_SPOON)==0);
 puts("Gift boundaries, original one-unit stock and new two-unit stock native C: PASS");
}
''')
    subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror','-Wno-missing-field-initializers',f'-I{p}',f'-I{root / "include"}',str(p/'test.c'),str(root/'src/project_gifts.c'),str(root/'src/limited_shop.c'),'-o',str(p/'test')],check=True)
    subprocess.run([str(p/'test')],check=True)
print(f'Flag allocation and {checked} dialogue lines within 208 pixels: PASS')
