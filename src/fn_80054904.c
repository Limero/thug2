// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054904-0x80054950 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80054A68(Unk_C7387A53 *, s32, s32, s32, s32);
s32 fn_8007671C(void);
s32 fn_80054904(s32 arg0, s32 arg1) {
    register s32 r30 asm("r30");
    register s32 r29 asm("r29");
    register s32 r28 asm("r28");
    r30 = arg0;
    asm volatile ("" ::: "memory");
    r29 = arg1;
    r28 = fn_8007671C();
    fn_80054A68(r28, r30, r29, 1, 0);
    return r28;
}
