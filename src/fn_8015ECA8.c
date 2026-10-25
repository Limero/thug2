// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015ECA8-0x8015ED4C (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80174AB8(void *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8003AB44(s32, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
bool ScriptGetActualPlayerAppearancePart(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 temp_r31;
    s32 temp_r3;

    sp8 = 0;
    GetInteger(pParams, QB_PLAYER, &sp8, 0);
    temp_r31 = fn_80174AB8(lbl_80305EAC, sp8) + 4;
    if ((GetChecksum_2(pParams, QB_PART, &spC, 0) != 0) &&
        ((temp_r3 = fn_8003AB44(temp_r31, spC)) != 0)) {
        fn_80126FF4(pScript->unk0x18, temp_r3);
        return true;
    }
    return false;
}
