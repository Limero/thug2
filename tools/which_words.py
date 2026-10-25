#!/usr/bin/env python3
"""Show only the instruction words where a draft disagrees with the DOL,
after applying the same relocation masks test_wip_drafts uses.

Usage: tools/venv/bin/python tools/which_words.py 0xADDR [body.c]
"""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from test_wip_drafts import test_one, _want_sizes


def main():
    addr = int(sys.argv[1], 0)
    if len(sys.argv) > 2:
        text = open(sys.argv[2]).read()
    else:
        text = open(os.path.join(gl.ROOT, "src/wip/fn_%08X.c" % addr)).read()
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    # Shared rule (gl.draft_flags): flagged drafts AND paired-single drafts must
    # be built exactly as the harness builds them.  The old naive parser both
    # accepted bogus tokens and ignored the __ps_t -> -mps-float rule, so every
    # PS draft was diffed as SCALAR code and the "diffs" were fiction.
    flags = gl.draft_flags(text)
    got, masks = gl.compile_fn(addr, body, extra_flags=flags or None)
    if got is None:
        print("FAIL")
        return
    want = _want_sizes().get(addr, len(got))
    if want < len(got):
        want = len(got)
    base = gl.t_off + (addr - gl.t_addr)
    orig = gl.d[base:base + want]
    n = len(orig) // 4
    bad = []
    for i in range(n):
        ow = int.from_bytes(orig[i * 4:(i + 1) * 4], "big")
        gw = int.from_bytes(got[i * 4:(i + 1) * 4], "big") if (i + 1) * 4 <= len(got) else 0
        if (ow & masks.get(i * 4, 0xFFFFFFFF)) != (gw & masks.get(i * 4, 0xFFFFFFFF)):
            bad.append((i, addr + i * 4, ow, gw, masks.get(i * 4, 0xFFFFFFFF)))
    print("%d/%d words differ" % (len(bad), n))
    for i, a, ow, gw, mk in bad:
        print("  +%3d  0x%08X  want %08X  got %08X  mask %08X" % (i * 4, a, ow, gw, mk))


if __name__ == "__main__":
    main()
