// WIP DRAFT (non-matching) — hand-written from disasm 2026-09-24,
// semantics corrected 2026-09-26, residual re-diagnosed 2026-10-30
// family=m2c range=0x8008757C-0x80087608 size=140B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// PARKED 2026-10-30: 82.9% -> 82.9% (29/35 words), SIZE-EXACT 140B
//
// *** CORRECTION TO THE 2026-09-26 PARK NOTE (it mis-attributed the pin). ***
// The old note called the `register f32 x __asm__("fr0")` pin "one non-pure-C
// lever" whose only job was to colour the x chain's FPRs, and called the
// residual "a single-chain coalescing tie-break in GCC 2.95's fma fusion".
// Both are wrong about the ROLE of the pin.  Measured decomposition:
//
//   PINNED (this file, fr0 on x):  the ENTIRE SCHEDULE is byte-identical to
//     want — all 11 `lfs` at the right addresses in the right slots, both
//     `stfs` (0xd4 t[1]=y, 0xdc t[0]=x) in the right slots, and every load and
//     store displacement correct.  Only 6 of 35 words differ, and they are 3
//     FPR webs of the x chain.  So the pin is LOAD-BEARING FOR THE SCHEDULE,
//     not just for the colour: removing it makes 9 words worse (see below).
//   UNPINNED (same body, no pins): ALL TEN arithmetic instructions match want
//     byte-for-byte, including the two that are wrong when pinned.  The 9
//     differing words are a pure PERMUTATION of the load emission order —
//     x's chain's coefficient loads get scheduled AHEAD of y's, which also
//     flips the two `stfs` — plus the offsets they feed.
//
// So the residual is ONE `coalesce`/`local_alloc` decision with two faces:
// forcing x's pseudo to f0 fixes the schedule but makes `coalesce` put the
// DYING ADDEND in the fmadds destination instead of the MULTIPLICAND.
//   want  lfs f0,0x20(r4) | fmadds f0,f12,f0,f11   dest = the m20 LOAD's reg
//                                                      (in place, accum f11)
//   got   lfs f11,0x20(r4)| fmadds f0,f12,f11,f0   dest = the ACCUM's reg
//                                                      (in place, m20 f11)
// Both are legal; the set {f0,f11} is identical, only which of the two
// operands coalesces with the destination differs.  Same shape for the seed:
// want has the seed in f0 and m20/final reusing f0 after the seed dies; got
// has the seed in f11 with m20 reusing f11.
//
// CHAIN DECODE (new, hand-verified from the raw want words).  All three
// chains are structurally identical; f8=v[1] f9=v[0] f12=v[2] f0=v[3].
//   out[j] = v[1]*m[1][j] + v[0]*m[0][j] + v[2]*m[2][j]     (j = 0,1,2)
// and m[3][*] is never read while v[3] is copied to lane 3 verbatim.  GCC
// canonicalises MULT operand order, so `v[0]*m[0][j] + v[1]*m[1][j] + ...`
// emits the v1 product as the bare `fmuls` seed — i.e. the source form in
// this file is CORRECT, not a v0/v1 swap.  Seed/accum/final regs per chain:
//   Y(t[1]): f13 / f10 / f13   <- seed and FINAL share
//   X(t[0]): f0  / f11 / f0    <- seed and FINAL share
//   Z(t[2]): f8  / f9  / f12   <- all distinct (f8 was already v1's reg)
// Y and X share the "seed and final share one reg" pattern; only X is wrong
// in the pinned build.  Statement order y,x,z and store order t[1],t[0],p[2]
// are BOTH required (every other permutation collapses to 25-43%).
//
// Semantics (unchanged and confirmed against the DOL): out = Mᵀ · v for a
// 4x4 row-major matrix and a 4-vector, materialised through a 4-float stack
// temp and copied out as two __ps_t pairs:
//     t[0] = v0*m[0][0] + v1*m[1][0] + v2*m[2][0]
//     t[1] = v0*m[0][1] + v1*m[1][1] + v2*m[2][1]
//     t[2] = v0*m[0][2] + v1*m[1][2] + v2*m[2][2]
//     t[3] = v3
//     ((__ps_t *)dst)[0] = ((__ps_t *)t)[0];
//     ((__ps_t *)dst)[1] = ...;
// Note only rows 0-2 are read; row 3 is never touched (v[3] is carried into
// lane 3 verbatim), so this is a mat4 whose 4th row is identity in practice.
//   arg0 (r3) = dst, mm (r4) = matrix, v (r5) = vector; 140B, frame 0x18,
// no callee-saved regs, no LR save — a frameless-leaf-shaped helper that only
// needs a frame for the t[4] local (t[0]@r1+8 .. t[3]@r1+0x14).
//
// *** THE 37.1% -> 82.9% FIX: the second pair copy wrote to the WRONG place.
// The old body ended with
//     ((__ps_t *)d)[0] = ((__ps_t *)t)[0];
//     ((__ps_t *)p)[1] = ((__ps_t *)t)[1];      /* p == t !! */
// with `f32 *p; p = t;` — so the second statement was t[1] = t[1], a
// self-assignment onto the STACK, not a store to dst+8.  ngccc faithfully
// emitted `psq_l f0,16(r1)` + `psq_st f0,8(r11)` (r11 = r1+8, i.e. r1+0x10
// = t[2]) — a stack round-trip that happens to be the same LENGTH, which is
// why the old body was still SIZE-EXACT and only scored 13/35.  With the
// destination corrected to `((__ps_t *)arg0)[1]`, the tail becomes want's
// `psq_l f0,8(r11)` + `psq_st f0,8(r9)` and 16 more words match.
// The `f32 *p` alias itself is still required and is NOT a bug: want
// materialises `addi r11,r1,8` (= &t[2]) early in the prologue and addresses
// t[2] and the second pair through r11 while t[0]/t[1]/t[3] and the first pair
// go through r1 directly.  `p = t` + `p[2] = ...` + `((__ps_t *)p)[1]` (with
// the p base used only for the READ) reproduces that split-base shape.
//
// The `void *` return + `return arg0;` is what reproduces want's `mr r9,r3`
// base copy and the bare `blr` (AGENTS.md recipes 249/264).  Using `arg0`
// directly as the pair-store base scores identically (82.9%) and needs no
// `d` temp, so the temp was dropped.  A `void` return does NOT work: the
// second psq store is then folded away and the body shrinks to 136B (8.6%).
//
// `register f32 x __asm__("fr0");` — the one non-pure-C lever left, and it is
// load-bearing: WANT's x chain lives in f0/f11 (result f0), and without the
// pin ngccc gives the x chain the {f10,f13} pair and the y chain {f0,f11}
// instead, which drops the score to 74.3% (26/35, and it also swaps the
// m4/m5 + m8/m9 load order and the t[0]/t[1] store order).  It is a register
// variable declaration, not an inline-asm block: it emits no instructions,
// it only states that the x accumulator is homed in f0, which is a fact read
// straight off the DOL.  The same 82.9% is reached by pinning y to fr13
// instead, so the plateau is not an artifact of this particular pin.
//
// RE-TRIAGE 2026-10-12: re-verified 82.86% (29/35) size-exact
// with -mps-float; residue is the same 6 words (x-chain fmadds dest +
// seed/final regs). New observation, no lever: the pinned and unpinned bodies
// are COMPLEMENTARY — unpinned gets all ten arithmetic insns byte-exact but
// permutes the load schedule; pinned fixes the schedule but flips the two
// fmadds colors. A schedule-shaping lever that doesn't touch FPR pressure
// would combine them, but every statement/load/store order is already pinned
// by the 25-43% cliffs above, and extra live ranges cost words. No body
// change; wall stands.
// RESIDUAL BLOCKER: the x chain's FPR role swap described above — 6 of 35
// words, one `coalesce` decision, a textbook doc-15 / doc-10 allocator
// coin-flip.  §6cs-1 length check: object .text = 0x8C = 140B = symbols.txt
// `size:0x8C` = the `size=140B` header marker, so every diff is placement,
// not index shift.  §6bw audit is VACUOUS here and that is a real result:
// the object has NO relocations at all (no branches, no calls, no data
// addresses), so the masked score compares all 35 words with nothing hidden.
// Only .text is emitted — no private .rodata pool, no doc-14 promote caveat.
// Body has ONE `__asm__`, the zero-instruction `register ... __asm__("fr0")`
// attribute.
//
// LEVER LOG 2026-10-30 (every score measured with LEAF_TMPDIR set; baseline
// 82.9% pinned / 74.3% unpinned).  Nothing beat 82.9%:
//  FPR pins, x pinned fr0 in all of these:
//    accumulator named + pinned fr6/7/8/9/10/11/12/13  48.6/51.4/54.3/57.1/
//      65.7/74.3/60.0/54.3%   <- the pin DOES bind (R_accF11's accum dest is
//      genuinely f11) but m00's load leaves f11 and the load schedule shifts
//    accumulator named, unpinned  74.3% (folded back, = baseline)
//    seed pinned fr0  60.0%  (in-place form) / 51.4% (separate accum)
//    seed fr0 + accum fr11 + x fr0  45.7%;  seed fr11 + x fr0  51.4%
//    y fr13 + z fr12  34.3%;  y fr13 + x fr0  65.7%;  y fr13+x fr0+z fr12 54.3%
//    x fr0 + named accum + `__asm__("" : "+f"(acc))`  77.1%  (best sub-82.9%:
//      the barrier does free the accum, but it slides one `lfs` a slot)
//  zero-instruction "+f" barriers, UNPINNED: on x 8.6%, on y 8.6%, on both
//    14.3%, on all three 40.0%  (a volatile/identity barrier on a float web
//    re-orders the whole block — §6ax-173/§6bz's frozen-ness, hostile here)
//  source shape, UNPINNED: named per-term coefficients 22.9%; explicit want
//    load order (all 9 coefficients as separate statements, relying on fma
//    contraction) 28.6%; in-place accumulation `x=..; x+=..; x+=..` 60.0%
//    (pinned); `volatile f32 acc` 5.4%; right-grouped `v2*m20 + (v0*m00 +
//    v1*m10)` 82.9% (exact tie with baseline, no gain); named vector locals
//    v0..v3 74.3% (tie with unpinned); hoisted row pointers r0/r1/r2 2.7%;
//    named v + row pointers 2.7%
//  term order of the x chain (6 permutations) x {pinned, unpinned}: the
//    natural v0,v1,v2 order is REQUIRED — 34.3/31.4/51.4/37.1/37.1/34.3%
//    pinned and 31.4-57.1% unpinned for every other permutation.  The header's
//    older "operand order (v1-first 51.4%, right-grouped 42.9%)" figures were
//    measured with a different body shape and do not reproduce.
//  declaration order: all 6 permutations of (x,y,z) are BYTE-IDENTICAL at
//    74.3% unpinned — completely inert, contrary to the usual §76-184 advice
//  statement order: y,x,z required — x,y,z 34.3%, y,z,x 40.0%, z,y,x 28.6%
//  store order: t[1],t[0],p[2] required — every other permutation 25.7-42.9%
//  `p = t` / `t[3] = v[3]` / `p[2] = z` statement positions: 74.3% at best,
//    all others 8.3-31.4%
//  flags on the PINNED baseline (28 combos): -fno-schedule-insns 5.7% (136B),
//    -fno-schedule-insns2 62.9%, -ffloat-store 7.7%, -Os 54.3%, -O1 8.6%,
//    -fno-expensive-optimizations 51.4%, and -fno-sched-spec /
//    -fno-sched-interblock / -fno-gcse / -fno-thread-jumps /
//    -fno-rerun-cse-after-loop / -fno-branch-count-reg / -fno-strength-reduce
//    / -fno-caller-saves / -fconserve-space / -fno-regmove /
//    -fno-optimize-register-move / -fforce-mem / -fdefault-single-float /
//    -O3 / -mcpu=603 / -mcpu=750 / -mcpu=603e  ALL 82.9% (neutral)
//  flags on the UNPINNED body: all 74.3% except -fno-schedule-insns 5.7%,
//    -fno-schedule-insns2 48.6%, -fno-expensive-optimizations 45.7%,
//    -Os 42.9%, -O1 5.7%
//  `-ffixed-f0` .. `-ffixed-f14` on BOTH bodies: completely inert (82.9% /
//    74.3% unchanged) — ProDG does not shrink the FPR pool with it, so it is
//    NOT a lever for "keep the accumulator out of f0".
//
// LEVER LOG 2026-10-12: split-x (xseed plain + xmid pinned fr11 +
// x fr0, three statements) 60.0% — extra live ranges shift the load
// schedule; unpinned + z pinned fr12 74.3% (= unpinned baseline, pin inert).
// Both reverted; baseline 82.9% re-verified.
//
// TOOL TRAP hit twice this round (cost ~10 min, will cost it again):
// `tools/score_body.py` reads ONLY `sys.argv[3]`, so any flags passed after
// the body path are SILENTLY IGNORED and the whole sweep reads as "every flag
// is neutral".  Pass every flag inside ONE quoted argument.  Positive control
// before trusting any flag sweep: -fno-schedule-insns must move 82.9% -> 5.7%.
// (Related: §6fj's shared-`LEAF_TMPDIR` race; set it per worker.)
//
// UNTIED AND THE OBVIOUS NEXT THING: with the pin the schedule is already
// perfect, so the only thing needed is a way to make `coalesce` prefer the
// MULTIPLICAND for the fmadds destination.  Every pure-C and pin/barrier route
// tried moves the schedule instead.  The untried lever is a 1-instruction
// opaque asm birth of the accumulator (not a barrier) placed between the two
// fmadds, e.g. `__asm__("fadd %0,%1,%1" : "=f"(acc) : "f"(acc));` — 1 of 35
// instructions = 2.9%, inside the §4g budget, and unlike a barrier it emits
// rather than re-orders, so it may leave the 11 `lfs` slots alone.  Not tried
// because it duplicates the value and so risks becoming a 36-word object.
#include "types.h"

typedef struct {
    f32 m[4][4];
} M8008757C;

void *fn_8008757C(char *arg0, M8008757C *mm, f32 *v) {
    f32 t[4];
    f32 *p;
    f32 y, z;
    register f32 x __asm__("fr0");
    p = t;
    y = v[0]*mm->m[0][1] + v[1]*mm->m[1][1] + v[2]*mm->m[2][1];
    x = v[0]*mm->m[0][0] + v[1]*mm->m[1][0] + v[2]*mm->m[2][0];
    z = v[0]*mm->m[0][2] + v[1]*mm->m[1][2] + v[2]*mm->m[2][2];
    t[1] = y;
    t[0] = x;
    p[2] = z;
    t[3] = v[3];
    ((__ps_t *)arg0)[0] = ((__ps_t *)t)[0];
    ((__ps_t *)arg0)[1] = ((__ps_t *)p)[1];
    return arg0;
}
