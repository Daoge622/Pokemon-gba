import sys, pathlib
sys.path.insert(0, r"E:\Pekemon Gba\_work\codex-tools")
from runtime import Core

c = Core(r"E:\es\pokeemerald.gba", r"E:\Pekemon Gba\_work\verif\user-save-copy.sav")
for j in range(45):
    c.run(4, [8]); c.run(26)

sb2 = c.rd(0x030051C8, 4)
sb1 = c.rd(0x030051CC, 4)

def s16(a):
    v = c.rd(a, 2)
    return v - 0x10000 if v >= 0x8000 else v

x, y = s16(sb1 + 0), s16(sb1 + 2)
grp, num, warp = s16(sb1 + 4), s16(sb1 + 6), s16(sb1 + 8)
print(f"gSaveBlock1Ptr = 0x{sb1:08X}")
print(f"玩家坐标 pos = ({x}, {y})")
print(f"所在地图 location: mapGroup={grp}  mapNum={num}  warpId={warp}")

# 玩家名 / 训练家 ID（确认这是用户存档而不是空档）
tid = c.rd(sb2 + 0x0A, 4) if sb2 else 0
print(f"TrainerId raw = 0x{tid:08X}")

# 徽章：SaveBlock1 里的 badge flags 区，简单验证存档非空
print(f"SB2 前 32 字节区非空: {sum(1 for i in range(0,32) if c.rd(sb2+i,1)) > 0}")
