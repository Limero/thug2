// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022E16C-0x8022E258 (236B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80056174(s32, s32);
void fn_80057298(s32);
s32 fn_801FC0E0(void);
void fn_801FA5E4(s32);
void fn_801FA628(s32);
void fn_801FA66C(s32);
s32 *fn_80238970(void);
void fn_8022F184(s32);
void fn_8022D4C4(s32);
void fn_8022DF2C(s32, s32);
s32 fn_80240C80(s32);
void fn_802403A0(s32);
extern char lbl_802B05C8[];
extern s32 lbl_80305FF4;
void fn_8022E16C(Unk_C8FEE62D *arg0) {
    CStruct *var_r30;
    Unk_9994C3F5 *var_r30_2;

    var_r30 = arg0->unk0x8;
    lbl_80305FF4 = 0;
    if (var_r30 != NULL) {
        do {
            fn_80056174(arg0->unk0x14, var_r30->unk0x0);
            var_r30 = var_r30->unk0x8;
        } while (var_r30 != NULL);
    }
    fn_801FA5E4(fn_801FC0E0());
    fn_801FA628(fn_801FC0E0());
    fn_8022F184(*(s32 *)fn_80238970());
    lbl_80305FF4 = 1;
    fn_80057298(arg0->unk0x14);
    var_r30_2 = arg0->unk0x8;
    if (var_r30_2 != NULL) {
        do {
            fn_8022DF2C(arg0, fn_80240C80(var_r30_2));
            var_r30_2 = var_r30_2->unk0x8;
        } while (var_r30_2 != NULL);
    }
    fn_8022D4C4(arg0);
    lbl_80305FF4 = 0;
    fn_801FA66C(fn_801FC0E0());
    lbl_80305FF4 = 1;
    fn_8022D4C4(arg0);
    fn_802403A0((s32)lbl_802B05C8);
}
