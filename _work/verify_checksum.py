"""校准：验证 pokeemerald 扇区校验和算法，找出 SaveBlock1 的真实扇区位置。"""
import struct, pathlib

for name, path in [
    ("codex-save", r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav"),
    ("user-save",  r"E:\Pekemon Gba\_work\verif\user-save-copy.sav"),
]:
    raw = pathlib.Path(path).read_bytes()
    print(f"\n=== {name}  size={len(raw)} ===")
    print(f"{'offset':>8} {'sectorId':>8} {'stored':>6} {'calcFF4':>8} {'calcFF6':>8} {'calcFF8':>8} {'match':>6}")
    for base in range(0, len(raw), 0x1000):
        if base + 0x1000 > len(raw):
            break
        sid = struct.unpack_from('<H', raw, base + 0xFF4)[0]
        stored = struct.unpack_from('<H', raw, base + 0xFF6)[0]
        sig = struct.unpack_from('<I', raw, base + 0xFF8)[0]
        if sig != 0x08012025:
            continue
        c_ff4 = sum(raw[base:base+0xFF4]) & 0xFFFF
        c_ff6 = sum(raw[base:base+0xFF6]) & 0xFFFF
        c_ff8 = sum(raw[base:base+0xFF8]) & 0xFFFF
        m = "FF4" if stored == c_ff4 else ("FF6" if stored == c_ff6 else ("FF8" if stored == c_ff8 else "-"))
        print(f"  0x{base:05X} {sid:>8} 0x{stored:04X}  0x{c_ff4:04X}  0x{c_ff6:04X}  0x{c_ff8:04X}   {m}")
