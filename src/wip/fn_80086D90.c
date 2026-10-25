// WIP DRAFT (non-matching) — hand reconstruction of fn_80086D90.
//
// family=m2c range=0x80086D90-0x80087010 size=640B
// INERT: not registered in splits.txt/configure.py — never compiled by the
// real build, not counted in objdiff progress. activate via tools/wip.py.
//
// extra_cflags: -mps-float   (REQUIRED: the body uses __ps_t pair arithmetic;
//   gen_leaves.draft_flags also auto-adds it, but keep the marker so a future
//   promote wires the right per-object cflags via add_gen_leaves.py)
//
// === PARKED (2026-10-01) ===
// SCORE: tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80086D90
//   -> DIFF 6.37%   (object 628B / 157 words vs want 640B / 160 words)
// Previous state of this draft was DIFF 3.8% at 580B — this pass is +48B and
// +2.6 points, and for the first time the object is only 3 words short (was
// 15) with the frame, the loop head form and the whole post-call tail
// instruction-for-instruction identical to want (modulo register numbers).
//
// WHAT IS NOW EXACT (verified instruction by instruction):
//  * frame: stwu -0xa8 / stfd f30,0x98 / stfd f31,0xa0 / stmw r20,0x68 /
//    stw r0,0xac ... lmw r20,0x68 / lfd f30,0x98 / lfd f31,0xa0 / addi 0xa8.
//    12 callee-saved GPRs r20..r31, EXACTLY want's set.
//  * locals: p0@0x08 p1@0x18 p2@0x28 hole@0x38 out@0x48 (the pad38 hole is
//    load-bearing, see AGENTS.md §6g-93).
//  * loop head form: the empty 4-iteration countdown loop makes ngccc emit
//    `li r0,4 / mtctr / lwz bases / slwi i*16 / slwi i*64 / bdnz` INSIDE the
//    loop head instead of byte-offset induction variables (`addi rX,rX,0x10`).
//    This is the single biggest lever found this pass: it is what turns
//    580B/3.8% into 628B/6.4%.  With it, `i*16` and `i*64` survive as
//    separate values (r31/r26) and the `lfsx f12,r31,r11` / `lfs 4(r9)` pair
//    for `bases[i*4+k]` is reproduced.
//  * the three `psq_l/psq_st` dead copies of `out` back into p0, p1 and p2
//    (2 x `psq_l 72(r1)` / `psq_st 8/16/24(r1)` + `psq_l 80(r1)` /
//    `psq_st 16/24/32/40/48(r1)`) — want keeps the p0 and p1 ones even though
//    they are dead; the draft previously only emitted the p2 one.
//  * the whole post-fn_8006BF04 tail is now op-for-op want: reload
//    `obj->bases`, `add r11,r31,r9`, p0[0]+=B[0], p0[2]+=B[2], the DEAD
//    `psq_lx f13,r31+r9` B[0] load, `p0[0]=p1[0]`, `p1[2]=p1[2]+p1[0]+B[2]`,
//    p2[0]+=B[0], p2[2]+=B[2], then the 12 `lfs`+`stfs` into att[i].s[k].
//
// ---------------------------------------------------------------------------
// WHAT THE FUNCTION ACTUALLY DOES (verified instruction by instruction against
// the DOL, 0x80086D90..0x80087010, 160 instructions)
// ---------------------------------------------------------------------------
// Skeleton / bone-attachment update, one iteration per bone.
//
//   obj+0x00  vec4 array, stride 0x10   "bind" positions
//   obj+0x0C  0x40-stride array of 3x3 matrices (12 floats at +0x00..+0x2B)
//   obj+0x20  s16/u16 bone count  (read with lhz, compared signed -> `u16` +
//             an `s32` compare; a `s16` field would emit lha and never match)
//   obj+0x34  array of 0x48-stride records, each three 0x18 sub-vectors at
//             +0x00 / +0x18 / +0x30  (the three attachment points)
//
//   for (i = 0; i < count; i++) {
//       p[k] = att[i].s[k] - bind[i]      (xyz only, w = lbl_802965D4 = 1.0f)
//       fn_8008757C(out, &mats[i], p0);  p0[0]=out[0]; p0[2]=out[2];  /* dead */
//       fn_8008757C(out, &mats[i], p1);  p1[0]=out[0]; p1[2]=out[2];  /* dead */
//       fn_8008757C(out, &mats[i], p2);  p2[0]=out[0]; p2[2]=out[2];
//       fn_8006BF04(obj, i, t);            /* side effects on obj */
//       p0[0] += bind[i][0];              /* dead: overwritten by p1[0]     */
//       p0[2] += bind[i][2];
//       p0[0]  = p1[0];                   /* cross-vector copy, want-only   */
//       p1[2] += p1[0] + bind[i][2];
//       p2[0] += bind[i][0];
//       p2[2] += bind[i][2];
//       att[i].s[k] = p[k]                (w re-stored as 1.0f)
//   }
//
// The three odd tail statements (the dead p0[0] add, the cross-vector
// `p0[0]=p1[0]`, and `p1[2] += p1[0] + B[2]` instead of `p1[0] += B[0]` and
// `p1[2] += B[2]`) are read straight off the DOL: the liveness of each is
// forced by the `lfs f9,8(r1)` / `lfs f10,0xc(r1)` pair that feeds
// `stfs f9,0(r30); stfs f10,4(r30)` (= att[0][0], att[0][1]) and by
// `psq_l f0,8(r27)` -> `stfs f0,8(r30)` (= att[0][2] = p0[2]+B[2]).
// NOTE: `p0[0]` is stored at 0x8(r1) and `p0[2]` at 8(r27) = 0x10(r1), so the
// want's `psq_st f0,8(r1)` at 0x80086F68 really is p0[0], not p1[0].
//
//   fn_8008757C(out, mat, v)  — 3-arg, VOID return (prologue saves no
//   arg regs, last insn is a store, never sets r3). 3x3 transform of v[0..2]
//   with v[3] passed straight through.
//   fn_8006BF04(obj, i, t) — void; prologue reads r3 (obj), r4 (i), f1.
//
// ---------------------------------------------------------------------------
// WHY IT IS STILL PARKED — three residual walls, all measured
// ---------------------------------------------------------------------------
// 1) LENGTH: 157 words vs 160. The 3 missing words are all in the loop head:
//      a) want computes the three attachment pointers as THREE INDEPENDENT
//         `A + i*0x48 + {0,0x18,0x30}` addresses, materialising the addends
//         into temps first:
//             mulli r9,r24,0x48 / addi r0,r9,0x30 / add r30,r20,r9
//             addi r9,r9,0x18 / add r28,r20,r0 / add r29,r20,r9
//         i.e. 5 instructions. Every C spelling tried (struct member access,
//         `&A[i]` record pointer, explicit `(char*)A + i*72 + k*24` with the
//         three written in want's addend order) makes ngccc CSE ONE
//         `A + i*0x48` pseudo and emit 3 (`add r30` + two `addi`), because
//         the constant ends up OUTSIDE the `plus` and the reload folds it
//         into the already-materialised pointer.  This is an RTL CSE shape,
//         not reachable from C.  Worth 2 words.
//      b) want hoists the loop increment to the head as
//         `addi r21,r24,1` + a late `mr r24,r21` copy-back (2 words). The
//         `register s32 i __asm__("r24")` pin that buys the exact frame
//         forces an in-place `addi r24,r24,1` (1 word) instead. Unpinned the
//         hoist appears but the frame goes back to 0xb0 (13 saved regs).
//         Pinned vs unpinned measured: 6.37% @628B/0xa8 vs 3.80% @632B/0xb0 —
//         pinned wins, so the pin stays.
// 2) REGISTER COLOURING. The 12 saved registers are the right COUNT and the
//    right ones in r20..r31, but six are permuted vs want:
//        want  r20=A r21=i+1 r22=&p1 r23=&p2 r24=i r25=i*64 r26=obj
//              r27=&p0 r28=&s2 r29=&s1 r30=&s0 r31=i*16
//        got   r20=A r21=&p2 r22=out r23=  -  r24=i r25=  -  r26=i*64
//              r27=obj r28=&s2 r29=&s1 r30=&s0 r31=i*16
//    want rematerialises `out` (`addi r3,r1,0x48` at each of the 3 calls) and
//    `&B[i]` and hoists `&p0`; got hoists `out` and `i*0x48` and rematerialises
//    `&p0` (`addi r5,r1,8` in the loop). Net one extra live value, so the
//    allocator fills r19..r31 instead of r20..r31. `&A[i]` record-pointer
//    form, `volatile f32 out[4]`, reordering the s0 store group, and a
//    `f32 p[3][4]` 2-D array (which does hoist &p0, but pushes the frame back
//    to 0xb0, 159 words, 1.26%) were all measured and none frees both.
// 3) The pinned variant also changes the countdown loop's extent: want's
//    `bdnz 0x80086E08` targets ITSELF (empty body), got's `bdnz` at
//    0x80086DF0 branches back to 0x80086DCC, i.e. it swallows the three
//    hoisted `addi rX,r1,N` of out/&p1/&p2 and re-executes them 4x
//    (idempotent, and REL14-masked so it costs nothing in the score, but it
//    is a real difference — the unpinned body gets the self-targeting bdnz).
//
// NOT TRIED (the next thing to try):
//   * forcing the `addi r0,r9,0x30` / `addi r9,r9,0x18` addend shape via a
//     zero-code `"+r"` barrier between the three address computations, or by
//     spelling the offsets through three separate `volatile` pointer locals
//     so the CSE cannot fold them (`__asm__("" : "+r"(a0), "+r"(a1), "+r"(a2))`).
//   * an RTL-level check with `cc1 -dr` to confirm the post-reload RTL for
//     the tail already matches want (it looks like it does — every psq/ps_add
//     pair is in want's order); the blocker is above the reload.
//
// No inline asm (zero emitted instructions: only two `register ... __asm__`
// attributes and volatile loads), no extra object sections, no cast roulette.

#include "types.h"

extern f32 lbl_802965D4;                        /* .rodata2 float 1.0f */
extern void fn_8008757C(void *out, f32 *mat, f32 *v);
extern void fn_8006BF04(void *obj, s32 i, f32 t);

/* obj+0x34 record: three 6-float sub-vectors; only the first 4 of each are
   touched by the game. */
typedef struct { f32 v[6]; } Sub;              /* 0x18 */
typedef struct { Sub s[3]; } Att;              /* 0x48 */

typedef struct {
    f32 *bases;                                 /* +0x00  vec4[]  stride 0x10 */
    s32   unk04;
    s32   unk08;
    f32  *mats;                                 /* +0x0C  3x3[]  stride 0x40 */
    s32   unk10;
    s32   unk14;
    s32   unk18;
    s32   unk1C;
    u16   count;                                /* +0x20  lhz, signed cmp */
    char  pad22[0x12];
    Att  *atts;                                 /* +0x34  stride 0x48 */
} Obj;

void fn_80086D90(Obj *obj, f32 t) {
    f32 p0[4];
    f32 p1[4];
    f32 p2[4];
    f32 pad38[4];   /* want has an unused 0x10 hole here; keeps `out` @ 0x48 */
    f32 out[4];
    f32 one = lbl_802965D4;
    register s32 i __asm__("r24");   /* want's loop counter register */
    s32 ctr4;
    register Att *A __asm__("r20");  /* want's atts-base register */
    f32 *s0;
    f32 *s1;
    f32 *s2;
    f32 *BP;
    __ps_t deadp;                   /* want has a dead B[0] load here */

    A = obj->atts;
    i = 0;
    if (i < (s32)obj->count) {
        do {
            /* Empty 4-iteration countdown. This is the load-bearing trick:
               it stops ngccc strength-reducing the loop index into
               byte-offset induction variables and makes it emit want's
               `slwi i,4 / slwi i,6` loop head. Its body is dead in want. */
            ctr4 = 4;
            do {
            } while (--ctr4 != 0);

            s0 = A[i].s[0].v;
            s1 = A[i].s[1].v;
            s2 = A[i].s[2].v;
            BP = obj->bases;

            p0[0] = s0[0] - BP[i * 4 + 0];
            p0[1] = s0[1] - BP[i * 4 + 1];
            p0[2] = s0[2] - BP[i * 4 + 2];
            p0[3] = one;
            p1[0] = s1[0] - BP[i * 4 + 0];
            p1[1] = s1[1] - BP[i * 4 + 1];
            p1[2] = s1[2] - BP[i * 4 + 2];
            p1[3] = one;
            p2[0] = s2[0] - BP[i * 4 + 0];
            p2[1] = s2[1] - BP[i * 4 + 1];
            p2[2] = s2[2] - BP[i * 4 + 2];
            p2[3] = one;

            fn_8008757C(out, (f32 *)((char *)obj->mats + i * 64), p0);
            *(__ps_t *)&p0[0] = *(__ps_t *)&out[0];
            *(__ps_t *)&p0[2] = *(__ps_t *)&out[2];
            fn_8008757C(out, (f32 *)((char *)obj->mats + i * 64), p1);
            *(__ps_t *)&p1[0] = *(__ps_t *)&out[0];
            *(__ps_t *)&p1[2] = *(__ps_t *)&out[2];
            fn_8008757C(out, (f32 *)((char *)obj->mats + i * 64), p2);

            *(__ps_t *)&p2[0] = *(__ps_t *)&out[0];
            *(__ps_t *)&p2[2] = *(__ps_t *)&out[2];

            fn_8006BF04(obj, i, t);

            /* `obj->bases[...]` (not the BP local) + volatile: this is what
               reproduces want's `lwz r9,0(r26)` reload of the bases pointer
               and the separate `add r11,r31,r9` after the call. */
            *(__ps_t *)&p0[0] = *(__ps_t *)&p0[0] + *(volatile __ps_t *)&obj->bases[i * 4 + 0];
            *(__ps_t *)&p0[2] = *(__ps_t *)&p0[2] + *(volatile __ps_t *)&obj->bases[i * 4 + 2];
            deadp = *(volatile __ps_t *)&obj->bases[i * 4 + 0];
            *(__ps_t *)&p0[0] = *(__ps_t *)&p1[0];
            *(__ps_t *)&p1[2] = *(volatile __ps_t *)&p1[2] + *(volatile __ps_t *)&p1[0] + *(volatile __ps_t *)&obj->bases[i * 4 + 2];
            *(__ps_t *)&p2[0] = *(volatile __ps_t *)&p2[0] + *(volatile __ps_t *)&obj->bases[i * 4 + 0];
            *(__ps_t *)&p2[2] = *(volatile __ps_t *)&p2[2] + *(volatile __ps_t *)&obj->bases[i * 4 + 2];

            s0[0] = p0[0];
            s0[1] = p0[1];
            s0[2] = p0[2];
            s0[3] = one;
            s1[0] = p1[0];
            s1[1] = p1[1];
            s1[2] = p1[2];
            s1[3] = one;
            s2[0] = p2[0];
            s2[1] = p2[1];
            s2[2] = p2[2];
            s2[3] = one;
            i++;
        } while (i < (s32)obj->count);
    }
}
