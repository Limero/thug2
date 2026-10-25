#!/usr/bin/env python3
"""Hill-climb the *source order* of a contiguous statement block in a draft.

ngccc's scheduler reorders independent statements, so for many drafts the
DOL's order is what the compiler emits for some *other* source order.
`store_order_search.py` only handles `base->unkNNN = ...` runs; this tool
permutes an arbitrary contiguous block, which is what the byte-map resets,
float-store groups and multi-store tails need.

Moves per round: all pairwise swaps, all single-element moves, all segment
reversals, and all 3-cycles; the best improvement is applied and the round
repeats.  Every candidate is scored through test_wip_drafts.test_one, so the
result is directly comparable with `tools/my_diff.py`.

Usage:
  tools/venv/bin/python tools/stmt_perm_search.py 0x80244924 \
        --from '0x7\\) = 0xFF' --to 'temp_r9 \\+ \\(s32\\)0x4\\) = 0' [--write]
  # --from / --to are regexes matched against the *body* lines; the block is
  # the inclusive line range between the first line matching --from and the
  # first following line matching --to.
"""
import os
import re
import sys
from multiprocessing import Pool

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import gen_leaves as gl
from test_wip_drafts import test_one

MAX_CANDS = 2500


def draft_flags(text):
    """Per-object flags from a WIP header, mirroring promote_wip.draft_flags().

    strip() drops the `// FLAG:` line, so without this the search scores under
    DEFAULT flags -- wrong for any draft whose header carries `-mps-float`,
    `-fno-schedule-insns`, `-fno-gcse`, ... and --write persists that body.
    """
    flags = []
    for line in text.splitlines()[:120]:
        m = re.match(r"^//\s*(?:FLAG|extra_cflags):\s*(.+)$", line)
        if m:
            flags.extend(t for t in m.group(1).replace(",", " ").split()
                         if gl.FLAG_TOKEN_RE.match(t))
    if ("__ps_t" in text or "__builtin_ps_" in text) and "-mps-float" not in flags:
        flags.append("-mps-float")
    return list(dict.fromkeys(flags))


def _init():
    # per-process scratch dir: workers sharing one LEAF_TMPDIR corrupt each
    # other's leaf.c/leaf.o and silently produce garbage scores
    os.environ["LEAF_TMPDIR"] = "/tmp/leaf/perm%d" % os.getpid()


def _score(args):
    idx, addr, body, flags = args
    try:
        _, pct, _ = test_one(addr, body, flags or None)
    except Exception:
        return idx, 0.0
    return idx, pct


def strip(text):
    return "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()


def build(lines, start, end, order):
    nl = list(lines)
    nl[start:end + 1] = [lines[start + i] for i in order]
    return "\n".join(nl) + "\n"


def moves(cur):
    """All neighbour permutations of `cur` worth trying."""
    n = len(cur)
    out = []
    for i in range(n):
        for j in range(i + 1, n):
            o = list(cur)
            o[i], o[j] = o[j], o[i]
            out.append(tuple(o))
    for k in range(n):
        for tgt in range(n):
            if tgt != k:
                o = list(cur)
                o.insert(tgt, o.pop(k))
                out.append(tuple(o))
    for i in range(n):
        for j in range(i + 2, n + 1):
            o = list(cur)
            o[i:j] = o[i:j][::-1]
            out.append(tuple(o))
    for i in range(n):
        for j in range(n):
            for k in range(n):
                if len({i, j, k}) == 3:
                    o = list(cur)
                    o[i], o[j], o[k] = o[k], o[i], o[j]
                    out.append(tuple(o))
    return list(dict.fromkeys(out))


def main():
    args = sys.argv[1:]
    write = "--write" in args
    if write:
        args.remove("--write")
    addr = int(args[0], 0)
    m_from = args[args.index("--from") + 1]
    m_to = args[args.index("--to") + 1]
    path = os.path.join(ROOT, "src/wip/fn_%08X.c" % addr)
    text = open(path).read()
    flags = draft_flags(text)
    lines = text.splitlines()
    start = next(i for i, l in enumerate(lines) if re.search(m_from, l))
    end = next(i for i, l in enumerate(lines[start:], start) if re.search(m_to, l))
    block = lines[start:end + 1]
    print("block lines %d..%d (%d)" % (start, end, len(block)))
    if len(block) > 13:
        print("block too large to permute exhaustively", file=sys.stderr)
        return
    cur = tuple(range(len(block)))
    with Pool(8, initializer=_init) as pool:
        best = _score((0, addr, strip(build(lines, start, end, cur)), flags))[1]
        print("start %.2f%%" % best)
        while True:
            cands = moves(cur)
            if len(cands) > MAX_CANDS:
                step = len(cands) / float(MAX_CANDS)
                cands = [cands[int(i * step)] for i in range(MAX_CANDS)]
            res = pool.map(_score, [(i, addr, strip(build(lines, start, end, c)), flags)
                                    for i, c in enumerate(cands)])
            res.sort(key=lambda r: -r[1])
            idx, pct = res[0]
            if pct <= best + 1e-9:
                break
            cur, best = cands[idx], pct
            print("  %.2f%%  %s" % (best, cur), flush=True)
        body = build(lines, start, end, cur)
    if write and cur != tuple(range(len(block))):
        note = ("// ORDERED 2026-09-11 (tools/stmt_perm_search.py): statement block "
                "lines %d..%d re-ordered; score now %.1f%%." % (start + 1, end + 1, best))
        bl = body.rstrip("\n").splitlines()
        inset = 0
        while inset < len(bl) and bl[inset].startswith("//"):
            inset += 1
        open(path, "w").write("\n".join(bl[:inset] + [note] + bl[inset:]) + "\n")
        print("written")


if __name__ == "__main__":
    main()
