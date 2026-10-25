#!/usr/bin/env python3
"""Sweep the M8.31 callee-return-type flip over the wip pool.

For every file-scope prototype whose result is DISCARDED at all its call
sites in the body, try flipping s32<->void (and s32<->u32) and keep any
strict improvement.  The flip changes the RTL type of the call, which
reorders expand_call's arg setup -- the single highest-yield doc-15 lever
in this project.

usage: rt_sweep.py <addrfile> <lo> <hi>     # prints  file<TAB>+delta<TAB>verdict
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import test_wip_drafts as T  # noqa: E402

# extern [static] <type> NAME( ... );
PROTO = re.compile(
    r"^(extern\s+)?(s32|void|u32|int)\s+([A-Za-z_]\w*)\s*\(([^;{]*)\)\s*;\s*$",
    re.M)
FLIP = {"s32": "void", "void": "s32", "u32": "s32", "int": "s32"}


def result_used(body, name):
    """True if any call to `name(` has its value consumed."""
    for m in re.finditer(rf"\b{re.escape(name)}\s*\(", body):
        # find the matching close paren
        i = m.end() - 1
        depth = 0
        while i < len(body):
            if body[i] == "(":
                depth += 1
            elif body[i] == ")":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        j = i + 1
        while j < len(body) and body[j] in " \t":
            j += 1
        # statement-position call => result discarded
        if j >= len(body) or body[j] in ";\n":
            continue
        return True
    return False


def variants(body):
    protos = PROTO.findall(body)
    seen = set()
    for _ext, ty, name, _args in protos:
        if name in seen or name in ("main",):
            continue
        seen.add(name)
        if result_used(body, name):
            continue
        for newty in {FLIP.get(ty)} - {None}:
            pat = re.compile(
                rf"^(extern\s+)?{ty}\s+{re.escape(name)}\s*\(", re.M)
            out, n = pat.subn(lambda m: f"{m.group(1) or ''}{newty} {name}(", body)
            if n:
                yield f"{name}:{ty}->{newty}", out


def one(fn):
    path = os.path.join(ROOT, "src/wip", fn)
    addr = int(fn[3:-2], 16)
    raw = open(path).read()
    fl = T.gl.draft_flags(raw)
    body = "\n".join(l for l in raw.splitlines()
                     if not l.lstrip().startswith("//"))
    best = (None, 0.0)
    try:
        st0, pct0, _ = T.test_one(addr, body, extra_flags=fl or None)
    except Exception:
        return (fn, "ERR0", 0.0, "")
    for name, out in variants(body):
        try:
            st, pct, _ = T.test_one(addr, out, extra_flags=fl or None)
        except Exception:
            continue
        if pct - pct0 > best[1]:
            best = (name, pct - pct0, st, pct)
    if best[0] is None:
        return (fn, "NONE", 0.0, "")
    return (fn, best[2], best[1], f"{best[0]} -> {best[3]:.2f}")


if __name__ == "__main__":
    files = [l.strip() for l in open(sys.argv[1]) if l.strip()]
    lo, hi = int(sys.argv[2]), int(sys.argv[3])
    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="rt_")
    for fn, v, d, info in map(one, files[lo:hi]):
        if v != "NONE":
            print(f"{v}\t{d:+.2f}\t{fn}\t{info}", flush=True)
