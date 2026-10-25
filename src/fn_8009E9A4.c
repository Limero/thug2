// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E9A4-0x8009E9F0 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8009E9A4(Unk_C7387A53 *arg0) {
    s32 temp_r3;

    temp_r3 = fn_8009EEAC();
    if (temp_r3 == 0) {
        return 0;
    }
    return (arg0->unk0x28 & temp_r3) == 0;
}
