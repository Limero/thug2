// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A498-0x8018A4E8 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Game_GetGoalManager();
extern void AddChecksum(CStruct *, s32, s32);

bool ScriptGoalManager_GetLastGoalId(s32 arg0, CScript *arg1) {
    s32 var_r5;

    var_r5 = *(s32 *)(Game_GetGoalManager() + 0x38);
    if (var_r5 != 0) {
        AddChecksum(arg1->unk0x18, QB_GOAL_ID, var_r5);
        return true;
    }
    return false;
}
