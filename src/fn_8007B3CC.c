// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B3CC-0x8007B418 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8007AC30(Unk_9994C3F5 *, s32);
s32 fn_8007AB20(CStruct *, s32);
s32 fn_8007B3CC(s32 arg0, s32 arg1) {
    s32 temp_r30;

    temp_r30 = fn_8007AB20(Mem_Alloc2(0x14), arg0);
    fn_8007AC30(temp_r30, arg1);
    return temp_r30;
}
