#!/usr/bin/env python3
"""Find wip drafts that match the DOL *shifted* by N instruction words.

fn_80125020 was 14.8% with the wrong frame: an m2c local temp kept a pointer
live across the calls, so MWCC saved one extra callee-saved register, the frame
grew 4 bytes and every instruction after the prologue slid one word.  Aligning
the two bodies at the right offset showed the whole function actually matches --
a single source-shape edit away.

This scan slides `got` against `want` over a window of shifts, counts matching
words in the body (prologue/epilogue and branch instructions excluded), and
prints the drafts whose best shift is nonzero and much better than shift 0.

Prints `0xADDR want=NNB body=<best_hits>/<body_words> shift=<s> @0=<hits0>`.

Usage: printf 'ADDR\\n' | tools/venv/bin/python tools/shift_scan.py
       tools/venv/bin/python tools/shift_scan.py --nofs 0xADDR...   (ignore FLAG)
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
BRANCH_OP = {16, 18}  # bc, b
REPORT_PCT = 0.75     # best shift must reach this fraction of the body to print


def words(b):
    return [int.from_bytes(b[i:i + 4], "big") for i in range(0, len(b) - 3, 4)]


def is_branch(w):
    return (w >> 26) in BRANCH_OP


def opcodes(ws):
    return [(w >> 26) for w in ws]


def body_match(want, got, s, skip_head=4, skip_tail=6):
    """Matching words with got slid by s, over want's body region."""
    n = len(want)
    hits = tot = 0
    for i in range(skip_head, max(skip_head, n - skip_tail)):
        j = i + s
        if j < skip_head or j >= n - skip_tail or j >= len(got):
            continue
        tot += 1
        if want[i] == got[j]:
            hits += 1
        elif is_branch(want[i]) and is_branch(got[j]):
            hits += 1
    return hits, tot


def main():
    nofs = "--nofs" in sys.argv
    addrs = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not addrs:
        addrs = [l.strip() for l in sys.stdin if l.strip()]
    rep = json.load(open("build/G2TE52/report.json"))
    sizes = {}
    for u in rep.get("units", []):
        for fn in u.get("functions", []):
            sizes[int(fn["metadata"]["virtual_address"])] = int(fn["size"])
    for a in addrs:
        addr = int(a, 16)
        text = open(f"src/wip/fn_{addr:08X}.c").read()
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        flags = None if nofs else (gl.draft_flags(text) or None)
        got, masks = gl.compile_fn(addr, body, extra_flags=flags)
        if got is None:
            continue
        size = sizes.get(addr, len(got))
        orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + size]
        want = words(orig)
        g = words(got)
        if not want or not g:
            continue
        hits0, tot = body_match(want, g, 0)
        best, best_s = hits0, 0
        for s in range(-10, 11):
            if s == 0:
                continue
            h, t = body_match(want, g, s)
            if t and h > best:
                best, best_s = h, s
        if best_s != 0 and tot and best / tot >= REPORT_PCT and best > hits0:
            print(f"0x{addr:08X} want={len(orig)}B body={best}/{tot} shift={best_s:+d} @0={hits0}")


if __name__ == "__main__":
    main()
