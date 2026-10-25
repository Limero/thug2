// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DE9A4-0x800DEA08 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8000C5D8(s32, s32, s32);
void fn_800DE9A4(CScript *arg0) {
    char *var_r31;
    s32 var_r30;
    s32 var_r28;

    if (arg0->unk0x1C != 0) {
        var_r30 = 1;
        var_r28 = 0;
        var_r31 = (char *)arg0 + 0x2C;
        do {
            fn_8000C5D8(arg0->unk0x38, var_r30, 0);
            *(s32 *)var_r31 = var_r28;
            var_r31 -= 0xC;
        } while (--var_r30 != -1);
    }
}
