// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80255FF4-0x80256020 (44B). Byte-identical.
#include "types.h"
s32 fn_80255FF4(s32 **arg0, s32 **arg1) {
    u32 a;
    u32 b;

    a = *(u32 *)*arg0;
    b = *(u32 *)*arg1;
    return (a > b) - (a < b);
}
