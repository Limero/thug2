// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F321C-0x800F3298 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void fn_800F31EC(void *);
void *fn_800F321C(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 temp_r30;
    s32 temp_r3;
    void *temp_r3_2;
    s32 var_r30;
    s32 var_r31;

    temp_r30 = 1 << arg1;
    *(s32 *)arg0 = arg1;
    var_r31 = temp_r30 - 1;
    temp_r3_2 = Mem_Alloc(temp_r30 * 0xC);
    var_r30 = (s32)temp_r3_2;
    if (temp_r30 != 0) {
        do {
            fn_800F31EC((void *)var_r30);
            var_r30 += 0xC;
            var_r31 -= 1;
        } while (var_r31 != -1);
    }
    arg0->unk0x4 = (s32)temp_r3_2;
    arg0->unk0x8 = 0;
    arg0->unk0x14 = 0;
    return arg0;
}
