from runtime import *
c=Core(sys.argv[1],sys.argv[2]);c.run(100);c.load((ROOT/'postbattle-free.state').read_bytes());c.run(10);c.run(4,[3]);c.run(80);c.shot('save-menu.png')
(ROOT/'save-menu.state').write_bytes(c.state())
for _ in range(4):c.run(4,[5]);c.run(20)
c.run(4,[8]);c.run(80);c.shot('save-confirm.png')
(ROOT/'save-confirm.state').write_bytes(c.state())
c.run(4,[8]);c.run(120);c.shot('save-overwrite.png')
(ROOT/'save-overwrite.state').write_bytes(c.state())
c.run(4,[8]);c.run(480);c.shot('save-complete.png')
output=ROOT.parent/'outputs/守墓人战后普通存档.sav'
output.write_bytes(C.string_at(c.dll.retro_get_memory_data(0),c.dll.retro_get_memory_size(0)))
print('saved',str(output),output.stat().st_size,flush=True)
