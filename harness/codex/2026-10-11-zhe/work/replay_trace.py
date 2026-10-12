from runtime import *
import hashlib
out=ROOT.parent/'outputs';trace=[]
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'battle-ended.state').read_bytes())
def snapshot(label):
 s=c.state();sb=struct.unpack_from('<I',s,0x19000+0x238c)[0]
 flag=s[0x21000+sb-0x2000000+0x1270+0x1aa//8]
 rec={'label':label,'frame':c.frame,'callback2':hex(struct.unpack_from('<I',s,0x19000+0x2418)[0]),'pc':hex(struct.unpack_from('<I',s,0x5c)[0]),'grave_worker_won':bool(flag&4)}
 trace.append(rec);return rec
def tap(k,n=1):
 for _ in range(n):c.run(4,[k]);c.run(70)
tap(7);tap(5,2);tap(8,2);c.run(180)
snapshot('Vaporeon selected')
for j in range(125):
 tap(8);record=snapshot(f'A cycle {j}')
 if j==85:(ROOT/'before-victory.state').write_bytes(c.state())
 if j==100:c.shot('trace-victory.png')
 if j>20 and record['callback2']=='0x81be4f9':tap(0,3)
for j in range(20):c.run(4,[0]);c.run(30)
record=snapshot('dialogue dismissed');c.shot('trace-field.png');c.run(50,[5]);c.run(50);snapshot('walking after battle');c.shot('trace-walking.png')
assert record['callback2']=='0x81b9521' and record['grave_worker_won']
data={'rom_sha256':hashlib.sha256(pathlib.Path(sys.argv[1]).read_bytes()).hexdigest(),'initial_checkpoint_sha256':hashlib.sha256((ROOT/'battle-ended.state').read_bytes()).hexdigest(),'note':'Checkpoint obtained from imported MyBoy mid-battle state during earlier normal input replay. ROM and battle HP/outcome were not patched. MyBoy BIOS, audio/timer internals are not fully imported. This is mGBA evidence, not a MyBoy reproduction.','trace':trace}
(out/'headless-replay.json').write_text(json.dumps(data,ensure_ascii=False,indent=2),encoding='utf8')
print('completed',record,flush=True)
