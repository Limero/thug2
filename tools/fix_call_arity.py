#!/usr/bin/env python3
"""Fix calls whose callee was declared with the wrong arity (doc-52 family).

m2c emits guessed prototypes.  When a draft's prototype for a promoted callee
has the wrong number of parameters the call passes/sets up arguments the wrong
way, which looks like unrelated regalloc noise.  Earlier passes fixed these by
hand; the dropped argument is nearly always a value already in scope (a
parameter, a local, a loop cursor) or a small constant.

For every callee whose declared arity disagrees with the real promoted source,
this rewrites the declaration to the real signature, aligns every call site to
that arity, and searches the (insert position, expression) space for the
alignment that best matches the DOL.

Usage:
  tools/venv/bin/python tools/fix_call_arity.py 0x8009E4B0 [more addrs]
  tools/venv/bin/python tools/fix_call_arity.py --file /tmp/arity_cands.txt
  ... --write   persist the best alignment found
"""
import os
import re
import sys
from multiprocessing import Pool

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from test_wip_drafts import test_one

DECL = re.compile(r"^([ \t]*)((?:static\s+)?[\w \t\*]*?)\b(fn_[0-9A-F]{8})\s*\(([^;{}]*)\)\s*;", re.M)
LOCAL = re.compile(r"^[ \t]{4,}(?:unsigned\s+|signed\s+)?[A-Za-z_]\w*[ \t\*]+([A-Za-z_]\w*)\s*;\s*$", re.M)
FUNCDEF = re.compile(r"^\w[\w \t\*]*?\b(fn_[0-9A-F]{8})\(([^)]*)\)\s*\{", re.M)
EXTRA = ["0", "1", "3", "NULL"]
# A draft with a big call graph can generate thousands of candidates per round;
# cap and subsample so a full-tree sweep stays bounded.
MAX_CANDS = 400


def _init():
    os.environ["LEAF_TMPDIR"] = "/tmp/leaf/arity%d" % os.getpid()


def _score(args):
    idx, addr, body = args
    try:
        _, pct, _ = test_one(addr, body)
    except Exception:
        return idx, 0.0
    return idx, pct


def types_only(params):
    out = []
    for a in params.split(","):
        a = a.strip()
        if not a or a == "void":
            continue
        a = re.sub(r"\s*\b\w+\s*$", "", a).strip()
        out.append(a or "s32")
    return out


def real_proto(name):
    p = os.path.join(ROOT, "src/%s.c" % name)
    if not os.path.exists(p):
        return None
    m = re.search(r"^(\w[\w \t\*]*?)\s*\b%s\(([^)]*)\)\s*\{" % name, open(p).read(), re.M)
    if not m:
        return None
    params = []
    for a in m.group(2).split(","):
        a = a.strip()
        if not a or a == "void":
            continue  # `f(void)` really takes ZERO args
        a = re.sub(r"\s*\b\w+\s*$", "", a).strip()
        params.append(a or "s32")
    return "%s" % m.group(1).strip(), params


def call_sites(text, callee, skip_span=None):
    out = []
    for m in re.finditer(r"\b%s\s*\(" % callee, text):
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
        args.append(cur)
        if skip_span and skip_span[0] <= m.start() < skip_span[1]:
            continue
        out.append((m.start(), i + 1, [a.strip() for a in args if a.strip()]))
    return out


def candidates_for(text):
    pool = []
    m = FUNCDEF.search(text)
    if m:
        for a in m.group(2).split(","):
            a = a.strip()
            if not a or a == "void":
                continue  # `f(void)` takes no args — "void" is not an expression
            nm = re.search(r"(\w+)\s*$", a)
            if nm:
                pool.append(nm.group(1))
    pool += LOCAL.findall(text)
    pool += EXTRA
    seen, out = set(), []
    for p in pool:
        if p not in seen:
            seen.add(p)
            out.append(p)
    return out


def align(text, name, real, pos, expr):
    """Rewrite the declaration of `name` to the real arity and align its calls."""
    proto = real_proto(name)
    if proto is None:
        return None
    _, params = proto
    m = None
    for cand in DECL.finditer(text):
        if cand.group(3) == name:
            m = cand
            break
    if m is None:
        return None
    new_decl = "%s%s%s(%s);" % (m.group(1), m.group(2), name, ", ".join(params))
    out = text[:m.start()] + new_decl + text[m.end():]
    decl_span = (m.start(), m.start() + len(new_decl))
    # rewrite call sites right-to-left so earlier offsets stay valid
    for site in reversed(call_sites(out, name, skip_span=decl_span)):
        s, e, args = site
        open_paren = out.index("(", s)
        new_args = list(args)
        while len(new_args) > real:
            new_args.pop()
        if len(new_args) < real:
            if pos is None or pos >= len(new_args):
                new_args.append(expr)
            else:
                new_args.insert(pos, expr)
        out = out[:s] + out[s:open_paren + 1] + ", ".join(new_args) + ")" + out[e:]
    return out


def search(addr, rounds=6):
    path = os.path.join(ROOT, "src/wip/fn_%08X.c" % addr)
    text = open(path).read()
    with Pool(8, initializer=_init) as pool:
        cur_text = text
        cur = _score((0, addr, text))[1]
        hist = []
        for _ in range(rounds):
            cands = []
            exprs = candidates_for(cur_text)
            for m in DECL.finditer(cur_text):
                name, params = m.group(3), m.group(4)
                proto = real_proto(name)
                if proto is None:
                    continue
                real = len(proto[1])
                if len(types_only(params)) == real:
                    continue
                for pos in range(0, real + 1):
                    for expr in exprs:
                        body = align(cur_text, name, real, pos, expr)
                        if body:
                            cands.append((name, pos, expr, body))
            if not cands:
                break
            if len(cands) > MAX_CANDS:
                step = len(cands) / float(MAX_CANDS)
                cands = [cands[int(i * step)] for i in range(MAX_CANDS)]
            res = pool.map(_score, [(i, addr, c[3]) for i, c in enumerate(cands)])
            res.sort(key=lambda r: -r[1])
            idx, pct = res[0]
            if pct > cur + 1e-9:
                name, pos, expr, body = cands[idx]
                cur_text, cur = body, pct
                hist.append("%s pos%d=%s -> %.1f%%" % (name, pos, expr, pct))
            else:
                break
    return cur, hist, cur_text


def main():
    args = sys.argv[1:]
    write = "--write" in args
    if write:
        args.remove("--write")
    rounds = 6
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
        try:
            pct, hist, body = search(addr, rounds)
        except Exception as e:
            print("%08X ERR %s" % (addr, str(e)[:70]), flush=True)
            continue
        if not hist:
            continue
        print("%08X %.1f%%  %s" % (addr, pct, " | ".join(hist)), flush=True)
        if write:
            path = os.path.join(ROOT, "src/wip/fn_%08X.c" % addr)
            if body != open(path).read():
                note = ("// ARITY SEARCH 2026-09-11 (tools/fix_call_arity.py): real callee "
                        "prototype restored + calls aligned; %s (score now %.1f%%)."
                        % (" | ".join(hist), pct))
                lines = body.rstrip("\n").splitlines()
                inset = 0
                while inset < len(lines) and lines[inset].startswith("//"):
                    inset += 1
                open(path, "w").write("\n".join(lines[:inset] + [note] + lines[inset:]) + "\n")


if __name__ == "__main__":
    main()
