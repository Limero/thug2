// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000DD2C-0x8000DDA0 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// String-list membership check: scans the 0x44-stride name table at
// arg0+0x20 for one equal to arg1 (strcmp); returns 0 if found else 1.
// Suggested rename: fn_8000DD2C_table_has_string.
#include "types.h"
#include "structs.h"
s32 strcmp(s32, s32);
bool fn_8000DD2C(Unk_A9B14BE5 *arg0, s32 arg1) {
    s32 var_r30;

    var_r30 = 0;
    while (var_r30 < (s32) arg0->unk0x23C) {
        if (strcmp((char *)arg0 + 0x20 + var_r30 * 0x44, arg1) == 0) {
            return false;
        }
        var_r30 += 1;
    }
    return true;
}
