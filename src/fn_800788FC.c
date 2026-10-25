// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800788FC-0x80078948 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
bool fn_800788FC(Unk_C7387A53 *arg0) {
    s32 v = *(s32 *)(arg0->unk0xC + 0x18);
    if (v != 0) {
        Mem_Free(v);
    }
    *(s32 *)(arg0->unk0xC + 0x18) = 0;
    return true;
}
