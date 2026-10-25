#!/usr/bin/env python3
"""Splice sweep-scanner winner bodies back into their drafts, A/B gated.

Scanners (`forwarded_test_scan.py`, `lead_arg_scan.py`, `label_call_arg_scan.py`,
`proto_undeclared_scan.py`, ...) write the winning *body* — comments stripped —
to `/tmp/<tag>_<ADDR>.c`.  Turning that back into a draft file naively loses
information, and two traps cost real debugging time:

1. **The `// FLAG:` line is not in the header block.**  `gen_leaves.draft_flags`
   scans the first 120 lines, and m2c-style drafts carry the flag *after* the
   includes, immediately above the function (`s32 fn_X(...);` then
   `// FLAG: -fno-expensive-optimizations`).  A splice that keeps "everything
   before the first `#include`" silently drops it, the draft is then scored
   *without* its flag, and a genuine win looks like a regression.  That is what
   made `fn_800E2A70` measure 34.8 -> 72.7 in the sweep and 34.8 -> 17.4 on
   re-apply.  This tool therefore keeps **every** comment line of the original.

2. **`LEAF_TMPDIR` / flags can make an in-process score unreachable.**  Always
   re-score the spliced file with `tools/score_addrs.py` before trusting it.

Usage
-----
    tools/venv/bin/python tools/apply_scan_winner.py /tmp/fwd_80131E50.c ...
    tools/venv/bin/python tools/apply_scan_winner.py --note "doc-59" /tmp/fwd_*.c

Exit status is 0 whether or not anything was written; the report says which.
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
import scan_score as ss  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ADDR_RE = re.compile(r"([0-9A-Fa-f]{8})\.c$")


def body_of(text):
    """Exactly how score_addrs.py builds a body from a draft file."""
    return "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()


def splice(orig, winner):
    """Original comment lines (in order) + winner's code lines (in order)."""
    comments = [l for l in orig.splitlines() if l.strip().startswith("//")]
    code = [l for l in winner.splitlines() if l.strip() and not l.strip().startswith("//")]
    return "\n".join(comments + code) + "\n"


def main():
    argv = sys.argv[1:]
    note = None
    if "--note" in argv:
        i = argv.index("--note")
        note = argv[i + 1]
        del argv[i:i + 2]
    args = [a for a in argv if not a.startswith("--")]

    applied, skipped = [], []
    for w in args:
        m = ADDR_RE.search(w)
        if not m:
            print("SKIP (no address in name):", w)
            continue
        a = m.group(1).upper()
        path = os.path.join(ROOT, "src", "wip", f"fn_{a}.c")
        if not os.path.exists(path):
            print("SKIP (no draft):", a)
            continue
        orig = open(path).read()
        new = splice(orig, open(w).read())

        flags_o = gl.draft_flags(orig) or None
        flags_n = gl.draft_flags(new) or None
        addr = int(a, 16)
        s0 = ss.pct(addr, body_of(orig), flags_o)
        s1 = ss.pct(addr, body_of(new), flags_n)

        if flags_o != flags_n:
            print(f"WARN {a}: flags changed {flags_o} -> {flags_n} (splice dropped a FLAG line?)")
        if s1 <= s0 + 0.05:
            skipped.append((a, s0, s1))
            continue
        if note:
            lines = new.splitlines()
            i = 0
            while i < len(lines) and lines[i].startswith("//"):
                i += 1
            lines.insert(i, f"// UPDATED 2026-09-15: {note}; now {s1:.1f}%.")
            new = "\n".join(lines) + "\n"
        open(path, "w").write(new)
        applied.append((a, s0, s1))

    print(f"applied {len(applied)}, skipped {len(skipped)}")
    for a, s0, s1 in sorted(applied, key=lambda t: t[2], reverse=True):
        print(f"  {a} {s0:.1f} -> {s1:.1f}")
    for a, s0, s1 in skipped:
        print(f"  (no gain) {a} {s0:.1f} -> {s1:.1f}")
    print("Re-verify every applied address with tools/score_addrs.py.")


if __name__ == "__main__":
    main()
