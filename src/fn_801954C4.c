// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801954C4-0x80195524 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_8018CAD0(Unk_C7387A53 *);
s32 fn_801954C4(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 var_r3;

    sp8 = 0;
    GetInteger(arg0->unk0x20, QB_SHOULD_CHECK_TRICK, &sp8, 1);
    var_r3 = 0;
    if (sp8 != 1) {
        var_r3 = fn_8018CAD0(arg0);
    }
    return var_r3;
}
