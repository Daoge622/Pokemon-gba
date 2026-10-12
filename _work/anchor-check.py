import os, sys, glob

roms = {
    "new_build_src": r"E:\es\pokeemerald.gba",
    "codex_current": r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba",
    "baseline_r2":   r"E:\Pekemon Gba\EmeraldStory-一周目完整版.gba",
}

anchors = [
    ("multiboot mb_ereader.gba", r"E:\es\data\mb_ereader.gba"),
    ("multiboot mb_colosseum.gba", r"E:\es\data\mb_colosseum.gba"),
    ("multiboot mb_berry_fix.gba", r"E:\es\data\mb_berry_fix.gba"),
]

# 再取两个纯数据资产做锚点（由工具生成、不经过 C 编译器）
for pat in ["E:/es/build/assets/graphics/title_screen/*.4bpp",
            "E:/es/build/assets/graphics/intro/*.4bpp"]:
    hits = sorted(glob.glob(pat))
    if hits:
        anchors.append((f"asset {os.path.basename(hits[0])}", hits[0]))

print("=== 锚点定义 ===")
for name, p in anchors:
    print(f"  {name:34} {os.path.getsize(p) if os.path.exists(p) else 'MISSING'} bytes  {p}")

blobs = {name: open(p, "rb").read() for name, p in anchors if os.path.exists(p)}
rom_data = {k: open(p, "rb").read() for k, p in roms.items()}

print("\n=== 各 ROM 中的锚点定位（ROM 地址 = 文件偏移 + 0x08000000）===")
for name, blob in blobs.items():
    # 用较长的 needle 保证唯一性；若过大则取首 4096 字节
    needle = blob
    print(f"\n[{name}] len={len(needle)}")
    for rk, rd in rom_data.items():
        pos = rd.find(needle)
        if pos < 0 and len(needle) > 4096:
            pos = rd.find(needle[:4096])
            if pos >= 0:
                print(f"   {rk:16} 前缀命中 @ 0x{pos:07X} (ROM 0x{pos+0x08000000:08X})")
                continue
        if pos >= 0:
            print(f"   {rk:16} 完整命中 @ 0x{pos:07X} (ROM 0x{pos+0x08000000:08X})")
        else:
            print(f"   {rk:16} 未命中")
