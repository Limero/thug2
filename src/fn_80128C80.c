// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128C80-0x80128CB0 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, void *, s32 *, s32);
void fn_80128C80(CStruct *a, void *b, void *c, s32 arg3) {
    s32 var_r6;

    var_r6 = 0;
    if (arg3 != 0) {
        var_r6 = 1;
    }
    GetInteger(a, b, c, var_r6);
}
