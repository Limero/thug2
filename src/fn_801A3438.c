// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A3438-0x801A34B4 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_801A26E0(Unk_31DE137E *, s32);
s32 fn_8009EE2C(s32, s32, s32, s32);
s32 fn_801A3438(Unk_31DE137E *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r3;
    void *temp_r3;
    Unk_B1B57F13 *temp_r9;

    temp_r3 = fn_801A26E0(arg0, 0);
    temp_r9 = ((Unk_C8FEE62D *)temp_r3)->unk0x14;
    var_r3 = ((s32 (*)(void *, s32, s32, s32))temp_r9->unk0x2C)(temp_r3 + temp_r9->unk0x28, arg1, arg2, arg3);
    if (var_r3 == 0) {
        var_r3 = fn_8009EE2C(arg0, arg1, arg2, arg3);
    }
    return var_r3;
}
