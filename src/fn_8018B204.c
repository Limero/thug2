// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018B204-0x8018B264 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(void);
s32 fn_80184F20(s32, s32);
s32 fn_80183D68(Unk_C7387A53 *, s32);

bool ScriptSkateLetters_Active(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;

    GetChecksum_2(pParams, QB_GOAL_ID, &sp8, 1);
    temp_r31 = Game_GetGoalManager();
    if (fn_80184F20(temp_r31, sp8) != 0) {
        fn_80183D68(temp_r31, sp8);
    }
    return true;
}
