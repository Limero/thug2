#!/usr/bin/env python3
"""A/B the "m2c invented a label address as a call argument" lever (doc 52 addendum).

fn_800249A4's `fn_800550D4(arg0->unk0x10, (s32)lbl_802913F8)` was wrong: retail
passes the function's own arg1 through and materialises lbl_802913F8 only for a
struct store.  m2c sees the `lis/addi` pair and assumes it feeds the call, then
has to invent a `mr r4, r9` that retail never had.

Unlike tools/drop_phantom_arg.py (bare 0x80xxxxxx literals), this scan targets
*symbol* arguments: `(s32)lbl_X`, `(u32)lbl_X`, `lbl_X`, `&lbl_X`, and the raw
`(s32)0x8029xxxx` form.  For each call site it tries dropping each candidate
argument alone and all of them together, keeps whichever scores best, and
prints `0xADDR orig% -> STATUS best%   <== BETTER`.

Usage: printf 'ADDR\\n' | tools/venv/bin/python tools/label_arg_scan.py
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from test_wip_drafts import test_one
from drop_phantom_arg import find_calls, trim_proto

LBL = re.compile(r"^\(?(s32|u32|int|unsigned)?\)?\s*(&?lbl_[0-9A-Fa-f]{8}"
                 r"|\(s32\)\s*0x80[0-9A-Fa-f]{6})\)?$")


def candidates(body):
    """(name, arg_start, arg_end, args, index) for every label-ish call arg."""
    out = []
    for name, i0, i1, args, _ in find_calls(body):
        if name in ("sizeof",):
            continue
        for k, arg in enumerate(args):
            if len(args) < 2:
                continue
            if LBL.match(arg.strip()):
                out.append((name, i0, i1, args, k))
    return out


def apply(body, edits):
    """Drop the given (name, i0, i1, args, k) sites back-to-front."""
    new = body
    protos = {}
    for name, i0, i1, args, k in sorted(edits, key=lambda e: -e[1]):
        keep = [x for idx, x in enumerate(args) if idx != k]
        new = new[:i0 + 1] + ", ".join(keep) + new[i1:]
        protos.setdefault(name, (len(args), set()))[1].add(k)
    for name, (n, dropped) in protos.items():
        for k in sorted(dropped, reverse=True):
            new = trim_proto(new, name, n, k)
    return new


def main():
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 16)
        text = open(f"src/wip/fn_{addr:08X}.c").read()
        flags = gl.draft_flags(text) or None
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        cands = candidates(body)
        if not cands:
            continue
        s0, p0, _ = test_one(addr, body, flags)
        best, best_pct, best_src = None, p0, None
        for e in cands:                       # one site at a time
            src = apply(body, [e])
            _, pct, _ = test_one(addr, src, flags)
            if pct > best_pct:
                best, best_pct, best_src = e, pct, src
        src = apply(body, cands)              # and all of them together
        _, pct, _ = test_one(addr, src, flags)
        if pct > best_pct:
            best_pct, best_src = pct, src
        mark = "  <== BETTER" if best_pct > p0 else ""
        print(f"0x{addr:08X} {p0:5.1f} -> {best_pct:5.1f}{mark}")
        if best_src is not None and best_pct > p0:
            open(f"/tmp/lblarg_{addr:08X}.c", "w").write(best_src + "\n")


if __name__ == "__main__":
    main()
