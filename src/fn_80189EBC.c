// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189EBC-0x80189F18 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 Game_GetGoalManager(void);
extern s32 GoalManager_GetGoal(s32, s32, s32);

bool ScriptGoalManager_ExpireGoal(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    Unk_C8FEE62D *temp_r3;
    Unk_64253088 *temp_r9;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    temp_r3 = GoalManager_GetGoal(Game_GetGoalManager(), sp8, 1);
    temp_r9 = temp_r3->unk0x14;
    ((s32 (*)(void *))temp_r9->unk0x34)((char *)temp_r3 + temp_r9->unk0x30);
    return true;
}
