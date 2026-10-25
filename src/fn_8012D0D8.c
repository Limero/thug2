// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012D0D8-0x8012D11C (68B). Byte-identical.
#include "types.h"
u8 *fn_8012B2A0(void);
void fn_8012D0D8(u8 *arg0) {
    u8 *var_r3;

    var_r3 = arg0;
    while ((s32) *(u8 *)var_r3 != 0x24) {
        var_r3 = fn_8012B2A0();
    }
    if ((s32) *(u8 *)fn_8012B2A0() == 2) {
        fn_8012B2A0();
    }
}
