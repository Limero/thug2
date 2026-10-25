// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EF690-0x800EF738 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800EF80C(Unk_C7387A53 *, s32, s32, s32, s32);

s32 fn_800EF690(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r3;

    GetChecksum_2(arg1, 0, &sp8, 1);
    spC = 0;
    GetInteger(arg1, QB_VOL, &spC, 0);
    sp10 = 0x66;
    GetInteger(arg1, QB_PRIORITY, &sp10, 0);
    if (fn_800EF80C(arg0, sp8, 0, spC, sp10) != 0) {
        var_r3 = 1;
    } else {
        var_r3 = 0;
    }
    return var_r3;
}
