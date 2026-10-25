// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A9E0-0x8018AA20 (64B). Byte-identical.
#include "types.h"
void fn_80183A1C(s32, s32, s32);
s32 Game_GetGoalManager(void);
void fn_80195AAC(void);
// ScriptGoalManager_FilmGoalCheckpoint @ 0x8018A9E0
bool ScriptGoalManager_FilmGoalCheckpoint(s32 arg0) {
    fn_80183A1C(Game_GetGoalManager(), arg0, 1);
    fn_80195AAC();
    return true;
}
