// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243320-0x8024336C (76B). Byte-identical.
#include "types.h"
#include "mem.h"
void fn_802432A8(void *);
void fn_80243320(s32 *arg0, s32 arg1) {
    if ((s32) *arg0 != 0) {
        fn_802432A8(*(s32 *)arg0);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
