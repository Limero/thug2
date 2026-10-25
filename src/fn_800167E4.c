// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800167E4-0x80016810 (44B). Byte-identical.
#include "types.h"
s32 CARDClose(void *);
s32 fn_800167E4(s32 arg0) {
    s32 temp_r3;

    temp_r3 = CARDClose(arg0 + 0x50);
    return temp_r3 == 0;
}
