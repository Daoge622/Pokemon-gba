"""修复版 ROM 的存档兼容性复验（用户存档 + Codex 基地存档）。"""
import sys, pathlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from runtime import Core
from PIL import Image

ROM = r"E:\es\pokeemerald.gba"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")
CASES = {
    "user-route120": r"E:\Pekemon Gba\_work\verif\user-save-copy.sav",
    "codex-base":    r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav",
}
for tag, sav in CASES.items():
    c = Core(ROM, sav)
    for j in range(80):
        c.run(4, [8]); c.run(26)
    sb1 = c.rd(0x030051CC, 4)
    def g2(a):
        v = c.rd(a, 2); return v - 0x10000 if v >= 0x8000 else v
    def s8(a):
        v = c.rd(a, 1); return v - 256 if v >= 128 else v
    x, y = g2(sb1 + 0), g2(sb1 + 2)
    grp, num = s8(sb1 + 4), s8(sb1 + 5)
    b, w, h, pitch = c.pixels
    Image.frombytes('RGB', (w, h), b, 'raw',
                    'BGRX' if c.fmt == 1 else 'BGR;16', pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / f"fix-verify-{tag}.png")
    ok = "OK" if 0 <= grp < 40 and 0 <= num < 255 and sb1 >= 0x02000000 else "SUSPECT"
    print(f"[{tag:14}] pos=({x},{y}) map={grp}/{num}  {ok}", flush=True)
