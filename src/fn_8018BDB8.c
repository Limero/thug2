// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018BDB8-0x8018BE00 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8018B6D0(void *, s32);
void fn_8018BDB8(void *arg0, void *arg1) {
    void *temp_r31;
    CStruct *var_r3;

    var_r3 = arg1;
    if (var_r3 != NULL) {
        do {
            temp_r31 = var_r3->unk0x4;
            if (var_r3 != NULL) {
                fn_8018B6D0(var_r3, 3);
            }
            var_r3 = temp_r31;
        } while (var_r3 != NULL);
    }
}
