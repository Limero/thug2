#!/usr/bin/env python3
"""Prefilter for the `forwarded_test_scan.py` lever.

m2c drops an argument that retail forwards from an `if` guard, and the tell is
that the guarded load becomes *compare-only*, so ngccc homes it in r0:

    want  lwz  r3, 0x190(r31)   /  cmpwi r3, 0
    got   lwz  r0, 0x190(r31)   /  cmpwi r0, 0

This scans a draft's own compiled object code for an adjacent
`lwz r0, d(rB)` + `cmpwi r0, 0` pair (and the `lhz`/`lbz`/`lha` variants) and
prints the address when it finds one, so the (expensive) argument-insertion
sweep only runs over drafts that can actually be helped.

Usage: printf 'ADDR\\n...' | tools/venv/bin/python tools/cmp0_home_scan.py
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs  # noqa: E402

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.skipdata = True
LOADS = {"lwz", "lhz", "lbz", "lha"}


def main():
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 16)
        fp = "src/wip/fn_%08X.c" % addr
        if not os.path.exists(fp):
            continue
        text = open(fp).read()
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        if not body:
            continue
        try:
            got, _ = gl.compile_fn(addr, body, extra_flags=gl.draft_flags(text) or None)
        except Exception:
            continue
        if got is None:
            continue
        ins = list(md.disasm(got, addr))
        hits = 0
        for i in range(len(ins) - 1):
            x, y = ins[i], ins[i + 1]
            if x.mnemonic in LOADS and x.op_str.startswith("r0, "):
                if y.mnemonic == "cmpwi" and y.op_str.replace(" ", "") == "r0,0":
                    hits += 1
        if hits:
            print("%08X %d" % (addr, hits))


if __name__ == "__main__":
    main()
