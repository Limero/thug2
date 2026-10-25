#!/usr/bin/env python3
"""Sweep splits.txt for unregistered .text gaps and rank the matchable ones.

A "gap" is any run of .text not covered by a hand-written split entry. Such
runs are currently emitted as auto-asm units (main/auto_*_text). Most gaps are
padding/data or already-parked drafts; the actionable ones are auto-asm
functions that have NO C draft on disk at all (neither src/ nor src/wip) and
fall in a matchable size range.

Used to close one-off gaps like fn_8006FAC8 / fn_8006FBCC (which were pure
auto-asm with no draft, then matched byte-identical and registered).

Usage:
    tools/venv/bin/python tools/sweep_gaps.py [--min N] [--max M] [--top K]
"""
import argparse
import json
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SPLITS = f"{ROOT}/config/G2TE52/splits.txt"
REPORT = f"{ROOT}/build/G2TE52/report.json"


def read_text_bounds():
    """Return (.text start, .text end)."""
    import sys
    sys.path.insert(0, f"{ROOT}/tools")
    import gen_leaves as gl
    return gl.t_addr, gl.t_addr + gl.t_size


def covered_ranges():
    ranges = []
    for ln in open(SPLITS):
        m = re.search(r"\.text\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)", ln)
        if m:
            ranges.append((int(m.group(1), 16), int(m.group(2), 16)))
    ranges.sort()
    merged = []
    for s, e in ranges:
        if merged and s <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(merged[-1][1], e))
        else:
            merged.append((s, e))
    return merged


def gaps(t0, t1, merged):
    out, cur = [], t0
    for s, e in merged:
        if s > cur:
            out.append((cur, s))
        cur = max(cur, e)
    if cur < t1:
        out.append((cur, t1))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--min", type=int, default=8)
    ap.add_argument("--max", type=int, default=256)
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--all", action="store_true", help="print every no-draft candidate")
    args = ap.parse_args()

    t0, t1 = read_text_bounds()
    merged = covered_ranges()
    gl = gaps(t0, t1, merged)
    print(f"text 0x{t0:08X}-0x{t1:08X}; {len(merged)} merged covered ranges; "
          f"{len(gl)} uncovered runs")

    wipsrc = {f[3:11].upper() for f in os.listdir(f"{ROOT}/src/wip") if f.startswith("fn_")}
    srcset = {f[3:11].upper() for f in os.listdir(f"{ROOT}/src") if f.startswith("fn_")}

    rep = json.load(open(REPORT))
    nocand = []
    thanked = 0
    for u in rep.get("units", []):
        uname = u.get("name", "")
        if not uname.startswith("main/auto_"):
            continue
        for fn in u.get("functions", []):
            va = int(fn["metadata"]["virtual_address"])
            if not (t0 <= va < t1):
                continue
            size = int(fn.get("size", 0))
            st = "%08X" % va
            if fn.get("fuzzy_match_percent") is not None and fn.get("fuzzy_match_percent") >= 100:
                continue
            if st in srcset:
                continue
            if st in wipsrc:
                thanked += 1
                continue
            nocand.append((va, size, uname.split("/")[-1]))

    nocand.sort()
    inrange = [c for c in nocand if args.min <= c[1] <= args.max]
    print(f"auto-asm functions with NO draft at all: {len(nocand)} "
          f"(drafted-but-unmatched: {thanked}); in {args.min}-{args.max}B: {len(inrange)}")

    shown = nocand if args.all else inrange[: args.top]
    print(f"--- candidates ({len(shown)}) ---")
    for va, size, unit in shown:
        print(f"  0x{va:08X} {size:4d}B  fn_{va:08X}  {unit}")


if __name__ == "__main__":
    main()