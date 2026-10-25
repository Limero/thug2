// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C26D8-0x801C27C8 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} Unk_801C26D8_vt;
void fn_801C26D8(Unk_C7387A53 *arg0) {
    CStruct *temp_r9;
    CStruct *temp_r9_2;
    Unk_801C26D8_vt *temp_r9_3;
    CStruct *temp_r9_4;
    CStruct *temp_r9_5;
    Unk_801C26D8_vt *temp_r9_6;
    void *var_r11;
    void *var_r11_2;
    void *var_r31;
    void *var_r31_2;
    void *var_r30;

    temp_r9 = arg0->unk0x28;
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
                temp_r9_3 = (Unk_801C26D8_vt *) ((Unk_C8FEE62D *)var_r11)->unk0x14;
                ((s32 (*)(void *, s32))temp_r9_3->unk0xC)(var_r11 + temp_r9_3->unk0x8, 3);
            }
            var_r11 = var_r31;
        } while (var_r11 != NULL);
    }
    var_r30 = (char *) arg0 + 0x34;
    temp_r9_4 = *(s32 *)((char *) var_r30 + 0xC);
    if ((s32) temp_r9_4->unk0x4 == -1) {
        var_r11_2 = NULL;
    } else {
        var_r11_2 = temp_r9_4;
    }
    if (var_r11_2 != NULL) {
        do {
            temp_r9_5 = ((Unk_C8FEE62D *)var_r11_2)->unk0xC;
            if ((s32) temp_r9_5->unk0x4 == -1) {
                var_r31_2 = NULL;
            } else {
                var_r31_2 = temp_r9_5;
            }
            if (var_r11_2 != NULL) {
                temp_r9_6 = (Unk_801C26D8_vt *) ((Unk_C8FEE62D *)var_r11_2)->unk0x14;
                ((s32 (*)(void *, s32))temp_r9_6->unk0xC)(var_r11_2 + temp_r9_6->unk0x8, 3);
            }
            var_r11_2 = var_r31_2;
        } while (var_r11_2 != NULL);
    }
}
