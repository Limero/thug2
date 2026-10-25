// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D620-0x8002D6AC (140B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8002D620(s32 arg0, u32 arg1, u32 *arg2) {
    s32 var_ctr;
    s32 var_r31;
    u32 temp_r0;
    u32 var_r3;
    void **var_r30;
    Unk_998B8376 *temp_r9;
    CStruct *temp_r9_2;

    var_r31 = 0;
    var_r3 = fn_800145AC();
    var_r30 = arg0 + 4;
    var_ctr = 0x32;
    do {
        temp_r9 = *((s32 *)var_r30);
        if (((u32) temp_r9->unk0x14 >= arg1) && ((u32) temp_r9->unk0x8 < var_r3)) {
            temp_r0 = temp_r9->unk0x168;
            if (!(temp_r0 & 0x40000)) {
                *arg2 = temp_r0 >> 0x13U;
                temp_r9_2 = *((s32 *)var_r30);
                var_r3 = temp_r9_2->unk0x8;
                var_r31 = temp_r9_2->unk0x4;
            }
        }
        var_r30 = (void **)((char *)var_r30 + 4);
        var_ctr -= 1;
    } while (var_ctr != 0);
    return var_r31;
}
