// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A87F8-0x801A8848 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_801A87F8(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 *var_r9;
    s32 var_ctr;

    if (((s32) arg0->unk0x44 != 0) && ((s32) arg0->unk0x40 == arg1)) {
        var_r9 = (char *)arg0 + 0x3C;
        arg0->unk0x44 = 0;
        arg0->unk0x1C = 0;
        var_ctr = 8;
        do {
            *((s32 *)var_r9) = 0;
            var_r9 = (char *)var_r9 - 4;
            var_ctr -= 1;
        } while (var_ctr != 0);
        return true;
    }
    return false;
}
