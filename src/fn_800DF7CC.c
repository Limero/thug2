// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DF7CC-0x800DF800 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_800DF7CC(Unk_D4A84CA9 *arg0) {
    s32 var_r9;

    var_r9 = 0;
    if (((s32) arg0->unk0x524 != 0) || ((s32) arg0->unk0x528 != 0)) {
        var_r9 = 1;
    }
    if (var_r9 == 0) {
        return false;
    }
    return true;
}
