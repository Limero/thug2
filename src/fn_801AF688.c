// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF688-0x801AF6CC (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801AF688(CStruct *arg0) {
    CStruct *var_r9;
    register s32 var_r3 __asm__("r3");

    var_r9 = *((void * *)&arg0->unk0x10);
    var_r3 = 0;
    if (var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    if (var_r9 == NULL) {
        return var_r3;
    }
    do {
        var_r9 = *((void * *)&var_r9->unk0xC);
        var_r3 += 1;
        if (var_r9->unk0x4 == -1) {
            var_r9 = NULL;
        }
    } while (var_r9 != NULL);
    return var_r3;
}
