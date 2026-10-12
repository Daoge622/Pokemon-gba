"""把玩家移到行走型小兵附近，静置观察是否被自动贴脸。

目标：MagmaHideout_2F_1R 的两个 WALK_SEQUENCE 小兵
  便当 pos=(18,19) sight=1
  手套 pos=(12,14) sight=3
存档格式：SaveBlock1 起始 = 逻辑扇区 id==1 的物理扇区；pos 在偏移 0(2B x)、2(2B y)。
"""
import sys, pathlib, struct, hashlib, shutil
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from runtime import Core
from PIL import Image

SAV_SRC = r"C:\Users\DaoGe\Documents\Codex\2026-10-11\zhe\work\dialogue-normal-save.sav"
ROM = r"E:\es\pokeemerald.gba"
OUT = pathlib.Path(r"E:\Pekemon Gba\_work\verif")

def make_save(target_x, target_y, tag):
    raw = bytearray(pathlib.Path(SAV_SRC).read_bytes())
    # 找所有逻辑扇区 id == 1（SaveBlock1 的第一段）
    hits = []
    for base in range(0, len(raw), 0x1000):
        if base + 0x1000 > len(raw):
            break
        sid = struct.unpack_from('<H', raw, base + 0xFF4)[0]
        if sid == 1:
            hits.append(base)
    assert hits, "no logical sector 1"
    for base in hits:
        struct.pack_into('<hh', raw, base + 0, target_x, target_y)   # pos.x / pos.y
        # 重算扇区校验和：前 0xFF4 字节求和
        s = sum(raw[base:base + 0xFF4]) & 0xFFFF
        struct.pack_into('<H', raw, base + 0xFF6, s)
    p = OUT / f"save-{tag}.sav"
    p.write_bytes(raw)
    return p, hits

def run(tag, target_x, target_y):
    sav, hits = make_save(target_x, target_y, tag)
    print(f"\n[{tag}] 目标 pos=({target_x},{target_y})  改写扇区 {[hex(h) for h in hits]}", flush=True)
    c = Core(ROM, str(sav))
    for j in range(80):
        c.run(4, [8]); c.run(26)
    sb1 = c.rd(0x030051CC, 4)
    def g2(a):
        v = c.rd(a, 2); return v - 0x10000 if v >= 0x8000 else v
    print(f"   进入后 pos=({g2(sb1+0)},{g2(sb1+2)})", flush=True)
    b, w, h, pitch = c.pixels
    mode = 'BGRX' if c.fmt == 1 else 'BGR;16'
    Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / f"walk-{tag}-enter.png")
    # 静置 1200 帧
    prev = hashlib.sha256(bytes(b[:pitch*h])).hexdigest()[:12]
    for i in range(20):
        c.run(60)
        b, w, h, pitch = c.pixels
        hh = hashlib.sha256(bytes(b[:pitch*h])).hexdigest()[:12]
        if hh != prev:
            print(f"   静置 {60*(i+1):4d} 帧: 画面变化 {prev} -> {hh}", flush=True)
            Image.frombytes('RGB', (w, h), b, 'raw', mode, pitch).resize((w*3, h*3), Image.NEAREST).save(OUT / f"walk-{tag}-chg{i:02d}.png")
            prev = hh
    sb1 = c.rd(0x030051CC, 4)
    print(f"   结束 pos=({g2(sb1+0)},{g2(sb1+2)})", flush=True)

run("bento", 18, 20)     # 便当下方一格
run("gloves", 12, 15)    # 手套下方一格
