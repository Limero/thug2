// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018B098-0x8018B16C (212B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 Game_GetGoalManager(void);
s32 fn_80184168(Unk_9994C3F5 *);
s32 fn_80183A64(s32, s32);
s32 fn_80190840(Unk_C7387A53 *);
s32 Script_GetInteger(s32, s32);
void AddInteger(CStruct *, s32, s32);

bool ScriptGoalManager_GetActiveRewardPoints(s32 arg0, CScript *arg1) {
    s32 temp_r28;
    s32 temp_r30_2;
    s32 temp_r31;
    s32 var_r26;
    s32 var_r27;
    s32 var_r29;
    Unk_C8FEE62D *temp_r30;
    Unk_5BE2D2B7 *temp_r9;

    var_r27 = 0;
    var_r26 = 0;
    temp_r28 = Game_GetGoalManager();
    var_r29 = 0;
    while (var_r29 < fn_80184168(temp_r28)) {
        temp_r30 = fn_80183A64(temp_r28, var_r29);
        temp_r31 = fn_80190840(temp_r30);
        temp_r9 = temp_r30->unk0x14;
        if (temp_r9->unk0xAC((char *)temp_r30 + temp_r9->unk0xA8) != 0) {
            var_r27 += temp_r31;
        }
        var_r26 += temp_r31;
        var_r29 += 1;
    }
    temp_r30_2 = arg1->unk0x18;
    AddInteger(temp_r30_2, QB_ACTIVE_POINTS, var_r27 + Script_GetInteger(QB_TOTAL_CHEAT_POINTS, 0));
    AddInteger(arg1->unk0x18, QB_TOTAL_POINTS, var_r26);
    return true;
}
