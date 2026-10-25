// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9890-0x801F98B4 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801F9890(Unk_C7387A53 *arg0) {
    s32 var_r3;
    Unk_C7387A53 *var_r9;

    var_r3 = 0;
    var_r9 = arg0->unk0xC;
    if (var_r9 != NULL) {
        do {
            var_r9 = var_r9->unk0x24;
            var_r3 = var_r3 + 1;
        } while (var_r9 != NULL);
    }
    return var_r3;
}
