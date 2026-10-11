#!/usr/bin/env python3
"""Opt-in mGBA core smoke tests. Not part of automatic builds; requires explicit ROM execution permission.
Fixtures change emulator RAM only; input ROM/save are never patched or overwritten.
"""
from pathlib import Path
import argparse, subprocess, re, json, hashlib, shutil
R=Path(__file__).resolve().parents[2]
a=argparse.ArgumentParser();a.add_argument('--allow-rom-execution',action='store_true');a.add_argument('--rom',required=True,type=Path);a.add_argument('--elf',required=True,type=Path);a.add_argument('--save',required=True,type=Path);a.add_argument('--output',required=True,type=Path);a.add_argument('--expect-old-capture-bug',action='store_true')
args=a.parse_args()
if not args.allow_rom_execution:a.error('User permission to execute ROMs is required; pass --allow-rom-execution only after authorization.')
for p in [args.rom,args.elf,args.save]:assert p.is_file(),p
assert args.save.stat().st_size==131072,'Expected a 128 KiB ordinary game save, not an emulator state.'
args.output.mkdir(parents=True,exist_ok=True);out=args.output.resolve()
assert out not in [args.rom.resolve().parent,args.save.resolve().parent],'Use a separate QA directory.'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
original={str(p.resolve()):sha(p) for p in [args.rom,args.elf,args.save]}
nm=subprocess.check_output(['arm-none-eabi-nm',str(args.elf.resolve())],text=True)
(out/'symbols.txt').write_text(nm,encoding='utf-8')
symbols={};types={}
for line in nm.splitlines():
 m=re.fullmatch(r'([0-9a-f]+) ([A-Za-z]) (\S+)',line)
 if m: symbols.setdefault(m[3],[]).append(int(m[1],16));types[m[3]]=m[2]
def sym(name):return symbols[name][0]
def fptr(name):return sym(name)|1
# Static duplicate names exist in link/recorded controllers; select the player implementation beside its caller.
action=min(symbols['HandleInputChooseAction'],key=lambda x:abs(x-sym('PlayerHandleChooseAction')))|1
main=sym('gMain');party=sym('gParties')
subprocess.run(['cc',str(R/'scripts/qa/gameplay-probe.c'),'-o',str(out/'probe'),'-lmgba'],check=True)
shutil.copyfile(args.save,out/'input-copy.sav')
load='''frames 4000
frames 4 8
frames 500
frames 4 1
frames 700
'''
def expect(addr,value,width=4,mask=None):return f'expect {hex(addr) if isinstance(addr,int) else addr} {value} {width}'+(f' {mask}' if mask else '')+'\n'
def dex():return f'''write {hex(main+4)} {hex(fptr('CB2_OpenPokedex'))}
write {hex(main+0x438)} 0 1
frames 700
screen dex-open.png
frames 4 2
frames 400
frames 4 2
frames 100
read sPokedexView
screen dex-closed.png
'''
def tap(k,n=100):return f'frames 4 {k}\nframes {n}\n'
def capture(full=True,after_dex=False,known=False):
 # Reuse valid encrypted Pokemon records from the isolated pre-fix save.
 # Release LTO inlines the scripting creation helpers; no ROM modifications are needed.
 c=load
 if full:
  c+=f'copy {hex(party+500)} {hex(party+200)} 100\n'
  for slot in [2,3,4]:c+=f'copy {hex(party+slot*100)} {hex(party+100)} 100\n'
  c+='write gPartiesCount 6 1\n'
 else:c+=f'zero {hex(party+100)} 500\nwrite gPartiesCount 1 1\n'
 # ExpShare is already enabled in the input fixture.
 if after_dex:c+=dex()
 if known:c+='call GetSetPokedexFlag 296 3\n'
 else:c+='call GetSetPokedexFlag 296 1\n' # fixture must not have previously caught Makuhita
 c+='call AddBagItem 1 20\ncall CreateScriptedWildMon 296 10 0\n'
 # Faint-safe deterministic fixture: one HP and sleep guarantee a normal Poke Ball succeeds.
 enemy=party+600
 c+=f'write 0x03007cc0 1\ncall SetMonData {hex(enemy)} 10 0x03007cc0\nwrite 0x03007cc0 7\ncall SetMonData {hex(enemy)} 1 0x03007cc0\n'
 c+='write 0x03007cc0 33\ncall SetMonData gParties 20 0x03007cc0\nwrite 0x03007cc0 35\ncall SetMonData gParties 24 0x03007cc0\n'
 c+='call BattleSetup_StartWildBattle\nframes 550\n'+f'wait gBattlerControllerFuncs {hex(action)} 600 1\n'
 # The R shortcut uses the last chosen ball from the action menu; open the actual bag for a fresh fixture.
 c+=tap(16,10)+tap(1,140)+tap(16,100)+tap(1,30)+tap(1,600)
 c+=''.join(tap(2) for _ in range(45))
 c+='read gBattleOutcome 1\nread gPartiesCount 1\nstatus\nscreen result.png\n'
 c+=expect('gBattleOutcome',7,1)+expect(main+0x439,0,1,'0x2')+expect('sPokedexView',0)
 c+='call GetSetPokedexFlag 296 1\n'
 return c
def faint_win():
 c=capture(full=False).split("call BattleSetup_StartWildBattle")[0]
 c+='write 0x03007cc0 33\ncall SetMonData gParties 20 0x03007cc0\nwrite 0x03007cc0 35\ncall SetMonData gParties 24 0x03007cc0\n'
 c+='call BattleSetup_StartWildBattle\nframes 550\n'+f'wait gBattlerControllerFuncs {hex(action)} 600 1\n'
 c+=tap(1,20)+tap(1,500)+''.join(tap(2) for _ in range(30))
 c+='status\nscreen result.png\n'+expect('gBattleOutcome',1,1)+expect(main+0x439,0,1,'0x2')
 return c
def faint_loss():
 enemy=party+600
 c=load+f'zero {hex(party+100)} 500\nwrite gPartiesCount 1 1\ncall CreateScriptedWildMon 296 100 0\n'
 c+='write 0x03007cc0 1\ncall SetMonData gParties 10 0x03007cc0\n'
 c+=f'write 0x03007cc0 33\ncall SetMonData {hex(enemy)} 20 0x03007cc0\n'
 for field in [21,22,23]:c+=f'write 0x03007cc0 0\ncall SetMonData {hex(enemy)} {field} 0x03007cc0\n'
 c+=f'write 0x03007cc0 35\ncall SetMonData {hex(enemy)} 24 0x03007cc0\n'
 c+='call BattleSetup_StartWildBattle\nframes 550\n'+f'wait gBattlerControllerFuncs {hex(action)} 600 1\n'
 c+=''.join(tap(1) for _ in range(50))
 c+='status\nscreen result.png\n'+expect('gBattleOutcome',2,1)+expect(main+0x439,0,1,'0x2')
 return c
def rusturf_rescue():
 c=load+"""call FlagClear 0x36E
call FlagClear 0x370
call FlagSet 0x36F
call FlagClear 0x8F
call FlagSet 0x8E
call VarSet 0x409A 3
call SetWarpDestination 24 4 255 13 5
call WarpIntoMap
"""
 c+=f'write {hex(main+4)} {hex(fptr("CB2_LoadMap"))}\nwrite {hex(main+0x438)} 0 1\nframes 700\n'
 c+='screen before-rescue.png\nwrite gSpecialVar_LastTalked 6 2\nwatch gObjectEvents\ncall ScriptContext_SetupScript RusturfTunnel_EventScript_Grunt\n'
 c+=f'wait gBattlerControllerFuncs {hex(action)} 2400 1\n'
 c+=''.join(tap(1) for _ in range(80))
 c+='expectcall FlagGet 1 0x8F\nexpectcall FlagGet 0 0x8E\nexpectcall VarGet 4 0x405A\nexpectcall VarGet 1 0x4090\nexpectcall ArePlayerFieldControlsLocked 0\nstatus\nscreen result.png\n'
 return c
results=[]
def run(name,commands,expect_failure=False):
 d=out/name;d.mkdir(exist_ok=True);(d/'commands.txt').write_text(commands,encoding='utf-8')
 proc=subprocess.run([str(out/'probe'),'--allow-rom-execution',str(args.rom.resolve()),str(out/'symbols.txt'),str(d/'commands.txt'),str(out/'input-copy.sav')],cwd=d,capture_output=True,text=True,timeout=90)
 (d/'result.log').write_text(proc.stdout+proc.stderr,encoding='utf-8')
 ok=(proc.returncode!=0 and 'got=00000000 expected=00000007' in proc.stderr) if expect_failure else proc.returncode==0 and 'TIMEOUT' not in proc.stdout
 assert ok,(name,proc.returncode,(proc.stdout+proc.stderr)[-1600:])
 results.append({'case':name,'result':'EXPECTED_FAIL_REPRODUCED' if expect_failure else 'PASS'})
 print(results[-1])
run('old-save-continue',load+expect('gPartiesCount',3,1)+expect(main,fptr('CB1_Overworld'))+'call GetMonData3 gParties 18 0\ncall FlagGet 0x867\nscreen dewford.png\n')
run('capture-after-dex',capture(after_dex=True),args.expect_old_capture_bug)
if not args.expect_old_capture_bug:
 run('capture-free-slot',capture(full=False))
 run('capture-full-party-exp-share-egg',capture())
 run('capture-owned-critical',capture(known=True))
 run('opponent-faint-return-to-field',faint_win())
 run('player-faint-blackout-return-to-field',faint_loss())
 if all(x in symbols for x in ['FlagClear','FlagSet','VarSet','SetWarpDestination','VarGet','ArePlayerFieldControlsLocked']):run('rusturf-briney-peeko-rescue',rusturf_rescue())
 else:results.append({'case':'rusturf-briney-peeko-rescue','result':'SKIP','reason':'Release LTO removed fixture initialization helpers; normal build runs the full event.'})
for p,h in original.items():assert sha(Path(p))==h,('input changed',p)
report={'rom_sha256':sha(args.rom),'elf_sha256':sha(args.elf),'input_save_sha256':sha(args.save),'cases':results,'inputs_unchanged':True,'scope':'Runtime fixture smoke tests only; not complete story acceptance.'}
(out/'results.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
print('Inputs preserved; all requested cases finished.')