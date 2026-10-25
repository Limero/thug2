// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80171FB0-0x8017200C (92B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetFloat(CStruct *, s32, f32 *, s32);
void fn_80170668(Unk_E9D95610 *, f32);
extern f32 lbl_802A8CFC;
extern s32 lbl_80305EA4;
s32 ScriptTODManager_SetTimeMultiplier(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    s32 mgr;
    s32 var_r3;

    sp8 = lbl_802A8CFC;
    GetFloat(pParams, 0, &sp8, 0);
    mgr = lbl_80305EA4;
    if (mgr == 0) {
        var_r3 = 0;
    } else {
        fn_80170668(mgr, sp8);
        var_r3 = 1;
    }
    return var_r3;
}
