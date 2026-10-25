// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161DD4-0x80161F24 (336B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern CStruct * lbl_80366474;
s32 fn_8005CBCC(CStruct *, s32, s32, s32, s32, s32, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);

bool ScriptCreateTexture(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 var_r31;
    register s32 var_r29 __asm__("r29");
    s32 var_r30;

    var_r31 = 0;
    GetChecksum_2(pParams, 0, &sp8, 0);
    if (GetInteger(pParams, QB_WIDTH, &spC, 0) != 0) {
        var_r31 = 1;
    }
    var_r29 = 0;
    if ((GetInteger(pParams, QB_HEIGHT, &sp10, 0) != 0) && (var_r31 != 0)) {
        var_r29 = 1;
    }
    var_r31 = var_r29;
    var_r29 = 0;
    if ((GetInteger(pParams, QB_UNKNOWN_0xBA0F2AC5, &sp14, 0) != 0) && (var_r31 != 0)) {
        var_r29 = 1;
    }
    var_r31 = var_r29;
    if (sp14 <= 8) {
        var_r30 = 0;
        if ((GetInteger(pParams, QB_UNKNOWN_0x51533ECB, &sp18, 0) != 0) && (var_r31 != 0)) {
            var_r30 = 1;
        }
        var_r31 = var_r30;
    }
    if (var_r31 == 0) {
        return false;
    }
    return fn_8005CBCC(lbl_80366474, sp8, spC, sp10, sp14, sp18, 1, 1) != 0;
}
