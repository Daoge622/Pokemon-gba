"""脚本执行流审计：模拟 lock/release 平衡，找出战斗后会让玩家永久锁定的脚本。

思路：把 data/**/*.inc 全部解析成「全局线性指令表 + 标签索引」，
pokeemerald 的标签不是块边界（没有 end 就继续往下执行），所以必须按真实控制流走。
从每个「有 trainer_type 的地图对象脚本」入口开始 DFS，报告 lock 深度 != 0 的终止路径。
"""
import re, os, glob, json, sys
from collections import defaultdict

ROOT = r"E:\es"

# ---------------- 1. 收集指令 ----------------
INSTR = []          # [(cmd, args_str, relfile, lineno)]
LABELS = {}         # label -> instr index
LABEL_OF_INDEX = {}

label_re = re.compile(r"^([A-Za-z_]\w*)::\s*$")
skip_prefix = (".", "@")

files = []
for pat in ("data/maps/*/scripts.inc", "data/scripts/*.inc",
            "data/scripts/*/*.inc", "data/maps/*/*.inc"):
    files += glob.glob(os.path.join(ROOT, pat))
files = sorted(set(f for f in files if os.path.isfile(f)))
for extra in ("data/event_scripts.s", "data/maps/scripts.inc"):
    p = os.path.join(ROOT, extra)
    if os.path.isfile(p):
        files.append(p)

for path in files:
    rel = os.path.relpath(path, ROOT)
    try:
        fh = open(path, encoding="utf-8", errors="replace")
    except OSError:
        continue
    with fh:
        for no, raw in enumerate(fh, 1):
            s = raw.strip()
            if not s or s.startswith(skip_prefix):
                continue
            m = label_re.match(s)
            if m:
                LABELS.setdefault(m.group(1), len(INSTR))
                LABEL_OF_INDEX[len(INSTR)] = m.group(1)
                continue
            parts = s.split(None, 1)
            cmd = parts[0]
            args = parts[1] if len(parts) > 1 else ""
            INSTR.append((cmd, args, rel, no))

print(f"解析 {len(files)} 个脚本文件，{len(INSTR)} 条指令，{len(LABELS)} 个标签")

# ---------------- 2. 控制流模拟 ----------------
LOCK = {"lock", "lockall"}
UNLOCK = {"release", "releaseall"}
STOP = {"end", "return"}
# 宏：goto_if_defeated trainer, dest  → 条件跳转到 dest
JUMP_MACROS = {"goto_if_defeated", "goto_if_not_defeated"}
CALLISH = {"call_if_set", "call_if_unset", "call_if_eq", "call_if_ne", "call_if_lt", "call_if_gt",
           "call_if_le", "call_if_ge", "call_if_defeated", "call_if_not_defeated",
           "call_if_unset", "call_if_var_eq", "call_if_var_ne"}

def target_of(cmd, args):
    """从命令参数里取出跳转目标标签名。"""
    a = args.strip()
    if not a:
        return None
    # 逗号分隔：最后一个 / 第二个是标签
    tok = [t.strip() for t in a.split(",")]
    if cmd in JUMP_MACROS:
        return tok[-1] if len(tok) >= 2 else None
    if cmd.startswith("goto_if_") or cmd.startswith("call_if_"):
        # 形如 goto_if_set FLAG_X, Label  或  call_if_eq VAR, V, Label
        return tok[-1] if len(tok) >= 2 else None
    if cmd in ("goto", "call"):
        return tok[0] if tok else None
    if cmd == "case":
        return tok[-1] if len(tok) >= 2 else None
    return None

MAX_STEPS = 4000

def analyze(entry):
    """返回 lock 残留的终止路径。lock/release 在 pokeemerald 里是布尔状态，不是引用计数。"""
    if entry not in LABELS:
        return [(-1, f"入口 {entry} 未找到")]
    problems = []
    seen = set()
    # 栈元素: (pc, locked, ret_stack(tuple), path)
    stack = [(LABELS[entry], False, (), [entry])]
    steps = 0
    while stack:
        pc, locked, rets, path = stack.pop()
        steps += 1
        if steps > 60000:
            problems.append((1, "分析步数超限: " + " -> ".join(path[-6:])))
            break
        while True:
            key = (pc, locked, len(rets))
            if key in seen:
                break
            seen.add(key)
            if pc < 0 or pc >= len(INSTR):
                if locked:
                    problems.append((1, "eof | " + " -> ".join(path[-6:])))
                break
            cmd, args, rel, no = INSTR[pc]
            if cmd in LOCK:
                locked = True
                pc += 1
            elif cmd in UNLOCK:
                locked = False
                pc += 1
            elif cmd == "return":
                if rets:
                    pc, locked, rets = rets[-1][0], rets[-1][1], rets[:-1]
                else:
                    if locked:
                        problems.append((1, f"return@{rel}:{no} | " + " -> ".join(path[-6:])))
                    break
            elif cmd == "end":
                if locked:
                    problems.append((1, f"end@{rel}:{no} | " + " -> ".join(path[-6:])))
                break
            elif cmd == "goto":
                t = target_of(cmd, args)
                if t in LABELS:
                    path.append(t)
                    pc = LABELS[t]
                else:
                    pc += 1
            elif cmd.startswith("goto_if_") or cmd in JUMP_MACROS:
                t = target_of(cmd, args)
                if t in LABELS:
                    stack.append((LABELS[t], locked, rets, path + [t]))
                pc += 1
            elif cmd == "call":
                t = target_of(cmd, args)
                if t in LABELS:
                    rets = rets + ((pc + 1, locked),)
                    path.append(t)
                    pc = LABELS[t]
                else:
                    pc += 1
            elif cmd in CALLISH:
                t = target_of(cmd, args)
                if t in LABELS:
                    stack.append((LABELS[t], locked, rets + ((pc + 1, locked),), path + [t]))
                pc += 1
            elif cmd == "case":
                t = target_of(cmd, args)
                if t in LABELS:
                    stack.append((LABELS[t], locked, rets, path + [t]))
                pc += 1
            else:
                pc += 1
    return problems

# ---------------- 3. 从游戏对象收集入口 ----------------
entries = []          # (map, local_id, trainer_type, script)
for mj in glob.glob(os.path.join(ROOT, "data", "maps", "*", "map.json")):
    mp = os.path.basename(os.path.dirname(mj))
    try:
        j = json.load(open(mj, encoding="utf-8"))
    except Exception:
        continue
    for o in j.get("object_events", []):
        tt = o.get("trainer_type", "TRAINER_TYPE_NONE")
        sc = o.get("script") or ""
        if tt and tt.startswith("TRAINER_TYPE") and tt != "TRAINER_TYPE_NONE" and sc:
            entries.append((mp, o.get("local_id"), tt, sc))

# 追加：项目自定义剧情入口里出现的 trainerbattle 标签
battle_labels = set()
for cmd, args, rel, no in INSTR:
    if cmd.startswith("trainerbattle") and rel.startswith("data\\") is False:
        pass
for cmd, args, rel, no in INSTR:
    if cmd.startswith("trainerbattle"):
        # 上一行的标签
        pass

print(f"地图训练家对象入口: {len(entries)}")

bad = []
for mp, lid, tt, sc in entries:
    probs = analyze(sc)
    probs = [p for p in probs if p[0] > 0]
    if probs:
        worst = max(p[0] for p in probs)
        bad.append((mp, lid, tt, sc, worst, probs[:2]))

print(f"\n=== 有 lock 未配对 release 的训练家对象：{len(bad)} ===")
for mp, lid, tt, sc, worst, probs in sorted(bad, key=lambda x: -x[4]):
    print(f"\n[{mp}] {lid}  ({tt})  script={sc}  max_lock_depth={worst}")
    for d, path in probs:
        print(f"    depth={d}  {path[:150]}")

# ---------------- 4. 地图对象脚本是否真的存在 ----------------
print("\n=== 地图对象引用的脚本标签未定义的情况 ===")
missing_script = [(mp, lid, tt, sc) for mp, lid, tt, sc in entries if sc not in LABELS]
print(f"  {len(missing_script)} 个：")
for mp, lid, tt, sc in missing_script[:20]:
    print(f"    [{mp}] {lid} ({tt}) -> {sc}")

# ---------------- 5. 所有 goto/call 目标是否存在 ----------------
missing = {}
for cmd, args, rel, no in INSTR:
    if cmd in ("goto", "call") or cmd.startswith("goto_if_") or cmd.startswith("call_if_") \
       or cmd in JUMP_MACROS or cmd == "case":
        t = target_of(cmd, args)
        if not t or t in LABELS:
            continue
        if t.startswith(("VAR_", "FLAG_", "0x", "MAP_", "TRAINER_")) or t.isdigit():
            continue
        missing.setdefault(t, []).append(f"{rel}:{no}")
print(f"\n=== goto/call 指向未定义标签：{len(missing)} 种 ===")
for t, locs in list(missing.items())[:40]:
    print(f"  {t:46} 出现 {len(locs)} 次，如 {locs[0]}")

# ---------------- 6. 训练家对象 -> 战斗后是否能正常结束（是否命中 end） ----------------
print("\n=== 每个训练家对象脚本是否可达 end/return（能退出脚本）===")
no_exit = []
for mp, lid, tt, sc in entries:
    if sc not in LABELS:
        continue
    probs = analyze(sc)
    # analyze 只在 locked 时报；这里额外检查是否存在"跑飞"(eof)路径
    eof = [p for p in probs if "eof" in p[1]]
    if eof:
        no_exit.append((mp, lid, sc, eof[:1]))
print(f"  跑到 eof 的入口：{len(no_exit)}")
for mp, lid, sc, e in no_exit[:15]:
    print(f"    [{mp}] {lid} -> {sc} : {e[0][1][:120]}")
