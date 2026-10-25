// WIP DRAFT (non-matching) — hand reconstruction of the vector-orthogonalise /
// clamp helper at 0x800C3A24.
// family=m2c range=0x800C3A24-0x800C3C00 size=476B
// extra_cflags: -mps-float
//
// PARKED 2026-10-03 (b10): DIFF 32.8% masked, but .text is now LENGTH-EXACT
// (476B == symbols.txt size:0x1DC), so every remaining diff is a real diff.
// Reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//            tools/test_wip_drafts.py --addr 0x800C3A24
//            (test_wip_drafts prints nothing below 50%; the pct above comes from
//             tools/want_vs_got.py + masked_pct, i.e. the same masking.)
// Baseline for this draft was DIFF 17.6% at **424B** — i.e. 52 bytes SHORT, so
// that 17.6% was pure positional coincidence. It went UP, not down, and the
// old body was semantically wrong (see CORRECTIONS 1-3).
//
// WHAT IS EXACT NOW (instruction-for-instruction, registers aside):
//   * every length — got == want == 476B == 119 words;
//   * the whole 0x00..0x58 guard chain (23 w, correct branch polarity);
//   * the main-dot chain 0x5C..0xB3 (21 w): psq_l/ps_mul/ps_merge00 from the
//     lbl_80298F18 pair, ps_madd, ps_sum0, ps_rsqrte, ps_res, the
//     `psq_st`/`lfs`/`fmr` triple for `x = e.hi`, the `ps_mr`+`fmuls` for
//     `y = sum*(f158*f1C4)`, fcmpu+ble;
//   * the 7-instruction `y > x` arm (0xB4..0xCF) INCLUDING the store order
//     0x50, 0x58, 0x5c, 0x54;
//   * the whole tail clamp block 0x1BC..0x1DF (fsubs/fadds/stfs/blr shapes).
//
// CORRECTIONS vs the previous (m2c-derived) draft — all verified off the want:
//   1. f5 is a PRODUCT `sum * (f158*f1C4)`: the want has `fmuls f12,f12,f11`
//      (0x3ABC) then `fmuls f5,f11,f12` (0x3AC8).  The old draft computed
//      `y = (-s)*s + sc`, an `fmadds`, which is not what the want computes.
//   2. The ps_muls0/ps_sub chain lives INSIDE the `y <= x` arm.  The `y > x`
//      arm is the 7-word store block + `b 0x3B80` (the four floats at o+0x50
//      become 0,0,0,1).  The old draft had no such arm: that is where 52 of the
//      52 missing bytes were.
//   3. The guard inside that arm is `sum > 0.0f` (want: `fcmpu cr0,f11,f6` /
//      `ble 0x3B44` against the 0.0f already live in f6).  The old draft tested
//      `-sum <= 0.0f` and carried a bogus ps_neg; there are ZERO ps_neg in the
//      want.
//   4. Only lane 0 is scaled: `ps_muls0` for the scalar slot plus the `ps1 <-
//      1.0f` patch the want stores to 0x34(r1) (the 1.0f load at 0x3B28 is
//      lbl_8029908C).  So `v58 * {rsq, 1.0f}`, not a plain ps_mul.
//   5. merge00's second operand is the {0,0} PAIR at lbl_80298F18 — declared
//      `extern V lbl_80298F18` (not `extern f32 lbl_80299088`) so cc1 emits
//      `lis`+`addi -0x70e8`+`psq_l`, exactly as the want does.
//   6. `s0`/`s1` must be `volatile V`: the want SPILLS them
//      (`psq_st f9,8(r1)` / `psq_st f8,8(r11)`) and reloads, which is what stops
//      cc1 from CSE-ing the second `ps_madd/ps_sum0` against the first.  With a
//      plain (non-volatile) local the whole recompute disappears (-3 words).
//      Two DISTINCT plain locals `e1`/`e2` are required too: the want spills
//      the res(rsqrte()) pair to 0x28(r1) and the bare rsqrte() pair to 0x30(r1).
//
// REMAINING DIFF (the honest residual):
//   A. TAIL BRANCH FORM, 1 word.  `if (o->f84 <= lbl_80299090) return;` lowers to
//      `fcmpu` + `cror cr0un,cr0eq,cr0lt` + `bso` (2 words) because GCC 2.95
//      computes UN=eq|lt to get NaN-correct `<=`.  The want has a bare `ble`
//      (1 word).  RULED OUT: `>=`, and `!(a > b)`, give the bare `ble` but drop
//      the object to **472B**, i.e. the whole tail then sits one word early and
//      masked_pct DROPS to 23.5%.  `if (a > b) { <body> }` likewise gives 472B.
//      So the exact-length version keeps the 2-word form on purpose: with the
//      length wrong the positional scorer penalises an otherwise-correct tail.
//   B. FRAME: `stwu r1,-0x30` (5 PS slots 0x08..0x28) vs the want's `-0x40`
//      (7 slots).  The want additionally homes the two muls0 results at 0x18/0x20
//      as DEAD stores (`psq_st f11,32(r1)` / `psq_st f0,24(r1)`, never reloaded).
//      RULED OUT: `volatile V r0, r1` does produce those two stores but also
//      forces two reloads -> 488B (3 words long).  A non-volatile local gets no
//      stack home at all.
//   C. ONE EXTRA `psq_l` of s0 at compute-block entry: the want loads s0 once
//      into f12 and reuses it for both `ps_madd` and `ps_muls0`; volatile s0
//      forces one load per read.  Fixing this needs a NON-volatile read of s0,
//      which re-CSEs the recompute (see CORRECTION 6).  This is the wall.
//   D. Want's `addi r11, r1, 8` (formed once, then s1 is addressed `8(r11)`)
//      and `ps_mr f10, f13` (a copy of the `t` pair) have no C spelling found.
//      RULED OUT: `volatile V *p0/p1 = &s0/&s1` -> ngccc 3.9.3 INTERNAL ERROR
//      ("unrecognizable insn", `(set (reg:PS ..) (const_int 0))`) as soon as a
//      volatile read reaches `ps_muls0`.  `volatile V t` adds no word.
//   E. Most residual word mismatches are pure FPR/GPR *register-number*
//      allocation (e.g. want f6/f7/f13 where got picks f5/f0/f12); the opcode
//      sequences match region for region.
//
// MOST PROMISING NEXT IDEA: the want's TWO homes for one logical scalar pair
// (`t` at 0x38 and its `ps_mr f10` copy) plus the dead 0x18/0x20 stores point at
// a struct/array of `volatile V` slots rather than separate locals.  Try
// declaring the seven working values as members of one `volatile V w[7]` (or a
// struct) in the want's slot order s0,s1,r0,r1,e1,e2,t: if cc1 then allocates
// 0x08..0x38 in declaration order the frame becomes 0x40 for free AND the dead
// r0/r1 stores appear without the extra reloads.
//
// INERT: not registered in splits.txt/configure.py — never compiled by the
// build, not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

typedef struct { f32 hi, lo; } flt_t;
typedef union { __ps_t p; flt_t f; } V;

typedef struct {
    char _a[0x50];
    V v50;
    V v58;
    char _b[0x84 - 0x60];
    f32 f84;
    char _c[0x120 - 0x88];
    s32 i120;
    char _d[0x134 - 0x124];
    f32 f134;
    char _e[0x158 - 0x138];
    f32 f158;
    char _f[0x1C0 - 0x15C];
    f32 f1C0;
    f32 f1C4;
    char _g[0x324 - 0x1C8];
    f32 f324;
    s32 i328;
    s32 i32C;
    s32 i330;
} C3A24;

extern V lbl_80298F18;
extern f32 lbl_80299088;
extern f32 lbl_8029908C;
extern f32 lbl_80299090;

void fn_800C3A24(C3A24 *o) {
    volatile V s0, s1;
    V v58, m, e1, e2, t, r0, r1, d;
    f32 sc, x, y;
    f32 *pp;

    if (o->i330 != 0 && (u32)o->i120 > 2) return;
    if (o->i328 == 0 && o->f324 != lbl_80299088 && (u32)o->i120 > 2) return;
    if (o->f134 > lbl_80299088) return;

    v58.p = o->v58.p;
    m.p = __builtin_ps_merge00(__builtin_ps_mul(v58.p, v58.p), lbl_80298F18.p);
    sc = o->f158 * o->f1C4;
    d.p = __builtin_ps_madd(o->v50.p, o->v50.p, m.p);
    d.p = __builtin_ps_sum0(d.p, d.p, d.p);
    e1.p = __builtin_ps_res(__builtin_ps_rsqrte(d.p));
    x = e1.f.hi;
    y = d.f.hi * sc;

    if (y > x) {
        o->v50.f.hi = lbl_80299088;
        o->v50.f.lo = lbl_80299088;
        o->v58.f.lo = lbl_8029908C;
        o->v58.f.hi = lbl_80299088;
    } else {
        s1.p = v58.p;
        s0.p = o->v50.p;
        d.p = __builtin_ps_madd(s0.p, s0.p, m.p);
        d.p = __builtin_ps_sum0(d.p, d.p, d.p);
        if (d.f.hi > lbl_80299088) {
            e2.p = __builtin_ps_rsqrte(d.p);
            s0.p = __builtin_ps_muls0(s0.p, e2.p);
            e2.f.lo = lbl_8029908C;
            s1.p = __builtin_ps_mul(s1.p, e2.p);
        }
        t.f.hi = y;
        r0.p = __builtin_ps_muls0(s0.p, t.p);
        r1.p = __builtin_ps_muls0(s1.p, t.p);
        o->v50.p = __builtin_ps_sub(o->v50.p, r0.p);
        o->v58.p = __builtin_ps_sub(o->v58.p, r1.p);
    }

    if (o->f324 != lbl_80299088) return;
    if ((u32)o->i120 <= 2) return;
    if (o->f84 <= lbl_80299090) return;
    sc = o->f1C0;
    pp = &o->v50.f.lo;
    x = o->f158;
    y = *pp;
    x = x * sc;
    if (fabsf(x) > fabsf(y)) {
        o->v50.f.lo = lbl_80299088;
        return;
    }
    *pp = (y > lbl_80299088) ? y - x : y + x;
}