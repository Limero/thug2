#!/usr/bin/env python3
"""harvest_lblloads.py - rewrite literal global derefs to extern-lbl form.

Recipe (fn_8011D81C, M7.29): a draft reads a global via a literal address
`*(s32 *)0x80302CA4` which ngccc folds to `lis rX,hi; ori rX,lo; lwz rX,0(rX)`.
WANT shows `lis rX,-0x7fd0; lwz rX,0x2ca4(rX)` — the @ha/@l reloc form emitted
when the global is referenced through `extern char lbl_XXXX[]`.

For every draft containing `*(\w+ *)0x80[34]......` derefs where a `lbl_`
symbol exists at that exact address in symbols.txt, rewrite the literal to
`*(s32 *)&lbl_XXXX` (inserting the extern decl), compile, and keep the edit
only if the masked pct improves.

Usage: tools/venv/bin/python tools/harvest_lblloads.py
"""

import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402

SIZES = {}
LBLS = set()
for line in open('config/G2TE52/symbols.txt'):
    m = re.match(r'^\S+ = \.text:0x([0-9A-Fa-f]{8}); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        SIZES[int(m.group(1), 16)] = int(m.group(2), 16)
    m2 = re.match(r'^lbl_([0-9A-F]{8})', line)
    if m2:
        LBLS.add(int(m2.group(1), 16))

LITERAL = re.compile(r'[*][(]([a-zA-Z0-9_]+) [*][)]0x(80[0-9A-Fa-f]{6})')


def masked_pct(orig, got, masks):
    n = min(len(orig), len(got)) // 4
    if n == 0:
        return 0.0
    hit = sum(1 for i in range(n)
              if (int.from_bytes(orig[i*4:(i+1)*4], 'big') & masks.get(i*4, 0xFFFFFFFF)) ==
                 (int.from_bytes(got[i*4:(i+1)*4], 'big') & masks.get(i*4, 0xFFFFFFFF)))
    return 100.0 * hit / n


def compile_pct(addr, body):
    try:
        got, masks = gl.compile_fn(addr, body)
    except Exception:
        return None
    if got is None:
        return None
    orig = bytes(gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + SIZES.get(addr, len(got))])
    return masked_pct(orig, got, masks)


def transform(body, addr):
    """Replace literal global derefs with extern-lbl form. Returns (newbody, changed)."""
    changed = False
    needs = []

    def repl(m):
        nonlocal changed
        typ = m.group(1)
        lit = int(m.group(2), 16)
        if lit not in LBLS:
            return m.group(0)
        changed = True
        needs.append('lbl_%08X' % lit)
        return '*(%s *)&lbl_%08X' % (typ, lit)

    nb = LITERAL.sub(repl, body)
    if not changed:
        return body, False
    # insert extern decls after the types.h include
    decls = '\n'.join('extern char %s[];' % n for n in sorted(set(needs)))
    if 'types.h"' in nb:
        nb = nb.replace('types.h"\n', 'types.h"\n' + decls + '\n', 1)
    else:
        nb = decls + '\n' + nb
    return nb, True


def main():
    gains = 0
    tested = 0
    for fp in sorted(glob.glob('src/wip/fn_*.c')):
        txt = open(fp).read()
        body = '\n'.join(l for l in txt.splitlines()
                         if not l.startswith('//') and 'types.h' not in l)
        if not LITERAL.search(body):
            continue
        addr = int(re.search(r'fn_([0-9A-F]{8})', os.path.basename(fp)).group(1), 16)
        before = compile_pct(addr, body)
        if before is None:
            continue
        if before >= 100.0:
            continue
        nb, changed = transform(body, addr)
        if not changed:
            continue
        tested += 1
        after = compile_pct(addr, nb)
        if after is None:
            continue
        if after > before:
            gains += 1
            hdr = txt.split('types.h"')[0] + 'types.h"\n'
            open(fp, 'w').write(hdr + nb + '\n')
            print('GAIN %08X %.1f -> %.1f' % (addr, before, after))
        elif after < before:
            print('REGRESS %08X %.1f -> %.1f' % (addr, before, after))
        else:
            print('same   %08X %.1f -> %.1f' % (addr, before, after))
    print('=== tested %d, gains %d ===' % (tested, gains))


if __name__ == '__main__':
    main()
