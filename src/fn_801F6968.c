// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6968-0x801F69CC (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801F5898(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801F35DC(void *, s32);
bool fn_801F6968(void *arg0, CStruct *arg1) {
    s32 sp8;
    s32 temp_r3;

    temp_r3 = fn_801F5898(arg0);
    if (temp_r3 != 0) {
        sp8 = 0;
        GetInteger(arg1, QB_SET_INDEX, &sp8, 0);
        fn_801F35DC(temp_r3, sp8);
    }
    return true;
}
