// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013ADE8-0x8013AE40 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 fn_8013BD50(s32, s32);
s32 fn_8013ADE8(s32 arg0) {
    s32 i;
    for (i = 1; i <= 0xFF; i++) {
        if (fn_8013BD50(arg0, i) == 0) {
            return i;
        }
    }
    return 0;
}
