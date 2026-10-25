#!/usr/bin/env python3
"""Item-26-adjacent: signatures that skip arg1 but read r5 (arg2).

m2c emits `fn_XXXX(arg0, arg2)` when the function reads r3 (arg0) and r5
(arg2) but not r4 (arg1). In C that 2-param declaration puts "arg2" in r4,
so the body reads the wrong register. Inserting an unused `s32 arg1,` shifts
arg2 back to r5. Keep only if the word-match count improves.

Usage:
    python3 tools/fix_unused_arg1.py
"""
import re, sys, glob, os
sys.path.insert(0, 'tools')
import gen_leaves as gl

sizes = {}
for line in open('config/G2TE52/symbols.txt'):
    m = re.match(r'^\S+ = \.text:0x([0-9A-Fa-f]{8}); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        sizes[int(m.group(1), 16)] = int(m.group(2), 16)

sig = re.compile(r'\bfn_([0-9A-F]{8})\s*\(([^()]*)\)\s*\{')


def mc(A, body):
    got, masks = gl.compile_fn(A, body)
    if got is None or A not in sizes:
        return None
    sz = sizes[A]
    WANT = bytes(gl.d[gl.t_off + (A - gl.t_addr):gl.t_off + (A - gl.t_addr) + sz])
    n = min(sz // 4, len(got) // 4)
    hit = 0
    for i in range(n):
        m = (masks or {}).get(i * 4, 0xFFFFFFFF)
        w = int.from_bytes(WANT[i * 4:(i + 1) * 4], 'big')
        g = int.from_bytes(got[i * 4:(i + 1) * 4], 'big')
        if (w & m) == (g & m):
            hit += 1
    return (hit, n)


improved = 0
exact = 0
for fp in sorted(glob.glob('src/wip/fn_*.c')):
    text = open(fp).read()
    if 'family=stub' in text or 'family=tp' in text:
        continue
    m = sig.search(text)
    if not m:
        continue
    params = m.group(2)
    if 'arg2' not in params or 'arg1' in params:
        continue
    if 'arg0' not in params:
        continue
    A = int(m.group(1), 16)
    body = '\n'.join(l for l in text.splitlines() if not l.startswith('//') and 'types.h' not in l)
    before = mc(A, body)
    if before is None:
        continue
    newparams = re.sub(r',\s*(?=[^,]*\barg2\b)', ', s32 arg1, ', params, count=1)
    newtext = text.replace(m.group(2), newparams)
    newbody = '\n'.join(l for l in newtext.splitlines() if not l.startswith('//') and 'types.h' not in l)
    after = mc(A, newbody)
    if after is not None and after[0] > before[0]:
        open(fp, 'w').write(newtext)
        improved += 1
        if after[0] == after[1]:
            exact += 1
        print('%s: %d/%d -> %d/%d%s' % (os.path.basename(fp), before[0], before[1], after[0], after[1], ' EXACT' if after[0] == after[1] else ''))
print('improved=%d exact=%d' % (improved, exact))
