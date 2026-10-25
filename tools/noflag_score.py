#!/usr/bin/env python3
"""Score wip drafts (addrs on stdin) with NO extra flags, ignoring `// FLAG:`.

A draft whose header flag is load-bearing will score worse here; a draft whose
flag *masks* the real defect scores better. Pair the output with a normal
tools/score_addrs.py run to find masked defects.

Usage: printf 'ADDR\n' | tools/venv/bin/python tools/noflag_score.py
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import test_wip_drafts as tw


def main():
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 16)
        text = open(f"src/wip/fn_{addr:08X}.c").read()
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        s, p, _ = tw.test_one(addr, body, None)
        print(f"0x{addr:08X} {s} {p:.1f}")


if __name__ == "__main__":
    main()
