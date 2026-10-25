// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020A8FC-0x8020A98C (144B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801259C8(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 fn_8020A808(Unk_59E38960 *, s32, s32);
s32 fn_8020A8FC(Unk_59E38960 *arg0, s32 arg1, s32 arg2) {
    s32 temp_r30;
    s32 var_r28;
    s32 var_r31;
    CStruct *temp_r3;

    var_r28 = 0;
    temp_r3 = fn_801259C8(arg1, 0);
    temp_r30 = temp_r3->unk0x4;
    for (var_r31 = 0; var_r31 < temp_r30; var_r31++) {
        if (fn_8020A808(arg0, fn_80129528(temp_r3, var_r31), arg2) != 0) {
            var_r28 |= 1 << var_r31;
        }
    }
    return var_r28;
}
