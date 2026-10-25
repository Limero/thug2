// PARKED 2026-10-01: FAIL (did not compile) -> DIFF 4.07% (118/123
// masked words).  Object .text = 0x1FC = 508B vs want 0x1EC = 492B
// (symbols.txt), i.e. 4 instructions TOO LONG; the range marker agrees
// (size=492B).  NB `want_got.py` prints "got 492B" -- that is its own compile
// and it is NOT what readelf reports; trust readelf on $LEAF_TMPDIR/*.o.
//
// THE COMPILE FAILURE IS FIXED (this is the round's win). m2c had rendered the
// `sqrtf(len2)` call with THREE extra arguments -> cc1 exits 1 with
// "too many arguments to function `sqrtf'" (printed as a *warning:* -- a grep
// for warning misses the only fatal line, AGENTS/draft brief). sqrtf also had no
// prototype; it is a scope:global symbol (.text:0x80270CA4) so `f32 sqrtf(f32)`
// is correct AND kills a crclr. The whole 32-instruction paired-single branch
// and the final arg2->arg0 copy were `0;` stubs (statics/psq DCE).
//
// VERIFIED want bytes were decoded with GNU objdump (capstone/ps_disasm
// mislabel the PS words). The pair-load print convention and pair overlap
// were confirmed by probe: loads print one higher than the true pair base,
// and the two loaded pairs overlap on one float.
//
// RESIDUAL, in the order worth attacking:
//  1. FRAME (dominant). want: frame 0x68 with 2 saved GPRs => locals region
//     0x38 = 56B, touched only at frame offsets 8..0x18 (five f32). got:
//     frame 0x88 with 3 saved GPRs => locals 0x54 = 84B, and sp18 lands 8
//     bytes lower than want. ~28B of extra locals; the paired-single arm's
//     scale temporaries are the bulk. TRIM THE PAIRED-SINGLE ARM'S LIVE SET
//     to ~4 pairs first -- this is the gate for everything else (the whole
//     body is offset-shifted until the frame matches).
//     Measured: with `volatile double _dummy` (the inherited scaffold) the frame
//     was 0x90; deleting it (the +8 FPR quirk lives in the FPR region, not
//     locals) gave 0x88. Do NOT re-add it.
//  2. Dot-product SEED order. want evaluates the Y term (arg1->y * arg2->y)
//     as the lone seed multiply, then chains X, Z, W accumulations onto it.
//     Both the m2c right-nested expression AND the staged three-statement form
//     made cc1 reassociate to a different seed (measured: staging gave the X
//     term as the seed). Per the staging recipe the two results must be staged
//     as NAMED locals then chained; try order variants before giving up.
//  3. Branch polarity is SOLVED: `if (dot < 0.0f)` gives want's float-compare
//     plus exit-branch layout with the negate INLINE. The inverted spelling
//     emits an extra condition-combine plus taken branch.
//  4. NEGATE-branch stack slots: want's 4 stores land at frame offsets 8, 0xc,
//     0x14, 0x10. Per the store-order recipe the emitted order groups each
//     class's head in source order then each tail, which for want's source
//     [sp8, spC, sp10, sp14] gives emit [8, c, 14, 10]. Measured with source
//     [sp8, spC, sp10, sp14]: got [0xc, 8, ...] -- the per-class split did not
//     hold; retry [sp8, spC, sp14, sp10] (m2c's order) before permuting further.
//  5. Two DEAD-but-kept operations in want: a self-difference (== 0, result
//     unused) and a select whose 3rd operand is never written in want. Family
//     zero-keep recipe: a zero-code constraint keeps a provably-dead value
//     alive -- budget 2 emitted units for these (4% of the function, inside
//     the 20% rule).
//  6. Constants: lbl_802915B4=0.0f B8=1e-5f BC=0.5f C0=3.0f C4=1.0f,
//     lbl_80300384=1 (so the paired-single arm is the LIVE one). All six
//     addresses were hand-decoded from want's constant setup and exist in
//     symbols.txt.
// WIP DRAFT (non-matching) — hand-rebuilt; original bytes in DOL, not
// reproduced here per repo policy.
// family=m2c range=0x80026140-0x8002632C size=492B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PURPOSE: a *lerp + normalize* on two 4-float vectors, with TWO mutually
// exclusive implementations selected by the .data flag `lbl_80300384`
// (currently 1 => the paired-single path is the live one):
//   flag == 0 -> scalar f32 path, inv = 1.0f / sqrtf(len2), ends at 0x26270
//   flag != 0 -> paired-single path, Newton-refined rsqrte, ends at 0x261ec
// Both converge on the shared tail at 0x262f4 which copies arg2 -> arg0 as
// TWO 8-byte PS pairs and returns arg0.
//
// Full verified shape of the flag!=0 path's paired-single ops, which is the
// part still to be matched: load both vector pairs and the time pair, broadcast
// the time, difference the vectors, interpolate, load the three scalar
// constants, square-and-accumulate through the paired ops, refine the
// reciprocal square root (Newton step), guard-select the estimate, scale both
// result pairs, store both pairs, and branch to the shared tail.
//
// ORIGINAL m2c BUGS FIXED (this is why the draft used to FAIL to compile):
//  1. m2c rendered the `sqrtf(len2)` call with THREE extra arguments
//     (temp_f11, temp_f12, temp_f13_2) -> "too many arguments to function
//     `sqrtf'", exit 1.  The real call is `sqrtf(len2)`, arity 1.
//  2. sqrtf had no declaration at all (it is a scope:global symbol,
//     .text:0x80270CA4). Declared `f32 sqrtf(f32)`.
//  3. m2c emitted the whole 32-instruction paired-single branch as the stub
//     `0;` (statics/psq DCE) — the object was ~128 bytes short of want.
//  4. the final `arg2 -> arg0` copy was missing entirely (0; x2).
//  5. the negate branch's 4 stack slots are read back as TWO 8-byte PS
//     pairs, not as 4 scalars (sp8/spC -> arg2[0]/arg2[4],
//     sp10/sp14 -> arg2[8]/arg2[C]).
#include "types.h"
extern char lbl_802915B4[]; /* 0.0f        */
extern char lbl_802915B8[]; /* 1.0e-5f     */
extern char lbl_802915BC[]; /* 0.5f        */
extern char lbl_802915C0[]; /* 3.0f        */
extern char lbl_802915C4[]; /* 1.0f        */
extern char lbl_80300384[]; /* s32 mode    */
f32 sqrtf(f32);

/* M6.89d / 6dy: the corpus-merged CStruct types 0x0..0xC as s32 (majority vote
   over 2041 files), so every read here would compile to lwz + an int->float
   conversion dance instead of want's lfs. File-local layout with real f32. */
typedef struct Vec4 { f32 x, y, z, w; } Vec4;

s32 fn_80026140(s32 arg0, Vec4 *arg1, Vec4 *arg2, f32 farg0) {
    f32 sp8;
    f32 spC;
    f32 sp10;
    f32 sp14;
    f32 sp18;
    f32 dot;
    f32 v0, v1, v2, v3;

    sp18 = farg0;
    dot = arg1->y * arg2->y;
    dot = arg1->x * arg2->x + dot;
    dot = arg1->z * arg2->z + dot;
    dot = arg1->w * arg2->w + dot;
    if (dot < *(f32 *)lbl_802915B4) {
        sp8 = -arg2->x;
        spC = -arg2->y;
        sp10 = -arg2->z;
        sp14 = -arg2->w;
        *(__ps_t *)arg2 = *(__ps_t *)&sp8;
        *((__ps_t *)arg2 + 1) = *(__ps_t *)&sp10;
    }
    if (*(s32 *)lbl_80300384 == 0) {
        v1 = ((arg2->y - arg1->y) * sp18) + arg1->y;
        v0 = ((arg2->x - arg1->x) * sp18) + arg1->x;
        v2 = ((arg2->z - arg1->z) * sp18) + arg1->z;
        v3 = ((arg2->w - arg1->w) * sp18) + arg1->w;
        dot = *(f32 *)lbl_802915C4 /
            sqrtf(((v3 * v3) + ((v2 * v2) + ((v0 * v0) + (v1 * v1)))));
        arg2->w = v3 * dot;
        arg2->x = v0 * dot;
        arg2->y = v1 * dot;
        arg2->z = v2 * dot;
    } else {
        SN_PS_type tb, d0, d1, r0, r1, ac, est;
        f32 half, corr, guard;
        tb.ps = *(__ps_t *)&sp18;
        tb.ps = __builtin_ps_merge00(tb.ps, tb.ps);
        d0.ps = __builtin_ps_sub(*(__ps_t *)&arg2->x, *(__ps_t *)&arg1->x);
        d1.ps = __builtin_ps_sub(*(__ps_t *)&arg2->z, *(__ps_t *)&arg1->z);
        r0.ps = __builtin_ps_madd(d0.ps, tb.ps, *(__ps_t *)&arg1->x);
        r1.ps = __builtin_ps_madd(d1.ps, tb.ps, *(__ps_t *)&arg1->z);
        guard = *(f32 *)lbl_802915B8;
        half = *(f32 *)lbl_802915BC;
        corr = *(f32 *)lbl_802915C0;
        ac.ps = __builtin_ps_madd(r1.ps, r1.ps, __builtin_ps_mul(r0.ps, r0.ps));
        ac.ps = __builtin_ps_sum0(ac.ps, ac.ps, ac.ps);
        est.ps = __builtin_ps_rsqrte(ac.ps);
        half = est.flt.lo * half;
        corr = corr - (est.flt.lo * est.flt.lo) * ac.flt.lo;
        guard = ac.flt.lo - guard;
        corr = corr * half;
        est.ps = __builtin_ps_sel(guard, corr, est.ps);
        *(__ps_t *)&arg2->x = __builtin_ps_muls0(r0.ps, est.ps);
        *(__ps_t *)&arg2->z = __builtin_ps_muls0(r1.ps, est.ps);
    }
    *(__ps_t *)arg0 = *(__ps_t *)arg2;
    *((__ps_t *)arg0 + 1) = *((__ps_t *)arg2 + 1);
    return arg0;
}