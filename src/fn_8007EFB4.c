// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007EFB4-0x8007EFE0 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8007EFB4(Unk_C7387A53 *arg0) {
    Unk_897A0ACF *temp_r9;

    temp_r9 = arg0->unk0x30;
    if (temp_r9 != NULL) {
        return (s32) temp_r9->unk0x50 == 0 == 0;
    }
    return arg0->unk0x2C;
}
