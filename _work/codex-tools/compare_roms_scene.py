"""对比实验：同一存档 + 不同 ROM，看战后是否会卡在对话里。"""
import sys, pathlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from runtime import Core
from PIL import Image

SAV = r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")
OUT.mkdir(parents=True, exist_ok=True)

ROMS = {
    "srcbuild": r"E:\es\pokeemerald.gba",
    "codex":    r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba",
    "baseline": r"E:\Pekemon Gba\EmeraldStory-一周目完整版.gba",
}

def shot(c, name):
    b, w, h, pitch = c.pixels
    mode = 'BGRX' if c.fmt == 1 else 'BGR;16'
    Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / name)

for tag, rom in ROMS.items():
    c = Core(rom, SAV)
    # 启动到 Overworld：连按 A
    for j in range(80):
        c.run(4, [8]); c.run(26)
    sb1 = c.rd(0x030051CC, 4)
    def g2(a):
        v = c.rd(a, 2); return v - 0x10000 if v >= 0x8000 else v
    x, y = g2(sb1 + 0), g2(sb1 + 2)
    cb2 = c.rd(0x03002418, 4)
    shot(c, f"cmp-{tag}-A.png")
    print(f"[{tag:9}] 进入后 pos=({x},{y}) cb2=0x{cb2:08X}", flush=True)

    # 静置 600 帧（不按键），看是否自动触发对话
    c.run(600)
    shot(c, f"cmp-{tag}-B-idle600.png")
    sb1b = c.rd(0x030051CC, 4)
    print(f"[{tag:9}] 静置600帧后 pos=({g2(sb1b+0)},{g2(sb1b+2)}) cb2=0x{c.rd(0x03002418,4):08X}", flush=True)

    # 再按 A 40 次，看对话能否关闭
    for j in range(40):
        c.run(4, [8]); c.run(26)
    c.run(120)
    shot(c, f"cmp-{tag}-C-afterA.png")
    sb1c = c.rd(0x030051CC, 4)
    print(f"[{tag:9}] 连按A后 pos=({g2(sb1c+0)},{g2(sb1c+2)}) cb2=0x{c.rd(0x03002418,4):08X}", flush=True)
    print(flush=True)
