// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802432E8-0x80243318 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802432E8(void *arg0) {
    void *temp_r0;
    Unk_C7387A53 *var_r3;

    var_r3 = arg0;
    if (var_r3 != NULL) {
        do {
            var_r3 = var_r3->unk0xC;
            temp_r0 = var_r3;
            __asm__("" : "+r"(temp_r0));
            if (var_r3 != NULL) {
                do {
                    var_r3 = var_r3->unk0xC;
                } while (var_r3 != NULL);
            }
            var_r3 = temp_r0;
        } while (var_r3 != NULL);
    }
}
