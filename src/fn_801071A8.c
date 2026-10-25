// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801071A8-0x80107228 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_80106560(Unk_C7387A53 *, s32, s32);
extern s32 fn_801064C8(Unk_C7387A53 *, s32);
s32 fn_801071A8(s32 arg0, s32 arg1, Unk_C7387A53 *arg2, Unk_C7387A53 *arg3, s32 arg4) {
    CStruct *temp_r9;
    Unk_F5317C5D *temp_r9_2;
    Unk_C8FEE62D *var_r31;

    if (arg4 > 0) {
        temp_r9 = arg3->unk0xC;
        if (temp_r9->unk0x4 == -1) {
            var_r31 = NULL;
        } else {
            var_r31 = temp_r9;
        }
        fn_80106560((void *)arg2, arg1, var_r31->unk0x4);
        if (var_r31 != NULL) {
            temp_r9_2 = var_r31->unk0x14;
            ((void (*)(void *, s32))temp_r9_2->unk0xC)(
                (char *)var_r31 + temp_r9_2->unk0x8, 3);
        }
    } else {
        fn_801064C8((void *)arg2, arg1);
    }
    return arg4 - 1;
}
