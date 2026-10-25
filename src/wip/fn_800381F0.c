// WIP DRAFT (non-matching) — worker rewrite of fn_800381F0
// family=m2c range=0x800381F0-0x80038C04 size=2580B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// PARKED 2026-10-05 (fn_800381F0-ps-skel): 7.9% (m2c draft) -> 42.6%, object
// 2576 B vs want 2580 B (one word short).  Everything from 0x80038700 on is
// pure block-misalignment; loop 1 (0x800381F0..0x800386D8) is ~85% correct.
//
// RESIDUAL (measured with tools/want_got.py / score_wip.py, -mps-float):
//  1. SIZE: 2576 vs 2580 B.  Loop-2 preheader is missing want's
//     `lis r9,0x8029; addi r10,r1,0x48; lfs f8,0x1f00(r9); fmr f7,f8` pair
//     (2 words) and loop 1's mm entry hoists `lwz r9,4(r30)` *above*
//     `cmpwi r28,0` (1 word).  Net -1 word.
//  2. FRAME: `stmw r23,0x6c(r1)` + `-0x90(r1)` vs want `stmw r24,0x68(r1)` +
//     `-0x88(r1)`.  ngccc hoists `lis r23,0` (the address of the 1.0f pool
//     entry lbl_80291F00) into a 9th callee-saved GPR across loop 1; want
//     rematerialises `lis`+`lfs` inside the loop body.  All *data* frame
//     offsets now match want exactly (out 0x08..0x47, pv 0x48/0x4c,
//     sc 0x50/0x58/0x60) thanks to the single `Frame` struct local.
//  3. BLOCK LAYOUT: want emits the loop-1 out-of-line "mask bit set" copy path
//     (0x800386DC) *after* the mm block and branches back to the loop latch;
//     got orders them the other way round.
//  4. FPR COLOURING: want's copy-back run alternates
//     f13,f0,f11,f13,f0,f11,f13,f0; got reuses f0 for all eight pairs (same
//     addresses, same order except the last two are swapped).
//  5. `mr r5, r31` before `bl fn_80038094` is missing in got (arg3 = d).
//  6. mm-block first two loads are transposed vs want's sched2 order.
//
// RULED OUT (all measured, none helped):
//  * `-mps-float` is required (the whole body is ps_mul/ps_muls0); extra flags
//    not swept - the residual is not a flag question.
//  * Volatile on the pv array, on the `__ps_t` mm accumulator, or on a single
//    copy pair: this ProDG/3.9.3 cc1 IGNORES `volatile` entirely (byte-identical
//    objects), so no stack slot can be forced that way.
//  * `extern f32` vs `extern const f32`, named local vs direct global reads of
//    lbl_80291F00, array-subscript / `*(__ps_t*)&f32` / `char*` spellings of the
//    constant, `&fr.out` vs `out` for the copy source: none move the `lis` into
//    the loop.
//  * `pv` as `void*[2]` / `Mat*[2]` / `struct{a,b}` / `void** = pv` / `&pv[0]`
//    — only the `(&fr.pv[0])[k]` address-taken form actually reaches the stack
//    (it is what produced the correct 0x48/0x4c slots), but `addi r10,r1,0x48`
//    (the CSE'd `&pv` hoisted into r10) never appears.
//  * Two independent 1.0f variables in loop 2 (`one`/`oneb`, `oneb` re-read from
//    the pool instead of copied): ngccc CSEs them into one FPR, so want's
//    `fmr f7,f8` never appears.
//  * Copy-back statement order: strictly ascending lets ngccc drop the 8th
//    `psq_st` entirely (2568 B); any non-identity permutation of the last pair
//    keeps all eight but emits the last two out of order.  [0,1,2,3,4,5,7,6] is
//    the best of the eight tried (42.6%).
//  * Whole-body transposition of the mm operand order: loop 1 MUST be
//    `d[k]*m[..]` and loop 2 MUST be `m[..]*d[k]` (the m2c draft had loop 1's
//    indices wrong as well: out[4i+j] = sum_t d[4i+t]*m[4t+j]).
//  * `volatile __ps_t ov[8]` as the mm accumulator: replaces `stfs` with
//    `ps_mr`+`psq_st` (2688 B, far worse).
//
// USEFUL SHAPES ESTABLISHED (reusable for sibling skeleton functions):
//  * `typedef union { __ps_t p; f32 f[2]; } Pair;` + `d[k].p = s[k].p` is what
//    emits `psq_l ..,W0` + `psq_st ..,W0` — i.e. the 4-byte-per-8-byte-stride
//    copies this whole function family uses.  A plain `((f32*)p)[k]` view emits
//    lfs/stfs instead and does NOT match.
//  * `typedef union { __ps_t p[8]; f32 f[16]; } Mat;` + `out.f[k] = ...` emits
//    `stfs` for the mm results (correct); reading the scale triple as
//    `*((__ps_t *)&e->s[0])[0]` / `[1]` is what makes the scale operands load as
//    `psq_l ..,W0` (feeding `ps_mul`) while the same fields read as `f32` for the
//    `fcmpu` guards stay `lfs`.  (cf. AGENTS-recipes §6fy2 items 1-2.)
//  * Loop shape: a plain `for (i=0;i<n;i++)` with a multi-exit body makes
//    ngccc emit the doubled test want has (top `cmpw i,n; bge` + latch
//    `inc; cmpw i,n; blt`).
//  * One `Frame` struct local is required to pin out(0x08) / pv(0x48) /
//    sc(0x50,0x58,0x60); separate locals are sorted by size by cc1 and the
//    offsets come out wrong in every declaration order tried.
#include "types.h"
#include "structs.h"

extern const f32 lbl_80291F00;

typedef union { __ps_t p; f32 f[2]; } Pair;
typedef union { __ps_t p[8]; f32 f[16]; } Mat;

/* arg0->unk0x18[i]: 0x20-byte lookup entry.  +0x04 parent matrix,
 * +0x08 packed flags, +0x10..+0x18 scale triple. */
typedef struct {
    char pad0x00[4];
    Mat *m;
    u32 flags;
    u32 pad0x0C;
    f32 s[4];
} Ent;

typedef struct {
    u32 pad0x00;
    Mat *dst;
    s32 mbase;
    s32 bit;
    s32 pad0x10;
    s32 n;
    Ent *ent;
} Ctl;

/* the caller's frame: 16-float product scratch (0x08), the 2-pointer
 * hand-off pair (0x48) and three 8-byte scale slots (0x50/0x58/0x60). */
typedef struct {
    Mat out;
    void *pv[2];
    Pair sc[3];
} Frame;

void fn_80038094(void *a, void *b, Mat *c, s32 d, s32 e);
void fn_80037CF4(Ctl *a);
Mat *fn_8003A428(s32 o);

#define DP(k) (((Pair *)(void *)d)[(k) >> 1].f[(k) & 1])
#define SP(k) (((Pair *)(void *)m)[(k) >> 1].f[(k) & 1])

void fn_800381F0(Ctl *a, void *arg1, void *arg2) {
    Frame fr;
    Ent *e = a->ent;
    Mat *d = a->dst;
    Mat *m;
    __ps_t *dp;
    __ps_t *sp;
    void *p = arg1;
    void *q = arg2;
    s32 bm = 1 << a->bit;
    s32 *mask = (s32 *)((char *)a->mbase + 0x408);
    s32 i;

    for (i = 0; i < a->n; i++) {
        if (!(e->flags & 0x40000000)) {
            s32 sel = 1;

            if ((mask[i] & bm) == 0) {
                sel = 0;
            }
            if (sel == 0) {
                fn_80038094(p, q, d, 0, 0);
                if (e->flags & 0x10000000) {
                    f32 one = lbl_80291F00;

                    dp = (__ps_t *)(void *)d;
                    sp = (__ps_t *)(void *)&e->s[0];
                    dp[0] = __builtin_ps_mul(dp[0], sp[0]);
                    dp[1] = __builtin_ps_mul(dp[1], sp[1]);
                    dp[2] = __builtin_ps_mul(dp[2], sp[0]);
                    dp[3] = __builtin_ps_mul(dp[3], sp[1]);
                    dp[4] = __builtin_ps_mul(dp[4], sp[0]);
                    dp[5] = __builtin_ps_mul(dp[5], sp[1]);
                    dp[6] = __builtin_ps_mul(dp[6], sp[0]);
                    dp[7] = __builtin_ps_mul(dp[7], sp[1]);
                    if (!(e->s[0] == one && e->s[1] == one && e->s[2] == one)) goto mm1;
                    m = e->m;
                    ((Pair *)(void *)d)[6].p = ((Pair *)(void *)m)[6].p; ((Pair *)(void *)d)[7].p = ((Pair *)(void *)m)[7].p;
                    continue;
mm1:
                    if (i != 0) {
                        m = e->m;
                        fr.out.f[ 0] = DP( 0)*SP( 0) + DP( 1)*SP( 4) + DP( 2)*SP( 8) + DP( 3)*SP(12);
                        fr.out.f[ 1] = DP( 0)*SP( 1) + DP( 1)*SP( 5) + DP( 2)*SP( 9) + DP( 3)*SP(13);
                        fr.out.f[ 2] = DP( 0)*SP( 2) + DP( 1)*SP( 6) + DP( 2)*SP(10) + DP( 3)*SP(14);
                        fr.out.f[ 3] = DP( 0)*SP( 3) + DP( 1)*SP( 7) + DP( 2)*SP(11) + DP( 3)*SP(15);
                        fr.out.f[ 4] = DP( 4)*SP( 0) + DP( 5)*SP( 4) + DP( 6)*SP( 8) + DP( 7)*SP(12);
                        fr.out.f[ 5] = DP( 4)*SP( 1) + DP( 5)*SP( 5) + DP( 6)*SP( 9) + DP( 7)*SP(13);
                        fr.out.f[ 6] = DP( 4)*SP( 2) + DP( 5)*SP( 6) + DP( 6)*SP(10) + DP( 7)*SP(14);
                        fr.out.f[ 7] = DP( 4)*SP( 3) + DP( 5)*SP( 7) + DP( 6)*SP(11) + DP( 7)*SP(15);
                        fr.out.f[ 8] = DP( 8)*SP( 0) + DP( 9)*SP( 4) + DP(10)*SP( 8) + DP(11)*SP(12);
                        fr.out.f[ 9] = DP( 8)*SP( 1) + DP( 9)*SP( 5) + DP(10)*SP( 9) + DP(11)*SP(13);
                        fr.out.f[10] = DP( 8)*SP( 2) + DP( 9)*SP( 6) + DP(10)*SP(10) + DP(11)*SP(14);
                        fr.out.f[11] = DP( 8)*SP( 3) + DP( 9)*SP( 7) + DP(10)*SP(11) + DP(11)*SP(15);
                        fr.out.f[12] = DP(12)*SP( 0) + DP(13)*SP( 4) + DP(14)*SP( 8) + DP(15)*SP(12);
                        fr.out.f[13] = DP(12)*SP( 1) + DP(13)*SP( 5) + DP(14)*SP( 9) + DP(15)*SP(13);
                        fr.out.f[14] = DP(12)*SP( 2) + DP(13)*SP( 6) + DP(14)*SP(10) + DP(15)*SP(14);
                        fr.out.f[15] = DP(12)*SP( 3) + DP(13)*SP( 7) + DP(14)*SP(11) + DP(15)*SP(15);
                        ((Pair *)(void *)d)[0].p = ((Pair *)(void *)&fr.out)[0].p; ((Pair *)(void *)d)[1].p = ((Pair *)(void *)&fr.out)[1].p; ((Pair *)(void *)d)[2].p = ((Pair *)(void *)&fr.out)[2].p; ((Pair *)(void *)d)[3].p = ((Pair *)(void *)&fr.out)[3].p; ((Pair *)(void *)d)[4].p = ((Pair *)(void *)&fr.out)[4].p; ((Pair *)(void *)d)[5].p = ((Pair *)(void *)&fr.out)[5].p; ((Pair *)(void *)d)[7].p = ((Pair *)(void *)&fr.out)[7].p; ((Pair *)(void *)d)[6].p = ((Pair *)(void *)&fr.out)[6].p;
                    }
                }
            } else {
                m = e->m;
                ((Pair *)(void *)d)[0].p = ((Pair *)(void *)m)[0].p; ((Pair *)(void *)d)[1].p = ((Pair *)(void *)m)[1].p; ((Pair *)(void *)d)[2].p = ((Pair *)(void *)m)[2].p; ((Pair *)(void *)d)[3].p = ((Pair *)(void *)m)[3].p; ((Pair *)(void *)d)[4].p = ((Pair *)(void *)m)[4].p; ((Pair *)(void *)d)[5].p = ((Pair *)(void *)m)[5].p; ((Pair *)(void *)d)[6].p = ((Pair *)(void *)m)[6].p; ((Pair *)(void *)d)[7].p = ((Pair *)(void *)m)[7].p;
            }
        }
        d += 1;
        e += 1;
        p = (char *)p + 0x10;
        q = (char *)q + 0x10;
    }
    {
        Mat *lm = fn_8003A428(a->mbase);
        f32 one = lbl_80291F00;
        f32 oneb = one;
        __ps_t *lp;
        s32 j;

        d = a->dst;
        e = a->ent;
        for (j = 0; j < a->n; j++) {
            if (!(e->flags & 0x40000000)) {
                if (e->flags & 0x20000000) {
                    fr.sc[0].f[0] = e->s[0];
                    fr.sc[1].f[0] = e->s[1];
                    fr.sc[2].f[0] = e->s[2];
                    lp = (__ps_t *)(void *)d;
                    lp[0] = __builtin_ps_muls0(lp[0], fr.sc[0].p);
                    lp[1] = __builtin_ps_muls0(lp[1], fr.sc[0].p);
                    lp[2] = __builtin_ps_muls0(lp[2], fr.sc[1].p);
                    lp[3] = __builtin_ps_muls0(lp[3], fr.sc[1].p);
                    lp[4] = __builtin_ps_muls0(lp[4], fr.sc[2].p);
                    lp[5] = __builtin_ps_muls0(lp[5], fr.sc[2].p);
                    if (!(e->s[0] == oneb && e->s[1] == oneb && e->s[2] == oneb)) goto mm2;
                    ((Pair *)(void *)d)[6].p = ((Pair *)(void *)lm)[6].p; ((Pair *)(void *)d)[7].p = ((Pair *)(void *)lm)[7].p;
                    goto setw;
                }
mm2:
                fr.pv[0] = lm;
                fr.pv[1] = d;
                m = (Mat *)(&fr.pv[0])[0];
                if (j != 0) {
                        fr.out.f[ 0] = SP( 0)*DP( 0) + SP( 1)*DP( 4) + SP( 2)*DP( 8) + SP( 3)*DP(12);
                        fr.out.f[ 1] = SP( 0)*DP( 1) + SP( 1)*DP( 5) + SP( 2)*DP( 9) + SP( 3)*DP(13);
                        fr.out.f[ 2] = SP( 0)*DP( 2) + SP( 1)*DP( 6) + SP( 2)*DP(10) + SP( 3)*DP(14);
                        fr.out.f[ 3] = SP( 0)*DP( 3) + SP( 1)*DP( 7) + SP( 2)*DP(11) + SP( 3)*DP(15);
                        fr.out.f[ 4] = SP( 4)*DP( 0) + SP( 5)*DP( 4) + SP( 6)*DP( 8) + SP( 7)*DP(12);
                        fr.out.f[ 5] = SP( 4)*DP( 1) + SP( 5)*DP( 5) + SP( 6)*DP( 9) + SP( 7)*DP(13);
                        fr.out.f[ 6] = SP( 4)*DP( 2) + SP( 5)*DP( 6) + SP( 6)*DP(10) + SP( 7)*DP(14);
                        fr.out.f[ 7] = SP( 4)*DP( 3) + SP( 5)*DP( 7) + SP( 6)*DP(11) + SP( 7)*DP(15);
                        fr.out.f[ 8] = SP( 8)*DP( 0) + SP( 9)*DP( 4) + SP(10)*DP( 8) + SP(11)*DP(12);
                        fr.out.f[ 9] = SP( 8)*DP( 1) + SP( 9)*DP( 5) + SP(10)*DP( 9) + SP(11)*DP(13);
                        fr.out.f[10] = SP( 8)*DP( 2) + SP( 9)*DP( 6) + SP(10)*DP(10) + SP(11)*DP(14);
                        fr.out.f[11] = SP( 8)*DP( 3) + SP( 9)*DP( 7) + SP(10)*DP(11) + SP(11)*DP(15);
                        fr.out.f[12] = SP(12)*DP( 0) + SP(13)*DP( 4) + SP(14)*DP( 8) + SP(15)*DP(12);
                        fr.out.f[13] = SP(12)*DP( 1) + SP(13)*DP( 5) + SP(14)*DP( 9) + SP(15)*DP(13);
                        fr.out.f[14] = SP(12)*DP( 2) + SP(13)*DP( 6) + SP(14)*DP(10) + SP(15)*DP(14);
                        fr.out.f[15] = SP(12)*DP( 3) + SP(13)*DP( 7) + SP(14)*DP(11) + SP(15)*DP(15);
                    ((Pair *)(void *)d)[0].p = ((Pair *)(void *)&fr.out)[0].p; ((Pair *)(void *)d)[1].p = ((Pair *)(void *)&fr.out)[1].p; ((Pair *)(void *)d)[2].p = ((Pair *)(void *)&fr.out)[2].p; ((Pair *)(void *)d)[3].p = ((Pair *)(void *)&fr.out)[3].p; ((Pair *)(void *)d)[4].p = ((Pair *)(void *)&fr.out)[4].p; ((Pair *)(void *)d)[5].p = ((Pair *)(void *)&fr.out)[5].p; ((Pair *)(void *)d)[7].p = ((Pair *)(void *)&fr.out)[7].p; ((Pair *)(void *)d)[6].p = ((Pair *)(void *)&fr.out)[6].p;
                }
setw:
                DP(3) = one; DP(7) = one; DP(11) = one;
            }
            lm++;
            d += 1;
            e += 1;
        }
    }
    fn_80037CF4(a);
}
