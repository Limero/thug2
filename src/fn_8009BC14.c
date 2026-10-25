// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009BC14-0x8009BC98 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8009BC14(Unk_C7387A53 *arg0, Unk_C7387A53 *arg1) {
    s32 r10 = 0;
    if ((s32) arg0->unk0x44 != 0) {
        if ((s32) arg1->unk0x44 == 0)
            return -1;
        r10 = 1;
    } else if ((s32) arg1->unk0x44 != 0) {
        return 1;
    }
    if (arg0->unk0x3C < arg1->unk0x3C) return 1;
    if (arg0->unk0x3C > arg1->unk0x3C) return -1;
    if (r10 != 0) {
        if ((u32) arg0->unk0x44 < (u32) arg1->unk0x44) return 1;
        if ((u32) arg0->unk0x44 > (u32) arg1->unk0x44) return -1;
    }
    return 0;
}
