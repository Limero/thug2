// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A8018-0x800A807C (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800A7EC4(CStruct *, Unk_9994C3F5 *);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_800F0F84(s32, s32);
s32 fn_800A8018(CStruct *arg0, Unk_9994C3F5 *arg1, s32 arg2) {
    s32 sp8;
    s32 t;

    t = fn_800F0F84(arg2, 1);
    sp8 = 0;
    GetInteger(t, QB_PATHNUM, &sp8, 0);
    fn_800A7EC4(arg0->unk0x4, arg1);
    return arg0->unk0x4;
}
