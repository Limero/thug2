#!/usr/bin/env python3
"""A/B the doc-52 phantom argument lever on wip drafts (robust scanner).

Finds every call whose argument list contains a bare `0x80xxxxxx` literal,
produces a variant with that argument removed (and the matching prototype
parameter removed when the arity matches), scores it, and prints

    0xADDR orig% -> STATUS variant%   <== BETTER

Usage: printf 'ADDR\n' | tools/venv/bin/python tools/drop_phantom_arg.py
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from test_wip_drafts import test_one

LIT = re.compile(r"^\(?(?:s32|u32|char \*|void \*)?\)?0x80[0-9A-Fa-f]{6}$")
# 2026-09-17: bare-0 extension (fn_8000B348 family). m2c invents a leading `0`
# for unknown first args (e.g. sprintf(0, dst, fmt) for a 2-arg call); WANT
# sets one fewer arg reg and the extra li shifts the whole tail. Same
# keep-only-gains gating as the address-literal class, so real zero args
# can never promote (they score worse and are discarded).


def find_calls(body):
    """Yield (name, arg_start, arg_end, args) for every ident(...) call."""
    for m in re.finditer(r"([A-Za-z_][A-Za-z_0-9]*)\s*\(", body):
        name = m.group(1)
        if name in ("if", "while", "for", "switch", "return", "sizeof"):
            continue
        i = m.end() - 1
        depth = 0
        j = i
        while j < len(body):
            if body[j] == "(":
                depth += 1
            elif body[j] == ")":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        if j >= len(body):
            continue
        args_text = body[i + 1:j]
        args = split_args(args_text)
        yield name, i, j, args, args_text


def split_args(s):
    parts, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append(cur.strip())
            cur = ""
        else:
            cur += ch
    parts.append(cur.strip())
    return parts


def trim_proto(text, name, nargs, drop_idx):
    m = re.search(r"^([^\n;{}/]*?\b" + name + r"\s*)\(([^)]*)\)\s*;", text, re.M)
    if not m:
        return text
    params = split_args(m.group(2))
    if len(params) != nargs:
        return text
    del params[drop_idx]
    return text[:m.start()] + f"{m.group(1)}({', '.join(params)});" + text[m.end():]


ZERO = re.compile(r"^\(?(?:s32|u32)?\)?0$")


def apply_edits(body, edits):
    """Apply a list of (name, i0, i1, args, k) drops back-to-front.
    Proto params are trimmed per call-site arity in a single pass: drops
    are grouped by (name, nargs) and all of that group's indices are
    deleted descending at once. (Grouping by name alone crashes when one
    name is called at several arities — the stored nargs can mismatch the
    proto while a foreign drop_idx slips through the length check.)"""
    new = body
    protos = {}
    for name, i0, i1, args, k in sorted(edits, key=lambda e: -e[1]):
        keep = [x for idx, x in enumerate(args) if idx != k]
        new = new[:i0 + 1] + ", ".join(keep) + new[i1:]
        protos.setdefault(name, []).append((len(args), k))
    by_arity = {}
    for name, lst in protos.items():
        for nargs, k in lst:
            by_arity.setdefault((name, nargs), []).append(k)
    for (name, nargs), ks in by_arity.items():
        m = re.search(r"^([^\n;{}/]*?\b" + name + r"\s*)\(([^)]*)\)\s*;",
                      new, re.M)
        if not m:
            continue
        params = split_args(m.group(2))
        if len(params) != nargs:
            continue
        if any(k >= len(params) for k in ks):
            continue
        for k in sorted(set(ks), reverse=True):
            del params[k]
        new = new[:m.start()] + f"{m.group(1)}({', '.join(params)});" + new[m.end():]
    return new


def main():
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 16)
        text = open(f"src/wip/fn_{addr:08X}.c").read()
        flags = gl.draft_flags(text) or None
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        s0, p0, _ = test_one(addr, body, flags)
        # collect edits back-to-front so offsets stay valid
        addr_edits, zero_edits = [], []
        for name, i0, i1, args, args_text in find_calls(body):
            for k, arg in enumerate(args):
                if LIT.match(arg):
                    addr_edits.append((name, i0, i1, args, k))
                elif ZERO.match(arg):
                    zero_edits.append((name, i0, i1, args, k))
        if not addr_edits and not zero_edits:
            print(f"0x{addr:08X} {p0:5.1f} -> (no raw-literal call arg)")
            continue
        # candidates: addr-drops all-at-once, then addr-drops + each single
        # zero-drop (bare zeros are often legitimate flags, so test singly).
        cands = []
        if addr_edits:
            cands.append(addr_edits)
        for ze in zero_edits:
            cands.append(addr_edits + [ze])
        best, best_p, best_s = body, p0, s0
        for edits in cands:
            new = apply_edits(body, edits)
            s1, p1, err = test_one(addr, new, flags)
            if p1 > best_p:
                best, best_p, best_s = new, p1, s1
        mark = "  <== BETTER" if best_p > p0 else ""
        print(f"0x{addr:08X} {p0:5.1f} -> {best_s} {best_p:5.1f}{mark}")
        if best_p > p0:
            open(f"/tmp/phantom_{addr:08X}.c", "w").write(best + "\n")


if __name__ == "__main__":
    main()
