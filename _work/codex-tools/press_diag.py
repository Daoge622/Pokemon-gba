"""逐次按键诊断：战后对话到底能不能推进 / 是不是在重复触发。"""
import sys, pathlib, hashlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from runtime import Core
from PIL import Image

SAV = r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")
ROMS = {
    "srcbuild": r"E:\es\pokeemerald.gba",
    "codex":    r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba",
    "baseline": r"E:\Pekemon Gba\EmeraldStory-一周目完整版.gba",
}
# 我的 ROM 的真实符号地址（来自 pokeemerald.map）
GMAIN   = 0x030066C8     # gMain
SB1PTR  = 0x030051CC     # gSaveBlock1Ptr

def frame_bytes(c):
    b, w, h, pitch = c.pixels
    return bytes(b[:pitch*h]), w, h, pitch

def save(c, name):
    b, w, h, pitch = frame_bytes(c)
    mode = 'BGRX' if c.fmt == 1 else 'BGR;16'
    Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / name)

for tag, rom in ROMS.items():
    c = Core(rom, SAV)
    for j in range(80):
        c.run(4, [8]); c.run(26)
    print(f"\n[{tag}] 到达 Overworld", flush=True)
    hashes = []
    for i in range(12):
        for j in range(2):
            c.run(4, [8]); c.run(22)
        b, _, _, _ = frame_bytes(c)
        hh = hashlib.sha256(b).hexdigest()[:12]
        hashes.append(hh)
        save(c, f"k-{tag}-{i:02d}.png")
        cb2 = c.rd(GMAIN + 8, 4)
        print(f"   press{i:02d}  frame_hash={hh}  cb2=0x{cb2:08X}", flush=True)
    uniq = len(set(hashes))
    print(f"   -> 12 次按键共 {uniq} 种不同画面 {'（画面在变=能推进）' if uniq > 1 else '（画面完全不变=卡死）'}", flush=True)
