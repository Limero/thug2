#!/usr/bin/env python3
"""Print only the NON-branch mismatching words of a wip draft vs the DOL.

Branch/reloc diffs are masked by the scorer, so this is the set of words that
actually decides the percentage.

Usage: tools/venv/bin/python tools/real_diffs.py 0xADDR [--all]
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
BRANCH = {"b", "bl", "ba", "bla", "bc", "bcl", "bclr", "bcctr", "beq", "bne",
          "blt", "bgt", "ble", "bge", "bdnz", "bdz", "bgelr", "bnelr", "beqlr"}


def main():
    addr = int(sys.argv[1], 0)
    show_all = "--all" in sys.argv
    cands = [a for a in sys.argv[2:] if not a.startswith("--")]
    f = cands[0] if cands else f"src/wip/fn_{addr:08X}.c"
    text = open(f).read()
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    # a body file has no `// FLAG:` header, so allow an explicit override
    flags = None
    for i, a in enumerate(sys.argv):
        if a == "--flags" and i + 1 < len(sys.argv):
            flags = sys.argv[i + 1].split()
    if flags is None:
        flags = gl.draft_flags(text) or None
    got, masks = gl.compile_fn(addr, body, extra_flags=flags)
    if got is None:
        print("COMPILE FAIL:", masks)
        return
    import json
    rep = json.load(open("build/G2TE52/report.json"))
    size = None
    for u in rep.get("units", []):
        for fn in u.get("functions", []):
            if int(fn["metadata"]["virtual_address"]) == addr:
                size = int(fn["size"])
    orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + (size or len(got))]
    n = min(len(orig), len(got)) // 4
    w = list(md.disasm(orig, addr))
    g = list(md.disasm(got, addr))
    full = "--full" in sys.argv
    print(f"=== {addr:08X} want {len(orig)}B got {len(got)}B words={len(orig)//4}")
    real = 0
    for i in range(min(n, len(w), len(g))):
        ow = int.from_bytes(orig[i * 4:i * 4 + 4], "big")
        gw = int.from_bytes(got[i * 4:i * 4 + 4], "big")
        if ow == gw:
            if full:
                print(f"  +{i*4:03x} want {w[i].mnemonic:<10} {w[i].op_str:<22} | ==")
            continue
        if masks.get(i * 4, 0xFFFFFFFF) == 0xFFFFFFFF or show_all:
            real += 1
            print(f"  +{i*4:03x} want {w[i].mnemonic:<10} {w[i].op_str:<22} | got {g[i].mnemonic:<10} {g[i].op_str}")
    print(f"non-branch mismatching words: {real} / {len(orig)//4}")


if __name__ == "__main__":
    main()
