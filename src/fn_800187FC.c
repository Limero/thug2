// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800187FC-0x80018834 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
// queue_length @ 0x800187FC
s32 queue_length(Unk_D78094DA *arg0) {
    u16 temp_r0;
    u16 temp_r3;

    temp_r0 = arg0->unk0x3C;
    if (temp_r0 == 5) {
        return 0;
    }
    temp_r3 = arg0->unk0x3E;
    if (temp_r0 > temp_r3) {
        return (temp_r0 - temp_r3) + 1;
    }
    return (temp_r0 - temp_r3) + 6;
}

