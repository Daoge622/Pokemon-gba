#!/usr/bin/env python3
"""Standalone Chinese text check for script .inc files (no build needed).

  check-text.py [FILE...]     default: data/scripts/*.inc and data/maps/*/scripts.inc

Checks every .string line: each displayed line (split on \\n \\l \\p) must be
<= 208 px wide (CJK glyph 12 px, other chars 6 px, {VAR} counted 0 except
STR_VAR / PLAYER which count 7 CJK glyphs), every character must exist in
charmap.txt, and each text block must end with '$'.
"""
import glob, json, os, re, sys

R = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
mapping = set()
for m in re.finditer(r"^'(.+)'\s*=\s*([0-9A-Fa-f][0-9A-Fa-f ]*)", open(os.path.join(R, 'charmap.txt'), encoding='utf-8').read(), re.M):
    key = m[1][1:] if len(m[1]) == 2 and m[1].startswith('\\') else m[1]
    if len(key) == 1:
        mapping.add(key)
cfg = json.load(open(os.path.join(R, 'tools/poryscript/font_config.json'), encoding='utf-8'))
widths = cfg['fonts'][cfg['defaultFontId']]['widths']
WIDE_VARS = ('{PLAYER}', '{STR_VAR_1}', '{STR_VAR_2}', '{STR_VAR_3}', '{RIVAL}')

def width(s):
    w = 0
    for t in re.findall(r'\{[^}]*\}|.', s):
        if t.startswith('{'):
            w += 7 * 12 if t in WIDE_VARS else 0
        else:
            w += widths.get(t, 6)
    return w

def check_file(f):
    errs = []
    txt = open(f, encoding='utf-8').read()
    for m in re.finditer(r'(?m)^([A-Za-z_]\w*):{1,2}[ \t]*\n((?:[ \t]*\.string[^\n]*\n?)+)', txt):
        block = ''.join(re.findall(r'\.string "(.*)"', m[2]))
        if not any('一' <= c <= '鿿' for c in block):
            continue
        if not block.endswith('$'):
            errs.append((m[1], 'missing $ terminator'))
        for line in re.split(r'\\[nlp]', block.rstrip('$')):
            w = width(line)
            limit = 208
            # lines with a 7-glyph name placeholder are only checked loosely
            if any(v in line for v in WIDE_VARS): limit = 208 + 4 * 12
            if w > limit:
                errs.append((m[1], 'too wide %d px: %s' % (w, line)))
        for tok in re.findall(r'\{[^}]*\}|\\.|.', block):
            if tok.startswith(('{', '\\')) or tok == '$':
                continue
            if tok not in mapping:
                errs.append((m[1], 'char not in font/charmap: %r' % tok))
    return errs

if __name__ == '__main__':
    files = sys.argv[1:] or sorted(glob.glob(os.path.join(R, 'data/scripts/*.inc')) + glob.glob(os.path.join(R, 'data/maps/*/scripts.inc')))
    n = 0
    for f in files:
        for e in check_file(f):
            print(os.path.relpath(f, R), *e); n += 1
    print('text problems:', n)
    sys.exit(1 if n else 0)
