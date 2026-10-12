import numpy as np, sys, json

paths = {
    "new_build_src": r"E:\es\pokeemerald.gba",
    "codex_current": r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba",
    "baseline_r2":   r"E:\Pekemon Gba\EmeraldStory-一周目完整版.gba",
}

data = {}
for k, p in paths.items():
    with open(p, "rb") as f:
        data[k] = np.frombuffer(f.read(), dtype=np.uint8)
    print(f"{k:16} size={data[k].size}")

def diff_report(a, b, name_a, name_b):
    n = min(a.size, b.size)
    d = a[:n] != b[:n]
    idx = np.flatnonzero(d)
    print(f"\n=== {name_a} vs {name_b} ===")
    if idx.size == 0:
        print("  identical")
        return
    print(f"  differing bytes: {idx.size} ({idx.size/n*100:.4f}%)")
    # group into contiguous regions (gap > 16 counts as new region)
    gaps = np.flatnonzero(np.diff(idx) > 16)
    starts = np.concatenate(([0], gaps + 1))
    ends = np.concatenate((gaps, [idx.size - 1]))
    regions = [(int(idx[s]), int(idx[e])) for s, e in zip(starts, ends)]
    print(f"  regions (gap>16): {len(regions)}")
    print("  first 25 regions: start..end (len)")
    for s, e in regions[:25]:
        print(f"    0x{s:07X}..0x{e:07X}  ({e-s+1})")
    if len(regions) > 25:
        print(f"    ... and {len(regions)-25} more")
    return regions

diff_report(data["new_build_src"], data["codex_current"], "new_build_src", "codex_current")
diff_report(data["new_build_src"], data["baseline_r2"], "new_build_src", "baseline_r2")
