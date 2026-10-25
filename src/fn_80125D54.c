// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125D54-0x80125DAC (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os
#include "types.h"
#include "types.h"
void *fn_80125568(s32);
void fn_80125D54(s32 arg0, s32 *arg1, s32 arg2) {
    s32 *var_r31;
    void *temp_r3;

    var_r31 = arg1;
    if (*var_r31 != 0) {
        s32 var_r29 = 9;

        do {
            temp_r3 = fn_80125568(*var_r31);
            *(u8 *)((char *)temp_r3 + 2) = var_r29;
            *(s32 *)((char *)temp_r3 + 0xC) = (s32)var_r31;
            var_r31 = (s32 *)((char *)var_r31 + arg2);
        } while (*var_r31 != 0);
    }
}
