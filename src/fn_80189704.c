// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189704-0x80189740 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80186818(Unk_31DE137E *, s32);
s32 Game_GetGoalManager(void);
// ScriptGoalManager_GoalIsLocked @ 0x80189704
void ScriptGoalManager_GoalIsLocked(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_80186818(Game_GetGoalManager(), sp8);
}
