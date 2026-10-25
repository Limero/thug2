// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3090-0x800F30D4 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800F3090(void **arg0, Unk_C7387A53 *arg1) {
    void *temp_r0;

    temp_r0 = *arg0;
    if (temp_r0 != NULL) {
        arg1->unk0x30 = (s32)temp_r0;
        arg1->unk0x2C = *(s32 *)((char *)*arg0 + (s32)0x2C);
        *(s32 *)((char *)(*(s32 *)((char *)*arg0 + (s32)0x2C)) + (s32)0x30) = (s32)arg1;
        *(s32 *)((char *)*arg0 + (s32)0x2C) = (s32)arg1;
        return;
    }
    *arg0 = arg1;
    arg1->unk0x30 = (s32)arg1;
    arg1->unk0x2C = (s32)arg1;
}
