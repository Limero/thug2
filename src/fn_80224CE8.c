// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80224CE8-0x80224D3C (84B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8021D358(s32 arg0, s32 arg1);
void fn_80229E18(void * arg0, s32 arg1);
bool fn_80224CE8(Unk_DB0E2BAB *arg0) {
    Unk_2DE2B2BA *temp_r31;
    s32 temp_r3;

    temp_r31 = arg0->unk0x0;
    temp_r3 = fn_8021D358(arg0->unk0x18, (u16)(s8)*(s8 *)temp_r31);
    if (temp_r3 != 0) {
        fn_80229E18(temp_r3, (s8)temp_r31->unk0x1);
    }
    return true;
}
