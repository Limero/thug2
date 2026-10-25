#!/usr/bin/env python3
"""A/B the "raw literal where a registered symbol exists" lever.

fn_8006A8C0 called `fn_8006A960(0x80366590, &sp8)`; retail is

    lis r3, -0x7fca
    addi r3, r3, 0x6590

MWCC materialises a *literal* constant's low half with `ori` and a *symbol*
address with `addi`.  Feeding it `lbl_80366590` (which exists in
symbols.txt) flips the instruction and the draft goes to 100%.

tools/fix_raw_lit.py (2026-09-06 one-off) already rewrote literals that sit at
the *end* of an argument list -- the `,`-separated mid-list ones were missed,
which is the common shape for these calls.

For each draft this tries (a) every literal site replaced at once and (b) each
site on its own, keeps the best, and prints
`0xADDR old% -> best%   <== BETTER`.  The winning body is written to
/tmp/rawsym_<ADDR>.c.

Usage: printf 'ADDR\\n' | tools/venv/bin/python tools/raw_sym_scan.py [--all-sites]
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from test_wip_drafts import test_one

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LBL = set()
for _line in open(f"{ROOT}/config/G2TE52/symbols.txt"):
    _m = re.match(r"(lbl_[0-9A-F]{8}) = \.[a-z0-9]+:0x([0-9A-F]{8});", _line)
    if _m:
        LBL.add(int(_m.group(2), 16))

# the literal, its leading cast if any, and what follows
SITE = re.compile(r"((?:\((?:s32|u32|int|char|void)\))?)\s*0x([0-9A-Fa-f]{8})")
MAX_SITES = 6


def sites(body):
    out = []
    for m in SITE.finditer(body):
        addr = int(m.group(2), 16)
        if addr not in LBL:
            continue
        after = body[m.end():m.end() + 2]
        before = body[:m.start()].rstrip()
        if before.endswith("(char *)") or before.endswith("(void *)"):
            continue  # handled by fix_raw_lit.py
        out.append((m.start(), m.end(), m.group(1), addr, after))
    return out


def replace(body, chosen):
    """chosen: list of (start, end, cast, addr, after) to rewrite."""
    sym = {}
    new = body
    for s, e, cast, addr, after in sorted(chosen, key=lambda t: -t[0]):
        name = f"lbl_{addr:08X}"
        sym[name] = 1
        # mid-arg / expression position needs an integer-typed reference
        txt = f"(s32){name}" if (cast or after.startswith(",") or after.startswith(")")
                                 or after == "") else name
        new = new[:s] + txt + new[e:]
    decls = "".join(f"extern char {n}[];\n" for n in sorted(sym))
    return decls + new


def main():
    all_sites = "--all-sites" in sys.argv
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 16)
        text = open(f"src/wip/fn_{addr:08X}.c").read()
        flags = gl.draft_flags(text) or None
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        st = sites(body)
        if not st:
            continue
        s0, p0, _ = test_one(addr, body, flags)
        best_pct, best_src = p0, None
        for trial in ([st] if all_sites else [[x] for x in st[:MAX_SITES]]) + [st]:
            src = replace(body, trial)
            _, pct, _ = test_one(addr, src, flags)
            if pct > best_pct:
                best_pct, best_src = pct, src
        mark = "  <== BETTER" if best_pct > p0 else ""
        print(f"0x{addr:08X} {p0:5.1f} -> {best_pct:5.1f}{mark}")
        if best_src is not None:
            open(f"/tmp/rawsym_{addr:08X}.c", "w").write(best_src + "\n")


if __name__ == "__main__":
    main()
