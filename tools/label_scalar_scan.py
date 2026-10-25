#!/usr/bin/env python3
"""Try declaring a `char[]` label as its real scalar object type.

m2c always emits `extern char lbl_X[];` for symbols it only knows as
addresses.  When the body then reads a *scalar* out of that address with

    *(s32 *)&lbl_X        (or u32 / f32 ... )

ngccc has to materialise the whole address (`lis` + `addi`) and load with
displacement 0, and the extra address computation perturbs scheduling (the
load sinks below unrelated stores).  The DOL often instead holds a real
scalar object declared with its own type, which folds to `lis rT, hi` +
`lwz rD, lo(rT)` -- found on fn_800A3C50 (75.9% -> EXACT).

This tool A/Bs that rewrite: for every label the draft uses *only* through
`*(T *)&lbl_X`, it emits `extern T lbl_X;` with a bare `lbl_X` use and keeps
the best.  Winning bodies go to /tmp/lblscalar_<ADDR>.c.

Usage: printf 'ADDR\n...' | tools/venv/bin/python tools/label_scalar_scan.py
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
import scan_score  # noqa: E402

SCALARS = ("s32", "u32", "f32", "s16", "u16")


def split_body(text):
    lines = [l for l in text.splitlines()
             if not l.startswith("//") and "types.h" not in l]
    return "\n".join(lines).strip()


def decl_re(label):
    return re.compile(r"^extern\s+char\s+%s\[\]\s*;\s*$" % re.escape(label), re.M)


def candidates(body):
    """Yield (label, type) for labels used only via `*(T *)&label`."""
    labels = re.findall(r"^extern\s+char\s+(\w+)\[\]\s*;", body, re.M)
    for label in dict.fromkeys(labels):
        decls = len(re.findall(r"extern\s+char\s+%s\[\]\s*;" % re.escape(label), body))
        derefs = re.findall(
            r"\*\(\s*(%s)\s*\*\)\s*&\s*%s\b" % ("|".join(SCALARS), re.escape(label)),
            body)
        total = len(re.findall(r"\b%s\b" % re.escape(label), body))
        if derefs and total == decls + len(derefs):
            yield label, max(set(derefs), key=derefs.count)


def variant(body, label, t):
    deref = re.compile(r"\*\(\s*%s\s*\*\)\s*&\s*%s\b" % (re.escape(t), re.escape(label)))
    out = decl_re(label).sub("extern %s %s;" % (t, label), body, count=1)
    out, n = deref.subn(label, out)
    if n == 0 or "&%s" % label in out:
        return None
    return out


def main():
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 16)
        path = "src/wip/fn_%08X.c" % addr
        if not os.path.exists(path):
            continue
        text = open(path).read()
        body = split_body(text)
        flags = gl.draft_flags(text) or None
        base = scan_score.pct(addr, body, flags)
        best = None
        for label, t in candidates(body):
            v = variant(body, label, t)
            if v is None:
                continue
            s2, sc = scan_score.score(addr, v, flags)
            mark = "BETTER" if sc > base + 0.001 else ("same" if sc >= base - 0.001 else "worse")
            print("%08X %-4s %-16s %5.1f -> %5.1f  %s" % (addr, t, label, base, sc, mark))
            sys.stdout.flush()
            if sc > base and (best is None or sc > best[3]):
                best = (label, t, v, sc, s2)
        if best:
            label, t, v, sc, s2 = best
            open("/tmp/lblscalar_%08X.c" % addr, "w").write(v + "\n")


if __name__ == "__main__":
    main()
