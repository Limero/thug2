// PARKED 2026-10-05 (fn_800EBC20 full reconstruction): best measured
// 12.54% masked positional (351 got words vs 387 want; 307 mismatches),
// official verdict DIFF. Baseline was the m2c stub at 3.64% / a 220-BYTE
// object (it declared every matrix element as a `static s32 spXX` GLOBAL,
// so it never touched the stack at all — that 3.64% is index-alignment
// luck on 4 prologue words and means nothing). This body is a complete
// hand reconstruction: 1404B, correct 0x1A8 frame, correct local layout,
// every semantic step recovered. Flag `-Os` below is LOAD-BEARING.
//
// At default opt this draft scores very low. The reason is not the float body:
// the optimiser homes the two call-argument addresses into callee-saved
// registers, set up in the prologue; that costs two extra saved registers,
// moves the float save area and grows the frame. The original keeps only three
// callee-saved registers with the float saves and frame as built here, and
// materialises both addresses fresh at the call. Disabling the global common
// subexpression pass reproduces the original frame exactly and is the big
// score jump. This matches the known call-argument homing pattern, except here
// the addresses are unavoidably shared with the pair-copy sites, so the size
// flag (the only lever measured that works) is the fix. With the call deleted
// the default-opt prologue already matches -- the call arguments are the sole
// cause; see "RULED OUT" below.
//
// NOW EXACT: the whole prologue, word for word -- frame setup, link save,
// float saves, integer save block, link slot, and the first words of the empty
// countdown loop at the same addresses. Control-flow shape, all four call
// sites and the frame offset of every scalar and pair access are right.
//
// RESIDUAL = short by 36 words. Census in plain terms:
//   scalar reloads short by about 15: the original reloads more matrix/temp
//   words from the stack inside the long float block than we do; we keep them
//   in float registers. Register-pressure and scheduling, not dag shape.
//   Address setups plus register copies short: the copy blocks home the array
//   base web in a volatile register plus a pair load, plus a second
//   node-pointer reload in one block.
//   Pair copies short by 7: the scale block writes through copies and reads via
//   loads into fresh registers; ours keeps the value in place and emits neither.
//   Counter loops short: the second empty countdown in the common preamble is
//   self-targeting in the original so it is not deletable; ours is the
//   compiler forward-branch empty-loop form and the size flag deletes it.
//   Small single-digit gaps in float arithmetic, address setups, word loads,
//   scalar stores and small-constant setups; four extra pair loads here with
//   no original counterpart.
// Net effect: everything after the float block start is shifted, so the tail
// (which would match almost exactly -- half its words are the epilogue) never
// gets a chance to align.
//
// RULED OUT (all measured, on the 12.54% body or the 1404B -Os body):
//  * the r27/r28 homing is NOT source-form dependent. Array vs pair-array vs
//    one local struct vs four separate arrays; address-of vs decay vs pinned
//    pointer vs zero-code wedge; and multi-pointer prototypes -- all home the
//    two call-argument addresses into callee-saved registers at default opt.
//    The size flag is the only thing that moves it.
//  * hard-register pins are ignored by this compiler build (probe compiles to
//    plain argument setup, pinned registers nowhere). So the colour swap in
//    the node block is not reachable by pinning.
//  * that swap by source shape: declaration order (s0 before p), pinning
//    `p` to r31, hoisting the `s0` load into `if (p != NULL) s0 = ...`,
//    and `fl = (s0 != 0)` all score WORSE (5.70% / 7.67% / 7.67%).
//  * flag sweep, 15 sets: only `-Os` and `-fno-gcse` change the frame.
//    `-O1`(1208B), `-fno-schedule-insns`(1224B), `-O3`, `-fno-schedule-
//    insns2`, `-fno-gcse`+`-Os`, `-fno-expensive-optimizations`,
//    `-fno-thread-jumps`, `-fno-strength-reduce`, `-fno-caller-saves`,
//    `-fno-crossjumping` are no-ops or worse; `-fno-rerun-cse-after-loop`,
//    `-fno-tree-precompute`, `-fno-partial-inlining`, `-mno-altivec` are
//    rejected by cc1 (COMPILE FAIL).
//  * `volatile double` dummies N=0..6: +8 bytes each, GPR count never
//    changes.
//  * a `for (i=0;i<8;i++)` scale loop compiles to a real CTR loop with
//    `psq_lx`; the straight-line unrolled form is required (used).
//  * naming the two CSE'd subexpressions explicitly (`A7b`, `AC22`) to
//    force retail's three `fsubs`: neutral (still folded into fnmadds).
// DO NOT re-grind the 219-word FP block: it is the same class of wall as
// docs/parkings/81 and src/wip/fn_800FD81C (53.5% on a 40-word block).
//
// SEMANTICS RECOVERED (all verified against the retail bytes):
//  * arg0->unk0x1C is a one-entry node. Live node takes one path; otherwise
//    the node is retired with an unlink call, a free, a null store and a
//    timestamp refresh from the global timer plus a constant word. (The old
//    label guess is wrong: the original constant setup plus word load is a
//    read-only-data word typed as a string.)
//  * Both paths pair-copy the node position and matrix into locals, all with
//    pair accesses.
//  * Then the difference of object and node positions as two pair differences,
//    stored back and also passed to the transform helper.
//  * The float block is the cofactor expansion of the matrix: nine 3x3
//    cofactors and nine 2x2 minors combining into the result array. Every
//    expression is in the body below in order.
//  * The scale guard compares the denominator against the one-float constant
//    twice, with two loads from the same constant where the second address is
//    materialised late. The decompiler mis-typed the second compare as an
//    integer view; it is the same float.
//  * The scaled multiply really does zero the low half of each scaled pair
//    (the original writes only part of every scale slot, so the other half is
//    uninitialised stack). That is what the bytes say and what the volatile
//    scalar store plus scaled multiply produces.
//  * The helper computes a 3x4 transform plus a passthrough lane.
// family=m2c range=0x800EBC20-0x800EC22C size=1548B
// extra_cflags: -mps-float
// FLAG: -Os
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

extern f32 lbl_8029ACF4;
extern s32 lbl_802A3150;

typedef struct G_Node {
    char pad0x00[0x58];
    f32 pos[4];
    char pad0x68[0x10];
    f32 m[4][4];
} G_Node;

typedef struct G_Obj {
    char pad0x00[0x0C];
    G_Node *mat4;
    char pad0x10[0x0C];
    G_Node *node;
    __ps_t pos[2];
    char pad0x30[0x40];
    s32 v70;
    s32 v74;
} G_Obj;

void Mem_Free(void *);
s32 Tmr_GetTime(void);
void CObject_RemoveRefLink(s32, G_Node *);
void fn_8008757C(__ps_t *, f32 *, f32 *);

void fn_800EBC20(G_Obj *arg0) {
    f32 a[4];
    f32 m[16];
    f32 v[4];
    f32 r[16];
    f32 A1, A2, AAC, A3, A4, A5, A6, A7, A8, A4b, A10, A11, A12, u;
    f32 A14, A15, A16, A17, A18, A19, A21, A22, w, A24, A26, A27, A28;
    f32 A30, A32, A7b, AC22, A36;
    volatile __ps_t sc[4];
    G_Node *p;
    G_Node *q;
    s32 s0;
    s32 fl;
    s32 i;
    f32 s;

    i = 4;
    do {
        i -= 1;
    } while (i != 0);

    p = arg0->node;
    if (p == NULL) {
        fl = 0;
    } else {
        s0 = *(s32 *)p;
        if (s0 != 0) {
            fl = 1;
        } else {
            arg0->v70 = s0;
            if (*(s32 *)p != 0) {
                CObject_RemoveRefLink(*(s32 *)p, p);
                *(s32 *)p = s0;
            }
            Mem_Free(p);
            arg0->node = (G_Node *)s0;
            arg0->v74 = lbl_802A3150 + Tmr_GetTime();
            fl = 0;
        }
    }

    if (fl != 0) {
        q = (G_Node *)(*(s32 *)arg0->node);
        *(__ps_t *)&a[0] = *(__ps_t *)&q->pos[0];
        *(__ps_t *)&a[2] = *(__ps_t *)&q->pos[2];
        *(__ps_t *)&m[0] = *(__ps_t *)&q->m[0][0];
        *(__ps_t *)&m[2] = *(__ps_t *)&q->m[0][2];
        *(__ps_t *)&m[4] = *(__ps_t *)&q->m[1][0];
        *(__ps_t *)&m[6] = *(__ps_t *)&q->m[1][2];
        *(__ps_t *)&m[8] = *(__ps_t *)&q->m[2][0];
        *(__ps_t *)&m[10] = *(__ps_t *)&q->m[2][2];
        *(__ps_t *)&m[12] = *(__ps_t *)&q->m[3][0];
        *(__ps_t *)&m[14] = *(__ps_t *)&q->m[3][2];
    } else if (arg0->v70 != 0) {
        q = (G_Node *)arg0->v70;
        *(__ps_t *)&a[0] = *(__ps_t *)&q->pos[0];
        *(__ps_t *)&a[2] = *(__ps_t *)&q->pos[2];
        *(__ps_t *)&m[0] = *(__ps_t *)&q->m[0][0];
        *(__ps_t *)&m[2] = *(__ps_t *)&q->m[0][2];
        *(__ps_t *)&m[4] = *(__ps_t *)&q->m[1][0];
        *(__ps_t *)&m[6] = *(__ps_t *)&q->m[1][2];
        *(__ps_t *)&m[8] = *(__ps_t *)&q->m[2][0];
        *(__ps_t *)&m[10] = *(__ps_t *)&q->m[2][2];
        *(__ps_t *)&m[12] = *(__ps_t *)&q->m[3][0];
        *(__ps_t *)&m[14] = *(__ps_t *)&q->m[3][2];
    }

    p = arg0->mat4;
    *(__ps_t *)&v[2] = *(__ps_t *)&p->pos[2] - *(__ps_t *)&a[2];
    arg0->pos[1] = *(__ps_t *)&v[2];
    *(__ps_t *)&v[0] = *(__ps_t *)&p->pos[0] - *(__ps_t *)&a[0];
    arg0->pos[0] = *(__ps_t *)&v[0];

    A1 = m[12] * m[10];
    A2 = m[8] * m[15] - m[12] * m[11];
    AAC = m[8] * m[14] - A1;
    A3 = m[10] * m[15] - m[14] * m[11];
    A4 = m[4] * m[9];
    A5 = m[9] * m[15] - m[13] * m[11];
    A6 = m[9] * m[14] - m[13] * m[10];
    A7 = m[9] * m[6];
    A8 = m[4] * m[15] - m[12] * m[7];
    A4b = A7;
    A10 = m[4] * m[14] - m[12] * m[6];
    A11 = m[5] * m[15] - m[13] * m[7];
    A12 = m[2] * A8;
    u = A12;
    A14 = m[8] * m[13] - m[12] * m[9];
    A15 = m[6] * m[15] - m[14] * m[7];
    A16 = m[4] * m[11] - m[8] * m[7];
    A17 = m[5] * m[11] - m[9] * m[7];
    A18 = m[5] * m[14] - m[13] * m[6];
    A19 = m[6] * m[11] - m[10] * m[7];
    A21 = m[4] * m[13] - m[12] * m[5];
    A22 = m[0] * A15 - A12;
    w = A22;
    A24 = m[0] * A11 - m[1] * A8;
    A26 = m[7] * AAC + (m[4] * A3 - m[6] * A2);
    A27 = m[6] * A14 + (m[4] * A6 - m[5] * AAC);
    A28 = m[4] * m[10] - m[8] * m[6];
    A7b = m[5] * m[10] - A7;
    r[3] = -((m[3] * A7b) + (m[1] * A19 - m[2] * A17));
    A30 = m[7] * A6 + (m[5] * A3 - m[6] * A5);
    AC22 = A4 - m[8] * m[5];
    r[11] = -((m[3] * AC22) + (m[0] * A17 - m[1] * A16));
    A32 = m[7] * A14 + (m[4] * A5 - m[5] * A2);
    r[0] = A30;
    r[8] = A32;
    r[13] = m[2] * A14 + (m[0] * A6 - m[1] * AAC);
    r[10] = m[3] * A21 + A24;
    r[9] = -((m[3] * A14) + (m[0] * A5 - m[1] * A2));
    r[6] = -((m[3] * A10) + A22);
    r[7] = m[3] * A28 + (m[0] * A19 - m[2] * A16);
    r[14] = -((m[2] * A21) + (m[0] * A18 - m[1] * A10));
    r[1] = -((m[3] * A6) + (m[1] * A3 - m[2] * A5));
    r[5] = m[3] * AAC + (m[0] * A3 - m[2] * A2);
    r[2] = m[3] * A18 + (m[1] * A15 - m[2] * A11);
    r[4] = -A26;
    r[12] = -A27;
    A36 = ((m[2] * A32) + (m[0] * A30 - m[1] * A26)) - (m[3] * A27);
    r[15] = (m[2] * AC22) + ((m[0] * A7b) - m[1] * A28);

    if (A36 != lbl_8029ACF4) {
        s = lbl_8029ACF4 / A36;
        if (s != lbl_8029ACF4) {
            *(volatile f32 *)&sc[0] = s;
            *(volatile f32 *)&sc[1] = s;
            *(volatile f32 *)&sc[2] = s;
            *(volatile f32 *)&sc[3] = s;
            *(volatile __ps_t *)&r[0] =
                __builtin_ps_muls0(*(volatile __ps_t *)&r[0], sc[0]);
            *(volatile __ps_t *)&r[1] =
                __builtin_ps_muls0(*(volatile __ps_t *)&r[1], sc[0]);
            *(volatile __ps_t *)&r[2] =
                __builtin_ps_muls0(*(volatile __ps_t *)&r[2], sc[1]);
            *(volatile __ps_t *)&r[3] =
                __builtin_ps_muls0(*(volatile __ps_t *)&r[3], sc[1]);
            *(volatile __ps_t *)&r[4] =
                __builtin_ps_muls0(*(volatile __ps_t *)&r[4], sc[2]);
            *(volatile __ps_t *)&r[5] =
                __builtin_ps_muls0(*(volatile __ps_t *)&r[5], sc[2]);
            *(volatile __ps_t *)&r[6] =
                __builtin_ps_muls0(*(volatile __ps_t *)&r[6], sc[3]);
            *(volatile __ps_t *)&r[7] =
                __builtin_ps_muls0(*(volatile __ps_t *)&r[7], sc[3]);
        }
    }

    *(__ps_t *)&m[0] = *(__ps_t *)&r[0];
    *(__ps_t *)&m[2] = *(__ps_t *)&r[2];
    *(__ps_t *)&m[4] = *(__ps_t *)&r[4];
    *(__ps_t *)&m[6] = *(__ps_t *)&r[6];
    *(__ps_t *)&m[8] = *(__ps_t *)&r[8];
    *(__ps_t *)&m[10] = *(__ps_t *)&r[10];
    *(__ps_t *)&m[12] = *(__ps_t *)&r[12];
    *(__ps_t *)&m[14] = *(__ps_t *)&r[14];
    fn_8008757C((__ps_t *)&v[0], m, (f32 *)&arg0->pos[0]);
    arg0->pos[1] = *(__ps_t *)&v[2];
    arg0->pos[0] = *(__ps_t *)&v[0];
}