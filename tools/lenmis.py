#!/usr/bin/env python3
"""Compile every non-promoted draft and report length mismatch (got vs want).

A length mismatch means a whole-frame transcription bug (a dropped call
argument, an extra/missing statement, a varargs `crclr`/`crset` word) -- the
class that took fn_80044F60 to EXACT.  Purely masked-word diffs always have
equal lengths.

Usage: tools/venv/bin/python tools/lenmis.py [min_pct]
"""
import glob
import json
import os
import sys
from multiprocessing import Pool

sys.path.insert(0, "tools")
MIN = float(sys.argv[1]) if len(sys.argv) > 1 else 0.0


def _init():
    os.environ["LEAF_TMPDIR"] = "/tmp/leaf/lm%d" % os.getpid()


def work(path):
    import gen_leaves as gl
    from test_wip_drafts import masked_pct
    addr = int(os.path.basename(path)[3:11], 16)
    text = open(path).read()
    if "family=stub" in text or "family=tp" in text:
        return None
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    want = SIZES.get(addr)
    if want is None:
        return None
    got, masks = gl.compile_fn(addr, body, extra_flags=gl.draft_flags(text) or None)
    if got is None:
        return None
    if len(got) == want:
        return None
    orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + max(want, len(got))]
    if len(orig) < want:
        return None
    pct = masked_pct(orig, got, masks)
    if pct < MIN:
        return None
    st = "EXACT" if pct >= 100.0 else ("NEAR" if pct >= 50.0 else "DIFF")
    return (abs(len(got) - want), addr, len(got), want, pct, st)


rep = json.load(open("build/G2TE52/report.json"))
SIZES = {int(fn["metadata"]["virtual_address"]): int(fn["size"])
         for u in rep.get("units", []) for fn in u.get("functions", [])}


if __name__ == "__main__":
    files = sorted(glob.glob("src/wip/fn_*.c"))
    rows = []
    with Pool(8, initializer=_init) as pl:
        for r in pl.imap_unordered(work, files, chunksize=2):
            if r:
                rows.append(r)
    rows.sort(reverse=True)
    print("length mismatches:", len(rows))
    for d, a, g, w, p, s in rows:
        print("  %08X  got %4d want %4d  (%+d)  %5.1f%% %s" % (a, g, w, g - w, p, s))
