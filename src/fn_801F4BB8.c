// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4BB8-0x801F4C88 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 CStruct_delete(s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_801F23F0(void *, s32);
s32 Game_GetGoalManager(void);
s32 fn_801F2184(void *);
void fn_801835B4(s32, s32, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_8018E584(void);
void fn_801F4BB8(void *arg0, s32 arg1) {
    s32 temp_r30;
    s32 temp_r3;
    void *temp_r30_2;
    Unk_4AA2E777 *temp_r9;

    temp_r3 = CStruct_ctor(CStruct_new(8));
    fn_801F23F0(arg0, temp_r3);
    temp_r30 = Game_GetGoalManager();
    fn_801835B4(temp_r30, fn_801F2184(arg0), temp_r3);
    temp_r30_2 = (void *)GoalManager_GetGoal(temp_r30, fn_801F2184(arg0), 1);
    fn_8018E584();
    if (arg1 != 0) {
        *(u8 *)((char *)arg0 + 0x2BD) = 0;
    }
    if (*(u8 *)((char *)arg0 + 0x2BD) != 0) {
        temp_r9 = (Unk_4AA2E777 *)(*((void **)&((Unk_C8FEE62D *)temp_r30_2)->unk0x14));
        temp_r9->unk0xDC((char *)temp_r30_2 + temp_r9->unk0xD8);
    }
    if (temp_r3 != 0) {
        CStruct_delete(temp_r3, 3);
    }
}
