// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188EE4-0x80188F34 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 Game_GetGoalManager();
extern void fn_801854C4(void *, void *);
bool ScriptGoalManager_GotCounterObject(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    if (GetChecksum_2(pParams, QB_NAME, &sp8, 0) != 0) {
        fn_801854C4(Game_GetGoalManager(), sp8);
        return true;
    }
    return false;
}
