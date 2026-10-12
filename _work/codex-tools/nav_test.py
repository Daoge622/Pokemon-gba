"""用游戏内输入走到行走型小兵附近并静置观察（不改存档）。"""
import sys, pathlib, hashlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from runtime import Core
from PIL import Image

SAV = r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav"
ROM = r"E:\es\pokeemerald.gba"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")

UP, DOWN, LEFT, RIGHT, A = 4, 5, 6, 7, 8

c = Core(ROM, SAV)
for j in range(80):
    c.run(4, [A]); c.run(26)
sb1 = c.rd(0x030051CC, 4)
def g2(a):
    v = c.rd(a, 2); return v - 0x10000 if v >= 0x8000 else v
def pos():
    return g2(sb1 + 0), g2(sb1 + 2)
def save(name):
    b, w, h, pitch = c.pixels
    mode = 'BGRX' if c.fmt == 1 else 'BGR;16'
    Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / name)

print("起点 pos =", pos(), flush=True)
save("nav-00-start.png")

def walk(dirkey, steps, tag):
    for i in range(steps):
        c.run(16, [dirkey]); c.run(4)
    c.run(30)
    print(f"  {tag}: pos={pos()}", flush=True)
    save(f"nav-{tag}.png")

# 探路：先向右走，看能到哪
walk(RIGHT, 10, "10-right")
walk(DOWN, 6, "20-down")
walk(RIGHT, 6, "30-right2")
