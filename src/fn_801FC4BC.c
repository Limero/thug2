// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC4BC-0x801FC52C (112B). Byte-identical.
#include "types.h"
extern s32 lbl_80305F60[];
extern bool lbl_80305F68[];
extern s32 lbl_80305F70;
void fn_80012098(s32 arg0, s32 arg1);

void fn_801FC4BC(void) {
    s32 v = lbl_80305F60[lbl_80305F70];

    if (v != 0) {
        if (lbl_80305F68[lbl_80305F70] != 0) {
            fn_80012098(v, 3);
        }
        lbl_80305F60[lbl_80305F70] = 0;
    }
}
