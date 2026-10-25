// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80139600-0x801396A4 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80139600(s32 arg0) {
    s32 var_r10;
    s32 f4;
    CStruct *temp_r9;
    CStruct *temp_r9_2;
    void *var_r11;
    void *var_r31;

    var_r10 = 0;
    do {
        var_r11 = *(s32 *)((char *)((var_r10 * 0x18) + arg0) + 0xC);
        f4 = (s32) ((Unk_C8FEE62D *)var_r11)->unk0x4;
        if (f4 == -1) {
            var_r11 = NULL;
        }
        if (var_r11 != NULL) {
            do {
                temp_r9 = ((Unk_C8FEE62D *)var_r11)->unk0xC;
                f4 = (s32) temp_r9->unk0x4;
                var_r31 = temp_r9;
                if (f4 == -1) {
                    var_r31 = NULL;
                }
                if (var_r11 != NULL) {
                    temp_r9_2 = ((Unk_C8FEE62D *)var_r11)->unk0x14;
                    ((s32 (*)(void *, s32))temp_r9_2->unk0xC)(var_r11 + *(s16 *)((char *)temp_r9_2 + 8), 3);
                }
                var_r11 = var_r31;
            } while (var_r11 != NULL);
        }
        var_r10 += 1;
    } while (var_r10 <= 0xFE);
}
