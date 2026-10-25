// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183BC0-0x80183C7C (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_8018D924(Unk_C7387A53 *arg0);
s32 fn_80183BC0(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    s32 var_r27;
    void *temp_r3;
    Unk_31DE137E *temp_r9;
    Unk_FFAD6788 *temp_r9_2;

    temp_r3 = GoalManager_GetGoal(arg0, arg1, 1);
    var_r27 = 0;
    if (temp_r3 == NULL) {
        if (arg2 != 0) {
            return 0;
        }
        goto block_8;
    }
    if (fn_8018D924(temp_r3) == 0) {
        temp_r9 = ((Unk_C8FEE62D *)temp_r3)->unk0x14;
        var_r27 = ((s32 (*)(void *))temp_r9->unk0x64)((char *)temp_r3 + (s32)*(s16 *)((char *)temp_r9 + 0x60));
        if (var_r27 != 0) {
            temp_r9_2 = ((Unk_C8FEE62D *)temp_r3)->unk0x14;
            if ((((s32 (*)(void *))temp_r9_2->unk0xD4)((char *)temp_r3 + (s32)*(s16 *)((char *)temp_r9_2 + 0xD0)) != 0) && ((s32) **((s32 * *)&((Unk_C8FEE62D *)temp_r3)->unk0x30) == 0)) {
                arg0->unk0x38 = arg1;
            }
        }
    }
block_8:
    return var_r27;
}
