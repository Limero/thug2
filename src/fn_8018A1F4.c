// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A1F4-0x8018A260 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 Game_GetGoalManager(void);
extern s32 fn_80186C20(s32, s32);
extern void AddInteger(CStruct *, s32, s32);

s32 ScriptGoalManager_GetNumberOfFlags(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r5;
    s32 var_r3;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    temp_r5 = fn_80186C20(Game_GetGoalManager(), sp8);
    if (temp_r5 == -1) {
        var_r3 = 0;
    } else {
        AddInteger(pScript->unk0x18, QB_NUMBER_OF_FLAGS, temp_r5);
        var_r3 = 1;
    }
    return var_r3;
}
