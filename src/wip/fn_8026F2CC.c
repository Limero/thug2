// WIP DRAFT (non-matching) — semantic reconstruction from the retail fdlibm
// family=m2c range=0x8026F2CC-0x8026F55C size=656B
// FLAG: -msdata=eabi -G8
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// ID: fdlibm __ieee754_log duplicate. The complete 0x290-byte body is the
// standard argument reduction, |f| < 2^-20 path, degree-14 log polynomial,
// and dk*ln2_hi/ln2_lo tails. Constants are the SDA doubles at 0x803CA480-
// 0x803CA500 (verified dump: -inf, 0.0, two54, one, 0x4330000080000000,
// ln2_hi/lo, 1/3, 0.5, 2.0, Lg6,Lg4,Lg2,Lg7,Lg5,Lg3,Lg1).
// REBUILT 2026-09-25: removed all m2c saved_reg_rXX/static artifacts; restored
// fdlibm variable types, word-union operations, and exact return control flow.
// REBUILT 2026-10-03: kept the 2026-09-25 body verbatim — it is still the
// best-scoring honest form (see EXPERIMENT LOG); every alternative tried this
// round measured worse. Body is unchanged; only the notes below are new.
//
// PARKED 2026-10-03: DIFF 37.8% masked (656B, size-exact). Baseline was
// also 37.8%, i.e. this round did not improve the score — the two structural
// blockers below are the reasons, and both are outside the C body.
//   reproduce: LEAF_TMPDIR=<private dir> tools/venv/bin/python \
//              tools/test_wip_drafts.py --addr 0x8026F2CC
//              (pct via the same masked_pct + compile_fn as that script)
//
// BLOCKER 1 — HARNESS CEILING 83.5% (NEW, general). test_wip_drafts.py masks
// only R_PPC_REL14 / REL24 / ADDR16_HA / ADDR16_LO (tools/gen_leaves.py
// compile_fn). R_PPC_EMB_SDA21 (reloc type 109) is NOT in the mask table, and
// under -msdata=eabi ngccc emits every extern-double reference as an
// instruction PLACEHOLDER: `lfd f1, 0(r0)` — rA=0, disp=0 — with an SDA21
// reloc. The WANT word is `lfd f1, -0x7e00(r13)` — rA=13, disp=-0x7e00 — so
// the rA bits alone can never compare equal and no mask would help (an SDA21
// reloc rewrites the WHOLE instruction word, so the displacement is not
// separable either). This want contains 27 SDA21 float loads in 164 words
// (24 fdlibm constants + 3 int->f64 bias loads), so the best possible masked
// score for ANY body is 137/164 = 83.5%. "DIFF" here is therefore NOT a body
// defect; tools/sda_verify.py (which adds the SDA21 mask) is the only authority
// on real byte-exactness. Corollary: any function whose
// body loads a float constant through r13 can never report EXACT from
// test_wip_drafts.py — check the SDA21 count before spending a round on one.
//
// BLOCKER 2 — the 3 int->f64 sites are one word too long (dominant loss).
// Retail site (0x8026F3D4, and identically at 0x8026F42C / 0x8026F464) builds
// the conversion in 5 words of an 11-word block: xor in the 0x8000 sign bit,
// spill the word to the 0x14 stack slot, materialise the 0x4330 bias high
// half, load the bias double from its SDA symbol (-0x7de0(r13)), and store
// the high word to the 0x10 stack slot.
// i.e. the bias constant is a SYMBOL reference (0x803CA4A0 == 0x4330000080000000,
// verified) and the hi word lands in a separate 0x10/0x14 stack slot from the
// word union at 8/0xc. ngccc's natural `(f64)k` emits 6 words instead —
// xoris ; stw ; lis 0x4330 ; `lis rX,0` ; `lfd f0,0(rX)` ; stw — because the
// synthesized bias goes to a PRIVATE module .rodata pool. So the got is +1 word
// from 0x108, +2 from 0x160, +3 from 0x198, and ~100 words downstream are
// misaligned; that is where the missing 75% lives. In the retail build that
// literal was SDA-referenced in the game's .rodata2 (same section as the other
// fdlibm constants) instead of a module pool, i.e. this is a BUILD/po routing
// difference (doc-14 class), not a source shape reachable by a flag (see the
// flag results below).
//
// RULED OUT THIS ROUND (all compiled with the draft's real flags, whole body):
//   hand union cvt, struct member form
//     cvt.w.hi = 0x43300000; cvt.w.lo = (u32)k ^ 0x80000000;
//     dk = cvt.d - lbl_803CA4A0;                      -> 15.2%, 644B
//     (recipes 6j-1 form; recipe 231 confirms the xoris+2^52+2^31 bias is the
//      SIGNED cast, so the constant choice is right.) Block COUNT is right
//      (11) but GCC scalarises the union and re-materialises it in the SAME
//      8/0xc slot as `bits`, so the frame loses 12B and the block order
//      permutes: this build materialises the bias first and then performs the
//      sign-bit merge and memory round trip, while the reference merges the
//      sign bit and spills first and only then materialises the bias before
//      completing the same round trip. 644B vs 656B.
//   same, `u32 w[2]` array member instead of the struct   -> 15.2%, 644B
//   ONE 16-byte local `union {...} ux[2]` (ux[0]=word union, ux[1]=cvt), i.e.
//     retail's 8/0xc + 0x10/0x14 layout as a single object  -> 1.2%, 616B
//   `volatile` on the word union alone                    -> 1.2%, 632B
//   `volatile` on both unions + hand cvt                  -> 2.4%, 628B
//   flags: -msdata=eabi alone 4.8%/752B; -msdata=eabi -G8 -G16 and
//     -msdata=eabi -G8 -msdata are byte-identical to the baseline. No flag makes
//     the synthesized 0x43300000/0x80000000 literal SDA-referenced.
// NOTE: `volatile` is the ONLY lever found that makes ngccc
// keep the word union in MEMORY — it really does reproduce retail's
// stfd f1,8 / lwz r9,8 / lwz r10,0xc / or / stw / stw / lfd f0,8 / fmr f1,f0
// round trip and the lwz-r9-then-mr-r8,r9 entry pair (verified in a flagless
// probe). It still loses on net word count, so do not re-try it without a new
// idea for the 24 constant loads.
//
// RESIDUAL MAP (102 misses of 164 words at 37.8%; 27 of them are Block 1):
//   0x00C-0x018 (4w) entry: retail `lwz r9; lwz r10; mr r8,r9; mr r11,r10`,
//     got `lwz r5; mr r8,r5; lwz r6; mr r11,r6` — pure register allocation.
//   0x01C-0x020 (2w) `li r7,0` and `lis r0,0xf` emitted in the opposite order.
//   0x03C/0x04C/0x05C, and every later constant word: Block 1, unwinnable.
//   0x070-0x078 (3w) two54 path: same lwz-temp register mismatch as the entry.
//   0x094-0x0AC (6w) `k += (hx>>20)-0x3FF` / `i = (hx+0x95F64)&0x100000`:
//     same opcodes, registers r0/r7/r9 vs retail r9/r0/r11.
//   0x0B0-0x0D4 (10w) ONE region: retail re-reads x from the stack
//     (stfd/lwz/lwz/xoris/or/stw/stw/lfd/fmr) where the draft folds to one
//     `stw r5,8(r1)` + `stw r6,0xc(r1)` + `lfd f13,8(r1)`, and retail keeps
//     `(2+hx)&0xfff` AFTER that block while the draft hoists `addi r11,r8,2`.
//     `volatile` fixes the shape but not the net count (see above).
//   0x0D8-0x108 (13w) mostly match modulo the Block-2 word shift.
//   0x10C-0x28C (~96w) shifted by 1/2/3 words: Block 2. The polynomial itself
//     (fmadd chain, fmul operand order, hfsq) and all four return sequences
//     match 1:1 once the shift is accounted for — see 0x8026F45C-0x8026F554,
//     which is instruction-for-instruction the draft's tail.
//   0x21C (1w) `fmul f0,f3,f0` vs `fmul f0,f0,f3` — GCC canonicalises MULT_EXPR
//     operand order (§6by-2: not source-reachable).
//
// BEST THEORY / NEXT IDEA (unchanged from 2026-10-02, still the best one):
// retail's normalization genuinely re-reads x from the stack instead of folding
// to a direct `stw`, and that reorders the 0x094-0x0D4 region. `volatile`
// achieves the memory traffic but pays for it in extra reloads; what is still
// untried is keeping the union in memory WITHOUT volatility — e.g. a frame
// template struct holding both word pairs as named members plus the round trip
// written as explicit member accesses, or making `hi`/`lo` (pinned r9/r10)
// genuinely live so the entry loads land in r9/r10 and the `mr`s survive
// (worth 4 words at 0x0C-0x018 alone).
//
// EXPERIMENT LOG (index-aligned %, tools/venv/bin/python scorer):
//   committed body (kept) ..................... 37.8%  656B   <- 2026-10-03
//   hand union cvt (struct member) ............ 15.2%  644B
//   hand union cvt (u32 w[2] member) .......... 15.2%  644B
//   volatile both + hand cvt ..................  2.4%  628B
//   one 16B union array ux[2] .................  1.2%  616B
//   volatile word union alone .................  1.2%  632B
//   flags -msdata=eabi (no -G8) ...............  4.8%  752B
//   (2026-10-02, earlier round, all worse than the committed body:
//    direct hx/lx extraction 41.46; pins removed 35.98; hi/lo asm barriers
//    10.37; array-union fr.cw + full RMW 20.73; + mask 20.73; hand cvt union +
//    extern bias 34.15; + volatile cvt slot 25.00; + swapped bits/cvt slots
//    34.15; + "m" pin 25.00; + volatile bits union 1.95; plain cvt struct +
//    pun 25.00; log10-style entry 28.66; + e20/tmp/i shaping 26.22; + dk read
//    via *(f64*)&fr.cw[0] 26.22; + f/s/dk pins 31.71; + hfsq=f*0.5*f 32.93;
//    + acc pin 32.93; log10 entry w/o cvt 28.66; log10 on committed 6.71;
//    named-const polynomial locals 30.49; den=2.0+f 31.71; den pinned fr0
//    32.93; -fno-schedule-insns2 +2.2, -fno-schedule-insns -3.7,
//    -fno-expensive-optimizations +0.6.)
#include "types.h"
extern f64 lbl_803CA480;
extern f64 lbl_803CA488;
extern f64 lbl_803CA490;
extern f64 lbl_803CA498;
extern f64 lbl_803CA4A0;
extern f64 lbl_803CA4A8;
extern f64 lbl_803CA4B0;
extern f64 lbl_803CA4B8;
extern f64 lbl_803CA4C0;
extern f64 lbl_803CA4C8;
extern f64 lbl_803CA4D0;
extern f64 lbl_803CA4D8;
extern f64 lbl_803CA4E0;
extern f64 lbl_803CA4E8;
extern f64 lbl_803CA4F0;
extern f64 lbl_803CA4F8;
extern f64 lbl_803CA500;

f64 fn_8026F2CC(f64 x) {
    union {
        f64 d;
        struct {
            u32 hi;
            u32 lo;
        } w;
    } bits;
    f64 hfsq;
    f64 f;
    f64 s;
    f64 z;
    f64 R;
    f64 w;
    f64 t1;
    f64 t2;
    f64 dk;
    register s32 hi __asm__("r9");
    register s32 lo __asm__("r10");
    register s32 hx __asm__("r8");
    register u32 lx __asm__("r11");
    register s32 k __asm__("r7");
    s32 i;
    s32 j;

    bits.d = x;
    hi = (s32)bits.w.hi;
    lo = (s32)bits.w.lo;
    hx = hi;
    lx = (u32)lo;
    __asm__ volatile("" : "+r"(hx), "+r"(lx));
    k = 0;
    if (hx < 0x00100000) {
        if (((hx & 0x7FFFFFFF) | (s32)lx) == 0) {
            return lbl_803CA480;
        }
        if (hx < 0) {
            return (x - x) / lbl_803CA488;
        }
        k = -54;
        x *= lbl_803CA490;
        bits.d = x;
        hx = (s32)bits.w.hi;
    }
    if (hx >= 0x7FF00000) {
        return x + x;
    }
    k += (hx >> 20) - 0x3FF;
    hx &= 0x000FFFFF;
    i = (hx + 0x95F64) & 0x100000;
    bits.w.hi = (u32)(hx | (i ^ 0x3FF00000));
    x = bits.d;
    k += i >> 20;
    f = x - lbl_803CA498;
    if ((hx & (2 + hx)) < 3) {
        if (f == lbl_803CA488) {
            if (k == 0) {
                return lbl_803CA488;
            }
            dk = (f64)k;
            return dk * lbl_803CA4A8 + dk * lbl_803CA4B0;
        }
        R = f * f * (lbl_803CA4C0 - f * lbl_803CA4B8);
        if (k == 0) {
            return f - R;
        }
        dk = (f64)k;
        return dk * lbl_803CA4A8 - ((R - dk * lbl_803CA4B0) - f);
    }
    s = f / (lbl_803CA4C8 + f);
    dk = (f64)k;
    z = s * s;
    i = hx - 0x6147A;
    w = z * z;
    j = 0x6B851 - hx;
    t1 = w * (lbl_803CA4E0 + w * (lbl_803CA4D8 + w * lbl_803CA4D0));
    t2 = z * (lbl_803CA500 + w * (lbl_803CA4F8 + w * (lbl_803CA4F0 + w * lbl_803CA4E8)));
    i |= j;
    R = t2 + t1;
    if (i > 0) {
        hfsq = lbl_803CA4C0 * f * f;
        if (k == 0) {
            return f - (hfsq - s * (hfsq + R));
        }
        return dk * lbl_803CA4A8 - ((hfsq - (s * (hfsq + R) + dk * lbl_803CA4B0)) - f);
    }
    if (k == 0) {
        return f - s * (f - R);
    }
    return dk * lbl_803CA4A8 - ((s * (f - R) - dk * lbl_803CA4B0) - f);
}
