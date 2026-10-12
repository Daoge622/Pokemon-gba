import ctypes as C, pathlib, struct, json, sys
from PIL import Image
ROOT=pathlib.Path(__file__).resolve().parent
class Game(C.Structure):
    _fields_=[('path',C.c_char_p),('data',C.c_void_p),('size',C.c_size_t),('meta',C.c_char_p)]
class Variable(C.Structure):
    _fields_=[('key',C.c_char_p),('value',C.c_char_p)]
ENV=C.CFUNCTYPE(C.c_bool,C.c_uint,C.c_void_p)
VID=C.CFUNCTYPE(None,C.c_void_p,C.c_uint,C.c_uint,C.c_size_t)
AUD=C.CFUNCTYPE(None,C.c_int16,C.c_int16)
BATCH=C.CFUNCTYPE(C.c_size_t,C.c_void_p,C.c_size_t)
POLL=C.CFUNCTYPE(None)
INPUT=C.CFUNCTYPE(C.c_int16,C.c_uint,C.c_uint,C.c_uint,C.c_uint)
class Core:
 def __init__(self,rom,save=None):
    self.dll=C.CDLL(str(ROOT/'mgba/mgba_libretro.dll'));self.keys=set();self.frame=0;self.pixels=None;self.fmt=0
    def env(cmd,data):
        if cmd==10:self.fmt=C.cast(data,C.POINTER(C.c_uint))[0];return True
        if cmd==15:return False
        if cmd==17:C.cast(data,C.POINTER(C.c_bool))[0]=False;return True
        if cmd in (3,18):return False
        if cmd==39:C.cast(data,C.POINTER(C.c_uint))[0]=3;return True
        if cmd==52:C.cast(data,C.POINTER(C.c_bool))[0]=True;return True
        return False
    def video(data,w,h,pitch):
        if data:self.pixels=(C.string_at(data,pitch*h),w,h,pitch)
    self.cb=[ENV(env),VID(video),AUD(lambda l,r:None),BATCH(lambda d,n:n),POLL(lambda:None),INPUT(lambda p,d,i,k:int(k in self.keys))]
    for name,cb in zip(['environment','video_refresh','audio_sample','audio_sample_batch','input_poll','input_state'],self.cb):
        getattr(self.dll,'retro_set_'+name)(cb)
    self.dll.retro_init()
    self.dll.retro_get_memory_data.restype=C.c_void_p
    self.dll.retro_get_memory_size.restype=C.c_size_t
    self.dll.retro_serialize_size.restype=C.c_size_t
    self.dll.retro_serialize.argtypes=[C.c_void_p,C.c_size_t];self.dll.retro_serialize.restype=C.c_bool
    self.dll.retro_unserialize.argtypes=[C.c_void_p,C.c_size_t];self.dll.retro_unserialize.restype=C.c_bool
    self.dll.retro_load_game.argtypes=[C.POINTER(Game)];self.dll.retro_load_game.restype=C.c_bool
    self.rombuf=C.create_string_buffer(pathlib.Path(rom).read_bytes());self.game=Game(b'isolated.gba',C.cast(self.rombuf,C.c_void_p),len(self.rombuf)-1,None)
    assert self.dll.retro_load_game(C.byref(self.game))
    if save:
        b=pathlib.Path(save).read_bytes();assert len(b)<=self.dll.retro_get_memory_size(0);C.memmove(self.dll.retro_get_memory_data(0),b,len(b))
 def run(self,n,keys=()):
    self.keys=set(keys)
    for _ in range(n):self.dll.retro_run();self.frame+=1
    self.keys=set()
 def state(self):
    n=self.dll.retro_serialize_size(); b=C.create_string_buffer(n);assert self.dll.retro_serialize(b,n);return bytearray(b.raw)
 def load(self,b):
    buf=C.create_string_buffer(bytes(b));assert self.dll.retro_unserialize(buf,len(b))
 def shot(self,name):
    b,w,h,p=self.pixels
    if self.fmt==1:im=Image.frombytes('RGB',(w,h),b,'raw','BGRX',p)
    else:im=Image.frombytes('RGB',(w,h),b,'raw','BGR;16',p)
    im.resize((w*3,h*3)).save(ROOT/name)
 def rd(self,a,n=4):
    b=self.state();o=(0x21000+a-0x2000000) if a<0x3000000 else (0x19000+a-0x3000000);return int.from_bytes(b[o:o+n],'little')
 def import_myboy(self,filename):
    import gzip
    d=gzip.decompress(pathlib.Path(filename).read_bytes());b=self.state()
    for dest,src,n in [(0x19000,0xb8,0x8000),(0x21000,0x80b8,0x40000),(0x1000,0x480b8,0x18000),(0xc00,0x600b8,0x400),(0x800,0x604b8,0x400),(0x400,0x608b8,0x400)]:b[dest:dest+n]=d[src:src+n]
    regs=list(struct.unpack_from('>16I',d,0x20));psr=struct.unpack_from('>I',d,0x60)[0]
    # MyBoy captured inside BIOS VBlankIntrWait. Restore its saved r4-r6/lr
    # and resume at the exact caller instruction after the completed SWI.
    assert regs[15]==0x210 and psr&0x1f==0x1f
    sp=regs[13];stack=sp-0x3000000+0xb8
    regs[4]=struct.unpack_from('<I',d,stack)[0]
    regs[14]=struct.unpack_from('<I',d,stack+12)[0]
    regs[13]+=16;regs[15]=(regs[14]&~1)+2;psr|=0x20
    struct.pack_into('<16I',b,0x20,*regs);struct.pack_into('<I',b,0x60,psr)
    struct.pack_into('<I',b,0x318,regs[15]-2)
    b[0x2f8:0x300]=bytes(8)
    # IRQ and SVC banked r13/r14, user/system shares current regs.
    for bank,spbank in [(2,0x03007fa0),(3,0x03007fe0)]:
        struct.pack_into('<2I',b,0x70+bank*28,spbank,0)
    self.load(b)
if __name__=='__main__':
    c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.import_myboy(sys.argv[3]);c.run(2);c.shot('initial.png')
    for j in range(250):
        c.run(4,[8]);c.run(56)
        if j%10==0:
            c.shot(f'replay-{j:03d}.png');s=c.state();print(j,hex(struct.unpack_from('<I',s,0x5c)[0]),flush=True)
    (ROOT/'after.state').write_bytes(c.state());c.shot('after.png')
