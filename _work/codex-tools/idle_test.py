"""静置测试：先关掉对话，然后不做任何输入，看 NPC 是否会自动再次触发对话。"""
import sys, pathlib, hashlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from runtime import Core
from PIL import Image

SAV = r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")
ROMS = {
    "srcbuild": r"E:\es\pokeemerald.gba",
    "codex":    r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\outputs\EmeraldStory-一周目完整版-组队与战后对话修复.gba",
}

def save(c, name):
    b, w, h, pitch = c.pixels
    mode = 'BGRX' if c.fmt == 1 else 'BGR;16'
    Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / name)

def fh(c):
    b, w, h, pitch = c.pixels
    return hashlib.sha256(bytes(b[:pitch*h])).hexdigest()[:12]

for tag, rom in ROMS.items():
    c = Core(rom, SAV)
    for j in range(80):
        c.run(4, [8]); c.run(26)
    # 关掉可能存在的对话
    for j in range(14):
        c.run(4, [8]); c.run(26)
    c.run(120)
    base = fh(c)
    save(c, f"idle-{tag}-closed.png")
    print(f"\n[{tag}] 对话关闭后 baseline hash={base}", flush=True)

    # 静置 900 帧，不做任何输入
    prev = base
    changes = 0
    for i in range(15):
        c.run(60)
        h = fh(c)
        if h != prev:
            changes += 1
            print(f"   静置第 {60*(i+1):4d} 帧: 画面变化 {prev} -> {h}", flush=True)
            save(c, f"idle-{tag}-chg{i:02d}.png")
            prev = h
    print(f"   -> 静置 900 帧共 {changes} 次画面变化", flush=True)
    print(f"   -> 最终 hash={fh(c)}", flush=True)
