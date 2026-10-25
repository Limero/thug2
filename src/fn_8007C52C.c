// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007C52C-0x8007C56C (64B). Byte-identical.
#include "types.h"
void fn_8007C148(void);
void fn_8007C39C(s32);
void fn_8007C52C(void) {
    s32 var_r31;

    fn_8007C148();
    var_r31 = 0;
    do {
        fn_8007C39C(var_r31);
        var_r31 += 1;
    } while (var_r31 <= 0x1E);
}
