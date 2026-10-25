// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015F5F4-0x8015F670 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80127358(CStruct *, Unk_C7387A53 *);
s32 fn_8015F5F4(CStruct *arg0, s32 arg1) {
    s32 var_r29;
    s32 *var_r31;
    s32 *temp_r3;

    var_r31 = fn_80127358(arg0, NULL);
    var_r29 = 0;
    if (var_r31 != NULL) {
        do {
            temp_r3 = fn_80127358(arg0, var_r31);
            if ((*var_r31 & 0x7F0000) == 0x10000 && var_r31[2] == arg1) {
                var_r29 = var_r31[1];
            }
            var_r31 = temp_r3;
        } while (var_r31 != NULL);
    }
    return var_r29;
}
