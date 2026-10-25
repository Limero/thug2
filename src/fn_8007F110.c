// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F110-0x8007F15C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80296258[];
extern bool lbl_80377A18;
extern char lbl_80377A08[];

s32 fn_8007F110(void *arg0) {
    f32 f13;
    f32 f12;
    f32 f0;
    f32 f11;

    if (lbl_80377A18 == 0) {
        lbl_80377A18 = 1;
    }
    f13 = *(f32 *)((char *)arg0 + 0x38);
    f0 = *(f32 *)((char *)arg0 + 0x3c);
    f12 = *(f32 *)((char *)arg0 + 0x40);
    f11 = *(f32 *)lbl_80296258;
    *(f32 *)(lbl_80377A08 + 0x0) = f13;
    *(f32 *)(lbl_80377A08 + 0x4) = f0;
    *(f32 *)(lbl_80377A08 + 0x8) = f12;
    *(f32 *)(lbl_80377A08 + 0xc) = f11;
    return (s32)lbl_80377A08;
}
