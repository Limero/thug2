// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198E8C-0x80198ED4 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80128C80(CStruct *, void *, void *, s32);
// IsTrue @ 0x80198E8C
s32 IsTrue(s32 arg0, void *arg1) {
    s32 sp8;
    s32 var_r3;

    sp8 = 0;
    fn_80128C80(arg0 + 4, arg1, &sp8, 0);
    var_r3 = 1;
    if (sp8 == 0) {
        var_r3 = 0;
    }
    return var_r3;
}
