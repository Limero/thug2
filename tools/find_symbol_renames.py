#!/usr/bin/env python3
"""Propose retail names for unnamed (fn_*/lbl_*) DOL functions.

READ-ONLY. Applies nothing; prints a ranked table for hand verification.

WHY
---
`config/G2TE52/symbols.txt` still holds ~19k `fn_*`/`lbl_*` placeholders, but
the retail build's metadata is on disk: `docs/thpg-func-names.tsv` (unit, name,
size, folder evidence) and `docs/thpg-callgraph.tsv` (caller -> callee). A DOL
function can often be identified by the set of functions it CALLS, because the
project has already renamed every function it has matched.

METHOD
------
 1. For each unnamed function, collect the set of `bl` targets that are ALREADY
    named in symbols.txt (its "known callees").
 2. Score every retail candidate by Jaccard overlap of its callee set with that
    known set, gated on:
      - >= 2 shared callees,
      - callee jaccard >= MIN_JACCARD,
      - per-function size within SIZE_TOL (retail sizes come from other builds,
        so allow slack),
      - the proposed name not already used anywhere in symbols.txt.
 3. UNIT LOCK: the linker lays a unit's functions out contiguously, so a run of
    adjacent unnamed functions whose size profile matches one retail unit's
    mid-size functions is over-determined evidence. Sub-windows are tried
    because a tiny evidence-free function often sits at either end of a run.

CAPSTONE GOTCHAS (both cost real time -- do not regress them)
------------------------------------------------------------
  * `md.disasm()` STOPS at the first undecodable word. Code sections contain
    data pools / jump tables, so whole-section scans need `md.skipdata = True`
    or you silently see ~20 `bl` targets instead of ~44,000.
  * This capstone version has no `ins.op`; use `ins.operands[0]` and compare
    `op.type == PPC_OP_IMM` (`PPC_OP_IMM` is 2).

LANDMINE WHEN APPLYING A RENAME
--------------------------------
Renaming in symbols.txt ALONE BREAKS THE LINK. dtk emits auto-asm for unmatched
callers and generates their call expressions from symbols.txt, so the caller
starts referencing the NEW name while the object still defines the OLD one:

    mwldeppc.exe Linker Error: undefined: 'translate'
    Referenced from 'fn_80017128' in auto_01_80016EDC_text.o

To apply a rename you must touch all of:
  1. config/G2TE52/symbols.txt          (the name at the address)
  2. src/<file>.c                      (the DEFINITION's function name)
  3. every src/ caller (declaration + call sites, registered AND wip drafts)
  4. nothing in configure.py / splits.txt -- those track addresses, not names
Then verify `tools/ninja build/G2TE52/ok` still reports OK. Renaming never
changes emitted code, so the DOL must stay byte-identical.

Usage:  tools/venv/bin/python tools/find_symbol_renames.py [--singles N]
"""
import argparse
import bisect
import collections
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYMS = f"{ROOT}/config/G2TE52/symbols.txt"
DOL = f"{ROOT}/orig/G2TE52/sys/main.dol"
CALLGRAPH = f"{ROOT}/docs/thpg-callgraph.tsv"
TSV = f"{ROOT}/docs/thpg-func-names.tsv"

MIN_SIZE = 0x30        # ignore retail fns below this (tiny/inlined)
SIZE_TOL = 0.28        # per-function size tolerance
MIN_GROUP = 2          # unit-lock group size
MAX_GROUP = 8
MIN_JACCARD = 0.6
MIN_KNOWN = 2          # a member needs >= this many already-named callees
MAX_DOL_SIZE = 0x600   # don't disassemble anything bigger

sys.path.insert(0, f"{ROOT}/tools")
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs  # noqa: E402
from capstone.ppc import PPC_OP_IMM  # noqa: E402


def load_symbols():
    addr2name, addr2size = {}, {}
    with open(SYMS, errors="ignore") as f:
        for line in f:
            m = re.match(r"^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(\.\w+):0x([0-9A-Fa-f]+);"
                         r".*size:(0x[0-9A-Fa-f]+)", line)
            if m:
                addr2name[int(m.group(3), 16)] = m.group(1)
                addr2size[int(m.group(3), 16)] = int(m.group(4), 16)
    return addr2name, addr2size


class Dol:
    def __init__(self, path):
        self.d = open(path, "rb").read()
        self.offs = struct.unpack_from(">18I", self.d, 0)
        self.addrs = struct.unpack_from(">18I", self.d, 0x48)
        self.sizes = struct.unpack_from(">18I", self.d, 0x90)
        self.md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
        self.md.detail = True
        self.md.skipdata = True          # see module docstring
        # executable sections only; a bare address-range test also sweeps up
        # .data/.rodata labels, which have no callees at all
        self.code = [(self.offs[i], self.addrs[i], self.sizes[i])
                     for i in range(18)
                     if 0x80000000 <= self.addrs[i] < 0x80400000
                     and self.sizes[i] > 0]

    def is_code(self, v):
        return any(a <= v < a + s for _o, a, s in self.code)

    def offset(self, v):
        for o, a, s in self.code:
            if a <= v < a + s:
                return o + (v - a)
        return None


def load_retail():
    cg = collections.defaultdict(set)
    with open(CALLGRAPH, errors="ignore") as f:
        next(f, None)
        for line in f:
            p = line.rstrip("\n").split("\t")
            if len(p) < 2:
                continue
            cu, cn = p[0].split("::")[-2:]
            vu, vn = p[1].split("::")[-2:]
            if cn and vn:
                cg[(cu, cn)].add(vn)
    meta, unit_fns = {}, collections.defaultdict(list)
    cals = {}
    with open(TSV, errors="ignore") as f:
        next(f, None)
        for line in f:
            p = line.rstrip("\n").split("\t")
            if len(p) < 9:
                continue
            nm, unit = (p[2] or p[0]), p[3]
            if not nm or not unit:
                continue
            try:
                size = int(p[6])
            except ValueError:
                continue
            cal = frozenset(cg.get((unit, nm), ()))
            cals[(unit, nm)] = cal
            meta[(unit, nm)] = (p[4], p[5], size, int(p[8]))
            if size >= MIN_SIZE:
                unit_fns[unit].append((nm, size, cal))
    return meta, unit_fns, cals


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--singles", type=int, default=30,
                    help="how many singleton candidates to print")
    args = ap.parse_args()

    addr2name, addr2size = load_symbols()
    dol = Dol(DOL)
    meta, unit_fns, cals = load_retail()
    name_at = collections.defaultdict(list)
    for a, n in addr2name.items():
        name_at[n].append(a)

    unnamed = sorted(a for a, n in addr2name.items()
                     if n.startswith(("fn_", "lbl_")) and dol.is_code(a))
    print(f"unnamed code symbols: {len(unnamed)}")

    dcs_cache = {}

    def known_callees(a):
        if a not in dcs_cache:
            sz = addr2size.get(a, 0)
            out, o = set(), dol.offset(a)
            if o is not None and 0 < sz <= MAX_DOL_SIZE:
                for ins in dol.md.disasm(dol.d[o:o + sz], a):
                    if ins.mnemonic != "bl":
                        continue
                    ops = ins.operands
                    if not ops or ops[0].type != PPC_OP_IMM:
                        continue
                    t = ops[0].imm & 0xFFFFFFFF
                    if 0x80000000 <= t < 0x80400000 and t != a:
                        n = addr2name.get(t)
                        if n and not n.startswith(("fn_", "lbl_")):
                            out.add(n)
            dcs_cache[a] = frozenset(out)
        return dcs_cache[a]

    # ---- singleton candidates ------------------------------------------
    singles = []
    for a in unnamed:
        d = known_callees(a)
        if len(d) < MIN_KNOWN:
            continue
        dsz = addr2size.get(a, 0)
        for (unit, rname), (folder, ev, rsize, builds) in meta.items():
            if rname in name_at or not rsize:
                continue
            sd = abs(dsz - rsize) / rsize
            if sd > SIZE_TOL:
                continue
            rcs = cals.get((unit, rname), frozenset())
            if not rcs or len(d & rcs) < 2:
                continue
            j = len(d & rcs) / len(d | rcs)
            if j < MIN_JACCARD:
                continue
            singles.append((j, -sd, a, rname, unit, folder, ev, rsize, dsz,
                            builds, len(d & rcs), sorted(d & rcs)))
    singles.sort(reverse=True)
    print(f"\n=== SINGLETON CANDIDATES (j>={MIN_JACCARD}, >=2 shared) ===")
    for (j, nsd, a, rname, unit, folder, ev, rsize, dsz, builds, ov, sh) in \
            singles[:args.singles]:
        print(f"  0x{a:08X} {dsz:4d}B -> {rname:28s} j={j:.2f} ovl={ov} "
              f"retail={rsize}B {folder}/{ev} b={builds}")
        print(f"        [{unit}]  shared={sh[:5]}")

    # ---- unit locks -----------------------------------------------------
    runs, cur = [], []
    for a in sorted(addr2name):
        ok = (addr2name[a].startswith(("fn_", "lbl_"))
              and addr2size.get(a, 0) >= MIN_SIZE and dol.is_code(a))
        if not ok:
            if len(cur) >= MIN_GROUP:
                runs.append(cur)
            cur = []
            continue
        if cur and cur[-1][0] + cur[-1][1] != a:
            if len(cur) >= MIN_GROUP:
                runs.append(cur)
            cur = []
        cur.append((a, addr2size[a]))
    if len(cur) >= MIN_GROUP:
        runs.append(cur)
    print(f"\ncontiguous unnamed runs: {len(runs)}")

    def try_window(win, fns):
        if len(fns) < len(win):
            return None
        pairs = []
        for a, sz in win:
            best = None
            for nm, rsz, rcs in fns:
                if not rsz:
                    continue
                sd = abs(sz - rsz) / rsz
                if sd > SIZE_TOL:
                    continue
                d = known_callees(a)
                if len(d) < MIN_KNOWN or not rcs or len(d & rcs) < 2:
                    continue
                j = len(d & rcs) / len(d | rcs)
                if j < MIN_JACCARD:
                    continue
                if best is None or (j - 0.5 * sd) > best[0]:
                    best = (j - 0.5 * sd, nm, rsz, j, sd, len(d & rcs))
            if best is None:
                return None
            pairs.append((a, sz) + best[1:])
        if len({p[2] for p in pairs}) != len(pairs):
            return None                 # name reused inside one group
        if any(p[2] in name_at for p in pairs):
            return None                 # name already taken
        return pairs

    found = {}
    for run in runs:
        n = len(run)
        if n > 12:
            continue
        for L in range(min(n, MAX_GROUP), MIN_GROUP - 1, -1):
            for i in range(0, n - L + 1):
                for unit, fns in unit_fns.items():
                    if not (MIN_GROUP <= len(fns) <= L + 2):
                        continue
                    pairs = try_window(run[i:i + L], fns)
                    if pairs:
                        key = tuple(p[0] for p in pairs)
                        mj = sum(p[4] for p in pairs) / len(pairs)
                        if key not in found or mj > found[key][0]:
                            found[key] = (mj, L, unit, pairs)
    # keep only maximal groups
    results = [v for v in found.values()
               if not any({p[0] for p in v[3]} < set(k) for k in found)]
    results.sort(key=lambda r: (-r[0], -r[1]))
    print(f"\n=== UNIT LOCKS ({len(results)}) ===")
    for mj, L, unit, pairs in results[:25]:
        print(f"\n  {unit}  (n={L}, mean j={mj:.2f})")
        for (a, sz, nm, rsz, j, sd, ov) in pairs:
            print(f"    0x{a:08X} {sz:4d}B -> {nm:26s} retail={rsz:4d}B "
                  f"dsz={sd:.0%} j={j:.2f} ovl={ov}")
    print("\nNOTE: unit locks are the strongest signal, but greedy per-member "
          "assignment cannot split siblings with IDENTICAL callee sets (e.g. "
          "rotateX/rotateY). Break those by hand on a disambiguating argument.")


if __name__ == "__main__":
    main()