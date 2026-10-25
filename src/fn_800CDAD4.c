// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CDAD4-0x800CDB60 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8011CAF0(s32, s32, s32);
s32 fn_800CDAD4(s32 arg0, CStruct *arg1) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    if (GetChecksum_2(arg1, 0, &sp8, 0) != 0) {
        spC = 0;
        if (GetChecksum_2(arg1, QB_ADD, &spC, 0) != 0) {
            return fn_8011CAF0(sp8, spC, arg0);
        }
    }
    return 0;
}
