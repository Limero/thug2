#!/usr/bin/env python3
"""Find drafts whose `// FLAG:` line has gone stale (default flags now better).

A FLAG line is a cached decision taken against whatever body existed at the
time.  Once the body is fixed the flag can *regress* the draft -- fn_80054388
was 76.3% with its recorded `-fno-gcse -fno-expensive-optimizations` and 89.5%
with no flags at all, and fn_8005D4F4 went the same way earlier (doc 55).

This is the cheap half of tools/flagrefresh.py: score each flagged draft twice
(header flags vs default) and print the ones where dropping the flag wins.
Paired-single drafts are skipped -- `-mps-float` is load-bearing for them, not a
cache (`draft_flags()` re-adds it from `__ps_t` anyway).

Prints `0xADDR with=<pct> without=<pct>   <== DROP` and writes the flag-free
body to /tmp/noflag_<ADDR>.c for tools/apply_better.py.

Usage: printf 'ADDR\\n' | tools/venv/bin/python tools/flagdrop_scan.py
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
        path = f"src/wip/fn_{addr:08X}.c"
        text = open(path).read()
        if "__ps_t" in text or "__builtin_ps_" in text:
            continue
        flags = gl.draft_flags(text)
        if not flags:
            continue
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        _, pw, _ = test_one(addr, body, extra_flags=flags)
        _, pn, _ = test_one(addr, body, extra_flags=None)
        mark = "   <== DROP" if pn > pw + 0.01 else ""
        print(f"0x{addr:08X} with={pw:5.1f} without={pn:5.1f}{mark}")
        if pn > pw + 0.01:
            open(f"/tmp/noflag_{addr:08X}.c", "w").write(body + "\n")


if __name__ == "__main__":
    main()
