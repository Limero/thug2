// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010631C-0x801063B4 (152B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_803810A4;
void fn_8010631C(s32 arg0) {
    CStruct *temp_r9;
    Unk_F5317C5D *temp_r9_2;
    void *var_r11;
    void *var_r31;

    var_r11 = lbl_803810A4;
    if ((s32) ((Unk_C8FEE62D *)var_r11)->unk0x4 == -1) {
        var_r11 = NULL;
    }
    if (var_r11 != NULL) {
        do {
            temp_r9 = ((Unk_C8FEE62D *)var_r11)->unk0xC;
            if ((s32) temp_r9->unk0x4 == -1) {
                var_r31 = NULL;
            } else {
                var_r31 = temp_r9;
            }
            if (((s32) ((Unk_C8FEE62D *)var_r11)->unk0x4 == arg0) && (var_r11 != NULL)) {
                temp_r9_2 = ((Unk_C8FEE62D *)var_r11)->unk0x14;
                ((s32 (*)(void *, s32))temp_r9_2->unk0xC)(var_r11 + temp_r9_2->unk0x8, 3);
            }
            var_r11 = var_r31;
        } while (var_r11 != NULL);
    }
}
