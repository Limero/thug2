// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80171E8C-0x80171EDC (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80170670(void *, s32);
extern s32 lbl_80305EA4;
s32 ScriptTODManager_SetTODInstant(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 mgr;
    s32 var_r3;

    GetChecksum_2(pParams, 0, &sp8, 1);
    mgr = lbl_80305EA4;
    if (mgr == 0) {
        var_r3 = 0;
    } else {
        fn_80170670(mgr, sp8);
        var_r3 = 1;
    }
    return var_r3;
}
