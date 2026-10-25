#!/usr/bin/env python3
"""SPLIT-EXPRESSION sweep for WIP drafts (AGENTS.md recipe: statement-splitting
the RHS of an arithmetic assignment is a general lever, not a one-off).

Retail frequently materialises a nested arithmetic expression as TWO
statements rather than one:

    want:   t = a * 0x3E8 ;  X = t * b        (two statements)
    ngccc:  X = b * (a * 0x3E8)                (one expression -> load order)

Because the score is computed per masked word, one statement vs two changes
the RTL dependency order, which is enough to flip a 2-word residue to EXACT
even though every operand and register is identical.  This is the same
family as the "comma-in-argument placement" and "temp-first staging"
recipes, but automated.

For every one-line assignment  `L = A op (B op C);`  or  `L = (A op B) op C;`
this emits one variant that hoists the inner group into a fresh named temp
assigned immediately before the statement.  The temp is declared as the
first declaration of the function (C89 requires decls before statements).

usage:
    expr_split_sweep.py <file-list> [lo] [hi]
prints:  verdict<TAB>delta<TAB>file<TAB>info
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import test_wip_drafts as T  # noqa: E402

# an assignment whose RHS is a single expression, at the end of a line
ASSIGN = re.compile(
    r"^\s*(?P<lhs>[A-Za-z_][\w.\-\>\[\]]*)\s*=\s*(?P<rhs>[^;]*);\s*$")
FUNC_OPEN = re.compile(r"^\w[^\n;]*\)\s*\{\s*$")
NESTED = re.compile(r"^(?P<a>[^()]*?)\s*(?P<op>[*+\-/])\s*"
                    r"\((?P<b>[^()]*?)\s*(?P<op2>[*+\-/])\s*(?P<c>[^()]+)\)$")


def _open_brace_line(lines):
    """index of the line holding the function body's opening brace"""
    for i, l in enumerate(lines):
        if FUNC_OPEN.match(l):
            return i
    return -1


def _used_names(text):
    return set(re.findall(r"\b[A-Za-z_]\w*\b", text))


def variants(body):
    lines = body.split("\n")
    ob = _open_brace_line(lines)
    if ob < 0:
        return
    used = _used_names(body)
    n = 0
    for i, l in enumerate(lines):
        m = ASSIGN.match(l)
        if not m:
            continue
        lhs, rhs = m.group("lhs"), m.group("rhs").strip()
        if not rhs or rhs.count("(") != rhs.count(")"):
            continue
        if rhs.count("(") > 1:
            continue                      # keep the shape unambiguous
        nm = NESTED.match(rhs)
        if not nm:
            continue
        if "asm" in rhs or "__" in rhs:
            continue
        a, op = nm.group("a").strip(), nm.group("op")
        b, op2, c = nm.group("b").strip(), nm.group("op2"), nm.group("c").strip()
        if not a or not b or not c:
            continue
        n += 1
        tmp = f"_xs{n}"
        while tmp in used:
            tmp += "x"
        # hoist the INNER group (b op2 c) into a fresh temp assigned
        # immediately BEFORE the statement, keeping both operand orders
        for rev in (False, True):
            t2 = tmp + ("r" if rev else "")
            outer = f"{t2} {op} {a}" if rev else f"{a} {op} {t2}"
            new_line = l.replace(rhs, outer, 1)
            stmt = f"    {t2} = {b} {op2} {c};\n{new_line}"
            out = list(lines)
            out[i] = stmt
            out.insert(ob + 1, f"    s32 {t2};")
            yield (f"split[{i}]{'rev' if rev else ''} {rhs[:40]}",
                   "\n".join(out))


def one(fn):
    fn = os.path.basename(fn)
    path = os.path.join(ROOT, "src/wip", fn)
    addr = int(fn[3:-2], 16)
    raw = open(path).read()
    fl = T.gl.draft_flags(raw)
    body = "\n".join(l for l in raw.splitlines()
                     if not l.lstrip().startswith("//"))
    try:
        _, pct0, _ = T.test_one(addr, body, extra_flags=fl or None)
    except Exception:  # noqa: BLE001
        return (fn, "ERR0", 0.0, "")
    best = (None, 0.0, "", 0.0)
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
    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="xs_")
    for fn, v, d, info in map(one, files[lo:hi]):
        if v != "NONE":
            print(f"{v}\t{d:+.2f}\t{fn}\t{info}", flush=True)
