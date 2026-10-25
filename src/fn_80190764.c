// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80190764-0x801907E0 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(void);
s32 fn_80187934(Unk_6BF95B44 *, s32);
s32 fn_80129528(CStruct *, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void fn_8018BA34(Unk_C7387A53 *, CStruct *);

void fn_80190764(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 temp_r3;

    if (GetArray(arg0->unk0x20, QB_DIFFICULTY_LEVEL_PARAMS, &sp8, 0) != 0) {
        temp_r3 = fn_80187934(Game_GetGoalManager(), 0);
        fn_80126FF4(arg0->unk0x20, fn_80129528(sp8, temp_r3));
        fn_8018BA34(arg0, arg0->unk0x20);
    }
}
