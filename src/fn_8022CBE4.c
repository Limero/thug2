// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CBE4-0x8022CC20 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_8022CBE4(CStruct *arg0, s32 arg1, s32 arg2) {
    Unk_31DE137E *var_r3;
    s32 var_r9;

    var_r3 = arg0->unk0x4;
    var_r9 = 0;
    while (var_r3 != NULL) {
        if ((s32) var_r3->unk0xC == arg1) {
            if (var_r9 == arg2) {
                return var_r3;
            }
            var_r9 += 1;
        }
        var_r3 = var_r3->unk0x1C;
    }
    return NULL;
}
