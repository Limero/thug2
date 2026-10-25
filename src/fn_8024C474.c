// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024C474-0x8024C4D8 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
// MSL printf-family deferred-output flush: calls the output fn pointer
// (lbl_803CA324) with the pending object (arg0->unk0x2C) and, when arg1's
// bit 0 is set, with arg0 itself. Suggested rename: fn_8024C474_flush_output.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA324;
void fn_8024C474(Unk_C7387A53 *arg0, s32 arg1) {
    s32 t;
    t = arg0->unk0x2C;
    if (t != 0) {
        ((s32 (*)(s32)) *(s32 *)&lbl_803CA324)(t);
    }
    if ((arg1 & 1) && (arg0 != NULL)) {
        ((s32 (*)(s32)) *(s32 *)&lbl_803CA324)(arg0);
    }
}
