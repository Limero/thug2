// PARKED 2026-10-05 (w_80024DA8): best measured 20.5% (24/117 words), object
// SIZE-EXACT (468B / 117 insns, delta 0), 0 emitted asm, 0 extra flags,
// 1 register pin (arg2 -> r5).  Started from 3.4% / 204B short.
//
// WHAT WAS RECOVERED (semantics, from a full hand-decode of the retail PS
// stream -- this part is real and verified, only the schedule is not):
//   * the function takes FIVE args, not m2c's two:
//       arg0 = r3 (struct: s32 @0xC, f32 @0x10, f32 @0x14), arg1 = r4 (f32[4]),
//       arg2 = r5 (f32*, two vec2s at +0x20 / +0x28), arg3 = r6 (f32[4]),
//       arg4 = r7 (passed straight through).
//   * 0x90-byte frame == exactly 16 8-byte paired-single slots at r1+0x08..0x87;
//     `addi r31,r1,8` is &slot0 and is what `mr r4,r31` feeds to fn_8005FD68.
//   * lbl_802913F0 == 1.0f and lbl_802913F4 == 0.0f; every PS op here is
//     vector arithmetic against those two constants (cross-product of arg3's
//     vec2 with arg2's two vec2s, then scaled by arg0->f10 / arg0->f14).
//   * fn_80024FDC is called with EIGHT GPR args (r3..r10 = &slot6, &slot10,
//     arg2, arg3, arg4, arg1, 0x80290000, &slot8) and NO crclr, so a real
//     8-arg prototype is required at this call site (m2c invented 9 args).
//   * the scalar `stfs` runs into slot8/slot9 (0x48/0x4C/0x50/0x54) and the
//     scalar store into slot15+0 (0x80) are writes of the LOW/HIGH halves of
//     __ps_t slots through f32 lvalues -- that is what makes the compiler
//     reload the pair afterwards; plain __ps_t stores do NOT (448B object,
//     5 instructions short) so those writes are kept volatile on the arg2
//     reloads.
//   * the 4-iteration empty `li r0,4 / mtctr r0 / bdnz .` countdown is
//     `ctr = 4; do { ctr -= 1; } while (ctr != 0);` -- self-targeting bdnz
//     falls out of plain C in this shape (doc 30 / recipe 7d-2) once the call
//     pointer births land inside the window.
//
// RESIDUAL (93/117 words differ; all three counters above ARE matched):
//   1. prologue -- want puts the count 4 in r0, homes arg0 into r30, moves the
//      count to the count register, homes arg1 into r8 and takes the slot0
//      address from the stack pointer into r31, then takes the 0x38 and 0x48
//      slot addresses from the stack pointer and counts down, with the P10
//      address materialised only AFTER the countdown. Got spends three
//      instructions on compiler copies instead: the count goes in r9, arg2 is
//      shuffled through r0, the count moves to the count register, arg1 is
//      copied through r12, arg2 is restored from r0, and the result is homed
//      into r8.  Pinning arg1->r8 fixes the last two but costs a third
//      callee-saved reg (frame 0x98, stmw r29, 9.4%); not pinning arg2->r5
//      gives 3 saved regs too.  0x90 + stmw r30 + arg0 in r30 + &slot0 in r31
//      is only reachable WITH the arg2 pin, at the price of the r0/r5 shuffle.
//   2. three register copies want makes that plain C will not: `fmr f13,f7`
//      before `stfs f13,0x7c(r1)` (want copies 1.0f into f13 first), and the
//      two `ps_mr`s (0xb0 f13<-f0 after the slot14 reload, 0x130 f0<-f13
//      after the slot15 reload).  Both are GCC ps-pass shuffles / forward-
//      forwarding that only appear when the original register pressure was
//      higher; pinning the FPRs via `register ps_reg` was NOT tried to
//      completion and is the most promising next lever.
//   3. want reuses ONE `lis r9,0x8029` for both the lbl_802913F4 page and the
//      7th fn_80024FDC argument (0x80290000); got emits a 3rd `lis` for the
//      integer literal (a CONST_INT does not CSE with the symbol's HA16).
//      `extern f32` vs `extern char[] + *(f32 *)` (recipes §6ek-1) was tried
//      both ways: identical 20.5%.
//   4. mid/tail scheduling: want's store order for the final block is
//      P2,P12,P3,P13,P6,P7,P4,P5,P10,P11 with the two `ps_muls0` slots
//      interleaved between the slot reloads.  Source order P2..P7 then
//      P12,P13 scores best (20.5%); the want-derived order P2,P12,P3,P13,P6,P7
//      and its reverse both score 17.1%.  Everything from 0x13c on is a
//      1-2 slot scheduler tie-break rotation.
//
// RULED OUT: no statement-order permutation can close (3) since it is a
// constant-CSE question, not an order question; `volatile` on the arg2 reloads
// is what makes the length exact (non-volatile = 448B); pinning the countdown
// counter to r0 breaks the mtctr/bdnz conversion entirely (addic./bne);
// `twin_scan`/`near_twin_scan` found nothing (fn_80024FDC/F7C/FAC are 24/48B
// neighbours, unrelated shapes).
#include "structs.h"
// family=m2c range=0x80024DA8-0x80024F7C size=468B
// extra_cflags: -mps-float
typedef struct {
    s32 unk0x0;
    char pad0x4[0x8];
    s32 unk0xC;
    f32 unk0x10;
    f32 unk0x14;
} Arg0;
extern char lbl_802913F0[];
extern char lbl_802913F4[];
void fn_80024FDC(void *, void *, f32 *, f32 *, s32, f32 *, s32, void *);
void fn_8005FD68(void *, s32, s32);

typedef struct {
    __ps_t P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15;
} FR;

void fn_80024DA8(Arg0 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4) {
    FR fr;
    __ps_t d0, d1, c0, c1, t1, t2, t3, t4, t5, u1, u2, u3, u4, u5, t6;
    f32 one, zero, a10;
    s32 ctr;
    __ps_t *p0 = &fr.P0;
    register f32 *a2 __asm__("r5") = arg2;

    ctr = 4;
    do {
        ctr -= 1;
    } while (ctr != 0);

    d0 = *(__ps_t *)arg3;
    d1 = *(__ps_t *)(arg3 + 2);
    c0 = *(__ps_t *)(a2 + 10);
    fr.P2 = d0;
    t1 = __builtin_ps_merge10(d0, d1);
    one = *(f32 *)&lbl_802913F0;
    c1 = *(__ps_t *)(a2 + 8);
    fr.P3 = *(__ps_t *)(arg3 + 2);
    t2 = __builtin_ps_merge10(c1, c0);
    zero = *(f32 *)&lbl_802913F4;
    t3 = __builtin_ps_mul(t1, c1);
    t4 = __builtin_ps_mul(d0, t2);
    a10 = arg0->unk0x10;
    u1 = __builtin_ps_merge00(c1, c0);
    u2 = __builtin_ps_merge00(d1, d0);
    u3 = __builtin_ps_mul(u2, u1);
    t5 = __builtin_ps_sub(t4, t3);
    fr.P14 = __builtin_ps_merge00(t5, t5);
    *(f32 *)((char *)&fr.P14 + 4) = one;
    u4 = __builtin_ps_merge10(u3, u3);
    u5 = __builtin_ps_sub(u3, u4);
    t6 = __builtin_ps_merge10(t5, u5);
    fr.P8 = t6;
    *p0 = t6;
    fr.P9 = fr.P14;
    fr.P4 = *(volatile __ps_t *)(a2 + 8);
    fr.P5 = *(volatile __ps_t *)(a2 + 10);
    *p0 = fr.P9;
    *(f32 *)&fr.P8 = zero;
    *(f32 *)((char *)&fr.P9 + 4) = one;
    *(f32 *)&fr.P9 = zero;
    *(f32 *)((char *)&fr.P8 + 4) = zero;
    fr.P6 = fr.P8;
    fr.P7 = fr.P9;
    *(f32 *)&fr.P8 = a10;
    *(f32 *)((char *)&fr.P8 + 4) = a10;
    *(f32 *)&fr.P9 = a10;
    *(f32 *)((char *)&fr.P9 + 4) = one;
    *p0 = __builtin_ps_mul(*p0, fr.P8);
    *(f32 *)&fr.P15 = arg0->unk0x14;
    *p0 = __builtin_ps_mul(*p0, fr.P9);
    fr.P12 = __builtin_ps_muls0(d0, fr.P15);
    fr.P13 = __builtin_ps_muls0(d1, fr.P15);
    fr.P2 = __builtin_ps_mul(fr.P2, fr.P8);
    fr.P3 = __builtin_ps_mul(fr.P3, fr.P9);
    fr.P4 = __builtin_ps_mul(fr.P4, fr.P8);
    fr.P5 = __builtin_ps_mul(fr.P5, fr.P9);
    fr.P6 = __builtin_ps_mul(fr.P6, fr.P8);
    fr.P7 = __builtin_ps_mul(fr.P7, fr.P9);
    fr.P10 = __builtin_ps_add(*(__ps_t *)arg1, fr.P12);
    fr.P11 = __builtin_ps_add(*(__ps_t *)(arg1 + 2), fr.P13);
    fn_80024FDC(&fr.P6, &fr.P10, arg2, arg3, arg4, arg1, 0x80290000,
                (void *)&fr.P8);
    if (arg0->unk0xC != 0) {
        fn_8005FD68(p0, 1, 0);
    }
}