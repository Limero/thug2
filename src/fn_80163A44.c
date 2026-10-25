// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80163A44-0x80163AA0 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F24;
extern char lbl_802A836C[];
void GetText(CStruct *, void *, void *, s32);
s32 fn_801B0F70(s32, s32);
bool ScriptSetInitialsString(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;

    temp_r30 = lbl_80305F24;
    sp8 = (s32)lbl_802A836C;
    GetText(pParams, QB_STRING, &sp8, 0);
    fn_801B0F70(temp_r30, sp8);
    return true;
}
