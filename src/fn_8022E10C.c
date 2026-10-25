// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022E10C-0x8022E16C (96B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8022E33C(CStruct *, CStruct *, s32);
s32 fn_80240C80(void);
void fn_8022E10C(Unk_9994C3F5 *arg0) {
    register void *var_r3 asm("r3");
    void *temp_r31;

    var_r3 = arg0->unk0x8;
    if (var_r3 != NULL) {
        do {
            temp_r31 = ((CStruct *)var_r3)->unk0x8;
            if (((CStruct *)var_r3)->unk0x4 & 0x1000) {
                fn_8022E33C(arg0, fn_80240C80(), 0);
            }
            var_r3 = temp_r31;
        } while (var_r3 != NULL);
    }
}
