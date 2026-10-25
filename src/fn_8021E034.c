// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021E034-0x8021E0E0 (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void *fn_801259C8(s32, s32);
void *fn_80129528(CStruct *, s32);
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 GetText(CStruct *, void *, void *, s32);

s32 fn_8021E034(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp8;
    s32 spC;
    CStruct *temp_r3;
    void *temp_r31;
    s32 var_r30;

    spC = 0;
    var_r30 = 0;
    temp_r3 = fn_801259C8(arg1, 0);
    while (var_r30 < temp_r3->unk0x4) {
        temp_r31 = fn_80129528(temp_r3, var_r30);
        fn_80128E34(temp_r31, QB_CHECKSUM, &sp8, 1);
        if (sp8 == arg2) {
            GetText(temp_r31, QB_NAME, &spC, 1);
        }
        var_r30 += 1;
    }
    return spC;
}
