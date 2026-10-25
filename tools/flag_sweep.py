#!/usr/bin/env python3
"""PER-OBJECT FLAG sweep for WIP drafts.

Many NEAR residuals are ngccc scheduler / CSE / hoisting artifacts that no
source rewrite reaches, but a single per-object flag does (AGENTS.md recipes
§4p-48/49, §4r, §6ao-165, §6ar-223, §6ak-176/177, §6au-228).  This tool
tries each flag ON TOP OF the draft's own header flags and keeps strict
improvements, so a winner can be recorded in the draft's `// FLAG:` line.

NOTE (AGENTS.md §6z-134): flags are per-draft here (each file keeps its own
header flags), so this sweep is safe to run over a mixed address list - the
hazard is only when a single `--extra-cflags` is forced onto every draft.

usage:
    flag_sweep.py <file-list> [lo] [hi]
prints:  verdict<TAB>delta<TAB>file<TAB>info
"""
import os
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import test_wip_drafts as T  # noqa: E402

# single flags, then the two pairs that historically work together
SINGLES = [
    "-fno-schedule-insns",
    "-fno-schedule-insns2",
    "-fno-sched-spec",
    "-fno-sched-interblock",
    "-fno-sched-round",
    "-fno-gcse",
    "-fno-rerun-cse-after-loop",
    "-fno-expensive-optimizations",
    "-fno-cse-follow-jumps",
    "-fno-peephole2",
    "-fno-crossjumping",
    "-fno-thread-jumps",
    "-fno-reorder-blocks",
    "-fno-strength-reduce",
    "-fno-branch-count-reg",
    "-fno-tree-pre",
    "-fno-tree-ter",
    "-fno-if-conversion",
    "-fno-if-conversion2",
    "-fno-delete-null-pointer-checks",
    "-fno-ipa-cp",
]
PAIRS = [
    "-fno-schedule-insns -fno-schedule-insns2",
    "-fno-sched-spec -fno-sched-interblock",
    "-fno-gcse -fno-rerun-cse-after-loop",
]
COMBOS = SINGLES + PAIRS


def one(fn):
    fn = os.path.basename(fn)
    path = os.path.join(ROOT, "src/wip", fn)
    addr = int(fn[3:-2], 16)
    raw = open(path).read()
    hdr = T.gl.draft_flags(raw)
    body = "\n".join(l for l in raw.splitlines()
                     if not l.lstrip().startswith("//"))
    try:
        _, pct0, _ = T.test_one(addr, body, extra_flags=hdr or None)
    except Exception:  # noqa: BLE001
        return (fn, "ERR0", 0.0, "")
    best = (None, 0.0, "", 0.0, "")
    for c in COMBOS:
        try:
            st, pct, _ = T.test_one(addr, body,
                                    extra_flags=(hdr or []) + c.split())
        except Exception:  # noqa: BLE001
            continue
        if pct - pct0 > best[1] + 1e-9:
            best = (c, pct - pct0, st, pct, st)
    if best[0] is None:
        return (fn, "NONE", 0.0, "")
    return (fn, best[4], best[1], f"{best[0]} -> {best[3]:.2f}")


if __name__ == "__main__":
    files = [l.strip() for l in open(sys.argv[1]) if l.strip()]
    lo = int(sys.argv[2]) if len(sys.argv) > 2 else 0
    hi = int(sys.argv[3]) if len(sys.argv) > 3 else len(files)
    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="fl_")
    for fn, v, d, info in map(one, files[lo:hi]):
        if v != "NONE":
            print(f"{v}\t{d:+.2f}\t{fn}\t{info}", flush=True)
