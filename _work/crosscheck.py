import numpy as np

def load(p):
    return np.frombuffer(open(p, "rb").read(), dtype=np.uint8)

base = load(r"E:\Pekemon Gba\EmeraldStory-一周目完整版.gba")
cur  = load(r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba")
new  = load(r"E:\es\pokeemerald.gba")

def diff(a, b, na, nb):
    d = a != b
    idx = np.flatnonzero(d)
    gaps = np.flatnonzero(np.diff(idx) > 16) if idx.size else []
    starts = np.concatenate(([0], np.asarray(gaps) + 1)) if idx.size else []
    ends = np.concatenate((np.asarray(gaps), [idx.size - 1])) if idx.size else []
    regions = [(int(idx[s]), int(idx[e])) for s, e in zip(starts, ends)]
    print(f"{na} vs {nb}: diff={idx.size} bytes ({idx.size/a.size*100:.4f}%), regions={len(regions)}")
    for s, e in regions[:12]:
        print(f"   0x{s:07X}..0x{e:07X} ({e-s+1})")
    if len(regions) > 12:
        print(f"   ... +{len(regions)-12} more")
    return regions

print("=== A. 校核对比方法：现用 ROM vs 基线 ROM（应只差 Codex 的定点补丁）===")
diff(base, cur, "baseline_r2", "codex_current")

print("\n=== B. 新构建 vs 基线 ===")
diff(base, new, "baseline_r2", "new_build_src")

# 新构建自洽性：ROM 尾部填充检查
print("\n=== C. 新构建 ROM 尾部（未使用区应为 0xFF 填充）===")
tail = new[-64:]
print("   last 64 bytes:", " ".join(f"{b:02X}" for b in tail))
nz = np.flatnonzero(new != 0xFF)
print(f"   非 0xFF 字节数: {nz.size}；最后一个非 0xFF 偏移: 0x{nz[-1]:07X}")
