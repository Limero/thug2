// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184EB4-0x80184F20 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0xA0];
    s16 unk0xA0;
    s32 unk0xA4;
} Rec_80184EB4;
void *GoalManager_GetGoal(s32, s32, s32);
s32 fn_80184EB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_r3;
    Rec_80184EB4 *temp_r9;

    temp_r3 = GoalManager_GetGoal(arg0, arg1, 0);
    if (temp_r3 == NULL) {
        return 0;
    }
    temp_r9 = (Rec_80184EB4 *) ((Unk_C8FEE62D *) temp_r3)->unk0x14;
    return ((s32 (*)(void *, s32, s32, s32)) temp_r9->unk0xA4)((char *) temp_r3 + temp_r9->unk0xA0, arg2, arg3, arg4);
}
