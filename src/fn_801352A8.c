// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801352A8-0x8013530C (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80135170(Unk_5B449B03 * arg0, s32 arg1);
void *fn_801352A8(CStruct *arg0, s32 arg1) {
    u32 temp_r0;
    void *var_r31;
    void *var_r3;

    var_r31 = arg0->unk0x4;
    if (var_r31 != NULL) {
        var_r31 += arg1;
        arg0->unk0x4 = var_r31;
    }
    var_r3 = (char *)arg0 + 8;
    if (var_r31 != NULL) {
        do {
            var_r3 = fn_80135170(var_r31, arg1);
            temp_r0 = *((u32 *)&((Unk_C7387A53 *)var_r31)->unk0xC);
            var_r31 = (void *)temp_r0;
            __asm__("" : "+r"(temp_r0));
        } while (temp_r0 != 0U);
    }
    return var_r3;
}
