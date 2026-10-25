// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80068510-0x80068528 (24B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80068510(CStruct *arg0) {
    s32 temp_r3;

    temp_r3 = arg0->unk0xC;
    if (temp_r3 == 0) {
        return arg0->unk0x4;
    }
    return temp_r3;
}
