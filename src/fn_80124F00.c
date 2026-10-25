// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80124F00-0x80124F44 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 lbl_80303150;
extern s32 lbl_80303154;
s32 Tmr_GetTime(void);
s32 fn_800145AC(void);

void fn_80124F00(void) {
    lbl_80303150 += Tmr_GetTime();
    lbl_80303154 = fn_800145AC();
}
