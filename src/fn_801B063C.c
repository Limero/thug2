// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B063C-0x801B06A0 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801B03E0(CStruct *, void *);
void fn_801B063C(CStruct *arg0, void *arg1) {
    s32 var_r29;
    s32 var_r31;

    var_r31 = 0;
    if (var_r31 < arg0->unk0x4) {
        var_r29 = 0;
        do {
            var_r31 += 1;
            fn_801B03E0((void *)(arg0->unk0x8 + var_r29), arg1);
            var_r29 += 0x14;
        } while (var_r31 < arg0->unk0x4);
    }
}
