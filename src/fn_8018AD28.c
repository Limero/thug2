// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AD28-0x8018AD80 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(void);
extern s32 GoalManager_GetGoal(s32, s32, s32);

s32 ScriptGoalManager_GoalInitialized(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    Unk_C8FEE62D *temp_r3;
    Unk_B79F8E21 *temp_r9;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    temp_r3 = GoalManager_GetGoal(Game_GetGoalManager(), sp8, 1);
    temp_r9 = temp_r3->unk0x14;
    return ((s32 (*)(void *))*((s32 *)&temp_r9->unk0xCC))((char *)temp_r3 +
                                                              temp_r9->unk0xC8);
}
