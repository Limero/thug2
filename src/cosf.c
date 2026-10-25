// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80271070-0x8027114C (220B). Byte-identical.
#include "types.h"
#include "qb_constants.h"

extern f32 fn_80271A34(s32 arg0, f32 arg1, f32 arg2);
extern f32 fn_80271948(f32 arg0, f32 arg1);
extern s32 fn_80271CF4(f32 *arg0);

/* newlib's `zero` constant lives in .sdata at 0x803CA744; read it as a plain
   scalar extern so ngccc emits the R_PPC_EMB_SDA21 reloc the target object
   has (per-object `-msdata=eabi -G4` in configure.py). The previous
   `__asm__ volatile("lfs %0,-0x7b3c(13)")` hardcoded the final displacement
   and left objdiff unable to prove the operand. */
extern f32 lbl_803CA744;

f32 cosf(f32 farg0) {
    volatile f32 sp8[2];
    f32 zero;
    union { f32 f; s32 i; } u;
    s32 ix;
    register s32 ix9 __asm__("r9");
    zero = lbl_803CA744;
    __asm__ volatile("");
    u.f = farg0;
    ix9 = u.i & QB_UNKNOWN_0x7FFFFFFF;
    __asm__ volatile("" : "+r"(ix9));
    ix = ix9;
    if (ix <= QB_UNKNOWN_0x3F490FD8) {
        return fn_80271948(farg0, zero);
    }
    if (ix > QB_UNKNOWN_0x7F7FFFFF) {
        return farg0 - farg0;
    }
    switch (fn_80271CF4(&sp8[0]) & 3) {
    case 0:
        return fn_80271948(sp8[0], sp8[1]);
    case 1:
        return -fn_80271A34(1, sp8[0], sp8[1]);
    case 2:
        return -fn_80271948(sp8[0], sp8[1]);
    default:
        return fn_80271A34(1, sp8[0], sp8[1]);
    }
}
