#!/usr/bin/env python3
"""Find wip drafts whose ONLY diffs are the call frame (doc 57's frame lever).

Locals live at positive offsets from r1, so a wrong local size changes only
`stwu r1,-N(r1)`, the saved-register slot (`stmw`/`lmw`), the LR slot
(`stw/lwz r0, ...`) and `addi r1, r1, N` — the whole body can still match word
for word. Such a draft is usually one buffer-size edit away, so they are worth
listing separately from the general residual census.

Prints `0xADDR frames=<want_N>/<got_N> body=<n> frame_diffs=<n> total=<t>`.

Usage: printf 'ADDR\n' | tools/venv/bin/python tools/frame_only_scan.py
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
FRAME_OPS = {"stwu", "stmw", "lmw", "addi", "lwz", "stw", "mtlr", "mflr", "blr"}


def frame_of(insn):
    m = re.search(r"(-?0x[0-9a-f]+)\(r1\)", insn.op_str)
    return m.group(1) if m and insn.mnemonic == "stwu" else None


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
        diffs = []
        for i in range(min(n, len(w), len(g))):
            if orig[i * 4:i * 4 + 4] == got[i * 4:i * 4 + 4]:
                continue
            if masks.get(i * 4, 0xFFFFFFFF) != 0xFFFFFFFF:
                continue
            diffs.append(i)
        if not diffs:
            continue
        # "frame-only" = every diff is inside the first 4 words or the last 8
        frame_only = all(i < 4 or i >= len(orig) // 4 - 8 for i in diffs)
        # a real frame change also moves the saved-reg/lr slots, so the sizes
        # must be equal and both must open with stwu — otherwise we are looking
        # at a truncated/mismatched compile, not a frame difference.
        if frame_only and len(got) == len(orig) and frame_of(w[0]) and frame_of(g[0]):
            print(f"0x{addr:08X} frames={frame_of(w[0])}/{frame_of(g[0])} "
                  f"body={len(diffs)} frame_diffs={len(diffs)} total={len(orig)//4}")


if __name__ == "__main__":
    main()
