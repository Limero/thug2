// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018ACAC-0x8018AD00 (84B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 Game_GetGoalManager(void);
extern s32 GetString(CStruct *, s32 *, s32 *, s32);
void fn_80187A68(Unk_C7387A53 *, void *);

bool ScriptGoalManager_SetTeamName(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;

    temp_r30 = Game_GetGoalManager();
    GetString(pParams, 0, &sp8, 1);
    fn_80187A68(temp_r30, sp8);
    return true;
}
