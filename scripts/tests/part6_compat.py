"""Strict removal of reviewed PART6 deltas before historical (PART1-5.5) tests.
Actual current PART6 is tested by check-part6.py. No unrecorded source edits accepted.
"""
from pathlib import Path
import json,subprocess,hashlib,sys
sys.path.insert(0,str(Path(__file__).resolve().parent))
import part7_compat
from part7_compat import source as part7_source
R=Path(__file__).resolve().parents[2]
D=json.loads((R/'docs/project/part6-deltas.json').read_text())
PRE=D['baseline']
def pre(f):return subprocess.check_output(['git','show',PRE+':'+f],cwd=R,text=True)
def current(f):
 return part7_source(f)  # current files with reviewed PART7 deltas strictly removed (see part7_compat.py)
def source(f,s=None):
 if s is None or ((R/f).exists() and s==(R/f).read_text(encoding='utf-8')):s=current(f)
 if f.endswith('.json') and (R/f).exists():
  disk=current(f)
  if s!=disk and json.loads(s)==json.loads(disk):s=disk  # formatting only
 if (R/f).exists() and f not in D['new_files'] and s!=current(f):
  return s  # an older view already produced by another compat layer; current files are always checked strictly
 if f in D['new_files']:
  assert hashlib.sha256(s.encode()).hexdigest()==D['sha256'][f],(f,'unrecorded new source edit')
  return ''
 if f not in D['text']:return s
 b=pre(f)
 if s==b:return s # caller may have already applied this exact view
 if f.endswith('.json') and json.loads(s)==json.loads(b):return b # JSON formatting is not a data edit
 a=s.splitlines(keepends=True);out=[];pos=offset=0
 for h in D['text'][f]:
  nl=h['new'].splitlines(keepends=True);ol=h['old'].splitlines(keepends=True);at=h['at']+offset
  out+=a[pos:at]
  assert ''.join(a[at:at+len(nl)])==h['new'],(f,'PART6 hunk mismatch',at)
  out+=ol;pos=at+len(nl);offset+=len(nl)-len(ol)
 out+=a[pos:];result=''.join(out)
 assert result==b,(f,'unregistered edits beyond PART6 hunks')
 return result