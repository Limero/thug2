// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007AC6C-0x8007ACBC (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
void fn_8005BF60(void *, void *, s32, s32);
void *fn_80077BAC(void *);
s32 fn_8007AC6C(s32 arg0, void *arg1, void *arg2) {
    s32 temp_r29;

    temp_r29 = fn_80077BAC(Mem_Alloc2(0x10));
    fn_8005BF60(temp_r29, arg1, arg2, 1);
    return temp_r29;
}
