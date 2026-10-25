// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC44C-0x801FC4BC (112B). Byte-identical.
#include "types.h"
extern s32 lbl_80305F4C[];
extern bool lbl_80305F54[];
extern s32 lbl_80305F5C;
void fn_80012098(s32 arg0, s32 arg1);

void fn_801FC44C(void) {
    s32 v = lbl_80305F4C[lbl_80305F5C];

    if (v != 0) {
        if (lbl_80305F54[lbl_80305F5C] != 0) {
            fn_80012098(v, 3);
        }
        lbl_80305F4C[lbl_80305F5C] = 0;
    }
}
