// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800329A8-0x80032A14 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct W329A8_S {
    u8 _p[0x60];
    f32 a60;
    f32 a64;
} W329A8_S;

extern f32 lbl_80291B3C;
extern f32 lbl_80291B40;
extern s32 fn_80032A60(W329A8_S *arg0);

f32 fn_800329A8(W329A8_S *arg0) {
    switch (fn_80032A60(arg0)) {
    case 2:
        return lbl_80291B3C;
    case 1:
        return arg0->a60 * arg0->a64;
    case 0:
        return lbl_80291B40;
    default:
        return lbl_80291B40;
    }
}
