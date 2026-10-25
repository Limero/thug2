// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800161C4-0x8001621C (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 CARDGetStatus(s32 chan, s32 slot, s32 *status);
s32 fn_800161C4(void) {
    // Retail places a 0x70-byte scratch buffer at r1+8 (giving the 0x80 frame)
    // and passes its address as the CARDGetStatus out-param; the value written
    // there is never read. Modelled as an oversized status array so the buffer
    // is the only stack object and lands at the same offset.
    s32 status[0x1C];
    s32 var_r30;
    s32 var_r31;

    var_r30 = 0;
    var_r31 = 0;
    do {
        if (CARDGetStatus(0, var_r31, &status[0]) == 0) {
            var_r30 += 1;
        }
        var_r31 += 1;
    } while (var_r31 <= 0x7E);
    return 0x7F - var_r30;
}