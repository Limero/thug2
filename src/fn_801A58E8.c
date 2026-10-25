// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A58E8-0x801A594C (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Deferred-call countdown dispatcher: decrements a pending-call counter;
// on expiry dispatches fn_801A5A9C(ptr, 3) and clears state. Same family
// as the vcall_* countdown dispatchers. Suggested rename: fn_801A58E8_dispatch_deferred_call.
#include "types.h"
#include "structs.h"
extern Unk_C7387A53 *lbl_80305EFC;
extern u32 lbl_80305F00;
void fn_801A5A9C(Unk_C7387A53 *arg0, s32 arg1);
void fn_801A58E8(void) {
    if (lbl_80305F00 > 1) {
        lbl_80305F00--;
    } else {
        if (lbl_80305EFC != 0) {
            fn_801A5A9C(lbl_80305EFC, 3);
        }
        lbl_80305EFC = 0;
        lbl_80305F00 = 0U;
    }
}