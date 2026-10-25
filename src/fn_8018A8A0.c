// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A8A0-0x8018A8EC (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(s32);
s32 fn_80187934(Unk_6BF95B44 *, s32);
void AddInteger(CStruct *, u32, s32);
bool ScriptGoalManager_GetDifficultyLevel(s32 arg0, CScript *arg1) {
    s32 temp_r5;

    temp_r5 = fn_80187934(Game_GetGoalManager(arg0), 0);
    AddInteger(arg1->unk0x18, QB_DIFFICULTY_LEVEL, temp_r5);
    return true;
}
