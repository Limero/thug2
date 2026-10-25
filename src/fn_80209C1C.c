// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80209C1C-0x80209D4C (304B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80303150;
s32 fn_801259C8(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 fn_802093E8(Unk_59E38960 *, CStruct *);
s32 fn_80206D2C(s32, s32);
s32 fn_80206DE4(void *, CStruct *);
s32 fn_80207990(void *, CStruct *, s32, s32, s32);
s32 Tmr_GetTime(void);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80209C1C(Unk_8D6DF6EE *arg0, s32 arg1, s32 arg2, s32 arg3) {
    CStruct *entry;
    s32 count;
    s32 var_r27;
    s32 temp_r28;
    s32 temp_r30;
    register s32 temp_r29 __asm__("r29");
    s32 temp_r3;

    entry = fn_801259C8(arg1, 0);
    if (entry == 0) {
        return;
    }
    count = entry->unk0x4;
    for (var_r27 = 0; var_r27 < count; var_r27++) {
        s32 lbl_sum;
        temp_r28 = fn_80129528(entry, var_r27);
        if (fn_802093E8(arg0, temp_r28) == 0) {
            continue;
        }
        temp_r30 = fn_80206D2C(arg0, temp_r28);
        temp_r29 = fn_80206DE4(arg0, temp_r28);
        if ((fn_80207990(arg0, temp_r30, 4, arg2, 0) != 0) || (fn_80207990(arg0, temp_r29, 4, arg2, 0) != 0)) {
            arg0->unk0x12B0 = arg1;
            arg0->unk0x12B4 = var_r27;
            temp_r3 = Tmr_GetTime();
            lbl_sum = lbl_80303150 + temp_r3;
            arg0->unk0x12BC = -1;
            arg0->unk0x12C0 = arg3;
            arg0->unk0x12B8 = lbl_sum;
            GetInteger(temp_r28, QB_DURATION, (char *)arg0 + 0x12BC, 0);
            arg0->unk0x12AC = 1;
        }
    }
}
