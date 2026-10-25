// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80172480-0x801724E4 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EA4;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8016D928(Unk_9472DC69 *, s32);
bool ScriptTODManager_SetFogActive(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 mgr;
    s32 var_r4;

    mgr = lbl_80305EA4;
    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    var_r4 = 1;
    if (sp8 == 0) {
        var_r4 = 0;
    }
    fn_8016D928(mgr, var_r4);
    return true;
}
