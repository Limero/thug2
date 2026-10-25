// WIP DRAFT (non-matching) — hand reconstruction from the retail disassembly
// PARKED 2026-10-05 (w_8002BC78): best 7.43% DIFF, 700B/700B (length EXACT).
//   Residual (162/175 words differ; the op SEQUENCE now matches retail almost
//   1:1 — the whole ps_mul/merge00/madd/sum0/rsqrte/res block, both muls0 dot
//   accumulators, the merge10 cross terms, the sC0 union idiom and the
//   fmsubs tail all emit the same opcodes in the same order). What blocks a
//   byte match:
//   (1) FRAME 0x170 vs retail 0x108. Local slots themselves DO land on retail's
//       offsets (8/16/20/24/28..36/40..200 verified identical), but ngccc adds
//       three spill slots (0xec = the M[3] scalar, 0xf4 + 0x12c = a spilled
//       1.0f) because it allocates the 1.0f/`zero`/`one` constants to
//       caller-saved PS FPRs. That pushes stmw/stfd/lmw/lfd/lwz off by 0x68.
//   (2) GCC 2.95 register allocation over ~90 PS ops: every value is one or two
//       FPRs off retail (want f8/f7/f4/f5/f11/f12/f13 ... got f7/f6/f4/f5/...).
//   (3) ADDRESS-PSEUDO COST MODEL: retail rematerialises `lis`+disp per use
//       (lbl_802916BC is re-loaded 3x, lbl_80291680 2x); here the address gets
//       CSE'd into a callee-saved GPR (`lis r9; addi r27,r9,0`) instead.
//   (4) 12 provably DEAD 8-byte stores in retail (write-only psq_st at
//       0x38,0x40,0x48,0x50,0x68,0x70,0x78,0x80,0x88,0x90,0x98,0xA0 — verified
//       by a full r1-relative read/write census of the function). They are
//       reproduced here via 12 `volatile __ps_t` shims, but the compiler puts
//       them in its own order/slots, so they cannot land on retail's offsets.
//       They are also why retail's locals are exactly 0x08..0xCF (200B:
//       3 x 16B arrays + 18 x 8B pair slots) — the slot budget is fixed.
//   (5) Block layout: retail's `if (len > 0.0f)` merge point is 4 instructions
//       after the branch; here GCC sinks the merge point to the end of the
//       straight-line region (ble -> 0x8002BE14 instead of 0x8002BD54).
//   Ruled out: -Os / other flag sets (function is 700B of straight-line math);
//   register pins (`register f32 one __asm__("fr14")` -> 844B, strictly worse);
//   writing the two late 1.0f uses as direct global reads (v5a 1.14%, v5b
//   716B, both 704B — all below the 7.43% body); inlining the A[] pair loads
//   to drop temps; moving the constant loads after the fn_8002B900 call is
//   what fixed the length (v3 712B -> v4 700B), so that one IS load-bearing.
//   Previous body (stock m2c draft) scored 1.69% with 472B/700B — the
//   statics-as-file-scope DCE pathology; this replaces it.
// family=m2c range=0x8002BC78-0x8002BF34 size=700B
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef union {
    __ps_t ps;
    f32 f[2];
} P2;

typedef struct {
    f32 x, y, z, w;
} V4;

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    P2 q[2];
    f32 unk0x20;
    f32 unk0x24;
    f32 unk0x28;
    f32 unk0x2c;
    s32 unk0x30;
} SelfT;

extern f32 lbl_802916B8;
extern f32 lbl_802916BC;
extern f32 lbl_802916C0;
extern f32 lbl_802916C4;
extern f32 lbl_802916C8;
extern __ps_t lbl_80291680;
#define ZP (*(volatile __ps_t *)&lbl_80291680)
extern char lbl_80291768[];

void *fn_8002B900(void *, s32);
void fn_8002C904(void *, f32, f32, f32);
void fn_8002C8FC(void *, f32);
f32 fn_80271170(f32);
f32 fn_80271070(f32);

void *fn_8002BC78(SelfT *arg0, s32 arg1, f32 *arg2, f32 *arg3, s32 arg4) {
    V4 V;
    volatile f32 A[4];
    volatile f32 R[4];
    volatile __ps_t s38, s40, s48, s50, s68, s70, s78, s80, s88, s90, s98, sA0;
    volatile SN_PS_type sA8, sB0, sB8, sC0, sC8, s58, s60;
    __ps_t p0, p1, z, d;
    __ps_t f0, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13;
    f32 t, x, sc, g, f30, f31, f2, f3, zero, one;

    fn_8002B900(arg0, arg1);
    zero = lbl_802916B8;
    one = lbl_802916BC;

    arg0->unk0x8 = (s32)lbl_80291768;
    arg0->q[0].f[0] = zero;
    arg0->q[1].f[1] = one;
    arg0->q[0].f[1] = zero;
    arg0->q[1].f[0] = zero;
    A[0] = one;
    A[2] = zero;
    A[1] = zero;
    A[3] = one;

    p0 = *(volatile __ps_t *)&A[0];
    p1 = *(volatile __ps_t *)&A[2];
    z = ZP;
    d = __builtin_ps_mul(p1, p1);
    t = lbl_802916C0;
    g = lbl_802916C4;
    d = __builtin_ps_merge00(d, z);
    f30 = lbl_802916C0 * lbl_802916C4 * lbl_802916C8;
    d = __builtin_ps_madd(p0, p0, d);
    d = __builtin_ps_sum0(d, d, d);
    d = __builtin_ps_rsqrte(d);
    d = __builtin_ps_res(d);
    sA8.ps = d;
    x = sA8.flt.hi;
    f31 = x;
    if (f31 > zero) {
        f31 = one / f31;
    }
    sc = f31 * fn_80271170(f30);
    fn_8002C904(&V, sc * A[0], sc * A[1], sc * A[2]);
    fn_8002C8FC(&V, fn_80271070(f30));

    f5 = *(volatile __ps_t *)&V.z;
    f2 = V.w;
    s50 = f5;
    f8 = *(volatile __ps_t *)&arg2[0];
    f7 = *(volatile __ps_t *)&arg2[2];
    f4 = *(volatile __ps_t *)&V.x;
    *(volatile __ps_t *)&R[2] = f7;
    f12 = __builtin_ps_merge10(f8, f7);
    sB8.flt.hi = f2;
    f11 = __builtin_ps_merge10(f4, f5);
    f3 = R[3];
    f13 = __builtin_ps_merge00(f7, f8);
    f11 = __builtin_ps_mul(f8, f11);
    *(volatile __ps_t *)&R[0] = f8;
    sB0.flt.hi = f3;
    f12 = __builtin_ps_mul(f12, f4);
    f10 = sB0.ps;
    f0 = __builtin_ps_merge00(f4, f5);
    f13 = __builtin_ps_mul(f13, f0);
    f11 = __builtin_ps_sub(f11, f12);
    f12 = sB8.ps;
    sC0.ps = __builtin_ps_merge00(f11, f11);
    f9 = f12;
    f12 = __builtin_ps_muls0(f4, f0);
    sC0.flt.lo = one;
    f6 = __builtin_ps_muls0(f8, f9);
    s78 = f12;
    f13 = __builtin_ps_sub(f13, __builtin_ps_merge10(f13, f13));
    s88 = f6;
    f12 = __builtin_ps_add(f12, f6);
    f11 = __builtin_ps_merge10(f11, f13);
    s68 = f12;
    f0 = __builtin_ps_muls0(f5, f0);
    s98 = f11;
    f9 = __builtin_ps_muls0(f7, f9);
    s80 = f0;
    f12 = __builtin_ps_add(f12, f11);
    s90 = f9;
    f11 = sC0.ps;
    f0 = __builtin_ps_add(f0, f9);
    s58.ps = f12;
    f10 = f4;
    s70 = f0;
    f13 = f11;
    f0 = __builtin_ps_add(f0, f13);
    sA0 = f13;
    f12 = f8;
    s60.ps = f0;
    s38 = f12;
    f7 = __builtin_ps_mul(f7, f5);
    f12 = s58.flt.hi;
    f13 = *(volatile __ps_t *)&arg2[2];
    f0 = s58.flt.lo;
    s40 = f13;
    s48 = f10;
    f13 = s60.flt.hi;
    R[0] = f12;
    R[1] = f0;
    R[2] = f13;
    f0 = ZP;
    f11 = *(volatile __ps_t *)&R[0];
    f7 = __builtin_ps_merge00(f7, f0);
    f8 = __builtin_ps_madd(f8, f4, f7);
    *(volatile __ps_t *)&A[0] = f11;
    f12 = f11;
    arg0->q[0].ps = f12;
    f8 = __builtin_ps_sum0(f8, f8, f8);
    sC8.ps = f8;
    f12 = one;
    f13 = sC8.flt.hi;
    f3 = f3 * f2 - f13;
    R[3] = f3;
    f0 = *(volatile __ps_t *)&R[2];
    arg0->q[1].ps = f0;
    f10 = *(volatile __ps_t *)&R[2];
    f13 = arg3[0];
    *(volatile __ps_t *)&A[2] = f10;
    arg0->unk0x20 = f13;
    f0 = arg3[2];
    arg0->unk0x24 = f0;
    f13 = arg3[1];
    arg0->unk0x2c = f12;
    f13 = -f13;
    arg0->unk0x30 = arg4;
    arg0->unk0x28 = f13;
    return arg0;
}