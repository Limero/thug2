// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121448-0x801214B8 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_8039B8C0[];
extern s32 lbl_80302F04;

s32 fn_80121448(s32 arg0) {
    s32 flags;

    if (arg0 > 2) {
        return 0;
    }
    if (lbl_8039B8C0[arg0] != 0) {
        return 4;
    }
    flags = lbl_80302F04;
    if (flags & (0x2000 << arg0)) {
        return 4;
    }
    if (flags & (0x200 << arg0)) {
        return 2;
    }
    return 1;
}
