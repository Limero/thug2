#!/usr/bin/env python3
"""Hoist a nested call that is the LAST argument into a temp, forcing the
nested call to evaluate BEFORE the outer call's other args.

    fn_80127684(*(s32 *)((char *)arg1 + 0x18), 0xAA0B4287, fn_8005581C());
->
    s32 temp_r5;
    ...
    temp_r5 = fn_8005581C();
    fn_80127684(*(s32 *)((char *)arg1 + 0x18), 0xAA0B4287, temp_r5);

Kept only if the match count improves. (ngccc is C89: the temp must be
declared at the top of the function block.)

Usage (slices):
    python3 tools/fix_nested_call_hoist.py 0 8
"""
import re, sys, glob, os
sys.path.insert(0, 'tools')
import gen_leaves as gl

sizes = {}
for line in open('config/G2TE52/symbols.txt'):
    m = re.match(r'^\S+ = \.text:0x([0-9A-Fa-f]{8}); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        sizes[int(m.group(1), 16)] = int(m.group(2), 16)

stmt = re.compile(
    r'(\bfn_[0-9A-F]{8}\()([^;\n]*?,\s*)(fn_[0-9A-F]{8}\([^;\n]*\))\)\s*;')


def match_count(ADDR, body):
    sz = sizes.get(ADDR, 0)
    if not sz:
        return None
    got, masks = gl.compile_fn(ADDR, body)
    if got is None:
        return None
    WANT = bytes(gl.d[gl.t_off + (ADDR - gl.t_addr):gl.t_off + (ADDR - gl.t_addr) + sz])
    n = min(sz // 4, len(got) // 4)
    hit = 0
    for i in range(n):
        m = (masks or {}).get(i * 4, 0xFFFFFFFF)
        w = int.from_bytes(WANT[i * 4:(i + 1) * 4], 'big')
        g = int.from_bytes(got[i * 4:(i + 1) * 4], 'big')
        if (w & m) == (g & m):
            hit += 1
    return (hit, n)


def hoist(text, m):
    outer = m.group(1)       # fn_A(
    prefix = m.group(2)      # ..., (trailing ", ")
    nested = m.group(3)      # fn_B(...)
    repl = 'temp_r5 = %s;\n    %s%s temp_r5);' % (nested, outer, prefix)
    return text[:m.start()] + repl + text[m.end():]


def main():
    slice_idx = int(sys.argv[1])
    num_slices = int(sys.argv[2])
    files = sorted(glob.glob('src/wip/fn_*.c'))
    mine = files[slice_idx::num_slices]
    improved = 0
    for fp in mine:
        ADDR = int(os.path.basename(fp)[3:11], 16)
        text = open(fp).read()
        m = stmt.search(text)
        if not m:
            continue
        body = '\n'.join(l for l in text.splitlines() if not l.startswith('//'))
        before = match_count(ADDR, body)
        if before is None:
            continue
        newtext = hoist(text, m)
        # add declaration after the function's opening brace (first `{`)
        brace = newtext.find('{')
        if brace < 0:
            continue
        nl = newtext.find('\n', brace)
        if nl < 0:
            continue
        newtext = newtext[:nl + 1] + '    s32 temp_r5;\n' + newtext[nl + 1:]
        newbody = '\n'.join(l for l in newtext.splitlines() if not l.startswith('//'))
        after = match_count(ADDR, newbody)
        if after is None:
            continue
        bhit, bn = before
        ahit, an = after
        if ahit > bhit:
            open(fp, 'w').write(newtext)
            improved += 1
            print('%s: %d/%d -> %d/%d' % (os.path.basename(fp), bhit, bn, ahit, an))
    print('slice done: improved=%d' % improved)


if __name__ == '__main__':
    main()
