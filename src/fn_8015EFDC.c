// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015EFDC-0x8015F178 (412B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_80174AB8(void *, s32);
s32 fn_8003ABA0(s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80127CD4(CStruct *, s32, s32);
void AddInteger(CStruct *, s32, s32);
bool ScriptSetPlayerAppearanceScale(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    f32 sp10;
    f32 sp14;
    f32 sp18;
    s32 sp1C;
    s32 temp_r30;
    s32 var_r31;

    sp8 = 0;
    GetInteger(pParams, QB_PLAYER, &sp8, 0);
    temp_r30 = fn_80174AB8(lbl_80305EAC, sp8);
    GetChecksum_2(pParams, QB_PART, &spC, 1);
    var_r31 = fn_8003ABA0(temp_r30 + 4, spC);
    if (var_r31 == 0) {
        var_r31 = CStruct_ctor(CStruct_new(8));
        fn_80127CD4(temp_r30 + 0x5C, spC, var_r31);
    }
    if (GetFloat(pParams, QB_X, &sp10, 0) != 0) {
        AddInteger(var_r31, QB_X, (s32)sp10);
    }
    if (GetFloat(pParams, QB_Y, &sp14, 0) != 0) {
        AddInteger(var_r31, QB_Y, (s32)sp14);
    }
    if (GetFloat(pParams, QB_Z, &sp18, 0) != 0) {
        AddInteger(var_r31, QB_Z, (s32)sp18);
    }
    if (GetInteger(pParams, QB_USE_DEFAULT_SCALE, &sp1C, 0) != 0) {
        AddInteger(var_r31, QB_USE_DEFAULT_SCALE, sp1C);
    }
    return true;
}
