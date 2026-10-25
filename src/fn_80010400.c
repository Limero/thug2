// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010400-0x80010434 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80010400(s32 arg0, s32 arg1, s32 arg2) {
    CStruct *temp_r3;

    temp_r3 = fn_800103C4();
    if (temp_r3 != NULL) {
        return temp_r3->unk0x4;
    }
    return 0;
}
