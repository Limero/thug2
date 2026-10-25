#!/usr/bin/env python3
"""Padded want-vs-got word diff for a wip draft.

Usage: tools/venv/bin/python tools/want_vs_got.py 0x800A07F0 [-mps-float ...]
Compiles the current draft body, pads to the longer of want/got, and prints
aligned word pairs with PS-aware decoding. Marks mismatched words with !!.
"""
import json
import struct
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
import ps_diff
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)


def dec_any(w, addr):
    d = ps_diff.dec(w)
    if d:
        return d
    for ins in md.disasm(struct.pack(">I", w), addr):
        return f"{ins.mnemonic} {ins.op_str}"
    return ".word"


def main():
    args = sys.argv[1:]
    addr = int(args[0], 0)
    cli_extra = args[1:]
    rep = json.load(open("build/G2TE52/report.json"))
    sizes = {int(fn["metadata"]["virtual_address"]): int(fn["size"])
             for u in rep.get("units", []) for fn in u.get("functions", [])}
    want = sizes.get(addr, 0)
    orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + want]
    text = open(f"src/wip/fn_{addr:08X}.c").read()
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    # Use the draft's own FLAG line (shared rule, incl. __ps_t -> -mps-float)
    # unless the caller passed flags explicitly; without this a flagged draft is
    # diffed against a different program and every "!!" line is a lie.
    extra = cli_extra or (gl.draft_flags(text) or None)
    got, err = gl.compile_fn(addr, body, extra_flags=extra)
    if got is None:
        print("FAIL:", err)
        return
    print(f"=== {addr:08X} want {want}B got {len(got)}B ===")
    n = max(want, len(got))
    for i in range(0, n, 4):
        o = struct.unpack_from(">I", orig, i)[0] if i + 4 <= len(orig) else 0
        g = struct.unpack_from(">I", got, i)[0] if i + 4 <= len(got) else 0
        mark = "  " if o == g else "!!"
        print(f"+{i:02x} {mark} want {o:08x} {dec_any(o, addr+i)}")
        if o != g:
            print(f"        got  {g:08x} {dec_any(g, addr+i)}")


if __name__ == "__main__":
    main()
