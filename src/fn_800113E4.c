// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800113E4-0x80011454 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
u32 MemAvailable(Unk_C8FEE62D *);
u32 fn_800113E4(Unk_C7387A53 *arg0) {
    u32 temp_r0;
    u32 temp_r3;
    u32 var_r31;
    CStruct *var_r9;

    var_r31 = 0;
    var_r9 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x40) + 0x1C);
    if (var_r9 != NULL) {
        do {
            temp_r0 = (u32) *((u32 *)&var_r9->unk0x8) >> 8U;
            if (temp_r0 >= var_r31) {
                var_r31 = temp_r0;
            }
            var_r9 = var_r9->unk0x0;
        } while (var_r9 != NULL);
    }
    temp_r3 = MemAvailable(arg0->unk0x34);
    if (temp_r3 > var_r31) {
        var_r31 = temp_r3;
    }
    return var_r31;
}
