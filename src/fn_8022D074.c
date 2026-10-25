// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D074-0x8022D0E4 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80305FCC[];
extern s32 lbl_80305FD4[];
extern s32 lbl_80305FDC;
extern void fn_80012098(s32 arg0, s32 arg1);
void fn_8022D074(void) {
    s32 v = lbl_80305FCC[lbl_80305FDC];

    if (v != 0) {
        if (lbl_80305FD4[lbl_80305FDC] != 0) {
            fn_80012098(v, 3);
        }
        lbl_80305FCC[lbl_80305FDC] = 0;
    }
}
