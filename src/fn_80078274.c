// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80078274-0x80078330 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8007818C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void DCFlushRange(s32 arg0, s32 arg1);
void fn_80078274(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r21;
    s32 temp_r26;
    u32 i;
    u32 j;
    u8 *p;
    temp_r21 = (arg4 + 3) >> 2;
    temp_r26 = (arg3 + 3) >> 2;
    p = (u8 *) arg2;
    for (i = 0U; i < (u32) temp_r21; i++) {
        for (j = 0U; j < (u32) temp_r26; j++) {
            fn_8007818C(arg0, arg1, arg3, arg4, j * 4, i * 4, p);
            p += 0x40;
        }
    }
    DCFlushRange(arg2, arg3 * arg4 * 4);
}
