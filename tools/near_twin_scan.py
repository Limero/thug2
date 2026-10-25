#!/usr/bin/env python3
"""Find NEAR byte-twins: matched functions whose retail bytes differ from a wip
draft's in only a handful of instruction words.

`tools/twin_scan.py` finds the 0-diff case (copy the matched source, rename the
function, done). This is the fuzzy version, and it is where most of the wins
actually are: a sibling in the same family routinely differs from a matched one
by one literal, one table offset, one branch polarity, or one operand type.

Every hit is a near-proven recipe, and the diff is small enough to fix by
inspection:

  tools/near_twin_scan.py --max-diff 2            # list candidates
  tools/near_twin_scan.py --addr 0x801A6D80       # one draft, with the
                                                  # differing words printed
  tools/near_twin_scan.py --addr 0x... --apply    # also try the twin's source
                                                  # at the draft's address

`--apply` renames the twin's function in its own source and scores it with the
project scorer, which is the least-effort way to see what is left. CAUTION: the
scorer masks relocation and REL14/REL24 branch fields, so a masked-EXACT result
still has to pass `promote_wip.py`'s linked-DOL check before it can be
registered (and the draft's `range=`/`size=` marker must be right, or the split
itself shifts the DOL).

2026-09-19: 16 drafts promoted EXACT from 16 candidates at max-diff 2 (see
docs/parkings/solved/64-byte-twin-recipe.md).
"""
import os
import sys
from collections import defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl          # noqa: E402
import scan_score as ss          # noqa: E402
import test_wip_drafts as tw     # noqa: E402

WANT = tw._want_sizes()
_CACHE = {}


def words(addr, size):
    key = (addr, size)
    if key not in _CACHE:
        off = gl.t_off + (addr - gl.t_addr)
        b = gl.d[off:off + size]
        _CACHE[key] = [int.from_bytes(b[i:i + 4], "big") for i in range(0, len(b), 4)]
    return _CACHE[key]


def collect(d):
    out = {}
    for f in os.listdir(d):
        if len(f) != len("fn_XXXXXXXX.c") or not f.startswith("fn_"):
            continue
        try:
            addr = int(f[3:11], 16)
        except ValueError:
            continue
        size = WANT.get(addr)
        if size:
            out[addr] = size
    return out


def argval(flag, default=None):
    return sys.argv[sys.argv.index(flag) + 1] if flag in sys.argv else default


def is_branch(w):
    """Direct branch / bclr-bcctr words."""
    return (w >> 26) in (16, 18, 19)


def br_target(base, i, w):
    """Resolve a direct branch word to its absolute target, or None.

    Two copies of the same function at different addresses encode the SAME
    branch with DIFFERENT displacement bits, so a raw word compare flags them as
    noise.  Resolving the target is what separates "same callee, different
    encoding" from "a different callee altogether" — the latter is a real
    difference and the usual reason a renamed twin fails to link (see
    docs/parkings/solved/64-byte-twin-recipe.md).
    """
    if (w >> 26) not in (16, 18):
        return None
    li = w & 0x03FFFFFC
    if li & 0x02000000:
        li -= 0x04000000
    return base + i * 4 + li


def split_diff(addr, maddr, w, m, d):
    """Partition differing word indices into (real, same-target branches)."""
    real, same = [], []
    for i in d:
        tw, tm = br_target(addr, i, w[i]), br_target(maddr, i, m[i])
        if tw is not None and tm == tw:
            same.append(i)
        else:
            real.append(i)
    return real, same


def classify(w, m):
    """Label one differing word pair.

    `imm`     same opcode + same registers, only the immediate/displacement
              differs -> almost always one struct field offset or one data
              label (the twin's source fixes it by editing that offset/name).
    `reg`     same opcode, different register field -> shape is close but a
              home/operand differs (harder, usually a real re-match).
    `op`      different opcode/instruction -> genuinely different code.
    """
    if (w >> 26) != (m >> 26):
        return "op"
    lop, rop = (w >> 26), (w >> 26)
    if lop in (32, 33, 34, 40, 42, 44, 36, 37, 38, 48, 50, 52):   # D-form ld/st
        if ((w >> 16) & 31) != ((m >> 16) & 31):                   # RA differs
            return "reg"
        return "imm"
    if lop == 14:                                                  # addi/addis
        if ((w >> 16) & 31) != ((m >> 16) & 31) or ((w >> 21) & 31) != ((m >> 21) & 31):
            return "reg"
        return "imm"
    if lop == 15:                                                  # lis / addis
        if ((w >> 21) & 31) != ((m >> 21) & 31):
            return "reg"
        return "imm"
    return "op"


def twin_of(addr, size, bysize, real=False):
    w = words(addr, size)
    best = None
    for maddr in bysize.get(size, ()):
        m = words(maddr, size)
        d = [i for i in range(len(w)) if w[i] != m[i]]
        key = split_diff(addr, maddr, w, m, d)[0] if real else d
        if best is None or len(key) < len(best[1]):
            best = (maddr, d, key)
            if not key:
                break
    return best


def main():
    matched = collect(os.path.join(gl.ROOT, "src"))
    wips = collect(os.path.join(gl.ROOT, "src/wip"))
    bysize = defaultdict(list)
    for a, s in matched.items():
        bysize[s].append(a)

    one = int(argval("--addr", "0"), 16)
    if one:
        size = matched.get(one) or wips.get(one)
        if not size:
            print(f"0x{one:08X}: not a known function")
            return
        found = twin_of(one, size, bysize)
        if found is None:
            print(f"0x{one:08X}: no matched function of the same size")
            return
        maddr, diff, _ = found
        w = words(one, size)
        m = words(maddr, size)
        # always classify for display; only the twin SELECTION depends on --real
        real, same = split_diff(one, maddr, w, m, diff)
        kinds = {i: classify(w[i], m[i]) for i in real}
        tally = {k: sum(1 for v in kinds.values() if v == k) for k in ("imm", "reg", "op")}
        print(f"0x{one:08X} ({size}B) closest: src/fn_{maddr:08X}.c "
              f"({len(real)} real / {len(same)} same-target branch word(s) differ)"
              + (f"  [{tally['imm']} imm / {tally['reg']} reg / {tally['op']} op]"
                 if real else ""))
        for i in diff:
            tw, tm = br_target(one, i, w[i]), br_target(maddr, i, m[i])
            if tw is None and tm is None:
                note = ""
            elif tw == tm:
                note = f"(branch -> 0x{tw:08X}, same target)"
            else:
                note = (f"(branch -> want {tw and format(tw, '#010x')} "
                        f"got {tm and format(tm, '#010x')})")
            kind = f"[{kinds[i]}] " if i in kinds else ""
            print(f"  word {i:3d}  got {m[i]:08X}  want {w[i]:08X} {kind}{note}")
        if "--apply" in sys.argv:
            import re
            path = os.path.join(gl.ROOT, "src", f"fn_{maddr:08X}.c")
            txt = open(path).read()
            body = "\n".join(l for l in txt.splitlines()
                             if not l.startswith("//")
                             and "types.h" not in l)
            body = re.sub(rf"\bfn_{maddr:08X}\b", f"fn_{one:08X}", body)
            print("  apply:", ss.score(one, body, None))
        return

    max_diff = int(argval("--max-diff", "4"))
    min_words = int(argval("--min-words", "12"))
    show_source = "--source" in sys.argv
    use_real = "--real" in sys.argv
    # only rank/report on real diffs; branch-displacement-only siblings are
    # reported too (a 0-word real diff means "already mask-exact, needs the
    # link/DOL check rather than a rewrite").
    rank = 1 if use_real else 0

    report = []
    for waddr in sorted(wips):
        size = wips[waddr]
        if size // 4 < min_words:
            continue
        found = twin_of(waddr, size, bysize, real=use_real)
        maddr, diff, key = found if found else (None, [0] * (max_diff + 1), [])
        if maddr is None or len(key) > max_diff:
            continue
        if "--imm-only" in sys.argv:
            w, m = words(waddr, size), words(maddr, size)
            real, _ = split_diff(waddr, maddr, w, m, diff)
            if any(classify(w[i], m[i]) != "imm" for i in real):
                continue
        report.append((len(key), len(diff), waddr, maddr, size, diff))

    report.sort()
    print(f"wips with a near-twin within {max_diff} words: {len(report)}")
    for d, nd, w, m, size, diff in report:
        where = " ".join(f"{i}" for i in diff)
        ws, ms = words(w, size), words(m, size)
        real, _ = split_diff(w, m, ws, ms, diff)
        tally = {k: sum(1 for i in real if classify(ws[i], ms[i]) == k)
                 for k in ("imm", "reg", "op")}
        print(f"  {d} real / {nd} raw  wip 0x{w:08X} <- src/fn_{m:08X}.c  "
              f"({size}B)  {tally['imm']}imm/{tally['reg']}reg/{tally['op']}op  words {where}")
        if show_source:
            print(f"      {gl.ROOT}/src/fn_{m:08X}.c")
    hist = defaultdict(int)
    for d, *_ in report:
        hist[d] += 1
    print("real-diff histogram:", dict(sorted(hist.items())))


main()
