// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D160-0x8022D1D0 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_80012098(s32, s32);
extern void *lbl_80305FE0[];
extern void *lbl_80305FE8[];
extern s32 lbl_80305FF0;
void fn_8022D160(void) {
    void *entry = lbl_80305FE0[lbl_80305FF0];
    if (entry != 0) {
        if (lbl_80305FE8[lbl_80305FF0] != 0) {
            fn_80012098((s32)entry, 3);
        }
        lbl_80305FE0[lbl_80305FF0] = 0;
    }
}
