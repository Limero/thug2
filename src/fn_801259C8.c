// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801259C8-0x80125A08 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801259C8(s32 arg0, s32 arg1) {
    Unk_1D62F22E *temp_r3;

    temp_r3 = fn_80125480();
    if ((temp_r3 != NULL) && ((s32) temp_r3->unk0x2 == 0xC)) {
        return temp_r3->unk0xC;
    }
    return 0;
}
