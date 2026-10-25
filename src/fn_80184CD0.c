// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184CD0-0x80184D74 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *GoalManager_GetGoal(void *arg0, void *arg1, s32 arg2);
extern void fn_8018EC08(Unk_C7387A53 * arg0);
extern void fn_8018EC38(Unk_C7387A53 * arg0);
s32 fn_80184CD0(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    Unk_C8FEE62D *temp_r3;
    s32 var_r3;

    temp_r3 = GoalManager_GetGoal(arg0, arg1, 1);
    if (temp_r3 == NULL) {
        if (arg2 != 0) {
            return 0;
        }
    }
    fn_8018EC08(temp_r3);
    var_r3 = ((Unk_A22CEC5B *)temp_r3->unk0x14)->unk0x64((char *)temp_r3 + ((Unk_A22CEC5B *)temp_r3->unk0x14)->unk0x60);
    if (var_r3 != 0) {
        if (((Unk_A22CEC5B *)temp_r3->unk0x14)->unk0xD4((char *)temp_r3 + ((Unk_A22CEC5B *)temp_r3->unk0x14)->unk0xD0) != 0) {
            arg0->unk0x38 = arg1;
        }
    }
    fn_8018EC38(temp_r3);
    return var_r3;
}
