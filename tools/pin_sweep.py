#!/usr/bin/env python3
"""HARD-REGISTER PIN sweep for WIP drafts.

When `tools/regdiff_scan.py` reports a draft whose residual is a pure
register RENAME, the fix is almost always a hard-register pin on the web
that owns the renamed value (AGENTS.md §6o-98, §6y-124, §6c-183,
§6ad-166).  This tool automates that: it takes the want-side registers
named by the rename pairs and tries pinning each function-top local to
each of them, keeping the best strict improvement.

Two pins to the SAME register are allowed only when the draft's own
locals are disjoint (the exclusive-range dual-pin of §6ad-166) - the
compiler rejects overlapping ranges, so a FAIL is just a dead variant.

usage:
    pin_sweep.py <file-list> [lo] [hi]
reads the want-registers from stdin lines of the form
    <pct>\t<file>\t<ndiff>\t<reg,reg>...>;<reg,reg>...
(one per line, as produced by regdiff_scan.py)
prints:  verdict<TAB>delta<TAB>file<TAB>info
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import test_wip_drafts as T  # noqa: E402

# function-top single-declarator locals: "<type> <name>[ = init];" at
# 4-space indent.  Structured types (Unk_XXXX *, CStruct *, ...) are included
# because the regdiff signature is usually a *pointer* web; pointer pins are
# dropped by cc1 (§74-161a/§6az-245) so those are aliased to s32 at rewrite
# time, but they must still be enumerated here to be tried.
DECL = re.compile(r"^    ((?:const\s+)?(?:volatile\s+)?"
                  r"(?:unsigned\s+|signed\s+)?"
                  r"(?:\w+)\s*\*?)\s*"
                  r"([A-Za-z_]\w*)\s*(?:=[^;]*)?;\s*$")
# the same, already carrying a pin
PINNED = re.compile(r"^    register\s+.*\b([A-Za-z_]\w*)\b.*__asm__")


def _pins(body):
    """set of (decl_line, name, reg) already pinned"""
    out = set()
    for l in body.split("\n"):
        m = PINNED.match(l)
        if m:
            out.add(m.group(1))
    return out


def _locals(body):
    """[(line_index, name, type_text)] for function-top plain locals"""
    out = []
    for i, l in enumerate(body.split("\n")):
        m = DECL.match(l)
        if m:
            out.append((i, m.group(2), m.group(1).strip()))
    return out


def _want_regs(pairs_field):
    regs = []
    for grp in pairs_field.split(";"):
        if ">" not in grp:
            continue
        for side in grp.split(">")[0].split(","):
            side = side.strip()
            if side.isdigit() and side not in regs:
                regs.append(side)
    return regs


def _pin_variant(lines, idx, name, typ, reg):
    """Return the source with `name` hard-pinned to `reg`, or None.

    cc1 silently drops pointer-typed hard-reg pins (AGENTS §74-161a,
    §6az-245), so a `T *name` local is pinned via an s32 alias whose uses
    are rewritten to the alias.  Only the function-top declaration line and
    the identifier's other uses are touched; the initializer is preserved.
    """
    decl = lines[idx]
    if typ.endswith("*"):
        alias = name + "_pin"
        m = re.match(r"^(\s*)(.*?)(" + re.escape(name) + r")\s*(=\s*.*)?;\s*$",
                     decl)
        if not m:
            return None
        out = list(lines)
        out[idx] = (f"    register s32 {alias} __asm__(\"r{reg}\");\n"
                    f"    {typ}{name} = ({typ}{name}){alias};")
        for j, l in enumerate(out):
            if j == idx:
                continue
            out[j] = re.sub(r"\b" + re.escape(name) + r"\b", alias, l)
        return "\n".join(out)
    lines2 = list(lines)
    lines2[idx] = f'    register {typ} {name} __asm__("r{reg}");'
    return "\n".join(lines2)


def one(fn, regs):
    path = os.path.join(ROOT, "src/wip", fn)
    addr = int(fn[3:-2], 16)
    raw = open(path).read()
    flags = T.gl.draft_flags(raw)
    body = "\n".join(l for l in raw.splitlines()
                     if not l.lstrip().startswith("//"))
    try:
        _, pct0, _ = T.test_one(addr, body, extra_flags=flags or None)
    except Exception:  # noqa: BLE001
        return (fn, "ERR0", 0.0, "")
    lines = body.split("\n")
    already = _pins(body)
    cands = [(i, n, t) for i, n, t in _locals(body) if n not in already]
    if not cands:
        return (fn, "NONE", 0.0, "")
    best = (None, 0.0, "", 0.0)
    for i, name, typ in cands:
        for reg in regs:
            # reg comes from the want-side register NUMBERS ("26"), while
            # the templates in _pin_variant write the "r" prefix themselves.
            reg = reg.lstrip("r")
            src = _pin_variant(lines, i, name, typ, reg)
            if src is None:
                continue
            try:
                st, pct, _ = T.test_one(addr, src,
                                        extra_flags=flags or None)
            except Exception:  # noqa: BLE001
                continue
            if pct - pct0 > best[1] + 1e-9:
                best = (f"{name}->r{reg}", pct - pct0, st, pct)
    if best[0] is None:
        return (fn, "NONE", 0.0, "")
    return (fn, best[2], best[1], f"{best[0]} -> {best[3]:.2f}")


if __name__ == "__main__":
    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="pin_")
    lo = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    hi = int(sys.argv[2]) if len(sys.argv) > 2 else 10 ** 9
    rows = []
    for line in sys.stdin:
        p = line.rstrip("\n").split("\t")
        if len(p) < 4:
            continue
        rows.append((p[1], p[3]))
    for fn, pairs in rows[lo:hi]:
        if not os.path.exists(os.path.join(ROOT, "src/wip", fn)):
            continue
        for regs in _want_regs(pairs):
            v, st, d, info = one(fn, [regs])
            if st not in ("NONE", "ERR0"):
                print(f"{st}\t{d:+.2f}\t{fn}\t{info}", flush=True)
            else:
                print(f"{st}\t+0.00\t{fn}\t(no strict pin improvement)",
                      flush=True)
