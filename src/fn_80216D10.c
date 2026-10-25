// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80216D10-0x80216DC8 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct Vtbl_16D10 {
    char pad0x0[0x8];
    s16 unk0x8;
    char pad0xA[0x2];
    s32 (*unk0xC)(void *, s32);
} Vtbl_16D10;
typedef struct Node_16D10 {
    s32 unk0x0;
    struct Node_16D10 *unk0x4;
    s32 unk0x8;
    struct Node_16D10 *unk0xC;
    s32 unk0x10;
    Vtbl_16D10 *unk0x14;
} Node_16D10;
s32 fn_8013E098(s32, s32);
void fn_8022AABC(void *, s32);
void fn_80216D10(Unk_A7137CF0 *arg0) {
    Node_16D10 *temp_r30;
    Node_16D10 *temp_r9;
    Node_16D10 *temp_r9_2;
    Vtbl_16D10 *temp_r9_3;
    Node_16D10 *var_r29;
    Node_16D10 *var_r31;

    temp_r9 = (Node_16D10 *)arg0->unk0x154;
    if (temp_r9->unk0x4 == (Node_16D10 *)-1) {
        var_r31 = NULL;
    } else {
        var_r31 = temp_r9;
    }
    if (var_r31 != NULL) {
        do {
            temp_r9_2 = var_r31->unk0xC;
            if (temp_r9_2->unk0x4 == (Node_16D10 *)-1) {
                var_r29 = NULL;
            } else {
                var_r29 = temp_r9_2;
            }
            temp_r30 = var_r31->unk0x4;
            if ((s32) arg0->unk0x8 != 0) {
                fn_8013E098(arg0->unk0x8, (s32)temp_r30->unk0x14);
            }
            if (var_r31 != NULL) {
                temp_r9_3 = var_r31->unk0x14;
                temp_r9_3->unk0xC((char *)var_r31 + (s16)temp_r9_3->unk0x8, 3);
            }
            if (temp_r30 != NULL) {
                fn_8022AABC(temp_r30, 3);
            }
            var_r31 = var_r29;
        } while (var_r31 != NULL);
    }
}
