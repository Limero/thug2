// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001E1D4-0x8001E248 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

void fn_8001DC30(s32);

void fn_8001E1D4(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r31;

    switch (arg1) {
    case 0x11:
        var_r31 = 0;
        break;
    case 0x13:
        var_r31 = 1;
        break;
    case 0x16:
        var_r31 = 2;
        break;
    default:
        var_r31 = 2;
        break;
    }
    fn_8001DC30(arg2 | QB_UNKNOWN_0xF4000000);
    fn_8001DC30(var_r31 | (arg0 << 2) | QB_UNKNOWN_0xF5000000);
}
