#!/usr/bin/env python3
"""Restore the highest-scoring committed revision of each wip draft's body.

The wip pool carries a drift class: a file's header notes can describe a body
that no longer exists.  Two in-tree passes rewrite bodies **in place** and keep
whatever they produced:

  * the struct-ification sweep (`void *` params/locals -> `Unk_XXXXXXXX *`,
    `s32 sp8` + `(Unk_59AB5482 *)&sp8` -> `Unk_59AB5482 sp8`), which changes
    register classes and store order, and
  * `tools/store_order_search.py`, which permutes store/assignment blocks and
    writes the result back even when the permutation is a regression.

Examples found 2026-09-20 (working body -> best committed revision):

    fn_80146560    1.0% ->  93.0%   (`s32 sp88` re-struct-ified)
    fn_80207430   92.4% -> 100.0%   (asm pinned init hoisted out of the loop)
    fn_8021D2C4   43.2% ->  97.3%   (store-order search + struct-ification)
    fn_8021D990   38.9% ->  97.2%
    fn_8021D5DC   44.4% ->  97.2%
    fn_801CD68C   47.7% ->  94.5%
    fn_80014FCC   60.0% ->  94.3%   (array-symbol globals re-typed to scalars)
    fn_801E1224   45.9% ->  92.5%

This tool enumerates every distinct body ever committed for `src/wip/fn_ADDR.c`,
scores each with the same rules `tools/score_addrs.py` uses (including the
per-draft `// FLAG:` line and the FPR dummy best-of), and — with `--write` —
replaces the file with the winner, prefixing a note that records the previous
score, the winning revision and the number of bodies compared.  Revisions that
tie are ignored, so a genuine later improvement is never reverted.

Always re-score afterwards with `tools/score_addrs.py`; a revision that won
here can still lose against a header that has since changed.

Usage:
  printf 'ADDR\\n' | tools/venv/bin/python tools/restore_best_body.py [--write]
  tools/venv/bin/python tools/restore_best_body.py --write < /tmp/candidates.txt
"""
import hashlib
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
from test_wip_drafts import inject_dummy, test_one, want_fpr_frame  # noqa: E402

TOLERANCE = 0.05


def score(addr, text):
    """Masked-match percentage of `text` scored as a draft for `addr`."""
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//")
                     and "types.h" not in l).strip()
    flags = gl.draft_flags(text) or None
    try:
        fpr = want_fpr_frame(addr)
        if fpr is not None and "volatile double" not in body:
            _, p0, _ = test_one(addr, body, flags)
            _, p1, _ = test_one(addr, inject_dummy(body), flags)
            return max(p0, p1)
        _, p, _ = test_one(addr, body, flags)
        return p
    except Exception:
        return -1.0


def committed_bodies(path):
    """{body-hash: (rev, text)} for every distinct committed revision."""
    revs = subprocess.run(["git", "log", "--format=%h", "--", path],
                          capture_output=True, text=True).stdout.split()
    out = {}
    for rev in revs:
        text = subprocess.run(["git", "show", f"{rev}:{path}"],
                              capture_output=True, text=True).stdout
        if not text.strip():
            continue
        out.setdefault(hashlib.md5(text.encode()).hexdigest(), (rev, text))
    return out


def with_note(text, note):
    """Insert a `//` note block before the first non-comment line."""
    lines = text.splitlines()
    for i, line in enumerate(lines):
        if line.strip() and not line.startswith("//"):
            return "\n".join(lines[:i] + note + lines[i:]) + "\n"
    return text


def main():
    write = "--write" in sys.argv[1:]
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 16)
        path = f"src/wip/fn_{addr:08X}.c"
        cur_text = open(path).read()
        cur = score(addr, cur_text)
        bodies = committed_bodies(path)
        best = max(((score(addr, t), rev) for rev, t in bodies.values()),
                   default=None)
        if best is None:
            print(f"0x{addr:08X} no git history")
            continue
        best_pct, best_rev = best
        if best_pct <= cur + TOLERANCE:
            print(f"0x{addr:08X} keep   cur={cur:5.1f} best={best_pct:5.1f} "
                  f"({len(bodies)} bodies)")
            continue
        note = [
            f"// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body",
            f"// scored {cur:.1f}% while git revision {best_rev} scores {best_pct:.1f}%;",
            f"// the pool's struct-ification sweep and/or tools/store_order_search.py had",
            f"// rewritten this body in place and kept the worse result while the notes",
            f"// above stayed put.  Winner picked from {len(bodies)} distinct committed bodies.",
            f"// Re-verify with tools/score_addrs.py before editing again.",
        ]
        new_text = with_note(bodies[[k for k, v in bodies.items()
                                     if v[0] == best_rev][0]][1], note)
        print(f"0x{addr:08X} RESTORE cur={cur:5.1f} -> {best_pct:5.1f} @{best_rev}"
              f" ({len(bodies)} bodies)")
        sys.stdout.flush()
        if write:
            with open(path, "w") as fh:
                fh.write(new_text)
            check = score(addr, new_text)
            if abs(check - best_pct) > TOLERANCE:
                print(f"0x{addr:08X} WARNING re-score {check:.1f} != {best_pct:.1f}")


if __name__ == "__main__":
    main()
