// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FB334-0x801FB358 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801FB334(Unk_C7387A53 *arg0) {
    s32 var_r3;
    CStruct *var_r9;

    var_r9 = arg0->unk0x24;
    var_r3 = 0;
    if (var_r9 == NULL) {
        return var_r3;
    }
    do {
        var_r9 = var_r9->unk0x4;
        var_r3 += 1;
    } while (var_r9 != NULL);
    return var_r3;
}
