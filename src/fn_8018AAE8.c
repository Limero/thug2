// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AAE8-0x8018AB38 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 Game_GetGoalManager(void);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
bool ScriptGoalManager_SetSponsor(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    Unk_C7387A53 *temp_r29;

    temp_r29 = Game_GetGoalManager();
    GetChecksum_2(pParams, 0, &sp8, 1);
    temp_r29->unk0x58 = sp8;
    return true;
}
