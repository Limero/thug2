// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80073828-0x80073880 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80301668;
void fn_80072BE8(void);
void fn_80072E4C(void);
void fn_80073594(void);

void fn_80073828(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 var_r0;

    var_r0 = lbl_80301668;
    if (arg3 != 0) {
        var_r0 = arg3;
    }
    switch (var_r0) {
    case 1:
    default:
        fn_80072BE8();
        return;
    case 2:
        fn_80072E4C();
        return;
    case 3:
        fn_80073594();
        return;
    }
}
