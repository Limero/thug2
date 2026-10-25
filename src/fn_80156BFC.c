// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80156BFC-0x80156C44 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EFC;
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern void fn_801A5CE0(Unk_C7387A53 *, s32);

bool ScriptSetCurrentSkaterProfile(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetInteger(pParams, 0, &sp8, 0);
    fn_801A5CE0(lbl_80305EFC, sp8);
    return true;
}
