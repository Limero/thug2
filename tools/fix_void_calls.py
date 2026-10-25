#!/usr/bin/env python3
"""Fix drafts that call a promoted `(void)` function WITH arguments.

m2c guessed an arity for every callee; when the real function is
`f(void)` the draft still passes anything m2c invented.  That phantom
argument forces the compiler to materialise a value (often into a
callee-saved register), which shifts the whole register role set and
looks like unfixable regalloc noise.

This scans every non-stub draft, finds call sites whose callee's real
source prototype is zero-argument, rewrites the declaration + call to
the real arity, and scores the result.  Writes only when it improves.

Usage:
  tools/venv/bin/python tools/fix_void_calls.py [--file addrs.txt] [--write]
"""
import glob
import os
import re
import sys
from multiprocessing import Pool

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from test_wip_drafts import test_one

DECL = re.compile(r"^([ \t]*)((?:static\s+)?[\w \t\*]*?)\b(fn_[0-9A-F]{8})\s*\(([^;{}]*)\)\s*;", re.M)
SVAR = re.compile(r"^[ \t]*[A-Za-z_]\w*(?:\s*\*)?\s+(fn_[0-9A-F]{8})\s*\(", re.M)
DECL_G = re.compile(r"^([ \t]*)((?:static\s+)?[\w \t\*]*?)\b(fn_[0-9A-F]{8})\s*\(([^;{}]*)\)\s*;", re.M)


def _init():
    os.environ["LEAF_TMPDIR"] = "/tmp/leaf/vc%d" % os.getpid()


def _score(args):
    idx, addr, body = args
    try:
        _, pct, _ = test_one(addr, body)
    except Exception:
        return idx, 0.0
    return idx, pct


def zero_arg_promoted(name):
    """True iff src/<name>.c defines it with an empty/void parameter list."""
    p = os.path.join(ROOT, "src/%s.c" % name)
    if not os.path.exists(p):
        return None
    m = re.search(r"^\w[\w \t\*]*?\b%s\(([^)]*)\)\s*\{" % name, open(p).read(), re.M)
    if not m:
        return None
    body = m.group(1).strip()
    return body == "" or body == "void"


def calls_with_args(text, name, skip_span=None):
    out = []
    for m in re.finditer(r"\b%s\s*\(" % name, text):
        if skip_span and skip_span[0] <= m.start() < skip_span[1]:
            continue
        i, depth, args, cur = m.end(), 1, [], ""
        while i < len(text) and depth:
            ch = text[i]
            if ch in "([":
                depth += 1
            elif ch in ")]":
                depth -= 1
                if depth == 0:
                    break
            if depth == 1 and ch == ",":
                args.append(cur)
                cur = ""
            else:
                cur += ch
            i += 1
        if cur.strip():
            args.append(cur)
        if args:
            out.append((m.start(), i + 1))
    return out


COMMENT = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)


def comment_spans(text):
    return [(m.start(), m.end()) for m in COMMENT.finditer(text)]


def in_code(pos, spans):
    for s, e in spans:
        if s <= pos < e:
            return False
    return True


def overlaps(a, b, spans):
    return any(a < e and s < b for s, e in spans)


def strip(text):
    return "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()


def fix(text):
    """Return a new draft text with zero-arg callees called with no args."""
    names = set()
    spans = comment_spans(text)
    for m in DECL.finditer(text):
        if not in_code(m.start(), spans):
            continue
        if zero_arg_promoted(m.group(3)):
            if calls_with_args(text, m.group(3), (m.start(), m.end())):
                names.add(m.group(3))
    if not names:
        return None
    spans = comment_spans(text)
    edits = []  # (start, end, replacement)
    decl_spans = []
    for name in names:
        for m in DECL_G.finditer(text):
            if m.group(3) == name:
                edits.append((m.start(), m.end(), "%s%s%s(void);" % (m.group(1), m.group(2), name)))
                decl_spans.append((m.start(), m.end()))
                break
    for name in names:
        for s, e in calls_with_args(text, name):
            if not in_code(s, spans):
                continue
            if any(ds <= s < de for ds, de in decl_spans):
                continue  # the declaration's own parameter list
            open_paren = text.index("(", s)
            if overlaps(open_paren + 1, e, spans):
                continue
            edits.append((open_paren + 1, e - 1, ""))
    # apply right-to-left so earlier offsets stay valid; never touch comments
    edits.sort(key=lambda t: -t[0])
    out = text
    last_start = len(text) + 1
    for s, e, rep in edits:
        if s >= last_start:
            continue  # overlapping edit already applied
        out = out[:s] + rep + out[e:]
        last_start = s
    return out


def main():
    args = sys.argv[1:]
    write = "--write" in args
    if write:
        args.remove("--write")
    if args[:1] == ["--file"]:
        addrs = []
        for l in open(args[1]):
            l = l.strip()
            if l:
                addrs.append(int(l, 16))
        files = [os.path.join(ROOT, "src/wip/fn_%08X.c" % a) for a in addrs]
    else:
        files = sorted(glob.glob(os.path.join(ROOT, "src/wip/fn_*.c")))
    work = []
    for f in files:
        t = open(f).read()
        if "family=stub" in t:
            continue
        fx = fix(t)
        if fx is None:
            continue
        work.append((f, t, fx))
    print("candidates:", len(work), file=sys.stderr)
    with Pool(8, initializer=_init) as pool:
        for f, t, fx in work:
            addr = int(os.path.basename(f)[3:11], 16)
            (i0, p0), (i1, p1) = pool.map(_score, [(0, addr, strip(t)), (1, addr, strip(fx))])
            if p1 > p0 + 1e-9:
                print("%08X %.1f%% -> %.1f%%%s" % (addr, p0, p1, "  <<<<" if p1 > 99.6 else ""), flush=True)
                if write:
                    body_lines = fx.rstrip("\n").splitlines()
                    inset = 0
                    while inset < len(body_lines) and body_lines[inset].startswith("//"):
                        inset += 1
                    note = ("// VOID-ARITY FIX 2026-09-11 (tools/fix_void_calls.py): callee is "
                            "`(void)` in src/ -- phantom argument removed; %.1f%% -> %.1f%%."
                            % (p0, p1))
                    open(f, "w").write("\n".join(body_lines[:inset] + [note]
                                                 + body_lines[inset:]) + "\n")


if __name__ == "__main__":
    main()
