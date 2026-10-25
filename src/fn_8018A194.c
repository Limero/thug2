// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A194-0x8018A1F4 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 Game_GetGoalManager(void);
extern s32 fn_80186BF8(s32, s32);
extern void AddInteger(CStruct *, s32, s32);

bool ScriptGoalManager_GetNumberCollected(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r5;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    var_r5 = fn_80186BF8(Game_GetGoalManager(), sp8);
    AddInteger(pScript->unk0x18, QB_NUMBER_COLLECTED, var_r5);
    return true;
}
