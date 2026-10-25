#!/usr/bin/env python3
"""Reloc-aware want/got diff:  reloc_diff.py 0xADDR body.c [words] [cflags...]

The masked compare behind tools/score_body.py blanks every relocation field
(`ffff0000` on a `lis`/`lwz` pair, `fc000003` on a branch), which is correct for
byte-exactness but hides *semantics*: a draft that stores two different globals
in the wrong order, or calls the same function with a different argument, still
scores 100% whenever the instruction shapes line up.  This tool prints, for each
instruction word:

  * the want word decoded from the DOL (with branch targets resolved to
    symbols.txt names — `bl 0x8003a754 -> fn_8003A754`),
  * the got word decoded from the compiled draft, annotated with the
    `.rela.text` SYMBOL each reloc points at (e.g. `stw r5, 0(r27) [lbl_803003E8@2:4]`),
    and with REL14/REL24 targets *resolved* to real addresses (got branch words
    come out of the object as placeholders — see fixup_branch below),
  * a leading `!!` when the masked compare finds a mismatch.

That makes "which global did this store aim at", "which callee is this", and
"did the draft swap two statements" readable directly.  Passing a word count
overrides the compare window (useful when splits.txt/symbols.txt disagree about
a function's size — see the fn_8007A9F8 note in WIP.md).
"""
import os
import struct
import sys
import bisect

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, f"{ROOT}/tools")
os.environ.setdefault("LEAF_TMPDIR", "/tmp/reloc_diff")
import gen_leaves as gl  # noqa: E402
import ps_diff  # noqa: E402
from elftools.elf.elffile import ELFFile  # noqa: E402
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs  # noqa: E402

MD = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)


def dec(w, a):
    return ps_diff.dec(w) or next(
        (f"{i.mnemonic} {i.op_str}" for i in MD.disasm(struct.pack(">I", w), a)), "?")


syms = []
for line in open(f"{ROOT}/config/G2TE52/symbols.txt"):
    if "=" not in line:
        continue
    name = line.split("=")[0].strip()
    try:
        value = int(line.split(":")[1].split(";")[0], 16)
    except (IndexError, ValueError):
        continue
    syms.append((value, name))
syms.sort()
SADDRS = [s[0] for s in syms]


def sym_at(value):
    i = bisect.bisect_right(SADDRS, value) - 1
    if i < 0:
        return None
    off = value - syms[i][0]
    return syms[i][1] + (f"+0x{off:x}" if off else "")


def reloc_map(addr):
    """{instruction offset in .text: [(symbol@halfword:type, type, value, addend), ...]}"""
    out = {}
    op = f"{os.environ['LEAF_TMPDIR']}/fn_{addr:08X}.o"
    with open(op, "rb") as f:
        elf = ELFFile(f)
        symtab = elf.get_section_by_name(".symtab")
        text_idx = elf.get_section_index(".text")
        relsec = (elf.get_section_by_name(".rela.text")
                  or elf.get_section_by_name(".rel.text"))
        if relsec:
            for rel in relsec.iter_relocations():
                off = rel["r_offset"]
                sym = symtab.get_symbol(rel["r_info_sym"])
                add = rel["r_addend"] if rel.is_RELA() else 0
                out.setdefault(off & ~3, []).append((
                    f"{sym.name}@{off & 3}:{rel['r_info_type']}",
                    rel["r_info_type"], sym, add, text_idx))
    return out


def fixup_branch(w, off, rels):
    """Resolve a branch word that carries a relocation to a target *inside*
    .text.  ngccc emits an R_PPC_REL14/REL24 relocation for EVERY internal
    branch (not just for external calls), and the BD/LI field left in the
    object is the *addend*, i.e. the target's .text offset written where a
    byte displacement belongs.  Decoding the raw object word therefore prints
    a bogus in-function target (the field is off by the instruction offset).
    The EABI result is `target = S + A`, so recompute the real displacement
    `A - P` here (off = P, the section-relative offset of the branch); without
    this the printed got target cannot be compared with the want target.
    Returns the word untouched for external/undefined symbols (their S is only
    known at link time)."""
    for _, typ, sym, add, text_idx in rels:
        if typ not in (10, 11) or sym["st_shndx"] != text_idx:
            continue
        disp = (sym["st_value"] + add) - off
        if typ == 11:  # R_PPC_REL14: BD lives in numeric bits 2..15
            return ((w & ~0x0000FFFC) | (((disp >> 2) & 0x3FFF) << 2)), sym
        return ((w & ~0x03FFFFFC) | (((disp >> 2) & 0x00FFFFFF) << 2)), sym
    return w, None


def main():
    addr = int(sys.argv[1], 0)
    body = open(sys.argv[2]).read()
    rest = sys.argv[3:]
    words = int(rest[0]) if rest and rest[0].isdigit() else 0
    flags = [a for a in rest if not a.isdigit()] or None
    got, masks = gl.compile_fn(addr, body, extra_flags=flags)
    if got is None:
        raise SystemExit(f"compile failed: {masks}")
    relmap = reloc_map(addr)
    n = words or len(got) // 4
    orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + n * 4]
    diffs = 0
    for i in range(n):
        a = addr + i * 4
        w = struct.unpack(">I", orig[i * 4:i * 4 + 4])[0]
        g = struct.unpack(">I", got[i * 4:i * 4 + 4])[0]
        mask = masks.get(i * 4, 0xFFFFFFFF)
        ok = (w & mask) == (g & mask)
        diffs += 0 if ok else 1
        # want-side branch target, named through symbols.txt
        note = ""
        opc = w >> 26
        if opc == 16 and (w & 2):
            d = w & 0xFFFC
            if d & 0x8000:
                d -= 0x10000
            note = f"-> {sym_at(a + d) or hex(a + d)}"
        elif opc == 18 and (w & 2):
            d = w & 0x03FFFFFC
            if d & 0x02000000:
                d -= 0x04000000
            note = f"-> {sym_at(a + d) or hex(a + d)}"
        rels = relmap.get(i * 4, ())
        rel = (" [" + ",".join(r[0] for r in rels) + "]") if rels else ""
        gdisp, gsym = fixup_branch(g, i * 4, rels)
        print(f"{'  ' if ok else '!!'} {a:08x} want {dec(w, a):<26} {note:<24} "
              f"got {dec(gdisp, a)}{rel}")
    print(f"# {n - diffs}/{n} words match under the reloc masks", file=sys.stderr)


if __name__ == "__main__":
    main()
