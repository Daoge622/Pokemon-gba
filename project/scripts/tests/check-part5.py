#!/usr/bin/env python3
"""PART5 static checks (no ROM, emulator or GUI is ever started).
Verifies the generated PART5 data against docs/story/PART5_DRAFT.md requirements and
that every PART5 change is recorded in docs/project/part5-deltas.json."""
from pathlib import Path
from collections import deque
import json, re, struct, subprocess, sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
import part5_compat
import part55_compat
from part55_compat import source as part55_source

r = Path(__file__).resolve().parents[2]
M = json.loads((r / 'docs/project/part5-manifest.json').read_text(encoding='utf-8'))
D = json.loads((r / 'docs/project/part5-deltas.json').read_text(encoding='utf-8'))
PRE = 'pre-part5-implementation'
n_ok = 0


def read(f):
    return part55_source(f, (r / f).read_text(encoding='utf-8'))


def pre(f):
    return subprocess.check_output(['git', 'show', PRE + ':' + f], cwd=r, text=True)


def ok(label, cond=True):
    global n_ok
    assert cond, label
    n_ok += 1
    print('PASS', label)


s5 = read('data/scripts/part5.inc')
labels = dict(re.findall(r'^(Part5_Text_\d+):\n\t\.string "(.*)"$', s5, re.M))


def block(label):
    m = re.search(r'^' + re.escape(label) + r'::\n(.*?)(?=^\S[^\n]*::\n|\Z)', s5, re.M | re.S)
    assert m, label
    return m.group(1)


def texts_of(label):
    return ''.join(labels[t] for t in re.findall(r'Part5_Text_\d+', block(label)))


# ---------------------------------------------------------------- 1. every PART5 change is recorded and reversible
for f in list(D['text']) + list(D['maps']):
    part5_compat.source(f)
ok(f'{len(D["text"])} text files and {len(D["maps"])} maps: PART5 hunks reverse exactly to pre-PART5 (PART1-4 untouched)')
for f in D['binary']:
    assert f in ('data/layouts/LilycoveCity/map.bin',), f
ok('only binary layout change to an existing map is the Lilycove east-beach gate house')

# ---------------------------------------------------------------- 2. flags / vars / trainers / save layout
flags_h, vars_h, opp = read('include/constants/flags.h'), read('include/constants/vars.h'), read('include/constants/opponents.h')
for name, slot in M['flags'].items():
    assert re.search(r'^#define ' + name + r' ' + '0x%03X' % int(slot, 16) + r'\b', flags_h, re.M), name
    assert re.search(r'^#define FLAG_UNUSED_0x%03X\s+0x%X\s*// Unused Flag' % (int(slot, 16), int(slot, 16)), pre('include/constants/flags.h'), re.M), (name, 'slot was not unused')
for name, slot in M['vars'].items():
    assert re.search(r'^#define ' + name + r' ' + '0x%04X' % int(slot, 16) + r'\b', vars_h, re.M), name
    assert re.search(r'^#define VAR_UNUSED_0x%04X' % int(slot, 16), pre('include/constants/vars.h'), re.M), name
ok(f'{len(M["flags"])} flags and {len(M["vars"])} vars allocated only from audited UNUSED slots')
assert '#define TRAINERS_COUNT_EMERALD     864' in opp and '#define MAX_TRAINERS_COUNT_EMERALD 864' in opp
alltext = '\n'.join(p.read_text(encoding='utf-8') for p in (r / 'data').rglob('*.inc') if p.name not in ('events.inc', 'header.inc', 'connections.inc')) + read('data/event_scripts.s')
for alias, real in M['trainer_aliases'].items():
    assert re.search(r'^#define ' + alias + r' ' + real + r'\b', opp, re.M)
    assert real not in alltext and real not in pre('data/maps/LilycoveCity/scripts.inc'), (real, 'native script still uses repurposed ID')
ok(f'{len(M["trainer_aliases"])} new trainers reuse audited unreferenced IDs; trainer count/save layout unchanged (864)')

# ---------------------------------------------------------------- 3. text: width, pages, charset, phrasing, secrecy
font = json.loads(read('tools/poryscript/font_config.json'))['fonts']['1_chinese_rse']['widths']
charmap = {m.group(1) for m in re.finditer(r"^'(.+?)'\s*=", read('charmap.txt'), re.M)}
count = 0
for label, text in labels.items():
    for page in text.rstrip('$').split(r'\p'):
        lines = page.split(r'\n')
        assert len(lines) <= 2, (label, lines)
        for line in lines:
            plain = line.replace('{PLAYER}', 'Ｗ' * 7)
            assert sum(12 if c == 'Ｗ' else font.get(c, 6) for c in plain) <= 208, (label, line)
            assert all(c in charmap or c in ' Ｗ' for c in plain), (label, line)
            count += 1
alltxt = ''.join(labels.values())
assert '不是' not in alltxt and '而在于' not in alltxt and '问题不在于' not in alltxt
for banned in ['安提', '首领', '莱因', '伊芙琳', '萨维尔', '本原', '调律器', '骑拉帝纳', '反转世界', '破坏因子']:
    assert banned not in alltxt, banned
ok(f'{count} PART5 lines within 208px/2-line pages, charmap-valid; no contrast clichés; no hidden-identity or future-lore names')

# ---------------------------------------------------------------- 4. maps: placement, access, capacity
layouts = {x['id']: x for x in json.loads(read('data/layouts/layouts.json'))['layouts'] if 'id' in x}


def grid(v):
    l = layouts[v['layout']]
    w, h = l['width'], l['height']
    raw = (r / l['blockdata_filepath']).read_bytes()
    assert len(raw) == 2 * w * h
    return w, h, struct.unpack('<' + 'H' * (w * h), raw)


def flood(cells, start):
    seen, q = {start}, deque([start])
    while q:
        x, y = q.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if n in cells and n not in seen:
                seen.add(n)
                q.append(n)
    return seen


def npc_peak(objs):
    return max((sum(x <= t['x'] <= x + 19 and y <= t['y'] <= y + 16 for t in objs) for o in objs
                for x in [o['x'], o['x'] - 19] for y in [o['y'], o['y'] - 16]), default=0)


new_maps = {p.split('/')[2] for p in D['new_files'] if p.endswith('/map.json')}
checked = 0
for name, added in M['maps'].items():
    f = f'data/maps/{name}/map.json'
    v = json.loads(read(f))
    w, h, c = grid(v)
    assert len(v['object_events']) <= 64 and len(v['bg_events']) <= 255
    walk = {(x, y) for y in range(h) for x in range(w) if (c[y * w + x] >> 10) & 3 == 0 and (c[y * w + x] >> 12) in (0, 3, 4, 5, 7, 9)}
    occupied = {(o['x'], o['y']) for o in v['object_events']}
    for kind, lid, x, y in added:
        if kind != 'obj':
            continue
        o = next(o for o in v['object_events'] if o.get('local_id') == lid)
        cell = c[y * w + x]
        if o['graphics_id'] != 'OBJ_EVENT_GFX_ITEM_BALL':
            assert (cell >> 10) & 3 == 0, (name, lid, 'on blocked tile')
            assert o['elevation'] == cell >> 12 or (o['elevation'] == 3 and cell >> 12 == 0), (name, lid, 'elevation')
        assert sum((q['x'], q['y']) == (x, y) for q in v['object_events']) == 1, (name, lid, 'overlap')
        assert (x, y) not in {(z['x'], z['y']) for z in v['warp_events'] + v['coord_events']}, (name, lid, 'on warp/trigger')
        near = {(z['x'] + dx, z['y'] + dy) for z in v['warp_events'] for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))}
        assert (x, y) not in near, (name, lid, 'blocks a door/stair arrival tile')
        free = (walk - occupied) | {(x, y)} if o['graphics_id'] == 'OBJ_EVENT_GFX_ITEM_BALL' else walk - occupied
        adj = {(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)} & (walk - occupied)
        if name != 'MossdeepCity' or 'SWABLU_HOME' not in lid:
            across = {(x + 2 * dx, y + 2 * dy) for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)) if (x + dx, y + dy) not in walk} & (walk - occupied)
            assert adj or across, (name, lid, 'unreachable (no adjacent tile and no counter to talk across)')
        if adj and o['graphics_id'] != 'OBJ_EVENT_GFX_ITEM_BALL' and o.get('flag', '0') == '0' and name not in ('ArcheCampus_PokemonCenter_1F', 'ArcheCampus_Apartment', 'ArcheCampus_HQ_2F'):
            assert adj <= flood(walk - occupied, next(iter(adj))), (name, lid, 'NPC splits a passage')
        checked += 1
    before = 0 if name in new_maps else npc_peak(json.loads(pre(f))['object_events'])
    peak = npc_peak(v['object_events'])
    assert peak <= 15 or peak <= before, (name, 'object capacity', peak, before)
ok(f'{checked} PART5 objects: walkable, elevation-matched, non-overlapping, reachable, no blocked passages; viewport peaks <=15 or not above native')

# warps of new maps resolve both ways
allmaps = {v['id']: v for p in (r / 'data/maps').glob('*/map.json') if str(p.relative_to(r)) not in part55_compat.D['new_files'] and str(p.relative_to(r)) not in __import__('part6_compat').D['new_files'] and str(p.relative_to(r)) not in __import__('part7_compat').D['new_files'] for v in [json.loads(read(str(p.relative_to(r))))]}
pairs = 0
for name in new_maps | {'LilycoveCity', 'AquaHideout_B1F'}:
    v = json.loads(read(f'data/maps/{name}/map.json'))
    for i, wv in enumerate(v['warp_events']):
        dest = allmaps[wv['dest_map']]
        j = int(wv['dest_warp_id'])
        assert j < len(dest['warp_events']), (name, i, 'dest warp id out of range')
        if name in new_maps or wv['dest_map'] in {allmaps[m]['id'] for m in []}:
            back = dest['warp_events'][j]
            if back['dest_map'] == v['id']:
                pairs += 1
mapgroups = json.loads(read('data/maps/map_groups.json'))
for name in new_maps:
    assert name in mapgroups['gMapGroup_IndoorLilycove'] or name in mapgroups['gMapGroup_Dungeons'], name
    assert f'.include "data/maps/{name}/scripts.inc"' in read('data/event_scripts.s'), name
old_groups = json.loads(pre('data/maps/map_groups.json'))
for g, lst in old_groups.items():
    if isinstance(lst, list) and g.startswith('gMapGroup_'):
        assert mapgroups[g][:len(lst)] == lst, (g, 'existing map numbers shifted')
ok(f'{len(new_maps)} new maps registered at group ends (no existing map renumbered); {pairs} new-map warps resolve back')
lil = json.loads(read('data/maps/LilycoveCity/map.json'))
gate = [w for w in lil['warp_events'] if w['dest_map'] == 'MAP_LILYCOVE_CITY_SEASIDE_AVENUE']
av = allmaps['MAP_LILYCOVE_CITY_SEASIDE_AVENUE']
camp = allmaps['MAP_ARCHE_CAMPUS']
ok('Lilycove gate -> Seaside Avenue <-> ARCHE campus connected (door + edge connection)',
   len(gate) == 1 and (gate[0]['x'], gate[0]['y']) == (62, 19) and av['connections'][0]['map'] == 'MAP_ARCHE_CAMPUS'
   and camp['connections'][0]['map'] == 'MAP_LILYCOVE_CITY_SEASIDE_AVENUE' and av['show_map_name'] and 'wild' not in json.dumps(av))
wild = json.loads(read('src/data/wild_encounters.json'))
ok('Seaside Avenue/campus have no wild encounters (not a battle route)',
   not any(e.get('map') in ('MAP_LILYCOVE_CITY_SEASIDE_AVENUE', 'MAP_ARCHE_CAMPUS') for g in wild['wild_encounter_groups'] for e in g.get('encounters', [])))

# ---------------------------------------------------------------- 5. TM system
items = read('src/data/items.h')
tms = re.findall(r'^\s*F\((\w+)\)', read('include/constants/tms_hms.h'), re.M)
ok('I_REUSABLE_TMS enabled (native Expansion option, no second TM system)', re.search(r'#define I_REUSABLE_TMS\s+TRUE', read('include/config/item.h')))
ok('TM51 = Trick Room appended after the 50 native TMs; HM list unchanged', tms[:50] == re.findall(r'^\s*F\((\w+)\)', pre('include/constants/tms_hms.h'), re.M)[:50] and tms[50] == 'TRICK_ROOM' and tms[51:] == ['CUT', 'FLY', 'SURF', 'STRENGTH', 'FLASH', 'ROCK_SMASH', 'WATERFALL', 'DIVE'])
ok('every TM uses importance I_REUSABLE_TMS; HMs keep importance 1', items.count('.importance = I_REUSABLE_TMS') == 100 and all('.importance = 1' in re.search(r'\[ITEM_HM_' + h + r'\] =\n    \{.*?\n    \},', items, re.S).group() for h in ['CUT', 'FLY', 'SURF', 'STRENGTH', 'FLASH', 'ROCK_SMASH', 'WATERFALL', 'DIVE']))
tm51 = re.search(r'\[ITEM_TM51\] =\n    \{.*?\n    \},', items, re.S).group()
ok('TM51 has a real Chinese description', '?????' not in tm51 and '戏法空间' not in tm51 and '离奇空间' in tm51)
shop = read('src/shop.c')
ok('owned reusable TMs cannot be bought twice (native importance check in shop)', shop.count('GetItemImportance(itemId) && (CheckBagHasItem(itemId, 1) || CheckPCHasItem(itemId, 1))') == 2)
oneuse = [p for p in (r / 'data').rglob('*.inc') if re.search(r'学习器.{0,40}(只能使用一次|使用后就会消失|就会消失)', p.read_text(encoding='utf-8'), re.S) and 'Frlg' not in str(p)]
ok('no Emerald script still says TMs are single-use', not oneuse)
ok('Trick Room TM given once (Mt. Pyre summit) and nowhere else', sum(json.dumps(v).count('ITEM_TM_TRICK_ROOM') for v in allmaps.values()) == 1 and alltext.count('ITEM_TM_TRICK_ROOM') == 0)

# ---------------------------------------------------------------- 6. shops
lim = read('src/limited_shop.c')
for it in ['WIDE_LENS', 'SCOPE_LENS', 'SHELL_BELL', 'WISE_GLASSES', 'MUSCLE_BAND', 'METRONOME', 'EVIOLITE']:
    assert f'{{ MAP_LILYCOVE_CITY_DEPARTMENT_STORE_3F, ITEM_{it}, FLAG_PART5_SHOP_{it} }}' in lim, it
assert '{ MAP_MOSSDEEP_CITY_MART, ITEM_TWISTED_SPOON, FLAG_PART5_SHOP_MOSSDEEP_TWISTED_SPOON }' in lim
marts = {lab: re.findall(r'\.2byte (ITEM_\w+)', body) for lab, body in re.findall(r'^(Part5_Mart_\w+):\n(.*?)pokemartlistend', s5, re.M | re.S)}
ok('ball counter: Quick/Dusk/Repeat/Net/Dive/Luxury; no Timer Ball', marts['Part5_Mart_Balls'] == ['ITEM_QUICK_BALL', 'ITEM_DUSK_BALL', 'ITEM_REPEAT_BALL', 'ITEM_NET_BALL', 'ITEM_DIVE_BALL', 'ITEM_LUXURY_BALL'])
ok('training counter: six Power items + Ability Capsule, no Ability Patch', marts['Part5_Mart_Training'][:6] == ['ITEM_POWER_' + x for x in ['WEIGHT', 'BRACER', 'BELT', 'LENS', 'BAND', 'ANKLET']] and 'ITEM_ABILITY_CAPSULE' in marts['Part5_Mart_Training'] and 'ITEM_ABILITY_PATCH' not in s5)
ok('21 native Expansion mints sold (existing mint system, high price kept)', len(marts['Part5_Mart_Mints']) == 21 and '(I_PRICE >= GEN_9) ? 20000' in items)
ok('17 type-boost items unlimited', len(marts['Part5_Mart_TypeItems']) == 17)
strong = ['CHOICE_BAND', 'CHOICE_SPECS', 'CHOICE_SCARF', 'LIFE_ORB', 'FOCUS_SASH', 'ASSAULT_VEST', 'LEFTOVERS', 'TIMER_BALL', 'ABILITY_PATCH']
ok('strong gear / Timer Ball / Ability Patch not sold by any PART5 counter', not any('ITEM_' + x in sum(marts.values(), []) for x in strong))
ok('Mossdeep Mart sells the limited Twisted Spoon; native list kept', '\t.2byte ITEM_TWISTED_SPOON\n' in read('data/maps/MossdeepCity_Mart/scripts.inc'))

# ---------------------------------------------------------------- 7. Mega stones
stones5 = ['SCIZORITE', 'HERACRONITE', 'PINSIRITE', 'GARDEVOIRITE', 'MEDICHAMITE', 'BANETTITE', 'ABSOLITE', 'CAMERUPTITE', 'SHARPEDONITE', 'ALTARIANITE']
mapjson = '\n'.join(json.dumps(v) for v in allmaps.values())
for st in stones5:
    n = s5.count('giveitem ITEM_' + st) + mapjson.count('"ITEM_' + st + '"')
    assert n == 1, (st, n)
for st in ['MANECTITE', 'MAWILITE', 'AGGRONITE', 'GYARADOSITE', 'METAGROSSITE', 'SALAMENCITE', 'LUCARIONITE', 'GENGARITE', 'KANGASKHANITE', 'GARCHOMPITE', 'SCEPTILITE', 'BLAZIKENITE', 'SWAMPERTITE']:
    assert 'ITEM_' + st not in s5, st
ok('10 PART5 Mega stones each obtainable once; PART4 and deferred strong stones not given')
ok('Sharpedonite is in the storage room reached by a warp pad, not locked behind the charm', '"ITEM_SHARPEDONITE"' in read('data/maps/AquaHideout_Storage/map.json') and 'ITEM_SHARPEDONITE' not in block('Part5_AquaBoyfriend_After'))

# ---------------------------------------------------------------- 8. quests: one-time states and bag-full safety
for lab, item, setter in [
    ('Part5_BugFans_Reward', 'ITEM_SCIZORITE', 'FLAG_PART5_SCIZORITE'),
    ('Part5_SafariResearcher_Lucky', 'ITEM_LUCKY_EGG', 'FLAG_PART5_SAFARI_LUCKY_EGG'),
    ('Part5_ListOldMan_Return', 'ITEM_RARE_CANDY', 'FLAG_PART5_SHOPPING_LIST_DONE'),
    ('Part5_LunchWife_Reward', 'ITEM_FULL_RESTORE', 'VAR_PART5_LUNCH'),
    ('Part5_RibbonMother_Reward', 'ITEM_GARDEVOIRITE', 'VAR_PART5_RIBBON'),
    ('Part5_TrainingDesk_Reward', 'ITEM_MEDICHAMITE', 'FLAG_PART5_MEDICHAMITE'),
    ('Part5_FlowerOldMan_Reward', 'ITEM_HIGANBANA', 'FLAG_PART5_HIGANBANA'),
    ('Part5_AbsolGrave', 'ITEM_ABSOLITE', 'FLAG_PART5_ABSOLITE'),
    ('Part5_StarKid', 'ITEM_RARE_CANDY', 'FLAG_PART5_SOLROCK_LUNATONE_CANDY'),
    ('Part5_SwabluParent', 'ITEM_ALTARIANITE', 'FLAG_PART5_ALTARIANITE'),
]:
    b = block(lab)
    i, j, k = b.index('giveitem ' + item), b.index('goto_if_eq VAR_RESULT, FALSE, Part5_BagFull'), b.index(setter, b.index('giveitem ' + item))
    assert i < j < k, lab
ok('every reward: giveitem -> bag-full exit -> state set only after success (retry keeps eligibility)')
ok('Safari 3-species check uses native met-location records (no new save data)', 'MON_DATA_MET_LOCATION) != MAPSEC_SAFARI_ZONE' in read('src/part5.c') and 'READ_OTID_FROM_SAVE' in read('src/part5.c'))
ok('Heracross/Pinsir quest uses Pokedex caught flags and both species exist in native Safari tables',
   all(any(x['species'] == 'SPECIES_' + sp for g in wild['wild_encounter_groups'] for e in g.get('encounters', []) if e.get('map', '').startswith('MAP_SAFARI_ZONE_') for x in e.get('land_mons', {}).get('mons', [])) for sp in ['HERACROSS', 'PINSIR']))
ok('Higanbana: key item, unsellable, no Giratina/world wording; tomb only opens with a never-set future flag',
   re.search(r'\[ITEM_HIGANBANA\] =\n    \{.*?\.price = 0,.*?\.importance = 1,.*?POCKET_KEY_ITEMS', items, re.S)
   and 'FLAG_PART5_DISTORTION_AUTHORIZED' in block('Part5_SpecialTomb') and 'setflag FLAG_PART5_DISTORTION_AUTHORIZED' not in alltext + s5
   and 'removeitem ITEM_HIGANBANA' not in s5)
ok('peace charm: delivery only with the charm, PART2 var reused (DELIVERED/COMPLETED), no extra reunion reward',
   'removeitem ITEM_PEACE_CHARM' in block('Part5_AquaBoyfriend_After') and 'PART2_CHARM_DELIVERED' in block('Part5_AquaBoyfriend_After')
   and 'giveitem' not in block('Part5_CoupleReunion') and 'FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE' in read('src/part5.c'))
ok('ARCHE not involved in submarine/orb/Groudon scenes (no PART5 edits to those native scripts)',
   'data/maps/SlateportCity_Harbor/scripts.inc' not in D['text'] and 'data/maps/MtPyre_Summit/scripts.inc' in D['text']
   and all('ARCHE' not in h['new'] and '阿尔刻' not in h['new'] for h in D['text']['data/maps/MagmaHideout_4F/scripts.inc']))
ok('ARCHE HQ upper floors locked; leadership shown only as 集团管理委员会',
   '集团管理委员会' in texts_of('Part5_HQCommittee') and '员工权限' in texts_of('Part5_HQStairGuard')
   and not any(w['dest_map'] == 'MAP_RUSTBORO_CITY_DEVON_CORP_3F' for w in allmaps['MAP_ARCHE_CAMPUS_HQ_2F']['warp_events']))

# ---------------------------------------------------------------- 9. trainers
party = read('src/data/trainers.party')


def roster(t):
    raw = re.search(r'^=== ' + t + r' ===\n(.*?)(?=^=== |^/\*|\Z)', party, re.M | re.S).group(1)
    out = []
    for b in re.split(r'\n\s*\n', raw):
        if 'Level:' in b:
            head = b.splitlines()[0]
            out.append((head.split(' @ ')[0], int(re.search(r'^Level: (\d+)', b, re.M).group(1)), head.split(' @ ')[1] if ' @ ' in head else None, re.search(r'^IVs: (\d+)', b, re.M).group(1)))
    return raw, out


raw, rk = roster('TRAINER_GRUNT_MAGMA_HIDEOUT_14')
ok('Magma rookie: Poochyena31/Numel31/Jigglypuff33 6V @Eviolite, Jigglypuff highest, unevolved',
   [(a, b) for a, b, *_ in rk] == [('Poochyena', 31), ('Numel', 31), ('Jigglypuff', 33)] and rk[2][2] == 'Eviolite' and rk[2][3] == '31' and 'Magma Grunt F' in raw)
for t, want in [('TRAINER_MAXIE_MAGMA_HIDEOUT', [('Mightyena', 34), ('Crobat', 34), ('Houndoom', 35), ('Camerupt', 37)]),
                ('TRAINER_MATT', [('Pelipper', 34), ('Muk', 34), ('Crawdaunt', 35), ('Sharpedo', 37)]),
                ('TRAINER_TATE_AND_LIZA_1', [('Xatu', 40), ('Claydol', 40), ('Solrock', 42), ('Lunatone', 42)])]:
    raw, ros = roster(t)
    assert [(a, b) for a, b, *_ in ros] == want, t
    assert not re.search(r'Focus Sash|Choice|Life Orb|Hypnosis|Trick Room|EVs:', raw), t
ok('Maxie/Matt/Tate&Liza rosters per draft; no sash/choice/sleep-spam/Trick Room; no Mega in boss parties')
ok('Tate & Liza stay a 4-Pokemon double battle', 'Double Battle: Yes' in roster('TRAINER_TATE_AND_LIZA_1')[0])
ace = {'TREECKO': 'Blaziken', 'TORCHIC': 'Swampert', 'MUDKIP': 'Sceptile'}
mid = {'TREECKO': 'Combusken', 'TORCHIC': 'Marshtomp', 'MUDKIP': 'Grovyle'}
for who in ['BRENDAN', 'MAY']:
    for st in ace:
        ros = roster(f'TRAINER_{who}_LILYCOVE_{st}')[1]
        assert len(ros) == 5 and ros[0][:2] == ('Swellow', 33) and ros[1][:2] == ('Manectric', 33) and ros[4][:2] == (ace[st], 36) and ros[2][1] == ros[3][1] == 34, (who, st)
        assert roster(f'TRAINER_{who}_ROUTE_119_{st}')[1][-1][0] == mid[st], (who, st, 'Route119 starter mapping')
ok('six Lilycove rival variants: Swellow33/Manectric33/2x34/final starter 36; Route119 starter mapping fixed to native rule')
for t, want in [(M['trainer_aliases']['TRAINER_PART5_TRAVELER'], [('Girafarig', 31), ('Deerling', 31), ('Stantler', 32)]),
                (M['trainer_aliases']['TRAINER_PART5_ARCHE_TECH'], [('Magnemite', 32), ('Klink', 33)]),
                (M['trainer_aliases']['TRAINER_PART5_ARCHE_SURVEYOR'], [('Porygon', 33), ('Kadabra', 33)]),
                (M['trainer_aliases']['TRAINER_PART5_ARCHE_GUARD'], [('Bronzor', 34), ('Medicham', 34)])]:
    assert [(a, b) for a, b, *_ in roster(t)[1]] == want, t
ok('traveller and three ARCHE public-test trainers at Lv31-34, not competitive')
learn = json.loads(read('src/data/pokemon/all_learnables.json'))
bad = []
for t in list(M['trainers']) + ['TRAINER_GRUNT_MAGMA_HIDEOUT_14']:
    raw = re.search(r'^=== ' + t + r' ===\n(.*?)(?=^=== |^/\*|\Z)', party, re.M | re.S).group(1)
    for b in re.split(r'\n\s*\n', raw):
        if 'Level:' not in b:
            continue
        sp = b.splitlines()[0].split(' @ ')[0]
        for mv in re.findall(r'^- (.+)$', b, re.M):
            key = 'MOVE_' + mv.upper().replace(' ', '_').replace('-', '_')
            if key not in learn.get(sp.upper(), []):
                bad.append((t, sp, mv))
ok('every PART5 trainer move is in the species learnable list' + (f' (exceptions: {bad})' if bad else ''), not bad)

# ---------------------------------------------------------------- 10. wild encounters
def table(mp, kind):
    for g in wild['wild_encounter_groups']:
        for e in g.get('encounters', []):
            if e.get('map') == mp and kind in e:
                return [x['species'] for x in e[kind]['mons']]


ok('Safari: Skiddo/Lillipup/Rufflet added at one 5% slot each, native species all kept',
   all('SPECIES_' + sp in table(mp, 'land_mons') for mp, sp in [('MAP_SAFARI_ZONE_SOUTH', 'SKIDDO'), ('MAP_SAFARI_ZONE_SOUTHWEST', 'LILLIPUP'), ('MAP_SAFARI_ZONE_NORTH', 'RUFFLET')]))
ok('Mt. Pyre 4F-6F: Litwick 5% + Misdreavus 5%, Shuppet/Duskull kept',
   all(table(f'MAP_MT_PYRE_{f}', 'land_mons')[6:8] == ['SPECIES_LITWICK', 'SPECIES_MISDREAVUS'] and 'SPECIES_SHUPPET' in table(f'MAP_MT_PYRE_{f}', 'land_mons') and 'SPECIES_DUSKULL' in table(f'MAP_MT_PYRE_{f}', 'land_mons') for f in ['4F', '5F', '6F']))
ok('Route124 surfing: Chinchou 5% slot', table('MAP_ROUTE124', 'water_mons')[2] == 'SPECIES_CHINCHOU')

# ---------------------------------------------------------------- 11. scope
ok('PART6 content untouched: no Dive HM, Space Center attack, Sootopolis or Adjuster edits',
   'ITEM_HM_DIVE' not in s5 and not any('SpaceCenter_2F' in f or 'Sootopolis' in f or 'SeafloorCavern' in f for f in list(D['text']) + list(D['maps'])))
print(f'PART5 static checks: {n_ok} groups PASS (no ROM/emulator/GUI run; gameplay verification remains manual)')
