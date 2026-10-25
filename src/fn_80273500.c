// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80273500-0x8027353C (60B). Byte-identical.
#include "types.h"
s32 fn_80273500(s32 arg0, u32 arg1, s32 arg2, u32 arg3) {
    if (arg0 < arg2) {
        return 0;
    }
    if (arg0 > arg2) {
        return 2;
    }
    if (arg1 < arg3) {
        return 0;
    }
    if (arg1 > arg3) {
        return 2;
    }
    return 1;
}
