"""全库脚本审计：找出「战斗脚本 lock 后无 release」等会导致战后卡死的模式。"""
import re, os, glob, sys
from collections import defaultdict

ROOT = r"E:\es"
files = []
files += glob.glob(os.path.join(ROOT, "data", "maps", "*", "scripts.inc"))
files += glob.glob(os.path.join(ROOT, "data", "scripts", "*.inc"))
files += glob.glob(os.path.join(ROOT, "data", "scripts", "**", "*.inc"), recursive=True)
files = sorted(set(files))

LABEL = re.compile(r"^([A-Za-z_]\w*)::\s*$")

def parse(path):
    blocks = []          # [(label, [cmd,...], startline)]
    cur = None
    with open(path, encoding="utf-8", errors="replace") as fh:
        for no, raw in enumerate(fh, 1):
            s = raw.strip()
            if not s or s.startswith("@") or s.startswith("."):
                continue
            m = LABEL.match(s)
            if m:
                cur = (m.group(1), [], no)
                blocks.append(cur)
            elif cur is not None:
                cur[1].append(s.split()[0])
    return blocks

allblocks = {}   # label -> (file, cmds, line)
for p in files:
    for label, cmds, line in parse(p):
        allblocks.setdefault(label, (p, cmds, line))

print(f"扫描 {len(files)} 个脚本文件，共 {len(allblocks)} 个标签\n")

LOCKISH = {"lock", "lockall"}
RELEASEISH = {"release", "releaseall"}

def lookahead(label, depth=0, seen=None):
    """返回该标签可达的 (lock数, release数, 是否显式 end/return)。简化版：只跟踪 goto/call 一层。"""
    seen = seen or set()
    if label in seen or depth > 3 or label not in allblocks:
        return 0, 0, False
    seen.add(label)
    _, cmds, _ = allblocks[label]
    lk = sum(1 for c in cmds if c in LOCKISH)
    rl = sum(1 for c in cmds if c in RELEASEISH)
    ended = any(c in ("end", "return") for c in cmds)
    # 追踪 goto/call 目标
    for c, rest in [(c, "") for c in cmds]:
        pass
    return lk, rl, ended

# 更实用：逐块列出结构，标出可疑
suspicious = []
trainer_battle_blocks = []
for label, (p, cmds, line) in sorted(allblocks.items()):
    nb = [c for c in cmds if c.startswith("trainerbattle")]
    if not nb:
        continue
    nl = sum(1 for c in cmds if c in LOCKISH)
    nr = sum(1 for c in cmds if c in RELEASEISH)
    has_end = any(c in ("end", "return") for c in cmds)
    tail = cmds[-1] if cmds else ""
    rel = os.path.relpath(p, ROOT)
    trainer_battle_blocks.append((label, rel, nl, nr, has_end, tail))
    # 可疑判定：有 lock 但本块无 release，且结尾不是 goto（goto 目标可能有 release）
    if nl > 0 and nr == 0 and tail != "goto":
        suspicious.append((label, rel, nl, nr, has_end, tail))

print(f"含 trainerbattle 的标签块：{len(trainer_battle_blocks)}")
print(f"\n=== 可疑（本块有 lock/lockall 但无 release/releaseall，且不以 goto 收尾）===")
print(f"共 {len(suspicious)} 个：")
for label, rel, nl, nr, has_end, tail in suspicious:
    print(f"  {label:58} lock={nl} rel={nr} end={has_end} tail={tail}  {rel}")

# 第二类：以 goto 收尾的，需要人工看 goto 目标
print(f"\n=== 以 goto 收尾且有 lock 的块（release 可能在目标块）===")
cnt = 0
for label, rel, nl, nr, has_end, tail in trainer_battle_blocks:
    if nl > 0 and nr == 0 and tail == "goto":
        cnt += 1
        if cnt <= 40:
            print(f"  {label:58} {rel}")
print(f"  共 {cnt} 个")

# 第三类：视线训练家对象 + 其脚本结构（从 map.json 找 trainer_type 与 script）
import json
vision_objs = []
for mj in glob.glob(os.path.join(ROOT, "data", "maps", "*", "map.json")):
    try:
        j = json.load(open(mj, encoding="utf-8"))
    except Exception:
        continue
    for o in j.get("object_events", []):
        tt = o.get("trainer_type", "TRAINER_TYPE_NONE")
        if tt and tt != "TRAINER_TYPE_NONE":
            vision_objs.append((os.path.basename(os.path.dirname(mj)), o.get("local_id"), tt, o.get("script")))
print(f"\n=== 有 trainer_type 的对象：{len(vision_objs)} ===")
from collections import Counter
print("  按类型:", Counter(t for _, _, t, _ in vision_objs))
