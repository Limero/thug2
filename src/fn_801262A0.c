// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801262A0-0x80126310 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80303220[];
extern bool lbl_80303228[];
extern s32 lbl_80303230;
void fn_80012098(s32 arg0, s32 arg1);
void fn_801262A0(void) {
    s32 v = lbl_80303220[lbl_80303230];
    if (v != 0) {
        if (lbl_80303228[lbl_80303230] != 0) {
            fn_80012098(v, 3);
        }
        lbl_80303220[lbl_80303230] = 0;
    }
}
