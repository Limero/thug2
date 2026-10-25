// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A275C-0x801A27CC (112B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801A269C(Unk_31DE137E *);
void *fn_801A26E0(Unk_31DE137E *, s32);
s32 fn_800AB3FC(Unk_C7387A53 *);
s32 fn_801A275C(Unk_31DE137E *arg0, s32 arg1) {
    s32 var_r30;
    void *temp_r31;

    for (var_r30 = 0; var_r30 < fn_801A269C(arg0); var_r30++) {
        temp_r31 = fn_801A26E0(arg0, var_r30);
        if (fn_800AB3FC(temp_r31) == arg1) {
            return temp_r31;
        }
    }
    return 0;
}
