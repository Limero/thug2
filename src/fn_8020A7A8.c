// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020A7A8-0x8020A808 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800145AC();                                  

void fn_8020A7A8(Unk_D386C1E6 *arg0) {
    s32 temp_r30;

    if (((s32) arg0->unk0x12F4 != 0) && ((s32) arg0->unk0x1304 != -1)) {
        temp_r30 = arg0->unk0x1300;
        if ((u32) (fn_800145AC() - temp_r30) > (u32) arg0->unk0x1304) {
            arg0->unk0x12F4 = 0;
        }
    }
}
