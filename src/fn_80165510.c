// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165510-0x80165580 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
void fn_80144CC4(Unk_6A70655D *, s32);
bool ScriptApplyCustomLogoToPart(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    GetChecksum_2(pParams, QB_PART, &sp8, 1);
    GetInteger(pParams, QB_PLAYER, &spC, 1);
    fn_80144CC4(fn_801746A4(lbl_80305EAC, spC), sp8);
    return true;
}
