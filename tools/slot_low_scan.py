#!/usr/bin/env python3
"""Prefilter for `lead_arg_scan.py`: the argument block is one slot low.

m2c never invents a pass-through argument, so when retail forwards a value the
draft dropped, every argument-setup word of that call is emitted one register
too low:

    want  mr  r31, r3 / li  r4, 1      / bl callee
    got   mr  r31, r3 / li  r3, 1      / bl callee

This compiles each draft, disassembles WANT and GOT position by position and
counts words where WANT writes an argument register rN (N in 4..10) and GOT
writes the *same kind* of instruction to r(N-1).  Two or more such words in
one function is a reliable signal, which keeps the (expensive) per-call
argument-insertion sweep affordable.

Usage: printf 'ADDR\\n...' | tools/venv/bin/python tools/slot_low_scan.py
Prints `ADDR <hits> [sample]`.
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs  # noqa: E402

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.skipdata = True
SETUP = {"li", "mr", "lis", "ori", "addi", "lwz", "lfs", "extsb"}
MODES = {"stwu", "mflr", "mtlr", "stmw", "lmw", "stw", "lwz", "addi", "blr"}


def argreg(op):
    m = re.match(r"r(\d+)\b", op)
    return int(m.group(1)) if m else None


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
        base = gl.t_off + (addr - gl.t_addr)
        size = min(len(got), 4096)
        want = gl.d[base:base + size]
        w = list(md.disasm(want, addr))
        g = list(md.disasm(got[:size], addr))
        if len(w) != len(g):
            continue
        hits, sample = 0, []
        for x, y in zip(w, g):
            if x.mnemonic != y.mnemonic or x.mnemonic not in SETUP:
                continue
            dx, dy = argreg(x.op_str), argreg(y.op_str)
            if dx is None or dy is None:
                continue
            if dx == dy + 1 and 4 <= dx <= 10:
                hits += 1
                if len(sample) < 3:
                    sample.append("%s:%s>%s" % (x.mnemonic, x.op_str, y.op_str))
        if hits:
            print("%08X %d %s" % (addr, hits, " ".join(sample)))


if __name__ == "__main__":
    main()
