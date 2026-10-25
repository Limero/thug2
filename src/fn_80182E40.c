// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182E40-0x80182E98 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80182E40(CStruct *arg0) {
    void *temp_r30;
    Unk_9994C3F5 *var_r30;

    var_r30 = arg0->unk0x8;
    if (var_r30 != NULL) {
        do {
            temp_r30 = var_r30->unk0x8;
            Mem_Free(var_r30);
            var_r30 = temp_r30;
        } while (var_r30 != NULL);
    }
    arg0->unk0x8 = NULL;
    arg0->unk0x10 = 0;
    arg0->unk0x4 = 0;
}
