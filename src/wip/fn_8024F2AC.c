// WIP DRAFT (PARKED 2.1% = 1/47 masked words, 2026-09-25 plain-C rescore)
// family=m2c range=0x8024F2AC-0x8024F360 size=180B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// SEMANTIC RECONSTRUCTION (plain C, no inline asm — 2026-09-25):
// Decoded directly from the DOL words at 0x8024F2AC (45 insns, 0xB4 bytes).
// GQR7-quantized (0x00070004) texture-block upload: computes plane addresses
// from the header at arg0 and issues six calls into the hand-written fragment
// fn_8024F360 (0x150 bytes of psq_l/psq_st + dcbz kernels using GQR7).
//
// WHAT THE ASM DOES, in order:
//   arg2 *= 16; h = *(u16 *)(arg0 + 4);
//   save GQR7 (SPR 919) + LR; th = arg2 * h;
//   src = *(arg0 + 8) + (arg1 * 64) + th;
//   GQR7 = 0x00070004; stride = h * 4; row8 = h * 8;
//   frag(src); frag(src + 0x20); src += row8;
//   frag(src); frag(src + 0x20);
//   arg2 /= 2; h /= 2 (both LOGICAL srwi -> unsigned); th2 = arg2 * h;
//   stride = h * 4; arg1 /= 2 (logical);
//   frag(*(arg0 + 0xC) + th2 + arg1); frag(*(arg0 + 0x10) + th2 + arg1);
//   restore GQR7 + LR; return.
//
// PARK REASON (verified, do not re-grind):
// fn_8024F2AC is HAND-WRITTEN ASSEMBLY, not compiler output. Evidence:
//  1. Prologue saves r14/r15 as INDIVIDUAL stw (stw r14,8(r1); stw r15,0xc(r1))
//     in a 0x10 frame with no LR stack slot; epilogue restores LR via
//     "mtlr r15" from a captured web. ngccc spills LR as mflr r0 / stw r0
//     and restores via lwz/mtlr (see the got side of diff_near).
//  2. GQR7 (SPR 919) and LR are parked in callee-saved r14/r15 across the
//     calls — a hand-asm save/restore idiom (mfspr/mflr at entry,
//     mtspr/mtlr at exit), not a compiler spill.
//  3. It calls the fragment fn_8024F360 with nonstandard register args
//     (r11=dest, r8=stride; r6 source row ptr INHERITED from ITS caller and
//     never set here) — impossible as an ordinary C call. The fragment body
//     (psq_l 0(r6),7 / psq_st 0(r11),7 + dcbz) confirms the GQR7-quantized
//     block-copy contract.
// Plain C therefore keeps the exact address math with the true unsigned
// types (u16 height gives lhz; u32 args give srwi, not srawi) and 2-arg
// fn_8024F360(dst, stride) calls (the C-expressible subset of the true
// r11/r8 (+inherited r6) contract; bare calls let DCE delete the math).
// It compiles clean (got 188B vs want 180B) but cannot byte-match reasons
// 1-3: rescore 2026-09-25 via tools/diff_near.py = 1/47 (2.1%), the only
// shared word the trailing blr. Prior asm-pinned draft scored 13.0% but
// used inline asm (mfspr/mtspr/bl wedges) — removed per the no-asm rule;
// that score was transcription, not decompilation. See docs/parkings/41
// (*NeGo texture-upload kernels*) and doc 36 (hand-asm fingerprints).
#include "types.h"

typedef struct {
    char _0[4];
    u16 h;
    u16 _6;
    void *base;
    void *base2;
    void *base3;
} T_8024F2AC;

extern void fn_8024F360(void *dst, u32 stride);

void fn_8024F2AC(T_8024F2AC *arg0, u32 arg1, u32 arg2) {
    u32 h;
    u32 th;
    u32 th2;
    u32 stride;
    u32 row8;
    s32 src;
    s32 dst;

    arg2 <<= 4;
    h = arg0->h;
    th = arg2 * h;
    src = (s32)arg0->base;
    arg1 <<= 6;
    /* GQR7 = 0x00070004 selected here in asm; not expressible in plain C. */
    src = src + (s32)arg1 + (s32)th;
    stride = h * 4;
    row8 = h * 8;
    /* fragment reads src row via inherited r6, stride via r8 — dest only below */
    dst = src;
    fn_8024F360((void *)dst, stride);
    dst = src + 0x20;
    fn_8024F360((void *)dst, stride);
    src += (s32)row8;
    dst = src;
    fn_8024F360((void *)dst, stride);
    arg2 >>= 1;
    h >>= 1;
    th2 = arg2 * h;
    dst = src + 0x20;
    fn_8024F360((void *)dst, stride);
    dst = (s32)arg0->base2;
    arg1 >>= 1;
    dst += (s32)th2 + (s32)arg1;
    stride = h * 4;
    fn_8024F360((void *)dst, stride);
    dst = (s32)arg0->base3 + (s32)th2 + (s32)arg1;
    fn_8024F360((void *)dst, stride);
    (void)stride;
    (void)dst;
}
