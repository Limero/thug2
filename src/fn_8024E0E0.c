// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024E0E0-0x8024E114 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8024E0E0(CStruct *arg0) {
    s32 temp_r0;

    temp_r0 = 1 << (*(u16 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x50) - 1);
    arg0->unk0x0 = (s32) ((temp_r0 << 5) - 1);
    arg0->unk0x8 = (s32) (temp_r0 << 6);
    arg0->unk0x4 = (s32) (temp_r0 * -0x20);
}
