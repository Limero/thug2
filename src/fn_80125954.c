// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125954-0x80125994 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
// GetStructure @ 0x80125954
s32 GetStructure(s32 arg0, s32 arg1) {
    Unk_1D62F22E *temp_r3;

    temp_r3 = fn_80125480();
    if ((temp_r3 != NULL) && ((s32) temp_r3->unk0x2 == 0xA)) {
        return temp_r3->unk0xC;
    }
    return 0;
}
