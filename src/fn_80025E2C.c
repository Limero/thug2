// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80025E2C-0x80025E64 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_803C9E40[16];
void fn_80025E2C(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x10; i++) {
        if (lbl_803C9E40[i] == arg0) {
            lbl_803C9E40[i] = 0;
            return;
        }
    }
}
