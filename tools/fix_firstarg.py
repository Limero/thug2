#!/usr/bin/env python3
"""Batch A/B for the dropped-first-arg m2c class.

For each (draft, callee) candidate: insert `arg0` as the callee's first call
arg, sync the draft's prototype to the callee's promoted signature, score
with my_diff, and keep the change only if the draft improves.
"""
import json
import os
import re
import subprocess
import sys

SCORE = re.compile(r"score: (\d+)/(\d+) = ([\d.]+)%")


def sig_of(name):
    p = "src/%s.c" % name
    if not os.path.exists(p):
        return None
    t = open(p).read()
    m = re.search(r"^(\w[\w \t\*]*?)\s*\b%s\(([^)]*)\)\s*\{" % name, t, re.M)
    if not m:
        return None
    ret = m.group(1).strip()
    params = []
    for a in m.group(2).split(","):
        a = a.strip()
        if not a:
            continue
        a = re.sub(r"\s*\b\w+\s*$", "", a).strip()  # drop param name, keep type
        params.append(a or "s32")
    return "%s %s(%s);" % (ret, name, ", ".join(params))


def arity_of(name):
    p = "src/%s.c" % name
    if not os.path.exists(p):
        return None
    t = open(p).read()
    m = re.search(r"\b%s\(([^)]*)\)\s*\{" % name, t)
    if not m:
        return None
    return len([a for a in m.group(1).split(",") if a.strip()])


def score(addr):
    r = subprocess.run(["tools/venv/bin/python", "tools/my_diff.py", "0x" + addr],
                       capture_output=True, text=True, timeout=240)
    m = SCORE.search(r.stdout)
    return (int(m.group(1)), int(m.group(2))) if m else None


def patch(t, callee, proto):
    if proto is None:
        return t, False
    # replace an existing prototype/decl for callee
    pat = re.compile(r"[^\n]*\b%s\s*\([^;)]*\);" % callee)
    if pat.search(t):
        t2 = pat.sub(proto, t, count=1)
    else:
        anchor = '#include "structs.h"'
        if anchor not in t:
            anchor = '#include "types.h"'
        if anchor not in t:
            return t, False
        t2 = t.replace(anchor, anchor + "\n" + proto, 1)
    return t2, (t2 != t)


def main():
    cands = [tuple(x) for x in json.load(open("/tmp/firstarg_cands.json"))]
    only = set(sys.argv[1:])
    results = []
    for draft, callee in cands:
        if only and draft not in only:
            continue
        if arity_of(callee) is None:
            continue
        addr = draft.replace("fn_", "")
        p = "src/wip/%s.c" % draft
        t = open(p).read()
        body_off = t.find("#include")
        if body_off < 0:
            continue
        head, body = t[:body_off], t[body_off:]
        # first plain call site (no nested parens in args)
        m = re.search(r"\b%s\(([^()]*)\);" % callee, body)
        if not m:
            continue
        base = score(addr)
        if base is None or base[1] == 0 or base[0] / base[1] < 0.5:
            continue  # corrupted bodies need re-matches, skip
        # only drafts whose own first param is literally `arg0` (insert-ready)
        fm = re.search(r"\b%s\(\w+ \*?\s*arg0[,)]" % draft, body)
        if not fm:
            continue
        body2 = body[:m.start()] + "%s(arg0, %s);" % (callee, m.group(1)) + body[m.end():]
        proto = sig_of(callee)
        body2, ok = patch(body2, callee, proto)
        if not ok:
            continue
        open(p, "w").write(head + body2)
        new = score(addr)
        if new and new[0] / new[1] > base[0] / base[1]:
            print("%s %s: %d/%d -> %d/%d  KEEP" % (addr, callee, base[0], base[1], new[0], new[1]))
            results.append((addr, callee, base, new))
        else:
            open(p, "w").write(t)
            print("%s %s: %d/%d -> %s  revert" % (addr, callee, base[0], base[1], new))
    print("KEPT:", len(results))


if __name__ == "__main__":
    main()
