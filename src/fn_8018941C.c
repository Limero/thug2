// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018941C-0x80189454 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80185D10(s32, CStruct *);
s32 Game_GetGoalManager(void);
// ScriptGoalManager_PlayGoalStartStream @ 0x8018941C
bool ScriptGoalManager_PlayGoalStartStream(CStruct *pParams, CScript *pScript) {
    fn_80185D10(Game_GetGoalManager(), pParams);
    return true;
}
