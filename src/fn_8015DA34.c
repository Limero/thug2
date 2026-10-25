// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015DA34-0x8015DAFC (200B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetStructure_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_80174AB8(void * arg0, s32 arg1);
extern s32 Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
bool ScriptEditPlayerAppearance(CStruct *pParams, CScript *pScript) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r28;

    spC = 0;
    sp8 = 0;
    GetInteger(pParams, 0, &sp8, 0);
    spC = sp8;
    GetInteger(pParams, QB_PROFILE, &spC, 0);
    temp_r28 = fn_80174AB8(lbl_80305EAC, spC) + 4;
    GetChecksum_2(pParams, QB_TARGET, &sp10, 1);
    sp14 = 0;
    GetStructure_2(pParams, QB_TARGETPARAMS, &sp14, 0);
    Script_RunScript(sp10, sp14, temp_r28, 0, 0);
    return true;
}
