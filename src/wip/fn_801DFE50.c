// WIP DRAFT — C body with PARKED status (non-matching)
// family=m2c range=0x801DFE50-0x801E0974 size=2852B
// UPDATE 2026-08-24 (re-audit): want has NO VMX words (unlike 801DE248/50C/8BC)
// but 32 psq_ ops (needs -mps-float) + xoris int->float dances referencing REAL
// rodata2 doubles (lfd -0x28d0(r9) = lbl_802AD730-class) -> use the 6j-1 manual
// union dance, NOT plain (f32)(f64) casts. Want frame 0x118 saves f25-f31 +
// stmw r26; draft reaches 0x70/f26-f31/r24: one whole FPR web + locals missing
// (same allocator-order wall as fn_801E0974 park note).
// PARKED: m2c-corrupt + FPR frame mismatch + float pool + large control flow
// Reason: 2852B function with 7 FPR saves (want frame 0x118, got 0x70 with 6 FPRs, +168B diff), 8 double slots,
//   m2c produced placeholder `0;` lines (6 occurrences) and `if (0 !=0)` dead branches that have no source equivalent,
//   plus int->double xoris pattern and .rodata float constants (lbl_802AD72C etc) that emit lfs vs f32 cast mismatches.
//   WANT prologue: stwu -0x118, stfd f25@0xe0..f31@0x110, stmw r26@0xc8 ; GOT: stwu -0x70, stfd f26@0x40..f31@0x68, stmw r24@0x20
//   Early diff shows entirely different FPR count (7 vs 6) and frame, so no single `volatile double _dummy` (tried via test_wip dual injection) fixes it - would need 3 dummies but still placeholder logic mismatches.
//   Also contains matrix multiply loops (sp48..sp84) with s32 casts of f32 data - width confusion.
// Tried: proto crclr (fn_801417B8, fn_800AA02C, fn_8014030C s32 vs f32 return), lbl s32 vs char[], stride char* vs s32*, volatile double injection (test_wip auto [dummy] still DIFF), flags -fno-schedule-insns etc - no gain, remains DIFF (<50%)
// WANT vs GOT: DIFF (<50% masked, first 0x30 bytes already mismatch on stfd count and lbz vs lwz at 0x15A0)
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.7% ([3]rev->2.5% [4]rev->2.7%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -Os
extern char lbl_802AD72C[];
extern f32 lbl_802AD738;
extern f32 lbl_802AD73C;
extern f32 lbl_802AD740;
extern f32 lbl_802AD744;
extern char lbl_80303150[];
static s32 sp88;
static s32 sp90;

void fn_801DFE50(Unk_7C6AB1BB *arg0) {
    void *sp90;
    void *sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    s32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f29;
    f32 temp_f29_2;
    f32 temp_f2;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f5;
    f32 temp_f6;
    f32 temp_f7;
    f32 temp_f8;
    f32 temp_f9;
    f32 var_f13;
    f32 var_f1;
    f32 var_f25;
    f32 var_f30;
    s32 temp_r11;
    s32 temp_r27;
    s32 temp_r30;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r28;
    void *temp_r26;
    Unk_DB0E2BAB *temp_r30_2;
    CStruct *temp_r31;
    CStruct *temp_r31_2;
    CStruct *temp_r31_3;
    CStruct *temp_r31_4;
    CStruct *temp_r31_5;
    CStruct *temp_r31_6;
    Unk_DB0E2BAB *temp_r31_7;
    void *temp_r3;
    void *temp_r9;
    Unk_C7387A53 *temp_r9_2;
    Unk_90685748 *temp_r9_3;
    Unk_C7387A53 *temp_r9_4;

    temp_r11 = ((Unk_BCBAA2B5 *)arg0)->unk0x3D8;
    temp_r26 = arg0->unk0xC;
    temp_r27 = ((Unk_BCBAA2B5 *)arg0)->unk0x15A0 + 0x24;
    if (temp_r11 == 0) {
        temp_r9 = *((s32 *)&arg0->unk0x15BC);
        if ((s32) ((Unk_C7387A53 *)temp_r9)->unk0xAC != 0) {
            temp_r31 = temp_r9 + 0x90;
            if ((s32) temp_r31->unk0x4 != 0) {
                temp_r31->unk0x4 = temp_r11;
                temp_r31->unk0x8 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
            }
        }
        var_f25 = *(f32 *)&lbl_802AD72C;
        var_r28 = 0;
        temp_r30 = *(char *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0x118);
        if (temp_r30 == 0) {
            temp_r31_2 = temp_r27 + 0x4C;
            if ((s32) temp_r31_2->unk0x4 != 0) {
                var_r28 = fn_800AA02C(temp_r31_2);
                var_f25 = fn_801417B8(arg0->unk0xC, QB_PHYSICS_AIR_ROTATION_STAT);
                if ((f32) (f64) var_r28 > fn_8014030C(QB_SKATER_AUTOTURN_CANCEL_TIME, 1, temp_r26)) {
                    temp_r31_3 = arg0->unk0x15BC + 0x90;
                    if ((s32) temp_r31_3->unk0x4 != 0) {
                        temp_r31_3->unk0x8 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
                        temp_r31_3->unk0x4 = temp_r30;
                    }
                }
            }
            temp_r31_4 = temp_r27 + 0x70;
            if ((s32) temp_r31_4->unk0x4 != 0) {
                var_f25 = -fn_801417B8(arg0->unk0xC, QB_PHYSICS_AIR_ROTATION_STAT);
                var_r28 = fn_800AA02C(temp_r31_4);
                if ((f32) (f64) var_r28 > fn_8014030C(QB_SKATER_AUTOTURN_CANCEL_TIME, 1, temp_r26)) {
                    temp_r31_5 = arg0->unk0x15BC + 0x90;
                    if ((s32) temp_r31_5->unk0x4 != 0) {
                        temp_r31_5->unk0x4 = 0;
                        temp_r31_5->unk0x8 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
                    }
                }
            }
            temp_f31 = fn_8014030C(QB_PHYSICS_AIR_NO_ROTATE_TIME, 1, temp_r26);
            temp_f1 = fn_8014030C(QB_PHYSICS_AIR_RAMP_ROTATE_TIME, 1, temp_r26);
            temp_f0 = (f32) (f64) var_r28;
            0;
            if (0 != 0) {
                var_f25 = *(s32 *)&lbl_802AD72C;
            }
            if (temp_f0 < temp_f1) {
                var_f25 = (var_f25 * (temp_f0 - temp_f31)) / (temp_f1 - temp_f31);
            }
        }
        temp_f28 = *(s32 *)&lbl_802AD72C;
        if (var_f25 == temp_f28) {
            temp_r9_2 = *((s32 *)&arg0->unk0x15BC);
            if (((s32) temp_r9_2->unk0x40 != 0) && ((s32) temp_r9_2->unk0x94 != 0)) {
                temp_f29 = lbl_802AD73C;
                temp_f0_2 = *(char *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x9C);
                var_f30 = lbl_802AD738;
                var_f13 = temp_f0_2;
                if (temp_f0_2 > temp_f29) {
                    var_f13 = temp_f29;
                }
                var_f1 = var_f13;
                if (var_f13 < var_f30) {
                    var_f1 = var_f30;
                }
                temp_f31_2 = acosf(var_f1);
                if (temp_f31_2 < (fn_8014030C(QB_SKATER_AUTOTURN_VERT_ANGLE, 1, temp_r26) * lbl_802AD740)) {
                    goto block_30;
                }
                temp_r3 = arg0->unk0xC;
                temp_f1_2 = fn_80006094(temp_r3 + 0x98, (char *)arg0 + 0x2C8, temp_r3 + 0x88);
                if (!(temp_f1_2 < temp_f28)) {
                    var_f30 = temp_f29;
                }
                temp_f12 = ((Unk_BCBAA2B5 *)arg0)->unk0x94;
                var_f25 = var_f30 * fn_8014030C(QB_SKATER_AUTOTURN_SPEED, 1, temp_r26);
                if (fabs(var_f25 * temp_f12) > fabs(temp_f1_2)) {
                    var_f25 = temp_f1_2 / temp_f12;
block_30:
                    temp_r31_6 = arg0->unk0x15BC + 0x90;
                    if ((s32) temp_r31_6->unk0x4 != 0) {
                        temp_r31_6->unk0x4 = 0;
                        temp_r31_6->unk0x8 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
                    }
                }
            }
        }
        temp_f0_3 = *(s32 *)&lbl_802AD72C;
        if (var_f25 != temp_f0_3) {
            ((Unk_BCBAA2B5 *)arg0)->unk0x424 = (s32) (var_f25 > temp_f0_3);
            var_ctr = 4;
            temp_f25 = var_f25 * ((Unk_BCBAA2B5 *)arg0)->unk0x94;
            temp_r31_7 = *((char *)&arg0->unk0xC) + 0x78;
            temp_r30_2 = (char *)arg0 + 0x20;
            do {
                var_ctr -= 1;
            } while (var_ctr != 0);
            sp88 = fn_80003EB0(&sp8, temp_f25);
            ((Unk_59AB5482 *)&sp88)->unk0x4 = temp_r31_7;
            var_ctr_2 = 4;
            sp48 = (((Unk_DB0E2BAB *)sp88)->unk0xC * temp_r31_7->unk0x30) + ((((Unk_DB0E2BAB *)sp88)->unk0x8 * temp_r31_7->unk0x20) + ((((Unk_DB0E2BAB *)sp88)->unk0x0 * temp_r31_7->unk0x0) + (((Unk_DB0E2BAB *)sp88)->unk0x4 * temp_r31_7->unk0x10)));
            sp4C = (((Unk_DB0E2BAB *)sp88)->unk0xC * temp_r31_7->unk0x34) + ((((Unk_DB0E2BAB *)sp88)->unk0x8 * temp_r31_7->unk0x24) + ((((Unk_DB0E2BAB *)sp88)->unk0x0 * temp_r31_7->unk0x4) + (((Unk_DB0E2BAB *)sp88)->unk0x4 * temp_r31_7->unk0x14)));
            sp50 = (((Unk_DB0E2BAB *)sp88)->unk0xC * temp_r31_7->unk0x38) + ((((Unk_DB0E2BAB *)sp88)->unk0x8 * temp_r31_7->unk0x28) + ((((Unk_DB0E2BAB *)sp88)->unk0x0 * temp_r31_7->unk0x8) + (((Unk_DB0E2BAB *)sp88)->unk0x4 * temp_r31_7->unk0x18)));
            sp54 = (((Unk_DB0E2BAB *)sp88)->unk0xC * temp_r31_7->unk0x3C) + ((((Unk_DB0E2BAB *)sp88)->unk0x8 * temp_r31_7->unk0x2C) + ((((Unk_DB0E2BAB *)sp88)->unk0x0 * temp_r31_7->unk0xC) + (((Unk_DB0E2BAB *)sp88)->unk0x4 * temp_r31_7->unk0x1C)));
            sp58 = (((Unk_DB0E2BAB *)sp88)->unk0x1C * temp_r31_7->unk0x30) + ((((Unk_DB0E2BAB *)sp88)->unk0x18 * temp_r31_7->unk0x20) + ((((Unk_DB0E2BAB *)sp88)->unk0x10 * temp_r31_7->unk0x0) + (((Unk_DB0E2BAB *)sp88)->unk0x14 * temp_r31_7->unk0x10)));
            sp5C = (((Unk_DB0E2BAB *)sp88)->unk0x1C * temp_r31_7->unk0x34) + ((((Unk_DB0E2BAB *)sp88)->unk0x18 * temp_r31_7->unk0x24) + ((((Unk_DB0E2BAB *)sp88)->unk0x10 * temp_r31_7->unk0x4) + (((Unk_DB0E2BAB *)sp88)->unk0x14 * temp_r31_7->unk0x14)));
            sp60 = (((Unk_DB0E2BAB *)sp88)->unk0x1C * temp_r31_7->unk0x38) + ((((Unk_DB0E2BAB *)sp88)->unk0x18 * temp_r31_7->unk0x28) + ((((Unk_DB0E2BAB *)sp88)->unk0x10 * temp_r31_7->unk0x8) + (((Unk_DB0E2BAB *)sp88)->unk0x14 * temp_r31_7->unk0x18)));
            sp64 = (((Unk_DB0E2BAB *)sp88)->unk0x1C * temp_r31_7->unk0x3C) + ((((Unk_DB0E2BAB *)sp88)->unk0x18 * temp_r31_7->unk0x2C) + ((((Unk_DB0E2BAB *)sp88)->unk0x10 * temp_r31_7->unk0xC) + (((Unk_DB0E2BAB *)sp88)->unk0x14 * temp_r31_7->unk0x1C)));
            sp68 = (((Unk_DB0E2BAB *)sp88)->unk0x2C * temp_r31_7->unk0x30) + ((((Unk_DB0E2BAB *)sp88)->unk0x28 * temp_r31_7->unk0x20) + ((((Unk_DB0E2BAB *)sp88)->unk0x20 * temp_r31_7->unk0x0) + (((Unk_DB0E2BAB *)sp88)->unk0x24 * temp_r31_7->unk0x10)));
            sp6C = (((Unk_DB0E2BAB *)sp88)->unk0x2C * temp_r31_7->unk0x34) + ((((Unk_DB0E2BAB *)sp88)->unk0x28 * temp_r31_7->unk0x24) + ((((Unk_DB0E2BAB *)sp88)->unk0x20 * temp_r31_7->unk0x4) + (((Unk_DB0E2BAB *)sp88)->unk0x24 * temp_r31_7->unk0x14)));
            sp70 = (((Unk_DB0E2BAB *)sp88)->unk0x2C * temp_r31_7->unk0x38) + ((((Unk_DB0E2BAB *)sp88)->unk0x28 * temp_r31_7->unk0x28) + ((((Unk_DB0E2BAB *)sp88)->unk0x20 * temp_r31_7->unk0x8) + (((Unk_DB0E2BAB *)sp88)->unk0x24 * temp_r31_7->unk0x18)));
            sp74 = (((Unk_DB0E2BAB *)sp88)->unk0x2C * temp_r31_7->unk0x3C) + ((((Unk_DB0E2BAB *)sp88)->unk0x28 * temp_r31_7->unk0x2C) + ((((Unk_DB0E2BAB *)sp88)->unk0x20 * temp_r31_7->unk0xC) + (((Unk_DB0E2BAB *)sp88)->unk0x24 * temp_r31_7->unk0x1C)));
            sp78 = (((Unk_DB0E2BAB *)sp88)->unk0x3C * temp_r31_7->unk0x30) + ((((Unk_DB0E2BAB *)sp88)->unk0x38 * temp_r31_7->unk0x20) + ((((Unk_DB0E2BAB *)sp88)->unk0x30 * temp_r31_7->unk0x0) + (((Unk_DB0E2BAB *)sp88)->unk0x34 * temp_r31_7->unk0x10)));
            sp7C = (((Unk_DB0E2BAB *)sp88)->unk0x3C * temp_r31_7->unk0x34) + ((((Unk_DB0E2BAB *)sp88)->unk0x38 * temp_r31_7->unk0x24) + ((((Unk_DB0E2BAB *)sp88)->unk0x30 * temp_r31_7->unk0x4) + (((Unk_DB0E2BAB *)sp88)->unk0x34 * temp_r31_7->unk0x14)));
            sp80 = (((Unk_DB0E2BAB *)sp88)->unk0x3C * temp_r31_7->unk0x38) + ((((Unk_DB0E2BAB *)sp88)->unk0x38 * temp_r31_7->unk0x28) + ((((Unk_DB0E2BAB *)sp88)->unk0x30 * temp_r31_7->unk0x8) + (((Unk_DB0E2BAB *)sp88)->unk0x34 * temp_r31_7->unk0x18)));
            sp84 = (((Unk_DB0E2BAB *)sp88)->unk0x3C * temp_r31_7->unk0x3C) + ((((Unk_DB0E2BAB *)sp88)->unk0x38 * temp_r31_7->unk0x2C) + ((((Unk_DB0E2BAB *)sp88)->unk0x30 * temp_r31_7->unk0xC) + (((Unk_DB0E2BAB *)sp88)->unk0x34 * temp_r31_7->unk0x1C)));
            0;
            0;
            0;
            0;
            0;
            0;
            do {
                var_ctr_2 -= 1;
            } while (var_ctr_2 != 0);
            sp90 = fn_80003EB0(&sp8, temp_f25);
            ((Unk_59AB5482 *)&sp90)->unk0x4 = temp_r30_2;
            temp_f27 = temp_r30_2->unk0x10;
            temp_f26 = ((Unk_BCBAA2B5 *)arg0)->unk0x20;
            temp_f31_3 = temp_r30_2->unk0x20;
            temp_f1_3 = temp_r30_2->unk0x30;
            temp_f30 = temp_r30_2->unk0x14;
            temp_f29_2 = temp_r30_2->unk0x4;
            sp48 = (((Unk_DB0E2BAB *)sp90)->unk0xC * temp_f1_3) + ((((Unk_DB0E2BAB *)sp90)->unk0x8 * temp_f31_3) + ((((Unk_DB0E2BAB *)sp90)->unk0x0 * temp_f26) + (((Unk_DB0E2BAB *)sp90)->unk0x4 * temp_f27)));
            temp_f28_2 = temp_r30_2->unk0x24;
            temp_f5 = temp_r30_2->unk0x34;
            temp_f4 = temp_r30_2->unk0x18;
            temp_f3 = temp_r30_2->unk0x8;
            sp4C = (((Unk_DB0E2BAB *)sp90)->unk0xC * temp_f5) + ((((Unk_DB0E2BAB *)sp90)->unk0x8 * temp_f28_2) + ((((Unk_DB0E2BAB *)sp90)->unk0x0 * temp_f29_2) + (((Unk_DB0E2BAB *)sp90)->unk0x4 * temp_f30)));
            temp_f2 = temp_r30_2->unk0x28;
            temp_f9 = temp_r30_2->unk0x38;
            temp_f8 = temp_r30_2->unk0x1C;
            temp_f7 = temp_r30_2->unk0xC;
            sp50 = (((Unk_DB0E2BAB *)sp90)->unk0xC * temp_f9) + ((((Unk_DB0E2BAB *)sp90)->unk0x8 * temp_f2) + ((((Unk_DB0E2BAB *)sp90)->unk0x0 * temp_f3) + (((Unk_DB0E2BAB *)sp90)->unk0x4 * temp_f4)));
            temp_f6 = temp_r30_2->unk0x2C;
            temp_f10 = temp_r30_2->unk0x3C;
            sp54 = (((Unk_DB0E2BAB *)sp90)->unk0xC * temp_f10) + ((((Unk_DB0E2BAB *)sp90)->unk0x8 * temp_f6) + ((((Unk_DB0E2BAB *)sp90)->unk0x0 * temp_f7) + (((Unk_DB0E2BAB *)sp90)->unk0x4 * temp_f8)));
            sp58 = (((Unk_DB0E2BAB *)sp90)->unk0x1C * temp_f1_3) + ((((Unk_DB0E2BAB *)sp90)->unk0x18 * temp_f31_3) + ((((Unk_DB0E2BAB *)sp90)->unk0x10 * temp_f26) + (((Unk_DB0E2BAB *)sp90)->unk0x14 * temp_f27)));
            sp5C = (((Unk_DB0E2BAB *)sp90)->unk0x1C * temp_f5) + ((((Unk_DB0E2BAB *)sp90)->unk0x18 * temp_f28_2) + ((((Unk_DB0E2BAB *)sp90)->unk0x10 * temp_f29_2) + (((Unk_DB0E2BAB *)sp90)->unk0x14 * temp_f30)));
            sp60 = (((Unk_DB0E2BAB *)sp90)->unk0x1C * temp_f9) + ((((Unk_DB0E2BAB *)sp90)->unk0x18 * temp_f2) + ((((Unk_DB0E2BAB *)sp90)->unk0x10 * temp_f3) + (((Unk_DB0E2BAB *)sp90)->unk0x14 * temp_f4)));
            sp64 = (((Unk_DB0E2BAB *)sp90)->unk0x1C * temp_f10) + ((((Unk_DB0E2BAB *)sp90)->unk0x18 * temp_f6) + ((((Unk_DB0E2BAB *)sp90)->unk0x10 * temp_f7) + (((Unk_DB0E2BAB *)sp90)->unk0x14 * temp_f8)));
            sp68 = (((Unk_DB0E2BAB *)sp90)->unk0x2C * temp_f1_3) + ((((Unk_DB0E2BAB *)sp90)->unk0x28 * temp_f31_3) + ((((Unk_DB0E2BAB *)sp90)->unk0x20 * temp_f26) + (((Unk_DB0E2BAB *)sp90)->unk0x24 * temp_f27)));
            sp6C = (((Unk_DB0E2BAB *)sp90)->unk0x2C * temp_f5) + ((((Unk_DB0E2BAB *)sp90)->unk0x28 * temp_f28_2) + ((((Unk_DB0E2BAB *)sp90)->unk0x20 * temp_f29_2) + (((Unk_DB0E2BAB *)sp90)->unk0x24 * temp_f30)));
            sp70 = (((Unk_DB0E2BAB *)sp90)->unk0x2C * temp_f9) + ((((Unk_DB0E2BAB *)sp90)->unk0x28 * temp_f2) + ((((Unk_DB0E2BAB *)sp90)->unk0x20 * temp_f3) + (((Unk_DB0E2BAB *)sp90)->unk0x24 * temp_f4)));
            sp74 = (((Unk_DB0E2BAB *)sp90)->unk0x2C * temp_f10) + ((((Unk_DB0E2BAB *)sp90)->unk0x28 * temp_f6) + ((((Unk_DB0E2BAB *)sp90)->unk0x20 * temp_f7) + (((Unk_DB0E2BAB *)sp90)->unk0x24 * temp_f8)));
            sp78 = (((Unk_DB0E2BAB *)sp90)->unk0x3C * temp_f1_3) + ((((Unk_DB0E2BAB *)sp90)->unk0x38 * temp_f31_3) + ((((Unk_DB0E2BAB *)sp90)->unk0x30 * temp_f26) + (((Unk_DB0E2BAB *)sp90)->unk0x34 * temp_f27)));
            sp7C = (((Unk_DB0E2BAB *)sp90)->unk0x3C * temp_f5) + ((((Unk_DB0E2BAB *)sp90)->unk0x38 * temp_f28_2) + ((((Unk_DB0E2BAB *)sp90)->unk0x30 * temp_f29_2) + (((Unk_DB0E2BAB *)sp90)->unk0x34 * temp_f30)));
            sp80 = (((Unk_DB0E2BAB *)sp90)->unk0x3C * temp_f9) + ((((Unk_DB0E2BAB *)sp90)->unk0x38 * temp_f2) + ((((Unk_DB0E2BAB *)sp90)->unk0x30 * temp_f3) + (((Unk_DB0E2BAB *)sp90)->unk0x34 * temp_f4)));
            sp84 = (((Unk_DB0E2BAB *)sp90)->unk0x3C * temp_f10) + ((((Unk_DB0E2BAB *)sp90)->unk0x38 * temp_f6) + ((((Unk_DB0E2BAB *)sp90)->unk0x30 * temp_f7) + (((Unk_DB0E2BAB *)sp90)->unk0x34 * temp_f8)));
            0;
            0;
            0;
            0;
            0;
            0;
            temp_r9_3 = ((Unk_BCBAA2B5 *)arg0)->unk0x15AC;
            temp_r9_3->unk0x13F0 = (f32) ((temp_f25 * lbl_802AD744) + temp_r9_3->unk0x13F0);
            temp_r9_4 = *((s32 *)&arg0->unk0x15BC);
            if (((s32) temp_r9_4->unk0x40 != 0) && ((s32) temp_r9_4->unk0xAC == 0)) {
                temp_f31_4 = fabs(*(char *)(*(s32 *)((char *)((char *)arg0) + 0x15AC) + 0x13F0));
                fn_8014030C(QB_SPIN_COUNT_SLOP, 1, temp_r26);
                0;
                if (0 != 0) {
                    fn_8017F5B0(*(char *)(*(s32 *)((char *)((char *)arg0) + 0x15B4) + 0x1C), (s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15AC) + 0x13F0));
                }
            } else {
                fn_8017F5B0(*(char *)(*(s32 *)((char *)((char *)arg0) + 0x15B4) + 0x1C), (s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15AC) + 0x13F0));
            }
        }
    }
}
