// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801853A8-0x8018544C (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct {
    char pad0x0[0xA8];
    s16 unk0xA8;
    s32 unk0xAC;
} Rec_801853A8;
s32 GoalManager_GetGoal(s32, s32, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(s32, s32, s32 *, s32);
s32 fn_801853A8(Unk_31DE137E *arg0, s32 arg1) {
    s32 sp8;
    s32 spC;
    s32 temp_r3;
    s32 var_r3;
    Rec_801853A8 *temp_r9;
    s32 (*fp)(char *);

    temp_r3 = GoalManager_GetGoal((s32)arg0, arg1, 0);
    if (temp_r3 != 0) {
        temp_r9 = *(Rec_801853A8 **)((char *)temp_r3 + 0x14);
        fp = temp_r9->unk0xAC;
        return fp((char *)temp_r3 + temp_r9->unk0xA8);
    }
    spC = temp_r3;
    if (GetStructure_2(arg0->unk0x1C, arg1, &sp8, 0) != 0) {
        GetInteger(sp8, QB_HASBEATEN, &spC, 1);
    }
    var_r3 = 1;
    if (spC == 0) {
        var_r3 = 0;
    }
    return var_r3;
}
