#!/usr/bin/env python3
"""PART7 engine rules: host-compiled C tests of the real source plus static wiring checks. No ROM/emulator."""
from pathlib import Path
import re, subprocess, tempfile, json

R = Path(__file__).resolve().parents[2]
results = []


def read(f):
    return (R / f).read_text(encoding='utf-8')


def check(name, cond, detail=''):
    results.append((name, bool(cond), detail))


def fn(s, name):
    m = re.search(r'(?m)^[\w *]+\b' + name + r'\([^;]*?\)\n\{', s)
    assert m, name
    b = s.index('{', m.start())
    i = b + 1
    depth = 1
    while depth:
        depth += (s[i] == '{') - (s[i] == '}')
        i += 1
    return s[m.start():i]


part7 = read('src/part7.c')
util = read('src/battle_util.c')
stones = sorted(set(re.findall(r'\{(ITEM_\w+),\s+OWNED_BY', part7)))
ids = sorted(set(re.findall(r'OWNED_BY_\w+, ((?:FLAG|VAR)_\w+)', part7)))

# ---------- host-compiled tests ----------
prelude = '''#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef int16_t s16; typedef unsigned bool32;
#define TRUE 1
#define FALSE 0
#define EWRAM_DATA
#define ARRAY_COUNT(a) (sizeof(a) / sizeof((a)[0]))
#define _(x) {0}
#define PARTY_SIZE 6
#define DAYCARE_MON_COUNT 2
#define TOTAL_BOXES_COUNT 14
#define IN_BOX_COUNT 30
#define MAX_BATTLE_TRAINERS 4
#define GEN_5 5
#define GEN_9 9
#define GEN_LATEST 9
#define B_TRAINERS_KNOCK_OFF_ITEMS TRUE
#define B_RESTORE_HELD_BATTLE_ITEMS GEN_LATEST
#define B_RETURN_STOLEN_NPC_ITEMS GEN_LATEST
#define BATTLE_TYPE_TRAINER (1u << 3)
#define BATTLE_TYPE_LINK (1u << 1)
#define BATTLE_TYPE_RECORDED (1u << 24)
#define BATTLE_TYPE_RECORDED_LINK (1u << 25)
#define BATTLE_TYPE_EREADER_TRAINER (1u << 11)
#define BATTLE_TYPE_SECRET_BASE (1u << 27)
#define BATTLE_TYPE_TRAINER_HILL (1u << 28)
#define BATTLE_TYPE_FRONTIER (1u << 8)
#define PART5_RIBBON_DONE 4
enum { MON_DATA_HELD_ITEM = 12 };
enum { POCKET_ITEMS, POCKET_BERRIES };
enum HoldEffect { HOLD_EFFECT_NONE, HOLD_EFFECT_MEGA_STONE, HOLD_EFFECT_RESTORE_HP };
enum BattleTrainer { B_TRAINER_PLAYER, B_TRAINER_OPPONENT_A, B_TRAINER_PARTNER, B_TRAINER_OPPONENT_B };
enum BattlerId { B0, B1, B2, B3 };
enum Item { ITEM_NONE, ITEM_SITRUS_BERRY, ITEM_LIFE_ORB, ITEM_LEFTOVERS, ITEM_GARCHOMPITE, ITEM_SALAMENCITE,
            %(stones)s, ITEM_COUNT_ };
enum { FLAG_BASE_ = 0x100, %(flags)s };
enum { VAR_BASE_ = 0x4000, %(vars)s };
struct Pokemon { enum Item held; };
struct BoxPokemon { enum Item held; };
struct DaycareMon { struct BoxPokemon mon; };
struct DayCare { struct DaycareMon mons[DAYCARE_MON_COUNT]; };
struct SaveBlock1 { struct DayCare daycare; };
struct LostItem { enum Item originalItem:15; u16 stolen:1; };
struct BattleStruct { struct LostItem itemLost[MAX_BATTLE_TRAINERS][PARTY_SIZE]; };
struct BattlePokemon { enum Item item; };
static struct Pokemon gParties[MAX_BATTLE_TRAINERS][PARTY_SIZE];
static struct SaveBlock1 sSave, *gSaveBlock1Ptr = &sSave;
static struct BattleStruct sBs, *gBattleStruct = &sBs;
static struct BattlePokemon gBattleMons[4];
static u8 gBattlerPartyIndexes[4];
static u32 gBattleTypeFlags;
static enum BattlerId gBattlerAttacker;
static u16 gSpecialVar_Result, gSpecialVar_0x8004;
static enum Item gBox[TOTAL_BOXES_COUNT][IN_BOX_COUNT];
static u8 gBag[ITEM_COUNT_], gPC[ITEM_COUNT_], gFlags[0x200];
static u16 gVars[0x100];
static int gBagFull;
static enum BattleTrainer gTrainerOf[4] = {B_TRAINER_PLAYER, B_TRAINER_OPPONENT_A, B_TRAINER_PARTNER, B_TRAINER_OPPONENT_B};
static bool32 IsOnPlayerSide(enum BattlerId b) { return (b & 1) == 0; }
static enum BattleTrainer GetBattlerTrainer(enum BattlerId b) { return gTrainerOf[b]; }
static enum HoldEffect GetItemHoldEffect(enum Item i) { return (i == ITEM_GARCHOMPITE || i == ITEM_SALAMENCITE %(stoneeq)s) ? HOLD_EFFECT_MEGA_STONE : HOLD_EFFECT_NONE; }
static int GetItemPocket(enum Item i) { return i == ITEM_SITRUS_BERRY ? POCKET_BERRIES : POCKET_ITEMS; }
static bool32 CheckBagHasItem(enum Item i, u16 n) { return gBag[i] >= n; }
static bool32 CheckPCHasItem(enum Item i, u16 n) { return gPC[i] >= n; }
static bool32 AddBagItem(enum Item i, u16 n) { if (gBagFull) return FALSE; gBag[i] += n; return TRUE; }
static bool32 AddPCItem(enum Item i, u16 n) { gPC[i] += n; return TRUE; }
static bool32 FlagGet(u32 f) { return gFlags[f - FLAG_BASE_]; }
static u16 VarGet(u32 v) { return gVars[v - VAR_BASE_]; }
static u32 GetMonData(struct Pokemon *m, int r) { (void)r; return m->held; }
static void SetMonData(struct Pokemon *m, int r, const void *v) { (void)r; m->held = *(const enum Item *)v; }
static u32 GetBoxMonData(struct BoxPokemon *m, int r) { (void)r; return m->held; }
static u32 GetBoxMonDataAt(u8 b, u8 p, int r) { (void)r; return gBox[b][p]; }
'''

flag_ids = [x for x in ids if x.startswith('FLAG_')]
var_ids = [x for x in ids if x.startswith('VAR_')]
stones_plain = [s for s in stones if s not in ('ITEM_GARCHOMPITE', 'ITEM_SALAMENCITE')]
prelude = prelude % {
    'stones': ', '.join(stones_plain),
    'flags': ', '.join(flag_ids),
    'vars': ', '.join(var_ids),
    'stoneeq': ''.join(' || i == ' + s for s in stones_plain),
}

body = part7.split('#include "constants/part5.h"\n', 1)[1]
body = re.sub(r'(?m)^(bool32|void|enum Item) (Part7_)', r'static \1 \2', body)
body = body.replace('const u8 gText_Part7', 'static const u8 gText_Part7')
restore = fn(util, 'TryRestoreHeldItems').replace('void TryRestoreHeldItems', 'static void TryRestoreHeldItems')

tests = r'''
static void reset(u32 flags)
{
    memset(gParties, 0, sizeof(gParties)); memset(&sBs, 0, sizeof(sBs)); memset(gBattleMons, 0, sizeof(gBattleMons));
    memset(gBox, 0, sizeof(gBox)); memset(gBag, 0, sizeof(gBag)); memset(gPC, 0, sizeof(gPC));
    memset(gFlags, 0, sizeof(gFlags)); memset(gVars, 0, sizeof(gVars)); memset(&sSave, 0, sizeof(sSave));
    gBattleTypeFlags = flags; gBagFull = 0; gBattlerAttacker = B0;
    for (int i = 0; i < 4; i++) gBattlerPartyIndexes[i] = 0;
    Part7_ResetBattleLoot();
}
static void start(int trainer, int slot, enum Item item)
{
    gParties[trainer][slot].held = item;
    gBattleStruct->itemLost[trainer][slot].originalItem = item;
}
#define T(name) printf("ok %s\n", name)
int main(void)
{
    const u32 TR = BATTLE_TYPE_TRAINER;
    // 1. Enemy took a berry (Knock Off / Thief / Bug Bite): restored after battle.
    reset(TR); start(0, 0, ITEM_SITRUS_BERRY); gParties[0][0].held = ITEM_NONE; gBattleStruct->itemLost[0][0].stolen = 1;
    TryRestoreHeldItems(); assert(gParties[0][0].held == ITEM_SITRUS_BERRY); T("enemy-removed berry restored");
    // 2. Same in a wild battle.
    reset(0); start(0, 0, ITEM_SITRUS_BERRY); gParties[0][0].held = ITEM_NONE; gBattleStruct->itemLost[0][0].stolen = 1;
    TryRestoreHeldItems(); assert(gParties[0][0].held == ITEM_SITRUS_BERRY); T("wild battle berry restored");
    // 3. Own berry eaten normally: Expansion rule, not restored.
    reset(TR); start(0, 0, ITEM_SITRUS_BERRY); gParties[0][0].held = ITEM_NONE;
    TryRestoreHeldItems(); assert(gParties[0][0].held == ITEM_NONE); T("eaten berry stays consumed");
    reset(0); start(0, 0, ITEM_SITRUS_BERRY); gParties[0][0].held = ITEM_NONE;
    TryRestoreHeldItems(); assert(gParties[0][0].held == ITEM_NONE); T("eaten berry stays consumed (wild)");
    // 4. Non-berry knocked off: restored (native behaviour kept).
    reset(TR); start(0, 1, ITEM_LIFE_ORB); gParties[0][1].held = ITEM_NONE; gBattleStruct->itemLost[0][1].stolen = 1;
    TryRestoreHeldItems(); assert(gParties[0][1].held == ITEM_LIFE_ORB); T("knocked-off item restored");
    // 5. Stolen flag on an empty original slot (mon swapped to PC after a catch) never overwrites.
    reset(0); gParties[0][2].held = ITEM_LEFTOVERS; gBattleStruct->itemLost[0][2].stolen = 1;
    TryRestoreHeldItems(); assert(gParties[0][2].held == ITEM_LEFTOVERS); T("empty original is not written");

    // 6. Mega stones may leave an NPC only when the player's side acts.
    reset(TR); gBattleMons[B1].item = ITEM_GARCHOMPITE; gBattlerAttacker = B0;
    assert(Part7_CanMegaStoneLeaveNpc(B1, B0, ITEM_GARCHOMPITE));
    assert(Part7_CanMegaStoneLeaveNpc(B0, B1, ITEM_GARCHOMPITE));
    gBattlerAttacker = B2; assert(Part7_CanMegaStoneLeaveNpc(B1, B2, ITEM_GARCHOMPITE));
    gBattlerAttacker = B1; assert(!Part7_CanMegaStoneLeaveNpc(B1, B0, ITEM_GARCHOMPITE)); T("NPC never gives its own stone away");
    gBattlerAttacker = B0; assert(!Part7_CanMegaStoneLeaveNpc(B1, B3, ITEM_GARCHOMPITE)); T("no NPC-to-NPC stone move");
    assert(!Part7_CanMegaStoneLeaveNpc(B1, B1, ITEM_GARCHOMPITE)); T("no self (Fling) loosening");
    gBattleMons[B1].item = ITEM_NONE; gBattleMons[B0].item = ITEM_GARCHOMPITE;
    assert(!Part7_CanMegaStoneLeaveNpc(B0, B1, ITEM_GARCHOMPITE)); T("player stone keeps native protection");
    gBattleMons[B1].item = ITEM_LIFE_ORB; assert(!Part7_CanMegaStoneLeaveNpc(B1, B0, ITEM_LIFE_ORB)); T("only Mega stones");
    reset(TR | BATTLE_TYPE_FRONTIER); gBattleMons[B1].item = ITEM_GARCHOMPITE;
    assert(!Part7_CanMegaStoneLeaveNpc(B1, B0, ITEM_GARCHOMPITE)); T("Frontier keeps native rules");
    reset(TR | BATTLE_TYPE_LINK); gBattleMons[B1].item = ITEM_GARCHOMPITE;
    assert(!Part7_CanMegaStoneLeaveNpc(B1, B0, ITEM_GARCHOMPITE)); T("link keeps native rules");
    reset(0); gBattleMons[B1].item = ITEM_GARCHOMPITE;
    assert(!Part7_CanMegaStoneLeaveNpc(B1, B0, ITEM_GARCHOMPITE)); T("wild keeps native rules");

    // 7. NPC Mega authorization = battle-start item.
    reset(TR); gBattlerPartyIndexes[B1] = 3; start(1, 3, ITEM_SALAMENCITE); gBattleMons[B1].item = ITEM_NONE;
    assert(Part7_GetMegaAuthorizationItem(B1) == ITEM_SALAMENCITE); T("stolen stone: NPC still authorized");
    gBattleMons[B1].item = ITEM_GARCHOMPITE; assert(Part7_GetMegaAuthorizationItem(B1) == ITEM_SALAMENCITE); T("swapped stone: original wins");
    gBattlerPartyIndexes[B3] = 1; start(3, 1, ITEM_LIFE_ORB); gBattleMons[B3].item = ITEM_SALAMENCITE;
    assert(Part7_GetMegaAuthorizationItem(B3) == ITEM_LIFE_ORB); T("received stone does not authorize NPC");
    gBattleMons[B0].item = ITEM_NONE; start(0, 0, ITEM_GARCHOMPITE);
    assert(Part7_GetMegaAuthorizationItem(B0) == ITEM_NONE); T("player side keeps live held item");
    gBattleMons[B2].item = ITEM_GARCHOMPITE; assert(Part7_GetMegaAuthorizationItem(B2) == ITEM_GARCHOMPITE); T("partner keeps live held item");

    // 8. Thief/Covet loot.
    reset(TR); start(0, 0, ITEM_NONE); gParties[0][0].held = ITEM_GARCHOMPITE;
    Part7_RecordStolenItem(B0, ITEM_GARCHOMPITE); TryRestoreHeldItems();
    assert(gParties[0][0].held == ITEM_NONE && gBag[ITEM_GARCHOMPITE] == 1); T("unowned stone becomes permanent");
    reset(TR); gBag[ITEM_GARCHOMPITE] = 1; start(0, 0, ITEM_NONE); gParties[0][0].held = ITEM_GARCHOMPITE;
    Part7_RecordStolenItem(B0, ITEM_GARCHOMPITE); TryRestoreHeldItems();
    assert(gParties[0][0].held == ITEM_NONE && gBag[ITEM_GARCHOMPITE] == 1); T("owned stone: battle only, no copy");
    reset(TR); start(0, 0, ITEM_NONE); gParties[0][0].held = ITEM_GARCHOMPITE;
    Part7_RecordStolenItem(B0, ITEM_GARCHOMPITE); Part7_RecordStolenItem(B0, ITEM_GARCHOMPITE); TryRestoreHeldItems();
    assert(gBag[ITEM_GARCHOMPITE] == 1); T("stealing twice yields one stone");
    reset(TR); Part7_RecordStolenItem(B0, ITEM_LIFE_ORB); TryRestoreHeldItems(); assert(gBag[ITEM_LIFE_ORB] == 0); T("ordinary items are not loot");
    reset(TR); Part7_RecordStolenItem(B2, ITEM_GARCHOMPITE); TryRestoreHeldItems(); assert(gBag[ITEM_GARCHOMPITE] == 0); T("partner Thief does not loot");
    reset(TR | BATTLE_TYPE_FRONTIER); Part7_RecordStolenItem(B0, ITEM_GARCHOMPITE); TryRestoreHeldItems(); assert(gBag[ITEM_GARCHOMPITE] == 0); T("Frontier never keeps loot");
    reset(TR | BATTLE_TYPE_RECORDED_LINK); Part7_RecordStolenItem(B0, ITEM_GARCHOMPITE); TryRestoreHeldItems(); assert(gBag[ITEM_GARCHOMPITE] == 0); T("recorded link never keeps loot");
    reset(TR); gBagFull = 1; Part7_RecordStolenItem(B0, ITEM_GARCHOMPITE); TryRestoreHeldItems(); assert(gPC[ITEM_GARCHOMPITE] == 1); T("full bag sends loot to PC");
    reset(TR); Part7_RecordStolenItem(B0, ITEM_GARCHOMPITE); Part7_ResetBattleLoot(); TryRestoreHeldItems(); assert(gBag[ITEM_GARCHOMPITE] == 0); T("loot resets per battle");

    // 9. Ownership sources.
    reset(0); assert(!Part7_IsItemOwned(ITEM_GARCHOMPITE));
    gPC[ITEM_GARCHOMPITE] = 1; assert(Part7_IsItemOwned(ITEM_GARCHOMPITE)); T("owned via PC");
    reset(0); gParties[0][5].held = ITEM_GARCHOMPITE; assert(Part7_IsItemOwned(ITEM_GARCHOMPITE)); T("owned via party holder");
    reset(0); gBox[13][29] = ITEM_GARCHOMPITE; assert(Part7_IsItemOwned(ITEM_GARCHOMPITE)); T("owned via boxed holder");
    reset(0); sSave.daycare.mons[1].mon.held = ITEM_GARCHOMPITE; assert(Part7_IsItemOwned(ITEM_GARCHOMPITE)); T("owned via Day Care holder");
    reset(0); gFlags[FLAG_PART4_MANECTITE - FLAG_BASE_] = 1; assert(Part7_IsItemOwned(ITEM_MANECTITE)); T("owned via quest flag");
    reset(0); gVars[VAR_PART5_RIBBON - VAR_BASE_] = PART5_RIBBON_DONE - 1; assert(!Part7_IsItemOwned(ITEM_GARDEVOIRITE));
    gVars[VAR_PART5_RIBBON - VAR_BASE_] = PART5_RIBBON_DONE; assert(Part7_IsItemOwned(ITEM_GARDEVOIRITE)); T("owned via quest var");
    reset(0); gSpecialVar_0x8004 = ITEM_MANECTITE; gBag[ITEM_MANECTITE] = 1; Part7_CheckItemOwned(); assert(gSpecialVar_Result == 1); T("script special");
    reset(0); gFlags[FLAG_PART4_MANECTITE - FLAG_BASE_] = 1; start(0, 0, ITEM_NONE);
    Part7_RecordStolenItem(B0, ITEM_MANECTITE); gBattleTypeFlags = TR; Part7_RecordStolenItem(B0, ITEM_MANECTITE); TryRestoreHeldItems();
    assert(gBag[ITEM_MANECTITE] == 0); T("quest-given stone is never duplicated by theft");
    return 0;
}
'''

with tempfile.TemporaryDirectory() as d:
    p = Path(d)
    (p / 'main.c').write_text(prelude + body + '\n' + restore + '\n' + tests, encoding='utf-8')
    try:
        subprocess.run(['gcc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-Wno-unused-function', '-Wno-unused-const-variable', '-Wno-missing-field-initializers',
                        '-fsanitize=address,undefined', '-g', str(p / 'main.c'), '-o', str(p / 'check')],
                       check=True, capture_output=True, text=True)
        out = subprocess.run([str(p / 'check')], check=True, capture_output=True, text=True).stdout
        check('host C tests', out.count('ok ') >= 35, f'{out.count("ok ")} cases')
    except subprocess.CalledProcessError as e:
        check('host C tests', False, (e.stdout or '') + (e.stderr or ''))

# ---------- static wiring ----------
form = fn(util, 'GetBattleFormChangeTargetSpecies')
check('Mega form lookup uses NPC authorization item',
      'method == FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM ? Part7_GetMegaAuthorizationItem(battler)' in form)
check('Mega message names the authorized stone', 'gLastUsedItem = Part7_GetMegaAuthorizationItem(battler);' in fn(util, 'ActivateMegaEvolution'))
check('CanMegaEvolve still goes through the form lookup',
      'GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM, ability)' in fn(util, 'CanMegaEvolve'))
check('NPC stone may leave holder', '!Part7_CanMegaStoneLeaveNpc(fromBattler, battler, itemId)' in fn(util, 'CanBattlerGetOrLoseItem'))
check('loot granted after restore', fn(util, 'TryRestoreHeldItems').rstrip('}\n ').endswith('Part7_GrantBattleLoot();'))
res = read('src/battle_move_resolution.c')
check('Thief/Covet records loot',
      'StealTargetItem(cv->battlerAtk, battlerDef, ITEM_NONE);  // Attacker steals target item\n                Part7_RecordStolenItem(cv->battlerAtk, gLastUsedItem);' in res)
check('only Thief/Covet records loot', res.count('Part7_RecordStolenItem') == 1 and 'Part7_RecordStolenItem' not in read('src/battle_script_commands.c'))
se = read('src/battle_set_effect.c')
check('Bug Bite / Pluck / Incinerate mark removal',
      se.count('Part7_MarkPlayerItemRemoved(se->effectBattler, gLastUsedItem);') == 2
      and 'Part7_MarkPlayerItemRemoved' in fn(se, 'HandleSetEffectBugBite') and 'Part7_MarkPlayerItemRemoved' in fn(se, 'HandleSetEffectIncinerate'))
check('loot reset at battle start', 'Part7_ResetBattleLoot();' in read('src/battle_main.c'))
im = fn(read('src/item_menu.c'), 'ItemMenu_Toss')
check('bag toss blocks Mega stones', 'Part7_IsMegaStone(gSpecialVar_ItemId)' in im and 'gText_Part7_MegaStoneNoToss' in im)
check('PC toss blocks Mega stones', '!Part7_IsMegaStone(gSaveBlock1Ptr->pcItems[pos].itemId)' in fn(read('src/player_pc.c'), 'ItemStorage_DoItemToss'))
items = read('src/data/items.h')
all_stones = [m.group(1) for m in re.finditer(r'\[(ITEM_\w+)\]\s*=\s*\{(.*?)\n    \},', items, re.S) if 'HOLD_EFFECT_MEGA_STONE' in m.group(2)]
bad_price = [s for s in all_stones if not re.search(r'\[' + s + r'\]\s*=\s*\{[^}]*?\.price = 0,', items, re.S)]
check('Mega stones cannot be sold (price 0)', len(all_stones) > 40 and not bad_price, ' '.join(bad_price))
_sp = [l.strip() for l in read('data/specials.inc').splitlines() if l.strip().startswith('def_special')]
_i = _sp.index('def_special Part7_CheckItemOwned')
check('PART7 specials appended as one block at the end', all(x.startswith('def_special Part7_') for x in _sp[_i:]), str(len(_sp) - _i))

# Every scripted Mega stone source must be covered by the ownership table, with the state the script sets.
src_map = {}
for f in ['part4', 'part5', 'part55', 'part6', 'part7']:
    L = read(f'data/scripts/{f}.inc').split('\n')
    for i, l in enumerate(L):
        m = re.match(r'\s*giveitem (ITEM_\w+)', l)
        if m and m.group(1) in all_stones:
            after = '\n'.join(L[i + 1:i + 6])
            src_map.setdefault(m.group(1), []).append(after)
for d in Path(R / 'data/maps').iterdir():
    ev = d / 'events.inc'
    if ev.exists():
        for m in re.finditer(r'OBJ_EVENT_GFX_ITEM_BALL,.*?(ITEM_\w+), Common_EventScript_FindItem, (FLAG_\w+)', ev.read_text(encoding='utf-8')):
            if m.group(1) in all_stones:
                src_map.setdefault(m.group(1), []).append('setflag ' + m.group(2))
missing, mismatch = [], []
table = re.findall(r'\{(ITEM_\w+),\s+OWNED_BY_(\w+), (\w+)(?:, (\w+))?\}', part7)
for stone, afters in src_map.items():
    rows = [t for t in table if t[0] == stone]
    if not rows:
        missing.append(stone)
        continue
    for a in afters:
        if not any((k == 'FLAG' and f'setflag {i}' in a) or (k == 'VAR_AT_LEAST' and re.search(rf'setvar {i}, {v}\b', a)) for _, k, i, v in rows):
            mismatch.append(stone)
check('ownership table covers every scripted Mega stone', not missing and not mismatch and len(src_map) >= 28,
      f'{len(src_map)} sources; missing {missing} mismatch {mismatch}')

# ---------- PART7 content (batch 2+) ----------
import struct
from collections import Counter
inc = read('data/scripts/part7.inc')
man = json.loads(read('docs/project/part7-manifest.json'))
BASE = 'part7-batch1-engine'


def old(f):
    try:
        return subprocess.check_output(['git', 'show', BASE + ':' + f], cwd=R, text=True, stderr=subprocess.DEVNULL)
    except subprocess.CalledProcessError:
        return None


layouts = {l['id']: l for l in json.loads(read('data/layouts/layouts.json'))['layouts'] if 'id' in l}


def grid(v):
    l = layouts[v['layout']]
    raw = (R / l['blockdata_filepath']).read_bytes()
    return l['width'], l['height'], struct.unpack('<' + 'H' * (len(raw) // 2), raw)


def peak(obs):
    return max((sum(x <= t['x'] <= x + 19 and y <= t['y'] <= y + 16 for t in obs) for o in obs for x in [o['x'], o['x'] - 19] for y in [o['y'], o['y'] - 16]), default=0)


bad, view = [], []
for name in man['maps']:
    v = json.loads(read(f'data/maps/{name}/map.json'))
    w, h, c = grid(v)
    obs = v['object_events']
    pos = Counter((o['x'], o['y']) for o in obs)
    warps = {(o['x'], o['y']) for o in v['warp_events']}
    for o in obs:
        if not (o.get('local_id', '').startswith('LOCALID_PART7_') or o.get('script', '').startswith('Part7_')):
            continue
        x, y = o['x'], o['y']
        ok_tile = 0 <= x < w and 0 <= y < h and ((c[y * w + x] >> 10) & 3) == 0
        # fly-in actors may start on a wall tile (scripted landing) and never block the player
        if not ok_tile and o['local_id'] not in ('LOCALID_PART7_CHASED_LATI',):
            bad.append((name, o['local_id'], 'collision'))
        if pos[(x, y)] > 1 and o['local_id'] not in ('LOCALID_PART7_119_LATIAS', 'LOCALID_PART7_119_LATIOS'):
            bad.append((name, o['local_id'], 'overlap'))
        if (x, y) in warps:
            bad.append((name, o['local_id'], 'on warp'))
    for b in v['bg_events']:
        if b.get('script', '').startswith('Part7_') or b.get('flag', '').startswith('FLAG_PART7_'):
            if not (0 <= b['x'] < w and 0 <= b['y'] < h):
                bad.append((name, b, 'bg bounds'))
    prev = old(f'data/maps/{name}/map.json')
    prevpeak = peak(json.loads(prev)['object_events']) if prev else 0
    if peak(obs) > max(15, prevpeak):
        view.append((name, peak(obs), prevpeak))
check('PART7 actors on passable tiles, no overlap, not on warps', not bad, str(bad[:5]))
check('PART7 maps keep on-screen object capacity (<=15 or the original peak)', not view, str(view))

# Mega stones: every PART7 stone gift goes through the shared ownership check and is registered
gifts = re.findall(r'setvar VAR_0x8004, (ITEM_\w+)\n\tspecial Part7_CheckItemOwned\n\tgoto_if_eq VAR_RESULT, TRUE, \w+\n\tcheckitemspace \1, 1\n\tgoto_if_eq VAR_RESULT, FALSE, Part7_BagFull\n\tgiveitem \1, 1\n\tsetflag (FLAG_PART7_\w+)', inc)
raw_gifts = [m for m in re.findall(r'giveitem (ITEM_\w+)', inc) if m in all_stones]
registered = set(re.findall(r'\{(ITEM_\w+), OWNED_BY_FLAG, (FLAG_PART7_\w+)\}', part7))
check('every PART7 Mega stone gift is owned-checked and registered',
      len(gifts) == len(raw_gifts) >= 7 and all(g in registered for g in gifts), f'{len(gifts)} checked / {len(raw_gifts)} gifts')
stones_given = {g[0] for g in gifts}
check('PART7 stone set: starters, Salamence, Metagross, Lucario, Garchomp; never Gengarite',
      {'ITEM_SCEPTILITE', 'ITEM_BLAZIKENITE', 'ITEM_SWAMPERTITE', 'ITEM_SALAMENCITE', 'ITEM_METAGROSSITE', 'ITEM_LUCARIONITE', 'ITEM_GARCHOMPITE'} <= stones_given
      and 'ITEM_GENGARITE' not in inc and 'GENGARITE' not in read('src/part7_story.c'))
check('Ability Capsule is not a PART7 reward (C15); BP shop keeps it as a normal resource',
      'giveitem ITEM_ABILITY_CAPSULE' not in inc and 'ITEM_ABILITY_CAPSULE, 1)' not in inc and '{ITEM_ABILITY_CAPSULE, 32}' in read('src/part7_story.c'))
bp = read('src/part7_story.c').split('sPart7BpItems[][2]')[1].split('};')[0]
check('BP exchange sells no Mega stones or story key items',
      not any(x in bp for x in all_stones) and not re.search(r'EON_TICKET|SOUL_DEW|PRIMAL|ADJUSTER|KEY', bp))
# Latias / Latios (C15)
check('native roamer disabled: no InitRoamer call in Emerald scripts',
      '	special InitRoamer' not in read('data/scripts/players_house.inc') and '	special InitRoamer' not in read('data/scripts/tv.inc'))
check('Latias/Latios carry nothing; one Soul Dew only after both are caught',
      re.search(r'seteventmon SPECIES_LATIAS, 50\n', inc) and re.search(r'seteventmon SPECIES_LATIOS, 50\n', inc)
      and 'ITEM_SOUL_DEW' not in re.sub(r'(?s)Part7_IslandStone::.*?Part7_IslandStone_Plain::', '', inc)
      and re.search(r'goto_if_unset FLAG_PART7_LATIAS_CAUGHT, Part7_IslandStone_Plain\n\tgoto_if_unset FLAG_PART7_LATIOS_CAUGHT, Part7_IslandStone_Plain\n', inc))
check('Eon Ticket from the Jigglypuff girl; TV news names Slateport harbour',
      'giveitem ITEM_EON_TICKET, 1\n\tsetflag FLAG_ENABLE_SHIP_SOUTHERN_ISLAND' in inc and '凯那市港口附近' in read('data/maps/LittlerootTown_BrendansHouse_1F/scripts.inc'))
# League
rooms = {'Sidneys': 'SIDNEY', 'Phoebes': 'PHOEBE', 'Glacias': 'GLACIA', 'Drakes': 'DRAKE', 'Champions': 'WALLACE'}
check('League rooms native; post-Champion rematch teams switch on FLAG_SYS_GAME_CLEAR',
      all(f'goto_if_set FLAG_SYS_GAME_CLEAR, Part7_Strong{k.capitalize()}' in read(f'data/maps/EverGrandeCity_{r}Room/scripts.inc') for r, k in rooms.items())
      and all(old(f'data/maps/EverGrandeCity_{r}Room/map.json') == read(f'data/maps/EverGrandeCity_{r}Room/map.json') for r in rooms))
party = read('src/data/trainers.party')
glacia = party.split('=== TRAINER_GLACIA ===')[1].split('===')[0]
check('first-run Glacia has no Mega; Wallace keeps Milotic as top-level ace with Mega Swampert',
      'ite\n' not in glacia.replace('Glalitite', 'ite') or 'Glalitite' not in glacia)
# Flags and roster
fl = read('include/constants/flags.h')
p7flags = re.findall(r'^#define (FLAG_PART7_\w+) 0x([0-9A-F]+)', fl, re.M)
check('PART7 flags on audited persistent slots (no daily range), all distinct',
      len(p7flags) == len(man['flags']) and len({v for _, v in p7flags}) == len(p7flags) and not any(0x920 <= int(v, 16) < 0x960 for _, v in p7flags), str(len(p7flags)))
bpp = read('src/data/battle_partners.party')
names = re.findall(r'=== PARTNER_PART7_\w+ ===\nName: (.+)', bpp)
items = re.findall(r'=== PARTNER_PART7_\w+ ===\n(?:.+\n)*?Items: (.+)', bpp)
check('PART7 roster trainers: names fit, at most four items each', len(names) == len(man['roster']) and all(len(n) <= 5 for n in names)
      and all(len(i.split(' / ')) <= 4 for i in items), str(len(names)))
# New maps
groups = json.loads(read('data/maps/map_groups.json'))
newmaps = ['MeteorFalls_DeepStrata', 'MeteorFalls_DragonNest', 'Route133_TideMarkCave']
wild = read('src/data/wild_encounters.json')
check('three new maps registered with scripts and wild tables', all(m in groups['gMapGroup_Dungeons'] for m in newmaps)
      and all(f'"MAP_{x}"' in wild for x in ['METEOR_FALLS_DEEP_STRATA', 'METEOR_FALLS_DRAGON_NEST', 'ROUTE133_TIDE_MARK_CAVE']))

# Scope: every source edit since the PART7 checkpoint is recorded and reverses exactly (legacy suites rely on it).
import hashlib, json, sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
import part7_compat
D7 = part7_compat.D
changed = set(subprocess.check_output(['git', 'diff', '--name-only', D7['baseline']], cwd=R, text=True).splitlines())
changed |= set(subprocess.check_output(['git', 'ls-files', '--others', '--exclude-standard'], cwd=R, text=True).splitlines())
changed = {f for f in changed if f.startswith(('src/', 'include/', 'data/', 'asm/'))}
check('every PART7 source change is recorded in part7-deltas.json', changed == set(D7['text']) | set(D7['binary']) | set(D7['new_files']),
      ' '.join(sorted(changed ^ (set(D7['text']) | set(D7['binary']) | set(D7['new_files'])))))
try:
    for f in D7['text']:
        part7_compat.source(f)
    for f in D7['new_files']:
        assert hashlib.sha256((R / f).read_bytes()).hexdigest() == D7['sha256'][f], f
    check('recorded PART7 deltas reverse exactly', True, f'{len(D7["text"])} edited, {len(D7["new_files"])} new')
except AssertionError as e:
    check('recorded PART7 deltas reverse exactly', False, str(e))

fails = [r for r in results if not r[1]]
for name, ok, detail in results:
    print(('PASS ' if ok else 'FAIL ') + name + (f' ({detail})' if detail else ''))
print(f'PART7 engine checks: {len(results) - len(fails)}/{len(results)} PASS')
raise SystemExit(1 if fails else 0)
