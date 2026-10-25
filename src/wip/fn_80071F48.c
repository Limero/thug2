// PARKED 2026-09-30: 81.2% -> 81.2%
//
// RESIDUAL, ROOT-CAUSED THIS ROUND: got is ONE CALLEE-SAVED REGISTER SHORT.
// want `stmw r18,0x28` = 14 saved (r18..r31); got `stmw r19,0x2c` = 13. The
// object is size-exact (596B) and instruction-for-instruction structurally
// correct — every diff is a register NUMBER or a 2-insn order, never an opcode
// or a missing/extra instruction. Counting the values live across the outer
// loop: want uses all 14, got only 13. Exactly TWO webs differ in class:
//   * the 0xC028 multiply constant: want `li r24,0 / ori r24,r24,0xc028 /
//     mullw r11,r7,r24` puts it in a CALLEE-SAVED reg; got materializes the
//     same two-instruction constant into SCRATCH r0 (`mullw r9,r7,r0`). GCC's
//     `force_operand` for an inline const_int always prefers a scratch, and
//     no C spelling tried turns it into a pseudo (named local, file-scope
//     const, `stride = 0xC028`) — all byte-identical.
//   * the body-row pointer: want `add r26,r11,r19` sits in the outer-loop
//     PREHEADER (so it is live across fn_8009BAD4 => callee-saved); got
//     recomputes it INSIDE the inner loop (`add r9,r24,r9`, scratch r9).
// The rest of the map then falls out of the allocation pool (descending
// r31..r18 in both, just one entry short):
//   web        want   got        web          want   got
//   anchor#2   r18    r19        body row     r26    r9/r25
//   baseA copy r19    r24        head row     r9     r26
//   const .C028 r24   r0 (scr.)  row counter  r31    r28 (SHARED with k)
//   baseB      r20    r20        rec ptr      r31    r31
// Note want's row counter and rec pointer SHARE r31 (counter dead mid-body,
// value kept in r27); got pairs the counter with the k counter in r28. Both
// pairings are disjoint-range-legal, so this is a pure tie-break.
// 28 diffs = 3 (stmw/lis/lmw) + ~15 preheader colour/order + 8 in-loop
// transpositions (`li r28,0`/`mtlr r0`; walker+=0x60/`add r3`;
// `add r27,+1`/`mr r31,r29`; `lfs f3,8(r31)`/`add r3`).
//
// MEASURED THIS ROUND (base = 81.2%, all on the current body):
//   delete the `register s32 var_r28 __asm__("r28")` pin   78.5%  (worse)
//     -> the pin IS load-bearing (ablation measured, not assumed).
//   delete the `"" "+r"(baseA2)` barrier                  DIFF   (worse)
//   move that barrier after `var_r29 = ...`               76.5%  (worse)
//   merge row counter + rec pointer into ONE variable      68.5%  (worse:
//     retail really has two names — the pin to r31 on the counter alone
//     gives 592B/DIFF 22.3%, one word short)
//   hoist `row = baseA2+off` out of the inner loop         77.2%  (worse:
//     gives the body row a callee-saved reg but frees another)
//   `baseA = lbl_8036B3A0` instead of `baseB - 0x20`       DIFF   (worse)
//   `baseA2 = baseA` instead of `baseB - 0x20`             81.2%  (no-op:
//     got already emits the `mr r24,r21` copy)
//   reorder the loop setup (baseB/baseA/off/counter)       81.2%  (no-op)
//   named `stride` local for 0xC028                        81.2%  (no-op)
//   `while (var_r31 < row->cnt)` instead of `rowh[7]`      DIFF   (worse)
//   move rec=/walker=/k=0 after the `vt` reload (x2)      81.2%  (no-op)
//   `var_r28 += 0;` inside loop_5 to force 14 regs         81.2%  (no-op)
// M8.31 return-type flips — ALL byte-identical 81.2%, so this is not a
// doc-15 arg-setup residual: `fn_8009B9F0` void*->s32, `fn_80070B74`
// void->s32, `fn_80070BF0`+`fn_80070BA8` void->s32. Arity audit re-verified
// from the retail prologues and the promoted siblings (`src/fn_8009BAD4.c`,
// `src/fn_80070BF0.c`, `src/fn_80070BA8.c`, `src/fn_80020494.c`,
// `src/fn_800204B4.c`, `src/fn_80070DB0.c`): all signatures in the draft are
// already correct (fn_8000F2F8 does read r4; fn_8009B9F0's r4 is dead).
// No flag sweep re-run (the header below already records every ProDG flag as
// a no-op or worse, and M8.31 already came back neutral).
//
// WIP DRAFT (non-matching) — hand-rebuilt from the want disassembly 2026-09-28.
// family=m2c range=0x80071F48-0x8007219C size=596B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// NEAR 81.2% (28/149 words differ), SIZE-EXACT 596B. Was DIFF 3.1% (m2c body).
//
// WHAT THE m2c DRAFT GOT WRONG (all semantic, none scheduling):
//  1. `Mem_Alloc2(0x54)` + `fn_8009B9F0(1)` were two statements; the want
//     chains them — `li r3,0x54; bl Mem_Alloc2; li r4,1; bl fn_8009B9F0` — so
//     fn_8009B9F0 is TWO-arg and takes the alloc result as arg0 (§4t).
//  2. `fn_80070B74(3, 2, 3)` passed the literals in r3/r4/r5. The want has
//     r3 = the fn_8009B9F0 return (already in r3), r4=3, r5=2, r6=3, i.e.
//     `fn_80070B74(temp_r30, 3, 2, 3)` with a 3-arg proto (callee body is
//     1-arg — dead-arg proto, §6t-3, keeps the li's and kills the crclr).
//  3. `fn_8000F2F8` was called with a bogus 3rd literal; it is 2-arg.
//  4. The four CP-register writes were all `(s8 *)0xCC008000`. The want is
//     stb 0x10 / sth 0 / sth 0x1025 / stfs, i.e. volatile u8/u16/u16/f32
//     stores through `extern char lbl_CC008000[]` (recipe 36 — the four must
//     be volatile or they coalesce).
//  5. `sp1C`/`sp20` were file-scope `static s32`; they are stack fields at
//     r1+0x1C / r1+0x20 WRITTEN BY CALLEE GX_GetProjectionv. Modelling them as two
//     uninitialised f32 locals made ngccc home them in callee-saved FPRs
//     (stfd f30/f31 + lfd) and shifted the whole frame. One 0x1C-byte struct
//     local `st` at r1+8, passed to GX_GetProjectionv/204B4, reproduces the frame.
//  6. `(char *)(*(void **)lbl_802FFE98)` deref chain -> `extern
//     Unk_9994C3F5 *lbl_802FFE98` (L1 / doc-51). NOTE: measured A/B — L1 is a
//     NO-OP here (81.2% either way); the load already folded to lis+lwz.
//  7. The vtable offsets are `s16` (`lha`), and the vcall fn-ptr types must
//     carry their FLOAT args: `(void*,s32,f32,f32,f32)` at vtable+0x44 and
//     `(void*,s32,f32,f32)` at +0x8C. With m2c's all-`void*` cast the floats
//     went into GPRs. `temp_r30 + vt->off80` also needs the `(char *)` cast
//     or ngccc emits `mulli r3,r3,0x24` (Obj is 0x24 bytes -> element index).
//  8. `var_r31_2 += 0x20` on a `Rec*` (0x20 bytes) became +0x400.
//  9. `Unk_DB0E2BAB`'s record fields are f32 here, so a file-local Rec/Vt/Obj
//     layout is used instead of the mega-merged shared classes.
//
// TWO LEVERS THAT DID THE FINAL 4%:
//  * `register s32 var_r28 __asm__("r28")` on the innermost (k) counter:
//    77.2% -> 79.9%. Without the pin ngccc recycles the dead j register for k
//    and every downstream home is off by one.
//  * `__asm__("" : "+r"(baseA2))` — a ZERO-CODE barrier on a second copy of
//    the row base (`baseA2 = baseB - 0x20`, same value as `baseA`). It stops
//    CSE merging the two address webs, which is what produces the want's
//    three separate `add`s off the same two base registers
//    (`add r9,r11,r21` head / `add r29,r11,r20` walker / `add r26,r11,r19`
//    body) plus the preheader `mr r19, r21`. 79.9% -> 81.2%.
//
// RESIDUAL (28 words, want 596B == got 596B):
//  * Frame: want `stmw r18,0x28(r1)` / `lmw r18,0x28(r1)` (14 saved regs,
//    second page anchor in r18); got `stmw r19,0x2c(r1)` (13 regs, anchor in
//    r19) — one register short, so every later stack offset is identical but
//    the save span is not. 3 words.
//  * Preheader register colouring only (structure matches now): want
//    r11=off, r19=baseA-copy, r22=zero, r24=const, r26=body-row, r31=j, r9 =
//    head-row; got r9=off, r24=copy, r23=zero, r0=const, r9=body-row, r28=j.
//    Plus the 0xC028 materialization: want interleaves `li r24,0` with
//    `addi r20,r9,-0x4c40` before the `ori`; got emits `li/ori` together
//    after the base derivations. ~15 words.
//  * Four pure scheduler transpositions inside the first vcall arg setup
//    (`li r28,0`/`mtlr r0`; `addi r29,r29,0x60`/`add r3,r30,r3`), the
//    `lfs f3,8(r31)`/`add r3,r30,r3` pair, and `addi r27,r31,1`(j+1) /
//    `mr r31,r29`(rec=walker) order. 8 words.
//
// DEAD ENDS (do not re-run):
//  * every hard `register` pin on top of the two above (off->r11 70.5,
//    baseA2->r19 72.5, j->r31 FAIL-size, zero->r22 73.2, row->r26 60.4,
//    baseA->r21 61.7, baseB->r20 FAIL-size) — every pin collapses or
//    re-shuffles the whole allocation.
//  * every ProDG scheduling flag: -fno-schedule-insns2 63.1, -fno-schedule-insns
//    53.7, -fno-gcse 41.6, -fno-rerun-cse-after-loop 9.4; -fno-sched-spec /
//    -fno-sched-interblock / -fno-expensive-optimizations / -fno-thread-jumps
//    are exact no-ops.
//  * spelling the loop as `for` / `do-while` / negated `if` instead of
//    `while`+`goto` (all 77.2% = no-op at the v4c4 stage).
//  * moving `var_r31 += 1` earlier in the inner body (63.8), moving
//    `var_r31_2 += 1` before the second vcall (72.5).
//  * `volatile`/plain `register` on baseA2 instead of the `""` barrier
//    (q_f 76.5, n3 72.5).
//  * the head test as a named `Row*`/`s32*` pointer WITHOUT the baseA2 copy
//    loses 2 words (588B, DIFF 23.5) — the copy is what pays for the add.
#include "types.h"
#include "structs.h"
#include "mem.h"

extern Unk_9994C3F5 *lbl_802FFE98;
extern f32 lbl_80295318;
extern bool lbl_803015F0;
extern char lbl_8036B3A0[];
extern char lbl_8036B3C0[];
extern char lbl_CC008000[];

extern void fn_8000F2F8(void *, s32);
extern void fn_8000F320(void *);
extern void GX_GetProjectionv(void *);
extern void GX_SetProjectionv(void *);
extern void *fn_8009B9F0(void *, s32);
extern void fn_8009BAD4(void *, s32, s32, s32);
extern void fn_80070B74(void *, s32, s32, s32);
extern void fn_80070BA8(void *);
extern void fn_80070BF0(void *);

typedef struct Vt {
    char pad0[0x8];
    s16 off8;
    char padA[2];
    void *(*fC)(void *, s32);
    char pad10[0x30];
    s16 off40;
    char pad42[2];
    void *(*f44)(void *, s32, f32, f32, f32);
    char pad48[0x38];
    s16 off80;
    char pad82[2];
    void *(*f84)(void *, s32, s32);
    s16 off88;
    char pad8A[2];
    void *(*f8C)(void *, s32, f32, f32);
} Vt;

typedef struct Obj {
    char pad0[0x10];
    s32 f10;
    char pad14[0xC];
    Vt *vt;
} Obj;

typedef struct Rec {
    f32 f0;
    f32 f4;
    f32 f8;
    char padC[8];
    f32 f14;
    f32 f18;
    char pad1C[4];
} Rec;

typedef struct Row {
    char pad0[0x1C];
    u32 cnt;
    char pad20[0xC000];
    s32 tail;
} Row;

typedef struct St {
    char pad0[0x14];
    f32 f1C;
    f32 f20;
} St;

void fn_80071F48(void) {
    St st;
    f32 cf;
    s32 var_r7;
    u32 var_r31;
    s32 temp_r11;
    s32 zero;
    Obj *temp_r30;
    Vt *vt;
    Row *row;
    char *var_r29;
    char *baseB;
    char *baseA;
    char *baseA2;
    s32 *rowh;
    Rec *var_r31_2;
    register s32 var_r28 __asm__("r28");

    fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->unk0x118);
    temp_r30 = (Obj *)fn_8009B9F0(Mem_Alloc2(0x54), 1);
    fn_80070B74(temp_r30, 3, 2, 3);
    GX_GetProjectionv(&st);
    cf = lbl_80295318;
    *(volatile u8 *)lbl_CC008000 = 0x10;
    *(volatile u16 *)lbl_CC008000 = 0;
    *(volatile u16 *)lbl_CC008000 = 0x1025;
    *(volatile f32 *)lbl_CC008000 = st.f1C * cf + st.f20;
    var_r7 = 0;
    while ((u32)var_r7 < (u32)lbl_803015F0) {
        temp_r11 = var_r7 * 0xC028;
        var_r31 = 0;
        baseB = lbl_8036B3C0;
        baseA = baseB - 0x20;
        baseA2 = baseB - 0x20;
        __asm__("" : "+r"(baseA2));
        var_r29 = baseB + temp_r11;
        rowh = (s32 *)(baseA + temp_r11);
        while ((u32)var_r31 < (u32)rowh[7]) {
            row = (Row *)(baseA2 + temp_r11);
            zero = 0;
            fn_8009BAD4(temp_r30, row->tail, 0, 0);
            var_r31_2 = (Rec *)var_r29;
            var_r28 = 0;
            var_r29 += 0x60;
            vt = temp_r30->vt;
            vt->f84((char *)temp_r30 + vt->off80, 0, 0x7F7F7FFF);
            vt = temp_r30->vt;
            vt->f84((char *)temp_r30 + vt->off80, 1, 0x7F7F7FFF);
            vt = temp_r30->vt;
            vt->f84((char *)temp_r30 + vt->off80, 2, 0x7F7F7FFF);
loop_5:
            vt = temp_r30->vt;
            vt->f44((char *)temp_r30 + vt->off40, var_r28, var_r31_2->f0,
                    var_r31_2->f4, var_r31_2->f8);
            vt = temp_r30->vt;
            vt->f8C((char *)temp_r30 + vt->off88, var_r28, var_r31_2->f14,
                    var_r31_2->f18);
            var_r28 += 1;
            var_r31_2 += 1;
            if (var_r28 <= 2) {
                goto loop_5;
            }
            temp_r30->f10 = zero;
            var_r31 += 1;
            fn_80070BF0(temp_r30);
        }
        var_r7 += 1;
    }
    GX_SetProjectionv(&st);
    lbl_803015F0 = 0;
    fn_80070BA8(temp_r30);
    if (temp_r30 != NULL) {
        vt = temp_r30->vt;
        vt->fC((char *)temp_r30 + vt->off8, 3);
    }
    fn_8000F320(lbl_802FFE98);
}
