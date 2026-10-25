// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188F34-0x80188F70 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8018551C(s32, s32);
s32 Game_GetGoalManager(void);
// ScriptGoalManager_CounterGoalDone @ 0x80188F34
void ScriptGoalManager_CounterGoalDone(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_8018551C(Game_GetGoalManager(), sp8);
}
