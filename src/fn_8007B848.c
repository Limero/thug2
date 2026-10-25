// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B848-0x8007B890 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80094010(u8 *);                               

s32 fn_8007B848(Unk_9994C3F5 *arg0, void *arg1) {
    s32 temp_r3;
    s32 var_r0;

    temp_r3 = fn_80094010(arg1);
    var_r0 = 1;
    arg0->unk0x8 = temp_r3;
    if (temp_r3 == 0) {
        var_r0 = 0;
    }
    return var_r0;
}
