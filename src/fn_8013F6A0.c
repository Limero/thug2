// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013F6A0-0x8013F6E4 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8013F6A0(Unk_C7387A53 *arg0) {
    u32 temp_r0;
    u32 temp_r3;

    temp_r3 = fn_800145AC();
    temp_r0 = arg0->unk0x74;
    if (temp_r3 < temp_r0) {
        return 0;
    }
    return temp_r3 - temp_r0;
}
