// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182150-0x8018223C (236B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetStructure(s32, s32);
void GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_801259C8(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 Script_GenerateCRC(s32);
void fn_80181AC0(s32, s32, s32, s32);
void fn_801281BC(s32, s32, void *, s32);
void fn_80182150(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r31;
    s32 var_r4;

    var_r4 = arg1;
    if (arg4 > 1) {
        var_r31 = arg4;
        var_r4 = GetStructure(var_r4, 1);
        GetStructure_2(var_r4, QB_PARAMS, &sp8, 1);
        do {
            var_r31 -= 1;
            GetChecksum_2(sp8, QB_EXTRATRICKS, &spC, 0);
            GetStructure_2(fn_80129528(fn_801259C8(spC, 1), 0), QB_PARAMS, &sp8, 1);
        } while (var_r31 > 1);
        fn_801281BC(sp8, QB_NAME, &sp10, 1);
        var_r4 = Script_GenerateCRC(sp10);
    }
    fn_80181AC0(arg0, var_r4, arg2, arg3);
}
