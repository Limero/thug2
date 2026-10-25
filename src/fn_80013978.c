// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013978-0x800139D4 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 lbl_803C9C38[16];
extern s32 lbl_802FFF0C;

bool fn_80013978(s32 arg0) {
    s32 i;
    s32 n;

    for (i = 0; i < 0x10; i++) {
        if (arg0 == lbl_803C9C38[i]) {
            n = lbl_802FFF0C - 1;
            lbl_802FFF0C = n;
            lbl_803C9C38[i] = lbl_803C9C38[n];
            lbl_803C9C38[n] = arg0;
            return true;
        }
    }
    return false;
}
