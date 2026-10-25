// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006BC90-0x8006BCDC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void memcpy(s32, s32, s32);
void fn_8006BC90(CStruct *arg0, s32 arg1) {
    memcpy((char *)arg0 + (arg0->unk0x0 + 8), arg1, arg0->unk0x4);
    arg0->unk0x0 = (s32) (arg0->unk0x0 + arg0->unk0x4);
}
