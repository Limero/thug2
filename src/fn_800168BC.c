// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800168BC-0x80016928 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_802FFE50;
extern bool lbl_802FFE58;
extern bool lbl_802FFE68;
extern s32 lbl_802FFE6C;
u32 VIGetTvFormat(void);
void fn_800168BC(void) {
    lbl_802FFE50 = 5;
    if (VIGetTvFormat() == 1) {
        lbl_802FFE68 = 0;
        lbl_802FFE6C = 0x32;
    } else {
        lbl_802FFE68 = 1;
        lbl_802FFE6C = 0x3C;
    }
    lbl_802FFE58 = 1;
}
