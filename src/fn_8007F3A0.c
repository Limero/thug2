// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F3A0-0x8007F3D8 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8007F3A0(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    Unk_C7387A53 *temp_r9;

    temp_r9 = arg0->unk0x30;
    if (temp_r9 != NULL) {
        memcpy(temp_r9->unk0x48, arg1, arg2 << 6);
    }
}
