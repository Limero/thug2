// WIP DRAFT — hand-rebuilt rational-conic (ellipse segment) evaluator; the
// X/Z accumulation is written with the paired-single builtins.
// family=m2c range=0x8003EF58-0x8003F208 size=688B
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// === PARKED (2026-10-01) — DIFF, masked 4/181 (2.2%), object 724B
//     vs want 688B (172 insns). Opcode-histogram overlap 142/172 = 83%.
//     tools/ps_diff.py 0x8003EF58   |   test_wip_drafts.py --addr 0x8003EF58
//
// WHAT THE FUNCTION IS (fully decoded from the DOL, no unknowns left):
//   fn_8003EF58(Vec3 *p0, Vec3 *p1, Vec3 *p2, s32 n, s32 a4, s32 a5,
//               f32 fa, f32 fb)
//   Rational-quadratic-conic evaluator over n equal arcs. Preheader:
//   tt = fb/fa; k = 1.0f - tt*tt; dn = (f32)(f64)n. Then, for i = n-1..0
//   (post-decrement latch, guarded by `if (n == 0)` on the ORIGINAL n):
//     a1 = 2*pi*i/dn ;  a2 = 2*pi*(i+1)/dn
//     k2 = 1.0f - k                       (rematerialised at the loop top)
//     r1 = fa*sqrtf(k2 / (1.0f - k*cosf(a1)^2))   <- cosf is called TWICE
//     r2 = fa*sqrtf(k2 / (1.0f - k*cosf(a2)^2))      per radius (once per
//     s1 = r1*cosf(a1) ; s2 = r1*sinf(a1)             argument, no CSE)
//     s3 = r2*cosf(a2) ; s4 = r2*sinf(a2)
//     o08 = p0.xz + p1.xz*s1 + p2.xz*s2     (arg1 of the callee)
//     o18 = p0.xz + p1.xz*s3 + p2.xz*s4     (arg2;  0x18 stack slot)
//     fn_8003EF4C(&o08, &o18, a4, 0, a5)
//   The muls0 shape proves the C was `x*(1+s)`-style: ps_muls0 fD,fD,fS
//   (fd = fa + fc*fd) with the scalar splatted into the pair's high lane.
//   fn_8003EF4C is a 4-byte `blr` STUB in the DOL, so the call is a no-op.
//
// WANT FPR MAP (10 saved: f22..f31) | GPR MAP (7 saved: r25..r31)
//   f22=lbl_802922A0=pi   f23=fa   f24=dn=(f32)(f64)n   f25=2^52 (magic)
//   f26=lbl_802922A4=1.0f f27=k    f28=k2, later r2      f29=r1
//   f30=a2   f31=a1   scratch f0/f1/f10/f11/f12/f13
//   r25=a4 r26=a5 r27=0x4330 scratch r28=p0 r29=p1 r30=p2 r31=i
// WANT LOCALS: 0x08/0x10 o08, 0x18/0x20 o18, three DEAD 8-byte product pairs
//   at 0x28, 0x38, 0x48, four 8-BYTE-SPACED scalar slots at 0x58/0x60/0x68/0x70
//   (s1..s4), int->f64 pair at 0xd0, Gsave 0xdc, LR 0x14c, frame 0x148.
//
// VERIFIED RIGHT IN THIS DRAFT (do not re-derive):
//   * `(f32)(f64)<s32>` in plain C reproduces want's whole cast dance
//     (xoris ,0x8000 / lis 0x4330 / stw lo+hi / lfd / fsub / frsp) AND the
//     dead `mr r10,r11` artifact of the `(f32)(f64)(i+1)` expander.
//   * `t.ps = __builtin_ps_muls0(<f32 lvalue>, <f32 local>)` emits a REAL
//     ps_muls0 + ps_add + psq_st chain; `s.flt.hi = expr` gives want's
//     stfs + psq_l(<slot>,W0) + ps_mr SF->PS conversion.
//
// THE WALL (compiler, not source shape) — ngccc 3.9.3 PS emission, probed:
//   1. `__builtin_ps_muls0` ACCEPTS ONLY `f32` arguments. Passing a PS-mode
//      value (`sn_ps`, `*(sn_ps*)&v.x`, `__ps_t *`) is rejected ("incompatible
//      type for argument 2") or ICEs in the backend ("internal error--
//      unrecognizable insn"). 3.7 / 3.8.1 ICE at optabs.c:4111 instead.
//   2. With (f32, f32) the FIRST operand is consumed straight from its FPR,
//      so its load is always `lfs` — never `psq_l`. With any PS-typed operand
//      the load degenerates to `lq rD,d(rA)` (GPR pair) and the PS op is
//      replaced by VMX garbage: vextdubvlx / vsel / xxsldwi / xsmaddasp.
//      `__builtin_ps_add(f32, PS)` survives; muls0(PS, ..) never does.
//   3. A PS-mode load whose lane 1 is dead is NARROWED to `lfs` by cc1
//      (`t.ps = *(sn_ps*)&v.x; out->x = t.flt.hi;` folds to one `lfs`), so
//      want's full 8-byte `psq_l f0,0(rA),W0` pair loads (20 of them) cannot
//      be produced from any SF-narrowable C source.
//   Diagnostic: want has psq_l x20 / psq_st x16 / lfs x2; this draft emits
//   psq_l x2 / psq_st x8 / lfs x24. That 18-load gap IS the blocker; the rest
//   (frame 0x148 vs 0x118, 10 vs 8 saved FPRs, 7 vs 11 saved GPRs, the
//   hoisted `addi r30,r1,8` output addresses, PS-reg colouring) is the
//   downstream allocator cascade it causes.
//   Flags measured, all inert: -fno-gcse 2.2%, -fno-schedule-insns2 2.2%,
//   -fno-schedule-insns 0.6%, -O1 1.6%, default 1.7%.
// NOT TRIED: hard `register f32 __asm__("frN")` pins on the ten cross-call
// values (to force the 10-FPR save + the 0x148 frame), and reviving the
// 18 psq_l loads through the `volatile __ps_t` self-copy trick doc-06 uses
// for the lq/xs artifacts.
#include "types.h"
#include "dolphin/SN_PS.h"

extern f32 lbl_802922A0;
extern f32 lbl_802922A4;
extern f32 cosf(f32);
extern f32 sinf(f32);
extern f32 sqrtf(f32);
void fn_8003EF4C(void *, void *, s32, s32, s32);

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3;

typedef struct {
    f32 x;
    f32 z;
} XZ;

void fn_8003EF58(V3 *p0, V3 *p1, V3 *p2, s32 n, s32 a4, s32 a5, f32 fa, f32 fb) {
    XZ o08;
    XZ o18;
    XZ mid;
    SN_PS_type t1, t2, u1, u2;
    f32 s1, s2, s3, s4;
    f32 tt, k, k2, r1, r2, a1, a2, c, dn;
    s32 i;

    i = n - 1;
    if (n == 0) {
        return;
    }
    tt = fb / fa;
    k = lbl_802922A4 - (tt * tt);
    dn = (f32)(f64)n;
    do {
        a1 = 2.0f * (f32)(f64)i * lbl_802922A0 / dn;
        a2 = 2.0f * (f32)(f64)(i + 1) * lbl_802922A0 / dn;
        k2 = lbl_802922A4 - k;
        c = cosf(a1);
        r1 = fa * sqrtf(k2 / (lbl_802922A4 - k * (c * c)));
        c = cosf(a2);
        r2 = fa * sqrtf(k2 / (lbl_802922A4 - k * (c * c)));
        s1 = r1 * cosf(a1);
        t1.ps = __builtin_ps_muls0(p1->x, s1);
        t2.ps = __builtin_ps_muls0(p1->z, s1);
        u1.ps = __builtin_ps_add(p0->x, t1.ps);
        u2.ps = __builtin_ps_add(p0->z, t2.ps);
        o18.x = u1.flt.hi;
        o18.z = u2.flt.hi;
        s2 = r1 * sinf(a1);
        t1.ps = __builtin_ps_muls0(p2->x, s2);
        t2.ps = __builtin_ps_muls0(p2->z, s2);
        u1.ps = __builtin_ps_add(o18.x, t1.ps);
        u2.ps = __builtin_ps_add(o18.z, t2.ps);
        o08.x = u1.flt.hi;
        o08.z = u2.flt.hi;
        s3 = r2 * cosf(a2);
        t1.ps = __builtin_ps_muls0(p1->x, s3);
        t2.ps = __builtin_ps_muls0(p1->z, s3);
        u1.ps = __builtin_ps_add(p0->x, t1.ps);
        u2.ps = __builtin_ps_add(p0->z, t2.ps);
        mid.x = u1.flt.hi;
        mid.z = u2.flt.hi;
        s4 = r2 * sinf(a2);
        t1.ps = __builtin_ps_muls0(p2->x, s4);
        t2.ps = __builtin_ps_muls0(p2->z, s4);
        u1.ps = __builtin_ps_add(mid.x, t1.ps);
        u2.ps = __builtin_ps_add(mid.z, t2.ps);
        o18.x = u1.flt.hi;
        o18.z = u2.flt.hi;
        fn_8003EF4C(&o08, &o18, a4, 0, a5);
    } while (i-- != 0);
}
