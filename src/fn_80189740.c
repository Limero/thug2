// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189740-0x801897A0 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Game_GetGoalManager(void);
extern void *fn_801868AC(s32 arg0);
extern s32 fn_8018E24C(Unk_C7387A53 * arg0);
extern void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);

bool ScriptGoalManager_IsInCompetition(s32 arg0, CScript *arg1) {
    void *temp_r3;

    temp_r3 = fn_801868AC(Game_GetGoalManager());
    if (temp_r3 != 0) {
        AddChecksum(arg1->unk0x18, QB_GOAL_ID, fn_8018E24C(temp_r3));
        return true;
    } else {
        return false;
    }
}
