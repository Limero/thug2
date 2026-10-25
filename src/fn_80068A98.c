// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80068A98-0x80068B58 (192B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80068A98(CStruct *arg0) {
    s32 temp_r0;
    void *temp_r11;
    Unk_C7387A53 *temp_r9;
    Unk_F5317C5D *temp_r9_2;
    void *var_r30;
    void *var_r31;
    void *var_r9;
    void *var_r9_2;

    temp_r9 = arg0->unk0x10;
    if (temp_r9 != NULL) {
        var_r9 = temp_r9->unk0xC;
        if ((s32) ((CStruct *)var_r9)->unk0x4 == -1) {
            var_r9 = NULL;
        }
        var_r30 = (var_r9 != NULL) ? var_r9 - 0xC : NULL;
        if (var_r30 != NULL) {
            do {
                temp_r11 = var_r30;
                var_r9_2 = ((Unk_AF849E78 *)temp_r11)->unk0x18;
                if ((s32) ((CStruct *)var_r9_2)->unk0x4 == -1) {
                    var_r9_2 = NULL;
                }
                var_r31 = (var_r9_2 != NULL) ? var_r9_2 - 0xC : NULL;
                var_r30 = var_r31;
                temp_r0 = ((Unk_AF849E78 *)temp_r11)->unk0x154;
                if ((temp_r0 == 0) && (temp_r11 != NULL)) {
                    temp_r9_2 = ((Unk_AF849E78 *)temp_r11)->unk0x8;
                    ((s32 (*)(void *, s32))temp_r9_2->unk0xC)(temp_r11 + temp_r9_2->unk0x8, 3);
                }
            } while (var_r31 != NULL);
        }
    }
}
