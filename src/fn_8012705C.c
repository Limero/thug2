// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012705C-0x801270B4 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80117E28(void *);
void fn_801266EC(Unk_5D1D68CC *);
// CStruct_dtor @ 0x8012705C
void CStruct_dtor(CStruct *arg0) {
    void *temp_r30;
    Unk_C7387A53 *var_r31;

    var_r31 = arg0->unk0x4;
    if (var_r31 != NULL) {
        do {
            temp_r30 = var_r31->unk0xC;
            fn_801266EC(var_r31);
            fn_80117E28(var_r31);
            var_r31 = temp_r30;
        } while (var_r31 != NULL);
    }
    arg0->unk0x4 = NULL;
}
