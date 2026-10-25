// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CD914-0x801CD950 (60B). Byte-identical.
#include "types.h"
bool fn_801CD914(void *arg0) {
    s32 var_r0;

    if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x120) != 0) {
        var_r0 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0x34);
    } else {
        var_r0 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0x34) ^ 1;
    }
    if (var_r0 == 0) {
        return false;
    }
    return true;
}
