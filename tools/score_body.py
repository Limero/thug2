#!/usr/bin/env python3
"""Score a candidate function body against the DOL:  score_body.py 0xADDR body.c

Reads a body file, strips comment lines, compiles it like the rest of the
toolchain, and prints "STATUS pct hit/total".  Optionally pass extra cflags
after the body path.

RACE HAZARD: `gen_leaves.compile_fn` writes `$LEAF_TMPDIR/<addr>.o`, whose name
is derived from the ADDRESS only.  Two processes scoring the SAME address in
parallel therefore share one object file and each can report the other's
score -- which silently corrupts variant sweeps (a body that really scores
62.3% was measured at 97.4% this way, because six variants of one function ran
under `xargs -P`).  So unless the caller already set `LEAF_TMPDIR`, this script
points it at a per-PID directory.  Bash one-liners that fan variants out with
`&` should use `-v` or `--tmpdir=DIR` per worker instead.
"""
import os
import sys

if os.environ.get("LEAF_TMPDIR") in (None, "", "/tmp/leaf"):
    os.environ["LEAF_TMPDIR"] = "/tmp/leaf/sb%d" % os.getpid()

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from test_wip_drafts import test_one


def main():
    addr = int(sys.argv[1], 0)
    text = open(sys.argv[2]).read()
    flags = sys.argv[3].split() if len(sys.argv) > 3 else None
    # Honor the draft's own `// FLAG:` / `// extra_cflags:` line, exactly like
    # the sweeps do.  Without this a draft that only matches WITH its flag is
    # scored under default flags and looks further away than it is (fn_800E3520
    # reads 87.1% here and 100.0% with its `-fno-schedule-insns2`).
    if flags is None:
        flags = gl.draft_flags(text) or None
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    status, pct, err = test_one(addr, body, flags)
    print("%s %.1f%% %s" % (status, pct, err))


if __name__ == "__main__":
    main()
