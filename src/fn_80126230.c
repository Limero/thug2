// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80126230-0x801262A0 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_8030315C[];
extern bool lbl_80303164[];
extern s32 lbl_8030316C;
void fn_80012098(s32 arg0, s32 arg1);
void fn_80126230(void) {
    s32 v = lbl_8030315C[lbl_8030316C];
    if (v != 0) {
        if (lbl_80303164[lbl_8030316C] != 0) {
            fn_80012098(v, 3);
        }
        lbl_8030315C[lbl_8030316C] = 0;
    }
}
