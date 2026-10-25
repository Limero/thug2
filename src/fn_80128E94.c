// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128E94-0x80128EC4 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetArray(CStruct *, void *, s32 *, s32);
void fn_80128E94(CStruct *a, void *b, void *c, s32 arg3) {
    s32 var_r6;

    var_r6 = 0;
    if (arg3 != 0) {
        var_r6 = 1;
    }
    GetArray(a, b, c, var_r6);
}
