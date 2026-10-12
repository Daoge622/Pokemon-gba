import os, re, io

def load(p):
    with open(p, "rb") as f:
        return f.read()

new  = load(r"E:\es\pokeemerald.gba")
cur  = load(r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba")

print("=== 头部 0x00-0x13F 差异（含入口代码区）===")
diff = [i for i in range(0x140) if new[i] != cur[i]]
print("  差异字节:", len(diff), "位置:", [hex(i) for i in diff][:20])

print("\n=== 存档相关源码常量 ===")
root = r"E:\es"
targets = {
    "include/constants/flags.h": r"FLAGS_COUNT",
    "include/constants/vars.h": r"VARS_COUNT",
    "include/global.h": r"SECTOR_SIGNATURE|SAVEBLOCK|SaveBlock1|SaveBlock2",
}
for rel, pat in targets.items():
    p = os.path.join(root, rel.replace("/", os.sep))
    if not os.path.exists(p):
        print(f"  MISSING {rel}")
        continue
    txt = io.open(p, encoding="utf-8", errors="replace").read()
    hits = [l.strip() for l in txt.split("\n") if re.search(pat, l)]
    print(f"\n  [{rel}] 匹配 {len(hits)} 行：")
    for h in hits[:12]:
        print("     ", h[:110])

# SaveBlock 大小常量（pokeemerald 习惯在 global.h 里定义）
g = io.open(os.path.join(root, "include", "global.h"), encoding="utf-8", errors="replace").read()
for m in re.finditer(r"#define\s+(SAVEBLOCK\w*|SECTOR\w*|SAVE\w*SIZE\w*)\s+(\(?\s*[\w\s\*\+\-]*\))", g):
    print("  ", m.group(0)[:110])

print("\n=== 用户存档 ===")
sav = r"C:\Users\DaoGe\Downloads\EmeraldStory-一周目完整版.sav"
if os.path.exists(sav):
    sd = load(sav)
    print(f"  size={len(sd)} (0x{len(sd):X})")
    SIG = bytes.fromhex("25012008")  # SECTOR_SIGNATURE 0x08012025 little-endian
    pos = []
    i = sd.find(SIG)
    while i >= 0 and len(pos) < 32:
        pos.append(i)
        i = sd.find(SIG, i + 1)
    print(f"  扇区签名 0x08012025 出现 {len(pos)} 次；前 8 个偏移: {[hex(p) for p in pos[:8]]}")
