// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198BA0-0x80198BE8 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_80198BA0(s32 arg0) {
    s32 sp8;
    s32 var_r3;

    fn_80128C80(arg0 + 4, QB_TIMER_BEEPS, &sp8, 1);
    var_r3 = 1;
    if (sp8 == 0) {
        var_r3 = 0;
    }
    return var_r3;
}
