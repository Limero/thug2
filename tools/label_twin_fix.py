#!/usr/bin/env python3
"""Re-point a near-twin's DATA LABELS at the draft's own addresses.

Usage:
  tools/label_twin_fix.py <wipaddr> <twinaddr> [--write] [--flags "..."]

`tools/near_twin_scan.py` classifies differing words as `imm` / `reg` / `op`.
An `imm` pair is very often one global the compiler reached with

    lis   rD, hi            ;  lwz   r0, lo(rD)
    lis   rD, hi            ;  addi  rD, rD, lo     (or ori)

The two halves resolve to absolute addresses, and because the scorer **masks**
`lis/addi` relocations, a draft that still names the twin's global scores a
perfect 100% masked while linking to the WRONG data — it only fails at the
`promote_wip.py` DOL compare (or worse, silently reads the wrong buffer).

This tool decodes both addresses out of retail, maps them to `symbols.txt`
names, and rewrites every occurrence of the twin's name in the twin's source
with the draft's name. Symbol names in this tree encode their address
(`lbl_80305F60` == 0x80305F60), so the rewrite is exact and needs no guesswork.

Anything it cannot decode (a plain field offset, a float literal, a scheduling
difference) is reported and left alone — fix those by inspection.
"""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl          # noqa: E402
import scan_score as ss          # noqa: E402
import test_wip_drafts as tw     # noqa: E402

WANT = tw._want_sizes()
SYMS = {}
for line in open(os.path.join(gl.ROOT, "config/G2TE52/symbols.txt")):
    m = re.match(r"(\w+) = \.\w+:(0x[0-9A-Fa-f]+);", line)
    if m:
        SYMS[int(m.group(2), 16)] = m.group(1)


def words(addr, size):
    off = gl.t_off + (addr - gl.t_addr)
    b = gl.d[off:off + size]
    return [int.from_bytes(b[i:i + 4], "big") for i in range(0, len(b), 4)]


def s16(v):
    return v - 0x10000 if v & 0x8000 else v


def br_t(base, w, i):
    """Absolute target of the direct branch at word i of a function at `base`."""
    x = w[i]
    if (x >> 26) != 18:
        return None
    li = x & 0x03FFFFFC
    if li & 0x02000000:
        li -= 0x04000000
    return base + i * 4 + li


def bases(w):
    """Register -> high half, from every `lis rD,hi` in the function.

    Data bases are frequently set up once in the prologue and reused much later
    (an SDA-style `lwz r9,0x5F28(r31)` with r31 = lis 0x8030), so the base has to
    be tracked per register rather than looked for immediately before the
    access.  A stale entry is harmless here: both sides must decode to different
    addresses AND both addresses must have symbol names before anything is
    rewritten.
    """
    b = {}
    for x in w:
        if x >> 26 == 15:
            b[(x >> 21) & 31] = (x & 0xFFFF) << 16
    return b


D_FORM = (32, 33, 34, 40, 42, 44, 36, 37, 38, 48, 50, 52)


def address_at(w, i, base):
    """Absolute address touched by word i, or None.

    Handles the two shapes the compiler emits for `lbl_XXXXXXXX[..]` and
    `*(T *)lbl_XXXXXXXX`: a `lis rD,hi` immediately followed by the access using
    rD, and a bare D-form access/addi/ori through a register that an earlier
    `lis` set up.
    """
    x = w[i]
    op = x >> 26
    ra = (x >> 16) & 31
    if op == 15:                                    # lis rD,hi  (+ next word)
        rd = (x >> 21) & 31
        if i + 1 < len(w):
            nxt = w[i + 1]
            nop, nra = nxt >> 26, (nxt >> 16) & 31
            if nra == rd and nop in (14, 24) + D_FORM:
                top = (x & 0xFFFF) << 16
                return (top + s16(nxt & 0xFFFF) if nop in (14,) + D_FORM
                        else top + (nxt & 0xFFFF))
        return None
    if ra not in base:
        return None
    if op in D_FORM:                                # lwz/stw/lha/... rX,D(rA)
        return base[ra] + s16(x & 0xFFFF)
    if op == 14:                                    # addi rD,rA,lo
        return base[ra] + s16(x & 0xFFFF)
    if op == 24:                                    # ori rA,rS,lo
        return base[ra] + (x & 0xFFFF)
    return None


def main():
    one = int(sys.argv[1], 16)
    twin = int(sys.argv[2], 16)
    size = WANT.get(one) or WANT.get(twin)
    assert size, f"no known size for 0x{one:08X}/0x{twin:08X}"
    w = words(one, size)
    m = words(twin, size)
    diff = [i for i in range(min(len(w), len(m))) if w[i] != m[i]]
    mt, wt = bases(m), bases(w)

    subs = {}
    rest = []
    for k in diff:
        got = address_at(m, k, mt)
        want = address_at(w, k, wt)
        if got is not None and want is not None and got != want:
            na = SYMS.get(got, f"lbl_{got:08X}")
            nb = SYMS.get(want, f"lbl_{want:08X}")
            subs[k] = (got, na, want, nb)
            continue
        # A differing `bl` whose target also differs is a WRONG CALLEE — the
        # single most common reason a masked-100% twin still fails the linked
        # DOL (and, when the wrong object becomes unreferenced, the reason the
        # DOL comes out short instead).
        tg, tw_ = br_t(twin, m, k), br_t(one, w, k)
        if tg is not None and tw_ is not None and tg != tw_:
            na = SYMS.get(tg, f"fn_{tg:08X}")
            nb = SYMS.get(tw_, f"fn_{tw_:08X}")
            subs[k] = (tg, na, tw_, nb)
            continue
        rest.append(k)

    print(f"0x{one:08X} <- src/fn_{twin:08X}.c ({size}B): "
          f"{len(diff)} differing word(s), {len(subs)} symbol substitution(s)")
    for k, (ga, na, wa, nb) in sorted(subs.items()):
        kind = "callee" if (m[k] >> 26) == 18 else "label "
        print(f"  word {k:3d}  [{kind}] {na} ({ga:#010x})  ->  {nb} ({wa:#010x})")
    for k in rest:
        print(f"  word {k:3d}  got {m[k]:08X}  want {w[k]:08X}  (not an address pair)")

    path = os.path.join(gl.ROOT, "src", f"fn_{twin:08X}.c")
    txt = open(path).read()
    body = "\n".join(l for l in txt.splitlines()
                     if not l.startswith("//") and "types.h" not in l)
    body = re.sub(rf"\bfn_{twin:08X}\b", f"fn_{one:08X}", body)
    # A rename is one substitution no matter how many sites triggered it (the
    # same global is usually touched several times), so dedupe before rewriting
    # or the second site's presence check fails on an already-rewritten body.
    missing = []
    applied = set()
    for (ga, na, wa, nb) in subs.values():
        if (na, nb) in applied:
            continue
        applied.add((na, nb))
        if re.search(rf"\b{re.escape(na)}\b", body):
            body = re.sub(rf"\b{re.escape(na)}\b", nb, body)
        else:
            missing.append(na)

    s, p = ss.score(one, body, None)
    print(f"  score after label rewrite: {s} {p:.2f}%")
    if missing:
        print(f"  NOTE: twin source does not name {missing} literally "
              f"(named constant? check by inspection).")

    if "--write" in sys.argv:
        wpath = os.path.join(gl.ROOT, "src/wip", f"fn_{one:08X}.c")
        old = open(wpath).read()
        hdr = []
        for line in old.splitlines():
            if not line.startswith("//"):
                break
            hdr.append(line)
        open(wpath, "w").write("\n".join(hdr) + "\n" + body + "\n")
        print(f"  wrote {wpath}")


main()
