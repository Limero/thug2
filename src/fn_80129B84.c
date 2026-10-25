// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80129B84-0x80129C08 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_80129574(s32, s32, s32);
s32 fn_8012A260(s32, s32, s32, s32);

s32 fn_80129B84(s32 arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4) {
    register s32 v0 __asm__("r9");
    register s32 c2 __asm__("r0");
    register s32 p2 __asm__("r28");
    register s32 v3 __asm__("r30");
    register s32 d __asm__("r31");
    s32 t, r;

    v0 = arg0;
    c2 = arg2;
    p2 = c2;
    v3 = arg3;
    if (v3 <= 4U) {
        return 0;
    }
    t = fn_80129574(c2, 0xC, v0);
    d = t - p2;
    r = fn_8012A260(arg1, t, v3 - d, arg4);
    if (r == 0) {
        return 0;
    }
    return d + r;
}
