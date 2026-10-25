// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003218C-0x800321EC (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80291AD8;
extern f32 lbl_80291ADC;
extern char lbl_80363CD8[];
void fn_8003218C(s32 arg0, u32 arg1) {
    f32 f0;
    f32 f1;
    s32 i;
    f32 *p;

    if (arg1 != 0xFFFF) return;
    if (arg0 == 0) return;
    f0 = lbl_80291AD8;
    f1 = lbl_80291ADC;
    p = (f32 *)lbl_80363CD8;
    for (i = 0; i < 0x40; i++) {
        p[0] = f0;
        p[1] = f0;
        p[2] = f0;
        p[3] = f1;
        p += 4;
    }
    for (i = 0; i < 0x40; i++) {
    }
}
