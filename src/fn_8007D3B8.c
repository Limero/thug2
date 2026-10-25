// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007D3B8-0x8007D3D0 (24B). Byte-identical.
#include "types.h"
bool fn_8007D3B8(s32 arg0, s32 arg1, s32 *arg2) {
    *(s32 *)((char *)((arg1 * 4) + arg0) + 0x24) = (s32) *arg2;
    return true;
}
