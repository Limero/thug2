// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80135424-0x801354B4 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_8013530C(Unk_1D62F22E *, s32);
void fn_80135424(CStruct *arg0, s32 arg1, s32 (*arg2)(void *, s32, s32), s32 arg3, s32 arg4) {
    void *temp_r29;
    void *temp_r30;
    void *var_r31;

    var_r31 = (char *)arg0 + 0x1C;
    temp_r29 = (char *)arg0 + arg0->unk0x4;
    while (var_r31 != temp_r29) {
        temp_r30 = fn_8013530C(var_r31, arg1);
        if (arg2 != NULL) {
            arg2(var_r31, arg3, arg4);
        }
        var_r31 = temp_r30;
    }
}
