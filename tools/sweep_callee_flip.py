#!/usr/bin/env python3
"""Sweep every NEAR WIP draft: try flipping each called callee's proto
`void fn_X(...)` -> `s32 fn_X(...)` and report which flips improve or
match the DOL byte-exactly.

Motivation (M8.31-M8.34): the callee RETURN TYPE changes the caller's
arg-setup emission order (r3 becomes return-live -> later args load before
r3, ori/addi completion lands after li/mr). 17 functions were promoted
this way. This tool automates the search across all remaining drafts.

Verdicts:
  MATCH  — flip makes the draft byte-exact (promote it)
  IMPROVE — flip lowers the diff count vs base
  same/worse — reported only in --verbose
Only the single best flip is applied per draft (tries all candidate
callees; if several make it EXACT, applies the first).

Usage:
  tools/venv/bin/python tools/sweep_callee_flip.py [--slice i/m] [--apply]
  --slice i/m  only test a fraction (files sorted by addr)
  --apply      write the winning flip back into the draft file
Without --apply the tool only reports; run promote_wip.py afterwards on
the MATCH addresses.
"""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl

ROOT = gl.ROOT
WIP_DIR = f"{ROOT}/src/wip"


def masked_pct(orig, got, masks):
    n = len(orig) // 4
    if n == 0:
        return 0.0
    hit = 0
    for i in range(n):
        ow = int.from_bytes(orig[i * 4:(i + 1) * 4], "big")
        gw = int.from_bytes(got[i * 4:(i + 1) * 4], "big")
        if (ow & masks.get(i * 4, 0xFFFFFFFF)) == (gw & masks.get(i * 4, 0xFFFFFFFF)):
            hit += 1
    return 100.0 * hit / n


def diff_count(addr, body):
    """Return (ndiffs, len) vs the DOL, or None on compile failure."""
    got, masks = gl.compile_fn(addr, body)
    if got is None:
        return None
    orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + len(got)]
    if len(orig) < len(got):
        return None
    n = len(got) // 4
    bad = 0
    for i in range(n):
        ow = int.from_bytes(orig[i * 4:(i + 1) * 4], "big")
        gw = int.from_bytes(got[i * 4:(i + 1) * 4], "big")
        if (ow & masks.get(i * 4, 0xFFFFFFFF)) != (gw & masks.get(i * 4, 0xFFFFFFFF)):
            bad += 1
    return bad


def main():
    sl = None
    do_apply = "--apply" in sys.argv
    max_diff = 20
    if "--max-diff" in sys.argv:
        max_diff = int(sys.argv[sys.argv.index("--max-diff") + 1])
    if "--slice" in sys.argv:
        i, m = sys.argv[sys.argv.index("--slice") + 1].split("/")
        sl = (int(i), int(m))

    files = sorted(glob.glob(f"{WIP_DIR}/fn_*.c"))
    if sl:
        lo = sl[0] * len(files) // sl[1]
        hi = (sl[0] + 1) * len(files) // sl[1]
        files = files[lo:hi]
        print(f"(slice {sl[0]}/{sl[1]}: files {lo}-{hi} of total)")

    matches = []
    improves = []
    for fp in files:
        addr = int(re.search(r"fn_([0-9A-F]{8})\.c", fp).group(1), 16)
        t = open(fp).read()
        body = "\n".join(l for l in t.splitlines()
                         if not l.startswith("//") and "types.h" not in l)
        base = diff_count(addr, body)
        if base is None:
            continue
        if base == 0:
            continue  # already exact
        if base > max_diff:
            continue  # too far; flip is a fine-tune, not a rewrite

        # candidate callees: void-return protos actually called in the body
        protos = re.findall(r"void\s+(fn_[0-9A-F]{8})\s*\(([^;]*?)\);", t)
        best = (base, None, None)
        for callee, argsig in protos:
            # only flip protos that look like plain scalar arg lists
            if not re.fullmatch(r"(\s*(?:const\s+)?(?:s\d+|u\d+|void\s*\*|char\s*\*|f32|f64)\s*,\s*)*(?:const\s+)?(?:s\d+|u\d+|void\s*\*|char\s*\*|f32|f64)\s*", argsig):
                continue
            t2 = t.replace("void %s(%s);" % (callee, argsig),
                           "s32 %s(%s);" % (callee, argsig), 1)
            body2 = "\n".join(l for l in t2.splitlines()
                              if not l.startswith("//") and "types.h" not in l)
            nd = diff_count(addr, body2)
            if nd is None:
                continue
            if nd < best[0]:
                best = (nd, callee, t2)
        if best[1] is None:
            continue
        nd, callee, t2 = best
        if nd == 0:
            matches.append((addr, callee))
            if do_apply:
                open(fp, "w").write(t2)
        elif nd < base:
            improves.append((addr, base, nd, callee))
            if do_apply:
                open(fp, "w").write(t2)

    print("=== MATCH (byte-exact after flip) ===")
    for addr, callee in sorted(matches):
        print("MATCH 0x%08X %s" % (addr, callee))
    print("=== IMPROVED ===")
    for addr, b, nd, callee in sorted(improves):
        print("IMPROVE 0x%08X %d->%d %s" % (addr, b, nd, callee))
    print("=== totals: %d matches, %d improved%s ===" % (
        len(matches), len(improves), " (applied)" if do_apply else ""))


if __name__ == "__main__":
    main()
