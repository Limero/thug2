// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80171DC0-0x80171E1C (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EA4;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8016D920(Unk_FF487DD2 *, s32);
bool ScriptTODManager_SetActive(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;
    s32 var_r4;

    temp_r31 = lbl_80305EA4;
    GetInteger(pParams, 0, &sp8, 1);
    var_r4 = 1;
    if (sp8 == 0) {
        var_r4 = 0;
    }
    fn_8016D920(temp_r31, var_r4);
    return true;
}
