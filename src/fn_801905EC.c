// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801905EC-0x801906BC (208B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Game_GetGoalManager(void);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 GetChecksum(CStruct *, s32);
extern s32 fn_80185380(s32, s32);

void fn_801905EC(Unk_C7387A53 *arg0) {
    s32 sp8;
    void *spC;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r3;
    s32 var_r31;

    temp_r29 = Game_GetGoalManager();
    spC = NULL;
    sp8 = 0;
    if (GetChecksum_2(arg0->unk0x20, QB_REWARD_GOAL, &sp8, 0) != 0) {
        fn_80185380(temp_r29, sp8);
        return;
    }
    if (GetArray(arg0->unk0x20, QB_REWARD_GOAL, &spC, 0) != 0) {
        temp_r30 = ((CStruct *)spC)->unk0x4;
        for (var_r31 = 0; var_r31 < temp_r30; var_r31++) {
            temp_r3 = GetChecksum(spC, var_r31);
            sp8 = temp_r3;
            if (temp_r3 != 0) {
                fn_80185380(temp_r29, temp_r3);
            }
        }
    }
}
