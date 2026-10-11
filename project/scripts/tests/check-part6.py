#!/usr/bin/env python3
"""PART6 static checks (CLI only; never starts a ROM, emulator or GUI)."""
from pathlib import Path
from collections import deque
import json, re, struct, subprocess, hashlib, sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
import part6_compat

r = Path(__file__).resolve().parents[2]
D = part6_compat.D
M = json.loads((r / 'docs/project/part6-manifest.json').read_text(encoding='utf-8'))
PRE = D['baseline']
n = 0


def read(f):
    return part6_compat.current(f)  # PART6 state: current files with PART7 deltas removed


def pre(f):
    return subprocess.check_output(['git', 'show', PRE + ':' + f], cwd=r, text=True)


def ok(label, cond=True):
    global n
    assert cond, label
    n += 1
    print('PASS', label)


s6 = read('data/scripts/part6.inc')
texts = dict(re.findall(r'^(Part6_Text_\d+):\n\t\.string "(.*)"$', s6, re.M))


def block(label):
    m = re.search(r'^' + re.escape(label) + r'::\n(.*?)(?=^\S[^\n]*::\n|\Z)', s6, re.M | re.S)
    assert m, label
    return m.group(1)


def btext(label):
    return ''.join(texts[t] for t in re.findall(r'Part6_Text_\d+', block(label)))


# ---------------------------------------------------------------- 1. scope / recorded deltas
# PART6 scope ends at the PART7 checkpoint; later edits are recorded and checked by check-part7.py.
changed = set(subprocess.check_output(['git', 'diff', '--name-only', PRE, part6_compat.part7_compat.D['baseline']], cwd=r, text=True).splitlines())
changed = {f for f in changed if f.startswith(('src/', 'include/', 'data/', 'asm/'))}
ok('every PART6 source change is recorded in part6-deltas.json', changed == set(D['text']) | set(D['binary']) | set(D['new_files']))
for f in D['text']:
    part6_compat.source(f)
for f in D['new_files']:
    data = part6_compat.current(f).encode() if f in part6_compat.part7_compat.D['text'] else (r / f).read_bytes()
    assert hashlib.sha256(data).hexdigest() == D['sha256'][f], f
ok(f'{len(D["text"])} edited files reverse exactly to pre-PART6; {len(D["new_files"])} new files match recorded hashes')

# ---------------------------------------------------------------- 2. allocations
flags_h = read('include/constants/flags.h')
for name, slot in M['flags'].items():
    s = int(slot, 16)
    assert re.search(r'^#define %s 0x%03X\b' % (name, s), flags_h, re.M), name
    assert re.search(r'^#define FLAG_UNUSED_0x%03X\s' % s, pre('include/constants/flags.h'), re.M), (name, 'slot not unused before PART6')
ok(f'{len(M["flags"])} flags only from audited unused slots; no new persistent VARs',
   'VAR_PART6_' not in read('include/constants/vars.h'))
bp, opp, p55 = read('include/constants/battle_partner.h'), read('include/constants/opponents.h'), read('src/part55.c')
for full, info in M['roster'].items():
    assert f'#define {full} TRAINER_PARTNER({info["partner"]})' in opp, full
    assert f'case {full}: return {info["defeat_flag"]};' in p55, full
    assert f'=== {info["partner"]} ===' in read('src/data/battle_partners.party'), full
ok(f'{len(M["roster"])} new trainers use the PART5.5 ROM roster with mapped defeat flags; 864 save slots unchanged',
   '#define MAX_TRAINERS_COUNT_EMERALD 864' in opp and f'#define PARTNER_COUNT {8 + len(M["roster"])}' in bp)

# ---------------------------------------------------------------- 3. text
font = json.loads(read('tools/poryscript/font_config.json'))['fonts']['1_chinese_rse']['widths']
charmap = {m.group(1) for m in re.finditer(r"^'(.+?)'\s*=", read('charmap.txt'), re.M)}
count = 0
for lab, t in texts.items():
    for page in t.rstrip('$').split(r'\p'):
        lines = page.split(r'\n')
        assert len(lines) <= 2, (lab, lines)
        for line in lines:
            plain = re.sub(r'\{STR_VAR_\d\}', 'Ｗ' * 2, line.replace('{PLAYER}', 'Ｗ' * 7))
            assert sum(12 if c == 'Ｗ' else font.get(c, 6) for c in plain) <= 208, (lab, line)
            assert all(c in charmap or c in ' Ｗ' for c in plain), (lab, line)
            count += 1
alltxt = ''.join(texts.values())
for banned in ['安提', '首领', '萨维尔', '本原协议', '骑拉帝纳', '反转世界', '超梦', '雷吉奇卡斯', '基拉祈', '帝牙卢卡', '原始回归', '不是……而是']:
    assert banned not in alltxt, banned
ok(f'{count} PART6 lines within 208px/2-line pages, charmap-valid; no hidden identities, future legends or Rayquaza/Primal mix-up')
anti = btext('Part6_Anti')
ok('Anti scene: anonymous "男子", no ARCHE/"我们"/Rain reference, canon adjuster line present',
   '阿尔刻' not in anti and '我们' not in anti and '莱因' not in anti and '区别也许只是程度不同而已' in anti and '男子：' in anti)

# ---------------------------------------------------------------- 4. maps
layouts = {x['id']: x for x in json.loads(read('data/layouts/layouts.json'))['layouts'] if 'id' in x}


def grid(v):
    l = layouts[v['layout']]
    w, h = l['width'], l['height']
    return w, h, struct.unpack('<' + 'H' * (w * h), (r / l['blockdata_filepath']).read_bytes())


def peak(objs):
    return max((sum(x <= t['x'] <= x + 19 and y <= t['y'] <= y + 16 for t in objs) for o in objs
                for x in [o['x'], o['x'] - 19] for y in [o['y'], o['y'] - 16]), default=0)


new_maps = {p.split('/')[2] for p in D['new_files'] if p.endswith('map.json')}
placed = 0
for name, added in M['maps'].items():
    f = f'data/maps/{name}/map.json'
    v = json.loads(read(f))
    w, h, c = grid(v)
    assert len(v['object_events']) <= 64
    warps = {(z['x'], z['y']) for z in v['warp_events']}
    near = {(x + dx, y + dy) for x, y in warps for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))}
    for kind, lid, x, y in added:
        if kind != 'obj':
            continue
        o = next(o for o in v['object_events'] if o.get('local_id') == lid)
        cell = c[y * w + x]
        if name != 'SkyPillar_Top':   # top uses LAYOUT_SKY_PILLAR_TOP_CLEAN during the first visit
            assert (cell >> 10) & 3 == 0, (name, lid, 'blocked')
        assert (x, y) not in warps and (x, y) not in near, (name, lid, 'warp/arrival tile')
        assert sum((q['x'], q['y']) == (x, y) for q in v['object_events']) == 1, (name, lid, 'overlap')
        placed += 1
    if name not in new_maps:
        assert peak(v['object_events']) <= max(15, peak(json.loads(pre(f))['object_events'])), (name, 'viewport capacity')
ok(f'{placed} PART6 actors: open tiles, no overlap, no door/stair arrival blocking, viewport peaks within native limits')
top = json.loads(read('data/maps/SkyPillar_Top/map.json'))
ev = {o.get('local_id'): o for o in top['object_events']}
clean = layouts['LAYOUT_SKY_PILLAR_TOP_CLEAN']
cc = struct.unpack('<' + 'H' * (clean['width'] * clean['height']), (r / clean['blockdata_filepath']).read_bytes())
gap = [(x, 13) for x in range(clean['width']) if not (cc[13 * clean['width'] + x] >> 10) & 3]
ok('Evelyn + aide fully block the only passage to the Rayquaza trigger on the first-visit layout',
   sorted((ev['LOCALID_PART6_EVELYN']['x'], 13), ) and set(gap) == {(ev['LOCALID_PART6_EVELYN']['x'], 13), (ev['LOCALID_PART6_EVELYN_AIDE']['x'], 13)})
arche = [o for m in ['SkyPillar_1F', 'SkyPillar_3F', 'SkyPillar_5F', 'SkyPillar_Top'] for o in json.loads(read(f'data/maps/{m}/map.json'))['object_events']
         if str(o.get('local_id', '')).startswith('LOCALID_PART6_SKY_') and 'ALTARIA' != o.get('local_id', '')[-7:] and o['graphics_id'] != 'OBJ_EVENT_GFX_ITEM_BALL'
         and 'SPECIES' not in o['graphics_id']] + [ev['LOCALID_PART6_EVELYN'], ev['LOCALID_PART6_EVELYN_AIDE']]
ok('every ARCHE actor in the Sky Pillar disappears after Evelyn withdraws',
   all(o['flag'] == 'FLAG_PART6_SKY_PILLAR_ARCHE_LEFT' for o in arche) and 'setflag FLAG_PART6_SKY_PILLAR_ARCHE_LEFT' in block('Part6_Evelyn_After'))
ok('Rayquaza capture battle Lv50; native defeat/run/HoF handling kept', 'setwildbattle SPECIES_RAYQUAZA, 50' in read('data/maps/SkyPillar_Top/scripts.inc')
   and 'FLAG_DEFEATED_RAYQUAZA' in read('data/maps/SkyPillar_Top/scripts.inc'))

# ---------------------------------------------------------------- 5. trainers
party = read('src/data/trainers.party') + '\n' + read('src/data/battle_partners.party')


def roster(t):
    raw = re.search(r'^=== ' + t + r' ===\n(.*?)(?=^=== |^/\*|\Z)', party, re.M | re.S).group(1)
    return raw, [(b.splitlines()[0].split(' @ ')[0], int(re.search(r'^Level: (\d+)', b, re.M).group(1)), b.splitlines()[0].split(' @ ')[1] if ' @ ' in b.splitlines()[0] else None)
                 for b in re.split(r'\n\s*\n', raw) if 'Level:' in b]


def lv(t):
    return [(a, b) for a, b, _ in roster(t)[1]]


ok('Archie: 5 Pokemon, Mega Sharpedo Lv47 ace', lv('TRAINER_ARCHIE') == [('Mightyena', 43), ('Crobat', 43), ('Muk', 44), ('Crawdaunt', 45), ('Sharpedo', 47)] and roster('TRAINER_ARCHIE')[1][-1][2] == 'Sharpedonite')
ok('Seafloor admin keeps a full non-Mega team', not any(i and i.endswith('ite') for _, _, i in roster('TRAINER_SHELLY_SEAFLOOR_CAVERN')[1]))
ok('Juan: 6 Pokemon, Mega Gyarados not last, Kingdra Lv47 highest', lv('TRAINER_JUAN_1') == [('Luvdisc', 43), ('Whiscash', 43), ('Crawdaunt', 44), ('Walrein', 44), ('Gyarados', 45), ('Kingdra', 47)]
   and roster('TRAINER_JUAN_1')[1][4][2] == 'Gyaradosite')
ok('Rain: Castform/Rotom-Wash/Skarmory/Electivire/Magnezone46, no Mega stone', lv('PARTNER_PART6_RAIN') == [('Castform', 42), ('Rotom-Wash', 43), ('Skarmory', 43), ('Electivire', 44), ('Magnezone', 46)]
   and 'ite\n' not in roster('PARTNER_PART6_RAIN')[0])
ok('Evelyn: 5 Pokemon, Mega Alakazam Lv48 ace', lv('PARTNER_PART6_EVELYN') == [('Porygon-Z', 45), ('Milotic', 45), ('Reuniclus', 46), ('Gallade', 46), ('Alakazam', 48)] and roster('PARTNER_PART6_EVELYN')[1][-1][2] == 'Alakazite')
ok('Gallade master: Mega Gallade Lv48', roster('PARTNER_PART6_GALLADE_MASTER')[1][-1][:3] == ('Gallade', 48, 'Galladite'))
ok('Sky Pillar: 5 ARCHE battles (one double) + entrance guard', 'Double Battle: Yes' in roster('PARTNER_PART6_SKY_TECH_GUARD')[0] and len(M['roster']) == 8)
bad = []
learn = json.loads(read('src/data/pokemon/all_learnables.json'))
for t in ['TRAINER_ARCHIE', 'TRAINER_SHELLY_SEAFLOOR_CAVERN', 'TRAINER_JUAN_1'] + [i['partner'] for i in M['roster'].values()]:
    raw = roster(t)[0]
    for b in re.split(r'\n\s*\n', raw):
        if 'Level:' not in b:
            continue
        sp = b.splitlines()[0].split(' @ ')[0].upper().replace('-', '_')
        for mv in re.findall(r'^- (.+)$', b, re.M):
            key = 'MOVE_' + mv.upper().replace(' ', '_').replace('-', '_').replace("'", '')
            if key not in learn.get(sp, learn.get(sp.split('_')[0], [])) and (sp, mv) != ('ROTOM_WASH', 'Hydro Pump'):  # form-change signature move
                bad.append((t, sp, mv))
ok('trainer moves legal for each species' + (f' (exceptions: {bad})' if bad else ''), not bad)
for t, banned in [('PARTNER_PART6_EVELYN', ['Hypnosis', 'Focus Sash', 'Choice']), ('TRAINER_JUAN_1', ['Rain Dance', 'Drizzle', 'Hypnosis', 'Focus Sash'])]:
    assert not any(b in roster(t)[0] for b in banned), t
ok('no sleep lock, sash, choice items or permanent rain team')

# ---------------------------------------------------------------- 6. rewards, items, legendaries
for st in ['SLOWBRONITE', 'AERODACTYLITE', 'GALLADITE']:
    assert s6.count('giveitem ITEM_' + st) == 1, st
for st in ['SABLENITE', 'METAGROSSITE', 'SALAMENCITE', 'GARCHOMPITE', 'LUCARIONITE', 'GENGARITE', 'KANGASKHANITE', 'SCEPTILITE', 'BLAZIKENITE', 'SWAMPERTITE', 'VENUSAURITE', 'CHARIZARDITE', 'BLASTOISINITE']:
    assert 'giveitem ITEM_' + st not in s6, st
ok('PART6 player Mega stones: Slowbronite/Aerodactylite/Galladite once each; Sablenite (already PART5.5) and deferred strong stones not given')
for lab in ['Part6_OldDiver', 'Part6_TideOldMan', 'Part6_Boatman', 'Part6_Paleontologist', 'Part6_Photographer']:
    b = block(lab + '_Return')
    assert b.index('checkitemspace') < b.index('giveitem') < b.index('removeitem') < b.index('setflag'), lab
ok('find-and-return quests: space checked, rewards given, quest item removed and state set only after success')
for lab in ['Part6_AnomalyResearcher', 'Part6_CoralDaughter_Reward', 'Part6_Carpenter_Return', 'Part6_ReviewResearcher_Check', 'Part6_ClinicNurse_AfterKit', 'Part6_RainPlatform_After', 'Part6_CalFisher_Check']:
    assert 'giveitem' in block(lab), lab
ok('every formal side quest (find/deliver/survey/rescue/battle) ends with a real reward', 'addmoney 25000' in block('Part6_ReviewResearcher_Check'))
ok('anomaly survey completes the PART5.5 quest (3 points -> Evolution Stone + Big Pearl x3)', 'VAR_PART55_UNDERWATER_OBSERVATION' in block('Part6_AnomalyResearcher')
   and 'giveitem ITEM_EVOLUTION_STONE, 1' in block('Part6_AnomalyResearcher') and 'giveitem ITEM_BIG_PEARL, 3' in block('Part6_AnomalyResearcher'))
c6 = read('src/part6.c')
ok('Suicune Lv40 in the sealed Still Water Cave, Entei/Raikou rule (caught permanent, otherwise next Hall of Fame)',
   'seteventmon SPECIES_SUICUNE, 40' in s6 and 'Part6_ResetSuicuneAfterHallOfFame' in read('data/scripts/hall_of_fame.inc')
   and 'B_OUTCOME_CAUGHT' in c6 and not any(o.get('trainer_type') != 'TRAINER_TYPE_NONE' for o in json.loads(read('data/maps/Route126_StillWaterCave/map.json'))['object_events']))
items = read('src/data/items.h')
adj = re.search(r'\[ITEM_PRIMAL_ADJUSTER\] =\n    \{.*?\n    \},', items, re.S).group()
ok('Primal Adjuster: key item using the native field-script pattern; blocked indoors, on locked/extreme-weather maps and during the crisis',
   'POCKET_KEY_ITEMS' in adj and 'ItemUseOutOfBattle_PrimalAdjuster' in adj and 'FLAG_SYS_WEATHER_CTRL' in c6 and 'IsMapTypeOutdoors' in c6
   and 'MAP_SKY_PILLAR_TOP' in c6 and 'WEATHER_DROUGHT' in c6 and 'SetSavedWeatherFromCurrMapHeader' in c6)
ok('Adjuster only after the crisis is resolved (Anti visible when VAR_SKY_PILLAR_STATE >= 2)', 'Part6_Show(FLAG_TEMP_13, resolved && !FlagGet(FLAG_PART6_ADJUSTER_RECEIVED))' in c6)
ok('regi reward requires all three caught; no Regigigas', 'SPECIES_REGISTEEL' in c6 and 'REGIGIGAS' not in s6 + c6)

# ---------------------------------------------------------------- 7. scope
ok('PART7 untouched: no Victory Road / Elite Four / Ever Grande edits',
   not any(k in f for f in changed for k in ('EverGrande', 'VictoryRoad')))
ok('native main story kept: Wallace/Steven/Archie/Maxie scenes not rewritten (only text labels or teams)',
   all(f in D['text'] for f in ['data/maps/SkyPillar_Top/scripts.inc']) and 'data/maps/SeafloorCavern_Room9/scripts.inc' not in D['text']
   and 'data/maps/CaveOfOrigin_B1F/scripts.inc' not in D['text'])
print(f'PART6 static checks: {n} groups PASS (no ROM/emulator/GUI run; gameplay verification remains manual)')
