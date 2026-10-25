// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800549E0-0x80054A68 (136B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_8029311C[];
void fn_80054A68(Unk_C7387A53 *, s32, s32, s32, s32);
s32 fn_80076EEC(Unk_5D1D68CC *, Unk_9994C3F5 *, s32, s32, s32);
void fn_8001075C(s32);
s32 fn_800549E0(s32 arg0, Unk_5D1D68CC *arg1, Unk_9994C3F5 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_r30;

    fn_8001075C(lbl_8029311C);
    temp_r30 = fn_80076EEC(arg1, arg2, arg3, arg4, arg5);
    fn_80010760();
    fn_80054A68(temp_r30, arg0, arg2, 0, arg6);
    return temp_r30;
}
