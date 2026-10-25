// WIP DRAFT (non-matching) — hand reconstruction from retail disassembly
// family=m2c range=0x800BCE9C-0x800BD050 size=436B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// (previous body: an m2c husk — 30 `0;` no-ops plus three dead statics,
// compiling to a 16-byte stub. Replaced by a full from-disasm rebuild.)
#include "types.h"

typedef union {
    __ps_t ps;
    f32 f[2];
} PSU;

typedef struct {
    char _00[0x30];
    f32 f30;
    f32 f34;
    char _38[0xF0];
    __ps_t v128;
    __ps_t v130;
} OBJ;

typedef struct {
    char _00[0x88];
    char _88[0x10];
    __ps_t v98;
    __ps_t vA0;
} ARG1;

extern __ps_t lbl_80298CA0;
extern f32 lbl_80298E20;
extern f32 lbl_80298E24;

void fn_800BD050(OBJ *obj, void *ctx, f32 s);

void fn_800BCE9C(OBJ *arg0, ARG1 *arg1) {
    volatile PSU p08, p10, p18, p20, p28, p30;
    volatile PSU *slot = &p08;
    PSU p38, p40, p48, p50, p58, p60, p68;
    __ps_t z, a1, a2, o1, o2, t, u, f6, f7, f8, f9, m, n, q, w08;
    f32 dep, c1, c2, s, len, inv, lim;

    a2 = arg1->vA0;
    o2 = arg0->v130;
    z = lbl_80298CA0;
    a1 = arg1->v98;
    o1 = arg0->v128;
    dep = arg0->f30;
    c1 = lbl_80298E20;
    c2 = lbl_80298E24;

    t = __builtin_ps_mul(o2, a2);
    t = __builtin_ps_merge00(t, z);
    t = __builtin_ps_madd(o1, a1, t);
    t = __builtin_ps_sum0(t, t, t);
    p38.ps = t;
    s = p38.f[0];

    dep = dep + c1;
    p48.f[0] = s;
    dep = dep * -s;
    p40.f[0] = dep;

    n = p48.ps;
    m = __builtin_ps_muls0(a2, n);
    p30.ps = m;
    f6 = __builtin_ps_sub(o2, m);
    p20.ps = f6;
    q = __builtin_ps_muls0(a1, n);
    p28.ps = q;
    u = __builtin_ps_mul(f6, f6);
    f7 = __builtin_ps_sub(o1, q);
    p18.ps = f7;
    u = __builtin_ps_merge00(u, z);
    u = __builtin_ps_madd(f7, f7, u);
    u = __builtin_ps_sum0(u, u, u);
    u = __builtin_ps_rsqrte(u);
    u = __builtin_ps_res(u);
    p50.ps = u;
n = p40.ps;
    w08 = __builtin_ps_muls0(a1, n);
    p08.ps = w08;
    p10.ps = __builtin_ps_muls0(a2, n);

    len = p50.f[0];
    if (len > c2) {
        p58.f[0] = len;
        lim = arg0->f34;
        p58.f[1] = len;
        u = __builtin_ps_res(p58.ps);
        f8 = __builtin_ps_muls0(f6, u);
        f9 = __builtin_ps_muls0(f7, u);
        p20.ps = f8;
        p18.ps = f9;
        n = slot[1].ps;
        t = __builtin_ps_mul(n, n);
        t = __builtin_ps_merge00(t, z);
        t = __builtin_ps_madd(w08, w08, t);
        t = __builtin_ps_sum0(t, t, t);
        t = __builtin_ps_rsqrte(t);
        t = __builtin_ps_res(t);
        p60.ps = t;
        inv = p60.f[0];
        lim = lim * inv;
        if (len > lim) {
            len = lim;
        }
        len = -len;
        p68.f[0] = len;
        n = p68.ps;
        m = __builtin_ps_muls0(f8, n);
        f8 = __builtin_ps_muls0(f9, n);
        p30.ps = m;
        p28.ps = f8;
        arg0->v128 = __builtin_ps_add(o1, f8);
        arg0->v130 = __builtin_ps_add(o2, m);
    }

    arg0->v128 = __builtin_ps_add(arg0->v128, p08.ps);
    arg0->v130 = __builtin_ps_add(arg0->v130, slot[1].ps);
    fn_800BD050(arg0, (void *)((char *)arg1 + 0x88), -s);
}

// ---------------------------------------------------------------------------
// IDENTITY: push a point out to a boundary. arg0 carries a 2D frame
// (v128/v130 = the point, f30/f34 = the two radii), arg1 a segment
// (v98 = direction, vA0 = offset, +0x88 = the segment's runtime context):
//   s  = 2 * dot(arg0.v128*arg1.v98, arg0.v130*arg1.vA0)   (ps_sum0 chain)
//   p40 = (arg0->f30 + 1.0) * -s                           (signed depth)
//   p30 = arg1.vA0.lo * s ;  f6 = arg0.v130 - p30          (normal offset)
//   p28 = arg1.v98.lo * s ;  f7 = arg0.v128 - p28
//   L  = rsqrt/res of 2*(f6.lo^2 + f7.lo^2)                (p50)
//   p08 = arg1.v98.lo * p40.lo ;  p10 = arg1.vA0.lo * p40.lo
//   if (L > 0.001f):
//     p20 = f6 * res(p58) ; p18 = f7 * res(p58)
//     p60 = rsqrt/res(2*(p10.lo^2 + p08.lo^2))            -- BOTH p08 and p10
//     L = min(L, arg0->f34 * p60.lo)
//     p30 = p20 * -L ; p28 = p18 * -L                      (p28 is a dead store)
//     arg0.v128 = o1 + p28 ; arg0.v130 = o2 + p30         (CORRECTED 2026-10-03)
//   arg0.v128 += p08 ; arg0.v130 += p10                   (DIFFERENT values)
// The two inside-the-if adds use DIFFERENT values: 0x800BD004 is
// `ps_add f12,f4,f0` with f0 = the f7-based muls0 (0x800BCFF4) i.e. p28, while
// 0x800BD008 is `ps_add f13,f3,f13` with f13 = the f6-based muls0 (0x800BCFF0)
// i.e. p30. f4 = o1 (X) gets the f7 (X-offset) term, so this is the sane
// X+Xoff / Y+Yoff pairing; the earlier "retail uses p30 twice" reading of the
// want was wrong. Likewise the second muls0 pair reads p20/p18 (already
// res-scaled) out of REGISTERS, not the unscaled f6/f7.
//   fn_800BD050(arg0, arg1+0x88, -s)
//
// lbl_80298CA0 = {0.0f, 0.0f} is the dot-chain accumulator zero: ps_merge00
// keeps lane 0 of operand A and takes lane 0 of operand B into lane 1, so the
// chain computes ps_sum0(ps_madd(o1,a1, ps_merge00(ps_mul(o2,a2), K))) with the
// 2x from sum0(a,a,a). lbl_80298E20 = 1.0f, lbl_80298E24 = 0.001f (epsilon).
//
// ---------------------------------------------------------------------------
// SLOT QUALIFIERS — the load-bearing part (recipes 7q + "three lane-read
// spellings"). Every one of the 13 PS temporaries is written one way and read
// the other, and the two classes need OPPOSITE qualifiers:
//
//  * p38/p40/p48/p50/p58/p60/p68 are declared as PLAIN (non-volatile) unions.
//    cc1 has no register lowering for V4SF->SF, so for `slot.ps = <pair>` /
//    `slot.f[0] = <scalar>` followed by a lane read it spills the pair to the
//    slot and reloads lane 0 into a scratch FPR, leaving the reload pseudo
//    distinct from the value pseudo. THAT is where retail's eight lane-reload
//    copies come from (lane 0 spilled to its slot and reloaded into a scratch
//    FPR at 0x38, 0x48, 72(r1), 64(r1), 0x50, 0x60 and 104(r1)) — declaring
//    them `volatile` instead coalesces the reload and loses all 8 words
//    (this draft measured 100 words instead of 109).
//
//  * p08/p10/p18/p20/p28/p30 stay `volatile` because their stores must survive:
//    p18/p20/p28/p30 keep a store whose value is never read back, and p08/p10
//    are re-read after each `arg0->v*` pointer store. Plain locals let GCC DCE
//    all of those (verified: making all 13 non-volatile drops the object to
//    92 words).
//
// `volatile PSU *slot = &p08;` exists only so the two p10 READS go through a
// materialised base: cc1 CSEs `&p08` into `addi r9,r1,8` (hoisted to just
// after the `lis` block, exactly as at 0x800BCEE4) and then emits the p10
// accesses as `8(r9)` = r1+0x10, which is what retail does at 0x800BCFA8 and
// 0x800BD030. p08's own store and the p10 STORE must stay direct `p08.ps` /
// `p10.ps` writes — retail uses `8(r1)` / `16(r1)` for those two.
//
// ---------------------------------------------------------------------------
// RE-TRIAGED 2026-10-13: still 67.9% NEAR, size-exact 436B.
// Pure FPR-numbering + scheduling slips (free-register picks from identical
// liveness per header). No new lever; body unchanged.
// STATUS 2026-10-03: NEAR 67.9% — got 436B / want 436B, 74/109
//   words bit-exact after relocation masking, opcode-sequence LCS 104/109.
//   Length is exact, so the residual is real (was 404B / 101 words / 7.9%).
//   Reproduce (official):
//     LEAF_TMPDIR=<private dir> tools/venv/bin/python
//       tools/test_wip_drafts.py --addr 0x800BCE9C
//     -> "NEAR  m2c  0x800BCE9C (436B) 67.9%"  (verified 2026-10-03; the tool
//     DOES honour the `// extra_cflags: -mps-float` marker above, and the body
//     ICEs at expr.c:28 without it). Per-word view: tools/ps_diff.py 0x800BCE9C
//
//   RESIDUAL: 35 words, ALL of them either an FPR colouring difference or a
//   1-2 slot scheduling slip inside an already-correct instruction run. No
//   instruction is missing or extra any more (the earlier 8-word deficit and
//   all 8 fmr/ps_mr copies are fixed). Specifically:
//     a. FPR colouring, 6 clusters (nothing structural):
//        - 0x800BCF74/0x800BCF80: want f13->f0 for the compare and f0->f10 for
//          the p58.f[0] store; got f13->f10 then f10->f0 (registers swapped).
//        - 0x800BCF88: arg0->f34 home f12 (want) vs f9 (got). Cascades into
//          the multiply, compare and copy triple at 0x800BCFD0/0x800BCFD4/
//          0x800BCFDC (want f12/f10/f12 homes, got f9-based).
//        - 0x800BCF98/0x800BCF9C/0x800BCFA0/0x800BCFA4: the p20/p18 pair wants
//          f8/f9 (the two regs that just went dead holding 0.001f and -s); got
//          picks f12/f0.
//        - 0x800BCFEC: want `ps_mr f0,f10`, got `ps_mr f13,f10`; this also moves
//          the two following ps_muls0 dests (want f13/f0, got f0/f12).
//        - 0x800BCFA8/0x800BCFAC: want reloads the square operand into the
//          pair accumulator while got keeps the loaded value in place (want
//          reloads into f0, got into f13).
//        - 0x800BCF08/0x800BCF0C: want `ps_sub`/p30 store in the order
//          `ps_sub f6,f3,f0` then `psq_st f0,48(r1)`; got store first.
//     b. Scheduling slips (same multiset, different slots):
//        - 0x800BCF58 `ps_mr f13,f10` sits 3 slots early (got emits it inside
//          the preceding rsqrt chain).
//        - 0x800BCFBC..0x800BD010: got hoists the p28 dead store above the
//          first `ps_add`; want keeps `psq_st f0,40(r1)` before both.
//        - tail 0x800BD010..0x800BD038: want defers the p10 load to after the
//          v128 store (`psq_st f12,296(r8)`); got hoists it above `addi r4`.
//
// RULED OUT (all measured, all byte-for-byte on this body):
//   * `register f32 lim __asm__("fr12")` to force arg0->f34's home: 67.9% ->
//     65.1% (pin cascade, recipes 7q/registry-list-walk note).
//   * Completing the first tail statement through an explicit temp
//     (`t = ps_add(...); arg0->v128 = t;`) so the p10 load is not hoisted:
//     67.9% -> 47.7%.
//   * Swapping the p30 store past the `ps_sub` (0x800BCF08): byte-identical
//     object, no effect.
//   * Moving `p50.ps = u;` after the p08/p10 block: byte-identical object.
//   * Reordering the leading assignments (a1 before z), reversing the f32
//     declaration order: byte-identical objects — cc1's -mps-float FPR
//     allocator ignores declaration/first-use order here (this re-confirms the
//     older note on this draft).
//
// NEXT IDEA: the six colouring clusters in (a) are all "cc1 picked a different
// free FPR than retail", not a different instruction. §7q's
// "second live name" rule is what creates the len/inv copies and those are now
// in place; the remaining lever is to give the p20/p18 and p08/p10 results
// distinct *fresh* __ps_t variables rather than reusing the f8/f9/f12/f0
// names, in case cc1's free-list order depends on which pseudo it reuses.

// ---------------------------------------------------------------------------
// PARKED 2026-10-03: 67.9%  436B object / 436B symbol, 74/109 words
//   bit-exact after relocation masking. Reproduce:
//     LEAF_TMPDIR=<private dir> tools/venv/bin/python
//       tools/test_wip_drafts.py --addr 0x800BCE9C     -> "NEAR m2c ... 67.9%"
//     per-word view: tools/ps_diff.py 0x800BCE9C --all
//
// TWO REAL SEMANTIC BUGS FOUND AND FIXED THIS ROUND (score-neutral, but they
//   make the object structurally right, so every remaining diff is now purely a
//   register/scheduling artefact rather than a wrong operand):
//   1. The second `ps_muls0` pair inside the `if` multiplies the *res-scaled*
//      vectors (the ones just stored to p20/p18), not the unscaled f6/f7.
//      want reads the two scaled results at 0x800BCFF0/0x800BCFF4 from the
//      registers holding the 0x800BCF80/0x800BCF88 scaled products; the old
//      body used f6/f7.
//   2. `arg0->v128` gets the f7-based product and `arg0->v130` the f6-based one.
//      want adds the f7 term (p28) into the X lane at 0x800BD004 and the f6
//      term (p30) into the Y lane at 0x800BD008; the old body added `m` to
//      both. This also FIXED the old (b)-tail scheduling note:
//      0x800BCFBC..0x800BD00C now emits store/store/add/add/store/store exactly
//      like want instead of hoisting the p28 dead store above the first add.
//
// RESIDUAL after those fixes (35 words, unchanged count — the two fixes traded
//   register errors for each other):
//   A. ~30 words are PURE FPR NUMBERING. In every one of the clusters the
//      instruction, its operands and its slot are already identical to want;
//      only the hard FPR differs, and in each case BOTH registers are provably
//      dead at that slot. Measured free sets (want's pick first):
//        At 0x800BCF74/78/80 four registers are free and retail picks f0 for
//        the compare and f10 for the store while the build picks f10 and f0.
//        At 0x800BCF88 two are free and retail picks f12 while the build
//        picks f9. At 0x800BCF94/98/9C four are free and retail picks f8 and
//        f9 while the build picks f12 and f8. At 0x800BCFA8 four are free and
//        retail picks f0 while the build picks f13. At 0x800BCEFE8 four are
//        free and retail picks f0 while the build picks f11.
//      The liveness sets are provably IDENTICAL (words 0x0000-0x00D4 are
//      byte-identical apart from the 0x800BCF08/0x800BCF0C swap, which uses
//      only already-allocated f0/f3/f6), so cc1's register allocator is
//      landing on a different FREE-REGISTER pick from an identical input state.
//      That is a difference in the allocator's internal free-list/relno state,
//      not in the C.
//   B. 2 words, 0x800BCF08/0x800BCF0C: want the subtract-then-pair-store
//      order; got the two swapped. Insensitive to source order —
//      `f6 = ps_sub(o2,m); p30.ps = m; p20.ps = f6;` compiles byte-identically
//      to the order in the body (re-measured this round).
//   C. 9 words, tail 0x800BD010..0x800BD03C: want orders the four reloads by
//      first use (p08, v128, v130, p10); got hoists the p10 reload to slot 2.
//      NOT fixable from the statement shape: `slot[1].ps` inline, via `t`, via
//      `u` and via `m` were all measured, and the `t`/`u`/`m` forms all made it
//      worse (47.7% / 18.2% / 67.0% + object grew to 440B in the `u` case).
//
// RULED OUT THIS ROUND (measured on this body, byte-for-byte):
//   * fresh `__ps_t g8,g9` names for the second muls0 pair (the previous
//     round's "NEXT IDEA"): 67.9% -> 63.3%, and it also un-groups the p28 store.
//   * recipe-273 "fewer temporaries": replacing `f6` by reusing `m` in the
//     first block: 67.9% -> 61.5%.  Replacing the scaled pair by reusing
//     `f6`/`f7`: 67.9% -> 57.9% AND the object lost a slot (428B).
//   * grouping the two inside-the-if adds into temps before the arg0->v128/v130
//     stores: byte-identical object (cc1 coalesces them).
//   * making `p08`/`p10` non-volatile: 12.3%, 424B — they DO need volatile.
//   * explicit temps for the tail values (`t`/`u`/`m`): see C above.
//   => the body is a local optimum in temp count, volatility and statement
//      order; the residual is not a "draft has too many/few temporaries" wall.
//
// WHAT WOULD UNBLOCK IT: the allocator state that makes cc1 pick f10 over f0
//   for the `len` compare copy at 0x800BCF74 is set by instructions BEFORE
//   0x800BCFD0, and everything before it is already byte-exact, so it cannot be
//   steered from the source side of 0x800BCF74. Landing this would need either
//   a reverse-engineered rule for ngccc 3.9.3's `-mps-float` free-FPR choice
//   (worth writing up generally if anyone cracks it — it is the last 30 of the
//   35 words on this function) or a matching sce version to diff RTL against.
