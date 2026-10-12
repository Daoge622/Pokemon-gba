"""加载基地(24/87)存档，检查战后场景是否异常。"""
import sys, pathlib
sys.path.insert(0, r"E:\Pekemon Gba\_work\codex-tools")
from runtime import Core
from PIL import Image

ROM = r"E:\es\pokeemerald.gba"
SAV = r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")
OUT.mkdir(parents=True, exist_ok=True)

def shot(c, name):
    b, w, h, pitch = c.pixels
    mode = 'BGRX' if c.fmt == 1 else 'BGR;16'
    Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / name)

c = Core(ROM, SAV)
print("loaded", flush=True)
for j in range(80):
    c.run(4, [8]); c.run(26)

sb1 = c.rd(0x030051CC, 4)
def s8(a): 
    v = c.rd(a, 1); return v - 256 if v >= 128 else v
x = c.rd(sb1 + 0, 2); x = x - 0x10000 if x >= 0x8000 else x
y = c.rd(sb1 + 2, 2); y = y - 0x10000 if y >= 0x8000 else y
grp, num = s8(sb1 + 4), s8(sb1 + 5)
lock = c.rd(0x030008A7, 1)
cb2 = c.rd(0x03002418, 4)
print(f"pos=({x},{y}) map={grp}/{num} lock={lock} cb2=0x{cb2:08X}", flush=True)
shot(c, "g01-base.png")

# 检查便当(719)/手套(720)小兵的击败标志: flag = 0x500 + trainer
def flag_get(n):
    sb = sb1
    q = sb + 0x1270 + n // 8
    return (c.rd(q, 1) >> (n % 8)) & 1
for tid, name in [(719, "便当小兵"), (720, "手套小兵"), (729, "胖丁女孩"), (0x500 + 3, "晕船(海洋队)")]:
    print(f"  trainer {tid} ({name}) 已击败 = {flag_get(0x500 + tid)}", flush=True)

# 走一圈看看会不会触发对话
for k in range(6):
    c.run(16, [4]); c.run(30)
    print(f"  walk{k}: pos=({c.rd(sb1+0,2)},{c.rd(sb1+2,2)}) lock={c.rd(0x030008A7,1)}", flush=True)
shot(c, "g02-after-walk.png")
print("done", flush=True)
