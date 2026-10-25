// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054F08-0x80054F98 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern CStruct *lbl_80364C28;
void fn_80054C6C(Unk_9D99273B *, s32);
void fn_8005D734(CStruct *);
void fn_80077610(s32);
bool fn_80054F08(void) {
    s32 temp_r31;
    s32 temp_r0;
    Unk_C7387A53 *temp_r3;
    CStruct *temp_r9;
    CStruct *var_r11;
    void *var_r30;

    var_r11 = lbl_80364C28;
    if ((s32) var_r11->unk0x4 == -1) {
        var_r11 = NULL;
    }
    if (var_r11 != NULL) {
        do {
            temp_r9 = var_r11->unk0xC;
            temp_r0 = (s32) temp_r9->unk0x4;
            var_r30 = temp_r9;
            if (temp_r0 == -1) {
                var_r30 = NULL;
            }
            temp_r3 = var_r11->unk0x4;
            temp_r31 = temp_r3->unk0x84;
            fn_80054C6C(temp_r3, 1);
            if (temp_r31 != 0) {
                fn_8005D734(temp_r31);
            }
            var_r11 = var_r30;
        } while (var_r11 != NULL);
    }
    fn_80077610(0);
    return true;
}
