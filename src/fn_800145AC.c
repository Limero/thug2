// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800145AC-0x80014638 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern volatile u64 lbl_802FFF38;
extern s32 lbl_802FFE6C;
extern f32 lbl_80290A68;

s32 fn_800145AC(void) {
    return (s32)((f32)(f64)(u32)lbl_802FFF38 *
                 (lbl_80290A68 / (f32)(f64)(s32)lbl_802FFE6C));
}
