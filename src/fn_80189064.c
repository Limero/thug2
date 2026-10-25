// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189064-0x801890DC (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Game_GetGoalManager();
extern s32 ContainsFlag(CStruct *, s32);
extern s32 fn_801855C8(Unk_C7387A53 *);
extern s32 fn_801855C0(Unk_C7387A53 *);
extern void AddInteger(CStruct *, s32, s32);
bool ScriptGoalManager_GetNumberOfGoalPoints(s32 arg0, void *arg1) {
    register s32 a0 __asm__("r30");
    register s32 a1 __asm__("r29");
    s32 temp_r31;
    s32 var_r3;

    a0 = arg0;
    a1 = arg1;
    temp_r31 = Game_GetGoalManager();
    if (ContainsFlag(a0, QB_TOTAL) != 0) {
        var_r3 = fn_801855C8(temp_r31);
    } else {
        var_r3 = fn_801855C0(temp_r31);
    }
    AddInteger(((CScript *)a1)->unk0x18, QB_GOAL_POINTS, var_r3);
    return true;
}
