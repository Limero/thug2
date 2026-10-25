// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80129890-0x801298EC (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_80129574(s32, s32, s32);
s32 fn_8012CB7C(s32, u32);
s32 fn_80129890(s32 arg0, u32 arg1, s32 arg2, u32 arg3) {
    register s32 p0 __asm__("r0");
    register s32 t30 __asm__("r30");
    s32 a0;
    s32 a1;
    s32 b0;
    s32 var_r3;
    a0 = arg0;
    p0 = arg2;
    t30 = arg2;
    a1 = arg1;
    __asm__("" : "+r"(a0));
    __asm__("" : "+r"(a0));
    var_r3 = 0;
    if (arg3 > 8U) {
        b0 = a0;
        __asm__("" : "+r"(b0));
        var_r3 = fn_8012CB7C(fn_80129574(p0, 0xD, b0), a1) - t30;
    }
    return var_r3;
}
