// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80031FC4-0x8003204C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} Unk_80031FC4_vt;
void fn_80031FC4(Unk_C7387A53 *arg0) {
    CStruct *temp_r9;
    CStruct *temp_r9_2;
    Unk_80031FC4_vt *temp_r9_3;
    void *var_r11;
    void *var_r31;

    temp_r9 = arg0->unk0x24;
    if ((s32) temp_r9->unk0x4 == -1) {
        var_r11 = NULL;
    } else {
        var_r11 = temp_r9;
    }
    if (var_r11 != NULL) {
        do {
            temp_r9_2 = ((Unk_C8FEE62D *)var_r11)->unk0xC;
            if ((s32) temp_r9_2->unk0x4 == -1) {
                var_r31 = NULL;
            } else {
                var_r31 = temp_r9_2;
            }
            if (var_r11 != NULL) {
                temp_r9_3 = (Unk_80031FC4_vt *) ((Unk_C8FEE62D *)var_r11)->unk0x14;
                ((s32 (*)(void *, s32))temp_r9_3->unk0xC)(var_r11 + temp_r9_3->unk0x8, 3);
            }
            var_r11 = var_r31;
        } while (var_r11 != NULL);
    }
}
