#!/usr/bin/env python3
"""Try prepending the enclosing function's own parameters to a call.

The most common remaining register-block defect in the pool:

    want  mr r31, r3            ; arg0 saved
          li  r4, 1             ; <- only r4 is set up
          bl  fn_8005C9A8
    got   li  r3, 1             ; m2c dropped the pass-through argument
          bl  fn_8005C9A8

Retail leaves r3 = the enclosing function's incoming argument and only writes
r4, i.e. the real source is `fn_8005C9A8(arg0, 1)`.  m2c never invents a
pass-through, so the draft's whole argument block sits one slot low and every
word of it mismatches.

For every call site this tool tries prepending each of the enclosing
function's parameters (cast to `s32` so the value is not re-loaded) at each
argument position, fixing the callee prototype, and keeps the best A/B.
Winning bodies go to /tmp/lead_<ADDR>.c.

Usage: printf 'ADDR\\n...' | tools/venv/bin/python tools/lead_arg_scan.py
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
import scan_score  # noqa: E402

CALL_RE = re.compile(r"(?<![\w>.])(\w+)\(([^;{}]*)\)\s*;")
DEF_RE = re.compile(r"^\s*(?:void|s32|u32|f32|static\s+\w+|\w+)\s+\**(\w+)\s*\(([^)]*)\)\s*\{",
                    re.M)
MAX_TRIES = 24


def split_body(text):
    lines = [l for l in text.splitlines()
             if not l.startswith("//") and "types.h" not in l]
    return "\n".join(lines).strip()


def split_args(s):
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


def own_definition(body):
    """(name, params) of the draft's own function definition."""
    for m in DEF_RE.finditer(body):
        # DEF_RE requires a `{`, so any match is a definition, not a prototype
        params = split_args(m.group(2))
        names = []
        for p in params:
            w = re.findall(r"[A-Za-z_]\w*", p)
            if not w or p.strip() in ("void", "void *"):
                continue
            # the last identifier of a declarator is the parameter name
            names.append(w[-1])
        return m.group(1), names
    return None, []


PROTO_LINE_RE = re.compile(
    r"^\s*(?:extern\s+)?(?:void|s32|u32|f32|s16|u16|char|int)\s+\**\w+\s*\(")


def prototype_lines(body):
    return {m.group(1): m.group(0) for m in
            re.finditer(r"^(?:void|s32|u32|f32|s16|u16|void \*|char \*)\s+(\w+)\([^;]*\)\s*;",
                        body, re.M)}


def retype_proto(line, name, pos):
    m = re.match(r"^(.*?\b%s\s*\()(.*)(\)\s*;)$" % re.escape(name), line)
    if not m:
        return None
    inner = m.group(2).strip()
    params = [] if inner in ("", "void") else split_args(inner)
    params.insert(pos, "s32")
    return m.group(1) + ", ".join(params) + m.group(3)


def main():
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a[2:], 16) if a[:2].lower() == "0x" else int(a, 16)
        path = "src/wip/fn_%08X.c" % addr
        if not os.path.exists(path):
            continue
        text = open(path).read()
        body = split_body(text)
        flags = gl.draft_flags(text) or None
        base = scan_score.pct(addr, body, flags)
        own, params = own_definition(body)
        if not params:
            continue
        protos = prototype_lines(body)
        lines = body.splitlines()
        best = None
        tries = 0
        for ln, l in enumerate(lines):
            if PROTO_LINE_RE.match(l):  # declaration, not a call
                continue
            for cm in CALL_RE.finditer(l):
                name, argstr = cm.group(1), cm.group(2)
                if name in ("if", "while", "for", "switch", "return", "sizeof"):
                    continue
                args = split_args(argstr)
                for p in params:
                    for pos in range(len(args) + 1):
                        if tries >= MAX_TRIES:
                            break
                        tries += 1
                        newargs = list(args)
                        newargs.insert(pos, p)
                        new = "%s(%s);" % (name, ", ".join(newargs))
                        cand = list(lines)
                        cand[ln] = l[:cm.start()] + new + l[cm.end():]
                        out = "\n".join(cand)
                        if name in protos:
                            np_ = retype_proto(protos[name], name, pos)
                            if np_ is None:
                                continue
                            out = out.replace(protos[name], np_, 1)
                        else:
                            out = "void %s(%s);\n" % (
                                name, ", ".join("s32" for _ in newargs)) + out
                        s2, sc = scan_score.score(addr, out, flags)
                        if sc > base + 0.001:
                            mark = "BETTER"
                        elif sc >= base - 0.001:
                            mark = "same"
                        else:
                            mark = "worse"
                        print("%08X %-16s %-12s pos=%d %5.1f -> %5.1f  %s" % (
                            addr, name, p, pos, base, sc, mark))
                        sys.stdout.flush()
                        if sc > base and (best is None or sc > best[0]):
                            best = (sc, s2, out)
                    if tries >= MAX_TRIES:
                        break
                if tries >= MAX_TRIES:
                    break
            if tries >= MAX_TRIES:
                break
        if best:
            open("/tmp/lead_%08X.c" % addr, "w").write(best[2] + "\n")


if __name__ == "__main__":
    main()
