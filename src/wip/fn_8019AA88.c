// WIP DRAFT (non-matching) - hand-rebuilt from the retail disassembly.
// family=m2c range=0x8019AA88-0x8019B2A0 size=2072B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-05 (hand-rebuild): 0.58% -> 45.95%, object now EXACTLY
// 2072B == symbol size (was 3548B). Semantics are now faithful (see the
// walk-through below); the residual is pure ProDG allocator/scheduler
// placement, not semantics.
//
// (a) BEST SCORE: 45.95% masked, 280/518 words differ, flags=none,
//     tools/score_wip.py 0x8019AA88 src/wip/fn_8019AA88.c
//     -> verdict DIFF (not NEAR). br_targets not applicable (not 100%).
//
// (b) RESIDUAL, by region (retail addr -> what got emits instead):
//   * 0x8019ACB8-0x8019AE9C (~150 words, the single biggest block): the six
//     software-pipelined (f32)(s32) int->f32 chains. Retail interleaves the
//     three `fctiwz` anchors and the three 2^52+2^31 double reloads in one
//     fixed order (f12/f10/f8 then f9/f6/f5); ngccc emits the same 6 chains
//     but with a different interleave and a different f5..f13 rotation, and
//     it sinks `frsp`/`fdivs f28` per chain (retail pairs them earlier).
//   * Prologue/epilogue (~14 words): frame is 0x90 vs retail 0x88, and
//     `stmw r23` (9 callee-saved GPRs) vs retail `stmw r24` (8). Cause:
//     ngccc hoists the lbl_802AAB3C rodata base into r23 (loaded at 0x8019AD4C,
//     used at 0x8019AEDC and 0x8019B100) where retail re-`lis r9`s it; that
//     extra callee-saved GPR also pushes one extra spilled word above the
//     convert temp. The convert temp itself IS at the retail slot (r1+0x3c)
//     and the LR slot/stfd f27..f31 block is otherwise right.
//   * Constant loads: retail loads lbl_802AAB38 (1e-4), lbl_802AAB3C (0.5),
//     lbl_802AAB40 (99.0) exactly once each (f0 / f2 / f3); this body emits
//     them 2-3x because ngccc does not CSE extern float loads outside a
//     register-var.
//   * Register numbering only (~60 words): pool base in r25/r26/r30 vs r9,
//     `f1` vs `f11` for 3.0f, `mr r8,r11` vs `mr r8,r9`, the second rec loop
//     using r28..r31 where retail uses r27..r30.
//
// (c) RULED OUT (each measured, all worse than 45.95% unless noted):
//   * register-var pins for the four hoistable constants DO work and are
//     kept: fr30=99.9, fr28=10.0, fr29=99.85, fr31=0.0, fr27=(99.9-score)/10
//     (worth +20 points: 23.6% -> 45.6% together with the do/while fix).
//     fr1=3.0f adds +0.4% and is kept.
//   * fr3=99.0f: 21.9%. fr2=0.4999f: 21.9%. fr0=1e-4f + all four at once
//     (`ve`): 18.5%. Plain (unpinned) locals for any of them: 19.9-21.0%.
//     The pins collide with ngccc's own fr0..fr3 argument/choice.
//   * Second rec loop MUST be `do { ... } while (i != 8)` to get retail's
//     `li r0,8; mtctr r0; ...; bdnz`; `for (i=0;i<8;i++)` gives
//     `cmpwi r28,7; ble` and 26.7% (+19 points from the do/while).
//   * Rewriting the FIRST rec loop as m2c's byte-offset indexed form
//     (`*(s32*)((char*)arg0 + 0x1C + i*0x24)`) to get retail's
//     `lwzx r0,r10,r7` / `stwx r9,r8,r0` two-base indexed form: 25.7-30.9%.
//     Same for the clamp loop (45.6%, neutral), the swap loop (28.8%), the
//     3-iteration vals[3..5] write loop (25.2%), the pointer-loop signed
//     compare (`cmplw`/`bgt` instead of retail's `cmpw`/`ble`: 45.6%, neutral).
//   * Statement-order variants of the three `v*10/10 + 1e-4` lines: 44.4%
//     (ascending) and 41.9% (temporaries then reversed stores) vs 45.95%.
//   * Explicit temporaries to mirror retail's lerp instruction order: 43.1%
//     (r1) and 4.8% (r2, `t = (g-f); t = t*z;` split into two statements).
//   * `volatile double` frame pad: 0/1/2 pads all give frame 0x58/0x60/0x68
//     at 40.0%, 3 pads give frame 0x88 but the convert temp at 0x34 (42.7%),
//     4 pads give the convert temp at the retail 0x3c with frame 0x90
//     (45.95%, kept). Mixing s32 pads does not separate the two.
//   * fn_80129068 must be 3-arg (`fn_80129068(o3, 5, 0xA)`), see the promoted
//     src/fn_80129068.c; a 2-arg prototype measures 0.4% higher only because
//     it emits 2 fewer words, but it is semantically wrong - kept correct.
//   * The 12 dead `mr rX,r7` den-fills retail has at 0x8019ACC0-0x8019AD44
//     (recipe 89 / doc-33 inlined-call staging residue) are NOT the blocker:
//     ngccc emits 13 of them on its own from this body.
//
// NEXT LEVER (unexplored): the region 0x8019ACB8-0x8019AE9C is one
// software-pipelined schedule; splitting the six (f32)(s32) conversions onto
// distinct `union { u32 w[2]; f64 d; }` stack temps (rather than letting
// ngccc share one) may change the interleave. Also unpriced: the 99.0f /
// 0.4999f / 1e-4f triple-load could go away if the source used three
// separate file-local `static f32` copies of them.
//
// STRUCTURE (retail 0x8019AA88-0x8019B29C, 518 words):
//   0xAA88-AAB8  guard: if (arg0->flag) return;
//   0xAABC-AAB8  x = (f32)(f64)(s32)arg1
//   0xAAEC-AB74  4-way piecewise-linear remap of x onto 0..100 using
//                rec[7].f/g/h/i (0x12C/0x130/0x134/0x138) + x1(0x13C)/
//                x2(0x140); the last arm's denominator is retail's dead
//                (x2 + x2) - x2.
//   0xAB74-AC88  score(0x174) = remap - bias(0x148), clamped to 99.9, then
//                jittered by Mth_PlusOrMinus((99.9-score)/10 * 0.5) and
//                Mth_PlusOrMinus((99.9-score)/10); vals[0..1] (0x14C/0x150)
//                are the jittered copies (clamped 99.85 but stored as 99.9),
//                vals[2] (0x154) = score*3 - (vals[0]+vals[1]).
//   0xAC8C-AD8C  each of the three is snapped: (f32)(s32)(v*10)/10 + 1e-4
//   0xAD90-AE9C  then round-half-up: (f32)(s32)((f32)(s32)(v + 0.5f)),
//                clamped to 99.0  -> the DOUBLE (f32)(s32) nest is real
//                retail code (two fctiwz + two 2^52+2^31 dances per value)
//   0xAEC8-AF48  score = mean(vals[0..2]) + 0.5 (double nest), clamp 99.0
//   0xAF4C-AFE8  slots[idx] = (s32)score; fill rec[i].cached from rec[i].gate == 0
//   0xAFB4       fn_8019B2A0(arg0)
//   0xAFC0-AFE8  slot = i+1 for every rec[i].gate == 0
//   0xAFEC-B034  vals[3..5] = min(vals[0..2]) - f27 + Mth_PlusOrMinus(f27)
//   0xB038-B064  clamp vals[0..4] at 0
//   0xB068-B098  4 Fisher-Yates swaps against Mth_Rnd2(5)
//   0xB09C-     push the score vectors into the goal manager's script data
//
// float-pool constants (src/r2d_802AAB10.c):
//   802AAB10 = 0.0f  AAB18 = 2^52+2^31  AAB20 = 100.0f  AAB24 = 99.9f
//   AAB28 = 10.0f    AAB2C = 0.5f        AAB30 = 99.85f  AAB34 = 3.0f
//   AAB38 = 1e-4f    AAB3C = 0.49999899f                AAB40 = 99.0f
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_802AAB10;
extern f64 lbl_802AAB18;
extern f32 lbl_802AAB20;
extern f32 lbl_802AAB24;
extern f32 lbl_802AAB28;
extern f32 lbl_802AAB2C;
extern f32 lbl_802AAB30;
extern f32 lbl_802AAB34;
extern f32 lbl_802AAB38;
extern f32 lbl_802AAB3C;
extern f32 lbl_802AAB40;
extern char lbl_802AAAD8[];
extern char lbl_802AAAE0[];
extern char lbl_802AAAE8[];
extern char lbl_802AAAF4[];

s32 Mth_Rnd2(s32 scale);
f32 Mth_PlusOrMinus(f32 arg);
void fn_8019B2A0(void *arg0);
s32 fn_8019B634(void *arg0, s32 arg1);
s32 Game_GetGoalManager(void);
void *fn_801868AC(s32 arg0);
void CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
void fn_8003E7CC(s32 arg0);
void *fn_80128F94(void *arg0);
void fn_80129068(void *arg0, s32 arg1, s8 arg2);
void fn_801276E8(void *arg0, void *arg1, s32 arg2);
void AddChecksum(void *arg0, s32 arg1, s32 arg2);
void fn_80129314(void *o, s32 i, s32 v);
void fn_80127B28(void *arg0, void *arg1, void *arg2);
void fn_80126A30(void *arg0);
void fn_80128FB4(void *arg0, s32 arg1);
void fn_80131714(s32 arg0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9);
void CStruct_delete(void *arg0, s32 arg1);

typedef struct {
    s32 gate;      /* 0x00 */
    s32 cached;    /* 0x04 */
    s32 pad0x8;
    s32 pad0xC;
    s32 pad0x10;
    f32 y0;         /* 0x14 */
    f32 y1;         /* 0x18 */
    f32 y2;         /* 0x1C */
    f32 x0;         /* 0x20 */
} Rec;

typedef struct {
    char pad0x0[8];
    s32 idx;        /* 0x08 */
    char pad0xC[0x10];
    Rec rec[8];     /* 0x1C, 8 x 0x24 */
    f32 x1;         /* 0x13C */
    f32 x2;         /* 0x140 */
    char pad0x144[4];
    f32 bias;       /* 0x148 */
    f32 vals[6];    /* 0x14C..0x160 */
    char pad0x164[0x10];
    f32 score;      /* 0x174 */
    s32 slots[3];   /* 0x178 */
    s32 flag;       /* 0x184 */
    s32 slot;       /* 0x188 */
} T;

void fn_8019AA88(T *arg0, s32 arg1) {
    register f32 c30 __asm__("fr30");
    register f32 c28 __asm__("fr28");
    register f32 c29 __asm__("fr29");
    register f32 c31 __asm__("fr31");
    register f32 f27v __asm__("fr27");
    register f32 k3 __asm__("fr1");
    /* frame pad: retail's frame is 0x88 with its int->f64 convert temp at
       r1+0x38/0x3c; this body needs 4 extra words of locals to land there */
    volatile double _frame_pad0;
    volatile double _frame_pad1;
    volatile double _frame_pad2;
    volatile double _frame_pad3;
    f32 x;
    f32 y;
    f32 z;
    f32 lo;
    f32 t;
    f32 tmp;
    s32 i;
    s32 j;
    s32 spC;
    s32 sp8;
    Rec *rec;
    f32 *p;
    void *o1;
    void *o2;
    void *o3;

    if (arg0->flag == 0) {
        x = (f32)(f64)(s32)arg1;
        if (x < arg0->rec[7].x0) {
            y = (arg0->rec[7].y0 * x) / arg0->rec[7].x0;
        } else if (x < arg0->x1) {
            z = (arg0->rec[7].y1 - arg0->rec[7].y0) * (x - arg0->rec[7].x0);
            y = arg0->rec[7].y0 + z / (arg0->x1 - arg0->rec[7].x0);
        } else if (x < arg0->x2) {
            z = (arg0->rec[7].y2 - arg0->rec[7].y1) * (x - arg0->x1);
            y = arg0->rec[7].y1 + z / (arg0->x2 - arg0->x1);
        } else {
            z = (lbl_802AAB20 - arg0->rec[7].y2) * (x - arg0->x2);
            y = arg0->rec[7].y2 + z / ((arg0->x2 + arg0->x2) - arg0->x2);
        }
        c30 = lbl_802AAB24;
        y -= arg0->bias;
        arg0->score = y;
        if (y > c30) {
            arg0->score = c30;
        }
        c28 = lbl_802AAB28;
        f27v = (c30 - arg0->score) / c28;
        arg0->score = arg0->score + Mth_PlusOrMinus(f27v * lbl_802AAB2C);
        if (arg0->score > c30) {
            arg0->score = c30;
        }
        c31 = lbl_802AAB10;
        if (arg0->score < c31) {
            arg0->score = c31;
        }
        c29 = lbl_802AAB30;
        arg0->vals[0] = arg0->score + Mth_PlusOrMinus(f27v);
        if (arg0->vals[0] > c29) {
            arg0->vals[0] = c30;
        }
        if (arg0->vals[0] < c31) {
            arg0->vals[0] = c31;
        }
        arg0->vals[1] = arg0->score + Mth_PlusOrMinus(f27v);
        if (arg0->vals[1] > c29) {
            arg0->vals[1] = c30;
        }
        if (arg0->vals[1] < c31) {
            arg0->vals[1] = c31;
        }
        arg0->vals[2] = arg0->score * lbl_802AAB34 - (arg0->vals[0] + arg0->vals[1]);
        if (arg0->vals[2] < c31) {
            arg0->vals[2] = c31;
        }
        if (arg0->vals[2] > c29) {
            arg0->vals[2] = c30;
        }
        arg0->vals[2] = (f32)(s32)(arg0->vals[2] * c28) / c28 + lbl_802AAB38;
        arg0->vals[0] = (f32)(s32)(arg0->vals[0] * c28) / c28 + lbl_802AAB38;
        arg0->vals[1] = (f32)(s32)(arg0->vals[1] * c28) / c28 + lbl_802AAB38;
        arg0->vals[0] = (f32)(s32)((f32)(s32)(arg0->vals[0] + lbl_802AAB3C));
        arg0->vals[1] = (f32)(s32)((f32)(s32)(arg0->vals[1] + lbl_802AAB3C));
        arg0->vals[2] = (f32)(s32)((f32)(s32)(arg0->vals[2] + lbl_802AAB3C));
        if (arg0->vals[0] > lbl_802AAB40) {
            arg0->vals[0] = lbl_802AAB40;
        }
        if (arg0->vals[1] > lbl_802AAB40) {
            arg0->vals[1] = lbl_802AAB40;
        }
        if (arg0->vals[2] > lbl_802AAB40) {
            arg0->vals[2] = lbl_802AAB40;
        }

        k3 = lbl_802AAB34;
        arg0->score = (f32)(s32)((f32)(s32)((arg0->vals[0] + arg0->vals[1] + arg0->vals[2]) / k3 + lbl_802AAB3C));
        if (arg0->score > lbl_802AAB40) {
            arg0->score = lbl_802AAB40;
        }
        arg0->slots[arg0->idx] = (s32)arg0->score;
        rec = arg0->rec;
        for (i = 0; i < 8; i++) {
            if (rec[i].gate == 0) {
                rec[i].cached = arg0->slots[arg0->idx];
            }
        }
        fn_8019B2A0(arg0);
        rec = arg0->rec;
        i = 0;
        do {
            if (rec->gate == 0) {
                arg0->slot = i + 1;
            }
            rec++;
            i++;
        } while (i != 8);
        lo = arg0->vals[0];
        if (arg0->vals[1] < lo) {
            lo = arg0->vals[1];
        }
        if (arg0->vals[2] < lo) {
            lo = arg0->vals[2];
        }
        t = lo - f27v;
        for (p = &arg0->vals[3]; p <= &arg0->vals[5]; p++) {
            *p = t + Mth_PlusOrMinus(f27v);
        }
        for (i = 0; i < 5; i++) {
            if (arg0->vals[i] < c31) {
                arg0->vals[i] = c31;
            }
        }
        for (i = 0; i < 4; i++) {
            j = Mth_Rnd2(5);
            tmp = arg0->vals[i];
            arg0->vals[i] = arg0->vals[j];
            arg0->vals[j] = tmp;
        }
        if (fn_801868AC(Game_GetGoalManager()) != 0) {
            CStruct_new(8);
            o1 = CStruct_ctor(8);
            fn_8003E7CC(0xC);
            o3 = fn_80128F94(0xC);
            fn_80129068(o3, 5, 0xA);
            for (i = 0; i < 5; i++) {
                CStruct_new(8);
                o2 = CStruct_ctor(8);
                fn_801276E8(o2, lbl_802AAAD8, (s32)((f32)(s32)(arg0->vals[i] + lbl_802AAB3C)));
                if (fn_8019B634(arg0, i) != 0) {
                    AddChecksum(o2, 0, QB_TOP_JUDGE);
                }
                fn_80129314(o3, i, o2);
            }
            fn_80127B28(o1, lbl_802AAAE0, o3);
            fn_801276E8(o1, lbl_802AAAE8, (s32)((f32)(s32)(arg0->score + lbl_802AAB3C)));
            fn_80126A30(o3);
            if (o3 != 0) {
                fn_80128FB4(o3, 3);
            }
            spC = 0;
            sp8 = 0;
            fn_80131714(lbl_802AAAF4, o1, 0, 0, 0, 0, 0, 0, sp8, spC);
            if (o1 != 0) {
                CStruct_delete(o1, 3);
            }
        }
    }
}
