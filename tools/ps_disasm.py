#!/usr/bin/env python3
"""PS-aware PPC disassembler for Gekko DOLs.

tools/disasm.py stalls at the first paired-single word (capstone can't decode
Gekko PS ops) and MISLABELS opcode-4 words as VMX mnemonics. This tool decodes
all paired-single load/store forms manually — D-form psq_l/lu/st/stu AND the
X-form indexed ops psq_lx/psq_stx/psq_lux/psq_stux (M5.0t: these read as bogus
"xo5=6/7" through an A-form lens) — and prints remaining opcode-4 words as
`.word # op4` (A-form arithmetic/merges/scalar X-forms; hand-decode per
docs/parkings/06, or use tools/ps_diff.py whose dec() labels them all).
D-form fields per Gekko PIM: W=bit16, I=bits17-19 (GQR 0-7), d=signed 12-bit.

Usage: tools/ps_disasm.py <dol> <vaddr_hex> <count>
"""
import struct
import sys

from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

DOL_HEADER = 0x100


def read_dol(path):
    data = open(path, "rb").read()
    offs = struct.unpack_from(">18I", data, 0)
    addrs = struct.unpack_from(">18I", data, 0x48)
    sizes = struct.unpack_from(">18I", data, 0x90)
    return data, offs, addrs, sizes


def vaddr_to_offset(addrs, sizes, offs, vaddr):
    for i in range(18):
        if sizes[i] and addrs[i] <= vaddr < addrs[i] + sizes[i]:
            return offs[i] + (vaddr - addrs[i])
    return None


def bits(w, a, b):
    """Big-endian bitfield, MSB=bit 0."""
    return (w >> (31 - b)) & ((1 << (b - a + 1)) - 1)


def ps_str(w):
    """Decode a paired-single load/store word, or None."""
    op = bits(w, 0, 5)
    # X-form indexed quantized ops (opcode 4): w=bit21, XO=bits22-30.
    # (M5.0t, 2026-08-26: these read as bogus "xo5=6/7" through an A-form
    # lens — they are plain indexed pair loads/stores, emittable from C.)
    if op == 4:
        xo9 = bits(w, 22, 30)
        wb = bits(w, 21, 21)
        nm = {6: "psq_lx", 7: "psq_stx", 38: "psq_lux", 39: "psq_stux"}
        if xo9 in nm:
            fD, rA, rB = bits(w, 6, 10), bits(w, 11, 15), bits(w, 16, 20)
            upd = "+" if xo9 in (38, 39) else ""
            return "%s%s f%d, r%d+r%d, w=%d" % (nm[xo9], upd, fD, rA, rB, wb)
        return None
    if op not in (56, 57, 60, 61):  # psq_l psq_lu psq_st psq_stu
        return None
    fD = bits(w, 6, 10)
    rA = bits(w, 11, 15)
    W = bits(w, 16, 16)
    I = bits(w, 17, 19)
    d = bits(w, 20, 31)
    if d >= 2048:
        d -= 4096
    name = {56: "psq_l", 57: "psq_lu", 60: "psq_st", 61: "psq_stu"}[op]
    upd = "+" if op in (57, 61) else ""
    ra = "(r%d)" % rA if rA else ""
    return "%s%s f%d, %d%s, W%d, I%d" % (name, upd, fD, d, ra, W, I)


def main():
    if len(sys.argv) < 4:
        print(f"usage: {sys.argv[0]} <dol> <vaddr_hex> <count>")
        sys.exit(1)
    dol = sys.argv[1]
    start = int(sys.argv[2], 16)
    count = int(sys.argv[3])

    data, offs, addrs, sizes = read_dol(dol)
    md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
    for i in range(count):
        a = start + i * 4
        off = vaddr_to_offset(addrs, sizes, offs, a)
        if off is None:
            print("0x%08X: <not mapped>" % a)
            continue
        w = struct.unpack_from(">I", data, off)[0]
        s = ps_str(w)
        if s is None:
            if (w >> 26) == 4:
                # Primary opcode 4 = Gekko paired-single space. capstone has
                # NO Gekko PS tables and prints VMX mnemonics for these
                # words — always wrong (Gekko has no VMX). psq D-forms and
                # the X-form indexed ops are decoded above; remaining op-4
                # words are A-form arithmetic / merges / scalar X-forms —
                # hand-decode per docs/parkings/06 M5.0h/M5.0q/M5.0t, or use
                # tools/ps_diff.py's dec() which labels them all.
                s = ".word 0x%08x  # op4" % w
            else:
                got = list(md.disasm(struct.pack(">I", w), a))
                if got:
                    insn = got[0]
                    s = "%s %s" % (insn.mnemonic, insn.op_str)
                else:
                    s = ".word 0x%08x" % w
        print("0x%08X: %s" % (a, s))


if __name__ == "__main__":
    main()
