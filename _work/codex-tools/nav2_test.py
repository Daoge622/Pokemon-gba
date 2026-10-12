"""关掉主动对话 → 走开 → 靠近行走型小兵 → 静置观察自动触发。"""
import sys, pathlib, hashlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from runtime import Core
from PIL import Image

SAV = r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")
UP, DOWN, LEFT, RIGHT, A, B, START = 4, 5, 6, 7, 8, 1, 3

def test(tag, rom):
    c = Core(rom, SAV)
    # 精简启动：标题->主菜单->继续（少按 A，避免对 NPC 开对话）
    for j in range(30):
        c.run(6, [A]); c.run(24)
    sb1 = c.rd(0x030051CC, 4)
    def g2(a):
        v = c.rd(a, 2); return v - 0x10000 if v >= 0x8000 else v
    def pos(): return g2(sb1 + 0), g2(sb1 + 2)
    print(f"\n[{tag}] 起点 pos={pos()}", flush=True)

    # 若开在对话里，先关掉
    for j in range(6):
        c.run(4, [A]); c.run(20)
    # 立刻往下走（离开女孩视线，也离开她的对话触发范围）
    for j in range(6):
        c.run(18, [UP]); c.run(6)
    c.run(40)
    print(f"[{tag}] 向上走位后 pos={pos()}", flush=True)

    for j in range(8):
        c.run(18, [RIGHT]); c.run(6)
    c.run(40)
    print(f"[{tag}] 向右走位后 pos={pos()}", flush=True)

    def save(name):
        b, w, h, pitch = c.pixels
        mode = 'BGRX' if c.fmt == 1 else 'BGR;16'
        Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / name)
    save(f"nav2-{tag}-arrived.png")

    # 静置 1200 帧，不做任何输入
    b, w, h, pitch = c.pixels
    prev = hashlib.sha256(bytes(b[:pitch*h])).hexdigest()[:12]
    changes = 0
    for i in range(20):
        c.run(60)
        b, w, h, pitch = c.pixels
        hh = hashlib.sha256(bytes(b[:pitch*h])).hexdigest()[:12]
        if hh != prev:
            changes += 1
            print(f"[{tag}]   静置 {60*(i+1):4d} 帧: 变化 {prev}->{hh}", flush=True)
            Image.frombytes('RGB', (w, h), b, 'raw',
                            'BGRX' if c.fmt == 1 else 'BGR;16', pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / f"nav2-{tag}-chg{i:02d}.png")
            prev = hh
    print(f"[{tag}] 静置 1200 帧共 {changes} 次画面变化；结束 pos={pos()}", flush=True)

for tag, rom in [
    ("srcbuild", r"E:\es\pokeemerald.gba"),
]:
    test(tag, rom)
