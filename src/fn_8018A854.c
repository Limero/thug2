// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A854-0x8018A8A0 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager();
s32 fn_801878EC(Unk_6BF95B44 *, s32);
bool ScriptGoalManager_SetDifficultyLevel(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetInteger(pParams, 0, &sp8, 1);
    fn_801878EC(Game_GetGoalManager(), sp8);
    return sp8 != 0;
}
