// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80227EBC-0x80227FAC (240B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 Game_GetGoalManager();
extern s32 GoalManager_GetGoal(s32, s32, s32);
extern s32 fn_8021D358(s32, u16);
extern s32 NextItem(s32);
extern void fn_8018ED70(Unk_C7387A53 *, void *);
extern void AddString(CStruct *, s32, void *);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
bool fn_80227EBC(CScript *arg0) {
    s32 sp8;
    Unk_C7387A53 *temp_r29;
    s32 var_r28;
    register void *temp_r30 __asm__("r30");
    CStruct *temp_r31;

    temp_r31 = *(void **)arg0;
    temp_r30 = *((void * *)&arg0->unk0x18);
    if ((var_r28 = GoalManager_GetGoal(Game_GetGoalManager(), temp_r31->unk0x4, 1)) != 0) {
        sp8 = 0;
        temp_r29 = (void *)fn_8021D358((s32)temp_r30, (u16)(s8)*(u8 *)temp_r31);
        if (*(s32 *)((char *)(s32)NextItem((s32)temp_r30) + 0x34) == temp_r29->unk0x34) {
            fn_8018ED70((void *)var_r28, &sp8);
            AddString(temp_r31 = (void *)CStruct_ctor(CStruct_new(8)), QB_PLAYERNAME, (char *)temp_r29 + 0x3C);
            AddString((s32)temp_r31, QB_GOALTEXT, (void *)sp8);
            Script_RunScript(QB_GOAL_ATTACK_STARTED_GOAL_OTHER_SAME_TEAM, temp_r31, 0, 0, 0);
            if ((s32)temp_r31 != 0) {
                CStruct_delete((s32)temp_r31, 3);
            }
        }
    }
    return true;
}
