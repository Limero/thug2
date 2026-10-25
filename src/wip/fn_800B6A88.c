// WIP DRAFT (non-matching) — hand reconstruction from the DOL disassembly
// family=m2c range=0x800B6A88-0x800B6B58 size=208B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// VERDICT: DIFF, 36.5% masked, SIZE-EXACT 208B (.text 0xD0).
//
// *** SEMANTIC FIX IN THIS REVISION (see "ps_neg" below) — the score went
// *** 38.46% -> 36.5% and that is CORRECT: the previous 38.46% body computed
// *** a[0..1] = +arg1[0..1] and left retail's `ps_neg` a dead no-op on the
// *** 0.0f constant.  It could never be a true match.  Do not "restore" it.
//
// ---------------------------------------------------------------------------
// IDENTIFIED SEMANTICS (this is a quaternion-vector rotation; the name is safe
// to carry into symbols.txt): rotates the 3-vector arg2 by the quaternion arg1
// and writes the result quat's vector part to *arg0.
//
//   lbl_8029898C = 0.0f , lbl_80298990 = 1.0f  (verified in the DOL .rodata2)
//   q  = arg1 (r4)                       b = (arg2->x, arg2->y, arg2->z, 1.0f)
//   t  = (q.x, q.y, q.z, q.w)             a = (-q.x, -q.y, -q.z, q.w)  == conj(q)
//   a is FIRST dead-initialised to the identity quat (0,0,0,1) — all four
//     stfs survive in retail because DSE cannot prove the later values differ
//     (a[0..1] come from an unsizable psq_st; a[2] gets -q.z, a[3] gets q.w).
//   t = fn_800B6B58(t, b)   /* t = t * (v,1)   */     b   = r1+0x18
//   t = fn_800B6B58(t, a)   /* t = t * conj(q) */      a   = r1+0x08
//   *arg0 = t                                        t   = r1+0x28
//   callee fn_800B6B58(out,in) = quaternion multiply: it copies *out to a
//   local, mixes in *in with paired-single ops and writes out[0..2].
// ---------------------------------------------------------------------------
// WHY a[0..1] IS NEGATED (this was the big discovery of this pass; the old
// header called the instruction at 0x800B6AEC a "dead ps_mr"):
//   0x10000050 is NOT ps_mr.  Decoded with ps_diff's A-form field layout it is
//   opcode 4, frD=f0, frA=f0, frB=f0, frC=f1, xo5=8  =>  XO10 = (1<<5)|8 = 40
//   = ps_neg (same family as ps_mr/abs/nabs = 72/40/264/136).  Retail:
//       At 0x800B6AE0 retail pair-loads f0 from 0(r9) with r9 holding arg1,
//       at 0x800B6AEC it negates that pair, and at 0x800B6AFC it pair-stores
//       f0 to 8(r1), so the a slots 0 and 1 provably hold the negated x and y
//       of the input quaternion.
//   and nothing else writes a[0] or a[1], so a[0..1] is provably the negated
//   pair.  The old body left the ps_neg dead, i.e. it computed the conjugate's
//   x/y with the WRONG sign, which makes t = q*(v,1)*q (not *q^-1) — nonsense.
//   `*(__ps_t *)pa = __builtin_ps_neg(src[0]);` emits the right opcode
//   (ngccc 3.9.3 gives 0x11A0..50, A-form xo5=8/C=1, operands in different
//   FPRs but the same instruction).
// ---------------------------------------------------------------------------
// RETAIL REGISTER MAP (target homes; the whole residual is a schedule/homing
// problem, not a semantic one) — worth keeping for any future attempt:
//   FPR: 0.0f -> f0   arg2->z -> f10   1.0f -> f11   arg2->x -> f12
//        arg2->y -> f13 (then reused for q->z);  f0 reused for the a-pair and
//        for q->w;  f12 reused for the t pair loads.  The FPR map implies the
//        original's b statements were ordered  y, x, w(1.0), z  — GCC 2.95
//        hands out float pseudos DESCENDING (first-created -> f13).
//   GPR: &a -> r30   arg0 -> r29   &t -> r28   &b -> r11 (scratch, dies before
//        the first call)   arg1 -> r9 (scratch).  r31 is never referenced but
//        the prologue saves it (`stmw r28,0x38`), so the file-scope dead
//        register var below is load-bearing (without it: 204B, `stmw r29`, 13.5%).
// ---------------------------------------------------------------------------
// PARKED residual, 36.5% masked, precise (index: want | got):
//   (a) &a is born in a SCRATCH reg and promoted (`addi r10,r1,8` @7 +
//       `mr r28,r10` @13); retail births it straight into a callee-saved reg
//       (`addi r30,r1,8` @9).  This also flips the r28<->r30 role: got r28=&a,
//       r30=&t; want r30=&a, r28=&t.  Consequence: retail's t pair stores use
//       r1 displacements (`psq_st f12,40(r1)` @33/35) while got uses the &t
//       register (`psq_st f12,0x28(r1)` @36) and the final out stores come out
//       off r28 instead of r29 @45/46.  DEAD: hard-reg `register s32 __asm__`
//       pins on &a/&t (p2/p5) — the pin forces an extra `mr r10,r30` copy,
//       steals r26/r27, and grows the frame to 0x50/`stmw r26`; one single &a
//       web for every access (s5) makes GCC emit `mr r30,r1` + `stfsu`; a
//       `char *`-hop / type-change barrier (the §6ap-7 idiom) is the wrong
//       direction here.  This is the same r28<->r30 role rotation the previous
//       pass reported after 120 decl-order permutations.
//   (b) arg2->z's load is retail's FIRST float op (`lfs f10,8(r5)` @5) but
//       lands @25 in every form tried, and retail's two rodata page anchors
//       are interleaved (lis @4, lfs z @5, lfs 0.0 @6, lis @7, lfs 1.0 @8)
//       while ngccc always emits them back-to-back @4/@5.
//   (c) the four b stores are retail b.x,b.z,b.y,b.w (@23,24,26,28) — source
//       order is preserved by ngccc, so the source really is x,z,y,w, yet the
//       FPR map says y,x,w,z.  The two constraints are mutually exclusive under
//       every ngccc scheduling flag; retail's store order is not reachable
//       together with retail's FPR homes.  (Tried all 24 b field orders: best
//       masked score is b = y,x,w,z at 36.5%, b = x,z,y,w at 32.7%; every
//       other order is 30.8-32.7% or 204B.)
//   (d) the a-pair `psq_l f0,0(r9)` is @22 in retail and @24 in got, i.e. after
//       the whole b-store group instead of before it.
//   FLAGS: `tools/flag_sweep.py` over all 21 single flags + 3 pairs finds NO
//   improvement (bit-identical or strictly worse) — consistent with the
//   previous pass.  Do not re-run it.
//   Also tried and dead: fr10/fr11/fr12/fr13 register pins on b's four values
//   (p1 — pins hold, but the 0.0f constant then lands in f9 and the schedule
//   gets worse, 11.5%); scalar `a.x = -arg1->x; a.y = -arg1->y;` instead of
//   the ps_neg (s3 — ngccc does NOT fuse two adjacent scalar negations into
//   psq_l/ps_neg/psq_st; +4 words, 224B); a named `__ps_t` temp (s2 — cc1
//   compile failure); an `sn_ps` (mode(PS)) temp (s6 — same 32.7% as the
//   inline form); swapping the t/out pair-copy order to pair0-first (s7 —
//   34.6%, so retail really does copy t[1] before t[0]); b before a instead of
//   after (25.0%); the `V4 a = {0,0,0,1}` aggregate initialiser (V1 — moves a
//   to slot 0x18, 6.8%); all four identity stores through one `volatile V4 *`
//   (p6 — 30.8%, GCC serialises them and spills r1).
// ---------------------------------------------------------------------------
#include "types.h"

extern f32 lbl_8029898C;
extern f32 lbl_80298990;

typedef struct { f32 x, y, z, w; } V4;

register s32 unused_r31 __asm__("r31");

void fn_800B6B58(V4 *out, V4 *in);

void *fn_800B6A88(void *arg0, V4 *arg1, V4 *arg2) {
    V4 a;
    V4 b;
    V4 t;
    __ps_t *src = (__ps_t *)arg1;
    volatile V4 *va = &a;
    volatile V4 *vb = &b;
    V4 *pa = &a;
    V4 *pb = &b;
    V4 *pt = &t;

    /* dead identity-quaternion default construction for `a` (see header) */
    a.x = lbl_8029898C;
    va->w = lbl_80298990;
    a.z = lbl_8029898C;
    va->y = lbl_8029898C;

    /* b = (arg2->x, arg2->y, arg2->z, 1.0f) */
    b.y = arg2->y;
    b.x = arg2->x;
    vb->w = lbl_80298990;
    b.z = arg2->z;

    /* a = conj(q) */
    *(__ps_t *)pa = __builtin_ps_neg(src[0]);
    a.z = -arg1->z;
    a.w = arg1->w;

    /* t = q */
    ((__ps_t *)pt)[1] = src[1];
    *(__ps_t *)pt = src[0];

    fn_800B6B58(pt, pb);
    fn_800B6B58(pt, pa);

    ((__ps_t *)arg0)[1] = ((__ps_t *)pt)[1];
    ((__ps_t *)arg0)[0] = *(__ps_t *)pt;
    return arg0;
}
