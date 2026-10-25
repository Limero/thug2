// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016D2E4-0x8016D348 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Deferred-call countdown dispatcher: decrements a pending-call counter;
// on expiry dispatches fn_8016D3D4(ptr, 3) and clears state. Same family
// as the vcall_* countdown dispatchers. Suggested rename: fn_8016D2E4_dispatch_deferred_call.
#include "types.h"
#include "structs.h"
extern CStruct *lbl_80305EA4;
extern u32 lbl_80305EA8;
void fn_8016D3D4(CStruct *arg0, s32 arg1);
void fn_8016D2E4(void) {
    if (lbl_80305EA8 > 1) {
        lbl_80305EA8--;
    } else {
        if (lbl_80305EA4 != 0) {
            fn_8016D3D4(lbl_80305EA4, 3);
        }
        lbl_80305EA4 = 0;
        lbl_80305EA8 = 0U;
    }
}