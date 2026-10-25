// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800187E8-0x800187FC (20B). Byte-identical.
#include "types.h"
#include "structs.h"
// queue_empty @ 0x800187E8
s32 queue_empty(Unk_F6ED4C32 *arg0) {
    u16 val = arg0->unk0x3C;
    return val == 5 ? 1 : 0;
}
