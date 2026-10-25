// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80167108-0x80167150 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE50[];
s32 s_get_platforms_block_size(void) {
    s32 v;

    v = *(s32 *)&lbl_802FFE50;
    switch (v) {
    case 1:
    case 2:
    case 3:
        return 0x400;
    case 5:
        return 0x2000;
    case 4:
        return 0x4000;
    default:
        return 1;
    }
}
