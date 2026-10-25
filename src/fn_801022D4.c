// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801022D4-0x80102348 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80381048[];
extern char lbl_80381088[];
extern f32 lbl_8029C920;
void fn_80003830(void *, f32, f32, f32);
void fn_801022D4(s32 arg0, s32 arg1) {
    register f32 temp_f1 __asm__("fr1");
    f32 temp_f2;
    f32 temp_f0;
    f32 *base;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        temp_f1 = lbl_8029C920;
        temp_f2 = temp_f1;
        __asm__("" : "+f"(temp_f2));
        fn_80003830((s32)lbl_80381048, temp_f1, temp_f2, temp_f2);
        temp_f0 = lbl_8029C920;
        base = (f32 *)lbl_80381088;
        *(f32 *)lbl_80381088 = temp_f0;
        base[1] = temp_f0;
        base[2] = temp_f0;
        base[3] = temp_f0;
    }
}
