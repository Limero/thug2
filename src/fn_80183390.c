// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183390-0x801833F4 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80183384(void *);
s32 fn_80182F98(s32, s32);
s32 fn_80182FA8(s32);
void Mem_Free(void);
void fn_80183390(s32 *arg0) {
    s32 temp_r3;
    s32 var_r31;

    var_r31 = 0;
    temp_r3 = fn_80182FA8(*arg0);
    while (var_r31 < temp_r3) {
        fn_80182F98(*arg0, var_r31);
        var_r31 += 1;
        Mem_Free();
    }
    fn_80183384(*arg0);
}
