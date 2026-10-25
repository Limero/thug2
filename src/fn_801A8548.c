// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A8548-0x801A8580 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_801A8548(Unk_C8FEE62D *arg0) {
    char *var_r9;
    s32 var_ctr;

    var_ctr = 8;
    var_r9 = (char *)arg0 + 0x3C;
    do {
        *(s32 *)var_r9 = 0;
        var_r9 -= 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x1C = 0;
    arg0->unk0x40 = 0;
    arg0->unk0x44 = 0;
    return true;
}
