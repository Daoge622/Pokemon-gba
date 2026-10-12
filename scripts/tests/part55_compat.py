"""Strict removal of reviewed PART5.5 deltas before historical tests.
Actual current PART5.5 is tested separately. No unrecorded source edits accepted.
"""
from pathlib import Path
import json,subprocess,hashlib
from part6_compat import source as part6_source
R=Path(__file__).resolve().parents[2]
D=json.loads((R/'docs/project/part55-deltas.json').read_text())
PRE=D['baseline']
def pre(f):return subprocess.check_output(['git','show',PRE+':'+f],cwd=R,text=True)
def source(f,s=None):
 if s is None:s=(R/f).read_text(encoding='utf-8')
 s=part6_source(f,s)  # strict PART6 reversal first (see part6_compat.py)
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
  assert ''.join(a[at:at+len(nl)])==h['new'],(f,'PART5.5 hunk mismatch',at)
  out+=ol;pos=at+len(nl);offset+=len(nl)-len(ol)
 out+=a[pos:];result=''.join(out)
 assert result==b,(f,'unregistered edits beyond PART5.5 hunks')
 return result