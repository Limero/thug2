#!/usr/bin/env python3
"""Stamp a winning per-object flag from `flag_sweep.py` output into the
draft's `// FLAG:` line (tools/flag_sweep.py produces the TSV; this applies it).

Skips drafts that already carry a FLAG marker, so it is safe to re-run.

usage: flag_apply.py <flag_sweep.tsv> [min_delta]
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    tsv = sys.argv[1]
    mind = float(sys.argv[2]) if len(sys.argv) > 2 else 0.0
    n = 0
    for line in open(tsv):
        line = line.rstrip("\n")
        if not line.strip():
            continue
        parts = line.split("\t")
        if len(parts) < 4:
            continue
        _verdict, delta, fn, info = parts[0], parts[1], parts[2], parts[3]
        if float(delta) < mind:
            continue
        flag = info.split(" -> ")[0].strip()
        if not flag.startswith("-f"):
            continue
        path = os.path.join(ROOT, "src/wip", fn)
        if not os.path.exists(path):
            print(f"SKIP (gone) {fn}")
            continue
        s = open(path).read()
        if "FLAG:" in s or "extra_cflags" in s:
            print(f"SKIP (has FLAG) {fn}")
            continue
        s2, k = re.subn(r"(?m)^(// family=.*)$", r"\1\n// FLAG: " + flag,
                        s, count=1)
        if not k:
            print(f"SKIP (no family= line) {fn}")
            continue
        open(path, "w").write(s2)
        print(f"{fn}: +{delta} FLAG: {flag}")
        n += 1
    print(f"applied {n}")


if __name__ == "__main__":
    main()
