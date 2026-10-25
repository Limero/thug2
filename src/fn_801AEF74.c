// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AEF74-0x801AF004 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801AEF74(void *arg0) {
    register void *obj_r30 __asm__("r30");
    register void *base_r10 __asm__("r10");
    register void *head_r31 __asm__("r31");
    Unk_0E2E8431 *temp_r9;
    CStruct *var_r9;
    void *var_r11;
    void *var_r11_2;

    obj_r30 = arg0;
    base_r10 = (char *)obj_r30 + 4;
    var_r9 = ((Unk_C7387A53 *)base_r10)->unk0xC;
    if ((s32)var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    var_r11 = var_r9;
    if (var_r11 != NULL) {
        head_r31 = base_r10;
        do {
            temp_r9 = ((Unk_C8FEE62D *)var_r11)->unk0x14;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)(var_r11 + temp_r9->unk0x8, 3);
            temp_r9 = ((Unk_C7387A53 *)head_r31)->unk0xC;
            var_r11_2 = NULL;
            if ((s32)temp_r9->unk0x4 != -1) {
                var_r11_2 = temp_r9;
            }
            var_r11 = var_r11_2;
        } while (var_r11 != NULL);
    }
    *(s32 *)obj_r30 = 0;
}
