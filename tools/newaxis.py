#!/usr/bin/env python3
"""Pool-wide sweep of new flag axes over EVERY non-promoted draft.

`-Os` and `-fno-rerun-cse-after-loop` were both absent from the historical
flag vocabulary; the flagrefresh pass found six drafts where `-Os` alone beat
the stored flags by 3.5-25.8 points.  This pass applies them to the whole pool.

Usage: tools/venv/bin/python tools/newaxis.py [-Os] [-fno-rerun-cse-after-loop]
"""
import glob
import os
import sys
from multiprocessing import Pool

sys.path.insert(0, "tools")
CAND = sys.argv[1:] or ["-Os"]


def _init():
    os.environ["LEAF_TMPDIR"] = "/tmp/leaf/na%d" % os.getpid()


def work(path):
    import gen_leaves as gl
    from test_wip_drafts import test_one
    addr = int(os.path.basename(path)[3:11], 16)
    text = open(path).read()
    if "family=stub" in text or "family=tp" in text:
        return None
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    base = gl.draft_flags(text) or []
    try:
        _, bp, _ = test_one(addr, body, extra_flags=base or None)
    except Exception:
        return None
    best, bfl = bp, base
    for c in CAND:
        if c in base:
            continue
        try:
            _, p, _ = test_one(addr, body, extra_flags=base + [c])
        except Exception:
            continue
        if p > best + 0.01:
            best, bfl = p, base + [c]
    if best > bp + 0.01:
        return "%08X\t%.2f\t%.2f\t%s\t%s" % (
            addr, bp, best, " ".join(base) or "-", " ".join(bfl))
    return None


if __name__ == "__main__":
    files = sorted(glob.glob("src/wip/fn_*.c"))
    print("drafts:", len(files), "candidates:", CAND, flush=True)
    with Pool(8, initializer=_init) as pl:
        for r in pl.imap_unordered(work, files, chunksize=2):
            if r:
                print(r, flush=True)
