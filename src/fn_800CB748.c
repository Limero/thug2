// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CB748-0x800CB898 (336B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80299434;
void fn_80031390(Unk_C7387A53 *, f32, f32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_80128CE0(CStruct *, void *, void *, s32);
void fn_80128E34(CStruct *, void *, void *, s32);
bool fn_800CB748(Unk_C7387A53 *arg0, s32 arg1, CStruct *arg2) {
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    s32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    CStruct *temp_r9;
    register CStruct *var_r9 __asm__("r9");
    Unk_C7387A53 *var_r31;
    void *var_r30;
    register s32 id __asm__("r11");
    register s32 outer __asm__("r0");

    temp_r9 = arg0->unk0x38;
    sp8 = 0;
    if ((s32) temp_r9->unk0x4 == -1) {
        var_r30 = NULL;
    } else {
        var_r30 = temp_r9;
    }
    var_r31 = var_r30;
    fn_80128E34(arg2, QB_SUBSETID, &sp8, 0);
    outer = sp8;
    if (outer != 0) {
        if (var_r30 != NULL) {
            id = outer;
            __asm__("" : "+r"(id));
loop_5:
            if ((s32) var_r31->unk0x30 != id) {
                var_r9 = var_r31->unk0xC;
                if ((s32) var_r9->unk0x4 == -1) {
                    var_r9 = NULL;
                }
                var_r31 = var_r9;
                if (var_r31 == NULL) {

                } else {
                    goto loop_5;
                }
            } else {
                temp_f0 = lbl_80299434;
                spC = temp_f0;
                sp10 = temp_f0;
                GetFloat(arg2, QB_BLENDWEIGHT, &spC, 1);
                fn_80128CE0(arg2, QB_BLENDDURATION, &sp10, 0);
                fn_80031390(var_r31, spC, sp10);
            }
        }
    } else {
        temp_f0_2 = lbl_80299434;
        sp14 = temp_f0_2;
        sp18 = temp_f0_2;
        GetFloat(arg2, QB_BLENDWEIGHT, &sp14, 1);
        fn_80128CE0(arg2, QB_BLENDDURATION, &sp18, 0);
        fn_80031390(var_r30, sp14, sp18);
    }
    return true;
}
