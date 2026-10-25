#!/usr/bin/env python3
"""Build the *sweepable* wip pool: drafts a body-level sweep can actually move.

Every "no-park" pool used to be built with

    grep -L -iE '^//.*park' src/wip/*.c

which only excludes drafts whose header happens to contain the word "park".
Several classes of draft can *never* be matched by editing a body, and they
were silently absorbed into every residual-ranked sweep (they score 0.0, so a
residual sort does not push them out; they merely consume sweep budget and get
re-picked every round).

Excluded classes
----------------
promoted      ``src/fn_<addr>.c`` exists — already matched, no work left.
parked        a leading ``// ...park...`` comment (the human/agent park note).
stub          ``family=stub`` — the file carries only a bare stub body and
              **no C statements**, so it compiles to an empty
              object and scores 0.0 by construction.  Writing it is author
              work, not sweep work.
untestable    ``Status: UNTESTABLE`` — the address is not a report.json
              boundary, so ``_want_sizes().get(addr)`` misses and the harness
              compares against a *slice of the neighbour*.
unlabeled     ``UNLABELED:`` — no symbols.txt function symbol claims the
              region, so ``check_markers`` blocks any promotion.  Also covers
              data regions misread as code.

Usage
-----
    python3 tools/sweepable_pool.py              # bare 8-hex addresses
    python3 tools/sweepable_pool.py --stats      # per-class counts
    python3 tools/sweepable_pool.py --0x           # 0x-prefixed addresses

The old ``grep -L`` idiom is only correct *after* every non-sweepable draft has
been tagged; this tool does not depend on that having happened.
"""
import glob
import os
import re
import sys

CLASSES = ("promoted", "parked", "stub", "untestable", "unlabeled")

# A park note is a COMMENT line containing "park": either a `//` line or any line
# inside a block comment (the opening `/*` line, or a ` *` continuation line).
# The original `^//.*park` test missed every note written as a `/* ... */` block
# at the bottom of the file (fn_8000A0A8), so those already-diagnosed drafts kept
# re-entering the residual-ranked sweeps and were re-picked every round.
PARK_RE = re.compile(r"(?m)^\s*(?://|/\*|\*).*?park", re.I)


def classify(path, promoted):
    base = os.path.basename(path)
    if base in promoted:
        return "promoted"
    text = open(path, encoding="utf-8", errors="replace").read()
    # Case-INSENSITIVE: the human/agent park note is written both as lowercase
    # `// parked ...` and uppercase `// PARKED ...` in this corpus, and the
    # uppercase form used to classify as sweepable — so already-diagnosed
    # drafts (including 9 false-EXACT lib-covered stubs and several
    # link-level-blocker notes) kept re-entering every residual-ranked sweep.
    # Specific structural tags first: an UNTESTABLE/draft also often carries a
    # park note, and reporting it as `parked` would hide the real reason.
    if "family=stub" in text:
        return "stub"
    if "Status: UNTESTABLE" in text:
        return "untestable"
    if "UNLABELED:" in text:
        return "unlabeled"
    if PARK_RE.search(text):
        return "parked"
    return None


def main():
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    wip = os.path.join(root, "src", "wip")
    promoted = {os.path.basename(p) for p in glob.glob(os.path.join(root, "src", "fn_*.c"))}

    counts = dict.fromkeys(CLASSES, 0)
    sweepable = []
    total = 0
    for path in sorted(glob.glob(os.path.join(wip, "fn_*.c"))):
        total += 1
        cls = classify(path, promoted)
        if cls is None:
            sweepable.append(os.path.basename(path)[3:11])
        else:
            counts[cls] += 1

    if "--stats" in sys.argv:
        for cls in CLASSES:
            print(f"{cls:11s} {counts[cls]:5d}")
        print(f"{'sweepable':11s} {len(sweepable):5d}")
        print(f"{'total':11s} {total:5d}")
        return

    prefix = "0x" if "--0x" in sys.argv else ""
    for a in sweepable:
        print(prefix + a)


if __name__ == "__main__":
    main()
