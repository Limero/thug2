// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801116C8-0x80111730 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_4(CStruct *, void *, void *, s32);
s32 fn_800546A0(s32);
s32 ContainsFlag(CStruct *, s32);
void fn_800583A4(s32, s32);
extern char lbl_8029CFC0[];
bool ScriptStartTextureAnim(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;

    GetChecksum_4(pParams, (void *)lbl_8029CFC0, &sp8, 0);
    temp_r30 = fn_800546A0(sp8);
    fn_800583A4(temp_r30, ContainsFlag(pParams, QB_RESET));
    return true;
}
