// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020A604-0x8020A724 (288B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801259C8(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 fn_802093E8(Unk_59E38960 *, CStruct *);
s32 fn_80206D2C(s32, s32);
s32 fn_80206DE4(void *, CStruct *);
s32 fn_80207990(void *, CStruct *, s32, s32, s32);
s32 fn_800145AC(void);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8020A604(Unk_D386C1E6 *arg0, s32 arg1, s32 arg2) {
    s32 temp_r26;
    s32 temp_r28;
    s32 temp_r30;
    s32 temp_r3_2;
    s32 var_r27;
    CStruct *temp_r3;

    temp_r3 = fn_801259C8(arg1, 0);
    if (temp_r3 != NULL) {
        temp_r26 = temp_r3->unk0x4;
        for (var_r27 = 0; var_r27 < temp_r26; var_r27++) {
            temp_r3_2 = fn_80129528(temp_r3, var_r27);
            if ((fn_802093E8(arg0, temp_r3_2) != 0) && ((temp_r30 = fn_80206D2C(arg0, temp_r3_2), temp_r28 = fn_80206DE4(arg0, temp_r3_2), ((fn_80207990(arg0, temp_r30, 8, -5, 0) == 0) == 0)) || (fn_80207990(arg0, temp_r28, 8, -5, 0) != 0))) {
                arg0->unk0x12F8 = arg1;
                arg0->unk0x12FC = var_r27;
                arg0->unk0x1300 = fn_800145AC();
                arg0->unk0x1304 = -1;
                arg0->unk0x1308 = arg2;
                GetInteger(temp_r3_2, QB_DURATION, (char *)arg0 + 0x1304, 0);
                arg0->unk0x12F4 = 1;
            }
        }
    }
}
