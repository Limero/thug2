// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F3D8-0x8007F3F4 (28B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8007F3D8(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    Unk_C7387A53 *temp_r9;

    temp_r9 = arg0->unk0x30;
    if (temp_r9 != NULL) {
        temp_r9->unk0x48 = arg1;
        *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x30) + 0x4C) = arg2;
    }
}
