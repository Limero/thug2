// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80059EB0-0x80059EE4 (52B). Byte-identical.
#include "types.h"
void Mem_NewZero(s32);
s32 fn_80058F64(void);
s32 fn_80059EB0(s32 arg0) {
    s32 var_r3;

    var_r3 = 0;
    if (arg0 == 1) {
        Mem_NewZero(0x38);
        var_r3 = fn_80058F64();
    }
    return var_r3;
}
