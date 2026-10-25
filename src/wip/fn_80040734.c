// WIP DRAFT — hand-rebuilt from want disasm.
// family=m2c range=0x80040734-0x80040A20 size=748B
// FLAG: -fno-expensive-optimizations
// 2026-10-21: 84.5% -> 98.9% (2 words of 187), size-exact.
//
// IDENTITY: applies the QB parameter block to a screen element — alpha,
// relative scale, rot angle, time->frame conversion, anim style flags and the
// RGBA resolve, each guarded by its own GetFloat/ContainsFlag test.
//
// WHAT CLOSED THE 30-WORD STACK-SLOT RESIDUAL: every local is ONE frame
// object (`Frm40734`) whose field offsets reproduce the want's layout, so the
// slot assignment is arithmetic instead of an allocator decision.  The frame
// part that mattered is the descriptor: a 0x14-byte aggregate gets an
// 8-rounded 0x18-byte slot, which pushed every later local +4; splitting it
// into { pad0[4]; x; y; padC[4]; tail; } inside the object puts `tail` at
// frame+0x18 (want) with `sp1C` at frame+0x1c, and because the object is
// entered through `&f.sp1C` in the first statement, the whole block lands at
// frame+0x08.  Measured and rejected: shrinking the vec to 0x10 and making
// `tail` a separate scalar (the scalar is slotted by first `&`, i.e. last, at
// 0x38, so everything moves -4), an s32[5] array (rounds to 0x18), and a
// packed `{ s32 tail; f32 v; }` pair for tail+sp1C (correct slots, but the
// shared base burns a callee-saved register and shifts arg0's home).
//
// The two call windows also need the float arguments read into locals first
// (`sv`, and `sx`/`sy`): written as direct member arguments the `lfs` sinks
// below the `var_r29 != 0` bool materialisation, which is 13 words of the
// residual above.
//
// REMAINING (2 words, one tie): in the QB_SCALE window the want copies arg0
// into r3 BEFORE the `fmr f2,f1` that duplicates the scale float; this build
// emits the fmr first.  Measured and inert: naming arg0 in a local, a
// `(SE *)` cast, two separately loaded locals, and a bool-typed temp for
// `var_r29 != 0` (all 2 diffs, 98.9%).  Also inert: every adjacent-statement
// transposition of the 20 top-level statements (compiler-searched), -Os
// (4 diffs), -fno-schedule-insns (24), -fno-schedule-insns2 (6).
// 2026-10-23 flag sweep, all 2 words: -fno-caller-saves, -fno-keep-static-consts,
// -fno-thread-jumps, -fno-branch-count-reg, -fno-function-cse,
// -fno-optimize-register-move, -fno-regmove, -fno-force-mem, -fno-inline,
// -fno-strict-aliasing, -fno-defer-pop, -fno-optimize-sibling-calls,
// -fno-delayed-branch, -fno-sched-interblock, -ffixed-r6|r7|r8|r10|r12.
// Worse: -fno-cse-follow-jumps 43, -O3 4, -ffixed-r9 14, -ffixed-r11 6.
// Body: an empty `"+f"` barrier on the copied scale and a full memory clobber
// both stay at 2; `"+r"` on arg0 itself costs 12, and a `"+r"` barrier on a
// local copy of arg0 does not compile with this cc1.  The pair is scheduler
// state, not source shape (§7zj).
#include "types.h"

/* One frame object: every local at the offset the want uses, so no slot
   ordering decision is left to the allocator.  The vec part is the same
   bytes as the original 0x14 typedef, split so that `tail` (want: frame+0x18)
   falls right before sp1C (frame+0x1c) instead of being rounded up. */
typedef struct {
    char pad0[4];
    f32 x;
    f32 y;
    char padC[4];
    s32 tail;
    f32 sp1C;
    f32 sp20;
    f32 sp24;
    f32 sp28;
    f32 sp2C;
    f32 sp30;
    s32 sp34;
    s32 sp38;
} Frm40734;

#include "qb_constants.h"
#include "structs.h"

// file-local: the out-param of fn_80125000/GetPair (two floats at +4/+8)
typedef struct { char pad0[4]; f32 x; f32 y; char padC[4]; s32 tail; } VecT;

// file-local: only the members this function touches (offsets byte-proven from want)
typedef struct {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0x78];
    f32 unk0x88;
    char pad0x8C[0xFC];
    f32 unk0x188;
    char pad0x18C[4];
} SE;

extern f32 lbl_80292334;
extern f64 lbl_80292338;

s32 ContainsFlag(CStruct *, s32);
s32 CScreenElement_resolve_pos(void *, CStruct *, f32 *, f32 *);
s32 GetPair(CStruct *, s32, VecT *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80125000(VecT *);
void CScreenElement_SetPos(SE *, s32, f32, f32);
void CScreenElement_SetAlpha(SE *, s32, f32);
void CScreenElement_SetScale(SE *, s32, s32, f32, f32);
void fn_8003FB80(SE *, s32, f32);
void CScreenElement_SetAnimTime(SE *, s32);
void CScreenElement_SetRGBA(SE *, s32 *, s32);
s32 CScreenElement_resolve_rgba(SE *, CStruct *, s32, s32 *);
// FLAG: -fno-expensive-optimizations

void CScreenElement_SetMorph(SE *arg0, CStruct *arg1) {
    Frm40734 f;
    s32 var_r29;
    s32 var_r4_3;
    f32 temp_f0;

    if (CScreenElement_resolve_pos(arg0, arg1, &f.sp1C, &f.sp20) != 0) {
        CScreenElement_SetPos(arg0, 0, f.sp1C, f.sp20);
    }
    if (ContainsFlag(arg1, QB_RESTORE_ALPHA) != 0) {
        CScreenElement_SetAlpha(arg0, 0, arg0->unk0x188);
    }
    if (GetFloat(arg1, QB_ALPHA, &f.sp24, 0) != 0) {
        if (ContainsFlag(arg1, QB_REMEMBER_ALPHA) != 0) {
            arg0->unk0x188 = arg0->unk0x88;
        }
        CScreenElement_SetAlpha(arg0, 0, f.sp24);
    }
    var_r29 = 0;
    if (ContainsFlag(arg1, QB_RELATIVE_SCALE) != 0) {
        var_r29 = 1;
    }
    if (GetFloat(arg1, QB_SCALE, &f.sp28, 0) != 0) {
        {
            f32 sv = f.sp28;
            CScreenElement_SetScale(arg0, var_r29 != 0, 0, sv, sv);
        }
    }
    fn_80125000(&f);
    if (GetPair(arg1, QB_SCALE, &f, 0) != 0) {
        {
            f32 sx = f.x;
            f32 sy = f.y;
            CScreenElement_SetScale(arg0, var_r29 != 0, 0, sx, sy);
        }
    }
    if (GetFloat(arg1, QB_ROT_ANGLE, &f.sp2C, 0) != 0) {
        fn_8003FB80(arg0, 0, f.sp2C);
    }
    if (GetFloat(arg1, QB_TIME, &f.sp30, 0) != 0) {
        temp_f0 = f.sp30 * lbl_80292334;
        if (!(temp_f0 >= lbl_80292338)) {
            var_r4_3 = (s32) temp_f0;
        } else {
            var_r4_3 = (s32) (temp_f0 - lbl_80292338) ^ 0x80000000;
        }
    } else {
        var_r4_3 = 0;
    }
    CScreenElement_SetAnimTime(arg0, var_r4_3);
    f.sp34 = 0;
    arg0->unk0xC = arg0->unk0xC & QB_UNKNOWN_0xFFFFFCFF;
    if (GetChecksum_2(arg1, QB_ANIM, &f.sp34, 0) != 0) {
        if (f.sp34 == QB_FAST_OUT) {
            arg0->unk0xC = arg0->unk0xC | 0x100;
        } else if (f.sp34 == QB_FAST_IN) {
            arg0->unk0xC = arg0->unk0xC | 0x200;
        } else if (f.sp34 == QB_GENTLE) {
            arg0->unk0xC = arg0->unk0xC | 0x300;
        }
    }
    if (CScreenElement_resolve_rgba(arg0, arg1, QB_RGBA, &f.sp38) != 0) {
        f.tail = f.sp38;
        CScreenElement_SetRGBA(arg0, &f.tail, 0);
    }
}