// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BB158-0x801BB1B8 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801B97F8(Unk_C7387A53 *, s32);
s32 fn_801BB158(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 var_r3;

    sp8 = 0;
    GetInteger(arg1, 0, &sp8, 0);

    return fn_801B97F8(arg0, sp8) != 0;
}
