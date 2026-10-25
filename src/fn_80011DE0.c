// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80011DE0-0x80011E00 (32B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80011DE0(CStruct *arg0, s32 arg1) {
    s32 temp_r0;

    temp_r0 = arg0->unk0x4 + arg1;
    arg0->unk0x4 = temp_r0;
    if (temp_r0 > (s32) arg0->unk0x8) {
        arg0->unk0x8 = temp_r0;
    }
}
