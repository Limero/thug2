#!/usr/bin/env python3
"""doc-56 sweep: declare a prototype for every *undeclared* callee.

ngccc adds a `crclr cr1eq` (one extra word, whole tail shifted) to calls whose
callee has no prototype in scope.  m2c drafts routinely call `fn_XXXXXXXX`
without any declaration, so this is a large, purely mechanical family.

Strategy per draft: for every `fn_XXXXXXXX(` call with no prototype line in the
draft, add a declaration.  The declaration is taken from the callee's own
already-decompiled `src/fn_XXXXXXXX.c` definition when it exists (so the types
are exactly right), otherwise a small set of arity guesses is tried.

Usage: printf 'ADDR\\n...' | tools/venv/bin/python tools/proto_undeclared_scan.py
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
import detect_structs as ds  # noqa: E402 (struct-class aliases)
from test_wip_drafts import test_one  # noqa: E402
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs  # noqa: E402

_md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
_md.skipdata = True


def has_cr_bit(body, addr):
    """Cheap prefilter: does the compile actually contain a crclr/crset?"""
    try:
        got, _ = gl.compile_fn(addr, body)
    except Exception:
        return False
    if not got:
        return False
    for i in _md.disasm(got, addr):
        if i.mnemonic in ("crclr", "crset"):
            return True
    return False

CALL = re.compile(r"\b(fn_[0-9A-F]{8})\s*\(")
# A *declaration* needs a return type before the name — otherwise the call
# statement `    fn_8005C944(arg0, arg1);` matches too and the callee is wrongly
# treated as prototyped.
DECL = re.compile(
    r"^[^\n{};]*?\b(?:void|char|short|int|long|float|double|s32|u32|s16|u16|"
    r"s8|u8|f32|f64|__ps_t|Unk_\w+|%s)\s*\**\s*(fn_[0-9A-F]{8})\s*\([^;{}]*\)\s*;"
    % "|".join(ds.ALIASES.values()),
    re.M)
DEF = re.compile(r"^[A-Za-z_][^\n{};]*?\bfn_([0-9A-F]{8})\s*\(([^;{}]*)\)\s*\{", re.M)


def call_arity(body, name):
    """Highest top-level argument count over every call to `name`."""
    best = 0
    for m in re.finditer(r"\b" + name + r"\s*\(", body):
        i = m.end()
        depth = 1
        n = 1 if body[i] == ")" else 1
        cur = ""
        args = 0
        while i < len(body):
            c = body[i]
            if c == "(":
                depth += 1
            elif c == ")":
                depth -= 1
                if depth == 0:
                    break
            if depth == 1 and c == ",":
                args += 1
            cur += c
            i += 1
        if cur.strip():
            args += 1
        best = max(best, args)
    return best

_cache = {}


def real_sig(name):
    """Return the definition's return type + parameter list, or None."""
    if name in _cache:
        return _cache[name]
    fp = "src/%s.c" % name
    val = None
    if os.path.exists(fp):
        src = open(fp).read()
        m = None
        for m in DEF.finditer(src):
            if m.group(1) * 0 + m.group(0):
                pass
        m = DEF.search(src)
        if m:
            head = m.group(0)[: m.group(0).index(name)].strip()
            head = head.split("\n")[-1].strip()
            val = (head, m.group(2).strip())
    _cache[name] = val
    return val


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
        if not has_cr_bit(base, addr):
            continue
        # Iterate: a draft often carries TWO or more undeclared callees, and the
        # first prototype only exposes the second one's `crclr`.  Each round
        # re-derives the declaration set from the current best body, so a
        # prototype already added is never tried twice.
        best = (p0, base)
        for _round in range(4):
            cur = best[1]
            if not has_cr_bit(cur, addr):
                break
            declared = set("fn_" + m.group(1) for m in DECL.finditer(cur))
            called = set(m.group(1) for m in CALL.finditer(cur))
            # names defined *in this file* are not callees
            own = re.search(r"\b(fn_[0-9A-F]{8})\s*\([^;]*\)\s*\{", cur)
            if own:
                called.discard(own.group(1))
            round_best = (best[0], None, None)
            for name in sorted(called - declared):
                cands = []
                sig = real_sig(name)
                if sig:
                    ret, params = sig
                    cands.append("%s %s(%s);" % (ret, name, params))
                # arity inferred from the call site: `void *` params pass
                # exactly like ints on PPC, so only the count decides the setup
                n = call_arity(cur, name)
                if n == 0:
                    cands.append("void %s(void);" % name)
                else:
                    cands.append("void %s(%s);" % (name, ", ".join(["void *"] * n)))
                for decl in dict.fromkeys(cands):
                    cand = decl + "\n" + cur
                    try:
                        _s1, p1, _ = test_one(addr, cand, flags)
                    except Exception:
                        continue
                    if p1 > round_best[0] + 0.05:
                        round_best = (p1, cand, decl)
            if round_best[2] is None:
                break
            best = (round_best[0], round_best[1])
            print("BETTER 0x%08X %.1f->%.1f [%s]" % (addr, p0, best[0], round_best[2]))
            open("/tmp/proto_%08X.c" % addr, "w").write(best[1])


if __name__ == "__main__":
    main()
