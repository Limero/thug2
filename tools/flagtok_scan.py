#!/usr/bin/env python3
"""A/B each individual token of a `// FLAG:` line (keep the rest).

tools/flagdrop_scan.py tests "all header flags vs none"; this tests the middle
ground -- one stale token inside an otherwise load-bearing flag set.  A header
like `-mps-float -fno-schedule-insns` can be right about -mps-float and wrong
about the scheduler flag.

Prints `0xADDR with=<pct> best=<pct> [-token ...]   <== DROP`; the winning body
plus its flag set go to /tmp/flagtok_<ADDR>.c and /tmp/flagtok_<ADDR>.flags.

Usage: printf 'ADDR\\n' | tools/venv/bin/python tools/flagtok_scan.py
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from test_wip_drafts import test_one


def main():
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 16)
        text = open(f"src/wip/fn_{addr:08X}.c").read()
        flags = gl.draft_flags(text)
        if len(flags) < 2:
            continue                      # nothing to peel; flagdrop covers len<=1
        if "__ps_t" in text or "__builtin_ps_" in text:
            continue
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        _, pw, _ = test_one(addr, body, extra_flags=flags)
        best_pct, best_flags, best_drop = pw, flags, None
        for i in range(len(flags)):
            sub = flags[:i] + flags[i + 1:]
            _, pct, _ = test_one(addr, body, extra_flags=sub)
            if pct > best_pct + 0.01:
                best_pct, best_flags, best_drop = pct, sub, flags[i]
        if best_drop:
            print(f"0x{addr:08X} with={pw:5.1f} best={best_pct:5.1f} "
                  f"[{best_drop}]   <== DROP")
            open(f"/tmp/flagtok_{addr:08X}.c", "w").write(body + "\n")
            open(f"/tmp/flagtok_{addr:08X}.flags", "w").write(" ".join(best_flags))


if __name__ == "__main__":
    main()
