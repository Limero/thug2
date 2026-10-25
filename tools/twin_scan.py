#!/usr/bin/env python3
"""Find byte-twin functions: a wip draft whose retail bytes duplicate a MATCHED fn.

The cheapest remaining lever on a parked draft is often not a new source shape at
all — it is the source shape of a function that has ALREADY been matched and
whose retail bytes are identical. Sibling families in this DOL were emitted from
one source file by one compiler, so a byte-identical twin is a proven recipe:
copy its body, rename the function, done (2026-09-19: 42 drafts promoted EXACT
this way, several of them carrying park notes that blamed a register-allocation
"wall" for years — see docs/parkings/solved/64-byte-twin-recipe.md).

The comparison is over the RAW retail bytes (relocation targets included), so a
hit means the whole instruction stream is identical, not merely the shape.

Usage:
  tools/venv/bin/python tools/twin_scan.py [--min-size N] [--parked-only]
                                          [--wip ADDR] [--addr ADDR] [--source]

  --min-size N     ignore functions smaller than N bytes (default: 12, which
                   skips the 4B/8B `blr` leaves whose "twins" are noise)
  --parked-only    only report drafts whose header mentions park/PARKED
  --wip ADDR       only report one draft
  --addr ADDR      also show every matched twin of this single address
  --source         print the twin's source file path (handy for `cat`)
"""
import hashlib
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl          # noqa: E402  (ROOT, DOL image, text bounds)
import test_wip_drafts as tw     # noqa: E402  (_want_sizes: per-symbol sizes)

WANT = tw._want_sizes()


def want_bytes(addr, size):
    off = gl.t_off + (addr - gl.t_addr)
    return gl.d[off:off + size]


def collect(d):
    """{addr: (size, sha1 of the retail bytes)} for fn_XXXXXXXX.c files in d."""
    out = {}
    for f in sorted(os.listdir(d)):
        m = re.match(r"fn_([0-9A-F]{8})\.c$", f)
        if not m:
            continue
        addr = int(m.group(1), 16)
        size = WANT.get(addr)
        if not size:
            continue
        b = want_bytes(addr, size)
        if len(b) != size:
            continue
        out[addr] = (size, hashlib.sha1(b).hexdigest())
    return out


def argval(flag, default=None):
    return sys.argv[sys.argv.index(flag) + 1] if flag in sys.argv else default


def main():
    min_size = int(argval("--min-size", "12"))
    parked_only = "--parked-only" in sys.argv
    show_source = "--source" in sys.argv
    one_wip = int(argval("--wip", "0"), 16)
    one_addr = int(argval("--addr", "0"), 16)

    matched = collect(os.path.join(gl.ROOT, "src"))
    wips = collect(os.path.join(gl.ROOT, "src/wip"))

    by_hash = {}
    for addr, (size, h) in matched.items():
        by_hash.setdefault(h, []).append(addr)

    if one_addr:
        size, h = matched.get(one_addr, (None, None))
        if not h:
            print(f"0x{one_addr:08X}: not a registered src/fn_*.c")
            return
        twins = [a for a in by_hash[h] if a != one_addr]
        print(f"0x{one_addr:08X} ({size}B) {len(twins)} byte-twin(s):")
        for a in twins:
            print(f"  src/fn_{a:08X}.c")
        return

    print(f"matched={len(matched)}  wip={len(wips)}  "
          f"distinct_matched_bytes={len(by_hash)}")
    hits = 0
    for addr in sorted(wips):
        size, h = wips[addr]
        if size < min_size or (one_wip and addr != one_wip):
            continue
        twins = by_hash.get(h)
        if not twins:
            continue
        path = os.path.join(gl.ROOT, "src/wip", f"fn_{addr:08X}.c")
        txt = open(path).read()
        parked = "parked" in txt.lower()
        if parked_only and not parked:
            continue
        hits += 1
        tag = " [parked]" if parked else ""
        print(f"0x{addr:08X} ({size}B){tag} twin of " +
              " ".join(f"0x{a:08X}" for a in twins))
        if show_source:
            print(f"    {gl.ROOT}/src/fn_{twins[0]:08X}.c")
    print(f"-- {hits} draft(s) with a matched byte-twin "
          f"(min-size {min_size})")


main()
