#!/usr/bin/env python3
"""Scan wip drafts (addrs on stdin) for the wrong-argument-order signature.

m2c sometimes transcribes a call's argument *order* wrong (or drops/inserts an
argument), which shows up as the whole argument-register set being shifted by
one slot: want `lwz r6,0x18(r3)` where ngccc has `lwz r5,0x18(r3)`, want
`mr r7,r5` where ngccc has `mr r6,r4`, `li r5,-1` vs `li r4,-1`, ...

Prints `0xADDR shift=<n> real=<m> total=<t>` where `shift` counts mismatching
word pairs whose mnemonic and operand shape are identical except that every GPR
number moved by the same ±1.

Usage: printf 'ADDR\n' | tools/venv/bin/python tools/argshift_scan.py
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
REG = re.compile(r"\br(\d+)\b")


def regs(s):
    return [int(x) for x in REG.findall(s)]


def shifted(a, b):
    """True when b's operand registers are all a's shifted by the same +-1."""
    if a.mnemonic != b.mnemonic:
        return False
    ra, rb = regs(a.op_str), regs(b.op_str)
    if not ra or len(ra) != len(rb):
        return False
    d = {y - x for x, y in zip(ra, rb)}
    return len(d) == 1 and next(iter(d)) in (-1, 1)


def main():
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 16)
        text = open(f"src/wip/fn_{addr:08X}.c").read()
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        flags = gl.draft_flags(text) or None
        got, masks = gl.compile_fn(addr, body, extra_flags=flags)
        if got is None:
            print(f"0x{addr:08X} shift=FAIL real=0 total=0")
            continue
        import json
        wsize = None
        rep = json.load(open("build/G2TE52/report.json"))
        for u in rep.get("units", []):
            for fn in u.get("functions", []):
                if int(fn["metadata"]["virtual_address"]) == addr:
                    wsize = int(fn["size"])
        size = wsize or len(got)
        orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + size]
        n = min(len(orig), len(got)) // 4
        w = list(md.disasm(orig, addr))
        g = list(md.disasm(got, addr))
        shift = real = 0
        for i in range(min(n, len(w), len(g))):
            if orig[i * 4:i * 4 + 4] == got[i * 4:i * 4 + 4]:
                continue
            if masks.get(i * 4, 0xFFFFFFFF) != 0xFFFFFFFF:
                continue
            real += 1
            if shifted(w[i], g[i]):
                shift += 1
        print(f"0x{addr:08X} shift={shift} real={real} total={len(orig)//4}")


if __name__ == "__main__":
    main()
