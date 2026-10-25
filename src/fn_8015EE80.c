// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015EE80-0x8015EFDC (348B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_80174AB8(void *, s32);
s32 fn_8003ABA0(s32, s32);
void AddInteger(CStruct *, s32, s32);
bool ScriptSetPlayerAppearanceColor(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    f32 sp10;
    f32 sp14;
    f32 sp18;
    s32 sp1C;
    s32 temp_r30;

    sp8 = 0;
    GetInteger(pParams, QB_PLAYER, &sp8, 0);
    temp_r30 = fn_80174AB8(lbl_80305EAC, sp8) + 4;
    GetChecksum_2(pParams, QB_PART, &spC, 1);
    if ((temp_r30 = fn_8003ABA0(temp_r30, spC)) != 0) {
        GetFloat(pParams, QB_H, &sp10, 1);
        GetFloat(pParams, QB_S, &sp14, 1);
        GetFloat(pParams, QB_V, &sp18, 1);
        GetInteger(pParams, QB_USE_DEFAULT_HSV, &sp1C, 1);
        AddInteger(temp_r30, QB_H, (s32)sp10);
        AddInteger(temp_r30, QB_S, (s32)sp14);
        AddInteger(temp_r30, QB_V, (s32)sp18);
        AddInteger(temp_r30, QB_USE_DEFAULT_HSV, sp1C);
    }
    return true;
}
