// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012FD0-0x800130AC (220B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80010670(void *, s32);
void fn_80013788(s32);
s32 fn_800132F8(Unk_DB0E2BAB *, void *, s32, s32);
void fn_80013294(CStruct *, s32, s32, s32);
s32 Mem_Alloc_3(s32);
s32 fn_8001371C(Unk_C8FEE62D *, s32, s32);
s32 fn_800132A4(CStruct *);
s32 fn_80012FD0(Unk_C8FEE62D *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_r29;
    s32 var_r30;
    CStruct *temp_r31;

    temp_r31 = fn_8001371C(arg0, 0, 0x64);
    temp_r29 = fn_800132A4(temp_r31);
    if (arg5 == 0) {
        var_r30 = Mem_Alloc_3((temp_r29 + 0x7FF) & QB_UNKNOWN_0xFFFFF800);
    } else {
        var_r30 = arg5;
    }
    if (arg2 != 0) {
        temp_r31->unk0x10 = 8;
        fn_80013294(temp_r31, arg2, arg3, arg4);
    }
    fn_800132F8(temp_r31, var_r30, 1, temp_r29);
    fn_80013788(temp_r31);
    if ((arg5 == 0) && (var_r30 != 0)) {
        fn_80010670(temp_r29, var_r30);
    }
    if (arg1 != NULL) {
        *arg1 = temp_r29;
    }
    return var_r30;
}
