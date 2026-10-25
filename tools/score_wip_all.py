#!/usr/bin/env python3
"""Bulk masked score of one or more src/wip drafts (clamped to the symbol
size). Prints one `<pct> <addr> <file>` line per draft, sorted descending when
run through tools/score_wip_sort.sh.

Usage: tools/venv/bin/python tools/score_wip_all.py <file> [flags...]
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402

SIZES = {}


def load_sizes():
    if SIZES:
        return SIZES
    with open(os.path.join(ROOT, "config/G2TE52/symbols.txt")) as fh:
        for line in fh:
            m = re.match(r"^\S+\s*=\s*\.text:0x([0-9A-Fa-f]+);.*size:0x([0-9A-Fa-f]+)", line)
            if m:
                SIZES[int(m.group(1), 16)] = int(m.group(2), 16)
    return SIZES


def score(addr, path, flags):
    raw = open(path).read()
    body = "\n".join(l for l in raw.splitlines() if not l.lstrip().startswith("//"))
    size = load_sizes().get(addr, 0)
    if not size:
        return "0.00 SYMBOL?"
    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="sa_")
    if ("__ps_t" in body or "__builtin_ps_" in body) and "-mps-float" not in flags:
        flags = flags + ["-mps-float"]
    try:
        got, masks = gl.compile_fn(addr, body, extra_flags=flags or None)
    except Exception:
        return "0.00 FAIL"
    if got is None:
        return "0.00 FAIL"
    off = gl.t_off + (addr - gl.t_addr)
    want = gl.d[off:off + size]
    n = min(len(want), len(got)) // 4
    if n == 0:
        return "0.00 EMPTY"
    nd = 0
    for i in range(n):
        gw = int.from_bytes(want[i * 4:i * 4 + 4], "big")
        gg = int.from_bytes(got[i * 4:i * 4 + 4], "big")
        if (gw & masks.get(i * 4, 0xFFFFFFFF)) != (gg & masks.get(i * 4, 0xFFFFFFFF)):
            nd += 1
    long = " LONG" if len(got) > size else ""
    return f"{100.0 * (n - nd) / n:.2f}{long} {len(got)}/{size}"


def main():
    path = sys.argv[1]
    flags = [a for a in sys.argv[2:] if a.startswith("-")]
    m = re.search(r"fn_([0-9A-Fa-f]{8})\.c$", path)
    if not m:
        print("skip", path)
        return
    addr = int(m.group(1), 16)
    print(score(addr, path, flags), path)


if __name__ == "__main__":
    main()
