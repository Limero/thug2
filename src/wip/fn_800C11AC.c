// WIP DRAFT (non-matching) — hand-rebuilt from WANT disasm 2026-09-27,
// semantic + frame rewrite 2026-10-04 (pass: <scratch>)
// family=m2c range=0x800C11AC-0x800C1538 size=908B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-04 at 37.4% (85/227 words masked; was 4.0% / 9 words with
// 852B vs 908B). HUGE improvement this round: the frame is now EXACT
// (stwu -0x110, locals [0x08,0xd4), stmw r29,r30,r31, stfd f26..f31 @0xe0,
// LR @0x114) and every stack displacement in the body matches the want.
//
// ---------------------------------------------------------------------------
// WHAT WAS WRONG BEFORE (all fixed; this is the reusable part):
//
// 1. `__builtin_ps_madds0(a,b,c)` is **a*b+c**, not a*b. The draft used it
//    everywhere the want has plain `ps_muls0`, so the compiled body was
//    `v*c + v`. Probed encodings (verified one builtin per TU, ngccc 3.9.3
//    -mps-float, four pinned FPRs):
//       __builtin_ps_madd(a,b,c)      -> ps_madd    fD,fa,fb,fc   = a*b+c
//       __builtin_ps_madds0(a,b,c)    -> ps_madds0  fD,fa,fb,fc   = a*b+c
//       __builtin_ps_madds1/muls1     -> likewise
//       __builtin_ps_muls0(a,b)       -> ps_muls0   fD,fa,fb     = a*b
//       __builtin_ps_sum0/sum1        -> ps_sum0/1  fD,fa,fb,fc
//       __builtin_ps_add/sub/div(a,b) -> ps_add/sub/div fD,fa,fb
//       __builtin_ps_merge00(a,b)     -> ps_merge00 fD,fa,fb
//    (this corrects the old header's "A=a, B=b, C=c, result A*C+B" claim.)
//
// 2. FRAME-SLOT TYPE IS THE WHOLE BALL GAME. With `-mps-float` every local is
//    PS-mode, so a slot's *declared type* decides whether GCC emits `psq_l`
//    (8-byte __ps_t operand) or `lfs` (4-byte f32) for the same read, and
//    whether a store is `psq_st W0` (4B) or `W1` (8B). The want's stack map is:
//      0x08 __ps_t  {a[0].hi, zero}          0x0c = lane1 (dead)
//      0x10 __ps_t  {a[1].hi, -}              (lane1 dead)
//      0x18 __ps_t  {-v.z, 0.0}               (n0)
//      0x20 __ps_t  { v.x, 1.0}               (n2)
//      0x28 __ps_t  rot.x      | 0x2c f32 accumulator (uninitialised in want!)
//      0x30 __ps_t  rot.y
//      0x38 __ps_t  -v.z*k3    | 0x3c f32 accumulator (also uninitialised)
//      0x40 __ps_t   v.x*k3
//      0x48 __ps_t  -v.z*k3*i178
//      0x50 __ps_t   v.x*k3*i178
//      0x58,0x60 __ps_t  dead stores of out.x / out.z
//      0x68 __ps_t {out0,out1}   0x70 __ps_t {out2, V.z}
//      0x78 __ps_t {rsq, 1.0}
//      0x80..0xa8  six 8-byte slots (c1,c2,k3,1/f170,1/f178,f170), hi lane only
//    Declaring them as `f32` arrays gets `lfs` everywhere and an 8-byte `W1`
//    store; declaring them `__ps_t` (via the P1 union for the lane puns) gets
//    `psq_l`/`psq_st W0` exactly as the want does.
//
// 3. **The `psq_l X,slot; ps_mr Y,X` copy is the tell for a SEPARATE local.**
//    The want has 8 `ps_mr`s, six of them the shape
//        psq_l  f8,  128(r1)      <- load a stack scalar slot
//        ps_mr  f10, f8          <- copy
//        ps_muls0 f0,  f0, f10   <- use #1
//        ps_muls0 f12, f12, f10  <- use #2
//    and this appears ONLY when the scalar is its own local variable read
//    twice.  If the same slot is a *struct field* of the frame template, GCC
//    loads it once straight into the use register and emits NO copy (verified
//    with a 20-line probe: separate `P1 c1;` -> psq_l+ps_mr+2x muls0;
//    `struct { ... P1 q80; }` -> psq_l+2x muls0).  So the six scalars
//    (0x80..0xa8) are declared as standalone `P1 q80..qA8;` AFTER the FR
//    struct -- GCC then lays them out at 0x80,0x88,...,0xa8 and emits the six
//    copies, which took this draft from 16% to 37% in one step.
//
// 4. Normalize chain operand order: the `ps_mul` runs on the **0x10** pair
//    (a[1]) and the `ps_madd` on the **0x08** pair (a[0]):
//        t = v2; u = v0; t = t*t; t = merge00(t, K); t = u*u + t;
//        t = sum0(t);  if (t > zero) { w = rsqrte(t); v0 = muls0(u,w);
//        rsq = w.lo; v0.hi = ...; v2 = v2*rsq; }
//    and `u = v0` must be read BEFORE the mul in source order, otherwise GCC
//    CSEs the reload and adds two ps_mr's the want doesn't have.
//
// 5. The dot product at the tail must be one nested expression
//    `V.x*M.a + (V.x*M.b + V.y*M.c)`; splitting it into named temporaries
//    costs 2 extra callee-saved FPRs (frame 0x120 instead of 0x110).
//    Reading `o->m170` into a named variable first is what produces the want's
//    extra `fmr f13,f8`.
//
// ---------------------------------------------------------------------------
// REMAINING BLOCKER (why this is parked):
//   got is 912B vs want 908B and 85/227 words match.  Three residuals, none of
//   which any plain-C spelling or flag combination tried removes:
//   (a) the want creates a frame-base register `addi r29,r1,8` in the PROLOGUE
//       and uses `8(r29)` for its six accesses to the 0x10 slot while still
//       using r1 for the 0x08 slot.  That is a reload.c `eliminate` artifact;
//       taking `&fr` (or `&fr.v0` / `&fr.v2`) and addressing through the
//       pointer DOES produce the base register, but then GCC routes *every*
//       field access through it and the frame grows to 0x108/0x120.
//   (b) one extra `ps_mr f12,f4` (got keeps a[1] live in f12 across the
//       `if (len > 0)` branch instead of reloading 0x10) and one extra
//       `ps_mr` in the tail (the want needs 1 register copy for s68/s70, got
//       needs 2).  Both are regalloc colouring, not semantics.
//   (c) the remaining ~140 mismatches are pure FPR colouring of ~45 PS ops.
//   Flag sweep at this body: default -O2 37.4%, -fno-schedule-insns2 26.9%,
//   -fno-schedule-insns 2.2%, -fno-gcse 37.0%, -fno-expensive-optimizations
//   21.1%, -fno-omit-frame-pointer 9.7%; -fomit-frame-pointer / -fno-caller-saves
//   identical to default.  None reaches 908B.
// Verified: all 8 undefined symbols (Mth_PlusOrMinus, fn_8012570C,
// lbl_80298F18, lbl_80298FEC/FF0/FF4/FF8/FFC, lbl_80299000) exist in
// config/G2TE52/symbols.txt at the addresses the want references (Mth =
// 0x80003594, rng = 0x8012570C, constants 0.0/1.0/0.5/1.5/0.2/0.8 and the
// {0,0} pair); the object's relocs are only R_PPC_ADDR16_HA/LO,
// R_PPC_REL14 and R_PPC_REL24.  No fabricated symbols.
#include "types.h"
#include "qb_constants.h"

typedef union {
    __ps_t p;
    struct { f32 hi, lo; } f;
} P1;

typedef struct {
    P1 v0, v2;
    P1 n0, n2;
    P1 p28, p30, p38, p40, p48, p50;
    P1 d58, d60;
    P1 s68, s70;
    P1 p78;
} FR;

typedef struct {
    char pad0[0x30];
    P1 v30, v38;
    char pad40[0x10];
    P1 m50, m58;
    s32 w60, w64;
    char pad68[0x48];
    P1 fB0, fB8, fC0, fC8;
    f32 mD0, mD4, mD8, mDC;
    f32 mE0, mE4, mE8, mEC;
    f32 mF0, mF4, mF8, mFC;
    char pad100[0x34];
    f32 f134;
    char pad138[0x38];
    f32 f170, f174, f178;
} S;

extern __ps_t lbl_80298F18;
extern f32 lbl_80298FEC;
extern f32 lbl_80298FF0;
extern f32 lbl_80298FF4;
extern f32 lbl_80298FF8;
extern f32 lbl_80298FFC;
extern f32 lbl_80299000;

f32 Mth_PlusOrMinus(f32);
f32 fn_8012570C(u32, s32);

void fn_800C11AC(S *o, __ps_t *a) {
    FR fr;
    P1 ln;
    P1 q80, q88, q90, q98, qA0, qA8;
    __ps_t t, e, u, w;
    f32 zero = lbl_80298FEC;
    f32 one;
    f32 f31, f28, f27;
    f32 d0, d1, d2, d3, d4, d5, d6, d7, d8;
    __ps_t a3, a5, a6, a7, a8, a9, a10;

    fr.v0.p = a[0];
    fr.v2.p = a[1];
    fr.v0.f.lo = zero;

    t = fr.v2.p;
    u = fr.v0.p;
    t = __builtin_ps_mul(t, t);
    t = __builtin_ps_merge00(t, lbl_80298F18);
    t = __builtin_ps_madd(u, u, t);
    t = __builtin_ps_sum0(t, t, t);
    ln.p = t;
    if (ln.f.hi > zero) {
        w = __builtin_ps_rsqrte(t);
        fr.p78.p = w;
        fr.v0.p = __builtin_ps_muls0(u, w);
        fr.p78.f.lo = lbl_80298FF0;
        fr.v2.p = __builtin_ps_mul(fr.v2.p, fr.p78.p);
    }

    fr.n0.f.hi = -fr.v2.f.hi;
    fr.n2.f.hi = fr.v0.f.hi;
    one = lbl_80298FF0;
    fr.n2.f.lo = one;
    fr.n0.f.lo = zero;

    f31 = Mth_PlusOrMinus(lbl_80298FF4);
    f31 = (f31 + one) * fn_8012570C(QB_UNKNOWN_0x3DB3FA83, 0);
    q80.f.hi = f31;
    f31 = Mth_PlusOrMinus(lbl_80298FF8);
    q88.f.hi = f31 * fn_8012570C(QB_UNKNOWN_0x39E99FEC, 0);
    f31 = Mth_PlusOrMinus(lbl_80298FFC);
    fn_8012570C(QB_UNKNOWN_0x738500FD, 0);
    f31 += one;

    t = __builtin_ps_muls0(fr.v0.p, q80.p);
    e = __builtin_ps_muls0(fr.n0.p, q88.p);
    fr.p38.p = t;
    fr.p48.p = e;
    fr.p28.p = __builtin_ps_add(t, e);
    u = __builtin_ps_muls0(fr.v2.p, q80.p);
    fr.p40.p = u;
    fr.p28.f.lo = f31 * lbl_80298FFC + fr.p28.f.lo;
    fr.p50.p = __builtin_ps_muls0(fr.n2.p, q88.p);
    fr.p30.p = __builtin_ps_add(u, fr.p50.p);

    f28 = Mth_PlusOrMinus(lbl_80298FF8) * fn_8012570C(QB_UNKNOWN_0x14DDB3EF, 0);
    f31 = Mth_PlusOrMinus(lbl_80299000);
    f31 = (f31 + one) * fn_8012570C(QB_UNKNOWN_0x4088E6EC, 0);
    q90.f.hi = f31;
    qA0.f.hi = one / o->f178;
    d1 = o->f170;
    f27 = one / d1;
    qA8.f.hi = d1;
    q98.f.hi = f27;

    t = __builtin_ps_muls0(fr.n0.p, q90.p);
    u = __builtin_ps_muls0(fr.n2.p, q90.p);
    fr.p38.p = t;
    fr.p40.p = u;
    a7 = o->m50.p;
    a8 = o->m58.p;
    a9 = o->v30.p;
    a10 = o->v38.p;
    fr.p50.p = __builtin_ps_muls0(fr.p40.p, qA0.p);
    fr.p38.f.lo = fr.p38.f.lo + f28;
    a8 = __builtin_ps_add(a8, fr.p50.p);
    a3 = __builtin_ps_muls0(fr.p30.p, q98.p);
    o->m58.p = a8;
    fr.p48.p = __builtin_ps_muls0(fr.p38.p, qA0.p);
    a7 = __builtin_ps_add(a7, fr.p48.p);
    o->m50.p = a7;
    a5 = __builtin_ps_muls0(fr.p28.p, q98.p);
    a10 = __builtin_ps_add(a10, a3);
    a9 = __builtin_ps_add(a9, a5);
    o->v38.p = a10;
    o->v30.p = a9;
    o->fB8.p = __builtin_ps_muls0(o->v38.p, qA8.p);
    o->fB8.f.lo = zero;
    o->fB0.p = __builtin_ps_muls0(o->v30.p, qA8.p);

    fr.s68.f.hi = o->m58.f.hi * o->mF0
                 + (o->m50.f.hi * o->mD0 + o->m50.f.lo * o->mE0);
    fr.s68.f.lo = o->m58.f.hi * o->mF4
                 + (o->m50.f.hi * o->mD4 + o->m50.f.lo * o->mE4);
    fr.d58.p = fr.s68.p;
    o->fC0.p = fr.s68.p;
    fr.s70.f.hi = o->m58.f.hi * o->mF8
                 + (o->m50.f.hi * o->mD8 + o->m50.f.lo * o->mE8);
    fr.s70.f.lo = o->m58.f.lo;
    fr.d60.p = fr.s70.p;
    o->fC8.p = fr.s70.p;
    o->f134 = fn_8012570C(QB_UNKNOWN_0x771922A6, 0);
    o->w64 = 0;
    o->w60 = 1;
}