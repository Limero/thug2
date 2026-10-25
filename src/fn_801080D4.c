// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801080D4-0x80108104 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_801080D4(Unk_0352A96C *arg0) {
    s32 temp_r9;

    temp_r9 = arg0->unk0xA8;
    if (temp_r9 != 0) {
        return true;
    }
    if ((s32) arg0->unk0xB4 != 0) {
        arg0->unk0xB4 = temp_r9;
        arg0->unk0x60 = temp_r9;
    }
    return false;
}
