// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A354-0x8018A3B4 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 Game_GetGoalManager();
extern s32 fn_80186CB8(s32, s32);
extern void AddInteger(CStruct *, s32, s32);

bool ScriptGoalManager_GetNumberOfTimesGoalStarted(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r5;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    temp_r5 = fn_80186CB8(Game_GetGoalManager(), sp8);
    AddInteger(pScript->unk0x18, QB_TIMES_STARTED, temp_r5);
    return true;
}
