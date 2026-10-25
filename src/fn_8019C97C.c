// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019C97C-0x8019C9EC (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_801745B4(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
bool ScriptCAT_SetRotsDone(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    CScript *temp_r30;
    s32 var_r0;

    if ((temp_r30 = fn_801745B4(lbl_80305EAC)) != 0) {
        GetInteger(pParams, 0, &sp8, 1);
        var_r0 = sp8;
        if (var_r0 != 0) {
            var_r0 = 1;
        }
        temp_r30->unk0x1D0 = var_r0;
        return true;
    }
    return false;
}
