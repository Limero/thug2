#!/usr/bin/env python3
"""Find claims of doc-56 addendum 2: a literal argument that belongs in a LATER
slot than r3.

Retail keeps the caller's incoming r3/r4 and materialises the literal further up
(`li r5/r6/r7, LIT` immediately before the `bl`); ngccc, working from m2c's
argument list, puts the same literal in **r3**.  Detect purely from the object
code:

  * want has `li rN, LIT` with N in {5,6,7} within 2 instructions of a `bl`
  * got has the same `li r3, LIT` in the neighbourhood of its own `bl`

Prints one line per (draft, callee) so the result can be grouped by callee
address — a single callee usually means a whole family of drafts.

Usage: printf 'ADDR\\n...' | tools/venv/bin/python tools/late_literal_slot_scan.py
"""
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs  # noqa: E402

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.skipdata = True


_SYMS = None


def sym_name(addr):
    """symbols.txt address -> fn_XXXXXXXX / lbl_XXXXXXXX name (or None)."""
    global _SYMS
    if _SYMS is None:
        _SYMS = {}
        try:
            for line in open("config/G2TE52/symbols.txt"):
                m = re.match(r"^(\S+) = \.(?:text|init|data|rodata|sdata2?|bss|[^:]+):0x([0-9A-Fa-f]{8});", line)
                if m:
                    _SYMS[int(m.group(2), 16)] = m.group(1)
        except Exception:
            pass
    return _SYMS.get(addr)


def li_imm(ins):
    """(register, immediate) for `li rX, IMM`, else None."""
    if ins.mnemonic != "li":
        return None
    m = re.match(r"r(\d+), (-?0x[0-9a-f]+|-?\d+)", ins.op_str)
    if not m:
        return None
    return int(m.group(1)), int(m.group(2), 0)


def main():
    sizes = {}
    try:
        rep = json.load(open("build/G2TE52/report.json"))
        for u in rep.get("units", []):
            for fn in u.get("functions", []):
                sizes[int(fn["metadata"]["virtual_address"])] = int(fn["size"])
    except Exception:
        pass
    for line in sys.stdin:
        a = line.strip()
        if not a:
            continue
        addr = int(a, 0)
        fp = "src/wip/fn_%08X.c" % addr
        if not os.path.exists(fp):
            continue
        text = open(fp).read()
        body = "\n".join(l for l in text.splitlines()
                         if not l.startswith("//") and "types.h" not in l).strip()
        if not body:
            continue
        try:
            got, _ = gl.compile_fn(addr, body, extra_flags=gl.draft_flags(text) or None)
        except Exception:
            continue
        if not got:
            continue
        size = sizes.get(addr) or len(got)
        base = gl.t_off + (addr - gl.t_addr)
        orig = gl.d[base:base + size]
        w = list(md.disasm(orig, addr))
        g = list(md.disasm(got, addr))
        # literals ngccc put in r3 AND immediately passed to a call
        got_r3_call = set()
        for k, ins in enumerate(g[:-1]):
            v = li_imm(ins)
            if v and v[0] == 3 and g[k + 1].mnemonic == "bl":
                got_r3_call.add(v[1])
        if not got_r3_call:
            continue
        for i, ins in enumerate(w[:-1]):
            v = li_imm(ins)
            if not v or v[0] < 5:
                continue
            if w[i + 1].mnemonic != "bl":        # must be passed immediately
                continue
            if v[1] not in got_r3_call:
                continue
            callee = w[i + 1].op_str.lstrip("#")
            try:
                cname = sym_name(int(callee, 16))
            except Exception:
                cname = callee
            # source-level confirmation: the draft passes this literal as the
            # callee's ONLY argument
            if cname and not re.search(
                    re.escape(cname) + r"\s*\(\s*-?(0x[0-9A-Fa-f]+|\d+)\s*\)", body):
                continue
            print("0x%08X callee=%s(%s) lit=%d want_r%d" % (addr, cname, callee, v[1], v[0]))


if __name__ == "__main__":
    main()
