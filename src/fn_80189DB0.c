// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189DB0-0x80189E1C (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern s32 Game_GetGoalManager(void);
extern s32 fn_80184CD0(Unk_C7387A53 * arg0, s32 arg1, s32 arg2);

void ScriptGoalManager_QuickStartGoal(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r31;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    var_r31 = 0;
    if (ContainsFlag(pParams, QB_DONTASSERT) != 0) {
        var_r31 = 1;
    }
    fn_80184CD0(Game_GetGoalManager(), sp8, var_r31);
}
