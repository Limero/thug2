#!/usr/bin/env python3
"""Build the Tier B string-xref table (plan section 8, Tier B).

For every string present verbatim in BOTH the THUG2 DOL (.rodata2) and the
Wii ELF (.rodata), finds the functions referencing it on each side by
scanning for lis + address-use pairs (addi/ori/load/store off the lis
register within a 12-instruction window) and attributes each hit to its
containing function. Emits docs/thpg-string-xrefs.tsv:

  string | thug2_addr | thug2_funcs | wii_addr | wii_funcs

Only same-string + size/shape-compatible pairs graduate to rename proposals
(see plan section 4) — this table is evidence, not renames.

Wii-side recall limitation (measured): direct lis+addi references resolve
for a minority of shared strings; the Wii compiler-held string bases
(mr-copied address webs, table-driven loads) are not covered. Missing Wii
callers are a scanner gap, NOT proof of no reference — never treat an empty
wii_funcs cell as negative evidence.

Usage:
  tools/venv/bin/python tools/build_thpg_string_xrefs.py --dol DOL \
      --elf ELF --map MAP [--out docs/thpg-string-xrefs.tsv]
"""
import argparse
import collections
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROW_RE = re.compile(r"\s*\d+\s+([0-9a-fA-F]+)\s+(\d+)\s+(.*?)\s{2,}(.*)$")
SYM_RE = re.compile(r"(lbl_[0-9A-F]+) = \.rodata2:(0x[0-9A-Fa-f]+);.*data:string")
FUNC_RE = re.compile(r"(\S+)\s*=\s*\.text:(0x[0-9A-Fa-f]+);\s*//\s*type:function\s+size:0x([0-9A-Fa-f]+)")


def dol_sections(dol_bytes):
    to = struct.unpack(">7I", dol_bytes[0:28])
    ta = struct.unpack(">7I", dol_bytes[72:100])
    ts = struct.unpack(">7I", dol_bytes[144:172])
    do = struct.unpack(">11I", dol_bytes[28:72])
    da = struct.unpack(">11I", dol_bytes[100:144])
    ds = struct.unpack(">11I", dol_bytes[172:216])
    return list(zip(to, ta, ts)) + list(zip(do, da, ds))


def section_bytes(sections, dol_bytes, addr, size):
    for off, base, length in sections:
        if base and base <= addr < base + length and addr + size <= base + length:
            return dol_bytes[off + addr - base:off + addr - base + size]
    return None


def read_cstring(data, off):
    end = data.find(b"\x00", off)
    if end < 0:
        return None
    try:
        s = data[off:end].decode("ascii")
    except UnicodeDecodeError:
        return None
    if s and all(32 <= ord(c) < 127 for c in s):
        return s
    return None


def find_refs(code, base, targets, sections=(), sda_base=None, sda2_base=None):
    """Set of target addrs referenced (capstone).

    Covers absolute lis + low-half use, mr/or-copied lis pages, small-data
    access (lwz/addi off r13/r2), AND pointer-table indirection (lis page +
    lwz/lwzu of a table entry, then lwz of the string pointer out of the
    table), resolved by reading table words from `sections` ([(vaddr, bytes)]
    link-time image, ADDR32-relocated). Unmapped reads miss silently; every
    candidate is checked against `targets`, so no false hit.

    Recall reality (measured): the table idiom decodes correctly, but the
    rodata tables it reads are zero in-file (runtime-filled or non-string
    data) — table resolution adds nothing today. Direct + relocated-table
    coverage stands at 20 Wii strings; most Wii string traffic flows through
    runtime pointers the static scan cannot see. Empty `wii_funcs` is a
    scanner gap, never negative evidence.
    """
    from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN
    cs = Cs(CS_ARCH_PPC, CS_MODE_32 + CS_MODE_BIG_ENDIAN)

    def read_word(addr):
        for vaddr, data in sections:
            if vaddr <= addr < vaddr + len(data) - 3:
                b = data[addr - vaddr:addr - vaddr + 4]
                return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]
        return None

    ins = list(cs.disasm(code, base))
    hits = set()
    pending = {}  # reg -> (page_value, idx)
    alias = {}    # reg -> (loaded pointer value, idx)
    tbase = {}    # reg -> (table-entry address, idx) after lwzu
    two = re.compile(r"r(\d+),\s*(-?0x[0-9a-fA-F]+|-?\d+)$")
    three = re.compile(r"r(\d+),\s*r(\d+),\s*(-?0x[0-9a-fA-F]+|-?\d+)$")
    # mr rD,rS / or rD,rS,rS copy a lis-held page into another register
    # (CodeWarrior-held string bases); propagate the pending entry so a
    # later addi off the copy still resolves.
    copy = re.compile(r"r(\d+),\s*r(\d+)(?:,\s*r\d+)?$")
    # lwz/addi rD, disp(r13|r2)
    sd = re.compile(r"r(\d+),\s*(-?0x[0-9a-fA-F]+|-?\d+)\(r(13|2)\)$")
    # lwz/lwzu/stw/stwu rD, disp(rBase): table-displacement form.
    tdisp = re.compile(r"r(\d+),\s*(-?0x[0-9a-fA-F]+|-?\d+)\(r(\d+)\)$")
    for idx, i in enumerate(ins):
        m = two.match(i.op_str)
        if i.mnemonic == "lis" and m:
            pending[m.group(1)] = (int(m.group(2), 0) & 0xFFFF, idx)
            continue
        ms = sd.match(i.op_str)
        if ms and i.mnemonic in ("lwz", "addi", "lfs", "lbz", "lhz"):
            anchor = sda_base if ms.group(3) == "13" else sda2_base
            if anchor is not None:
                disp = int(ms.group(2), 0)
                disp = disp if disp < 0x8000 else disp - 0x10000
                tgt = (anchor + disp) & 0xFFFFFFFF
                if tgt in targets:
                    hits.add(tgt)
            continue
        mc = copy.match(i.op_str)
        if i.mnemonic in ("mr", "or") and mc and mc.group(2) in pending:
            pending[mc.group(1)] = (pending[mc.group(2)][0], idx)
            continue
        mt = tdisp.match(i.op_str)
        if (mt and i.mnemonic in ("lwz", "lwzu", "stw", "stwu", "lfs")
                and mt.group(3) in pending
                and idx - pending[mt.group(3)][1] <= 24):
            off = int(mt.group(2), 0)
            off = off if off < 0x8000 else off - 0x10000
            taddr = ((pending[mt.group(3)][0] << 16) + off) & 0xFFFFFFFF
            w = read_word(taddr)
            if w is not None:
                if w in targets:
                    hits.add(w)
                alias[mt.group(1)] = (w, idx)
                if i.mnemonic == "lwzu":
                    tbase[mt.group(3)] = (taddr, idx)
            continue
        m3 = three.match(i.op_str)
        if not m3:
            continue
        rd, ra, imm = m3.groups()
        lo = int(imm, 0)
        lo_s = lo if lo < 0x8000 else lo - 0x10000
        # Table-entry load off a lis page: lwz/lwzu rX, off(rPage).
        if (i.mnemonic in ("lwz", "lwzu") and ra in pending
                and idx - pending[ra][1] <= 24):
            taddr = ((pending[ra][0] << 16) + lo_s) & 0xFFFFFFFF
            w = read_word(taddr)
            if w is not None:
                if w in targets:
                    hits.add(w)
                alias[rd] = (w, idx)
                if i.mnemonic == "lwzu":
                    tbase[ra] = (taddr, idx)
            continue
        # String-pointer load out of a table: lwz rY, k(rTbl).
        if i.mnemonic == "lwz" and ra in tbase and idx - tbase[ra][1] <= 24:
            s = read_word((tbase[ra][0] + lo_s) & 0xFFFFFFFF)
            if s is not None:
                if s in targets:
                    hits.add(s)
                alias[rd] = (s, idx)
            continue
        if i.mnemonic == "lwz" and ra in alias and idx - alias[ra][1] <= 24:
            s = read_word((alias[ra][0] + lo_s) & 0xFFFFFFFF)
            if s is not None and s in targets:
                hits.add(s)
            continue
        # Plain absolute lis + low-half use.
        if ra in pending and idx - pending[ra][1] <= 12:
            hiv = pending[ra][0]
            tgt = ((hiv << 16) + lo_s) & 0xFFFFFFFF
            if tgt in targets:
                hits.add(tgt)
            if i.mnemonic == "ori":
                tgt2 = ((hiv << 16) | (lo & 0xFFFF)) & 0xFFFFFFFF
                if tgt2 in targets:
                    hits.add(tgt2)
        if len(pending) > 64:
            pending = {k: v for k, v in pending.items() if idx - v[1] <= 24}
    return hits


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--dol", required=True)
    ap.add_argument("--elf", required=True)
    ap.add_argument("--map", required=True)
    ap.add_argument("--out", default="docs/thpg-string-xrefs.tsv")
    args = ap.parse_args()

    from elftools.elf.elffile import ELFFile

    dol_bytes = open(args.dol, "rb").read()
    secs = dol_sections(dol_bytes)

    # THUG2 strings from data:string symbols, content read from the DOL.
    thug2 = {}
    n_sym = 0
    for line in open(os.path.join(ROOT, "config/G2TE52/symbols.txt")):
        m = SYM_RE.match(line)
        if not m:
            continue
        n_sym += 1
        addr = int(m.group(2), 16)
        for off, base, length in secs:
            if base and base <= addr < base + length:
                s = read_cstring(dol_bytes, off + addr - base)
                if s:
                    thug2.setdefault(s, []).append(addr)
                break
    print("thug2 data:string syms: %d, readable: %d" % (n_sym, len(thug2)))

    with open(args.elf, "rb") as f:
        elffile = ELFFile(f)
        text = elffile.get_section_by_name(".text")
        tv, td = text["sh_addr"], text.data()
        symtab = elffile.get_section_by_name(".symtab")
        sda = sda2 = None
        for sym in symtab.iter_symbols():
            if sym.name == "_SDA_BASE_":
                sda = sym["st_value"]
            elif sym.name == "_SDA2_BASE_":
                sda2 = sym["st_value"]
        esecs = []
        for sec in elffile.iter_sections():
            flags = sec["sh_flags"]
            if sec["sh_addr"] and flags & 0x2:  # SHF_ALLOC
                esecs.append((sec["sh_addr"], sec.data()))
        # Pre-apply ADDR32 data relocations: Wii pointer tables (string
        # addresses included) are zero in-file and relocated at load. Without
        # this, every table indirection reads 0 and silently misses.
        from elftools.elf.relocation import RelocationSection
        symtab_sec = elffile.get_section_by_name(".symtab")
        syms = list(symtab_sec.iter_symbols())
        esecs = [(v, bytearray(d)) for v, d in esecs]
        n_applied = 0
        for sec in elffile.iter_sections():
            if not isinstance(sec, RelocationSection):
                continue
            target = sec.name[5:] if sec.name.startswith(".rela") else None
            tgt_sec = elffile.get_section_by_name(target) if target else None
            if tgt_sec is None:
                continue
            buf = next((b for v, b in esecs if v == tgt_sec["sh_addr"]), None)
            if buf is None:
                continue
            base = tgt_sec["sh_addr"]
            for rel in sec.iter_relocations():
                if rel["r_info_type"] != 1:  # R_PPC_ADDR32 only
                    continue
                off = rel["r_offset"] - base
                if 0 <= off < len(buf) - 3:
                    val = (syms[rel["r_info_sym"]]["st_value"] + rel["r_addend"]) & 0xFFFFFFFF
                    buf[off:off + 4] = bytes([(val >> 24) & 0xFF, (val >> 16) & 0xFF,
                                              (val >> 8) & 0xFF, val & 0xFF])
                    n_applied += 1
        esecs = [(v, bytes(b)) for v, b in esecs]
        print("relocations applied: %d" % n_applied)

        def section_strings(names):
            out = {}
            for n in names:
                sec = elffile.get_section_by_name(n)
                if sec is None:
                    continue
                rv, rd = sec["sh_addr"], sec.data()
                i = 0
                while i < len(rd):
                    if 32 <= rd[i] < 127:
                        j = i
                        while j < len(rd) and 32 <= rd[j] < 127:
                            j += 1
                        if j < len(rd) and rd[j] == 0 and j - i >= 6:
                            out.setdefault(rd[i:j].decode("ascii"), []).append(rv + i)
                        i = max(j, i + 1)
                    else:
                        i += 1
            return out

        # String POINTERS live in .sdata2 for the most part; the characters
        # may sit in .rodata or .sdata — scan all three.
        wii = section_strings((".rodata", ".sdata", ".sdata2"))
    print("wii strings: %d (SDA_BASE=%s SDA2_BASE=%s)" % (
        len(wii),
        hex(sda) if sda is not None else None,
        hex(sda2) if sda2 is not None else None))

    shared = [(s, thug2[s], wii[s]) for s in thug2 if s in wii]
    print("shared distinct: %d" % len(shared))

    t_targets = set(a for _, t, _ in shared for a in t)
    tfuncs = []
    for line in open(os.path.join(ROOT, "config/G2TE52/symbols.txt")):
        m = FUNC_RE.match(line)
        if m:
            tfuncs.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
    t_hit = collections.defaultdict(set)
    dsecs = [(base, dol_bytes[off:off + length])
             for off, base, length in secs if base]
    for name, addr, size in tfuncs:
        code = section_bytes(secs, dol_bytes, addr, size)
        if code:
            for t in find_refs(code, addr, t_targets, sections=dsecs):
                t_hit[t].add(name)
    print("thug2 strings referenced: %d" % len(t_hit))

    w_targets = set(a for _, _, w in shared for a in w)
    lines = open(args.map, encoding="utf-8", errors="replace").read().splitlines()
    fi = next(i for i, l in enumerate(lines) if l.strip().startswith("FUNCTIONS"))
    wfuncs = []
    for line in lines[fi + 3:]:
        if not line.strip():
            break
        m = ROW_RE.match(line)
        if m:
            wfuncs.append((int(m.group(1), 16), int(m.group(2)),
                           m.group(3).strip(), m.group(4).strip()))
    w_hit = collections.defaultdict(set)
    for addr, size, unit, name in wfuncs:
        off = addr - tv
        if 0 <= off and off + size <= len(td):
            for t in find_refs(td[off:off + size], addr, w_targets,
                                sections=esecs,
                                sda_base=sda, sda2_base=sda2):
                w_hit[t].add("%s::%s" % (unit, name))
    print("wii strings referenced: %d" % len(w_hit))

    rows = []
    for s, t, w in sorted(shared):
        tf = sorted({f for a in t for f in t_hit.get(a, ())})
        wf = sorted({f for a in w for f in w_hit.get(a, ())})
        if tf or wf:
            rows.append((s, t, tf, w, wf))
    with open(args.out, "w", encoding="utf-8") as f:
        f.write("string\tthug2_addr\tthug2_funcs\twii_addr\twii_funcs\n")
        for s, t, tf, w, wf in rows:
            f.write("%s\t%s\t%s\t%s\t%s\n" % (
                s, ",".join("0x%X" % a for a in t), ",".join(tf),
                ",".join("0x%X" % a for a in w), ",".join(wf)))
    print("wrote %s (%d strings with any xref)" % (args.out, len(rows)))


if __name__ == "__main__":
    main()
