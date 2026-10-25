// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AB7C-0x8018AC00 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(void);
void fn_80127C14(CStruct *, s32, CStruct *);
s32 fn_80127358(CStruct *, Unk_C7387A53 *);
void AddInteger(CStruct *, s32, s32);
bool ScriptGoalManager_GetTeam(s32 arg0, CScript *arg1) {
    s32 var_r30 = 0;
    s32 team = *(s32 *)((char *)Game_GetGoalManager() + (s32)0x5C);
    s32 temp_r3;

    fn_80127C14(arg1->unk0x18, QB_TEAM, team);
    {
        register s32 t3 __asm__("r3");
        register s32 var_r4 __asm__("r4");
        t3 = team;
        var_r4 = 0;
        goto test;
body:
        var_r4 = temp_r3;
        var_r30 += 1;
        t3 = team;
test:
        temp_r3 = fn_80127358(t3, var_r4);
        if (temp_r3 != 0) goto body;
    }
    AddInteger(arg1->unk0x18, QB_NUM_TEAM_MEMBERS, var_r30);
    return true;
}
