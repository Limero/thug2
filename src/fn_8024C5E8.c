// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024C5E8-0x8024C624 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
// MSL printf-family flush: if the pending-output flag (lbl_803CA338) is set,
// routes it through the output fn pointer (lbl_803CA324) and clears the flag.
// Suggested rename: fn_8024C5E8_flush_pending_output.
#include "types.h"
extern s32 lbl_803CA324;
extern s32 lbl_803CA338;
void fn_8024C5E8(void) {
    s32 t = lbl_803CA338;
    if (t != 0) {
        ((s32 (*)(s32)) *(s32 *)&lbl_803CA324)(t);
        lbl_803CA338 = 0;
    }
}
