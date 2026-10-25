// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AF70-0x8018B004 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(void);
s32 GoalManager_GetGoal(s32, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 fn_80196740(Unk_3F93CF38 *, Unk_5AA7B5D7 *, s32);

register s32 r31_guard __asm__("r31");

bool ScriptGoalManager_SetTrickBeatPattern(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r29;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    temp_r29 = GoalManager_GetGoal(Game_GetGoalManager(), sp8, 1);
    GetInteger(pParams, QB_TEMPO, &spC, 1);
    GetArray(pParams, QB_BEAT_PATTERN, &sp10, 1);
    fn_80196740(temp_r29, sp10, spC);
    return true;
}
