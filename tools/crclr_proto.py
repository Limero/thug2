#!/usr/bin/env python3
"""For each draft with a spurious `crclr cr1eq`, find the callee and try
injecting a prototype at various arities/return types; report any improvement.

Usage: tools/venv/bin/python tools/crclr_proto.py 0xADDR [0xADDR ...]
"""
import multiprocessing as mp
import os
import re
import struct
import sys

CRCLR = 0x4CC63182
ADDRS = []


def _init():
    os.environ["LEAF_TMPDIR"] = "/tmp/leaf/cp%d" % os.getpid()


def _insert(body, decl):
    lines = body.splitlines()
    idx = 0
    for i, l in enumerate(lines):
        if l.lstrip().startswith("#include"):
            idx = i + 1
    lines.insert(idx, decl)
    return "\n".join(lines)


def _count_args(body, name):
    """Return the max arg count seen at any call of `name(` in body."""
    best = None
    for m in re.finditer(re.escape(name) + r"\s*\(", body):
        i = m.end()
        depth = 1
        parts = []
        cur = ""
        while i < len(body) and depth:
            c = body[i]
            if c in "([":
                depth += 1
            elif c in ")]":
                depth -= 1
                if depth == 0:
                    break
            if depth == 1 and c == ",":
                parts.append(cur)
                cur = ""
            else:
                cur += c
            i += 1
        if cur.strip() or parts:
            parts.append(cur)
        n = len([p for p in parts if p.strip()])
        if best is None or n > best:
            best = n
    return best


def _callees(addr, body, flags):
    from elftools.elf.elffile import ELFFile
    import gen_leaves as gl
    got, masks = gl.compile_fn(addr, body, extra_flags=flags)
    if got is None:
        return []
    op = os.path.join(os.environ["LEAF_TMPDIR"], "fn_%08X.o" % addr)
    names = {}
    with open(op, "rb") as f:
        elf = ELFFile(f)
        symtab = elf.get_section_by_name(".symtab")
        for i, s in enumerate(symtab.iter_symbols()):
            names[i] = s.name
        relsec = (elf.get_section_by_name(".rela.text")
                  or elf.get_section_by_name(".rel.text"))
        rels = {}
        if relsec:
            for rel in relsec.iter_relocations():
                rels[rel["r_offset"]] = rel["r_info_sym"]
    out = []
    for i in range(0, len(got) - 4, 4):
        if struct.unpack_from(">I", got, i)[0] == CRCLR:
            t = rels.get(i + 4)
            nm = names.get(t, "?") if t is not None else "?"
            if nm != "?" and nm not in out:
                out.append(nm)
    return out


def _score(addr, body, flags):
    sys.path.insert(0, "tools")
    from test_wip_drafts import test_one
    st, pct, err = test_one(addr, body, extra_flags=flags)
    if st == "FAIL":
        return None
    return pct


def _run(addr):
    sys.path.insert(0, "tools")
    import gen_leaves as gl
    path = "src/wip/fn_%08X.c" % addr
    text = open(path).read()
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    flags = gl.draft_flags(text) or None
    try:
        base = _score(addr, body, flags)
    except Exception as e:
        return "%08X  ERR %s" % (addr, e)
    if base is None:
        return "%08X  FAIL" % addr
    try:
        callees = _callees(addr, body, flags)
    except Exception:
        callees = []
    results = []
    for nm in callees:
        n = _count_args(body, nm)
        if n is None:
            continue
        for arity in {n, max(0, n - 1), n + 1, 0}:
            args = ", ".join(["s32"] * arity)
            for ret in ("s32", "void", "f32", "u32"):
                decl = "%s %s(%s);" % (ret, nm, args)
                try:
                    b = _insert(body, decl)
                    s = _score(addr, b, flags)
                except Exception:
                    continue
                if s is None:
                    continue
                if s > base + 0.05:
                    results.append((s, decl))
    results.sort(reverse=True)
    if not results:
        return "%08X  %.1f  (no proto helps; callees=%s)" % (addr, base, callees)
    return "%08X  %.1f -> %.1f  %s" % (addr, base, results[0][0], results[0][1])


def main():
    global ADDRS
    ADDRS = [int(a, 0) for a in sys.argv[1:]]
    if len(ADDRS) == 1:
        print(_run(ADDRS[0]))
        return
    with mp.Pool(min(6, len(ADDRS)), initializer=_init) as pool:
        for r in pool.imap_unordered(_run, ADDRS):
            print(r, flush=True)


if __name__ == "__main__":
    main()
