// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801840A4-0x801840F0 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct VT_7A53 {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0x10];
    s16 unk0x20;
    char pad0x22[0x2];
    s32 unk0x24;
} VT_7A53;

s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_801840A4(s32 arg0, s32 arg1) {
    void *temp_r3;
    VT_7A53 *temp_r9;

    temp_r3 = GoalManager_GetGoal(arg0, arg1, 0);
    if (temp_r3 != NULL) {
        temp_r9 = *(VT_7A53 **)((char *)temp_r3 + 0x14);
        return ((s32 (*)(void *))temp_r9->unk0x24)((char *)temp_r3 + temp_r9->unk0x20);
    }
    return 0;
}
