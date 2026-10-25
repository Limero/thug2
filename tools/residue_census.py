#!/usr/bin/env python3
"""Census the *kind* of every non-branch residual word across wip drafts.

`diff_census.py` says how many words are wrong; this says *what* is wrong.
For each draft it prints one line per mismatching unmasked word as

    WANTMNEM>GOTMNEM

so a sweep can pipe the whole pool through awk/sort/uniq and see which
instruction class dominates the remaining work.

Usage: printf 'ADDR\\n...' | tools/venv/bin/python tools/residue_census.py
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs  # noqa: E402

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.skipdata = True

_SIZES = None


def sizes():
    global _SIZES
    if _SIZES is None:
        _SIZES = {}
        try:
            rep = json.load(open("build/G2TE52/report.json"))
            for u in rep.get("units", []):
                for fn in u.get("functions", []):
                    _SIZES[int(fn["metadata"]["virtual_address"])] = int(fn["size"])
        except Exception:
            pass
    return _SIZES


def main():
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 0)
        fp = f"src/wip/fn_{addr:08X}.c"
        if not os.path.exists(fp):
            continue
        text = open(fp).read()
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        if not body:
            continue
        try:
            got, masks = gl.compile_fn(addr, body, extra_flags=gl.draft_flags(text) or None)
        except Exception:
            continue
        if got is None:
            continue
        size = sizes().get(addr) or len(got)
        base = gl.t_off + (addr - gl.t_addr)
        orig = gl.d[base:base + size]
        n = min(len(orig), len(got)) // 4
        w = list(md.disasm(orig, addr))
        g = list(md.disasm(got, addr))
        if len(orig) != len(got):
            print(f"0x{addr:08X} SIZE {len(orig)}>{len(got)}")
        out = []
        for i in range(min(n, len(w), len(g))):
            ow = orig[i * 4:i * 4 + 4]
            gw = got[i * 4:i * 4 + 4]
            if ow == gw:
                continue
            if masks.get(i * 4, 0xFFFFFFFF) != 0xFFFFFFFF:
                continue
            out.append(f"{w[i].mnemonic}>{g[i].mnemonic}")
        if out:
            print(f"0x{addr:08X} " + " ".join(out))


if __name__ == "__main__":
    main()
