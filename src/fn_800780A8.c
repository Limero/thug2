// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800780A8-0x80078104 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800780A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 *arg4, u8 *arg5, u8 *arg6, u8 *arg7) {
    s32 temp_r3;

    temp_r3 = ((arg3 * arg1) + arg2) * 4;
    *arg4 = *(u8 *)(arg0 + temp_r3);
    if (arg5 != NULL) {
        *arg5 = *(u8 *)(arg0 + temp_r3 + 1);
    }
    if (arg6 != NULL) {
        *arg6 = *(u8 *)(arg0 + temp_r3 + 2);
    }
    if (arg7 != NULL) {
        *arg7 = *(u8 *)(arg0 + temp_r3 + 3);
    }
}
