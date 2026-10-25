#!/usr/bin/env python3
"""Dump WIP draft + original asm for a function address, then compile the draft
and show a side-by-side instruction diff vs the original.

Usage: python3 tools/dump_analysis.py <addr-hex> [size]
"""
import re
import struct
import sys

sys.path.insert(0, 'tools')
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)


def main():
    addr = int(sys.argv[1], 16)
    size = int(sys.argv[2], 16) if len(sys.argv) > 2 else None

    fp = 'src/wip/fn_%08X.c' % addr
    try:
        text = open(fp).read()
    except IOError:
        print('no draft at %s' % fp)
        return
    if size is None:
        m = re.search(r'size=(\d+)B', text)
        size = int(m.group(1)) if m else 64

    # --- original asm ---
    want = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + size]
    wo = list(md.disasm(want, addr))
    print('=== ORIGINAL ASM (0x%X, %d bytes) ===' % (addr, len(want)))
    for i in wo:
        print('  %08X: %-8s %s' % (i.address, i.mnemonic, i.op_str))

    # --- draft C body ---
    body = '\n'.join(l for l in text.splitlines() if not l.startswith('//') and 'types.h' not in l)
    print()
    print('=== DRAFT C ===')
    print(body)
    print()

    # --- compile & diff ---
    got, masks = gl.compile_fn(addr, body)
    if got is None:
        print('COMPILE FAIL: %s' % (masks or '')[-300:])
        return
    print('=== SIDE-BY-SIDE (want | got), %d vs %d bytes ===' % (len(want), len(got)))
    mo = list(md.disasm(got, addr))
    n = 0
    for k in range(max(len(wo), len(mo))):
        w = wo[k] if k < len(wo) else None
        g = mo[k] if k < len(mo) else None
        ws = ('%s %s' % (w.mnemonic, w.op_str)) if w else ''
        gs = ('%s %s' % (g.mnemonic, g.op_str)) if g else ''
        same = bool(w and g and w.mnemonic == g.mnemonic and w.op_str == g.op_str)
        if not same:
            n += 1
        mark = '  ' if same else 'D>'
        print('  %04X %s %-26s | %s' % (k * 4, mark, ws, gs))
    print()
    if len(got) != len(want):
        print('SIZE MISMATCH %d/%d' % (len(got), len(want)))
    else:
        print('MISMATCHED INSTRUCTIONS: %d' % n)


if __name__ == '__main__':
    main()
