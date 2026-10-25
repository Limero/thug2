// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013F65C-0x8013F6A0 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800145AC();                                  

void fn_8013F65C(Unk_C7387A53 *arg0, s32 arg1) {
    u32 temp_r3;

    temp_r3 = fn_800145AC() + arg1;
    if (temp_r3 > (u32) *((u32 *)&arg0->unk0x74)) {
        *((u32 *)&arg0->unk0x74) = temp_r3;
    }
}
