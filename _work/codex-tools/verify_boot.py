"""无窗口 mGBA 冷启动验证：新构建 ROM + 用户存档（副本）。"""
import sys, pathlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from runtime import Core
from PIL import Image

ROM = r"E:\es\pokeemerald.gba"
SAV = r"E:\Pekemon Gba\_work\verif\user-save-copy.sav"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")
OUT.mkdir(parents=True, exist_ok=True)

def shot(c, path):
    b, w, h, pitch = c.pixels
    mode = 'BGRX' if c.fmt == 1 else 'BGR;16'
    im = Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch)
    im.resize((w * 3, h * 3), Image.NEAREST).save(path)

c = Core(ROM, SAV)
print("ROM + save loaded into core", flush=True)

def ptrs():
    return c.rd(0x030051C8, 4), c.rd(0x030051CC, 4)

def pos_of(p1):
    if 0x02000000 <= p1 < 0x02040000:
        return c.rd(p1, 2), c.rd(p1 + 2, 2)
    return None, None

p2, p1 = ptrs()
print(f"t=0   SB2={p2:08X} SB1={p1:08X}", flush=True)

rows = []
for j in range(45):
    c.run(4, [8])     # 按 A 4 帧
    c.run(26)         # 松手 26 帧
    if j % 3 == 0 or j >= 40:
        p2, p1 = ptrs()
        x, y = pos_of(p1)
        row = f"j={j:3d} frame={c.frame:5d} SB2={p2:08X} SB1={p1:08X} pos=({x},{y})"
        print(row, flush=True)
        rows.append(row)
        shot(c, OUT / f"v{j:03d}.png")

(OUT / "probe-log.txt").write_text("\n".join(rows), encoding="utf-8")
print("done", flush=True)
