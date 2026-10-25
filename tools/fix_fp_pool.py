#!/usr/bin/env python3
"""Retarget ngccc FP constant pools out of .rodata into existing DOL symbols.

ngccc synthesizes the magic constants of int->double / float->u32 casts
(0x4330000080000000, 0x4330000000000000, 0x41E0000000000000, ...) into each
object's .rodata. The game's DOL already holds those exact doubles in its
.rodata2 region with lbl_ symbols, and each function's original bytes point at
one of those addresses. This script retargets each .rodata HA/LO reloc pair to
the lbl_ symbol at the address the ORIGINAL DOL bytes reference, then zeroes
the .rodata section — keeping the promoted function text-only and byte-exact.

No-op (exit 0) when the object has no .rodata, or no .text (data-only
objects like src/rd_*.c carry real game data in .rodata and never pool
constants). Fails loudly (exit 1) when a pool constant resolves to an
address with no lbl_ symbol.

Usage: fix_fp_pool.py <object> [<output>]   (default: rewrite in place)
The object's path must contain the fn_XXXXXXXX function name (as the build's
build/G2TE52/src/fn_XXXXXXXX.o paths do) so the original bytes can be read.
"""
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DOL = f"{ROOT}/orig/G2TE52/sys/main.dol"

R_PPC_ADDR16_HA = 6
R_PPC_ADDR16_LO = 4

# DOL headers: sec 1 = .text, sec 7 = rodata, sec 8 = rodata2
_d = open(DOL, "rb").read()
_offs = struct.unpack_from(">18I", _d, 0)
_addrs = struct.unpack_from(">18I", _d, 0x48)
_sizes = struct.unpack_from(">18I", _d, 0x90)

SYMS = {}
_symp = f"{ROOT}/config/G2TE52/symbols.txt"
if os.path.isfile(_symp):
    for _ln in open(_symp):
        _m = re.match(
            r"(lbl_[0-9A-Fa-f]{8}) = \.(rodata|rodata2|data|sdata|sdata2|bss|sbss):0x([0-9A-Fa-f]+)",
            _ln)
        if _m:
            SYMS[int(_m.group(3), 16)] = _m.group(1)


def getstr(tab, off):
    e = tab.find(b"\0", off)
    return tab[off:e].decode()


def dol_word(addr):
    """32-bit instruction word from the original DOL .text at VA addr."""
    off = _offs[1] + (addr - _addrs[1])
    return struct.unpack_from(">I", _d, off)[0]


def original_target(addr):
    """Address the original DOL bytes at VA `addr` reference via lis+disp.

    The instruction at `addr` is expected to be either `lis rX, HA` (opcode
    0x3C00 | rX<<16) or a load with `disp(rX)`; both encode the 16-bit pieces
    of a lbl_ address in .rodata2. Returns the full 32-bit address.
    """
    w = dol_word(addr)
    op = w >> 26
    if op == 15:  # addi/addis family? 15 = addis (lis)
        ra = (w >> 16) & 0x1F
        imm = w & 0xFFFF
        # find the paired disp instruction within +-8 words
        for delta in (4, -4, 8, -8, 12, -12, 16, -16, 0):
            try:
                w2 = dol_word(addr + delta)
            except Exception:
                continue
            op2 = w2 >> 26
            if op2 in (48, 50, 34, 40, 32, 36, 44, 46, 56):  # lfd/lfs/lwz/lbz/lhz/stw...
                ra2 = (w2 >> 16) & 0x1F
                if ra2 == ra:
                    disp = w2 & 0xFFFF
                    if disp & 0x8000:
                        disp -= 0x10000
                    return ((imm << 16) + disp) & 0xFFFFFFFF
            if op2 == 14:  # addi
                ra2 = (w2 >> 16) & 0x1F
                if ra2 == ra:
                    disp = w2 & 0xFFFF
                    if disp & 0x8000:
                        disp -= 0x10000
                    return ((imm << 16) + disp) & 0xFFFFFFFF
    # maybe the instruction IS the load: find its own disp; need base from lis
    return None


def original_target_from_pair(addr_ha, addr_lo):
    """Compute the referenced address from the HA and LO instructions."""
    try:
        wha = dol_word(addr_ha)
        wlo = dol_word(addr_lo)
    except Exception:
        return None
    if (wha >> 26) != 15:  # must be lis
        return None
    ha = wha & 0xFFFF
    lo = wlo & 0xFFFF
    if lo & 0x8000:
        lo -= 0x10000
    return ((ha << 16) + lo) & 0xFFFFFFFF


def label_for_addr(va):
    """lbl_ symbol name at exact DOL address, or None."""
    if va in SYMS:
        return SYMS[va]
    # allow the generic lbl_ synthesized name if the auto-asm defines it
    name = "lbl_%08X" % va
    return name if name in SYMS.values() else None


def fixup(path, out_path):
    d = bytearray(open(path, "rb").read())
    e_shoff = struct.unpack_from(">I", d, 0x20)[0]
    e_shentsize = struct.unpack_from(">H", d, 0x2E)[0]
    e_shnum = struct.unpack_from(">H", d, 0x30)[0]
    e_shstrndx = struct.unpack_from(">H", d, 0x32)[0]
    shdrs = [list(struct.unpack_from(">IIIIIIIIII", d, e_shoff + i * e_shentsize))
             for i in range(e_shnum)]
    shstr_data = bytes(d[shdrs[e_shstrndx][4]:shdrs[e_shstrndx][4] + shdrs[e_shstrndx][5]])
    names = [getstr(shstr_data, sh[0]) for sh in shdrs]

    if ".rodata" not in names:
        return 0
    rodata_i = names.index(".rodata")
    if shdrs[rodata_i][5] == 0:
        return 0

    rel_i = names.index(".rela.text") if ".rela.text" in names else (
        names.index(".rel.text") if ".rel.text" in names else None)
    symtab_i = names.index(".symtab")
    strtab_i = names.index(".strtab")
    if rel_i is None:
        if ".text" not in names:
            return 0  # data-only object (e.g. src/rd_*.c): no calls, so no
            # pool constants to retarget; its .rodata holds real game data
        print(f"fix_fp_pool: {path}: .rodata present but no reloc section", file=sys.stderr)
        return 1

    # function address from the object filename (build/G2TE52/src/fn_XXXXXXXX.o)
    m = re.search(r"fn_([0-9A-Fa-f]{8})", os.path.basename(path))
    if not m:
        print(f"fix_fp_pool: {path}: cannot determine function address from name",
              file=sys.stderr)
        return 1
    fn_addr = int(m.group(1), 16)

    rel = shdrs[rel_i]
    rel_data = bytearray(bytes(d[rel[4]:rel[4] + rel[5]]))
    entsize = rel[9] or 12
    n_rel = rel[5] // entsize

    sym_data = bytes(d[shdrs[symtab_i][4]:shdrs[symtab_i][4] + shdrs[symtab_i][5]])
    n_syms = shdrs[symtab_i][5] // 16
    rodata_sym = None
    for i in range(n_syms):
        st = struct.unpack_from(">IIIBBH", sym_data, i * 16)
        if st[5] == rodata_i and st[3] == 0x03:
            rodata_sym = i
    assert rodata_sym is not None, f"{path}: no .rodata section symbol"

    # collect reloc entries against .rodata
    relocs = []  # (reloc_index, roff, type, addend)
    for i in range(n_rel):
        base = i * entsize
        if entsize == 12:
            roff, rinfo, radd = struct.unpack_from(">IIi", rel_data, base)
        else:
            roff, rinfo = struct.unpack_from(">II", rel_data, base)
            radd = 0
        if (rinfo >> 8) == rodata_sym:
            relocs.append((i, roff, rinfo & 0xFF, radd))
    if not relocs:
        print(f"fix_fp_pool: {path}: .rodata present but no HA/LO relocs — leaving as-is",
              file=sys.stderr)
        return 1

    # ---- group relocs into pool SITES ------------------------------------------------
    # A "site" is one pool ADDRESS (identified by its .rodata addend = byte offset
    # into the pool), and it may carry ANY number of HA and LO relocs.
    #
    # The earlier version of this code paired "each HA with the first unused LO
    # within 0x40 bytes".  That breaks in two real shapes, both seen failing
    # promotions with a clean 0x10000-page / 2-byte skew (recipes §6bp item 2):
    #   (a) ONE address used by BOTH an `lfd`/`lfs` AND a separate `addi`
    #       (`fn_80120824`: `lfd r0,0xD820(r9)` + `addi r9,r9,0xD820`).  The
    #       second LO was paired with the NEXT site's HA and retargeted to a
    #       completely different label.
    #   (b) ngccc CSEs the `lis` across uses, so ONE `lis` (HA) can feed TWO or
    #       more LO relocs (`fn_801227CC`: one HA, two LOs).  Only the first LO
    #       got a label; the leftover LO kept pointing at the now-EMPTYED
    #       `.rodata`, which the linker resolves against `.rodata+0`.
    #
    # Keying on the pool ADDEND fixes both: HA and LO for the same pool address
    # always share it, it is unique per pool entry, and it does not care how
    # many relocs reference that entry.  We then resolve the site's ORIGINAL
    # DOL address once (from any HA/LO instruction pair in the group) and
    # retarget every reloc in the group to that one label.
    by_addend = {}
    for (i, roff, typ, radd) in relocs:
        by_addend.setdefault(radd, []).append((i, roff, typ))

    sites = []  # (label, [(reloc_idx, roff), ...])
    for radd in sorted(by_addend):
        grp = sorted(by_addend[radd], key=lambda t: t[1])
        ha = [(i, roff) for (i, roff, typ) in grp if typ == R_PPC_ADDR16_HA]
        lo = [(i, roff) for (i, roff, typ) in grp if typ == R_PPC_ADDR16_LO]
        if not ha and not lo:
            continue
        if not ha or not lo:
            print(f"fix_fp_pool: {path}: pool slot +{radd:#x} has "
                  f"{len(ha)} HA / {len(lo)} LO reloc(s) — cannot resolve target",
                  file=sys.stderr)
            return 1
        # Resolve the original target from the first HA and the first LO that
        # sits AFTER it (that is the lis->load pair in program order).
        va = None
        for (_hi, hoff) in ha:
            hinsn = (hoff - 2) & ~3
            for (_li, loff) in lo:
                linsn = (loff - 2) & ~3
                if linsn <= hinsn:
                    continue
                va = original_target_from_pair(fn_addr + hinsn, fn_addr + linsn)
                if va is not None:
                    break
            if va is not None:
                break
        if va is None:
            print(f"fix_fp_pool: {path}: cannot resolve original target for pool "
                  f"slot +{radd:#x}", file=sys.stderr)
            return 1
        lbl = label_for_addr(va)
        if lbl is None:
            print(f"fix_fp_pool: {path}: no lbl_ symbol at original target {va:#x}",
                  file=sys.stderr)
            return 1
        sites.append((lbl, ha + lo))
    if not sites:
        print(f"fix_fp_pool: {path}: no HA/LO pairs resolved", file=sys.stderr)
        return 1

    print(f"fix_fp_pool: {os.path.basename(path)}: {len(sites)} pool site(s) -> "
          + ", ".join(lbl for (lbl, _rels) in sites))

    # ---- add symbols for each distinct label ----
    str_data = bytes(d[shdrs[strtab_i][4]:shdrs[strtab_i][4] + shdrs[strtab_i][5]])
    new_str = bytearray(str_data)
    sym_idx_of = {}
    for (lbl, _rels) in sites:
        if lbl not in sym_idx_of:
            name_off = len(new_str)
            new_str += lbl.encode() + b"\0"
            sym_idx_of[lbl] = n_syms + len(sym_idx_of)
    add_syms = b"".join(
        struct.pack(">IIIBBH", new_str.find(lbl.encode() + b"\0"), 0, 0, 0x10, 0, 0)
        for lbl in sym_idx_of)
    new_symtab = sym_data + add_syms

    for (lbl, rels) in sites:
        new_sym = sym_idx_of[lbl]
        for (ri, roff2) in rels:
            base = ri * entsize
            if entsize == 12:
                roffv, rinfo, radd = struct.unpack_from(">IIi", rel_data, base)
                struct.pack_into(">IIi", rel_data, base, roffv,
                                 (new_sym << 8) | (rinfo & 0xFF), 0)
            else:
                roffv, rinfo = struct.unpack_from(">II", rel_data, base)
                struct.pack_into(">II", rel_data, base, roffv,
                                 (new_sym << 8) | (rinfo & 0xFF))

    # ---- rebuild the file (preserve section order by original file offset) ----
    order = sorted(range(1, e_shnum), key=lambda i: shdrs[i][4])
    new_symtab_len = len(new_symtab)
    new_str_len = len(new_str)

    def align_up(v, a):
        return (v + a - 1) & ~(a - 1) if a else v

    out = bytearray(bytes(d[:0x34]))
    cur = 0x34
    new_offsets = {}
    for i in order:
        sh = shdrs[i]
        align = sh[6]
        if i == symtab_i:
            content, size = new_symtab, new_symtab_len
        elif i == strtab_i:
            content, size = new_str, new_str_len
        elif i == rodata_i:
            content, size = b"", 0
        elif i == rel_i:
            content, size = bytes(rel_data), len(rel_data)
        else:
            content, size = bytes(d[sh[4]:sh[4] + sh[5]]), sh[5]
        if not content and not size:
            new_offsets[i] = cur
            continue
        cur = align_up(cur, align)
        out += b"\0" * (cur - len(out))
        out += content
        new_offsets[i] = cur
        cur += size
    new_shdrs = []
    for i, sh in enumerate(shdrs):
        sh = list(sh)
        if i == symtab_i:
            sh[4], sh[5] = new_offsets[i], new_symtab_len
        elif i == strtab_i:
            sh[4], sh[5] = new_offsets[i], new_str_len
        elif i == rodata_i:
            sh[4], sh[5] = new_offsets[i], 0
        elif i == 0:
            pass
        else:
            sh[4] = new_offsets[i]
        new_shdrs.append(struct.pack(">IIIIIIIIII", *sh))
    shdrs_off = align_up(len(out), e_shentsize)
    out += b"\0" * (shdrs_off - len(out))
    out += b"".join(new_shdrs)
    struct.pack_into(">I", out, 0x20, shdrs_off)
    with open(out_path, "wb") as f:
        f.write(bytes(out))
    print(f"fix_fp_pool: wrote {out_path} ({len(out)}B)")
    return 0


def main():
    path = sys.argv[1]
    out = sys.argv[2] if len(sys.argv) > 2 else path
    sys.exit(fixup(path, out))


if __name__ == "__main__":
    main()
