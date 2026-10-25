// WIP DRAFT (non-matching) — hand-rebuilt SNAPS paired-single reconstruction
// family=m2c range=0x801FF57C-0x801FFC88 size=1804B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-09-25 — full semantic rebuild done; 2.2% masked (DIFF),
//   1660B / 415 insns compiled vs 1804B / 451 want (92% of the body),
//   all 9 call sites present. Blocked on REGISTER ALLOCATION / FRAME SIZE,
//   not on the PS opcode set (details at the bottom). Previous state of this
//   file was a ~1/4-body m2c stub at 0.2%; the body below is complete.
//
// === SIGNATURE (prologue-audited) ===
// 6 integer args, NO float arg (m2c's farg9 is bogus):
//   r28 = arg0  f32[4]   (a 3D position, 4th lane unused)
//   r31 = arg1  f32[16]  (0x40-byte "plane": 4 rows of 4 floats)
//   r26 = arg2  f32[4]
//   r25 = arg3  f32[3]   (3D position)
//   r24 = arg4  s32 flag
//   r22 = arg5  s32 flag
// arg1 layout (all accesses observed in this fn):
//   +0x00,+0x04,+0x08,+0x0C   row0   (w at +0x0C forced to 0.0f here)
//   +0x10,+0x14,+0x18,+0x1C   row1   (w at +0x1C forced to 0.0f here)
//   +0x20,+0x24,+0x28,+0x2C   row2   (w at +0x2C forced to 0.0f here)
//   +0x30..+0x3F              row3   (only +0x3C = 1.0f is written)
//
// === FRAME MAP (r1-relative) ===
// 0x08/0x0C  fr.v[0..1]  = arg0 row0 - arg2 row0   (psq pair)
// 0x10/0x14  fr.v[2..3]  = arg0 row1 - arg2 row1
// 0x18..0xBF fr.ctx       0xA8-byte descriptor ctx, &ctx in r21 AND r30
//   +0x80 (r1+0x98)  f32 read once (used as a scale factor)
//   +0x88 (r1+0xA0)  f32[4] read as two psq pairs in the reflection step
//   +0xA8 (r1+0xC0)  s32 "handle" — written by fn_80107B20, then tested and
//                    released with CObject_RemoveRefLink; NEVER initialised in
//                    this function (it aliases ctx+0xA8).
// 0xD8..0x15F  17 psq-pair temps, expressed here as f32 t[34] (t[k] = 4k+0xD8):
//   t0 0xD8  spD8   t2 0xE0  spE0   t4 0xE8  spE8   t6 0xF0  spF0
//   t8 0xF8  est+1.0f          t10 0x100  2.0f    t12 0x108 1/sqrt + res
//   t14 0x110 clamp result     t16 0x118 (8.0f,0.0f)  t18 0x120 est+1.0f
//   t20 0x128 (8.0f,0.0f)      t22 0x130 est+1.0f     t24 0x138 est+1.0f
//   t26 0x140 cross+1.0f       t28 0x148 est+1.0f     t30 0x150 cross+1.0f
//   t32 0x158 est+1.0f
// 0x174 stmw r21  (11 callee-saved GPRs)   0x1A0 stfd f30   0x1A8 stfd f31
// 0x1B4 LR (above the frame)   frame = 0x1B0
// Values live across the section-2 calls (10, held in 11 slots because &ctx
// occupies both r21 and r30): &ctx, arg5, &lbl_802AEAE0, arg4, arg3, arg2,
// &sp8, arg0, &spD8, arg1.
// Callee-saved FPRs: f30 = 8.0f (whole function), f31 = 2.0f (sections 2-3,
// then RELOADED as 0.0f at 0x801FF7A0 for section 4).
//
// === RODATA CONSTANTS (all .rodata2, one `lis r9,-0x7fd5` page anchor) ===
//   lbl_802AEAE0 = {0.0f, 0.0f}  (the zero PAIR; r23/r10 hold its address)
//   lbl_802AEB14 = 0.0f     lbl_802AEB18 = 1.0f    lbl_802AEB1C = 2.0f
//   lbl_802AEB20 = 13.9f   lbl_802AEB24 = 8.0f
//
// === CALLEE SIGNATURES (ground truth from the DOL, all auto-asm) ===
//   void fn_8010794C(void *p)            1-arg void: mr r30,r3; zeroes
//                                        p+0xA8/p+0xAC; calls 0x800063b4, 0x80107A28
//   void fn_80107A80(void *p,s16 a,s16 b) 3-arg void: sth r5,0x56(r3); sth r4,0x54(r3)
//                                        => r4 lands at +0x54, r5 at +0x56
//   void fn_80107AB4(void *d,void *s,void *s2) 3-arg void: forwards r3/r4/r5 to
//                                        0x80107A8C (16B copy r4->r3+0) and
//                                        0x80107AA0 (16B copy r4->r3+0x10)
//   s32  fn_80107B20(void *p,s32 f1,void *f2) 3-arg -> s32 (0/1). Also writes
//                                        p+0xA8, which IS this function's
//                                        r1+0xC0 handle slot.
//   s32  fn_80108094(void *p,void *a,void *b,s32 c) 4-arg -> s32: forwards r4
//                                        and r5 VERBATIM to fn_80107AB4, then
//                                        fn_80107B20(p,r6,0) and returns it.
//                                        Both call sites here (0x801FF858,
//                                        0x801FF958) set only r3/r4/r6 — r5 is
//                                        never written, so the C passes an
//                                        UNINITIALISED 3rd argument (that is what
//                                        produces the untouched-middle-register
//                                        layout; writing it would add a setup insn).
//   void CObject_RemoveRefLink(s32 v, void *link)  2-arg (0x8009DFC0)
//
// === THE REPEATED "NORMALISE" PIPELINE (7 copies, all emittable) ===
// The pipeline squares the pair with a multiply, merges the square with the
// zero pair, accumulates the pair against itself plus the merge with a
// multiply-add, and reduces with a three-way sum. (The section 4 and else
// arms use the merge01 form with an (8.0f,0.0f) pair instead.) If the low
// lane of the sum is above 0.0f, the pipeline takes a reciprocal square root
// (with an extra reciprocal-estimate step in section 3), scales the pair by
// the estimate with a lane-0 multiply, builds an estimate pair whose high
// lane is set to 1.0f via a pair store plus a high-lane float store, scales
// a second pair by the scale factor with another lane-0 multiply, and
// finishes with a second scaling multiply of the pair by the estimate pair.
// cc1 operand mapping, PROBE-VERIFIED (one builtin per TU, op4 fields dumped):
//   ps_mul / ps_muls0 / ps_div   operands at bits 11-15 (A) and 21-25 (C)
//   ps_sub / ps_add / merge00/01/10/11   operands at bits 11-15 and 16-20
//   ps_madd   fD = f(11-15) * f(21-25) + f(16-20)
//   ps_sum0(a,b,c)  fD = {a.lo + c.lo, b.hi}   <-- sum0(x,x,x) DOUBLES lane 0
//   ps_rsqrte / ps_res / ps_abs / ps_neg      source at bits 16-20
// The lane-0 "length" is therefore 2*(x^2 + z^2) and lane 1 is y^2 — that is
// RETAIL semantics, not a decode slip: pipeline #3 (0x801FFA14..A38) shows the
// identical merge00/madd/sum0 triple over a different pair. Confirmed twice.
// The op4 opcode words themselves already match: e.g. want ps_madd 0x100B02FA,
// ps_sum0 0x10000014 and ps_rsqrte 0x10000034 are reproduced verbatim.
//
// === CONTROL FLOW (0x801FF57C..0x801FFC88) ===
//  S1 0x59C..0x62C  fr.v = arg0 - arg2; normalise fr.v[0..1] in place
//  S2 0x630..0x6A8  fn_8010794C(ctx); fn_80107A80(ctx,0x90,0);
//                   scale fr.v by the 2.0f pair's lane 0, add arg0, store to
//                   spD8/spE8/spF0, then fn_80107AB4(ctx, arg2, &spD8)
//  S3 0x6AC..0x770  if (fn_80107B20(ctx,1,0)) { normalise the ctx pair; clamp
//                   with 13.9f; arg0 = arg2 + arg0*s; mirror back to spD8/spE0 }
//  S4 0x774..0x794  if (arg4 == 0) { if (handle) { RemoveRefLink; handle=arg4; }
//                   return; }
//  S5 0x798..0x99C  seed spD8=(arg1[0],0.0f), spE0=(arg1[8],0.0f),
//                   sp118=(8.0f,0.0f); normalise in place; arg0 += spD8;
//                   res = fn_80108094(ctx, arg0, <uninit>, 1);
//                   if (res) arg0 -= (ctx+0x88) pair  else
//                   { negate arg1 row0, seed sp128=(8.0f,0.0f), normalise,
//                     arg0 += it, second fn_80108094, reflect if it returned }
//  S6 0x99C..0x9BC  if (arg5 == 0) { if (res) { RemoveRefLink; handle=arg5; }
//                   return; }
//  S7 0x9C0..0xC4C  if (res) { arg1 row2 = arg3-arg0 (+1.0f w); normalise;
//                   two cross-product/Gram-Schmidt blocks building arg1 row0
//                   then row1 (each with its own normalise); negate rows 0
//                   and 2; the four w's 0.0f/0.0f/0.0f/1.0f }
//  S8 0xFFC50..    if (handle) { RemoveRefLink; handle = 0; }
//  epilogue 0xFFC6C
//
// === VERIFICATION (2026-09-25) ===
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x801FF57C
//     -> DIFF 2.2%   (the sweep auto-adds -mps-float for __ps_t bodies)
//   compiled object: 1660B / 415 insns  vs  want 1804B / 451 insns
//   all 9 `bl` sites present, all 7 PS pipelines present.
//   No inline __asm__, no register pins, no store-order search: the body is a
//   straight semantic transcription of the decoded disassembly.
//
// === BLOCKERS (why it is parked; dominant first) ===
//  1. FRAME / SAVE-AREA SIZE — this alone destroys the word-by-word score,
//     because an 8-byte-different frame shifts EVERY r1 displacement.
//     The want saves eleven GPRs starting at r21 at offset 0x174, f30
//     at 0x1A0 and f31 at 0x1A8, keeps LR at 0x1B4, and uses a 0x1B0-byte
//     frame (f30 holds 8.0f, f31 holds 2.0f/0.0f). This draft instead
//     saves ten GPRs starting at r22 at 0x188, f29/f30/f31 at
//     0x1B0/0x1B8/0x1C0, keeps LR at 0x1CC, and uses a 0x1C8-byte frame.
//     Two independent causes:
//       (a) One extra callee-saved FPR. GCC 2.95 CSEs every load of
//           lbl_802AEB14 (0.0f) into a single f29 home shared by section 1's
//           `fcmpu` and section 4's live-across-call `z0`; retail keeps
//           section 1's 0.0f in a caller-saved f13 and re-loads it at
//           0x801FF7A0. Forcing retail's 2 homes needs the two 0.0 webs to be
//           distinct C objects (a dying one + a crossing-one), which GCC
//           2.95's constant propagation re-merges — this is the doc-15
//           constant-remat class, not a source-shape bug.
//       (b) One GPR short. Retail holds &ctx TWICE (r21 copy + r30 original,
//           see `addi r30,r1,0x18` / `mr r21,r30` at 0x801FF630/0x801FF63C and
//           the `mr r3,r21` vs `mr r3,r30` split across the call sites). The
//           draft has one &ctx web, so only 10 pseudos need callee-saved homes.
//  2. PS OPERAND COLOURING. Every pipeline's operand registers are permuted
//     (e.g. want `ps_mul f0,f0,f0` fed by `psq_l f0,8(r27)` reloading sp8; got
//     keeps the same value in f7 and never reloads). This is doc-06
//     M5.0o/M5.0r FPR colouring, made worse by (1) because the frame offset
//     differs so the reload cannot fold to the same displacement.
//  3. The 2.0f web. Retail stores only lane 0 of the pair at r1+0x100 and
//     reloads the PAIR from the stack at 0x801FF678 (`psq_l f13,256(r1)`) with
//     r1+0x104 left uninitialised; GOT hoists the whole pair into f30 across
//     fn_80107AB4 + fn_80107B20 (3 psq_st f30 / 4 psq_l f30).
//  4. Not tried this round (candidates for the next one, in order of expected
//     value): hard-register pins for the six parameter homes and the four
//     pointers (recipes §6o-98 / §6y-124 / §6p-111 — NOT used here because
//     this round deliberately stayed a pure semantic rebuild); declaration-order
//     steering of the six __ps_t webs (§6ae-7, §6ay-184); and a
//     frame-template struct whose tail padding is sized so the locals region
//     lands on 0x174 (§6q-86, §6ap-5). Note `volatile double _dummy` is NOT
//     part of the fix here: want's first stfd is frame-0x10, not frame-8, so
//     the issue-01 +8 FPR quirk is not in play (tools/test_wip_drafts.py's
//     want_fpr_frame() returns None for this function, correctly).
//  5. The four trailing `w` stores (0x801FFC38..0x801FFC4C, emitted
//     0x3C,0x2C,0x0C,0x1C) will need the store-run rotation lever
//     (recipes 24/64/198/206) once the frame matches; not attempted, since a
//     permutation search is out of scope for this round.
#include "structs.h"

extern __ps_t lbl_802AEAE0;
extern f32 lbl_802AEB14;
extern f32 lbl_802AEB18;
extern f32 lbl_802AEB1C;
extern f32 lbl_802AEB20;
extern f32 lbl_802AEB24;
void fn_8010794C(void *);
void fn_80107A80(void *, s32, s32);
void fn_80107AB4(void *, void *, void *);
s32 fn_80107B20(void *, s32, void *);
s32 fn_80108094(void *, void *, s32, s32);
void CObject_RemoveRefLink(s32, void *);

typedef union { __ps_t p; f32 w[2]; } SU;

typedef struct {
    char pad[0x80];
    f32 f80;
    f32 f88[8];
    s32 hA8;
} Ctx;

typedef struct {
    f32 v[4];
    Ctx ctx;
    char gap[0x14];
    f32 t[34];
    f32 pad[5];
} FR;

void fn_801FF57C(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4, s32 arg5) {
    FR fr;
    void *ctx;
    void *pD8;
    __ps_t z;
    __ps_t t, m, a, s, e, v, w;
    SU su, eu;
    s32 res;
    s32 gap;
    f32 sc;
    f32 vv;
    f32 two;
    f32 eight;
    f32 z0;
    f32 *pv;

    ctx = (void *)&fr.ctx;
    pD8 = (void *)&fr.t[0];
    z = lbl_802AEAE0;
    pv = &fr.v[0];
    eight = lbl_802AEB24;

    /* S1: delta = arg0 - arg2, then normalise its first pair in place. */
    *(__ps_t *)pv = __builtin_ps_sub(*(__ps_t *)arg0, *(__ps_t *)arg2);
    *(__ps_t *)&pv[2] = __builtin_ps_sub(*(__ps_t *)&arg0[2],
                                         *(__ps_t *)&arg2[2]);
    t = *(__ps_t *)pv;
    m = __builtin_ps_merge00(__builtin_ps_mul(t, t), z);
    su.p = __builtin_ps_sum0(__builtin_ps_madd(t, t, m), t, t);
    if (su.w[0] > lbl_802AEB14) {
        e = __builtin_ps_rsqrte(su.p);
        *(__ps_t *)&fr.t[8] = e;
        *(__ps_t *)pv = __builtin_ps_muls0(t, e);
        fr.t[11] = lbl_802AEB18;
        *(__ps_t *)pv = __builtin_ps_mul(*(__ps_t *)pv, *(__ps_t *)&fr.t[8]);
    }

    /* S2: build a descriptor context and seed it from arg0/arg2. */
    fn_8010794C(ctx);
    fn_80107A80(ctx, 0x90, 0);
    two = lbl_802AEB1C;
    fr.t[10] = two;
    *(__ps_t *)&fr.t[6] = __builtin_ps_muls0(*(__ps_t *)&fr.v[2],
                                             *(__ps_t *)&fr.t[10]);
    *(__ps_t *)&fr.t[4] = __builtin_ps_muls0(*(__ps_t *)&fr.v[0],
                                             *(__ps_t *)&fr.t[10]);
    *(__ps_t *)pD8 = __builtin_ps_add(*(__ps_t *)arg0, *(__ps_t *)&fr.t[4]);
    *(__ps_t *)&fr.t[2] = __builtin_ps_add(*(__ps_t *)&arg0[2],
                                           *(__ps_t *)&fr.t[6]);
    fn_80107AB4(ctx, arg2, pD8);

    /* S3: project onto the freshly built context. */
    if (fn_80107B20(ctx, 1, 0) != 0) {
        w = __builtin_ps_sub(*(__ps_t *)&fr.t[12], *(__ps_t *)&fr.t[8]);
        v = __builtin_ps_sub(*(__ps_t *)&fr.t[10], *(__ps_t *)&fr.t[6]);
        *(__ps_t *)&fr.t[2] = w;
        *(__ps_t *)pD8 = v;
        m = __builtin_ps_merge00(__builtin_ps_mul(w, w), z);
        su.p = __builtin_ps_sum0(__builtin_ps_madd(v, v, m), v, v);
        sc = fr.ctx.f80;
        eu.p = __builtin_ps_res(__builtin_ps_rsqrte(su.p));
        *(__ps_t *)&fr.t[12] = eu.p;
        vv = eu.w[0];
        if (vv * sc < lbl_802AEB20) {
            sc = lbl_802AEB20 / vv;
        }
        fr.t[14] = sc * vv - two;
        w = __builtin_ps_muls0(*(__ps_t *)&fr.v[0], *(__ps_t *)&fr.t[14]);
        v = __builtin_ps_muls0(*(__ps_t *)&fr.v[2], *(__ps_t *)&fr.t[14]);
        *(__ps_t *)&fr.t[6] = w;
        *(__ps_t *)&fr.t[4] = v;
        *(__ps_t *)arg0 = __builtin_ps_add(*(__ps_t *)arg2, v);
        *(__ps_t *)&arg0[2] = __builtin_ps_add(*(__ps_t *)&arg2[2], w);
        *(__ps_t *)pD8 = *(__ps_t *)arg0;
        *(__ps_t *)&fr.t[2] = *(__ps_t *)&arg0[2];
    }

    /* S4: arg4 == 0 means "just release the handle and leave". */
    if (arg4 == 0) {
        if (*(s32 *)&fr.ctx.hA8 != 0) {
            CObject_RemoveRefLink(*(s32 *)&fr.ctx.hA8, (void *)&fr.ctx.hA8);
            *(s32 *)&fr.ctx.hA8 = arg4;
        }
        return;
    }

    /* S5a: seed the working pairs, then normalise arg1 row0. */
    z0 = lbl_802AEB14;
    fr.t[2] = arg1[0x08];
    fr.t[3] = z0;
    fr.t[16] = eight;
    fr.t[17] = z0;
    fr.t[0] = arg1[0x00];
    fr.t[1] = z0;
    t = *(__ps_t *)&fr.t[16];
    w = *(__ps_t *)&fr.t[2];
    m = __builtin_ps_merge01(__builtin_ps_mul(w, w), t);
    su.p = __builtin_ps_sum0(__builtin_ps_madd(*(__ps_t *)pD8, *(__ps_t *)pD8, m),
                             *(__ps_t *)pD8, *(__ps_t *)pD8);
    if (su.w[0] > z0) {
        e = __builtin_ps_rsqrte(su.p);
        v = __builtin_ps_muls0(e, t);
        *(__ps_t *)&fr.t[18] = v;
        fr.t[19] = lbl_802AEB18;
        *(__ps_t *)pD8 = __builtin_ps_muls0(*(__ps_t *)pD8, v);
        *(__ps_t *)&fr.t[2] = __builtin_ps_mul(w, *(__ps_t *)&fr.t[18]);
    }
    *(__ps_t *)pD8 = __builtin_ps_add(*(__ps_t *)pD8, *(__ps_t *)arg0);
    *(__ps_t *)&fr.t[2] = __builtin_ps_add(*(__ps_t *)&fr.t[2],
                                           *(__ps_t *)&arg0[2]);
    res = fn_80108094(ctx, arg0, gap, 1);
    if (res != 0) {
        /* reflected straight off the context normal */
        w = *(__ps_t *)&fr.t[2];
        t = *(__ps_t *)pD8;
        m = __builtin_ps_sub(w, *(__ps_t *)&fr.ctx.f88[0]);
        a = *(__ps_t *)arg0;
        t = __builtin_ps_sub(t, *(__ps_t *)&fr.ctx.f88[2]);
        *(__ps_t *)pD8 = t;
        a = __builtin_ps_sub(a, m);
        *(__ps_t *)arg0 = a;
        *(__ps_t *)&arg0[2] = __builtin_ps_sub(*(__ps_t *)&arg0[2], m);
        *(__ps_t *)&fr.t[2] = m;
    } else {
        /* S5b: flip the direction, re-seed, normalise, retry once. */
        fr.t[21] = z0;
        fr.t[20] = eight;
        fr.t[4] = -arg1[0x00];
        fr.t[5] = z0;
        fr.t[6] = -arg1[0x08];
        fr.t[7] = z0;
        t = *(__ps_t *)&fr.t[20];
        w = *(__ps_t *)&fr.t[6];
        m = __builtin_ps_merge01(__builtin_ps_mul(w, w), t);
        su.p = __builtin_ps_sum0(__builtin_ps_madd(*(__ps_t *)&fr.t[4],
                                                   *(__ps_t *)&fr.t[4], m),
                                 *(__ps_t *)&fr.t[4], *(__ps_t *)&fr.t[4]);
        if (su.w[0] > z0) {
            e = __builtin_ps_rsqrte(su.p);
            v = __builtin_ps_muls0(e, t);
            *(__ps_t *)&fr.t[22] = v;
            fr.t[23] = lbl_802AEB18;
            *(__ps_t *)&fr.t[4] = __builtin_ps_muls0(*(__ps_t *)&fr.t[4], v);
            *(__ps_t *)&fr.t[6] = __builtin_ps_mul(w, *(__ps_t *)&fr.t[22]);
        }
        *(__ps_t *)&fr.t[4] = __builtin_ps_add(*(__ps_t *)&fr.t[4],
                                               *(__ps_t *)arg0);
        *(__ps_t *)&fr.t[6] = __builtin_ps_add(*(__ps_t *)&fr.t[6],
                                               *(__ps_t *)&arg0[2]);
        res = fn_80108094(ctx, arg0, gap, 1);
        if (res != 0) {
            w = *(__ps_t *)&fr.t[6];
            t = *(__ps_t *)&fr.t[4];
            m = __builtin_ps_sub(w, *(__ps_t *)&fr.ctx.f88[0]);
            a = *(__ps_t *)arg0;
            t = __builtin_ps_sub(t, *(__ps_t *)&fr.ctx.f88[2]);
            *(__ps_t *)&fr.t[4] = t;
            a = __builtin_ps_sub(a, m);
            *(__ps_t *)arg0 = a;
            *(__ps_t *)&arg0[2] = __builtin_ps_sub(*(__ps_t *)&arg0[2], m);
            *(__ps_t *)&fr.t[6] = m;
        }
    }

    /* S6: arg5 == 0 mirrors the arg4 early-out, but gated on `res`. */
    if (arg5 == 0) {
        if (res != 0) {
            CObject_RemoveRefLink(*(s32 *)&fr.ctx.hA8, (void *)&fr.ctx.hA8);
            *(s32 *)&fr.ctx.hA8 = arg5;
        }
        return;
    }

    /* S7: rebuild arg1's rows as an orthonormal frame around arg3-arg0. */
    if (res != 0) {
        arg1[0x20] = arg3[0] - arg0[0];
        arg1[0x24] = arg3[1] - arg0[1];
        arg1[0x28] = arg3[2] - arg0[2];
        arg1[0x2C] = lbl_802AEB18;
        w = *(__ps_t *)&arg1[0x28];
        m = __builtin_ps_merge00(__builtin_ps_mul(w, w), z);
        su.p = __builtin_ps_sum0(__builtin_ps_madd(*(__ps_t *)&arg1[0x20],
                                                   *(__ps_t *)&arg1[0x20], m),
                                 *(__ps_t *)&arg1[0x20], *(__ps_t *)&arg1[0x20]);
        if (su.w[0] > lbl_802AEB14) {
            e = __builtin_ps_rsqrte(su.p);
            *(__ps_t *)&fr.t[24] = e;
            fr.t[25] = lbl_802AEB18;
            *(__ps_t *)&arg1[0x20] = __builtin_ps_muls0(*(__ps_t *)&arg1[0x20], e);
            *(__ps_t *)&arg1[0x28] = __builtin_ps_mul(w, *(__ps_t *)&fr.t[24]);
        }
        v = *(__ps_t *)&arg1[0x10];
        w = *(__ps_t *)&arg1[0x18];
        t = *(__ps_t *)&arg1[0x20];
        m = *(__ps_t *)&arg1[0x28];
        a = __builtin_ps_mul(__builtin_ps_merge10(v, w), t);
        s = __builtin_ps_mul(v, __builtin_ps_merge10(t, m));
        t = __builtin_ps_merge00(w, v);
        m = __builtin_ps_merge00(t, m);
        s = __builtin_ps_sub(s, a);
        a = __builtin_ps_mul(t, m);
        v = __builtin_ps_merge00(s, s);
        *(__ps_t *)&fr.t[26] = v;
        m = __builtin_ps_merge10(a, a);
        fr.t[27] = lbl_802AEB18;
        a = __builtin_ps_sub(a, m);
        m = __builtin_ps_merge10(s, a);
        *(__ps_t *)&arg1[0x00] = m;
        w = v;
        *(__ps_t *)&arg1[0x08] = w;
        e = __builtin_ps_mul(w, w);
        *(__ps_t *)&fr.t[4] = m;
        *(__ps_t *)&fr.t[6] = w;
        e = __builtin_ps_merge00(e, z);
        su.p = __builtin_ps_sum0(__builtin_ps_madd(m, m, e), m, m);
        if (su.w[0] > lbl_802AEB14) {
            e = __builtin_ps_rsqrte(su.p);
            *(__ps_t *)&fr.t[28] = e;
            fr.t[29] = lbl_802AEB18;
            *(__ps_t *)&arg1[0x00] = __builtin_ps_muls0(m, e);
            *(__ps_t *)&arg1[0x08] = __builtin_ps_mul(w, *(__ps_t *)&fr.t[28]);
        }
        v = *(__ps_t *)&arg1[0x20];
        w = *(__ps_t *)&arg1[0x28];
        t = *(__ps_t *)&arg1[0x00];
        m = *(__ps_t *)&arg1[0x08];
        a = __builtin_ps_mul(__builtin_ps_merge10(v, w), t);
        s = __builtin_ps_mul(v, __builtin_ps_merge10(t, m));
        t = __builtin_ps_merge00(w, v);
        m = __builtin_ps_merge00(t, m);
        s = __builtin_ps_sub(s, a);
        a = __builtin_ps_mul(t, m);
        v = __builtin_ps_merge00(s, s);
        *(__ps_t *)&fr.t[30] = v;
        m = __builtin_ps_merge10(a, a);
        fr.t[31] = lbl_802AEB18;
        a = __builtin_ps_sub(a, m);
        m = __builtin_ps_merge10(s, a);
        *(__ps_t *)&arg1[0x10] = m;
        w = v;
        *(__ps_t *)&arg1[0x18] = w;
        e = __builtin_ps_mul(w, w);
        *(__ps_t *)&fr.t[4] = m;
        *(__ps_t *)&fr.t[6] = w;
        e = __builtin_ps_merge00(e, z);
        su.p = __builtin_ps_sum0(__builtin_ps_madd(m, m, e), m, m);
        if (su.w[0] > lbl_802AEB14) {
            e = __builtin_ps_rsqrte(su.p);
            *(__ps_t *)&fr.t[32] = e;
            fr.t[33] = lbl_802AEB18;
            *(__ps_t *)&arg1[0x10] = __builtin_ps_muls0(m, e);
            *(__ps_t *)&arg1[0x18] = __builtin_ps_mul(w, *(__ps_t *)&fr.t[32]);
        }
        *(__ps_t *)&arg1[0x00] = __builtin_ps_neg(*(__ps_t *)&arg1[0x00]);
        *(__ps_t *)&arg1[0x08] = __builtin_ps_neg(*(__ps_t *)&arg1[0x08]);
        *(__ps_t *)&arg1[0x20] = __builtin_ps_neg(*(__ps_t *)&arg1[0x20]);
        *(__ps_t *)&arg1[0x28] = __builtin_ps_neg(*(__ps_t *)&arg1[0x28]);
        arg1[0x0C] = lbl_802AEB14;
        arg1[0x1C] = lbl_802AEB14;
        arg1[0x2C] = lbl_802AEB14;
        arg1[0x3C] = lbl_802AEB18;
    }

    /* S8: shared tail — release the handle unless arg5 already cleared it. */
    if (*(s32 *)&fr.ctx.hA8 != 0) {
        CObject_RemoveRefLink(*(s32 *)&fr.ctx.hA8, (void *)&fr.ctx.hA8);
        *(s32 *)&fr.ctx.hA8 = 0;
    }
}
