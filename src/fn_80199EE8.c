// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80199EE8-0x80199F2C (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 NextItem(s32);
s32 fn_8022A470(CScript *);
s32 fn_80199EE8(void) {
    s32 temp_r3;
    s32 var_r3;

    temp_r3 = NextItem(lbl_80305F9C);
    if (temp_r3 != 0) {
        temp_r3 = fn_8022A470(temp_r3);
        var_r3 = 1;
        if (temp_r3 != 0) {
            goto done;
        }
    }
    var_r3 = 0;
done:
    return var_r3;
}
