// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802417A8-0x80241804 (92B). Byte-identical.
#include "types.h"
s32 fn_802417A8(u8 *arg0, u8 *arg1) {
    s32 ret;

    if (arg0[0] < arg1[0]) {
        goto fail;
    }
    if ((arg0[0] + arg0[3]) > (arg1[0] + arg1[3])) {
        goto fail;
    }
    if (arg0[2] < arg1[2]) {
        goto fail;
    }
    ret = 1;
    __asm__("" : "+r"(ret));
    if ((arg0[2] + arg0[5]) > (arg1[2] + arg1[5])) {
        ret = 0;
    }
    return ret;
fail:
    return 0;
}
