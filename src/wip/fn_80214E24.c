// PARKED 55.8% (with FLAG: -fno-schedule-insns; 50.0% flagless): doc-15-class
// arg-setup/sched residue in a -mps-float PS function. Structure + frame + FPR
// pins match (prologue/epilogue/trig block byte-exact). Residual: (a) cvt
// window - want [xoris r5][stw w1][3x lis][stw w0][lfd magic f0][lfd cvt f31]
// vs got [mr][mr][xoris r12][lis][stw w0][stw w1][lfd magic f0][lfd cvt f13];
// fsub/frsp output matches mgc operand not cvt operand (tried: store-order
// flips, memory barriers, mgc/cvtd frN pins, source reorder x8, -fno-sched-*).
// (b) fp=&blk web homes r11 instead of recycled r9; psq second pair f13 vs f0.
// Tried: P1-P4/V1-V3 statement permutations, full/partial pin sets, barriers.
// FLAG: -fno-schedule-insns
// family=m2c range=0x80214E24-0x80214EF4 size=208B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f64 lbl_802AF6F8;
extern f32 lbl_802AF700;
extern f32 lbl_802AF704;
extern f32 lbl_802AF708;
extern f32 cosf(f32);
extern f32 sinf(f32);
s32 fn_80214E24(s32 arg0, Unk_C7387A53 *arg1, s32 arg2) {
    union { u32 w[2]; f64 d; } cvt;
    union { struct { f32 a, b, c, d; } f; struct { f32 a, b, c, d; char _p[0x18]; } w; __ps_t p[2]; } blk;
    register f64 mgc __asm__("fr0");
    register f32 temp_f31 __asm__("fr31");
    register f32 temp_f13 __asm__("fr13");
    register f32 temp_f30 __asm__("fr30");
    register f32 temp_f1 __asm__("fr1");
    register f32 temp_f0 __asm__("fr0");
    register f32 temp_f11 __asm__("fr11");
    register f32 temp_f13_2 __asm__("fr13");
    register f32 c4 __asm__("fr12");
    register f32 c8 __asm__("fr0");
    f32 *fp;

    cvt.w[1] = (u32)arg2 ^ 0x80000000;
    __asm__ volatile("" ::: "memory");
    cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
    __asm__ volatile("" ::: "memory");
    mgc = lbl_802AF6F8;
    temp_f31 = (f32)(cvt.d - mgc);
    temp_f13 = lbl_802AF700;
    temp_f31 = temp_f31 * temp_f13;
    temp_f30 = cosf(temp_f31);
    temp_f1 = sinf(temp_f31);
    temp_f0 = *((f32 *)&arg1->unk0x58);
    temp_f11 = *((f32 *)&arg1->unk0x50);
    c4 = lbl_802AF704;
    temp_f13_2 = temp_f1 * temp_f0;
    temp_f30 = (temp_f30 * temp_f11) - temp_f13_2;
    temp_f1 = (temp_f1 * temp_f11) + (temp_f30 * temp_f0);
    fp = (f32 *)&blk;
    c8 = lbl_802AF708;
    blk.f.b = c4;
    blk.f.a = temp_f30;
    fp[2] = temp_f1;
    blk.f.d = c8;
    *(__ps_t *)arg0 = blk.p[0];
    ((__ps_t *)((char *)arg0))[1] = ((__ps_t *)fp)[1];
    return arg0;
}
