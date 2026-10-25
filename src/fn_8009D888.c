// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D888-0x8009D8B4 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009D888(CScript *arg0, s32 arg1) {
    s32 temp_r4;

    temp_r4 = ~(arg1 | arg1);
    arg0->unk0x1C = (s32) (arg0->unk0x1C & temp_r4);
    arg0->unk0x20 = (s32) (arg0->unk0x20 & temp_r4);
    arg0->unk0x24 = (s32) (arg0->unk0x24 & temp_r4);
}
