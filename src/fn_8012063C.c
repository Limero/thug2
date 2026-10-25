// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012063C-0x80120664 (40B). Byte-identical.
#include "types.h"
s32 Mem_Free2();                                  

s32 fn_8012063C(s32 arg0) {
    s32 var_r3;

    var_r3 = arg0;
    if (var_r3 != 0) {
        var_r3 = Mem_Free2();
    }
    return var_r3;
}
