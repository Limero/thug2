// WIP DRAFT (non-matching) — hand-written C recovered from the retail bytes.
// family=m2c range=0x800699C8-0x80069C58 size=656B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
//
// PARKED 2026-10-05: recovered semantics + structure, blocked on GPR allocation.
//
// (a) BEST MEASURED SCORE: prefix-exact 3/164 words (frame setup, pair load,
//     index shift), object 632 B vs want 656 B (24 B / 6 words short).  `tools/score_wip.py` reports 1.90% because the
//     24-byte length shortfall voids the index-aligned score.
//
// (b) RESIDUAL.  Every semantic element is now in place and every operand
//     offset matches want; what is left is purely the GPR prologue shape.
//     want 0x800699D4..0x8006A000 builds a SIX-register pointer web: the
//     frame-slot address, three independent copies of the row base, and two
//     base-plus-offset copies.  This object compiles to a single base-sum
//     register reused for everything, so all 161 words from 0x800699D4 on
//     shift and the six missing words are the absent copies.  Secondary
//     (already correct in this body, listed because it is what a retry should
//     NOT re-chase): the block-1/block-2 scalar walks (update-load then three
//     lane loads off each base copy), and the two dead pair stores to the
//     frame sink — this body's `V r` sink already reproduces them.
//
// (c) RULED OUT.
//     * Wrong vector layout: want's block-1 scalars are base+0xA8,0xB0,0xB4,0xB8
//       and block-2's are 0xD8,0xE0,0xE4,0xE8 (gap at +0xAC / +0xDC), NOT a
//       contiguous Vec4 — the `n1.c` contiguous-Vec4 layout was measured and is
//       wrong.  This `E` matches.
//     * `__ps_t` is 8 B (recipes §6dq): each 16-byte vector op is TWO
//       assignments (`p[0]` / `p[1]`), which is what the body does; a
//       single-`__ps_t` member under-counts by 8 B and was measured.
//     * Wrong pair-op spelling: a plain `V`/`__ps_t` struct assignment lowers
//       to `lwz`/`stw` runs (measured on every 64-byte-copy and 16-byte-copy
//       shape); per-`__ps_t` element assignment is required for the `psq_l` /
//       `psq_st` pairs want uses.  The 8-pair tail at +0x68 is written as 8
//       explicit pair assignments for the same reason.
//     * Wrong subtraction order/polarity: want subtracts the second pair
//       first (pair-subtract off the still-live saved-vector load), then
//       reloads the first pair from the frame slot — the body's ordering
//       already produces that subtract + store pair set.
//     * Register pins on the base pointer: pinning it to any of six colours
//       measured IDENTICAL output — the compiler folds the scaled-index sum
//       before allocation, so the pin has nothing to bite on.  Pointer-typed
//       pins fail to parse / are dropped (recipes §6az-245: only word pins
//       bind).  The CSE cannot be turned off from the command line (no such
//       flag in this compiler family, recipes §6bq), so the tree-level fold
//       cannot be disabled that way.
//     * Defeating the CSE structurally: independently-typed pointers
//       (`__ps_t*` + `f32*` + `V*` to the same address), separate struct
//       pointers derived twice, `f32 *base`-with-absolute-indices, `char*`
//       chains, and a union/struct local for `sv` were all measured; every one
//       still yields ONE shared base-sum register and the same 632 B object.
//
// The next thing to try is not another C spelling but a lever that changes
// cc1's alias/CSE view of the `base` sum — e.g. a zero-code `__asm__("" : "+r")`
// barrier between the `sv` pair stores and the `p1`/`p2` derivations, or
// `volatile` staging of the `sv` load — since the six missing words are all
// copies of a value cc1 currently believes it can share.
// UPDATE 2026-10-18: `volatile s32` staging of the base sum measured WORSE
// (640B object, 0.00%, prefix lost; baseline 632B with 3-word prefix-exact).
// The volatile round-trip lands in the prologue and does not create the six
// downstream base copies. Reverted.
#include "types.h"
#include "structs.h"

/* The per-frame object.  `arg1` selects a 16-byte-stride row, so every field
 * below is addressed off `arg0 + arg1*16`.  The two vectors at +0xA8 and
 * +0xD8 are the ones this function rewrites; the +0x68..+0xA7 run is the
 * 4x4 matrix it copies from arg2 (seen as eight __ps_t pairs).  Blocks A and B
 * each carry a 4-byte hole at +0xAC / +0xDC: want's `lfsu f9,0xa8(r9)` walk
 * steps to 0xB0/0xB4/0xB8, skipping 0xAC. */
typedef struct {
    char pad0[0xA8];
    f32 a;  f32 hole;  f32 b, c, d;   /* +0xA8 block: read at A8, B0, B4, B8 */
    char pad1[0x1C];
    f32 e;  f32 hole2; f32 f, g, h;   /* +0xD8 block: read at D8, E0, E4, E8 */
} Row;

/* 16-byte paired-single value with both views: the `__ps_t` view gives the
 * psq_l/ps_add/ps_sub/ps_mr ops, the `f` view gives the scalar lfs lanes. */
typedef union {
    struct { f32 x, y, z, w; } f;
    __ps_t p[2];
} V;

void fn_800699C8(s32 arg0, s32 arg1, f32 *arg2) {
    Row *o = (Row *)(arg0 + (arg1 << 4));
    V *va = (V *)&o->a;     /* +0xA8, rewritten twice */
    V *vd = (V *)&o->e;     /* +0xD8, rewritten once */
    V sv;                   /* frame sp+8: the saved +0xA8 vector of arg0 */
    V t;                    /* frame sp+0x18: the computed vector */
    V r;                    /* frame sp+0x28: the four dot-product results */
    f32 A;

    /* Save arg0's own +0xA8 vector (two psq pairs off r3). */
    sv.p[0] = ((__ps_t *)(arg0 + 0xA8))[0];
    sv.p[1] = ((__ps_t *)(arg0 + 0xA8))[1];

    /* Re-base the row relative to arg0, then transform: row.v = M * (row.v - sv). */
    va->p[0] -= sv.p[0];
    va->p[1] -= sv.p[1];
    A = o->a;
    r.f.x = A*arg2[0]  + o->b*arg2[4]  + o->c*arg2[8]  + o->d*arg2[12];
    r.f.y = A*arg2[1]  + o->b*arg2[5]  + o->c*arg2[9]  + o->d*arg2[13];
    r.f.z = A*arg2[2]  + o->b*arg2[6]  + o->c*arg2[10] + o->d*arg2[14];
    r.f.w = A*arg2[3]  + o->b*arg2[7]  + o->c*arg2[11] + o->d*arg2[15];
    t.p[0] = r.p[0];
    t.p[1] = r.p[1];
    va->p[0] = r.p[0];
    va->p[1] = r.p[1];

    /* Same transform on the second vector, then undo the re-basing. */
    r.f.x = o->e*arg2[0]  + o->f*arg2[4]  + o->g*arg2[8]  + o->h*arg2[12];
    r.f.y = o->e*arg2[1]  + o->f*arg2[5]  + o->g*arg2[9]  + o->h*arg2[13];
    r.f.z = o->e*arg2[2]  + o->f*arg2[6]  + o->g*arg2[10] + o->h*arg2[14];
    r.f.w = o->e*arg2[3]  + o->f*arg2[7]  + o->g*arg2[11] + o->h*arg2[15];
    t.p[0] = r.p[0];
    t.p[1] = r.p[1];
    vd->p[0] = r.p[0];
    vd->p[1] = r.p[1];
    va->p[0] += sv.p[0];
    va->p[1] += sv.p[1];

    /* Copy the 64-byte matrix arg2 -> arg0+0x68 (eight psq pairs, r3/r5 based). */
    ((__ps_t *)(arg0 + 0x68))[0] = ((__ps_t *)arg2)[0];
    ((__ps_t *)(arg0 + 0x68))[1] = ((__ps_t *)arg2)[1];
    ((__ps_t *)(arg0 + 0x68))[2] = ((__ps_t *)arg2)[2];
    ((__ps_t *)(arg0 + 0x68))[3] = ((__ps_t *)arg2)[3];
    ((__ps_t *)(arg0 + 0x68))[4] = ((__ps_t *)arg2)[4];
    ((__ps_t *)(arg0 + 0x68))[5] = ((__ps_t *)arg2)[5];
    ((__ps_t *)(arg0 + 0x68))[6] = ((__ps_t *)arg2)[6];
    ((__ps_t *)(arg0 + 0x68))[7] = ((__ps_t *)arg2)[7];
}
