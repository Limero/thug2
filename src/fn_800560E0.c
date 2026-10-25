// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800560E0-0x80056174 (148B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80057C90(CStruct *);
void fn_80055EA4(Unk_FFAD6788 *, CStruct *);
void fn_80057C98(CStruct *, s32);
s32 fn_8005841C(Unk_C8FEE62D *, Unk_C8FEE62D *, s32, s32);
s32 fn_800560E0(void *arg0, Unk_C8FEE62D *arg1, void *arg2, Unk_C8FEE62D *arg3, s32 arg4, s32 arg5) {
    s32 temp_r3;
    Unk_71062261 *var_r30;

    var_r30 = arg2;
    if (var_r30 == NULL) {
        var_r30 = arg0;
    }
    temp_r3 = fn_8005841C(arg1, arg3, arg4, var_r30);
    if (temp_r3 != 0) {
        if (arg5 != 0) {
            fn_80057C98(temp_r3, arg5);
        }
        fn_80055EA4(var_r30, temp_r3);
        if (arg4 != 0) {
            var_r30->unk0x274 = 1;
        }
        return fn_80057C90(temp_r3);
    }
    return 0;
}
