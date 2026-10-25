// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801952F8-0x80195464 (364B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 fn_80129528(CStruct *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801745B4(s32);
s32 fn_801403CC(void *);
s32 fn_8018E24C(Unk_C7387A53 *);
s32 Game_GetGoalManager(void);
s32 fn_80184EB4(s32, s32, s32, s32, s32);
s32 fn_8018513C(s32, s32);
s32 fn_80183F08(Unk_C7387A53 *, s32);
s32 AddInteger(CStruct *, s32, s32);
void fn_801952F8(Unk_C7387A53 *arg0) {
    void *sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 temp_r27;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 var_r29;

    GetArray(arg0->unk0x20, QB_HORSE_SPOTS, &sp8, 1);
    var_r29 = 0;
    temp_r27 = ((CStruct *)sp8)->unk0x4;
    while (var_r29 < temp_r27) {
        temp_r30 = fn_80129528(sp8, var_r29);
        GetChecksum_2(temp_r30, QB_FLAG, &spC, 1);
        GetInteger(arg0->unk0x24, spC, &sp10, 1);
        if (sp10 == 0) {
            if (GetInteger(temp_r30, QB_SCORE, &sp14, 0) == 0) {
                GetInteger(arg0->unk0x20, QB_SCORE, &sp14, 1);
            }
            break;
        }
        var_r29++;
    }
    if (var_r29 != temp_r27) {
        temp_r29 = *(s32 *)((char *)fn_801403CC(fn_801745B4(lbl_80305EAC)) + (s32)0x24);
        if (temp_r29 > 0) {
            temp_r30 = fn_8018E24C(arg0);
            temp_r31 = Game_GetGoalManager();
            if (temp_r29 > sp14) {
                fn_80184EB4(temp_r31, temp_r30, spC, 1, 0);
                fn_8018513C(temp_r31, temp_r30);
            } else {
                fn_80183F08(temp_r31, temp_r30);
            }
        }
        AddInteger(arg0->unk0x20, QB_SHOULD_CHECK_TRICK, 0);
    }
}
