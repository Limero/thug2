// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019CC4C-0x8019CCAC (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_801745B4(s32);
void GetFloat(CStruct *, s32, f32 *, s32);
s32 ScriptCAT_SetHoldTime(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    s32 var_r3;
    CScript *temp_r30;

    if ((temp_r30 = fn_801745B4(lbl_80305EAC)) == 0) {
        var_r3 = 0;
    } else {
        GetFloat(pParams, 0, &sp8, 1);
        temp_r30->unk0x1D4 = sp8;
        var_r3 = 1;
    }
    return var_r3;
}
