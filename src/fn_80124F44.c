// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80124F44-0x80124FDC (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern u32 lbl_80303154;
extern f32 lbl_80303158;

u32 fn_800145AC(void);

u32 Tmr_GetTime(void) {
    u32 base = lbl_80303154;
    u32 now = fn_800145AC();

    return (u32)(lbl_80303158 * (f32)(now - base));
}
