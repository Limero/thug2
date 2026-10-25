// WIP DRAFT (non-matching) — hand-rebuilt from the DOL disassembly
// family=m2c range=0x8001CB60-0x8001CC70 size=272B
// INERT: not registered in splits.txt/configure.py — never compiled by the
// build, not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-30: 83.8% -> 85.3% NEAR (58/68 words, size-exact 272B).
// UPDATED 2026-10-02: 15.6% -> 83.8% NEAR (56/68 words, size-exact 272B).
//   Semantics recovered from the want:
//   * the six stack slots are all `u8` (retail loads them with `lbz` and never
//     touches sp8 as a word) — m2c had sp9..spD as `s32`, which alone cost
//     every stack displacement.
//   * the inner-loop bound is `(u32)count * 0x11` compared UNSIGNED against
//     the unsigned elapsed/divisor quotient, so the multiply must be
//     `(u32)*(s32*).. * 0x11` (not a signed product).
//   * the divisor is `busclock / 4000`; retail strength-reduces that constant
//     division into `mulhwu`/`srwi 8` with the magic 0x10624DD3, so the magic
//     is materialized as a normal local (r31) and the multiply is spelled as
//     an explicit u64 product.  (`clk / 4000` as plain C is also correct but
//     hoists the whole divisor chain into the preheader — 60.3%.)
//   * OSVReport needs a real 2-arg prototype (a `void` one emits a spurious
//     `crclr cr1eq`); OSPanic must stay IMPLICIT (retail *keeps* the crclr).
//   * the four `0x80000000+`/`0x80290000+` page anchors are named locals
//     assigned before the loop, not inline literals (an inline literal gives
//     lis+ori and a different regalloc) and not extern symbols (10.1%).
// Levers that carry the match:
//   * `__asm__("" : "+r"(pg29a), "+r"(pg29b))` right before the OSPanic call:
//     zero emitted instructions, but it stops LICM hoisting the two
//     `addi rX,0x10cc/0x10fc` argument addresses into the loop preheader,
//     which is what gives retail's 12 live-across-call webs and therefore
//     `stwu -0x40` + `stmw r20,0x10(r1)`.  Removing it -> 28.6%, and moving
//     it after the call -> 27.1%.  DISCLOSED: 0 emitted instructions.
//   * `__asm__ __volatile__("")` right after the OSVReport call: splits the
//     pre-loop block so the anchor `lis` block is a distinct basic block,
//     which is what places `lis r23` (row 8) after the `bl` as retail has it.
//     DISCLOSED: 0 emitted instructions.  Moving it before OSVReport -> 79.4%.
//   * `register s32 temp_r30 __asm__("r30")`: fixes the r29/r30 swap between
//     the saved start tick and `&spD` (67.7% -> 76.5%).  One pin, and the
//     pin-a-member-of-a-permuted-group rule applies (pinning `&spD` instead
//     regresses to 42.0%).
//   * `register u32 cnt __asm__("r9") / bound __asm__("r11")` with the
//     operands named through assignment expressions
//     inside the comparison: 76.5% -> 83.8%.  Naming alone is inert
//     (76.5%); the pins are what buy the colours.
// ROUND r3 (2026-10-30) GAIN: 83.8% -> 85.3%, +1.5% from ONE zero-instruction
//   construct, and 3 provably-inert pins deleted.
//   * `__asm__ __volatile__("")` right after `pg29b = 0x80290000;` (i.e. as a
//     SECOND block split in the preheader, on top of the existing one after
//     OSVReport).  It closes the preheader right before the hoisted-address
//     block, so the preheader emits as
//       [lis r23][lis r22][lis r20][lis r21] | [addi r24..r27][addi r29]
//     instead of the unsplit
//       [lis r23][lis r22][addi r24..r27][addi r29][lis r20][lis r21].
//     DISCLOSED: 0 emitted instructions (empty volatile asm).  Ablation:
//     removing it drops back to 83.8%; removing the OSVReport split drops to
//     82.4%; both are load-bearing.
//   * Pins `clk -> r0`, `pg00 -> r22`, `pg36 -> r23` are now INERT (each
//     removal is byte-identical at 85.3%, and removing all three together is
//     also 85.3%) — deleted.  The remaining five pins (pg29a, pg29b,
//     temp_r30, cnt, bound) are all load-bearing: 77.9 / 77.9 / 75.0 / 80.9 /
//     80.9 when removed.  Removing ALL pins collapses to 28.6%.
// Residual 10 words, both windows documented:
//   1. rows 9-15 — the PREHEADER EMISSION ORDER.  want
//      [lis r23][addi r24..r27][lis r22][lis r20][lis r21][addi r29];
//      got [lis r23][lis r22][lis r20][lis r21][addi r24..r27][addi r29].
//      Only the four hoisted `addi r24..r27` are in the wrong place now
//      (they must sit between `lis r23` and `lis r22`); `addi r29` is already
//      last in both, matching want.
//      The four `addi r24..r27` are `loop.c`hoisted address-of insns that are
//      APPENDED at the end of the loop preheader, so within one block they can
//      only follow every source-written statement.  Want's order therefore
//      requires them in a block that ends before `lis r22` — and hoisting
//      always targets the LAST block before the loop head, which makes that
//      unreachable by block splitting.  Measured: naming them as locals so they
//      become source-written gives the right order but destroys the allocation
//      (10.1%, everything moves to r26..r31); assigning the anchors inside the
//      loop so THEY become hoisted gives [addi x4][addi r29][call setup][lis…]
//      (69.1%) / 76.5%; splitting after pg36 instead of after pg29b is 80.9%;
//      4 other split positions 82.4-85.3%; symbol references instead of the
//      named pages 10.1%.
//   2. rows 39/42/43 — the DImode magic-multiply temp: want
//      `mulhwu r0,r0,r31` / `srwi r0,r0,8` / `divwu r3,r3,r0` (all in-place
//      in the loaded busclock's register), got `mulhwu r5,r0,r31` /
//      `srwi r8,r5,8` / `divwu r3,r3,r8`.  The `umul_highpart` destination is a
//      fresh SImode pseudo and is live AT the insn together with its rA input,
//      so `local_alloc` cannot share a register — want's in-place form must come
//      from a different RTL shape than any of these spellings.
//      Pinning the *result* is silently dropped (the web is created by the
//      DImode expand and has no single def pseudo).  All byte-identical or
//      worse: `(u64)` cast on the magic; `u64` magic; `>>32` then `>>8`;
//      in-place `clk = ...`; named `u64 prod`; dropping the clk pin; `& 0xFFFFFFFF`;
//      and plain `/4000` (61.8% — hoists the whole divisor chain).
// Exhausted (measured, all worse or byte-identical): 11 compiler flags
// (-fno-schedule-insns{,2}, -fno-sched-spec, -fno-sched-interblock,
// -fno-gcse, -fno-expensive-optimizations, -fno-rerun-cse-after-loop,
// -fno-thread-jumps, -fno-strength-reduce, -O3, -Os), 4 declaration
// permutations, 8 anchor-placement variants, 5 store/compare orderings,
// `volatile` and `const` on the globals, divisor/count/bound/quotient temps
// as statements, and the `/4000` plain-C spelling.
#include "types.h"
extern char lbl_802910C0[];
extern void OSVReport(char *, s32);
s32 OSGetTick(void);
s32 GX_GetGPStatus(s32, s32, s32, s32, s32);
s32 GX_GetOverflowCount(void);
void fn_8001CA68(void);
void fn_8001CB60(void) {
    u8 sp8;
    u8 sp9;
    u8 spA;
    u8 spB;
    u8 spC;
    u8 spD;
    s32 pg36;
    s32 pg00;
    register s32 pg29a __asm__("r20");
    register s32 pg29b __asm__("r21");
    s32 temp_r28;
    register s32 temp_r30 __asm__("r30");
    u32 magic;
    u32 divisor;
    register u32 clk;
    register u32 cnt __asm__("r9");
    register u32 bound __asm__("r11");

    OSVReport(lbl_802910C0, 0);
    __asm__ __volatile__("");
    pg36 = 0x80360000;
    pg00 = 0x80000000;
    pg29a = 0x80290000;
    pg29b = 0x80290000;
    __asm__ __volatile__("");
loop_1:
    GX_GetGPStatus(&sp8, &sp9, &spA, &spB, &spC);
    if ((s32) sp8 == 0) {
        goto loop_1;
    }
    if (*(s32 *) ((char *) pg36 + 0x1428) == 0) {
        goto loop_1;
    }
    temp_r28 = GX_GetOverflowCount();
    magic = 0x10624DD3;
    temp_r30 = OSGetTick();
loop_4:
    if ((u32) ((OSGetTick() - temp_r30) / (divisor = (u32) ((((unsigned long long) (clk = *(u32 *) ((char *) pg00 + 0xF8)) * magic) >> 40))) < (bound = (cnt = *(s32 *) ((char *) pg36 + 0x1428)) * 0x11))) {
        if (temp_r28 == GX_GetOverflowCount()) {
            goto loop_4;
        }
    }
    GX_GetGPStatus(&sp8, &spD, &spD, &spD, &spD);
    if ((s32) sp8 == 0) {
        goto loop_1;
    }
    if (temp_r28 != GX_GetOverflowCount()) {
        goto loop_1;
    }
    fn_8001CA68();
    __asm__("" : "+r"(pg29a), "+r"(pg29b));
    OSPanic((char *) (pg29a + 0x10cc), 0x73A, (char *) (pg29b + 0x10fc));
    goto loop_1;
}
