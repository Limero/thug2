// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80059ACC-0x80059BB8 (236B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80300460;
extern s32 lbl_803008A0;
extern s32 lbl_803008A4;
extern s32 lbl_803008A8;
extern s32 lbl_803008AC;
extern s32 lbl_803008B0;
extern bool lbl_803008B4;
void fn_800599B0(void);
void fn_800F0F84(s32, s32);
s32 fn_800F0AFC(void);
void fn_8005AC44(s32, CStruct *);
void fn_80059ACC(void) {
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r9;
    s32 var_r31;

    if ((lbl_803008A0 != 0) && (lbl_80300460 == 0)) {
        temp_r10 = lbl_803008B0;
        temp_r11 = lbl_803008AC;
        if (temp_r10 > temp_r11) {
            fn_800599B0();
            return;
        }
        if (temp_r11 != 0) {
            var_r31 = (s32) (lbl_803008A4 * temp_r10) / temp_r11;
        } else {
            var_r31 = lbl_803008A4;
        }
        if (lbl_803008A8 < var_r31) {
            do {
                fn_800F0F84(*((s32 *)((char *)lbl_803008A0 + (lbl_803008A8 * 4))), 1);
                fn_8005AC44(fn_800F0AFC(), lbl_803008B4);
                temp_r9 = lbl_803008A8 + 1;
                lbl_803008A8 = temp_r9;
            } while (temp_r9 < var_r31);
        }
        lbl_803008B0 = (s32) (lbl_803008B0 + 1);
    }
}
