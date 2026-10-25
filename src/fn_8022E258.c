// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022E258-0x8022E33C (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_80240C80(void *);
void fn_8022DD54(void *, s32, s32);
void fn_8022DF2C(void *, void *);
void fn_8022D4C4(void *);
extern s32 lbl_80305FF4;
void fn_8022E258(Unk_9994C3F5 *arg0) {
    s32 var_r11;
    s32 var_r11_2;
    void *temp_r3;
    CStruct *var_r31;
    Unk_9994C3F5 *var_r31_2;

    var_r31 = (CStruct *)arg0->unk0x8;
    lbl_80305FF4 = 0;
    if (var_r31 != NULL) {
        do {
            temp_r3 = fn_80240C80(var_r31);
            var_r11 = 1;
            if (!(*(s32 *)(*(s32 *)((char *)temp_r3 + 0x14) + 0x4) & 0x4000)) {
                var_r11 = 0;
            }
            if (var_r11 != 0) {
                fn_8022DD54(arg0, var_r31->unk0x0, var_r31->unk0x4);
            }
            var_r31 = (CStruct *)var_r31->unk0x8;
        } while (var_r31 != NULL);
    }
    var_r31_2 = (Unk_9994C3F5 *)arg0->unk0x8;
    if (var_r31_2 != NULL) {
        do {
            temp_r3 = fn_80240C80(var_r31_2);
            var_r11_2 = 1;
            if (!(*(s32 *)(*(s32 *)((char *)temp_r3 + 0x14) + 0x4) & 0x4000)) {
                var_r11_2 = 0;
            }
            if (var_r11_2 != 0) {
                fn_8022DF2C(arg0, temp_r3);
            }
            var_r31_2 = (Unk_9994C3F5 *)var_r31_2->unk0x8;
        } while (var_r31_2 != NULL);
    }
    lbl_80305FF4 = 1;
    fn_8022D4C4(arg0);
}
