// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189494-0x801894CC (56B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80185E9C(s32, CStruct *);
s32 Game_GetGoalManager(void);
// ScriptGoalManager_PlayGoalWinStream @ 0x80189494
bool ScriptGoalManager_PlayGoalWinStream(CStruct *pParams, CScript *pScript) {
    fn_80185E9C(Game_GetGoalManager(), pParams);
    return true;
}
