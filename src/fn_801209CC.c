// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801209CC-0x80120A00 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8039D940[];
s32 fn_801209CC(void) {
    s32 *base = (s32 *)lbl_8039D940;
    if (base[0x30] != 0) {
        return 4;
    }
    if (base[0x64] != 0) {
        return 2;
    }
    return 1;
}
