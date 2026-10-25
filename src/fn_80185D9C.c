// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185D9C-0x80185E70 (212B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80185D9C(s32, CStruct *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_80191050(CStruct *, s32, s32, s32, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
void fn_80191260(CStruct *, s32 *, CStruct *);
void fn_80185D9C(s32 arg0, CStruct *arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    CScript *temp_r30;

    GetChecksum_2(arg1, QB_NAME, &sp8, 1);
    temp_r30 = GoalManager_GetGoal(arg0, sp8, 1);
    spC = 0;
    GetChecksum_2(arg1, QB_VO, &spC, 0);
    if (spC != 0) {
        fn_80191050(temp_r30->unk0x18, spC, 1, 0, 0);
        return;
    }
    sp10 = spC;
    if (GetString(arg1, QB_TYPE, &sp10, 0) != 0) {
        fn_80191260(temp_r30->unk0x18, sp10, arg1);
    }
}
