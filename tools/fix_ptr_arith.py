#!/usr/bin/env python3
"""Fix pointer-arithmetic offset scaling: (s32 *)base + 0xOFF -> (char *)base + 0xOFF.

m2c sometimes emits `*(s32 *)((s32 *)base + 0x5C)` to mean "s32 field at byte
offset 0x5C", but the s32* cast scales the offset by 4 (-> 0x170). WANT reads
the unscaled byte offset, so the fix is to cast the base to (char *) so the
offset stays a byte offset. The change is kept only if the match count
improves, so genuine s32-array indexing (where scaling is correct) is never
broken.

Usage (slices):
    python3 tools/fix_ptr_arith.py 0 8
"""
import re, sys, glob, os
sys.path.insert(0, 'tools')
import gen_leaves as gl

sizes = {}
for line in open('config/G2TE52/symbols.txt'):
    m = re.match(r'^\S+ = \.text:0x([0-9A-Fa-f]{8}); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        sizes[int(m.group(1), 16)] = int(m.group(2), 16)

pat = re.compile(r'\(s32 \*\)\(((?:[^()]|\([^()]*\))*)\) \+ (0x[0-9A-Fa-f]+)')


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


def main():
    slice_idx = int(sys.argv[1])
    num_slices = int(sys.argv[2])
    files = sorted(glob.glob('src/wip/fn_*.c'))
    mine = files[slice_idx::num_slices]
    improved = 0
    for fp in mine:
        ADDR = int(os.path.basename(fp)[3:11], 16)
        text = open(fp).read()
        if not pat.search(text):
            continue
        body = '\n'.join(l for l in text.splitlines() if not l.startswith('//'))
        before = match_count(ADDR, body)
        if before is None:
            continue
        # fix one occurrence at a time, keep if the whole file improves
        newtext = pat.sub(lambda m: '(char *)(%s) + %s' % (m.group(1), m.group(2)), text)
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
