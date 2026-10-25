// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014070-0x80014100 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
void Mem_Free_3(s32);
s32 fn_80014070(CStruct *arg0, s32 arg1, s32 arg2) {
    s32 *var_r30;
    s32 var_r28;
    s32 var_r3;
    s32 var_r25;
    void *var_r31;

    var_r3 = 0;
    var_r28 = 0;
    if (var_r3 < (s32) arg0->unk0x10) {
        var_r25 = 0;
        var_r30 = (char *)arg0 + 0x1C38;
        var_r31 = (char *)arg0 + 0x24;
        do {
            if (((s32) *(s32 *)((char *)var_r31 - 0x4) == arg1) && ((s32) ((CStruct *)var_r31)->unk0x0 == arg2)) {
                Mem_Free_3(*var_r30);
                *var_r30 = var_r25;
                var_r3 = 1;
            }
            var_r28 += 1;
            var_r30 += 1;
            var_r31 += 0x10;
        } while (var_r28 < (s32) arg0->unk0x10);
    }
    return var_r3;
}
