#!/usr/bin/env python3
"""One-way Windows authority -> Linux build cache. No GUI or ROM execution."""
from pathlib import Path
import argparse,fcntl,hashlib,json,os,subprocess,sys
SOURCE=Path('/mnt/d/Pokemon gba/project')
CACHE=Path('/home/pokemon/projects/emerald-story')
ENTRY=Path('/mnt/d/Pokemon gba')
p=argparse.ArgumentParser();p.add_argument('action',choices=['sync','build','release','record-deltas']);args=p.parse_args()
if Path(__file__).resolve().parents[2]!=SOURCE or not (SOURCE/'.git/HEAD').is_file():
    raise SystemExit('Unexpected authoritative source path; refusing sync.')
if CACHE.resolve()!=Path('/home/pokemon/projects/emerald-story') or not (CACHE/'.git/HEAD').is_file():
    raise SystemExit('Unexpected Linux cache; refusing sync.')
if not (SOURCE/'.windows-source-authority').is_file():raise SystemExit('Authority marker missing.')
if (SOURCE/'.git/index.lock').exists():raise SystemExit('Windows Git is busy; retry after it finishes.')
lock=Path('/home/pokemon/projects/.emerald-story-windows-build.lock')
with lock.open('a') as f:
    try:fcntl.flock(f,fcntl.LOCK_EX|fcntl.LOCK_NB)
    except BlockingIOError:raise SystemExit('Another sync/build is running; wait for completion.')
    if (CACHE/'.git/index.lock').exists():raise SystemExit('Linux cache Git is busy; retry later.')
    print('Authority: D:\\Pokemon gba\\project; synchronizing one-way to Linux build cache.',flush=True)
    # Exact literal destination checked above. Generated build outputs stay in cache.
    # Compare size and nanosecond mtime for incremental sync; first migration is checksum-verified.
    excludes=['/build/','**/__pycache__/','/pokeemerald*.gba','/pokeemerald*.elf','/pokeemerald*.map','/pokeemerald*.sav','/.migration-sync.lock']
    cmd=['rsync','-rlt','--modify-window=-1','--delete']
    for x in excludes:cmd+=['--exclude='+x]
    cmd+=['--',str(SOURCE)+'/',str(CACHE)+'/']
    subprocess.run(cmd,check=True)
    if args.action=='sync':raise SystemExit(0)
    if args.action=='record-deltas':
        manifest=SOURCE/'docs/project/part7-deltas.json';before=manifest.read_bytes()
        subprocess.run(['python3','scripts/dev/record-part7-deltas.py'],cwd=CACHE,check=True)
        if manifest.read_bytes()!=before:raise SystemExit('Windows manifest changed concurrently; review cache result manually.')
        result=(CACHE/'docs/project/part7-deltas.json').read_bytes()
        manifest.write_bytes(result)
        print('Recorded deltas returned to Windows; REVIEW them before building.',flush=True)
        raise SystemExit(0)
    command=['bash','scripts/build.sh']
    if args.action=='release':command.append('--release')
    env=os.environ.copy();env.setdefault('BUILD_JOBS','6')
    subprocess.run(command,cwd=CACHE,env=env,check=True)
    print('Build/checks complete. ROM saved in D:\\Pokemon gba\\artifacts\\current; no emulator started.',flush=True)
