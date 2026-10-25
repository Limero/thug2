// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80129A90-0x80129AFC (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
u8 *fn_8012CBA0(u8 *, f32);
u8 *fn_80129574(u8 *, s8, s32);
s32 fn_80129A90(s32 arg0, f32 *arg1, u8 *arg2, u32 arg3) {
    register s32 p0 __asm__("r0");
    register s32 t30 __asm__("r30");
    s32 a0;
    s32 a1;
    s32 b0;
    s32 var_r3;

    a0 = arg0;
    p0 = arg2;
    t30 = arg2;
    a1 = (s32)arg1;
    __asm__("" : "+r"(a0));
    __asm__("" : "+r"(a0));
    var_r3 = 0;
    if (arg3 > 0x10U) {
        b0 = a0;
        __asm__("" : "+r"(b0));
        var_r3 = (s32)fn_8012CBA0(fn_8012CBA0(fn_8012CBA0(fn_80129574((u8 *)p0, 6, b0), ((f32 *)a1)[1]), ((f32 *)a1)[2]), ((f32 *)a1)[3]) - t30;
    }
    return var_r3;
}
