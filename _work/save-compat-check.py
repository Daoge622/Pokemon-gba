import numpy as np, os

def load(p):
    with open(p, "rb") as f:
        return f.read()

new  = load(r"E:\es\pokeemerald.gba")
base = load(r"E:\Pekemon Gba\EmeraldStory-一周目完整版.gba")
cur  = load(r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba")

print("=== GBA 头部 0x00-0xBF 对比（存档识别与游戏代码）===")
print(f"{'偏移':>8} {'长度':>4}  新构建 = 现用?  内容")
segments = [(0x00,4,"ROM 入口指令"),(0x04,156,"Nintendo 徽标"),(0xA0,12,"游戏标题"),
            (0xAC,4,"游戏代码"),(0xB0,2,"厂商"),(0xB2,1,"固定值 0x96"),(0xBC,1,"版本"),
            (0xBD,1,"校验和"),(0xBE,2,"保留")]
allhead = True
for off, ln, name in segments:
    a = new[off:off+ln]; b = cur[off:off+ln]
    same = "相同" if a==b else "不同"
    if a!=b: allhead = False
    val = a[:16].hex() if ln<=16 else a[:16].hex()+"..."
    print(f"0x{off:06X} {ln:>4}  {same:7}  {name:12} {val}")
print("头部(0x00-0xBF)完全一致:" , "是" if new[:0xC0]==cur[:0xC0] else "否")

print("\n=== 0x0000-0x013F 全段逐字节 ===")
d = new[:0x140] != cur[:0x140]
print("  差异字节数:", int(d.sum()))

print("\n=== 游戏代码/版本 ===")
print("  新构建:", new[0xAC:0xB0], "版本:", new[0xBC])
print("  现用  :", cur[0xAC:0xB0], "版本:", cur[0xBC])
print("  标题  :", new[0xA0:0xAC])

print("\n=== 用户存档文件 ===")
sav = r"C:\Users\DaoGe\Downloads\EmeraldStory-一周目完整版.sav"
if os.path.exists(sav):
    sd = load(sav)
    print(f"  {sav}")
    print(f"  size={len(sd)} (0x{len(sd):X})")
    # pokeemerald 存档：14 个 4KB 扇区 = 0xE000；实际文件通常是 0x20000（含两个槽）
    sec = sd[0xFF4:0xFF8]  # 扇区 0 的 id 字段位置（0xFF4）
    print("  扇区0 签名/ID 区样例:", sd[0xFF4:0xFFC].hex())
else:
    print("  未找到")
