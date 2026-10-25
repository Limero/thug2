// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024D480-0x8024D4D0 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_80250EAC(CStruct *, s32);
s32 fn_8024D480(Unk_C7387A53 *arg0, s32 arg1) {
    s32 var_r3;

    var_r3 = fn_80250EAC(arg0->unk0x44, arg1);
    if ((var_r3 >> (arg1 - 1)) == 0) {
        var_r3 = -(var_r3 ^ ((1 << arg1) - 1));
    }
    return var_r3;
}
