"""Exact PART5 delta removal for historical fixed-snapshot tests (PART1-4).

docs/project/part5-deltas.json lists every PART5 change against the tag
pre-part5-implementation. A legacy test sees a file only after the recorded
PART5 hunks are reversed; the result must equal the pre-PART5 file exactly,
so any unrecorded edit to PART1-4 content still fails the old checks.
PART5 content itself is verified by check-part5.py.
"""
from pathlib import Path
import json, subprocess
from part55_compat import source as part55_source

R = Path(__file__).resolve().parents[2]
PRE = 'pre-part5-implementation'
D = json.loads((R / 'docs/project/part5-deltas.json').read_text(encoding='utf-8'))


def pre(f):
    return subprocess.check_output(['git', 'show', PRE + ':' + f], cwd=R, text=True)


def revert_text(f, s):
    hunks = D['text'][f]
    a = s.splitlines(keepends=True)
    # walk forward: hunk 'at' is the line index in the old file; offset tracks new-old growth
    out, pos, offset = [], 0, 0
    for h in hunks:
        new_lines = h['new'].splitlines(keepends=True)
        old_lines = h['old'].splitlines(keepends=True)
        start = h['at'] + offset
        out += a[pos:start]
        assert ''.join(a[start:start + len(new_lines)]) == h['new'], (f, 'PART5 hunk mismatch at line', start)
        out += old_lines
        pos = start + len(new_lines)
        offset += len(new_lines) - len(old_lines)
    out += a[pos:]
    r = ''.join(out)
    assert r == pre(f), (f, 'content differs from pre-PART5 beyond recorded PART5 hunks')
    return r


def revert_map(f, s):
    v = json.loads(s)
    d = D['maps'][f]
    for key, delta in d.items():
        lst = v.get(key) or []
        added = delta['added']
        if added:
            assert lst[len(lst) - len(added):] == added, (f, key, 'PART5 additions changed')
            lst = lst[:len(lst) - len(added)]
        for i, before, after in delta['modified']:
            assert lst[i] == after, (f, key, i, 'PART5 modification changed')
            lst[i] = before
        v[key] = lst
    b = json.loads(pre(f))
    assert v == b, (f, 'map differs from pre-PART5 beyond recorded PART5 events')
    return pre(f)


def source(f, s=None):
    if s is None:
        s = (R / f).read_text(encoding='utf-8')
    s = part55_source(f, s)  # strict PART5.5 reversal before PART5
    if f in D['maps']:
        return revert_map(f, s)
    if f in D['text']:
        return revert_text(f, s)
    return s
