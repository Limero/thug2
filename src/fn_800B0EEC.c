// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B0EEC-0x800B0F50 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80301B0C[];
void fn_800B0EEC(void) {
    void *temp_r30;
    CStruct *temp_r3;
    Unk_C7387A53 *var_r30;

    temp_r3 = *(void * *)&lbl_80301B0C;
    if (temp_r3 != NULL) {
        var_r30 = temp_r3->unk0x4;
        if (var_r30 != NULL) {
            do {
                temp_r30 = var_r30->unk0xA8;
                Mem_Free(var_r30);
                var_r30 = temp_r30;
            } while (var_r30 != NULL);
        }
        *(s32 *)((char *)(*(s32 *)&lbl_80301B0C) + (s32)0x4) = NULL;
    }
}
