#!/usr/bin/env python3
"""Stale-prototype sweep: a draft that DECLARES a callee with the wrong
signature is invisible to tools/protoscale.py, which only splices prototypes for
callees that have NO declaration at all (doc-56).

The signature that matters most is the **return type**: the RTL of a call to a
value-returning function is not the RTL of a call to a void one, and ngccc
schedules the caller's argument setup differently for the two.  fn_800A64F0 was
stuck at 92.1% on `mr r3,r31` one slot late purely because the draft declared
`s32 fn_801286D0(...)` as `void`; the promoted src/fn_8002E1CC.c already had the
real `s32` return type, and using it was 100%.

This tool re-reads the REAL signature out of the promoted definition in
src/<name>.c (or libs/<name>.c, same source protoscale.py uses) and rewrites
every draft declaration that disagrees with it, in place, keeping only strict
score improvements.

Usage: protomismatch.py <list-of-draft-paths> [nproc]
Winners are written to /tmp/protomm/fn_XXXXXXXX.c and printed as
  BETTER 0xADDR pct -> pct  out  <which declarations changed>
"""
import os
import re
import sys

sys.path.insert(0, os.path.abspath("tools"))
import gen_leaves as gl  # noqa: E402
from protoscale import real_sig  # noqa: E402
from test_wip_drafts import test_one  # noqa: E402

# `extern` type name(args);  — the type may contain spaces/`*` but no semantics
DECL = re.compile(
    r"^(?P<ws>[ \t]*)(?P<ext>extern[ \t]+)?(?P<ret>[A-Za-z_][\w \t]*?[ \t]*\*?)"
    r"(?P<name>[A-Za-z_]\w*)[ \t]*\((?P<args>[^;{}]*)\)[ \t]*;[ \t]*$", re.M)


def norm(s):
    return re.sub(r"\s+", " ", s.replace(" ", ""))


def sig_of(ret, args):
    return f"{ret.strip()} {norm(args)}"


def candidates(body):
    """[(match, old_text, new_text, name)] for every declaration that disagrees."""
    out = []
    for m in DECL.finditer(body):
        name = m.group("name")
        rs = real_sig(name)
        if not rs:
            continue
        ret, params = rs
        old = m.group(0).strip()
        new = f"{ret} {name}({params});"
        if norm(old) == norm(new):
            continue
        out.append((m, old, new, name))
    return out


def rewrite(body, hits):
    """Replace the disagreeing declarations; keep each at its original indent."""
    out = body
    for m, old, new, _name in sorted(hits, key=lambda h: -h[0].start()):
        out = out[:m.start()] + new + out[m.end():]
    return out


def work(path):
    os.environ["LEAF_TMPDIR"] = "/tmp/leafmm%d" % (os.getpid() % 24)
    if not os.path.exists(path):
        return None
    addr = int(os.path.basename(path)[3:11], 16)
    text = open(path).read()
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    flags = gl.draft_flags(text) or None
    hits = candidates(body)
    if not hits:
        return None
    try:
        s0, p0, _ = test_one(addr, body, flags)
    except Exception:
        return None
    if s0 == "EXACT":
        return None
    overall = (p0, None, [])
    # all-at-once, then each declaration on its own (one stale decl can mask another)
    for subset in [hits] + [[h] for h in hits]:
        cand = rewrite(body, subset)
        if cand == body:
            continue
        try:
            _s1, p1, _ = test_one(addr, cand, flags)
        except Exception:
            continue
        if p1 > overall[0] + 0.05:
            overall = (p1, cand, [h[3] for h in subset])
    if overall[1] is None:
        return None
    os.makedirs("/tmp/protomm", exist_ok=True)
    out = "/tmp/protomm/fn_%08X.c" % addr
    open(out, "w").write("// protomismatch winner (stale prototype)\n" + overall[1] + "\n")
    return ("BETTER", p0, overall[0], addr, out, ",".join(overall[2]))


if __name__ == "__main__":
    files = [l.strip() for l in open(sys.argv[1]) if l.strip()]
    n = int(sys.argv[2]) if len(sys.argv) > 2 else 8
    from multiprocessing import Pool
    rows = []
    with Pool(n) as pool:
        for r in pool.imap_unordered(work, files, chunksize=4):
            if r:
                rows.append(r)
    rows.sort(key=lambda r: -r[2])
    for r in rows:
        print("BETTER 0x%08X %.1f -> %.1f  %s  [%s]" % (r[3], r[1], r[2], r[4], r[5]))
    print("scanned %d, hits %d" % (len(files), len(rows)))
