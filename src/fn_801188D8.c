// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801188D8-0x80118934 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "qb_constants.h"
#include "structs.h"
s32 fn_80128C80(CStruct *, s32, s32 *, s32);
void fn_800F2ECC(s32, s32);
extern s32 lbl_80301B48;
bool ScriptSetDefaultPermanent(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r4;
    s32 temp_r31;
    temp_r31 = lbl_80301B48;
    fn_80128C80(pParams, 0, &sp8, 1);
    var_r4 = 1;
    if (sp8 == 0) {
        var_r4 = 0;
    }
    fn_800F2ECC(temp_r31, var_r4);
    return true;
}
