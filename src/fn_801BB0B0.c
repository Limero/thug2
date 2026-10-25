// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BB0B0-0x801BB134 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_801B301C(Unk_C7387A53 *, s32, Unk_C8FEE62D *);

bool fn_801BB0B0(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    if (GetChecksum_2(arg1, QB_NAME, &sp8, 1) != 0) {
        spC = 0;
        GetStructure_2(arg1, QB_PARAMS, &spC, 0);
        fn_801B301C(arg0, sp8, spC);
    }
    return true;
}
