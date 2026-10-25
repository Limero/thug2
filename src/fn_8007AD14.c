// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007AD14-0x8007AD80 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void Mem_Alloc2(s32);
s32 fn_80077BAC(void);
void fn_8005C038(s32, s32, s32, s32, s32, s32, s32);
s32 fn_8007AD14(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_r30;

    Mem_Alloc2(0x10);
    temp_r30 = fn_80077BAC();
    fn_8005C038(temp_r30, arg1, arg2, arg3, arg4, arg5, arg6);
    return temp_r30;
}
