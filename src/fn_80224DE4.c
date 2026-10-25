// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80224DE4-0x80224E28 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8021D358(s32 arg0, s32 arg1);
void fn_8022A21C(Unk_C7387A53 * arg0);
bool fn_80224DE4(Unk_DB0E2BAB *arg0) {
    s32 temp_r9;
    s32 temp_r3;

    temp_r9 = arg0->unk0x0;
    temp_r3 = fn_8021D358(arg0->unk0x18, (u16)(s8)*(s8 *)temp_r9);
    if (temp_r3 != 0) {
        fn_8022A21C(temp_r3);
    }
    return true;
}
