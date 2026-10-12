"""同按键节奏对比：对话到底能不能关掉 / 玩家能不能动。"""
import sys, pathlib, hashlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from runtime import Core
from PIL import Image

SAV = r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")
UP, DOWN, LEFT, RIGHT, A = 4, 5, 6, 7, 8

ROMS = {
    "srcbuild": r"E:\es\pokeemerald.gba",
    "codex":    r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba",
    "baseline": r"E:\Pekemon Gba\EmeraldStory-一周目完整版.gba",
}

def run(tag, rom):
    c = Core(rom, SAV)
    # Codex 的节奏：按 A 4 帧、松 90 帧
    for j in range(45):
        c.run(4, [A]); c.run(90)
    sb1 = c.rd(0x030051CC, 4)
    def g2(a):
        v = c.rd(a, 2); return v - 0x10000 if v >= 0x8000 else v
    def pos(): return g2(sb1 + 0), g2(sb1 + 2)
    p0 = pos()
    # 再按 A 收尾（Codex 在验证里也这么做）
    for j in range(12):
        c.run(4, [A]); c.run(90)
    c.run(120)
    p1 = pos()
    # 试着走：如果对话真的关了，位置应该变化
    for j in range(8):
        c.run(16, [RIGHT]); c.run(6)
    c.run(60)
    p2 = pos()
    b, w, h, pitch = c.pixels
    mode = 'BGRX' if c.fmt == 1 else 'BGR;16'
    Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / f"pace-{tag}.png")
    moved = "能移动" if p2 != p0 else "仍不能移动"
    print(f"[{tag:9}] 启动后 pos={p0} → 收尾后 pos={p1} → 尝试右移后 pos={p2}   {moved}", flush=True)

for tag, rom in ROMS.items():
    run(tag, rom)
