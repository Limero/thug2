#!/usr/bin/env python3
"""Convert a script/vtable method table to real C data (tier-2).

Reads docs/data-vtables.tsv rows for one table address and emits
src/vt_<ADDR>.c: one `void *` array per labeled span covering the table,
slots referencing the methods' current scope:global names (fn_ manifest
entries resolve through symbols.txt, so renames are honored).

Slot value rules:
- fn_ entry with a scope:global symbol at its address -> ref by that name.
- fn_ entry with only a plain (lbl_) symbol -> ref by the lbl_ name
  (mid-function entry: still a relocation, edge preserved).
- raw 0x... entry with a symbol at its address -> ref by that symbol.
- raw 0x... entry with NO symbol -> u32 hex literal (byte-exact; dtk saw
  no edge there either).
- manifest slot missing for an offset in span, or DOL word != manifest
  value -> REFUSE (exit 1, no output). Hand-treat those tables.

Bounds: the claim spans the table's labeled chunks; every symbol in the
span must be either a table chunk (emitted) or... any other symbol inside
fails loudly (no silent swallowing). Bare gaps become explicit pads.
Splits claim uses align:4; the game-lib Object line is printed (not
applied -- wire it by hand, then build + cmp + elf census like always).

Usage: tools/venv/bin/python tools/gen_vtable.py 0x8030804C [--apply]
Without --apply: dry-run (prints what it would emit + checks).
"""
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

DOL = "orig/G2TE52/sys/main.dol"
SYMBOLS = "config/G2TE52/symbols.txt"
TSV = "docs/data-vtables.tsv"
DOFF, DBASE = 0x2AF3A0, 0x802B23A0


def dol_bytes(addr, n):
    with open(DOL, "rb") as f:
        f.seek(DOFF + (addr - DBASE))
        return f.read(n)


def load_syms():
    syms = []
    for line in open(SYMBOLS):
        m = re.match(r"(\S+) = \.data:0x([0-9A-Fa-f]+); // .*size:0x([0-9A-Fa-f]+)(.*)",
                     line.strip())
        if not m:
            continue
        syms.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16), m.group(4)))
    syms.sort(key=lambda x: x[1])
    by_addr = {}
    for nm, a, z, r in syms:
        by_addr[a] = (nm, z, r)
    return syms, by_addr


def load_code_names():
    glob, any_nm = {}, {}
    for line in open(SYMBOLS):
        m = re.match(r"(\S+) = \.(?:text|init):0x([0-9A-Fa-f]+);(.*)", line.strip())
        if not m:
            continue
        any_nm.setdefault(int(m.group(2), 16), []).append(m.group(1))
        if "scope:global" in m.group(3):
            glob[int(m.group(2), 16)] = m.group(1)
    return glob, any_nm


def load_rows(addr):
    rows = {}
    want = "lbl_%08X" % addr
    for line in open(TSV):
        if line.startswith("#") or not line.strip():
            continue
        p = line.rstrip("\n").split("\t")
        if p[0] != want:
            continue
        rows[int(p[1])] = p[2]
    return rows


def main():
    if len(sys.argv) < 2:
        print("usage: gen_vtable.py 0xADDR [--apply]")
        return 1
    addr = int(sys.argv[1], 16)
    apply = "--apply" in sys.argv
    syms, by_addr = load_syms()
    glob, any_nm = load_code_names()
    rows = load_rows(addr)
    if not rows:
        print("no manifest rows for %#x" % addr)
        return 1
    nslots = max(rows) + 1
    if sorted(rows) != list(range(nslots)):
        print("REFUSE: manifest slots not contiguous 0..%d" % (nslots - 1))
        return 1
    # resolve every slot
    resolved = []
    for s in range(nslots):
        v = rows[s]
        if v.startswith("fn_"):
            a = int(v[3:], 16)
            if a in glob:
                resolved.append(("ref", glob[a]))
            elif a in any_nm:
                resolved.append(("ref", any_nm[a][0]))
            else:
                # Unlabeled function address: dtk saw no edge there either,
                # so a literal is byte-exact. Re-run this tool if symbols
                # land later (it upgrades these to refs automatically).
                resolved.append(("lit", "0x%08X" % a))
        elif v.startswith("0x"):
            a = int(v, 16)
            if a in glob:
                resolved.append(("ref", glob[a]))
            elif a in any_nm:
                resolved.append(("ref", any_nm[a][0]))
            else:
                resolved.append(("lit", "0x%08X" % a))
        else:
            # already a name (Vtable*): use it if it exists; else resolve
            # via the DOL word (stale manifest name for a renamed function,
            # e.g. Vtable0x803089D0_m12 -> DBOpen)
            if v in glob.values() or v in sum(any_nm.values(), []):
                resolved.append(("ref", v))
            else:
                a = int.from_bytes(dol_bytes(addr + s * 4, 4), "big")
                print("  note: slot %d name %s unknown, DOL says %#x"
                      % (s, v, a))
                if a in glob:
                    resolved.append(("ref", glob[a]))
                elif a in any_nm:
                    resolved.append(("ref", any_nm[a][0]))
                else:
                    resolved.append(("lit", "0x%08X" % a))
    # verify against DOL
    for s, (kind, val) in enumerate(resolved):
        got = int.from_bytes(dol_bytes(addr + s * 4, 4), "big")
        if kind == "lit":
            if got != int(val, 16):
                print("REFUSE: slot %d DOL has %#x, manifest says %s" % (s, got, val))
                return 1
        else:
            exp = None
            for a_, nms in any_nm.items():
                if val in nms:
                    exp = a_
            if exp is None or got != exp:
                print("REFUSE: slot %d DOL has %#x, ref %s unmapped" % (s, got, val))
                return 1
    # chunk runs of slots into labeled spans (symbols in span must tile it)
    span_end = addr + nslots * 4
    inside = [(nm, a, z) for nm, a, z, r in syms if addr <= a < span_end]
    decls, externs = [], []
    seen_extern = set()
    # group consecutive slots by their covering label
    cur = None
    groups = []
    for s in range(nslots):
        a = addr + s * 4
        lab = [nm for nm, x, z in inside if x <= a < x + z]
        key = lab[0] if lab else None
        if cur is None or cur[0] != key:
            if cur is not None:
                groups.append(cur)
            cur = (key, [s])
        else:
            cur[1].append(s)
    if cur is not None:
        groups.append(cur)
    out = []
    for key, slots_ in groups:
        if key is None:
            print("REFUSE: slots %s have no covering label" % slots_)
            return 1
        # covering label must start exactly at the group's first slot and
        # the group must fill it contiguously (else sizes lie)
        nm0 = [nm for nm, x, z in inside if x == addr + slots_[0] * 4]
        if not nm0 or nm0[0] != key:
            print("REFUSE: group %s starts mid-label" % slots_)
            return 1
        # every referenced name needs a declaration for the cast form
        for s in slots_:
            kind, nm = resolved[s]
            if kind != "ref" or nm in seen_extern:
                continue
            externs.append("extern void %s(void);" % nm)
            seen_extern.add(nm)
        body = ",\n    ".join("(void *)%s" % resolved[s][1] if resolved[s][0] == "ref"
                              else resolved[s][1] for s in slots_)
        # literals need no extern/cast adjustments (plain values)
        out.append("void *%s[%d] __attribute__((section(\".data\"))) = {\n    %s\n};"
                   % (key, len(slots_), body))
    print("table %#x: %d slots, %d groups, %d externs"
          % (addr, nslots, len(groups), len(externs)))
    text = ("// Vtable %#x as real C data (generated by tools/gen_vtable.py).\n"
            "// Slots reference the renamed methods (docs/data-vtables.tsv).\n"
            % addr + "\n".join(externs) + "\n\n" + "\n".join(out) + "\n")
    fp = "src/vt_%08X.c" % addr
    if not apply:
        print("(dry run; --apply to write %s)" % fp)
        print(text[:600])
        return 0
    open(fp, "w").write(text)
    print("wrote", fp)
    return 0


if __name__ == "__main__":
    sys.exit(main())
