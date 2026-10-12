"""走到手套小兵(12,14)附近并静置，观察是否被自动贴脸（对齐用户报告的场景）。"""
import sys, pathlib, hashlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from runtime import Core
from PIL import Image

SAV = r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav"
ROM = r"E:\es\pokeemerald.gba"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")
UP, DOWN, LEFT, RIGHT, A = 4, 5, 6, 7, 8

c = Core(ROM, SAV)
def save(name):
    b, w, h, pitch = c.pixels
    mode = 'BGRX' if c.fmt == 1 else 'BGR;16'
    Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / name)
def fh():
    b, w, h, pitch = c.pixels
    return hashlib.sha256(bytes(b[:pitch*h])).hexdigest()[:12]

# 启动 + 关闭主动对话（Codex 节奏：按4帧松90帧）
for j in range(45):
    c.run(4, [A]); c.run(90)
for j in range(12):
    c.run(4, [A]); c.run(90)
c.run(120)

sb1 = c.rd(0x030051CC, 4)
def g2(a):
    v = c.rd(a, 2); return v - 0x10000 if v >= 0x8000 else v
def pos(): return g2(sb1 + 0), g2(sb1 + 2)
print("起点 pos =", pos(), flush=True)
save("glv-00-start.png")

def step(dirkey, n, tag):
    for i in range(n):
        c.run(18, [dirkey]); c.run(4)
    c.run(30)
    print(f"  {tag}: pos={pos()}", flush=True)
    save(f"glv-{tag}.png")

# 手套小兵在 (12,14)：先右移后下移
step(RIGHT, 4, "10-right4")
step(DOWN, 7, "20-down7")
c.run(60)
print(f"靠近后 pos={pos()}", flush=True)

# 静置 1500 帧，零输入
prev = fh()
changes = 0
for i in range(25):
    c.run(60)
    h = fh()
    if h != prev:
        changes += 1
        print(f"  静置 {60*(i+1):4d} 帧: 变化 {prev}->{h}", flush=True)
        save(f"glv-idle-{i:02d}.png")
        prev = h
print(f"静置 1500 帧共 {changes} 次变化；结束 pos={pos()}", flush=True)
save("glv-99-final.png")
