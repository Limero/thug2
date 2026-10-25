#!/usr/bin/env python3
"""Callee-ARITY sweep: the hidden-leading-arg / dead-arg family (AGENTS.md
§6e-32, §6o-99, §6t-3, §6w-119, §6y-132, §6ab-136).

m2c guesses a callee's parameter list from the registers it SEES used, and
it systematically drops a leading passthrough arg, drops a trailing dead
arg, or invents a phantom one.  Every one of those shifts the whole
expand_call argument setup, so a single extra/missing parameter often
flips a NEAR draft to EXACT.

For every file-scope prototype in a draft, try:
  * widen  by one  (append `, s32`)      - the arg rides in the next GPR
  * narrow by one  (drop the last param) - the arg is dead / not passed
  * narrow by one LEADING param          - m2c invented a leading arg
and keep the best strict improvement.

usage: arity_sweep.py <file-list> [lo] [hi]
prints: verdict<TAB>delta<TAB>file<TAB>info
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import test_wip_drafts as T  # noqa: E402

# a file-scope prototype: [extern] [static] type NAME(params);
PROTO = re.compile(
    r"^(extern\s+|static\s+)?([A-Za-z_][\w\s\*]*?)\b([A-Za-z_]\w*)\s*\(([^;{()]*)\)\s*;\s*$",
    re.M)
SKIP_TYPES = {"return", "if", "for", "while", "switch"}


def split_params(s):
    s = s.strip()
    if s == "" or s == "void":
        return []
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def variants(body):
    seen = set()
    for m in PROTO.finditer(body):
        ext, ty, name, params = m.group(1), m.group(2).strip(), m.group(3), m.group(4)
        if ty.split()[0] in SKIP_TYPES or name in seen:
            continue
        seen.add(name)
        plist = split_params(params)
        pat = re.compile(
            r"^" + re.escape(m.group(0).rstrip()) + r"\s*$", re.M)
        forms = []
        if plist:
            forms.append((f"{name}: drop-last",
                          ", ".join(plist[:-1]) or "void"))
            forms.append((f"{name}: drop-first",
                          ", ".join(plist[1:]) or "void"))
        forms.append((f"{name}: +arg", (", ".join(plist) + ", s32")
                      if plist else "s32"))
        for label, newparams in forms:
            new = m.group(0)
            new = new.replace("(" + params + ")", "(" + newparams + ")", 1)
            out, n = pat.subn(lambda _m: new, body)
            if n:
                yield label, out


def one(fn):
    path = os.path.join(ROOT, "src/wip", fn)
    addr = int(fn[3:-2], 16)
    raw = open(path).read()
    fl = T.gl.draft_flags(raw)
    body = "\n".join(l for l in raw.splitlines()
                     if not l.lstrip().startswith("//"))
    try:
        st0, pct0, _ = T.test_one(addr, body, extra_flags=fl or None)
    except Exception:  # noqa: BLE001
        return (fn, "ERR0", 0.0, "")
    best = (None, 0.0, "")
    for label, out in variants(body):
        try:
            st, pct, _ = T.test_one(addr, out, extra_flags=fl or None)
        except Exception:  # noqa: BLE001
            continue
        if pct - pct0 > best[1] + 1e-9:
            best = (label, pct - pct0, st, pct)
    if best[0] is None:
        return (fn, "NONE", 0.0, "")
    return (fn, best[2], best[1], f"{best[0]} -> {best[3]:.2f}")


if __name__ == "__main__":
    files = [l.strip() for l in open(sys.argv[1]) if l.strip()]
    lo = int(sys.argv[2]) if len(sys.argv) > 2 else 0
    hi = int(sys.argv[3]) if len(sys.argv) > 3 else len(files)
    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="ar_")
    for fn, v, d, info in map(one, files[lo:hi]):
        if v != "NONE":
            print(f"{v}\t{d:+.2f}\t{fn}\t{info}", flush=True)
