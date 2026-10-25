// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B29D8-0x800B2A50 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800607A0(Unk_2FEA250A *, s32, s32, s32);
void fn_8005F1F0(s32, s32);
s32 fn_8005EF7C(s32, s32, s32);
s32 fn_800546A0(s32);
s32 fn_800B29D8(Unk_ADD6B5FC *arg0, s32 arg1) {
    s32 temp_r30;
    s32 var_r3;

    var_r3 = fn_800546A0(arg1);
    if (var_r3 != 0) {
        var_r3 = fn_80057CA0();
        if (var_r3 != 0) {
            temp_r30 = fn_8005EF7C(var_r3, 1, 0);
            fn_8005F1F0(temp_r30, 1);
            var_r3 = fn_800607A0(arg0->unk0x210, temp_r30, 0, 1);
            arg0->unk0x240 = 1;
        }
    }
    return var_r3;
}
