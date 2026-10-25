#!/usr/bin/env python3
"""Re-sweep the flag axis on every draft that carries a `// FLAG:` line.

Motivated by fn_8005D4F4: its `// FLAG: -O1` was chosen against a crclr-broken
body; once the body was fixed the FLAG *regressed* it (85.2%) while the default
`-O2` was EXACT.  A FLAG line is a cached decision -- re-test it after any
structural fix.

Writes TSV: addr, base_pct, best_pct, base_flags, best_flags
"""
import glob
import os
import sys
from multiprocessing import Pool

sys.path.insert(0, "tools")

CAND = [
    [], ["-O1"], ["-O2"], ["-O3"], ["-Os"],
    ["-fno-schedule-insns"], ["-fno-schedule-insns2"],
    ["-fno-expensive-optimizations"], ["-fno-gcse"], ["-fno-strength-reduce"],
    ["-ffixed-r9"], ["-ffixed-r11"], ["-mps-float"],
    ["-fno-schedule-insns", "-fno-schedule-insns2"],
    ["-fno-rerun-cse-after-loop"], ["-fno-branch-count-reg"],
]


def _init():
    os.environ["LEAF_TMPDIR"] = "/tmp/leaf/fr%d" % os.getpid()


def work(path):
    import gen_leaves as gl
    from test_wip_drafts import test_one
    addr = int(os.path.basename(path)[3:11], 16)
    text = open(path).read()
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    base = gl.draft_flags(text) or []
    try:
        _, bp, _ = test_one(addr, body, extra_flags=base or None)
    except Exception:
        return None
    best, bfl = bp, base
    for c in CAND:
        if c == base:
            continue
        try:
            _, p, _ = test_one(addr, body, extra_flags=c or None)
        except Exception:
            continue
        if p > best + 0.01:
            best, bfl = p, c
    if best > bp + 0.01 or bfl != base:
        return "%08X\t%.2f\t%.2f\t%s\t%s" % (
            addr, bp, best, " ".join(base) or "-", " ".join(bfl) or "-")
    return None


if __name__ == "__main__":
    files = sorted(glob.glob("src/wip/fn_*.c"))
    files = [f for f in files if "\n// FLAG:" in "\n" + open(f).read()]
    print("drafts with FLAG:", len(files), flush=True)
    with Pool(8, initializer=_init) as pl:
        for r in pl.imap_unordered(work, files, chunksize=1):
            if r:
                print(r, flush=True)
