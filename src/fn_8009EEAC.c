// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009EEAC-0x8009EF74 (200B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GetChecksum(CStruct *, s32);
s32 Script_GetInteger(s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 fn_8009EEAC(s32 arg0, CStruct *arg1) {
    s32 spC;
    void *sp8;
    s32 var_r30;
    u32 var_r31;

    var_r30 = 0;
    spC = 0;
    sp8 = NULL;
    GetArray(arg1, 0, &sp8, 0);
    if (sp8 != NULL) {
        var_r31 = 0;
        if (var_r30 < (u32) *((u32 *)&((CStruct *)sp8)->unk0x4)) {
            do {
                var_r30 |= 1 << Script_GetInteger(GetChecksum(sp8, var_r31), 0);
                var_r31 += 1;
            } while (var_r31 < (u32) *((u32 *)&((CStruct *)sp8)->unk0x4));
        }
    } else if (GetInteger(arg1, 0, &spC, 0) != 0) {
        var_r30 = 1 << spC;
    }
    return var_r30;
}
