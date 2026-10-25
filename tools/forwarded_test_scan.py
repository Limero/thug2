#!/usr/bin/env python3
"""Try forwarding the `if`-tested value into the call it guards.

Found by hand three times in one round (fn_8004238C, fn_8005C944,
fn_800685A4, fn_80242528):

    if ((s32) arg0->unk0x190 != 0) {
        fn_80009AAC();                 /* <- m2c dropped the argument */
    }

Retail leaves the tested value in the argument register the callee reads:

    lwz  r3, 0x190(r31)     <- homes in r3/r4, not the compare-only r0
    cmpwi r3, 0
    beq  ...
    bl   fn_80009AAC        <- no argument setup at all

So the real source passes it.  Two symptoms in one: the load lands in r0
instead of a real GPR (`lwz r0` / `cmpwi r0,0`) *and* the callee's register
block is shifted by one slot when the insertion point is not the last param.

For each call inside an `if` block this tool tries inserting the tested load
expression at every argument position, adjusting the callee prototype, and
keeps the best.  Winning bodies go to /tmp/fwd_<ADDR>.c.

Usage: printf 'ADDR\\n...' | tools/venv/bin/python tools/forwarded_test_scan.py
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
import scan_score  # noqa: E402

EXPR_RES = [
    re.compile(r"\(s32\)\s*\w+->unk0x[0-9A-Fa-f]+"),
    re.compile(r"\w+->unk0x[0-9A-Fa-f]+"),
    re.compile(r"\*\(\s*s32\s*\*\)\s*&?\s*\w+"),
    re.compile(r"\*\(\(s32 \*\)\s*\w+\)"),
]
CALL_RE = re.compile(r"(?<![\w>.])(\w+)\(([^;{}]*)\)\s*;")
MAX_TRIES = 16


def split_body(text):
    lines = [l for l in text.splitlines()
             if not l.startswith("//") and "types.h" not in l]
    return "\n".join(lines).strip()


def split_args(s):
    """Split a call's argument list on top-level commas."""
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def prototype_lines(body):
    return {m.group(1): m.group(0) for m in
            re.finditer(r"^(?:void|s32|u32|f32|s16|u16|void \*|char \*)\s+(\w+)\([^;]*\)\s*;",
                        body, re.M)}


def retype_proto(line, name, pos):
    """Insert an `s32` parameter at position `pos` of a prototype line."""
    m = re.match(r"^(.*?\b%s\s*\()(.*)(\)\s*;)$" % re.escape(name), line)
    if not m:
        return None
    params = split_args(m.group(2)) if m.group(2).strip() else []
    if (m.group(2).strip() in ("", "void")) and not params:
        params = []
    params.insert(pos, "s32")
    return m.group(1) + ", ".join(params) + m.group(3)


def candidates(body):
    """Yield (call_name, args, expr, position) insertion candidates."""
    protos = prototype_lines(body)
    lines = body.splitlines()
    seen = set()
    for ln, line in enumerate(lines):
        for cm in CALL_RE.finditer(line):
            name, argstr = cm.group(1), cm.group(2)
            if name in ("if", "while", "for", "switch", "return", "sizeof"):
                continue
            args = split_args(argstr)
            # The guarded call must be the FIRST statement of the `if` body --
            # that is the only shape the retail evidence supports (the tested
            # value is still live in its argument register when the `bl` runs).
            # Any later call in the block is a different defect and inserting
            # the expression there just destroys the body.
            k = ln
            while k >= 0 and not re.search(r"\bif\s*\(", lines[k]):
                k -= 1
            if k < 0 or ln - k > 1:
                continue
            cond = lines[k]
            brace = lines[k].rfind("{")
            if brace < 0:
                continue
            if ln == k:
                between = lines[k][brace + 1:cm.start()]
            else:
                between = lines[k][brace + 1:] + lines[ln][:cm.start()]
            if between.strip():  # only `{` may separate the `if` from the call
                continue
            exprs = []
            for rx in EXPR_RES:
                exprs.extend(rx.findall(cond))
            for e in dict.fromkeys(exprs):
                if any(e.replace(" ", "") == a.replace(" ", "") or e in a for a in args):
                    continue
                for pos in range(len(args) + 1):
                    key = (ln, name, e, pos)
                    if key in seen:
                        continue
                    seen.add(key)
                    yield ln, name, args, e, pos, protos


PREV_CALL_RE = re.compile(r"^(?:[^=;]*=\s*)?(\w+\s*\([^;{}]*\))\s*;\s*$")


def prev_call_candidates(body):
    """Yield candidates whose argument is the PRECEDING call expression.

    The second shape of this defect (fn_80126E28, fn_80242528, fn_800AAEA4):

        temp_r30 = fn_801291FC(arg1);
        fn_801291FC(arg0);
        fn_80126BF0(temp_r30, temp_r31, temp_r28);   /* r3 = that call's result */

    Retail emits no `mr r3` before the last `bl`, so the leading argument is
    the value the previous call left in r3.  Here the guarded call is *not*
    the first statement of the block, so `candidates()` cannot see it; the
    scoping rule instead is "the statement immediately above is a call".
    """
    protos = prototype_lines(body)
    lines = body.splitlines()
    seen = set()
    for ln in range(1, len(lines)):
        pm = PREV_CALL_RE.match(lines[ln - 1].strip())
        if not pm:
            continue
        expr = pm.group(1).strip()
        for cm in CALL_RE.finditer(lines[ln]):
            name, argstr = cm.group(1), cm.group(2)
            if name in ("if", "while", "for", "switch", "return", "sizeof"):
                continue
            if name == expr.split("(")[0].strip():
                continue
            args = split_args(argstr)
            e = "(s32) %s" % expr
            if any(e in a or expr in a for a in args):
                continue
            key = (ln, name, e, 0)
            if key in seen:
                continue
            seen.add(key)
            yield ln, name, args, e, 0, protos


def build(body, ln, name, args, expr, pos, protos):
    lines = body.splitlines()
    old = lines[ln]
    m = CALL_RE.search(old)
    newargs = list(args)
    newargs.insert(pos, expr)
    newcall = "%s(%s);" % (name, ", ".join(newargs))
    lines[ln] = old[:m.start()] + newcall + old[m.end():]
    out = "\n".join(lines)
    if name in protos:
        newp = retype_proto(protos[name], name, pos)
        if newp is None:
            return None
        out = out.replace(protos[name], newp, 1)
    else:
        out = "void %s(%s);\n" % (name, ", ".join("s32" for _ in newargs)) + out
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
        tries = 0
        cands = list(candidates(body)) + list(prev_call_candidates(body))
        for ln, name, args, expr, pos, protos in cands:
            if tries >= MAX_TRIES:
                break
            tries += 1
            v = build(body, ln, name, args, expr, pos, protos)
            if v is None:
                continue
            s2, sc = scan_score.score(addr, v, flags)
            mark = "BETTER" if sc > base + 0.001 else ("same" if sc >= base - 0.001 else "worse")
            print("%08X %-16s %-30s pos=%d %5.1f -> %5.1f  %s" % (
                addr, name, expr, pos, base, sc, mark))
            sys.stdout.flush()
            if sc > base and (best is None or sc > best[0]):
                best = (sc, s2, v)
        if best:
            open("/tmp/fwd_%08X.c" % addr, "w").write(best[2] + "\n")


if __name__ == "__main__":
    main()
