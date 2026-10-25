#!/usr/bin/env python3
"""Greedy search over the *source order* of store blocks in a draft body.

ngccc reorders independent stores, so for many drafts the DOL's order is what
the compiler emits for some *different* source order.  In practice the winning
arrangement is almost always plain ascending or descending field order (the
DOL order is the compiler's schedule, not the original source).  This tool
re-runs that search on every run of consecutive `base->unk0xNN = ...;` lines
and keeps whatever improves the masked-match score.

Usage:
  tools/venv/bin/python tools/store_order_search.py 0x8005D380 [more addrs]
  tools/venv/bin/python tools/store_order_search.py --file /tmp/cands.txt [rounds]
  ... --write   persist improvements back into src/wip (add --note to tag them)
"""
import os
import re
import sys
from multiprocessing import Pool

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import gen_leaves as gl
from test_wip_drafts import test_one

ASSIGN = re.compile(r"^(\s*)(\w+(?:->\w+)*(?:\[\w+\])?)->unk0x([0-9A-Fa-f]+)\s*=")
MIN_RUN = 3


def _init():
    os.environ["LEAF_TMPDIR"] = "/tmp/leaf/sos%d" % os.getpid()


def draft_flags(text):
    """Per-object flags from a WIP header, mirroring promote_wip.draft_flags().

    strip() drops the `// FLAG:` line, so without this the search would score the
    body under DEFAULT flags -- for any draft whose header carries
    `-mps-float`, `-fno-schedule-insns`, `-fno-gcse`, ... the baseline is then a
    completely different program, and --write persists that wrong body.
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


SIMPLE = re.compile(r"^(\s*)((?:\w+->|\*?\w+\[[^]]*\]|\w+(?:\.\w+)*|\(\s*\w+\s*\*\s*\))\s*[\w\[\]\.\-\>\*\+\s]*?)\s*=\s*[^=;]+;\s*$")
OFFSET = re.compile(r"(?:unk0x|\+\s*\(?(?:s32\)?\s*)?0x|\[)\s*([0-9A-Fa-f]+)")


def find_runs(lines):
    """Maximal runs of >=MIN_RUN stores.

    Two detectors, unioned:
      (a) the original `base->unkNNN = ...` runs (same base, same statement), and
      (b) any run of >=2 consecutive single-line assignments at the SAME indent
          (independent stores the scheduler may reorder, whatever spelling m2c
          chose: `*(u8 *)((char *)p + 0x7) = 0xFF;`, `arr[i] = 0;`, ...).
    """
    runs = []
    i = 0
    while i < len(lines):
        m = ASSIGN.match(lines[i])
        if not m:
            i += 1
            continue
        base, j, group = m.group(2), i, []
        while j < len(lines):
            mm = ASSIGN.match(lines[j])
            if not mm or mm.group(2) != base:
                break
            group.append(j)
            j += 1
        if len(group) >= MIN_RUN:
            runs.append(group)
        i = j if j > i else i + 1
    i = 0
    while i < len(lines):
        m = SIMPLE.match(lines[i])
        if not m:
            i += 1
            continue
        indent, j, group = m.group(1), i, []
        while j < len(lines):
            mm = SIMPLE.match(lines[j])
            if not mm or mm.group(1) != indent:
                break
            group.append(j)
            j += 1
        if len(group) >= 2:
            runs.append(group)
        i = j if j > i else i + 1
    return runs


def offset_of(line):
    m = OFFSET.search(line)
    return int(m.group(1), 16) if m else None


def variants(lines, runs):
    """One candidate per (run, asc|desc), holding all other runs unchanged."""
    out = []
    for gi, g in enumerate(runs):
        nl = list(lines)
        vals = [lines[k] for k in g]
        if vals[::-1] != vals:
            nl2 = list(lines)
            for k, v in zip(g, vals[::-1]):
                nl2[k] = v
            out.append((gi, "rev", "\n".join(nl2) + "\n"))
        offs = [offset_of(lines[k]) for k in g]
        if all(o is not None for o in offs) and len(set(offs)) == len(offs):
            for direction in ("asc", "desc"):
                order = sorted(range(len(g)), key=lambda t: offs[t])
                if direction == "desc":
                    order = list(reversed(order))
                vals2 = [lines[g[t]] for t in order]
                if vals2 == vals:
                    continue
                nl3 = list(lines)
                for k, v in zip(g, vals2):
                    nl3[k] = v
                out.append((gi, direction, "\n".join(nl3) + "\n"))
    return out


def search(addr, rounds=4, path=None):
    path = path or os.path.join(ROOT, "src/wip/fn_%08X.c" % addr)
    text = open(path).read()
    flags = draft_flags(text)
    lines = text.splitlines()
    runs = find_runs(lines)
    if not runs:
        return None
    with Pool(8, initializer=_init) as pool:
        cur_lines = list(lines)
        cur = _score((0, addr, strip("\n".join(cur_lines)), flags))[1]
        best_hist = []
        for _ in range(rounds):
            cands = variants(cur_lines, find_runs(cur_lines))
            if not cands:
                break
            res = pool.map(_score, [(i, addr, strip(c[2]), flags) for i, c in enumerate(cands)])
            res.sort(key=lambda r: -r[1])
            idx, pct = res[0]
            if pct > cur + 1e-9:
                gi, direction, body = cands[idx]
                cur_lines = body.rstrip("\n").splitlines()
                cur = pct
                best_hist.append("[%d]%s->%.1f%%" % (gi, direction, pct))
            else:
                break
    return cur, best_hist, "\n".join(cur_lines) + "\n"


def main():
    args = sys.argv[1:]
    write = "--write" in args
    if write:
        args.remove("--write")
    rounds = 4
    if args and args[-1].isdigit():
        rounds = int(args.pop())
    if args[:1] == ["--file"]:
        addrs = []
        for l in open(args[1]):
            l = l.strip()
            if not l:
                continue
            tok = l.split()[0] if not l.startswith("0x") else l
            addrs.append(int(tok, 16))
    else:
        addrs = [int(a, 0) for a in args]
    for addr in addrs:
        path = os.path.join(ROOT, "src/wip/fn_%08X.c" % addr)
        try:
            orig = open(path).read()
            r = search(addr, rounds, path)
        except Exception as e:
            print("%08X ERR %s" % (addr, str(e)[:60]))
            continue
        if r is None:
            continue
        pct, hist, body = r
        if not hist:
            continue
        print("%08X %.1f%%  %s" % (addr, pct, " ".join(hist)))
        if write:
            note = ("// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment "
                    "block(s) re-ordered (reversed / ascending / descending); score now "
                    "%.1f%% (%s)." % (pct, " ".join(hist)))
            body_lines = body.rstrip("\n").splitlines()
            inset = 0
            while inset < len(body_lines) and body_lines[inset].startswith("//"):
                inset += 1
            open(path, "w").write("\n".join(body_lines[:inset] + [note]
                                           + body_lines[inset:]) + "\n")


if __name__ == "__main__":
    main()
