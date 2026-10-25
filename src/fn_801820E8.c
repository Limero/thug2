// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801820E8-0x80182150 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801820E8(Unk_FFAD6788 *);
s32 fn_80182B5C(void *, void *);
s32 fn_801820E8(Unk_FFAD6788 *arg0) {
    s32 var_r29;
    s32 var_r31;

    var_r29 = 0;
    var_r31 = 0;
    while (var_r31 < (s32) arg0->unk0x68) {
        if (fn_80182B5C(arg0, var_r31) == 0) {
            var_r29 += 1;
        }
        var_r31 += 1;
    }
    return var_r29;
}
