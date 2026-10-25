#!/usr/bin/env python3
"""doc-58: m2c reads a *label address* as an extra call argument.

For `arg0->unk0x18 = (s32)lbl_802988F8;` followed by a call, m2c sometimes
also puts `(s32)lbl_802988F8` in the call's argument list.  The DOL's `bl`
has no argument setup at all, so the extra argument costs a `lis/addi` pair
plus a bogus `mr r3, rX`, and it flips the two field-store register
assignments.  The tell is a **duplicated `extern char lbl_XXX[];`** line in
the draft (m2c emitted one declaration per role).

This tool, for every draft, tries removing each `(s32)lbl_*` argument from
every call (with and without a matching prototype-parameter removal),
scores each candidate and prints `BETTER ...` / `EXACT ...` lines.

Usage: printf 'ADDR\\n...' | tools/venv/bin/python tools/label_call_arg_scan.py
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
from test_wip_drafts import test_one  # noqa: E402

LABEL_ARG = re.compile(r"^\s*\(s32\)(?:&)?lbl_[0-9A-Fa-f]+\s*$")
CALL = re.compile(r"\b(fn_[0-9A-F]{8}|[A-Za-z_]\w*)\s*\(")


def split_args(text, start):
    """Split the argument list starting at `start` (index of '(')."""
    depth = 0
    i = start
    args = []
    cur = ""
    while i < len(text):
        c = text[i]
        if c == "(":
            depth += 1
            if depth == 1:
                i += 1
                continue
        elif c == ")":
            depth -= 1
            if depth == 0:
                args.append(cur)
                return args, i
        if depth >= 1:
            cur += c
        i += 1
    return None, None


def call_arg_spans(body):
    """Yield (name, arglist_start, arglist_end, [spans]) for every call."""
    out = []
    for m in CALL.finditer(body):
        name = m.group(1)
        if name in ("if", "while", "for", "switch", "sizeof", "return"):
            continue
        args, end = split_args(body, m.end() - 1)
        if args is None:
            continue
        # locate each argument's absolute span
        spans = []
        pos = m.end()
        for a in args:
            s = body.index(a, pos)
            spans.append((s, s + len(a)))
            pos = s + len(a)
        out.append((name, m.start(), m.end(), end, [a for a in args], spans))
    return out


def proto_variants(body, name, arg_index, n_args):
    """Candidate prototype rewrites for `name` after dropping arg `arg_index`."""
    res = []
    pat = re.compile(r"^[^\n]*\b" + re.escape(name) + r"\s*\(([^)]*)\)\s*;", re.M)
    m = pat.search(body)
    if not m:
        return res
    params = [p for p in m.group(1).split(",")]
    if n_args - 1 == 0:
        newp = ""
    else:
        drop = arg_index if arg_index < len(params) else len(params) - 1
        del params[drop]
        newp = ", ".join(params)
    # keep the return type, rewrite the parameter list
    head = m.group(0)[: m.group(0).index(name)]
    res.append((m.start(), m.end(), "%s%s(%s);" % (head, name, newp)))
    return res


def main():
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 0)
        fp = "src/wip/fn_%08X.c" % addr
        if not os.path.exists(fp):
            continue
        text = open(fp).read()
        flags = gl.draft_flags(text) or None
        base = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        try:
            s0, p0, _ = test_one(addr, base, flags)
        except Exception:
            continue
        if s0 == "EXACT":
            continue
        best = (p0, None)
        # every label-argument occurrence
        for name, cstart, astart, cend, args, spans in call_arg_spans(base):
            for i, (arg, (s, e)) in enumerate(zip(args, spans)):
                if not LABEL_ARG.match(arg):
                    continue
                kept = [x for j, x in enumerate(args) if j != i]
                newcall = (base[:cstart] + name + "(" + ", ".join(kept)
                           + ")" + base[cend + 1:])
                assert newcall != base and newcall.count(name) == base.count(name)
                for tag, cand in [("p", newcall)]:
                    # add prototype-rewritten variants
                    cands = [("noproto", newcall)]
                    for (ps, pe, repl) in proto_variants(newcall, name, i, len(args)):
                        cands.append(("proto", newcall[:ps] + repl + newcall[pe:]))
                    for kind, c in cands:
                        try:
                            s1, p1, _ = test_one(addr, c, flags)
                        except Exception:
                            continue
                        if p1 > best[0] + 0.05:
                            best = (p1, c)
                            print("BETTER 0x%08X %.1f->%.1f [%s %s arg%d/%d]"
                                  % (addr, p0, p1, name, kind, i, len(args)))
                            open("/tmp/label_call_%08X.c" % addr, "w").write(c)
                        elif s1 == "EXACT" and s0 != "EXACT" and best[0] < 100.0:
                            best = (100.0, c)
                            print("EXACT 0x%08X %.1f->100.0 [%s %s arg%d]"
                                  % (addr, p0, name, kind, i))
                            open("/tmp/label_call_%08X.c" % addr, "w").write(c)


if __name__ == "__main__":
    main()
