// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801890DC-0x80189114 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetString(CStruct *, s32 *, s32 *, s32);
s32 fn_801855E0(s32, s32);
s32 Game_GetGoalManager(void);
// ScriptGoalManager_HasBeatenGoalWithProset @ 0x801890DC
void ScriptGoalManager_HasBeatenGoalWithProset(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetString(pParams, 0, &sp8, 1);
    fn_801855E0(Game_GetGoalManager(), sp8);
}
