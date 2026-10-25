// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001E66C-0x8001E6F0 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void (*lbl_80300280)(u32);
void fn_8001E66C(s32 arg0, u32 *arg1) {
    u32 t = *arg1;
    s32 b = arg0 * 2;
    u32 alpha0 = ((b + 0xE0) << 24) | 0x800000;
    u32 alpha1 = ((b + 0xE1) << 24) | 0x800000;
    u32 color0 = (t >> 24) | ((t << 12) & 0xFF000) | alpha0;
    u32 color1 = ((t >> 8) & 0xFF) | ((t >> 4) & 0xFF000) | alpha1;
    lbl_80300280(color0);
    lbl_80300280(color1);
}
