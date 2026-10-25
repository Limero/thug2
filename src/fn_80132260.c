// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80132260-0x8013229C (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern bool lbl_803032F0[];

// sSameOrLowerPrecedence @ 0x80132260
s32 sSameOrLowerPrecedence(s32 arg0, s32 arg1) {
    if (arg0 == arg1) {
        return 1;
    }
    return lbl_803032F0[arg0] <= lbl_803032F0[arg1];
}
