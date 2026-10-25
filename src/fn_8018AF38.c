// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AF38-0x8018AF70 (56B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 Game_GetGoalManager(void);
s32 fn_80183A94(Unk_C7387A53 *);
s32 fn_8019072C(void *);

s32 ScriptGoalManager_GetUnlimitedTimeInNetGame(CStruct *pParams, CScript *pScript) {
    s32 temp_r3;

    temp_r3 = fn_80183A94(Game_GetGoalManager());
    if (temp_r3 == 0) {
        return 1;
    }
    return fn_8019072C(temp_r3);
}
