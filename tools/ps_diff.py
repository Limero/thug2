#!/usr/bin/env python3
"""diff_near.py for paired-single functions (-mps-float + PS/FP decoding).

diff_near.py can't decode psq_l/ps_* words and never passes -mps-float, so
every PS draft shows garbage there. This tool:
  - compiles the src/wip draft with gen_leaves.compile_fn(extra_flags=["-mps-float"])
    (extra flags may be appended: ps_diff.py 0xADDR [want_size] "FLAG1 FLAG2")
  - decodes opcode 4 (ps_sum0/muls0/madd/merge00/...), opcode 59 scalar-singles
    (fmadds/fmuls/fdivs — NOT paired-single) and psq loads/stores
  - prints want|got per word with relocation masking + a match score

Usage: tools/ps_diff.py <0xADDR> [want_size_bytes] [extra_flags] [--all]
"""
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs  # noqa: E402

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.detail = False


def bits(w, a, b):
    return (w >> (31 - b)) & ((1 << (b - a + 1)) - 1)


# ---------------------------------------------------------------------------
# Gekko A-form field layout (primary opcodes 4, 59, 63).
#
# FIX 2026-09-27: every field below was verified by compiler probes (one
# __builtin_ps_* / __asm__ mnemonic per TU, ngccc 3.9.3 -mps-float, each operand
# pinned to a distinct FPR via `register f32 x __asm__("fr13")`, encodings read
# back from .text).  The old code extracted the primary opcode as
# `bits(w, 0, 5)` == (w >> 26) & 0x1F, which TRUNCATES bit 31: opcodes 4 works
# by luck (bit31==0) but 56/57/60/61, 59 and 63 can never be produced, so the
# whole psq / scalar-singles / fmr-frsp half of this decoder was dead code.
#
#   primary opcode = bits 31-26      -> (w >> 26), 6 bits, NEVER w & 0x3F
#   frD            = bits 25-21
#   frA            = bits 20-16
#   frB            = bits 15-11
#   frC            = bits 10-6
#   xo5            = bits 5-1
#   Rc             = bit 0
#   XO10           = bits 10-1  ==  frC << 5 | xo5   (Gekko "10-bit" XO)
#
# XO10 is what makes the selector families decode as one number:
# merge00..11 = 16..19 << 5 | 16 = 528/560/592/624
# ps_mr/neg/abs/nabs = 2/1/8/4 << 5 | 8 = 72/40/264/136
# ---------------------------------------------------------------------------


def afields(w):
    """(frD, frA, frB, frC, xo5) -- args are bits() MSB-index positions."""
    return (bits(w, 6, 10),    # frD <- bits 25-21
            bits(w, 11, 15),   # frA <- bits 20-16
            bits(w, 16, 20),   # frB <- bits 15-11
            bits(w, 21, 25),   # frC <- bits 10-6
            bits(w, 26, 30))   # xo5 <- bits 5-1


def xo10(w):
    """Gekko extended opcode at bits 10-1 == frC<<5 | xo5."""
    return bits(w, 21, 30)


# frC is an op selector, not an FPR, for these two families:
#   xo5 == 8 : C = 1 ps_neg, 2 ps_mr, 4 ps_nabs, 8 ps_abs
#              (probe: ps_mr fr1,fr13 -> frC=2; the ps_mr words ngcasm emits for
#               the byte-identical src/fn_801B19DC.c agree: xo5=8, frC=2)
#   xo5 == 16: C = 16 merge00, 17 merge01, 18 merge10, 19 merge11
# (C == 0 is also spelled ps_mr by some references; the compiler never emits it,
#  so it is decoded as ps_mr to stay tolerant.)
PS_OP8 = {0: "ps_mr", 1: "ps_neg", 2: "ps_mr", 4: "ps_nabs", 8: "ps_abs"}
F_OP8 = {0: "fmr", 1: "fneg", 2: "fmr", 4: "fnabs", 8: "fabs"}
MERGE = {16: "ps_merge00", 17: "ps_merge01", 18: "ps_merge10", 19: "ps_merge11"}


def dec(w):
    op = w >> 26
    if op in (56, 57, 60, 61):
        S = bits(w, 6, 10)
        A = bits(w, 11, 15)
        W = bits(w, 16, 16)
        # Field split fixed 2026-08-26 (M5.0t round): I is 3 bits (GQR 0-7),
        # d is a SIGNED 12-bit field at bits 20-31. The old split (I=4b,
        # d=11b) misdecoded every word with bit20 set (~25% of all psq
        # words) as phantom I8-I15 with halved displacements.
        d = bits(w, 20, 31)
        if d >= 2048:
            d -= 4096
        nm = {56: "psq_l", 57: "psq_lu", 60: "psq_st", 61: "psq_stu"}[op]
        return "%s f%d,%d(r%d),W%d,I%d" % (nm, S, d, A, W, bits(w, 17, 19))
    if op == 59:  # scalar single-precision (NOT paired-single!)
        # Same A-form layout as op 4/63 -- verified by probe
        # (fadds v,w -> frA=fr13, frB=fr14; fmuls v,w -> frA=fr13, frC=fr14;
        #  fmadds v,w,y -> frA=fr13, frC=fr14, frB=fr16, i.e. the standard
        #  `fmadds frD,frA,frC,frB` assembler syntax).
        D, A, B, C, xo5 = afields(w)
        Rc = w & 1
        dot = "." if Rc else ""
        # XO5 map per MPC750 PEM (2026-08-23 fix: the old table was shifted
        # from xo=24 up and had a bogus fsqrts@22; fres=24, frsqrtes=26,
        # fnmsubs=30, fnmadds=31).
        nm = {18: "fdivs", 20: "fsubs", 21: "fadds", 23: "fsels", 24: "fres",
              25: "fmuls", 26: "frsqrtes", 28: "fmsubs", 29: "fmadds",
              30: "fnmsubs", 31: "fnmadds"}
        if xo5 in (18, 20, 21):
            return "%s%s f%d,f%d,f%d" % (nm[xo5], dot, D, A, B)
        if xo5 == 23:
            return "fsels%s f%d,f%d,f%d" % (dot, D, A, B)
        if xo5 in (24, 26):
            return "%s%s f%d,f%d" % (nm[xo5], dot, D, B)
        if xo5 == 25:
            return "fmuls%s f%d,f%d,f%d" % (dot, D, A, C)
        if xo5 in (28, 29, 30, 31):
            return "%s%s f%d,f%d,f%d,f%d" % (nm[xo5], dot, D, A, C, B)
        return "op59xo%d" % xo5
    if op == 63:
        # A-form FP / pair-move family.  Same field layout as op 4; the XO is
        # at bits 10-1 (XO10), NOT bits 10-0 as the old `bits(w, 21, 31)` read
        # (that included the Rc bit, so fmr read as 144 and never matched).
        # Probe: plain f32/f64 copy -> xo5=8, frC=2, source in frB
        #        (this is also what the ps_mr/fmr selector is);
        #        fneg frC=1, fnabs frC=4, fabs frC=8;
        #        frsp -> xo5=12, frC=0, source in frB.
        D, A, B, C, xo5 = afields(w)
        if xo5 == 8 and C in F_OP8:
            return "%s f%d,f%d" % (F_OP8[C], D, B)
        if xo5 == 12 and C == 0:
            return "frsp f%d,f%d" % (D, B)
        return None
    if op == 4:  # Gekko paired-single arithmetic (primary opcode 4)
        D, A, B, C, xo5 = afields(w)
        Rc = w & 1
        # XO5 map per Gekko PIM (2026-08-23 fix: the old tail was shifted one
        # low — sel/res/mul/rsqrte/msub/madd/nmsub/nmadd are 23/24/25/26/28/
        # 29/30/31; verified against cc1.exe __builtin_ps_* encodings where
        # __builtin_ps_mul emits xo5=25). 14/15/31 were missing.
        nm = {10: "ps_sum0", 11: "ps_sum1", 12: "ps_muls0", 13: "ps_muls1",
              14: "ps_madds0", 15: "ps_madds1", 18: "ps_div", 20: "ps_sub",
              21: "ps_add", 23: "ps_sel", 24: "ps_res", 25: "ps_mul",
              26: "ps_rsqrte", 28: "ps_msub", 29: "ps_madd", 30: "ps_nmsub",
              31: "ps_nmadd"}
        dot = "." if Rc else ""
        # FIX 2026-09-27: the operand ORDER below is the assembler's own syntax,
        # probed mnemonic-by-mnemonic with four distinct pinned FPRs:
        #   ps_sum0/ps_madds0/ps_sel/ps_madd  %0,%1,%2,%3 -> frD,frA,frC,frB
        #   ps_mul/ps_muls0                     %0,%1,%2   -> frD,frA,frC
        #   ps_add/ps_sub/ps_div                %0,%1,%2   -> frD,frA,frB
        #   ps_res/ps_rsqrte                    %0,%1     -> frD,frB
        # The old code printed sum0/sum1/madds0/madds1 as (D,A,B,C) -- B and C
        # transposed -- and dropped ps_sel's 4th operand entirely.
        if xo5 in nm:
            if xo5 in (24, 26):
                return "%s%s f%d,f%d" % (nm[xo5], dot, D, B)
            if xo5 in (12, 13, 25):
                return "%s%s f%d,f%d,f%d" % (nm[xo5], dot, D, A, C)
            if xo5 in (18, 20, 21):
                return "%s%s f%d,f%d,f%d" % (nm[xo5], dot, D, A, B)
            # xo5 10/11/14/15/23/28/29/30/31 all take frD,frA,frC,frB
            return "%s%s f%d,f%d,f%d,f%d" % (nm[xo5], dot, D, A, C, B)
        xo = xo10(w)
        if xo5 == 16 and C in MERGE:
            return "%s f%d,f%d,f%d" % (MERGE[C], D, A, B)
        if xo5 == 8 and C in PS_OP8:
            return "%s f%d,f%d" % (PS_OP8[C], D, B)
        # Paired-single compares mirror scalar fcmpu/fcmpo XO values (0/32).
        # CORRECTION 2026-08-26: the previous mapping (64=u, 128=o) NEVER
        # occurs in the DOL (census: zero words); real sites = exactly 2x
        # xo10=32 (crfD=0 compare feeding bne, fn_8025E104/E1FC).
        if xo in (0, 32):
            return "ps_cmp%s0 cr%d,f%d,f%d" % ("u" if xo == 0 else "o",
                                               bits(w, 6, 8), A, B)
        # X-form words (M5.0t/M5.0q decode corrections, 2026-08-26).
        # Indexed quantized ops: w=bit21, XO9=bits22-30. Through an A-form
        # lens these read as the bogus "xo5=6/7 hard wall" — they are plain
        # indexed pair loads/stores (emittable from C under -mps-float).
        # NOTE (2026-09-27): this block is UNCHANGED and still reads the 9-bit
        # XO at bits 9-1.  It is a distinct encoding from the A-form XO10 above
        # (docs/parkings/06 M5.0t: 9-bit XO at bits 22-30 + w at bit 21), so the
        # w bit and rA/rB positions here are still unverified; left alone
        # because changing them without a probe would be a guess.
        xo9 = bits(w, 22, 30)
        wb = bits(w, 21, 21)
        ix = {6: "psq_lx", 7: "psq_stx", 38: "psq_lux", 39: "psq_stux"}
        if xo9 in ix:
            rA, rB = bits(w, 11, 15), bits(w, 16, 20)
            upd = "+" if xo9 in (38, 39) else ""
            return "%s%s f%d,r%d+r%d,w%d" % (ix[xo9], upd, D, rA, rB, wb)

    return None


def disasm(data, addr):
    out = []
    for i in range(len(data) // 4):
        w = int.from_bytes(data[i * 4:i * 4 + 4], "big")
        d = dec(w)
        if d is None:
            dc = list(md.disasm(data[i * 4:i * 4 + 4], addr + i * 4))
            d = "%s %s" % (dc[0].mnemonic, dc[0].op_str) if dc else ".word %08x" % w
        out.append(d)
    return out


def main():
    a = int(sys.argv[1], 16)
    want_sz = None
    flags = ["-mps-float"]
    show = "--all" in sys.argv
    for arg in sys.argv[2:]:
        if arg == "--all":
            continue
        if arg.isdigit():
            want_sz = int(arg)
        elif arg.startswith("-"):
            flags = arg.split() + ["-mps-float"]
    fp = os.path.join(gl.ROOT, "src/wip/fn_%08X.c" % a)
    text = open(fp).read()
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and ".h>" not in l)
    body = '#include "types.h"\n#include "qb_constants.h"\n' + body
    got, masks = gl.compile_fn(a, body, extra_flags=flags)
    if got is None:
        print("COMPILE FAIL:", masks)
        sys.exit(1)
    span = max(len(got), want_sz or 0)
    orig = gl.d[gl.t_off + (a - gl.t_addr): gl.t_off + (a - gl.t_addr) + span]
    oi = disasm(orig, a)
    gi = disasm(got, a)
    n = max(len(oi), len(gi))
    hit = mism = 0
    for i in range(n):
        o = oi[i] if i < len(oi) else "<EOF>"
        g = gi[i] if i < len(gi) else "<EOF>"
        ow = int.from_bytes(orig[i * 4:i * 4 + 4], "big") if i * 4 + 4 <= len(orig) else -1
        gw = int.from_bytes(got[i * 4:i * 4 + 4], "big") if i * 4 + 4 <= len(got) else -2
        m = (ow >= 0 and gw >= 0
             and (ow & masks.get(i * 4, 0xFFFFFFFF)) == (gw & masks.get(i * 4, 0xFFFFFFFF)))
        if m:
            hit += 1
            if show:
                print("OK   %04X %08x %-36s | %s" % (i * 4, ow, o, g))
        else:
            mism += 1
            print("DIFF %04X %08x/%08x %-34s | %s" % (i * 4, ow, gw, o, g))
    print("=== %d/%d match (%.1f%%), %d mismatches, got %dB"
          % (hit, n, 100.0 * hit / n, mism, len(got)))


if __name__ == "__main__":
    main()
