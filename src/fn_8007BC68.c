// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007BC68-0x8007BCAC (68B). Byte-identical.
#include "types.h"
#include "mem.h"
void fn_800585B4(s32, s32);
s32 fn_8007BC68(s32 arg0) {
    s32 temp_r30;

    Mem_Alloc2(0xC);
    temp_r30 = fn_8007B7B0();
    fn_800585B4(temp_r30, arg0);
    return temp_r30;
}
