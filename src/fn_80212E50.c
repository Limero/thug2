// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80212E50-0x80212F20 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_802AF670;
extern f32 lbl_802AF674;
extern f32 lbl_802AF678;
extern f32 lbl_802AF67C;
extern f32 lbl_802AF680;
extern f32 atan2f(f32, f32);
void fn_80212E50(Unk_5C9E9D58 *arg0, Unk_5F85C510 *arg1, f32 argF) {
    f32 ang1;
    f32 ang2;
    f32 delta;
    f32 m;
    f32 lim;

    ang1 = atan2f(arg0->unk0x50,
                       arg0->unk0x58);
    ang2 = atan2f(*(f32 *)arg1, *((f32 *)&arg1->unk0x8));
    delta = ang2 - ang1;
    lim = lbl_802AF670;
    arg0->unk0x1A1C = delta;
    if (!(__builtin_fabsf(delta) > lim)) {
        goto pairs;
    }
    m = (delta < lbl_802AF674) ? lbl_802AF678 : lbl_802AF67C;
    arg0->unk0x1A1C -= m * lbl_802AF680;
pairs:
    arg0->unk0x1A08 = *(__ps_t *)arg1;
    arg0->unk0x1A10 = *((__ps_t *)&arg1->unk0x8);
    arg0->unk0x1A18 = argF;
}
