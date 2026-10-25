// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015F178-0x8015F2DC (356B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80174AB8(void *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8003ABA0(s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_8012772C(CStruct *, s32, f32);
void AddInteger(CStruct *, s32, s32);
bool ScriptSetPlayerAppearanceUV(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    f32 sp10;
    f32 sp14;
    f32 sp18;
    f32 sp1C;
    s32 sp20;
    s32 temp_r30;

    sp8 = 0;
    GetInteger(pParams, QB_PLAYER, &sp8, 0);
    temp_r30 = fn_80174AB8(lbl_80305EAC, sp8) + 4;
    GetChecksum_2(pParams, QB_PART, &spC, 1);
    temp_r30 = fn_8003ABA0(temp_r30, spC);
    if (temp_r30 != 0) {
        GetFloat(pParams, QB_UV_U, &sp10, 1);
        GetFloat(pParams, QB_UV_V, &sp14, 1);
        GetFloat(pParams, QB_UV_SCALE, &sp18, 1);
        GetFloat(pParams, QB_UV_ROT, &sp1C, 1);
        GetInteger(pParams, QB_USE_DEFAULT_UV, &sp20, 1);
        fn_8012772C(temp_r30, QB_UV_U, sp10);
        fn_8012772C(temp_r30, QB_UV_V, sp14);
        fn_8012772C(temp_r30, QB_UV_SCALE, sp18);
        fn_8012772C(temp_r30, QB_UV_ROT, sp1C);
        AddInteger(temp_r30, QB_USE_DEFAULT_UV, sp20);
    }
    return true;
}
