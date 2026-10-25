#!/usr/bin/env python3
"""Find parked drafts whose RETAIL bytes match a known function-family template.

Usage:
  tools/template_scan.py [--addr 0xADDR] [--size-cap 0x60] [--family NAME]

`tools/twin_scan.py` / `tools/near_twin_scan.py` need an already-MATCHED function
to copy from. This scanner needs nothing but the family's instruction template:
several families in this DOL are emitted from one source file, so their retail
byte shape is fixed except for a few immediates (a tail callee, a returned
constant, a QB name). A parked draft only has to sit at the right address to be
recognised — its own body is usually wrong, which is why text-grepping
`src/wip` for the family idiom under-reports (it misses every draft whose body
was recovered wrongly).

Each template is a list of expected words; `None` means "wildcard". Templates can
also declare `capture` indices to decode (currently: rel24 branch targets and
`li rD,imm` constants) so the fix can be generated automatically.

Add a template when a family is cracked; re-run after every promotion batch.
"""
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402

ROOT = gl.ROOT
SYMS = open(os.path.join(ROOT, "config/G2TE52/symbols.txt")).read()
OFF, TADDR, DATA = gl.t_off, gl.t_addr, gl.d

# --- templates ---------------------------------------------------------------
# `query` — the QB bool-query family (ScriptIsStreamPlaying, ScriptIsTrue, ...):
#   sp8 = 0; fn_801286D0(arg0, 0, &sp8, K4); if (<tail> != 0) return f(sp8);
#   return 0;
QUERY = {
    "size_cap": 0x60,
    "words": [0x9421FFF0, 0x7C0802A6, 0x90010014, 0x38000000, 0x38800000,
              0x90010008, 0x38A10008, 0x38C00000, None, 0x2C030000, None,
              None, 0x80610008, None],
    "li_at": 10,        # li r3,K  (K = returned constant)
    "bc_at": 11,        # beq
    "rel_at": 13,       # bl <tail>
}
TEMPLATES = {"query": QUERY}


def words(addr, n):
    o = OFF + (addr - TADDR)
    return list(struct.unpack(">%dI" % n, DATA[o:o + 4 * n]))


def fn_size(addr):
    m = re.search(r"= \.text:0x%08X; // type:function size:0x([0-9A-Fa-f]+)" % addr, SYMS)
    return int(m.group(1), 16) if m else None


def name_of(addr):
    m = re.search(r"(\w+) = \.text:0x%08X;" % addr, SYMS)
    return m.group(1) if m else "fn_%08X" % addr


def rel24_target(insn_addr, w):
    off = w & 0x03FFFFFC
    if off & 0x02000000:
        off -= 0x04000000
    return insn_addr + off


def match(addr, tpl, size_cap):
    size = fn_size(addr)
    if not size or size > size_cap:
        return None
    w = words(addr, size // 4 + 1)
    for j, exp in enumerate(tpl["words"]):
        if exp is not None and (j >= len(w) or w[j] != exp):
            return None
    if (w[tpl["li_at"]] & 0xFFFF0000) != 0x38600000:
        return None
    if (w[tpl["bc_at"]] >> 26) != 16 or ((w[tpl["bc_at"]] >> 21) & 31) != 12:
        return None
    if (w[tpl["rel_at"]] >> 26) != 18:
        return None
    tail = rel24_target(addr + 4 * tpl["rel_at"], w[tpl["rel_at"]])
    return {"addr": addr, "size": size, "K": w[tpl["li_at"]] & 0xFFFF,
            "tail": tail, "name": name_of(addr), "tail_name": name_of(tail)}


def main():
    fam = "query"
    if "--family" in sys.argv:
        fam = sys.argv[sys.argv.index("--family") + 1]
    tpl = TEMPLATES[fam]
    cap = int(sys.argv[sys.argv.index("--size-cap") + 1], 0) if "--size-cap" in sys.argv else tpl["size_cap"]
    if "--addr" in sys.argv:
        addrs = [int(sys.argv[sys.argv.index("--addr") + 1], 0)]
    else:
        addrs = [int(os.path.basename(p)[3:11], 16)
                 for p in sorted(glob.glob(os.path.join(ROOT, "src/wip/fn_*.c")))]
    hits = [h for h in (match(a, tpl, cap) for a in addrs) if h]
    print("family=%s  cap=0x%X  scanned=%d  hits=%d" % (fam, cap, len(addrs), len(hits)))
    for h in hits:
        print("  0x%08X size=0x%02X K=%d tail=0x%08X(%s)  %s"
              % (h["addr"], h["size"], h["K"], h["tail"], h["tail_name"], h["name"]))


if __name__ == "__main__":
    sys.exit(main())
