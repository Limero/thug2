// WIP DRAFT (concrete attempt;)
// family=m2c range=0x80116518-0x801166CC size=436B
// PARKED: array-permutation candidate scored 12.8%; target allocation loop and optional callback path differ.
// UPDATED 2026-09-15 (e): 14.7% -> 18.3%. m2c invented a *symbol* call argument: it read the lis/addi pair that materialises a label address as an extra arg. tools/label_arg_scan.py automated the A/B; keep the best body.
#include "types.h"
#include "structs.h"
extern char lbl_8029D1F0[];
extern char lbl_8029D210[];
static s32 sp8;

s32 ScriptPermuteArray(CStruct *arg0, CScript *arg1) {
    s32 sp14;
    s32 spC;
    void *sp8;
    s32 *temp_r31;
    s32 temp_r0;
    s32 temp_r25;
    s32 temp_r28;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 var_r29;
    s32 var_r3;
    void *var_r26;
    CStruct *var_r31;

    sp14 = 0;
    sp8 = NULL;
    fn_80128610(0x8029D1E8, &sp8, 0);
    if (sp8 == NULL) {
        0;
        return 0;
    }
    var_r31 = sp8;
    var_r26 = NULL;
    temp_r3 = fn_80128A90(arg0, (s32)lbl_8029D1F0) ^ 1;
    spC = 0;
    0;
    if (temp_r3 != 0) {
        GetChecksum_4(arg0, 0x8029D200, &spC, 0);
        var_r3 = 0;
        if (spC != 0) {
            fn_8003E7CC(0xC);
            var_r26 = fn_80128F94(arg0);
            var_r31 = var_r26;
            fn_80126E28(sp8);
            goto block_5;
        }
    } else {
block_5:
        temp_r28 = var_r31->unk0x4;
        0;
        if (temp_r28 != 0) {
            temp_r0 = temp_r28 * 0xA;
            temp_r31 = fn_801291FC(var_r31);
            temp_r25 = *(s32 *)((s32 *)((temp_r28 * 4) + temp_r31) - 0x4);
            if (temp_r0 > 0) {
                var_r29 = temp_r0;
                do {
                    temp_r30 = Mth_Rnd(temp_r28);
                    temp_r3_2 = Mth_Rnd(temp_r28);
                    var_r29 -= 1;
                    temp_r9 = temp_r31[temp_r30];
                    temp_r31[temp_r30] = temp_r31[temp_r3_2];
                    temp_r31[temp_r3_2] = temp_r9;
                } while (var_r29 != 0);
            }
            if ((fn_80128A90(arg0, arg0) != 0) && (temp_r28 > 1) && ((s32) *((s32 *)temp_r31) == temp_r25)) {
                temp_r3_3 = Mth_Rnd(temp_r28 - 1) + 1;
                temp_r9_2 = *((s32 *)temp_r31);
                *((s32 *)temp_r31) = temp_r31[temp_r3_3];
                temp_r31[temp_r3_3] = temp_r9_2;
            }
        }
        if (0) {
            AddArrayPointer(arg1->unk0x18, spC, var_r26);
        }
        var_r3 = 1;
    }
    0;
    return var_r3;
}
