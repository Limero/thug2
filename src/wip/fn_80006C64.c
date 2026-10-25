// WIP DRAFT (non-matching) — PARKED 2026-10-04
//
// 0x80006C64 = THUG2 segment/segment closest-approach solver
//   s32 fn(Seg *s0, Seg *s1, Vec *o0, Vec *o1, f32 *ts, f32 *tt, s32 clamp)
//   r = p0-q0, d0 = s0->p1-s0->p0, d1 = s1->p1-s1->p0  (each 2 x __ps_t pairs)
//   guards: |d1.x|,|d1.y|,|d1.z| and |d0.x|,|d0.y|,|d0.z| < 1e-5  -> return 0
//   5 three-component dot products via ps_mul/ps_merge00(const 0)/ps_madd/ps_sum0
//   a=d0.d0  b=d0.d1  c=d1.d1  d=r.d1  e=r.d0
//   den = a*c - b*b ; if |den| < 1e-5 -> return 0
//   s = (b*d - c*e)/den ; *ts = s ; clamp to [0,1] when arg6 != 0
//   t = (d + b*s)/c    ; *tt = t ; clamp to [0,1] when arg6 != 0
//   *o0 = s0->p0 + d0*s ; *o1 = s1->p0 + d1*t ; return 1
// Semantics are complete and verified; every frame slot, the ps_sub store
// pattern and the tail all reproduce the want. See PARK NOTE at the bottom.
//
// family=m2c range=0x80006C64-0x80006F58 size=756B
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

/* 8-byte paired-single value with scalar lane access (recipes §5.0h). */
typedef union {
    __ps_t ps;
    struct {
        f32 hi, lo;
    } flt;
} PSV;

/* 16-byte vector = two PS pairs, loaded with 8-aligned psq_l/psq_st. */
typedef struct {
    PSV xy, zw;
} Vec;

typedef struct {
    Vec p0, p1;
} Seg;

extern __ps_t lbl_8028FD98; /* {0.0f, 0.0f} */
extern f32 lbl_8028FDE8;     /* 1e-5 */
extern f32 lbl_8028FDEC;     /* 0.0 */
extern f32 lbl_8028FDF0;     /* 1.0 */

s32 fn_80006C64(Seg *s0, Seg *s1, Vec *o0, Vec *o1, f32 *ts, f32 *tt, s32 clamp) {
    Vec r, e1, e0, ip, sd;
    /* declaration order = frame slot order for equal-refcount addressables
     * (docs/parkings/78), and the want's slots are ff,ab,gg,cd,ee */
    PSV ff, ab, gg, cd, ee, sv, tv;
    __ps_t t, z;
    f32 den, s, u, aa, cc, a2, dd, e2;

    /* base pointers: the want materializes &r and &s0->p1 in registers */
    Vec *q1 = &s0->p1;
    Vec *pr = &r;

    /* each difference goes through ip so the ps_sub result gets a home:
     * that is what emits the (dead) psq_st pair at r1+56/64 */
    ip.xy.ps = s0->p0.xy.ps - s1->p0.xy.ps;
    ip.zw.ps = s0->p0.zw.ps - s1->p0.zw.ps;
    r.xy.ps = ip.xy.ps;
    pr->zw.ps = ip.zw.ps;
    ip.xy.ps = s1->p1.xy.ps - s1->p0.xy.ps;
    ip.zw.ps = s1->p1.zw.ps - s1->p0.zw.ps;
    e1.xy.ps = ip.xy.ps;
    e1.zw.ps = ip.zw.ps;

    if ((fabsf(e1.xy.flt.hi) < lbl_8028FDE8) && (fabsf(e1.xy.flt.lo) < lbl_8028FDE8) && (fabsf(e1.zw.flt.hi) < lbl_8028FDE8)) {
        return 0;
    }

    ip.xy.ps = q1->xy.ps - s0->p0.xy.ps;
    ip.zw.ps = q1->zw.ps - s0->p0.zw.ps;
    e0.xy.ps = ip.xy.ps;
    e0.zw.ps = ip.zw.ps;

    if ((fabsf(e0.xy.flt.hi) < lbl_8028FDE8) && (fabsf(e0.xy.flt.lo) < lbl_8028FDE8) && (fabsf(e0.zw.flt.hi) < lbl_8028FDE8)) {
        return 0;
    }

    z = lbl_8028FD98;

    t = e1.zw.ps * e0.zw.ps;
    t = __builtin_ps_merge00(t, z);
    t = __builtin_ps_madd(e1.xy.ps, e0.xy.ps, t);
    ab.ps = __builtin_ps_sum0(t, t, t);

    t = e1.zw.ps * e1.zw.ps;
    t = __builtin_ps_merge00(t, z);
    t = __builtin_ps_madd(e1.xy.ps, e1.xy.ps, t);
    cd.ps = __builtin_ps_sum0(t, t, t);

    t = e0.zw.ps * e0.zw.ps;
    t = __builtin_ps_merge00(t, z);
    t = __builtin_ps_madd(e0.xy.ps, e0.xy.ps, t);
    ee.ps = __builtin_ps_sum0(t, t, t);

    t = pr->zw.ps * e1.zw.ps;
    t = __builtin_ps_merge00(t, z);
    t = __builtin_ps_madd(r.xy.ps, e1.xy.ps, t);
    ff.ps = __builtin_ps_sum0(t, t, t);

    t = pr->zw.ps * e0.zw.ps;
    t = __builtin_ps_merge00(t, z);
    t = __builtin_ps_madd(r.xy.ps, e0.xy.ps, t);
    gg.ps = __builtin_ps_sum0(t, t, t);

    /* one read each, exactly like the want (each ps_sum0 result is stored and
     * immediately reloaded through its union member) */
    aa = ab.flt.hi;
    cc = cd.flt.hi;
    a2 = ee.flt.hi;
    dd = ff.flt.hi;
    e2 = gg.flt.hi;

    den = a2 * cc - aa * aa;
    if (fabsf(den) < lbl_8028FDE8) {
        return 0;
    }

    s = (dd * aa - e2 * cc) / den;
    *ts = s;

    /* the ternary spelling is what gives the want's two-register clamp
     * (hi in one FPR, lo in the reused *ts register, both bounds loaded
     * up front) — the plain if-form collapses both into one FPR */
    if (clamp) {
        f32 hi, lo;
        hi = *ts;
        hi = (hi > lbl_8028FDF0) ? lbl_8028FDF0 : hi;
        lo = hi;
        lo = (lo < lbl_8028FDEC) ? lbl_8028FDEC : lo;
        *ts = lo;
    }

    u = (dd + aa * *ts) / cc;
    *tt = u;

    if (clamp) {
        f32 hi, lo;
        hi = *tt;
        hi = (hi > lbl_8028FDF0) ? lbl_8028FDF0 : hi;
        lo = hi;
        lo = (lo < lbl_8028FDEC) ? lbl_8028FDEC : lo;
        *tt = lo;
    }

    /* scalar -> PS splat: stfs + psq_l 128/136(r1) + ps_mr, as in the want */
    sv.flt.hi = *ts;
    o0->xy.ps = s0->p0.xy.ps + __builtin_ps_muls0(e0.xy.ps, sv.ps);
    o0->zw.ps = s0->p0.zw.ps + __builtin_ps_muls0(e0.zw.ps, sv.ps);

    tv.flt.hi = *tt;
    sd.xy.ps = __builtin_ps_muls0(e1.xy.ps, tv.ps);
    sd.zw.ps = __builtin_ps_muls0(e1.zw.ps, tv.ps);
    ip.xy.ps = s1->p0.xy.ps + sd.xy.ps;
    ip.zw.ps = s1->p0.zw.ps + sd.zw.ps;
    o1->xy.ps = ip.xy.ps;
    o1->zw.ps = ip.zw.ps;
    return 1;
}

// RE-TRIAGED 2026-10-17: still DIFF 5.3% (re-measured, body untouched — the
// 2026-10-04 reconstruction below remains the best match). Want prologue
// confirmed `stwu -0x98 / stw r31,0x94 / mr r12,r3`: the single missing word
// is the r31 save for `&r`, a pure global-alloc colouring choice (no calls in
// this leaf, so no source shape forces a callee-saved home for `pr`). No new
// lever; parking without changes.
// ============================ PARK NOTE (2026-10-04) ============================
// WHY PARKED: semantics are fully recovered; what is left is pure register /
// scheduler colouring. Official verdict DIFF 5.3% (752B vs want 756B = 1 word
// short). Discounting the single missing `stw r31,0x94(r1)` word the object is
// instruction-for-instruction identical to the want over the whole prologue
// (measured 52/187 = 27.8% masked, longest identical run 17 words from
// 0x80006C64). Baseline for this draft was DIFF 1.4% at 856B.
//
// THE MISSING WORDS: the want holds `&r` in a CALLEE-SAVED r31
// (`addi r11,r1,8` / `mr r31,r11` / `psq_st f13,8(r31)` ... `lwz r31,0x94(r1)`),
// which is also why its frame is 0x98 and mine is 0x90 (17 addressable slots +
// 4 pad + the 4-byte r31 save area). 3.9.3 keeps the same value in a VOLATILE
// register (r3 or r12 depending on the run) and emits no save. This is GCC's
// local-pointer register-class choice, not a source-shape issue: adding
// `-ffixed-r12` (or `-ffixed-r3`, alone) to the UNMODIFIED source flips it to
// r31 and produces the 0x98 frame plus stw/lwz r31. `-ffixed-r12 -ffixed-r10`
// measures 27.5% but allocates r31=arg1 / r30=&r with an `stmw r30` — a
// different shape that is not the retail allocation — so no `-ffixed` is kept
// here; the pure body is the honest reconstruction. (Project precedent for
// -ffixed exists: src/fn_80054E40.c etc.)
//
// WHAT IS REPRODUCED (all verified with tools/want_got.py + tools/ps_diff.py):
//   * every frame slot: the 6 difference pairs at 8/16/24/32/40/48, the dead
//     store / scratch pairs at 56/64 and 72/80, the 5 dot results at
//     88/96/104/112/120 (ff,ab,gg,cd,ee) and the 2 scalar->PS splats at
//     128/136;
//   * the four DEAD psq_st pairs (56/64 for all six ps_sub results, 72/80 for
//     the two ps_muls0) — doc-06 M5.0j-2r: the ps_sub result must land in an
//     addressable local that is then copied out;
//   * the want's base registers `addi rX,r1,8` + `8(rX)` (i.e. `&r`) and
//     `addi rX,r12,0x10` (i.e. `&s0->p1`) — both need an explicit
//     `Vec *` local in C, plain member access does not produce them;
//   * the eps/det guard branch layout, `mr r0,r9` (7th arg parked in r0, cr7
//     beq), the clamp blocks, and the whole o1 tail including its dead stores.
//
// REMAINING (all measured colouring/scheduling tie-breaks):
//   1. dot block FPR assignment + interleave (want f6/f10/f7/f5/f11/f9/f8 for
//      the six pair loads and the zero pair, got f8/f7/f11/f6/f13/f5/f9) and
//      the placement of the second `lis` for the zero-pair page address;
//   2. the clamp's constant-load placement: the want emits `lis r9`,`lis r11`
//      then BOTH `lfs` before the first compare, mine interleaves the second
//      `lis`/`lfs` after the first `fmr` (same 14-word block, same two
//      registers);
//   3. GPR choice for the arg0 copy (want r12, got r10) and the eps `lis` base
//      (want r10, got r11).
//
// USEFUL SIDE RESULTS FOR docs/parkings/06 + AGENTS-recipes.md:
//   * `fmsubs`/`fmadds` print as (frD, frA, frC, frB) with frD = frA*frC + frB
//     (fmadds) and frD = frA*frC - frB (fmsubs). Verified with a pinned
//     register probe (`register f32 a __asm__("fr13")`; `b*c - a` emits
//     `fmsubs f1,f5,f11,f13`, i.e. f13 - f5*f11). Consequence: the want's
//     den is `a*c - b*b` and its numerator `b*d - c*e` (the Cramer form) — NOT
//     their negations. Writing the negated form in C makes ngccc emit fmsubs
//     with the multiplicand/addend swapped.
//   * ngccc 2.95.3 DOES inline static functions with scalar/`__ps_t` args
//     (probed: `padd` inlines to one `ps_add`) but NEVER inlines a
//     struct-returning one (probed: the `bl` survives, even with `__inline__`
//     and `__attribute__((always_inline))`). So a Vec-returning helper cannot
//     explain the dead stores — addressable temporaries must.
//   * equal-refcount addressable locals take frame slots in DECLARATION order
//     (this extends docs/parkings/78, which only covers the unequal-refcount
//     race): declaring the five dot results `ff,ab,gg,cd,ee` pins them to
//     88/96/104/112/120 exactly as the want; declaration order changes nothing
//     else in the body.
//   * the clamp needs the TERNARY spelling (`hi = hi > 1 ? 1 : hi; lo = hi;
//     lo = lo < 0 ? 0 : lo;`) to get the want's two-FPR clamp + both bounds
//     preloaded: the equivalent if-form collapses to one FPR and costs 3
//     words per clamp.
// ================================================================
