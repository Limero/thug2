// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AEB58-0x801AEBA0 (72B). Byte-identical.
#include "types.h"
#include "structs.h"

void *fn_801AEB58(Unk_C7387A53 *arg0, s32 arg1) {
    register s32 cnt __asm__("r3");
    void *temp_r0;
    s32 var_r9;
    void *var_r3;
    s32 bound;

    temp_r0 = *((void * *)&arg0->unk0x48);
    if (temp_r0 != NULL) {
        cnt = arg0->unk0x50;
        var_r9 = 0;
        if (var_r9 < cnt) {
            bound = cnt;
            var_r3 = temp_r0;
            do {
                if (((Unk_C7387A53 *)var_r3)->unk0x54 == arg1) {
                    return var_r3;
                }
                var_r9 += 1;
                var_r3 += 0x60;
            } while (var_r9 < bound);
        }
    }
    return NULL;
}
