// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153A20-0x80153ABC (156B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_8030191C;
extern char lbl_80305EAC[];
void fn_8009D2EC(s32, s32);
void fn_8009D320(s32, s32);
void GetInteger(CStruct *, s32, s32 *, s32);
bool ScriptEnableActuators(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    char *var_r31;
    s32 temp_r0;
    s32 temp_r29;
    s32 var_r30;

    sp8 = 1;
    var_r30 = 0;
    GetInteger(pParams, 0, &sp8, 0);
    temp_r29 = lbl_8030191C;
    var_r31 = *(s32 *)&lbl_80305EAC + 0x3A4;
    do {
        temp_r0 = *(s32 *)var_r31;
        var_r31 += 0x10;
        if (temp_r0 != 0) {
            if (sp8 != 0) {
                fn_8009D320(temp_r29, var_r30);
            } else {
                fn_8009D2EC(temp_r29, var_r30);
            }
        }
        var_r30 += 1;
    } while (var_r30 <= 3);
    return true;
}

