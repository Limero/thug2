// WIP DRAFT (non-matching) — hand-reconstructed from the want disassembly
// (the m2c husk was a stub with ~40 `0;` no-ops; 236B of 888B).
// family=m2c range=0x80090958-0x80090CD0 size=888B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// ---------------------------------------------------------------------------
// PARKED: DIFF, byte-level 22.4% (49/219 masked words), object 876B vs want
// 888B (3 words short).  Measured with LEAF_TMPDIR isolated:
//   tools/test_wip_drafts.py --addr 0x80090958  ->  DIFF (no NEAR band)
//   tools/ps_diff.py 0x80090958                ->  49/219 (22.4%), got 876B
//   tools/want_got.py 0x80090958               ->  170 diffs, 22.37%
// Previous agent's parked body measured DIFF 15.4% at 884B.  The +7 points and
// the smaller size gap come entirely from fixing SEMANTIC errors in the
// reconstruction (see "SEMANTIC FIXES BELOW"), not from luck: with the right
// value web cc1 hands out the want's FPRs for the whole prologue.
//
// WHAT IS NOW BYTE-EXACT
//   * the first 33 instructions (0x80090958..0x80090980) are byte-identical,
//     INCLUDING every FPR number: x=f5, t=f4, first PS temp f7, the six
//     `src` pair copies in f0/f7/f8/f9/f13/f0, the three scalar lane
//     overwrites f12/f11/f10, the `lwz/cmpwi/beq` on 0x168, and the
//     `fsubs/fmuls/fdivs` that build `c`.  This is new: the previous body had
//     x=f4/t=f3 and diverged at instruction 4.
//   * frame 0x108, NO FPR saves; local pool slot-for-slot on the want's
//     offsets (22 pairs 0x08..0xb0, then ten 8-byte scalars 0xb8..0x100);
//   * the three separate 1.5 scale slots (0xf0/0xf8/0x100) each get their own
//     `fmr` + `stfs` — the want's three-fmr shape (the previous body
//     coalesced one of them away, which is where its extra word went).
//
// SEMANTIC FIXES BELOW (relative to the previous parked body — these are real
// bugs in the reconstruction, each verified instruction-by-instruction
// against the want, and each one changes cc1's register allocation):
// 1. then-branch scaled p[18]/p[19] by `ktt`; the want scales them by
//      `kx` (ktt only appears on the p[11]/p[0] row).
// 2. then-branch subtracted p[5] where the want subtracts p[4], and
//      scaled by kt/kx where the want scales by kc/kt.
// 3. p[16]/p[20] in and p[12] in the else-branch must read
//      `arg0->src.p[2]/src.p[4]` DIRECTLY off r3 (0xb8 / 0xc8) — the want has
//      `psq_l f,0xb8(r3)` / `0xc8(r3)` there, not a pool reload.
// 4. the batch tails are not symmetric: ends
//      p[11]=p[13]*ktt, p[0]=p[12]*ktt, p[10]=p[0], p[1]=p[11];
// ends p[11]=p[13]*kc2, p[3]=p[11], p[2]=p[12]*kc2, p[10]=p[2].
//      (The previous body wrote the same shape for both.)
//   5. `out.p[2]` and `out.p[3]` BOTH read pool slot 0x08 (q.p[0]); the old
//      body used `w[1]` (0x10) for out.p[3], a slot the want never reads.
//   6. `out.f[11] = q.f[7] - m.f[11]*pt5` (stack 0x24), not `q.f[5]` (0x1c).
//   7. the final section also stores p[10]=out.p[4] (0x58) and p[11]=out.p[5]
//      (0x60) — two stores the previous body did not have at all.
//
// REMAINING BLOCKER: pure cc1 FPR colouring + list scheduling (no semantic
// residue left that I can find).  Three concrete residuals:
//   (a) the very first divergence, at 0x80090984: want `psq_l f9,168(r3)` then
//       `psq_l f8,48(r1)`; this body emits f8 then f9 — an f8/f9 colour swap in
//       a two-element cluster, plus want reloads pool p[9] (`80(r1)`) early at
//       0x80090998 while this body sinks it to 0x80090…c8.
//   (b) the six constant stores (kt/kx/kxx/ktt/kc/kc2) come out in source order
//       kt,kx,kxx,ktt,kc,kc2 in the want but kx,kxx,kt,kc,ktt,kc2 here, which
//       swaps the f7/f12 roles of kt and kx.  Swapping the two assignments in
//       the source does NOT change this — measured.
//   (c) length: 3 words missing (`addi r9,r1,0x18` + 2x `mr r11,r9`), against
//       2 redundant `psq_st f,16(r1)` this body emits next to the want's
//       `8(rN)` stores.  See "MEASURED AND REJECTED" for the pointer forms.
//
// THINGS THAT DID NOT CLOSE IT (all measured this run)
//   * all pool traffic through `r[i]` (reads AND writes) -> 5 `stfd f27..f31`
//     and frame 0x130.  Only the write-only slots may go through the pointer.
//   * pool accessed only as `q.p[i]` (no pointer) -> cc1 dead-store-eliminates
//     the twelve write-only slots; 792B, 24 words short.  `r = q.p` makes `q`
//     address-taken, which is what keeps the plain `q.p[i] =` stores alive.
// * tail with p[2] before p[3] (the want's *store* order is p[3] then
//     p[2]; source order is the lever, not the store order) -> neutral, kept
//     the want's store order anyway.
//   * computing p[21]=p[9]-p[5] first (the want's *subtraction* order) so p[9]
//     loads early -> neutral (22.4% either way).
//   * `w = q.p` instead of `w = r` -> neutral.
//   * the previous run's `volatile __ps_t`, plain-local, and PSVec4-union
//     variants (see git history of this note) still do not work.
//
// Reusable ngccc facts confirmed/added this run:
//   (1) under -mps-float cc1 does NOT dead-store-eliminate a `psq_st` to a
//       union member or array element reached through a pointer, but it DOES
//       eliminate them for a plain local `__ps_t`.  Taking `&q` anywhere is
//       enough to keep plain `q.p[i] =` stores too — that asymmetry is the only
//       reason the original can leave twelve write-only stack slots.
//   (2) an 8-byte PS slot written only as a scalar and read only as a pair is
//       `union { __ps_t p; struct { f32 lo, hi; } w; }`: `.w.lo = f` gives the
//       4-byte `stfs`, `.p` gives the `psq_l`.
//   (3) NEW: on a ~220-instruction PS body the FPR colouring of the *prologue*
//       is decided by the value web of the whole function, not by the
//       prologue.  Fixing six wrong multipliers moved x from f4 to f5, t from
//       f3 to f4 and the first PS temp from f8 to f7 — i.e. the entire first
//       33 instructions went byte-exact with no flag, pin, barrier or ordering
//       change.  On PS drafts, read the tail's semantics BEFORE concluding
//       "FPR-colouring wall" (AGENTS-recipes §5 NEAR triage order pays off).
//   (4) `q.p[1] = r[1] = q.p[11];` with `r = q.p` emits BOTH `8(rN)` and
//       `16(r1)` stores (cc1 does not CSE the two spellings of one address);
//       dropping the `q.p[1] =` half removes the duplicate but costs 5 points,
//       because the resulting schedule shift moves more than the word it saves.
// ---------------------------------------------------------------------------
#include "types.h"
#include "structs.h"
#include "dolphin/SN_PS.h"


// A paired-single half: `.p` is the 8-byte PS pair, `.w.lo` / `.w.hi` its two
// float words.  The game writes only the low word and then uses the whole pair
// as a `ps_muls0` scale factor, which is why every one of these locals has a
// 4-byte store followed by an 8-byte psq_l in the want.
typedef union {
    __ps_t p;
    struct {
        f32 lo;
        f32 hi;
    } w;
} PSVal;

// Six packed pairs (a 3x2 matrix of paired quads) at 0x260 / 0x290 of the
// script struct; also readable as twelve plain floats (0x26c, 0x27c, 0x28c and
// 0x29c, 0x2ac, 0x2bc are the `.w` components the code uses scalar-wise).
typedef union {
    __ps_t p[6];
    f32 f[12];
} SixPS;

// The 22-pair scratch pool the want allocates at 0x8..0xb0.  Its elements are
// addressed through pointers in the original, which is what stops cc1 from
// deleting the twelve stores whose values are never read again.
typedef union {
    __ps_t p[22];
    f32 f[44];
} BigPS;

typedef struct {
    char pad0x00[0x18];
    f32 v18;
    f32 v1c;
    f32 v20;
    char pad0x24[0x14];
    f32 v38;
    f32 v3c;
    char pad0x40[0x68];
    SixPS src;
    char pad0xD8[0x90];
    s32 flag;
    char pad0x16C[0xF4];
    SixPS m;
    SixPS out;
} Attractor;

extern f32 lbl_80296F04;
extern f32 lbl_80296F08;
extern f32 lbl_80296F0C;
extern f32 lbl_80296F10;

void fn_80090958(Attractor *arg0) {
    BigPS q;
    __ps_t *r;
    __ps_t *w;
    PSVal kxx, ktt, kc, kt, kx, kc2, kinv, k15a, k15b, k15c;
    f32 x, t, c, pt5;

    x = arg0->v38;
    t = x * arg0->v3c * lbl_80296F04;
    q.p[5] = arg0->src.p[1];
    q.p[7] = arg0->src.p[3];
    q.p[9] = arg0->src.p[5];
    q.p[4] = arg0->src.p[0];
    q.p[6] = arg0->src.p[2];
    q.p[8] = arg0->src.p[4];
    q.f[11] = arg0->v18;
    q.f[15] = arg0->v1c;
    q.f[19] = arg0->v20;

    if (arg0->flag != 0) {
        r = q.p;
        w = r;
        c = lbl_80296F08 / ((t * x) * (x - t));
        kt.w.lo = t;
        kx.w.lo = x;
        kxx.w.lo = x * x;
        ktt.w.lo = t * t;
        kc.w.lo = c;
        kc2.w.lo = c;

        q.p[17] = __builtin_ps_sub(q.p[7], q.p[5]);
        q.p[16] = __builtin_ps_sub(arg0->src.p[2], arg0->src.p[0]);
        q.p[20] = __builtin_ps_sub(arg0->src.p[4], arg0->src.p[0]);
        q.p[21] = __builtin_ps_sub(q.p[9], q.p[5]);
        q.p[15] = __builtin_ps_muls0(q.p[17], kxx.p);
        q.p[14] = __builtin_ps_muls0(q.p[16], kxx.p);
        q.p[19] = __builtin_ps_muls0(q.p[21], kx.p);
        q.p[18] = __builtin_ps_muls0(q.p[20], kx.p);
        q.p[12] = __builtin_ps_sub(q.p[14], q.p[18]);
        q.p[13] = __builtin_ps_sub(q.p[15], q.p[19]);
        q.p[11] = __builtin_ps_muls0(q.p[13], ktt.p);
        q.p[0] = __builtin_ps_muls0(q.p[12], ktt.p);
        q.p[10] = q.p[0];
        q.p[1] = r[1] = q.p[11];

        q.p[16] = __builtin_ps_sub(q.p[8], q.p[4]);
        q.p[17] = __builtin_ps_sub(q.p[9], q.p[5]);
        q.p[20] = __builtin_ps_sub(q.p[6], q.p[4]);
        q.p[21] = __builtin_ps_sub(q.p[7], q.p[5]);
        q.p[15] = __builtin_ps_muls0(q.p[17], kc.p);
        q.p[14] = __builtin_ps_muls0(q.p[16], kc.p);
        q.p[18] = __builtin_ps_muls0(q.p[20], kt.p);
        q.p[19] = __builtin_ps_muls0(q.p[21], kt.p);
        q.p[12] = __builtin_ps_sub(q.p[14], q.p[18]);
        q.p[13] = __builtin_ps_sub(q.p[15], q.p[19]);
        q.p[11] = __builtin_ps_muls0(q.p[13], kc2.p);
        q.p[3] = q.p[11];
        q.p[2] = __builtin_ps_muls0(q.p[12], kc2.p);
        q.p[10] = q.p[2];
    } else {
        r = q.p;
        w = r;
        kinv.w.lo = lbl_80296F08 / x;
        q.p[13] = __builtin_ps_sub(q.p[9], q.p[5]);
        q.p[12] = __builtin_ps_sub(arg0->src.p[4], arg0->src.p[0]);
        q.p[11] = __builtin_ps_muls0(q.p[13], kinv.p);
        q.p[0] = __builtin_ps_muls0(q.p[12], kinv.p);
        q.p[10] = q.p[0];
        q.p[1] = r[1] = q.p[11];
        q.f[4] = lbl_80296F0C;
        q.f[9] = lbl_80296F0C;
        q.f[5] = lbl_80296F0C;
        q.f[6] = lbl_80296F0C;
    }

    pt5 = lbl_80296F10;
    k15a.w.lo = pt5;
    k15b.w.lo = pt5;
    k15c.w.lo = pt5;
    q.p[13] = __builtin_ps_muls0(arg0->m.p[3], k15b.p);
    q.p[12] = __builtin_ps_muls0(arg0->m.p[2], k15b.p);
    arg0->out.p[0] = __builtin_ps_sub(q.p[4], __builtin_ps_muls0(arg0->m.p[0], k15a.p));
    arg0->out.p[1] = __builtin_ps_sub(q.p[5], __builtin_ps_muls0(arg0->m.p[1], k15a.p));
    arg0->out.p[3] = __builtin_ps_sub(w[0], q.p[13]);
    arg0->out.p[2] = __builtin_ps_sub(w[0], q.p[12]);
    q.p[12] = __builtin_ps_muls0(arg0->m.p[4], k15c.p);
    q.p[13] = __builtin_ps_muls0(arg0->m.p[5], k15c.p);
    arg0->out.p[4] = __builtin_ps_sub(q.p[2], q.p[12]);
    arg0->out.p[5] = __builtin_ps_sub(q.p[3], q.p[13]);
    arg0->out.f[3] = q.f[11] - arg0->m.f[3] * pt5;
    arg0->out.f[7] = q.f[3] - arg0->m.f[7] * pt5;
    q.p[10] = arg0->out.p[4];
    q.p[11] = arg0->out.p[5];
    arg0->out.f[11] = q.f[7] - arg0->m.f[11] * pt5;
}
