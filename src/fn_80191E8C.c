// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80191E8C-0x80191FD4 (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80301A38[];
s32 CStruct_new(s32);
void CStruct_delete(CStruct *, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void AddChecksum(CStruct *, s32, s32);
s32 CStruct_ctor(s32);
void fn_8009F9AC(Unk_6A70655D *, s32);
s32 fn_800A398C(s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 Game_GetGoalManager(void);
s32 fn_80191FD4(s32 *);

void fn_80191E8C(s32 *arg0, s32 arg1) {
    /* The GetChecksum_2 out-param reload.  Pinning it to r4 is what makes the
     * whole call-setup window match -- see the note above. */
    register s32 sp8r4 __asm__("r4");
    s32 sp8;
    s32 temp_r31;
    s32 temp_r31_2;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_4;
    s32 var_r3;
    void *temp_r3_3;
    Unk_5BE2D2B7 *temp_r9;

    temp_r31 = fn_80191FD4(arg0);
    temp_r3 = ContainsFlag(temp_r31, QB_NULL_GOAL);
    if (temp_r3 == 0) {
        sp8 = temp_r3;
        GetChecksum_2(temp_r31, QB_TRIGGER_OBJ_ID, &sp8, 0);
        sp8r4 = sp8;
        if (sp8r4 != 0) {
            temp_r3_2 = fn_800A398C(*(s32 *)&lbl_80301A38);
            if (temp_r3_2 != 0) {
                fn_8009F9AC(temp_r3_2, arg1);
            }
            temp_r31_2 = CStruct_ctor(CStruct_new(8));
            AddChecksum(temp_r31_2, QB_GOAL_ID, *arg0);
            if (arg1 != 0) {
                Script_RunScript(QB_GOAL_PED_KILL_ARROW, temp_r31_2, 0, 0, 0);
            } else {
                temp_r3_3 = GoalManager_GetGoal(Game_GetGoalManager(), *arg0, 0);
                var_r3 = 1;
                if (temp_r3_3 != NULL) {
                    temp_r9 = ((Unk_C8FEE62D *)temp_r3_3)->unk0x14;
                    temp_r3_4 = temp_r9->unk0xAC(temp_r3_3 + temp_r9->unk0xA8);
                    var_r3 = temp_r3_4 == 0;
                }
                if (var_r3 != 0) {
                    Script_RunScript(QB_GOAL_ADD_PED_ARROW, temp_r31_2, 0, 0, 0);
                }
            }
            if (temp_r31_2 != 0) {
                CStruct_delete(temp_r31_2, 3);
            }
        }
    }
}
