#!/usr/bin/env python3
"""Explicitly refresh PART7 review deltas after an intentional source edit.
Not called by builds/tests; records hunks for strict legacy regression adapters.
"""
from pathlib import Path
import subprocess,json,difflib,hashlib
R=Path(__file__).resolve().parents[2];PRE='pre-part7-implementation'
def git(*args):return subprocess.check_output(['git',*args],cwd=R)
paths=set(git('diff','--name-only',PRE).decode().splitlines())|set(git('ls-files','--others','--exclude-standard').decode().splitlines())
d={'baseline':PRE,'baseline_commit':git('rev-parse',PRE).decode().strip(),'text':{},'binary':{},'new_files':[],'sha256':{}}
for f in sorted(paths):
 if not f.startswith(('data/','src/','include/','asm/')):continue
 p=R/f
 if not p.is_file():raise AssertionError(('deleted source',f))
 new=p.read_bytes(); prior=subprocess.run(['git','show',PRE+':'+f],cwd=R,capture_output=True)
 if prior.returncode:
  d['new_files'].append(f);d['sha256'][f]=hashlib.sha256(new).hexdigest();continue
 old=prior.stdout
 if new==old:continue
 d['sha256'][f]=hashlib.sha256(new).hexdigest()
 try:a,b=old.decode('utf-8'),new.decode('utf-8')
 except UnicodeDecodeError:
  d['binary'][f]={'before':hashlib.sha256(old).hexdigest(),'after':hashlib.sha256(new).hexdigest()};continue
 al,bl=a.splitlines(keepends=True),b.splitlines(keepends=True)
 d['text'][f]=[{'at':i,'old':''.join(al[i:j]),'new':''.join(bl[k:l])} for op,i,j,k,l in difflib.SequenceMatcher(None,al,bl,autojunk=False).get_opcodes() if op!='equal']
(R/'docs/project/part7-deltas.json').write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n')
print('Recorded',len(d['text']),'text deltas,',len(d['new_files']),'new source files,',len(d['binary']),'existing binary deltas')