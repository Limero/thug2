// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6464-0x801A64A8 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_801A6464(Unk_C7387A53 *arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_r9;
    s32 bound;
    char *var_r3;

    temp_r0 = arg0->unk0x2C;
    var_r9 = 0;
    if (var_r9 < temp_r0) {
        bound = temp_r0;
        __asm__ __volatile__("" : "+r"(bound));
        var_r3 = (char *)arg0 + 0x3C;
        do {
            if (*(s32 *)(var_r3 - 0xC) == arg1) {
                return *(s32 *)var_r3;
            }
            var_r9 += 1;
            var_r3 += 4;
        } while (var_r9 < bound);
    }
    return 0;
}
