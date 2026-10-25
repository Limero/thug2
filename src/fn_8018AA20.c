// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AA20-0x8018AA60 (64B). Byte-identical.
#include "types.h"
void fn_80183A1C(s32, s32, s32);
s32 Game_GetGoalManager(void);
void fn_80195D94(void);
// ScriptGoalManager_StartFilming @ 0x8018AA20
bool ScriptGoalManager_StartFilming(s32 arg0) {
    fn_80183A1C(Game_GetGoalManager(), arg0, 1);
    fn_80195D94();
    return true;
}
