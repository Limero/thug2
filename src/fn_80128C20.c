// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128C20-0x80128C50 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80128170(CStruct *, void *, void *, s32);
void fn_80128C20(CStruct *a, void *b, void *c, s32 arg3) {
    s32 var_r6;

    var_r6 = 0;
    if (arg3 != 0) {
        var_r6 = 1;
    }
    fn_80128170(a, b, c, var_r6);
}
