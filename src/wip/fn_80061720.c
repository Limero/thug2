// WIP DRAFT — best measured DIFF 8.44% (object 948 B == want 948 B).
// family=m2c range=0x80061720-0x80061AD4 size=948B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-05. WHAT IT IS: a linked-list walk over
// arg0->unk0x10 that tests each node against a QuickBool criterion. A helper
// decodes a 3-float vector into a packed s32 (`fmadds` -> `fctiwz` ->
// `stfd 0x60(r1)` -> `lwz 0x64(r1)` -> `stb`, three times, 4th byte = 0xFF);
// that packed value + `sp24 = GetChecksum_2(arg1, QB_PART, ..) ^ QB_ALL` decides
// the match, which ends in an `mtlr`+`blrl` COM thunk. Three inner loops over
// QB_MATERIALS / QB_PASS arrays call fn_8005F148 and OR the results into r28.
// Blocker: 219 of 237 words differ. The FRAME is the first domino — want
// `stwu -0x98 / stfd f29-f31 / stmw r26,0x68 / stw lr,0x9c`; this draft emits
// `stwu -0x78 / stfd f29-f31 / stmw r24,0x40 / stw lr,0x7c`, i.e. 0x20 too
// small and one saved GPR short (want saves r26-r31, got r24-r31). The want's
// local map is sp8=0x08 sp10=0x10 sp18=0x18 sp20=0x20 sp24=0x24 sp28/2C/30=
// the 3 fn_80053D10 out-params sp34=0x34 (4B) sp38/3C/40/44 = the four QB
// out-pointers, plus an 8-byte fctiwz spill at 0x60 and 8-byte STRIDES at
// 0x08/0x10/0x18 that four `s32` locals cannot produce. Also note the want has
// NO crclr/crset anywhere; this draft emits four of them, which means some
// comparison in the body is being kept in a CR bit across a call — the
// `if (count > 0U) do{..}while(..)` guards around the two array loops are the
// prime suspects.
// FIXED THIS ROUND (semantic, both keep the 948 B size): the match test was
// `sp24 == node->unk0x8 || (sp24 ^ QB_ALL) == 0`, which is INVERTED — want is
// `cmpw r11,r0; beq MATCH; cmpwi r26,0; beq skip`, i.e. `|| (sp24^QB_ALL) != 0`
// (r26 is the `subfic/adde` boolean of `sp24 != QB_ALL`). 8.02% -> 8.44%.
// TRIED AND REVERTED (both scored WORSE, do not redo): rewriting the three
// m2c `var = 1; if (x == 0) var = 0;` bool folds as `var = (x != 0)` drops it to
// 7.17%, and flipping only their `var_r28 == 0` operand to `!= 0` drops it to
// 7.59% — even though want's `or r28, r0, r3` really is `(r28!=0)|(r3!=0)`.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80293EF8;
extern f32 lbl_80293EFC;
static s32 sp10;
static s32 sp38;
static s32 sp44;
static s32 sp8;

s32 fn_80061720(void *arg0, CStruct *arg1, f32 farg0, f32 farg1, f32 farg2) {
    void *sp44;
    s32 sp40;
    s32 sp3C;
    void *sp38;
    Unk_6677BDCE sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp18;
    CStruct *sp10;
    void *sp8;
    f32 temp_f8;
    f32 temp_f9;
    s32 temp_r26;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r28;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    u32 var_r31;
    u32 var_r31_2;
    CStruct *temp_r9;
    void *temp_r0;
    void *temp_r11;
    void *temp_r29;
    CStruct *temp_r7;
    Unk_C7387A53 *temp_r9_2;
    void *var_r9;

    GetChecksum_2(arg1, (s32 *)QB_PART, &sp24, 1);
    var_r28 = 0;
    fn_80053D10(&sp28, &sp2C, &sp30, farg0, farg1, farg2);
    temp_r7 = *(s32 *)( !(char *)arg0 + (s32)0x10);
    temp_f9 = lbl_80293EFC;
    temp_f8 = lbl_80293EF8;
    *((s8 *)&sp34) = (s8) ((sp28 * temp_f8) + temp_f9);
    var_r9 = NULL;
    sp34.unk0x1 = (s8) ((sp2C * temp_f8) + temp_f9);
    *(s32 *)((char *)&sp34 + 0x3) = 0xFF;
    sp34.unk0x2 = (s8) ((sp30 * temp_f8) + temp_f9);
    sp8 = temp_r7;
    temp_r26 = sp24 ^ QB_ALL;
    if (temp_r7 != NULL) {
        var_r9 = temp_r7->unk0x4;
    }
    sp10 = var_r9;
    if (var_r9 != temp_r7) {
        do {
            sp40 = 0;
            if (fn_8005F8E0(**((s32 * *)&sp10->unk0x0)) == 0) {
                temp_r9 = sp10->unk0x0;
                if ((sp24 == (s32) temp_r9->unk0x8) || (temp_r26 != 0)) {
                    temp_r11 = temp_r9->unk0x0;
                    var_r28 = 1;
                    sp18 = (s32) *((s8 *)&sp34);
                    temp_r9_2 = ((Unk_C8FEE62D *)temp_r11)->unk0x14;
                    ((s32 (*)(void *, void *))temp_r9_2->unk0x3C)(temp_r11 + temp_r9_2->unk0x38, &sp18);
                }
            } else if (GetArray(arg1, QB_MATERIALS, &sp38, 0) != 0) {
                var_r31 = 0U;
                if ((u32) *((u32 *)&((CStruct *)sp38)->unk0x4) > 0U) {
                    do {
                        temp_r30 = fn_80129528(sp38, var_r31);
                        GetChecksum_2(0, &sp3C, (s32 *)1);
                        GetInteger(temp_r30, 0, &sp40, 1);
                        sp20 = (s32) *((s8 *)&sp34);
                        temp_r3 = fn_8005F148(**((s32 * *)&sp10->unk0x0), sp3C, sp40, &sp20);
                        
                        var_r3 = 1;
                        if (temp_r3 == 0) {
                            var_r3 = 0;
                        }
                        var_r28 = ((var_r28 == 0) ) | var_r3;
                        var_r31 += 1;
                    } while (var_r31 < (u32) *((u32 *)&((CStruct *)sp38)->unk0x4));
                }
            } else if (GetChecksum_2(arg1, (s32 *)QB_MATERIAL, &sp3C, 0) != 0) {
                if (GetArray(arg1, QB_PASS, &sp44, 0) != 0) {
                    var_r31_2 = 0U;
                    if ((u32) *((u32 *)&((CStruct *)sp44)->unk0x4) > 0U) {
                        do {
                            sp20 = (s32) *((s8 *)&sp34);
                            temp_r29 = **((s32 * *)&sp10->unk0x0);
                            temp_r3_2 = fn_8005F148(temp_r29, sp3C, fn_801293FC(sp44, var_r31_2), &sp20);
                            var_r0_2 = 1;
                            if (var_r28 == 0) {
                                var_r0_2 = 0;
                            }
                            var_r3_2 = 1;
                            if (temp_r3_2 == 0) {
                                var_r3_2 = 0;
                            }
                            var_r28 = var_r0_2 | var_r3_2;
                            var_r31_2 += 1;
                        } while (var_r31_2 < (u32) *((u32 *)&((CStruct *)sp44)->unk0x4));
                    }
                } else if (GetInteger(arg1, QB_PASS, &sp40, 1) != 0) {
                    sp20 = (s32) *((s8 *)&sp34);
                    temp_r3_3 = fn_8005F148(**((s32 * *)&sp10->unk0x0), sp3C, sp40, &sp20);
                    var_r0_3 = 1;
                    if (var_r28 == 0) {
                        var_r0_3 = 0;
                    }
                    var_r3_3 = 1;
                    if (temp_r3_3 == 0) {
                        var_r3_3 = 0;
                    }
                    var_r28 = var_r0_3 | var_r3_3;
                }
            }
            temp_r0 = sp10->unk0x4;
            sp10 = temp_r0;
        } while (temp_r0 != sp8);
    }
    return var_r28;
}

// PARK-NOTE 2026-08-30: class-B M2C_CARRY bool-fold artifact resolved via
// recipe-100 equality rewrite — `(0 - X) + X + M2C_CARRY` -> `(X == 0)`
// (want's xor;subfic;adde idiom). Removes the .bss payload static.
