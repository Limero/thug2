// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9CE0-0x801B9D4C (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
bool fn_801B9CE0(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 var_r0;

    sp8 = 0;
    GetInteger(arg1, 0, &sp8, 1);
    if (sp8 != 0) {
        var_r0 = arg0->unk0x24 | 4;
    } else {
        var_r0 = arg0->unk0x24 & QB_UNKNOWN_0xFFFFFFFB;
    }
    arg0->unk0x24 = var_r0;
    return true;
}
