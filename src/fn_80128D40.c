// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128D40-0x80128D70 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetVector(CStruct *, void *, CStruct *, s32);
void fn_80128D40(CStruct *a, void *b, CStruct *c, s32 arg3) {
    s32 var_r6;

    var_r6 = 0;
    if (arg3 != 0) {
        var_r6 = 1;
    }
    GetVector(a, b, c, var_r6);
}
