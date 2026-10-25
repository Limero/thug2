// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007A230-0x8007A2A8 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_8009B3B4(s32, s32, s32, s32, s32, s32, s32);

s32 fn_8007A230(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_r3;

    temp_r3 = Mem_Alloc2(0x1C);
    temp_r3 = fn_8009B3B4(temp_r3, arg1, arg2, arg3, arg4, arg5, arg6);
    arg0->unk0xC = temp_r3;
    if (temp_r3 != 0) {
        temp_r3 = 1;
    } else {
        temp_r3 = 0;
    }
    return temp_r3;
}
