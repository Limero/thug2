// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801980C4-0x80198190 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.

#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x8];
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} Unk_801980C4_vt;
void fn_801980C4(CScript *arg0) {
    register CStruct *temp_r11 __asm__("r11");
    void *temp_r11_2;
    register CStruct *temp_r9 __asm__("r9");
    Unk_801980C4_vt *temp_r9_2;
    Unk_801980C4_vt *temp_r9_3;
    void *var_r30;
    void *var_r31;

    temp_r9 = arg0->unk0x18;
    {
        s32 t4 = (s32) temp_r9->unk0x4;

        var_r31 = temp_r9;
        if (t4 == -1) {
            var_r31 = NULL;
        }
    }
    if (var_r31 != NULL) {
        do {
            temp_r11 = ((Unk_C8FEE62D *)var_r31)->unk0xC;
            var_r30 = temp_r11;
            if ((s32) temp_r11->unk0x4 == -1) {
                var_r30 = NULL;
            }
            *(s32 *)(*(s32 *)((char *)((char *)var_r31) + 0x10) + 0xC) = temp_r11;
            *(s32 *)(*(s32 *)((char *)((char *)var_r31) + 0xC) + 0x10) =  ((Unk_C8FEE62D *)var_r31)->unk0x10;
            ((Unk_C8FEE62D *)var_r31)->unk0xC = var_r31;
            temp_r11_2 = ((Unk_C8FEE62D *)var_r31)->unk0x4;
            ((Unk_C8FEE62D *)var_r31)->unk0x10 = var_r31;
            if (temp_r11_2 != NULL) {
                temp_r9_2 = ((CStruct *)temp_r11_2)->unk0x4;
                ((s32 (*)(void *, s32))temp_r9_2->unk0xC)(temp_r11_2 + temp_r9_2->unk0x8, 3);
            }
            if (var_r31 != NULL) {
                temp_r9_3 = ((Unk_C8FEE62D *)var_r31)->unk0x14;
                ((s32 (*)(void *, s32))temp_r9_3->unk0xC)(var_r31 + temp_r9_3->unk0x8, 3);
            }
            var_r31 = var_r30;
        } while (var_r31 != NULL);
    }
}
