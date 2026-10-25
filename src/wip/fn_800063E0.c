// WIP DRAFT (non-matching) — PARKED 2026-10-04.
// family=m2c range=0x800063E0-0x80006AB0 size=1744B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress.
// Measured: DIFF, 1.7% masked over the 116-word window this body produces
// (object 464B vs want 1744B — 1280B short; per AGENTS §6es the score is
// index-aligned and meaningless until the length matches; only 2 of the 116
// words match — `psq_l f0,16(r4)` and one `bns` — both by accident of
// alignment, not by construction).  Baseline before this attempt was DIFF
// 0.0% (object 584B).
//
// WHY PARKED (blocker): the body splits into two parts that cannot be matched
// independently.
//
//  (1) HEAD 0x800063E0-0x80006534 (85 insns) IS expressible in plain C — the
//      whole Paired-Single idiom below is reproduced verbatim by ngccc 3.9.3
//      with `// extra_cflags: -mps-float` (ps_sub / ps_mul / ps_merge00 /
//      ps_madd / ps_sum0 / psq_l / psq_st, the `lfs`-reload-of-just-stored-lane0
//      idiom, `addi r10,r1,8` second base, `lfs` of `lbl_8028FDC4` = 1e-6).
//      But its *register allocation and stack frame* are NOT reproducible in
//      isolation: the want spills all six vector halves to r1+0x08..0x38,
//      the four `-d` lanes to r1+0x38..0x44, and eight single-pair scalar
//      results to r1+0x48..0x80, and callee-saves f30/f31 — all of which only
//      happens because the 35-leaf tail keeps 5 quadratic forms live across the
//      whole body.  A head-only body compiles to a 0x28 frame with no spills
//      (measured: 0 of the first 85 words identical).  Matching the head needs
//      the tail; matching the tail needs the original source.
//
//  (2) TAIL 0x80006534-0x80006AAC (302 insns) is a ~35-leaf float decision
//      tree whose leaves are near-duplicates of each other (e.g. 0x800066C0
//      vs 0x800066FC, 0x800066B0 vs 0x80006730, 0x80006614 vs 0x80006664) —
//      the signature of a hand-unrolled / macro-expanded clamp cascade, not of
//      anything GCC re-derives from a short if/else chain.  Reproducing it
//      byte-exactly means reproducing the original source line for line.
//
// WHAT WAS ESTABLISHED (reusable; measured by hand from the want bytes):
//  * Signature is f32 fn(SEG *a, SEG *b, f32 *outA, f32 *outB) — FOUR args.
//    r3/r4 point at 32-byte objects = two 4-float Vec4s read as four PS pairs
//    at +0x00/+0x08/+0x10/+0x18 (so `typedef float v4sf mode(V4SF)`-shaped, or
//    2x{lo,hi} __ps_t).  r5/r6 are the only out-params used: `cmpwi r5,0;
//    beq; stfs f8,0(r5)` then the same for r6 with f9 (0x80006A84-0x80006A9C).
//    r7 is never read.  The m2c draft's `f32(f32*,f32*,s32,s32)` was wrong.
//    Confirmed against caller src/wip/fn_800F76E8.c, which passes
//    (arg0, &sp58, &sp88, &sp8C).
//  * Math: with P=a[0], Q=a[1], R=b[0], S=b[1]:
//        d = Q-P,  e = S-R,  c = P-R
//        dd=|d|^2  de=-(d.e)  ee=|e|^2  cd=c.d  cc=|c|^2  ce=-(c.e)
//        f30 = |dd*ee - de^de|          (Gram determinant; vs 1e-6)
//        f8  = de*ce - ee*cd            f9 = de*cd - dd*ce
//    then a 2-D Gram solve with both parameters clamped to [0,1]; every leaf
//    evaluates the same quadratic  q(x) = ee*x0^2 + 2*de*x0*x1 + dd*x1^2
//                                                     + 2*cd*x0 + 2*ce*x1 + cc
//    (verified against the general case at 0x800065D0-0x80006610 and against
//    the two-leaf tail at 0x80006A5C / 0x80006A74), and returns |q| via the
//    `fabs` instruction (0x80006A9C).
//  * WANT STACK MAP (r1-relative, 0x98 frame, f30@0x88 f31@0x90):
//      0x00 r10 = r1+8 (second base for the +8/+16 slots)
//      0x08 c.lo = a[0].lo - b[0].lo      0x0C  (junk hi)
//      0x10 c.hi = a[0].hi - b[0].hi      0x14
//      0x18 d.lo = a[1].lo - a[0].lo      0x1C
//      0x20 d.hi = a[1].hi - a[0].hi      0x24
//      0x28 e.lo = b[1].lo - b[0].lo      0x2C
//      0x30 e.hi = b[1].hi - b[0].hi      0x34
//      0x38..0x44  -d[0..3] as four stfs  (re-read as 2 psq_l at 0x38/0x40)
//      0x48 dd  0x50 de  0x58 ee  0x60 cd  0x68 cc
//      0x70/0x78/0x80  three independent copies of ce, one per main branch
//  * ROdata: 0x8028FDC4 = 1.0e-6f (epsilon), 0x8028FDC8 = 0.0f,
//    0x8028FDCC = 1.0f, 0x8028FD98 = the (0,0) pair every ps_merge00 uses.
//
// NOT TRIED / NEGATIVE: rebuilding the head in several statement orders and
// with the 5 quadratic forms forced live (`volatile` struct of 6 pairs +
// 4 floats + 8 pairs) — GCC never spills in head-only bodies, so no
// statement order can reproduce the want frame without the tail's live
// ranges.  Permutation/pin sweeps were deliberately not run.
// Sibling already matched: fn_80006AB0 (same struct shape, closest-point
// between two segments) — see src/fn_80006FA8.c / fn_800070E4.c for the
// `__ps_t` + `__builtin_ps_*` house idiom this draft uses.
#include "types.h"

extern __ps_t lbl_8028FD98; /* the (0,0) PS pair every ps_merge00 takes */
extern f32 lbl_8028FDC4;    /* 1.0e-6f */
extern f32 lbl_8028FDC8;    /* 0.0f */
extern f32 lbl_8028FDCC;    /* 1.0f */

/* A 16-byte vector: two PS pairs. `a`/`b` are 32-byte SEG objects = two of
 * these, i.e. the two endpoints of a segment. */
typedef struct {
    __ps_t lo;
    __ps_t hi;
} Vec4;

typedef struct {
    Vec4 p0;
    Vec4 p1;
} Seg;

/* Lane view of a PS pair. Per the byte-exact src/fn_8000714C.c the first
 * member (lane0) is the one a plain `lfs` at the pair's base displacement
 * reads — that is also what __builtin_ps_sum0 leaves in it. */
typedef union {
    __ps_t ps;
    struct {
        f32 lane0;
        f32 lane1;
    } f;
} PSV;

f32 fn_800063E0(Seg *a, Seg *b, f32 *outA, f32 *outB) {
    __ps_t zero = lbl_8028FD98;
    __ps_t dlo, dhi, clo, chi, elo, ehi, nlo, nhi, t;
    PSV v, w;
    f32 dd, de, ee, cd, cc, ce, g, n0, n1, n2, n3;

    /* d = a[1] - a[0],  e = b[1] - b[0],  c = a[0] - b[0] */
    dhi = __builtin_ps_sub(a->p1.hi, a->p0.hi);
    dlo = __builtin_ps_sub(a->p1.lo, a->p0.lo);
    chi = __builtin_ps_sub(a->p0.hi, b->p0.hi);
    elo = __builtin_ps_sub(b->p1.lo, b->p0.lo);
    clo = __builtin_ps_sub(a->p0.lo, b->p0.lo);
    ehi = __builtin_ps_sub(b->p1.hi, b->p0.hi);

    /* -d, kept as four scalars and re-read as two pairs later */
    v.ps = dlo;
    n0 = -v.f.lane0;
    n1 = -v.f.lane1;
    v.ps = dhi;
    n2 = -v.f.lane0;
    n3 = -v.f.lane1;
    nlo = *(volatile __ps_t *)&n0;
    nhi = *(volatile __ps_t *)&n2;

    t = __builtin_ps_mul(dhi, dhi);
    t = __builtin_ps_merge00(t, zero);
    t = __builtin_ps_madd(dlo, dlo, t);
    w.ps = __builtin_ps_sum0(t, t, t);
    dd = w.f.lane0;

    t = __builtin_ps_mul(nhi, ehi);
    t = __builtin_ps_merge00(t, zero);
    t = __builtin_ps_madd(nlo, elo, t);
    w.ps = __builtin_ps_sum0(t, t, t);
    de = w.f.lane0;

    t = __builtin_ps_mul(ehi, ehi);
    t = __builtin_ps_merge00(t, zero);
    t = __builtin_ps_madd(elo, elo, t);
    w.ps = __builtin_ps_sum0(t, t, t);
    ee = w.f.lane0;

    t = __builtin_ps_mul(chi, dhi);
    t = __builtin_ps_merge00(t, zero);
    t = __builtin_ps_madd(clo, dlo, t);
    w.ps = __builtin_ps_sum0(t, t, t);
    cd = w.f.lane0;

    t = __builtin_ps_mul(chi, chi);
    t = __builtin_ps_merge00(t, zero);
    t = __builtin_ps_madd(clo, clo, t);
    w.ps = __builtin_ps_sum0(t, t, t);
    cc = w.f.lane0;

    /* |Gram determinant of (d,e)| — must not be degenerate. */
    g = dd * ee - de * de;
    g = fabs(g);
    if (!(g > lbl_8028FDC4)) {
        /* want: 0x800068B4 — the d-parallel-e clamp cascade, unreconstructed */
        return 0.0f;
    }

    t = __builtin_ps_mul(nhi, ehi);
    t = __builtin_ps_merge00(t, zero);
    t = __builtin_ps_madd(nlo, elo, t);
    w.ps = __builtin_ps_sum0(t, t, t);
    ce = w.f.lane0;

    /* Two Gram solve numerators; each is clamped to [0,g] by the want's tree. */
    {
        f32 x = de * ce - ee * cd;
        f32 y = de * cd - dd * ce;

        if (x >= 0.0f && x <= g && y >= 0.0f && y <= g) {
            /* want: 0x800065D0-0x80006610 — the unclamped case */
            f32 s = x / g;
            f32 u = y / g;
            f32 q = s * (dd * s + de * u + 2.0f * cd) +
                    u * (de * s + ee * u + 2.0f * ce) + cc;
            if (outA != NULL) {
                *outA = s;
            }
            if (outB != NULL) {
                *outB = u;
            }
            return fabs(q);
        }
        /* The want's ~35-leaf clamp cascade (0x80006614-0x80006A84) evaluates
         * the same q() at the clamped corner; not reconstructed. */
        return fabs(cc);
    }
}
