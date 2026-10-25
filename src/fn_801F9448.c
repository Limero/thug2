// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9448-0x801F9498 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801F7FEC(s32, void *, s32);                  

s32 fn_801F9448(Unk_C7387A53 *arg0) {
    s32 temp_r3;
    s32 temp_r5;

    temp_r3 = arg0->unk0x24;
    if (temp_r3 != 0) {
        temp_r5 = arg0->unk0x28;
        if (temp_r5 != 0) {
            return fn_801F7FEC(temp_r3 + 8, (char *)arg0 + 8, temp_r5 + 8);
        }
    }
    return 1;
}
