// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020A808-0x8020A8FC (244B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure(s32, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_80128C50(CStruct *, void *, void *, s32);
s32 strcasecmp(s32, s32);
s32 fn_8020A808(Unk_59E38960 *arg0, s32 arg1, s32 arg2) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r31;
    s32 temp_r3;
    s32 var_r3;

    var_r31 = arg1;
    sp8 = 0;
    if (((GetChecksum_2(var_r31, QB_TRICKSLOT, &sp8, 0) == 0) || (spC = 0, GetChecksum_2(arg0->unk0xA6C, sp8, &spC, 0), (spC == 0)) || (var_r31 = GetStructure(spC, 0), (var_r31 != 0))) && (sp10 = 0, GetStructure_2(var_r31, QB_PARAMS, &sp10, 0), (sp10 != 0)) && (sp14 = 0, fn_80128C50(sp10, QB_NAME, &sp14, 0), (sp14 != 0))) {
        temp_r3 = strcasecmp(sp14, arg2);
        var_r3 = 1;
        if (temp_r3 != 0) {
            goto block_4;
        }
    } else {
block_4:
        var_r3 = 0;
    }
    return var_r3;
}
