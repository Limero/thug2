// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A43C-0x8018A498 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 Game_GetGoalManager(s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern void fn_80186DDC(Unk_C7387A53 *, s32);

bool ScriptGoalManager_SetCanStartGoal(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;

    temp_r29 = Game_GetGoalManager(pParams);
    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    fn_80186DDC(temp_r29, sp8);
    return true;
}
