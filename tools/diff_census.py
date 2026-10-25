#!/usr/bin/env python3
"""Census wip drafts (addrs on stdin): non-branch diff count + width-diff count.

Prints `0xADDR real=<n> width=<n> total=<n>` so a sweep can rank drafts by how
small and how mechanical their residual is.

Usage: printf 'ADDR\n...' | tools/venv/bin/python tools/diff_census.py
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)

WIDTH = {
    ("lha", "lwz"), ("lhz", "lwz"), ("lbz", "lwz"), ("lfs", "lwz"),
    ("sth", "stw"), ("stb", "stw"), ("lwz", "lha"), ("lwz", "lhz"),
    ("lwz", "lbz"), ("stw", "sth"), ("stw", "stb"),
}


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
            print(f"0x{addr:08X} real=FAIL width=0 total=0")
            continue
        wsize = None
        rep = gl.report() if hasattr(gl, "report") else None
        try:
            import json
            rep = json.load(open("build/G2TE52/report.json"))
            for u in rep.get("units", []):
                for fn in u.get("functions", []):
                    if int(fn["metadata"]["virtual_address"]) == addr:
                        wsize = int(fn["size"])
        except Exception:
            pass
        size = wsize or len(got)
        orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + size]
        n = min(len(orig), len(got)) // 4
        w = list(md.disasm(orig, addr))
        g = list(md.disasm(got, addr))
        real = 0
        width = 0
        for i in range(min(n, len(w), len(g))):
            ow = orig[i * 4:i * 4 + 4]
            gw = got[i * 4:i * 4 + 4]
            if ow == gw:
                continue
            if masks.get(i * 4, 0xFFFFFFFF) != 0xFFFFFFFF:
                continue
            real += 1
            if (w[i].mnemonic, g[i].mnemonic) in WIDTH:
                width += 1
        print(f"0x{addr:08X} real={real} width={width} total={len(orig)//4}")


if __name__ == "__main__":
    main()
