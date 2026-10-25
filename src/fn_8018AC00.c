// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AC00-0x8018AC84 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(void);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_801879F0(Unk_C7387A53 *, s32, s32, s32);
bool ScriptGoalManager_SetTeamMember(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r5;

    temp_r28 = Game_GetGoalManager();
    GetChecksum_2(pParams, QB_PRO, &sp8, 1);
    temp_r29 = ContainsFlag(pParams, QB_REMOVE);
    temp_r5 = ContainsFlag(pParams, QB_MARK_USED);
    fn_801879F0(temp_r28, sp8, temp_r29, temp_r5);
    return true;
}
