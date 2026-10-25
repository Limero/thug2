// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802380EC-0x80238104 (24B). Byte-identical.
#include "types.h"
s32 fn_802380EC(s32 arg0, s32 arg1, s32 arg2) {
    s32 idx = arg2 * 4 + arg1 * 0xE8;
    s32 *base = (s32 *)((char *)arg0 + 0x90);
    return *(s32 *)((char *)base + idx);
}
