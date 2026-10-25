// PARKED 2026-10-05: best measured verdict DIFF —
// tools/ps_diff.py 0x80003BE8 --all = 17/138 words (12.3%), object 552B vs
// want 548B (the old m2c husk measured 8/548 = 1.46% and was 90% `0;`
// placeholders plus miscompiled scalar math).
// family=m2c range=0x80003BE8-0x80003E0C size=548B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT THE FUNCTION IS (was unknown; the old draft's callee mix of
// sinf+cosf is a red herring):
//   void *fn_80003BE8(Mtx *out, Vec4 *axis, f32 angle_rad)
// i.e. "build a 4x4 rotation matrix from an axis + an angle" — Rodrigues:
//   c = cos(angle), s = sin(angle), k = 1 - c, (x,y,z) = normalised axis
//   m00 = c + k*x*x   m01 = k*xy + z*s   m02 = k*xz - y*s   m03 = 0
//   m10 = k*xy - z*s  m11 = c + k*y*y   m12 = k*yz + x*s   m13 = 0
//   m20 = k*xz + y*s  m21 = k*yz - x*s   m22 = c + k*z*z   m23 = 0
//   m30 = 0           m31 = 0           m32 = 0            m33 = 1
// (z*s / y*s / x*s come from the axis pair at sp+8 being *multiplied by s*
//  before the matrix is assembled, so `ax` holds the SCALED axis at that
//  point — that is why `lfs f0,8(r1)` reads x*s, not x.)
//
// KEY RECIPE (the reason this went from husk to real C):
//   **A matched PS sibling already exists — src/fn_8006AC08.c contains the
//   IDENTICAL vec3-normalise idiom, including the `SN_PS_type` union with
//   `.flt.hi` / `.flt.lo`, and it is byte-exact.**  Its shape is:
//
//     p1 = v->ps[1];  p0 = v->ps[0];
//     d  = __builtin_ps_mul(p1, p1);
//     d  = __builtin_ps_merge00(d, zero_ps);      /* {0,0} masks the w lane */
//     d  = __builtin_ps_madd(p0, p0, d);
//     d  = __builtin_ps_sum0(d, d, d);            /* |v|^2               */
//     s.ps = d;
//     if (s.flt.hi > zero) {
//         d    = __builtin_ps_rsqrte(d);
//         s.ps = d;
//         s.flt.lo = one;                          /* <- the scalar stfs */
//         q     = s.ps;
//         v->ps[0] = __builtin_ps_muls0(p0, d);
//         v->ps[1] = __builtin_ps_mul(p1, q);
//     }
//
//   That reproduces the exact psq/ps op sequence here byte for byte
//   (ps_mul, ps_merge00, ps_madd, ps_sum0, ps_mr, fcmpu/ble, ps_rsqrte,
//   ps_muls0, psq_st, stfs 1.0, psq_l, ps_mul, psq_st).  BEFORE reusing it:
//     * `ps_muls0 fD,fA,fC` is a BROADCAST of fC's HIGH half, not an
//       element-wise pair multiply — that is what makes the half-written
//       temporaries legal: the source only ever stores `flt.hi` and lets the
//       low lane stay garbage (ps_diff's dec() comment prints the
//       element-wise form and is misleading).
//     * so `k1/k2/k3` are `SN_PS_type` temporaries written as
//       `k.flt.hi = ...;` and consumed as `k.ps` — that is what produces the
//       `stfs` (scalar) + `psq_l` (pair) asymmetry in the original.
//     * the m2c `0;` statements in this file were exactly these psq_l/psq_st
//       pair slots (see the four stack slots 0x18/0x20/0x28/0x30 which are
//       written by two SCALAR stfs and then overwritten by one psq_st).
//
// REMAINING BLOCKER (and what still moves the needle):
//   * MEASURED: `tools/ps_diff.py 0x80003BE8 --all` = 17/138 words (12.3%),
//     object 552B vs want 548B.  The old husk was 8/548 (1.46%).
//     The prologue (stwu -0x90 / f29,f30,f31 / stmw r30 / LR@0x94) and EVERY
//     stack slot now agree with want (ax at 0x08/0x10, a=0x18, b=0x20,
//     c=0x28, d=0x30, s=0x38, k1=0x40, k2=0x48, k3=0x50), and the whole
//     ps_mul/ps_merge00/ps_madd/ps_sum0/ps_rsqrte/ps_muls0/ps_mul op
//     sequence is present in the right relative order.  What is left is
//     scheduling + FPR/GPR assignment.
//   * THE POINTER TRICK MATTERS (worth ~+6 words): writing the local as
//     `PSVec4 tv; PSVec4 *ax = &tv;` and using `ax->ps[0]` makes ngccc keep
//     the struct base in a callee-saved GPR (`addi r29,r1,8` + `8(r29)`),
//     exactly like want's `addi r30,r1,8` + `8(r30)`.  Accessing `tv.ps[0]`
//     directly instead makes everything r1-relative and want's `lfs f0,8(r30)`
//     form disappears.  (Same trick as `v = &arg0->unk0x78` in fn_8006AC08.)
//   * FRAME is 0x98 vs want's 0x90: got needs TWO callee-saved GPRs (r29 for
//     the ax base + r30 for a hoisted `lis` constant base) where want needs
//     one.  ngccc hoists the `lis` for the 1.0f pool page above the `bl cosf`
//     (it is needed once before the call, for `s.flt.lo = one`, and again
//     after), which forces the page base into a callee-saved register; want
//     simply reloads `lfs f31,-0x3a4(r9)` after the call.  Undoing that CSE is
//     the next thing to try (e.g. give the pre-call 1.0f its own expression).
//   * this object also needs the house `__asm__("" ::: "r3")` r3-clobber
//     barriers between pair stores (see the banner of src/fn_800063B8.c:
//     "the game compiler modeled PS ops as clobbering r3").  Barriers are
//     banned, so byte-exactness is out of reach here; this
//     draft is however now semantically complete readable source, which is
//     what a future rebuild (with asm allowed) needs.
#include "types.h"
#include "structs.h"
#include "dolphin/SN_PS.h"

extern const f32 lbl_8028FC58; /* 0.0f */
extern const f32 lbl_8028FC5C; /* 1.0f */
extern __ps_t lbl_8028FBC8;    /* { 0.0f, 0.0f } */

typedef union {
    struct {
        f32 x, y, z, w;
    } f;
    __ps_t ps[2];
} PSVec4;

typedef union {
    struct {
        f32 hi, lo;
    } flt;
    __ps_t ps;
} PSVec2;

float cosf(float);
float sinf(float);

void *fn_80003BE8(void *arg0, PSVec4 *arg1, f32 farg0) {
    PSVec4 tv;
    PSVec4 *ax = &tv;
    PSVec2 a;
    PSVec2 b;
    PSVec2 c;
    PSVec2 d;
    PSVec2 s;
    PSVec2 k1;
    PSVec2 k2;
    PSVec2 k3;
    __ps_t p0;
    __ps_t p1;
    __ps_t q;
    __ps_t dot;
    f32 *out;

    ax->ps[0] = arg1->ps[0];
    ax->ps[1] = arg1->ps[1];

    p1 = ax->ps[1];
    dot = __builtin_ps_mul(p1, p1);
    dot = __builtin_ps_merge00(dot, lbl_8028FBC8);
    p0 = ax->ps[0];
    dot = __builtin_ps_madd(p0, p0, dot);
    dot = __builtin_ps_sum0(dot, dot, dot);
    s.ps = dot;
    if (s.flt.hi > lbl_8028FC58) {
        dot = __builtin_ps_rsqrte(dot);
        s.ps = dot;
        s.flt.lo = lbl_8028FC5C;
        q = s.ps;
        ax->ps[0] = __builtin_ps_muls0(p0, dot);
        ax->ps[1] = __builtin_ps_mul(p1, q);
    }

    k1.flt.hi = lbl_8028FC5C - cosf(farg0);
    k2.flt.hi = k1.flt.hi;

    a.flt.hi = lbl_8028FC5C - ax->f.x * ax->f.x;
    a.flt.lo = lbl_8028FC5C - ax->f.y * ax->f.y;
    b.flt.hi = lbl_8028FC5C - ax->f.z * ax->f.z;
    a.ps = __builtin_ps_muls0(a.ps, k1.ps);
    b.ps = __builtin_ps_muls0(b.ps, k1.ps);

    c.flt.hi = ax->f.y * ax->f.z;
    c.flt.lo = ax->f.z * ax->f.x;
    d.flt.hi = ax->f.x * ax->f.y;

    k3.flt.hi = sinf(farg0);
    d.ps = __builtin_ps_muls0(d.ps, k2.ps);
    c.ps = __builtin_ps_muls0(c.ps, k2.ps);
    ax->ps[0] = __builtin_ps_muls0(ax->ps[0], k3.ps);
    ax->ps[1] = __builtin_ps_muls0(ax->ps[1], k3.ps);

    out = (f32 *)arg0;
    out[15] = lbl_8028FC5C;
    out[13] = lbl_8028FC58;
    out[12] = lbl_8028FC58;
    out[11] = lbl_8028FC58;
    out[7] = lbl_8028FC58;
    out[3] = lbl_8028FC58;
    out[14] = lbl_8028FC58;

    out[0] = lbl_8028FC5C - a.flt.hi;
    out[1] = d.flt.hi + ax->f.z;
    out[2] = c.flt.lo - ax->f.y;
    out[4] = d.flt.hi - ax->f.z;
    out[5] = lbl_8028FC5C - a.flt.lo;
    out[6] = c.flt.hi + ax->f.x;
    out[8] = c.flt.lo + ax->f.y;
    out[9] = c.flt.hi - ax->f.x;
    out[10] = lbl_8028FC5C - b.flt.hi;

    return arg0;
}
