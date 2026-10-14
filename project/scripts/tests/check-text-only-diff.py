#!/usr/bin/env python3
"""Verify that only .string text changed in the given script files vs a git ref.

  check-text-only-diff.py REF FILE...

Fails if any non-.string line (labels, commands, comments) differs, or if a
text label lost all of its .string lines.
"""
import os, re, subprocess, sys

R = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))

def skeleton(txt):
    out = []
    for line in txt.split('\n'):
        if re.match(r'\s*\.string\s', line):
            if out and out[-1] == '<TEXT>':
                continue
            out.append('<TEXT>')
        else:
            out.append(line)
    return out

ref = sys.argv[1]
bad = 0
for f in sys.argv[2:]:
    rel = os.path.relpath(os.path.abspath(f), os.path.join(R, '..'))
    old = subprocess.check_output(['git', 'show', '%s:%s' % (ref, rel)], cwd=R).decode('utf-8')
    new = open(f, encoding='utf-8').read()
    a, b = skeleton(old), skeleton(new)
    if a != b:
        import difflib
        bad += 1
        print('NON-TEXT CHANGE in', f)
        for l in list(difflib.unified_diff(a, b, lineterm='', n=1))[:40]:
            print('  ', l)
print('files with non-text changes:', bad)
sys.exit(1 if bad else 0)
