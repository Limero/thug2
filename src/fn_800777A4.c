// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800777A4-0x800777E8 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_8037B5E8[];
void fn_800777A4(s32 arg0) {
    if (arg0 != 0) {
        if (lbl_8037B5E8[0x6D] == 0) {
            lbl_8037B5E8[0x6D] = 1;
        }
    } else if (lbl_8037B5E8[0x6D] == 1) {
        lbl_8037B5E8[0x6D] = arg0;
    }
}
