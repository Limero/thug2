// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003D590-0x8003D664 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 GetInteger(s32, s32, s32 *, s32);
void GetChecksum_2(s32, s32, s32 *, s32);
s32 fn_80129528(s32, s32);
void *fn_801259C8(s32, s32);
void fn_8003D590(void *arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 spC;
    s32 sp8;
    s32 *var_r29;
    s32 temp_r27;
    s32 temp_r31;
    s32 var_r30;
    void *temp_r26;

    var_r29 = arg2;
    temp_r26 = fn_801259C8(arg0, 1);
    *arg3 = 0;
    var_r30 = 0;
    temp_r27 = *(s32 *)((char *)temp_r26 + 4);
    while (var_r30 < temp_r27) {
        temp_r31 = fn_80129528(temp_r26, var_r30);
        sp8 = 0;
        GetInteger(temp_r31, QB_ALLOWED_TO_PICK, &sp8, 1);
        if (sp8 != 0) {
            spC = 0;
            GetChecksum_2(temp_r31, QB_RANDOM_SET, &spC, 0);
            if (spC == arg1) {
                *(s32 *)var_r29 = temp_r31;
                var_r29 += 1;
                *arg3 += 1;
            }
        }
        var_r30 += 1;
    }
}
