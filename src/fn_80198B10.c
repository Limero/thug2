// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198B10-0x80198B68 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_80305F9C;

extern s32 fn_8009CF2C(CStruct * arg0);
extern s32 fn_80198B68(s32 arg0);

s32 fn_80198B10(s32 arg0) {
    s32 var_r30;

    var_r30 = 0;
    if (fn_8009CF2C(lbl_80305F9C) != 0) {
        if (fn_80198B68(arg0) > 0) {
            var_r30 = 1;
        }
    }
    return var_r30;
}
