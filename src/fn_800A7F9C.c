// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7F9C-0x800A8018 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800A7EC4(CStruct *, Unk_9994C3F5 *);
void GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_800F0F84(s32, s32);
s32 fn_800A7F9C(s32 *arg0, Unk_9994C3F5 *arg1, s32 arg2) {
    s32 sp8;
    s32 var_r3;

    var_r3 = fn_800F0F84(arg2, 1);
    sp8 = 0;
    GetInteger(var_r3, QB_PATHNUM, &sp8, 0);
    fn_800A7EC4(*arg0 + (sp8 * 8), arg1);
    return *arg0 + (sp8 * 8);
}
