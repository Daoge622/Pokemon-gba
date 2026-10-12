import os

sav = r"C:\Users\DaoGe\Downloads\EmeraldStory-一周目完整版.sav"
d = open(sav, "rb").read()
print(f"size = {len(d)} (0x{len(d):X})")

nz = sum(1 for b in d if b != 0)
print(f"非零字节: {nz} / {len(d)}  ({nz/len(d)*100:.1f}%)")

print("\n前 32 字节:", d[:32].hex(" "))
print("0xE000 附近:", d[0xE000:0xE020].hex(" "))

print("\n各 4KB 扇区 0xFF8 处的 4 字节：")
for s in range(0, len(d), 0x1000):
    off = s + 0xFF8
    if off + 4 <= len(d):
        sig = d[off:off+4]
        mark = "  <== SECTOR_SIGNATURE" if sig == bytes.fromhex("25012008") else ""
        if sig != b"\xff\xff\xff\xff":
            print(f"  sector {s//0x1000:2d}  0x{off:05X}: {sig.hex(' ')}{mark}")

print("\n各 4KB 扇区 0xFF4 处的 id/checksum：")
for s in range(0, len(d), 0x1000):
    off = s + 0xFF4
    if off + 4 <= len(d):
        v = d[off:off+4]
        if v != b"\xff\xff\xff\xff":
            print(f"  sector {s//0x1000:2d}  0x{off:05X}: {v.hex(' ')}")

# 另外找 "any 4-byte value that repeats 14+ times" —— 若签名被换过，仍会规律出现
from collections import Counter
c = Counter()
for s in range(0, len(d) - 4, 4):
    c[d[s:s+4]] += 1
print("\n最常见 4 字节（出现次数 >= 14）：")
for v, n in c.most_common(12):
    if n >= 14:
        print(f"  {v.hex(' ')}  x{n}")
