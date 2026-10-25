// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013F6E4-0x8013F708 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8013F6E4(Unk_FFAD6788 *arg0) {
    volatile s32 sp8;
    s32 temp_r0;

    temp_r0 = arg0->unk0x68;
    sp8 = 4;
    temp_r0 = (temp_r0 & ~1) | 4;
    arg0->unk0x68 = temp_r0;
}
