// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80226E08-0x80226F04 (252B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager();
void fn_801848C8(s32);
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_8018E6C4(Unk_C7387A53 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void Script_SpawnScript(Unk_15EF4A35 *, s32, s32, Unk_80577C09 *, s32, s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
bool fn_80226E08(void *arg0) {
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s8 temp_r28;
    register s32 var_r4 __asm__("r4");
    char *p;

    p = *(char **)arg0;
    temp_r29 = Game_GetGoalManager();
    fn_801848C8(temp_r29);
    temp_r28 = *(s8 *)p;
    var_r4 = *(s32 *)(p += 1);
    goto check;
    do {
        temp_r30 = GoalManager_GetGoal(temp_r29, var_r4, 1);
        ((void (*)(void *))(((Unk_724636E1 *)((Unk_C8FEE62D *)temp_r30)->unk0x14)->unk0xF4))(
            temp_r30 + ((Unk_724636E1 *)((Unk_C8FEE62D *)temp_r30)->unk0x14)->unk0xF0);
        fn_8018E6C4(temp_r30);
        var_r4 = *(s32 *)p;
    check:
        p += 4;
    } while (var_r4 != 0);
    if (temp_r28 == 1) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        AddChecksum(temp_r31, QB_GOAL_SUMMARY, QB_GOAL_SUMMARY);
        Script_SpawnScript(QB_WAIT_AND_CREATE_VIEW_SELECTED_GOALS_MENU, temp_r31, 0, 0, 0, 0, 0, 0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
    return true;
}
