// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80053FB0-0x80054048 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
bool fn_80053FB0(s32 *arg0, CStruct *arg1) {
    s32 var_r0;

    *arg0 = 0;
    if (ContainsFlag(arg1, QB_CYCLE) != 0) {
        var_r0 = 1;
        goto block_6;
    }
    if (ContainsFlag(arg1, QB_PINGPONG) != 0) {
        var_r0 = 2;
        goto block_6;
    }
    if (ContainsFlag(arg1, QB_WOBBLE) != 0) {
        var_r0 = 3;
block_6:
        *arg0 = var_r0;
    }
    return true;
}
