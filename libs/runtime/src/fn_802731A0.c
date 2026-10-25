// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802731A0-0x80273268 (200B). Byte-identical.
#include "types.h"

/* fdlibm floorf's `huge` and `0.0f` live in .sdata at 0x803CA948/4C.
   They MUST be plain scalar externs read as C so ngccc emits the
   R_PPC_EMB_SDA21 relocs the target object has; spelling them as
   `__asm__ volatile("lfs %0,-0x7938(13)")` hardcodes the final
   displacement and leaves objdiff unable to prove the operand.
   Per-object flags `-msdata=eabi -G4` (configure.py) make them SDA. */
extern f32 lbl_803CA948;
extern f32 lbl_803CA94C;

f32 fn_802731A0(f32 farg0) {
    union { f32 f; u32 i; } v;
    u32 ix;
    s32 e;
    s32 msk;
    register f32 t __asm__("fr0");
    f32 big;
    f32 zerof;
    f32 big2;
    f32 zerof2;
    v.f = farg0;
    ix = v.i;
    e = ((ix >> 23) & 0xff) - 0x7f;
    if (e > 0x16) {
        goto bigexp;
    }
    if (e < 0) {
        big = lbl_803CA948;
        zerof = lbl_803CA94C;
        t = farg0 + big;
        if (!(t > zerof)) {
            goto retbits;
        }
        if ((s32)ix >= 0) {
            ix = 0u;
            goto retbits;
        }
        if ((ix & 0x7fffffffu) == 0) {
            goto retbits;
        }
        ix = 0xBF800000u;
        goto retbits;
    } else {
        msk = 0x7fffff >> e;
        if ((ix & (u32)msk) == 0) {
            return farg0;
        }
        big2 = lbl_803CA948;
        zerof2 = lbl_803CA94C;
        t = farg0 + big2;
        if (t > zerof2) {
            if ((s32)ix < 0) {
                ix += (u32)(0x800000 >> e);
            }
            ix &= ~(u32)msk;
        }
        goto retbits;
    }
bigexp:
    if (e == 0x80) {
        return farg0 + farg0;
    }
    return farg0;
retbits:
    return *(f32 *)&ix;
}
