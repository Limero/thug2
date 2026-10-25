// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189818-0x80189850 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80185D9C(s32, CStruct *);
s32 Game_GetGoalManager(void);
// ScriptGoalManager_PlayGoalStream @ 0x80189818
bool ScriptGoalManager_PlayGoalStream(CStruct *pParams, CScript *pScript) {
    fn_80185D9C(Game_GetGoalManager(), pParams);
    return true;
}
