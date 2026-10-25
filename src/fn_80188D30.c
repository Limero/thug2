// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188D30-0x80188D88 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
// ScriptGoalManager_SetGraffitiMode @ 0x80188D30
void ScriptGoalManager_SetGraffitiMode(CStruct *, CScript *pScript);
s32 Game_GetGoalManager(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80185164(Unk_C7387A53 *, s32);
void ScriptGoalManager_SetGraffitiMode(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;

    temp_r29 = Game_GetGoalManager(pParams);
    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    fn_80185164(temp_r29, sp8);
}
